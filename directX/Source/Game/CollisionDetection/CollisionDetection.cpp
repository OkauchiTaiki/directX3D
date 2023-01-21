#include "framework.h"
#include "Source\environment.h"

const float CollisionDetection::collisionTrueDistance = 0.04f;
const float CollisionDetection::insideOutsideDetectionAngle = 2.0f * PI - PI / 90.0f;   //358��
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
	//�_���畽�ʂ܂ł̍ŒZ���������߂�
	XMFLOAT3 vertexToPoint = point - vertex1.pos;
	float distance = OriginalMath::dot(vertexToPoint, vertex1.normal);

	//������0���傫���ꍇ�͓������Ă��Ȃ�
	if (distance > 0.0f)
	{
		return COLLISION_FALSE;
	}

	//0�ȉ��̏ꍇ�͓������Ă���\��������
	//��L�̏����ł͖����ɍL���镽�ʂƉ��肵���ꍇ�ɂȂ邽�߁A�����������ʃ|���S���͈͓̔����ǂ������ׂ�K�v������
	//�܂��_�𕽖ʂɓ��˂����Ƃ��̈ʒu�����߂�
	XMFLOAT3 projectionPos = point + vertex1.normal * -distance;

	//���̈ʒu����Ƃ��Ċe���_�Ԃ̊p�x�����߂�
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - projectionPos, vertex2.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex2.pos - projectionPos, vertex3.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex3.pos - projectionPos, vertex4.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex4.pos - projectionPos, vertex1.pos - projectionPos);

	//�a�����l�i���_�l360���j�����Ȃ�͈͊O
	if (angleSum < insideOutsideDetectionAngle)
	{
		return COLLISION_FALSE;
	}

	//�ŏI�I�ɂ̓|���S���͈͓����� -1.0f * collisionTrueDistance <= distance <= 0.0f �Ȃ瓖�����Ă���Ƃ���B
	if (distance >= -collisionTrueDistance)   return COLLISION_TRUE;
	if (distance >= -valueOfSinkingInto)   return COLLISION_SINKING_INTO;   //�߂荞�݂̔���
	return COLLISION_FALSE;   //����ȊO�͓������Ă��Ȃ�
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
	return COLLISION_FALSE;   //�g���\��Ȃ�
}

CollisionDetectionResult CollisionDetection::lineAndRectangle(const Object& object1, const Object& object2)
{
	const Object& line = object1.getType() == OBJECT_LINE ? object1 : object2;
	const Object& rectangle = object1.getType() == OBJECT_RECTANGLE ? object1 : object2;

	return lineAndRectangle(line.vertex[0].pos, line.vertex[1].pos, rectangle.vertex[0], rectangle.vertex[1], rectangle.vertex[2], rectangle.vertex[3]);
}

CollisionDetectionResult CollisionDetection::lineAndRectangle(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4)
{
	//�܂��͐����Ɩ����ɍL���镽�ʂ̓����蔻������
	//�@���x�N�g�����g���āA�����̗��[�����ʂ̕\�Ɨ��ɂ��邩�𒲂ׂ邱�ƂŔ�������
	float startPointDot = OriginalMath::dot(lineStartPoint - vertex1.pos, vertex1.normal);
	float endPointDot = OriginalMath::dot(lineEndPoint - vertex1.pos, vertex1.normal);
	//���̓�̐ς��}�C�i�X�Ȃ疳�����ʂɏՓ˂��Ă���B�v���X�Ȃ�Փ˂��Ă��Ȃ��B
	if (startPointDot * endPointDot >= 0.0f)
	{
		return COLLISION_FALSE;
	}

	//���ɖ������ʂł͂Ȃ��|���S�����ɐ������ђʂ��Ă��邩�𒲂ׂ�B�ђʂ��Ă���ΏՓ˂��Ă��邱�ƂɂȂ�B
	XMFLOAT3 vertexToStartPoint = lineStartPoint - vertex1.pos;
	float distanceOfStartPoint = fabsf(OriginalMath::dot(vertexToStartPoint, vertex1.normal));
	XMFLOAT3 vertexToEndPoint = lineEndPoint - vertex1.pos;
	float distanceOfEndPoint = fabsf(OriginalMath::dot(vertexToEndPoint, vertex1.normal));
	//����������߂�
	float internalRatio = distanceOfStartPoint / (distanceOfStartPoint + distanceOfEndPoint);
	//�ђʂ��Ă���_�̍��W�����߂�
	XMFLOAT3 penetratingPoint = vertex1.pos + vertexToStartPoint * (1 - internalRatio) + vertexToEndPoint * internalRatio;

	//�ђʂ��Ă���_���������ǂ������ׂ�
	//���̈ʒu����Ƃ��Ċe���_�Ԃ̊p�x�����߂�
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - penetratingPoint, vertex2.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex2.pos - penetratingPoint, vertex3.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex3.pos - penetratingPoint, vertex4.pos - penetratingPoint);
	angleSum += OriginalMath::angle(vertex4.pos - penetratingPoint, vertex1.pos - penetratingPoint);

	//�a�����l�i���_�l360���j�����Ȃ�͈͊O
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
	return COLLISION_FALSE;   //�g���\��Ȃ�
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
	return COLLISION_FALSE;   //�g���\��Ȃ�
}

