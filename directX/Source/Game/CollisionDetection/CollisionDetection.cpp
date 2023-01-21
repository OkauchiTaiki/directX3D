#include "framework.h"
#include "Source\environment.h"

const float CollisionDetection::collisionTrueDistance = 0.04f;
const float CollisionDetection::insideOutsideDetectionAngle = 2.0f * PI - PI / 90.0f;   //358°
const float CollisionDetection::correctionMagnificationOfCubeAndSphere = 0.90f;
CollisionDetectionResult(*CollisionDetection::collisionDetectionArray[OBJECT_TYPE_NUM][OBJECT_TYPE_NUM])(const Object& object1, const Object& object2) = { nullptr };

void CollisionDetection::initializeCollisionDetection()
{
	collisionDetectionArray[OBJECT_LINE][OBJECT_LINE] = &lineAndLine;
	collisionDetectionArray[OBJECT_LINE][OBJECT_RECTANGLE] = &lineAndRectangle;
	collisionDetectionArray[OBJECT_LINE][OBJECT_CUBE] = &lineAndCube;
	collisionDetectionArray[OBJECT_LINE][OBJECT_SPHERE] = &lineAndSphere;

	collisionDetectionArray[OBJECT_RECTANGLE][OBJECT_LINE] = &lineAndRectangle;
	collisionDetectionArray[OBJECT_RECTANGLE][OBJECT_RECTANGLE] = &rectangleAndRectangle;
	collisionDetectionArray[OBJECT_RECTANGLE][OBJECT_CUBE] = &rectangleAndCube;
	collisionDetectionArray[OBJECT_RECTANGLE][OBJECT_SPHERE] = &rectangleAndSphere;

	collisionDetectionArray[OBJECT_CUBE][OBJECT_LINE] = &lineAndCube;
	collisionDetectionArray[OBJECT_CUBE][OBJECT_RECTANGLE] = &rectangleAndCube;
	collisionDetectionArray[OBJECT_CUBE][OBJECT_CUBE] = &cubeAndCube;
	collisionDetectionArray[OBJECT_CUBE][OBJECT_SPHERE] = &cubeAndSphere;

	collisionDetectionArray[OBJECT_SPHERE][OBJECT_LINE] = &lineAndSphere;
	collisionDetectionArray[OBJECT_SPHERE][OBJECT_RECTANGLE] = &rectangleAndSphere;
	collisionDetectionArray[OBJECT_SPHERE][OBJECT_CUBE] = &cubeAndSphere;
	collisionDetectionArray[OBJECT_SPHERE][OBJECT_SPHERE] = &sphereAndSphere;
}

CollisionDetectionResult CollisionDetection::detectCollision(const Object* object1, const Object* object2)
{
	return (*collisionDetectionArray[object1->getType()][object2->getType()])(*object1, *object2);
}

CollisionDetectionResult CollisionDetection::pointAndRectangle(const XMFLOAT3& point, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4, float valueOfSinkingInto)
{
	//点から平面までの最短距離を求める
	XMFLOAT3 vertexToPoint = point - vertex1.pos;
	float distance = OriginalMath::dot(vertexToPoint, vertex1.normal);

	//距離が0より大きい場合は当たっていない
	if (distance > 0.0f)
	{
		return COLLISION_FALSE;
	}

	//0以下の場合は当たっている可能性がある
	//上記の条件では無限に広がる平面と仮定した場合になるため、そもそも平面ポリゴンの範囲内かどうか調べる必要がある
	//まず点を平面に投射したときの位置を求める
	XMFLOAT3 projectionPos = point + vertex1.normal * -distance;

	//その位置を基準として各頂点間の角度を求める
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - projectionPos, vertex2.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex2.pos - projectionPos, vertex3.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex3.pos - projectionPos, vertex4.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex4.pos - projectionPos, vertex1.pos - projectionPos);

	//和が一定値（理論値360°）未満なら範囲外
	if (angleSum < insideOutsideDetectionAngle)
	{
		return COLLISION_FALSE;
	}

	//最終的にはポリゴン範囲内かつ -1.0f * collisionTrueDistance <= distance <= 0.0f なら当たっているとする。
	if (distance >= -collisionTrueDistance)   return COLLISION_TRUE;
	if (distance >= -valueOfSinkingInto)   return COLLISION_SINKING_INTO;   //めり込みの判定
	return COLLISION_FALSE;   //それ以外は当たっていない
}

