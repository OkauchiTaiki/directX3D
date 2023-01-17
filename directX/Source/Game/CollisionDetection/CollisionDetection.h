#pragma once

enum CollisionDetectionResult
{
    COLLISION_TRUE,
    COLLISION_FALSE,
    COLLISION_SINKING_INTO
};

class CollisionDetection
{ 
public:
    static const float collisionDistance;
private:
    //�e�Փˌ��m�̊֐�������֐��|�C���^�[�̔z��
    static CollisionDetectionResult(*collisionDetectionArray[OBJECT_TYPE_NUM][OBJECT_TYPE_NUM])(const Object* object1, const Object* object2);

public:
    //���̊֐����o�R���ēK�؂ȃI�u�W�F�N�g�̑g�ݍ��킹�̊֐����Ăяo��
    static CollisionDetectionResult detectCollision(const Object* object1, const Object* object2);

private:
    CollisionDetection() {}
    ~CollisionDetection() {}

    static void initializeCollisionDetection();

    static CollisionDetectionResult pointAndRectangle(const XMFLOAT3* point, const Object* rectangle);
    static CollisionDetectionResult pointAndCube(const XMFLOAT3* point, const Object* Cube);
    static CollisionDetectionResult pointAndSphere(const XMFLOAT3* point, const Object* Sphere);
 
    static CollisionDetectionResult lineAndLine(const Object* line1, const Object* line2);
    static CollisionDetectionResult lineAndRectangle(const Object* object1, const Object* object2);
    static CollisionDetectionResult lineAndCube(const Object* object1, const Object* object2);
    static CollisionDetectionResult lineAndSphere(const Object* object1, const Object* object2);

    static CollisionDetectionResult rectangleAndRectangle(const Object* rectangle1, const Object* rectangle2);
    static CollisionDetectionResult rectangleAndCube(const Object* object1, const Object* object2);
    static CollisionDetectionResult rectangleAndSphere(const Object* object1, const Object* object2);

    static CollisionDetectionResult cubeAndCube(const Object* cube1, const Object* cube2);
    static CollisionDetectionResult cubeAndSphere(const Object* object1, const Object* object2);

    static CollisionDetectionResult sphereAndSphere(const Object* sphere1, const Object* sphere2);
};