CollisionDetectionResult CollisionDetection::lineAndSphere(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Object& sphere)
{
	//�����̒P�ʃx�N�g�������߂�
	XMFLOAT3 unitVector = OriginalMath::normalize(lineEndPoint - lineStartPoint);
	//�n�_���狅�̒��S���܂ł̃x�N�g�������߂�
	XMFLOAT3 startToPoint = sphere.position - lineStartPoint;
	//�P�ʃx�N�g���Ƃ̓��ς��g���āA������̒��ōł��߂��_�����߂�
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
	return COLLISION_FALSE;   //�g���\��Ȃ�
}

CollisionDetectionResult CollisionDetection::rectangleAndCube(const Object& object1, const Object& object2)
{
	return COLLISION_FALSE;   //�g���\��Ȃ�
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

	//�_���畽�ʂ܂ł̍ŒZ���������߂�
	XMFLOAT3 vertexToPoint = sphere.position - vertex1.pos;
	float distance = OriginalMath::dot(vertexToPoint, vertex1.normal);
	float radius = sphere.size.x * sphere.scale.x / 2.0f;

	if (radius < fabsf(distance))
	{
		return COLLISION_FALSE;
	}

	//��L�̏����ł͖����ɍL���镽�ʂƉ��肵���ꍇ�ɂȂ邽�߁A�����������ʃ|���S���͈͓̔����ǂ������ׂ�K�v������
	//�܂��_�𕽖ʂɓ��˂����Ƃ��̈ʒu�����߂�
	XMFLOAT3 projectionPos = sphere.position + vertex1.normal * -distance;

	//���̈ʒu����Ƃ��Ċe���_�Ԃ̊p�x�����߂�
	float angleSum = 0.0f;
	angleSum += OriginalMath::angle(vertex1.pos - projectionPos, vertex2.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex2.pos - projectionPos, vertex3.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex3.pos - projectionPos, vertex4.pos - projectionPos);
	angleSum += OriginalMath::angle(vertex4.pos - projectionPos, vertex1.pos - projectionPos);

	//�a�����l�i���_�l360���j�����Ȃ�͈͊O�B�ȏ�Ȃ�͈͓��B
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
	//���_�ƕ��ʁi���������̎��Ɏg���j
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

	//�ǂ��炩��cube�̍��W���A�����Е���cube���ɂ���ꍇ�͖������ɂ߂荞�݂ŕԂ�
	if (pointAndCube(cube1.position, cube2))   return COLLISION_SINKING_INTO;
	if (pointAndCube(cube2.position, cube1))   return COLLISION_SINKING_INTO;

	//�Ƃ肠�����߂荞�݂͍l�����Ȃ�����(�ӂƖ�)
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

	//sphere�̍��W��cube�̓����ɂ���ꍇ�A�������ɂ߂荞�݂ŕԂ�
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