CollisionDetectionResult CollisionDetection::pointAndCube(const XMFLOAT3& point, const Object& cube)
{
	CollisionDetectionResult result = COLLISION_FALSE;
	for (int i = 0; i < 6; i++)
	{
		float halfSideLength;
		if     (i == 0 || i == 1)   halfSideLength = cube.size.y * cube.scale.y;
		else if(i == 2 || i == 3)   halfSideLength = cube.size.z * cube.scale.z;
		else                        halfSideLength = cube.size.x * cube.scale.x;

		CollisionDetectionResult instantResult = pointAndRectangle(point, cube.vertex[i * 4 + 0], cube.vertex[i * 4 + 1], cube.vertex[i * 4 + 2], cube.vertex[i * 4 + 3], halfSideLength);
		if (instantResult == COLLISION_SINKING_INTO)
		{
			result = COLLISION_SINKING_INTO;
		}
		else if (instantResult == COLLISION_TRUE)
		{
			return COLLISION_TRUE;
		}
	}

	return result;
}

CollisionDetectionResult CollisionDetection::pointAndSphere(const XMFLOAT3& point, const Object& sphere)
{
	float distance = OriginalMath::length(point - sphere.position);
	float radius = sphere.size.x * sphere.scale.x / 2.0f;

	CollisionDetectionResult result = COLLISION_FALSE;
	if (radius - distance >= 0.0f)
	{
		result = COLLISION_SINKING_INTO;
		if (radius - distance <= collisionTrueDistance)
		{
			result = COLLISION_TRUE;
		}
	}

	return result;
}

CollisionDetectionResult CollisionDetection::lineAndLine(const Object& line1, const Object& line2)
{
	return COLLISION_FALSE;   //使う予定なし
}

CollisionDetectionResult CollisionDetection::lineAndRectangle(const Object& object1, const Object& object2)
{
	const Object& line = object1.getType() == OBJECT_LINE ? object1 : object2;
	const Object& rectangle = object1.getType() == OBJECT_RECTANGLE ? object1 : object2;

	return lineAndRectangle(line.vertex[0].pos, line.vertex[1].pos, rectangle.vertex[0], rectangle.vertex[1], rectangle.vertex[2], rectangle.vertex[3]);
}

CollisionDetectionResult CollisionDetection::lineAndRectangle(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4)
{
	//まずは線分と無限に広がる平面の当たり判定を取る
	//法線ベクトルを使って、線分の両端が平面の表と裏にあるかを調べることで判定を取る
	float startPointDot = OriginalMath::dot(lineStartPoint - vertex1.pos, vertex1.normal);
	float endPointDot = OriginalMath::dot(lineEndPoint - vertex1.pos, vertex1.normal);
	//この二つの積がマイナスなら無限平面に衝突している。プラスなら衝突していない。
	if (startPointDot * endPointDot >= 0.0f)
	{
		return COLLISION_FALSE;
	}

	//次に無限平面ではなくポリゴン内に線分が貫通しているかを調べる。貫通していれば衝突していることになる。
	XMFLOAT3 vertexToStartPoint = lineStartPoint - vertex1.pos;
	float distanceOfStartPoint = fabsf(OriginalMath::dot(vertexToStartPoint, vertex1.normal));
	XMFLOAT3 vertexToEndPoint = lineEndPoint - vertex1.pos;
	float distanceOfEndPoint = fabsf(OriginalMath::dot(vertexToEndPoint, vertex1.normal));
	//内分比を求める
	float internalRatio = distanceOfStartPoint / (distanceOfStartPoint + distanceOfEndPoint);
	//貫通している点の座標を求める
	XMFLOAT3 penetratingPoint = vertex1.pos + vertexToStartPoint * (1 - internalRatio) + vertexToEndPoint * internalRatio;

	//貫通している点が内部かどうか調べる
	//その位置を基準として各頂点間の角度を求める
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - penetratingPoint, vertex2.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex2.pos - penetratingPoint, vertex3.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex3.pos - penetratingPoint, vertex4.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex4.pos - penetratingPoint, vertex1.pos - penetratingPoint);

	//和が一定値（理論値360°）未満なら範囲外
	if (angleSum < insideOutsideDetectionAngle)
	{
		return COLLISION_FALSE;
	}
	else
	{
		return COLLISION_TRUE;
	}
}

