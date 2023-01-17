#include "framework.h"
#include "Source\environment.h"

const float CollisionDetection::collisionDistance = 0.1f;

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
	return (*collisionDetectionArray[object1->getType()][object2->getType()])(object1, object2);
}

CollisionDetectionResult pointAndRectangle(const XMFLOAT3* point, const Object* rectangle)
{

}

CollisionDetectionResult pointAndCube(const XMFLOAT3* point, const Object* Cube)
{

}

CollisionDetectionResult pointAndSphere(const XMFLOAT3* point, const Object* Sphere)
{

}

CollisionDetectionResult lineAndLine(const Object* line1, const Object* line2)
{

}

CollisionDetectionResult lineAndRectangle(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult lineAndCube(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult lineAndSphere(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult rectangleAndRectangle(const Object* rectangle1, const Object* rectangle2)
{

}

CollisionDetectionResult rectangleAndCube(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult rectangleAndSphere(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult cubeAndCube(const Object* cube1, const Object* cube2)
{

}

CollisionDetectionResult cubeAndSphere(const Object* object1, const Object* object2)
{

}

CollisionDetectionResult sphereAndSphere(const Object* sphere1, const Object* sphere2)
{
	float distance = sphere1->position - sphere2->position
}