CollisionDetectionResult CollisionDetection::lineAndCube(const Object& object1, const Object& object2)
{
	return COLLISION_FALSE;   //使う予定なし
}

CollisionDetectionResult CollisionDetection::lineAndCube(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Object& cube)
{
	for (int i = 0; i < 6; i++)
	{
		if (lineAndRectangle(lineStartPoint, lineEndPoint, cube.vertex[i * 4 + 0], cube.vertex[i * 4 + 1], cube.vertex[i * 4 + 2], cube.vertex[i * 4 + 3]))
		{
			return COLLISION_TRUE;
		}
	}

	return COLLISION_FALSE;
}

CollisionDetectionResult CollisionDetection::lineAndSphere(const Object& object1, const Object& object2)
{
	return COLLISION_FALSE;   //使う予定なし
}

CollisionDetectionResult CollisionDetection::lineAndSphere(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Object& sphere)
{
	//線分の単位ベクトルを求める
	XMFLOAT3 unitVector = OriginalMath::normalize(lineEndPoint - lineStartPoint);
	//始点から球の中心部までのベクトルを求める
	XMFLOAT3 startToPoint = sphere.position - lineStartPoint;
	//単位ベクトルとの内積を使って、線分上の中で最も近い点を求める
	XMFLOAT3 closestPosition{};
	float dot = OriginalMath::dot(startToPoint, unitVector);
	if (dot <= 0.0f)
	{
		closestPosition = lineStartPoint;
	}
	else if(dot >= OriginalMath::length(lineEndPoint - lineStartPoint))
	{
		closestPosition = lineEndPoint;
	}
	else
	{
		closestPosition = lineStartPoint + unitVector * dot;
	}

	float radius = sphere.size.x * sphere.scale.x / 2.0f;
	float distance = OriginalMath::length(sphere.position - closestPosition);

	if (radius < distance)   return COLLISION_FALSE;
	if (radius - distance <= collisionTrueDistance)   return COLLISION_TRUE;
	return COLLISION_SINKING_INTO;
}

CollisionDetectionResult CollisionDetection::rectangleAndRectangle(const Object& rectangle1, const Object& rectangle2)
{
	return COLLISION_FALSE;   //使う予定なし
}

CollisionDetectionResult CollisionDetection::rectangleAndCube(const Object& object1, const Object& object2)
{
	return COLLISION_FALSE;   //使う予定なし
}

CollisionDetectionResult CollisionDetection::rectangleAndSphere(const Object& object1, const Object& object2)
{
	const Object& rectangle = object1.getType() == OBJECT_RECTANGLE ? object1 : object2;
	const Object& sphere = object1.getType() == OBJECT_SPHERE ? object1 : object2;

	return rectangleAndSphere(rectangle.vertex[0], rectangle.vertex[1], rectangle.vertex[2], rectangle.vertex[3], sphere);
}

CollisionDetectionResult CollisionDetection::rectangleAndSphere(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4, const Object& sphere)
{
	CollisionDetectionResult result = COLLISION_FALSE;

	//点から平面までの最短距離を求める
	XMFLOAT3 vertexToPoint = sphere.position - vertex1.pos;
	float distance = OriginalMath::dot(vertexToPoint, vertex1.normal);
	float radius = sphere.size.x * sphere.scale.x / 2.0f;

	if (radius < fabsf(distance))
	{
		return COLLISION_FALSE;
	}

	//上記の条件では無限に広がる平面と仮定した場合になるため、そもそも平面ポリゴンの範囲内かどうか調べる必要がある
	//まず点を平面に投射したときの位置を求める
	XMFLOAT3 projectionPos = sphere.position + vertex1.normal * -distance;

	//その位置を基準として各頂点間の角度を求める
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - projectionPos, vertex2.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex2.pos - projectionPos, vertex3.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex3.pos - projectionPos, vertex4.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex4.pos - projectionPos, vertex1.pos - projectionPos);

	//和が一定値（理論値360°）未満なら範囲外。以上なら範囲内。
	if (angleSum >= insideOutsideDetectionAngle)
	{
		if (radius - fabsf(distance) <= collisionTrueDistance)
		{
			return COLLISION_TRUE;
		}
		else
		{
			return COLLISION_SINKING_INTO;
		}
	}

	const Vertex* vertex[4] = {&vertex1, &vertex2, &vertex3, &vertex4};
	for (int i = 0; i < 4; i++)
	{
		CollisionDetectionResult instantResult = lineAndSphere(vertex[i]->pos, vertex[i >= 3 ? 0 : i + 1]->pos, sphere);
		if (instantResult == COLLISION_SINKING_INTO)
		{
			return COLLISION_SINKING_INTO;
		}
		else if (instantResult == COLLISION_TRUE)
		{
			result = COLLISION_TRUE;
		}
	}

	return result;
}

CollisionDetectionResult CollisionDetection::cubeAndCube(const Object& cube1, const Object& cube2)
{
	//---------------------------------
	//頂点と平面（物理挙動の時に使う）
	//---------------------------------
	//CollisionDetectionResult result = COLLISION_FALSE;
	/*for (int i = 0; i < 8; i++)
	{
		CollisionDetectionResult instantResult = pointAndCube(cube1.vertex[i].pos, cube2);
		if (instantResult == COLLISION_SINKING_INTO)
		{
			result = COLLISION_SINKING_INTO;
		}
		else if (instantResult == COLLISION_TRUE)
		{
			return COLLISION_TRUE;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		CollisionDetectionResult instantResult = pointAndCube(cube2.vertex[i].pos, cube1);
		if (instantResult == COLLISION_SINKING_INTO)
		{
			result = COLLISION_SINKING_INTO;
		}
		else if (instantResult == COLLISION_TRUE)
		{
			return COLLISION_TRUE;
		}
	}*/

	//どちらかのcubeの座標が、もう片方のcube内にある場合は無条件にめり込みで返す
	if (pointAndCube(cube1.position, cube2))   return COLLISION_SINKING_INTO;
	if (pointAndCube(cube2.position, cube1))   return COLLISION_SINKING_INTO;

	//とりあえずめり込みは考慮しないやり方(辺と面)
	if (lineAndCube(cube1.vertex[0].pos, cube1.vertex[1].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[1].pos, cube1.vertex[2].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[2].pos, cube1.vertex[3].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[3].pos, cube1.vertex[0].pos, cube2))   return COLLISION_TRUE;

	if (lineAndCube(cube1.vertex[4].pos, cube1.vertex[5].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[5].pos, cube1.vertex[6].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[6].pos, cube1.vertex[7].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[7].pos, cube1.vertex[4].pos, cube2))   return COLLISION_TRUE;

	if (lineAndCube(cube1.vertex[0].pos, cube1.vertex[4].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[1].pos, cube1.vertex[5].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[2].pos, cube1.vertex[6].pos, cube2))   return COLLISION_TRUE;
	if (lineAndCube(cube1.vertex[3].pos, cube1.vertex[7].pos, cube2))   return COLLISION_TRUE;

	return COLLISION_FALSE;
}

CollisionDetectionResult CollisionDetection::cubeAndSphere(const Object& object1, const Object& object2)
{
	CollisionDetectionResult result = COLLISION_FALSE;
	const Object& cube = object1.getType() == OBJECT_CUBE ? object1 : object2;
	const Object& sphere = object1.getType() == OBJECT_SPHERE ? object1 : object2;

	//sphereの座標がcubeの内部にある場合、無条件にめり込みで返す
	if (pointAndCube(sphere.position, cube))   return COLLISION_SINKING_INTO;

	for (int i = 0; i < 6; i++)
	{
		CollisionDetectionResult instantResult = rectangleAndSphere(cube.vertex[i * 4 + 0], cube.vertex[i * 4 + 1], cube.vertex[i * 4 + 2], cube.vertex[i * 4 + 3], sphere);
		if (instantResult == COLLISION_SINKING_INTO)
		{
			return COLLISION_SINKING_INTO;
		}
		else if (instantResult == COLLISION_TRUE)
		{
			result = COLLISION_TRUE;
		}
	}

	return result;
}

CollisionDetectionResult CollisionDetection::sphereAndSphere(const Object& sphere1, const Object& sphere2)
{
	float distance = OriginalMath::length(sphere1.position - sphere2.position);
	float radiusSum = sphere1.size.x * sphere1.scale.x / 2.0f + sphere2.size.x * sphere2.scale.x / 2.0f;

	CollisionDetectionResult result = COLLISION_FALSE;
	if (radiusSum - distance >= 0.0f)
	{
		result = COLLISION_SINKING_INTO;
		if (radiusSum - distance <= collisionTrueDistance)
		{
			result = COLLISION_TRUE;
		}
	}

	return result;
}