#pragma once

enum CollisionDetectionResult
{
    COLLISION_FALSE = 0,
    COLLISION_TRUE,
    COLLISION_SINKING_INTO
};

class CollisionDetection
{ 
public:
    static const float collisionTrueDistance;
    static const float insideOutsideDetectionAngle;   //���͎l�p�`�p�B���̑��̑��p�`��������Βǉ�����B
    static const float correctionMagnificationOfCubeAndSphere;

private:
    //�e�Փˌ��m�̊֐�������֐��|�C���^�[�̔z��
    static CollisionDetectionResult(*collisionDetectionArray[OBJECT_TYPE_NUM][OBJECT_TYPE_NUM])(const Object& object1, const Object& object2);

public:
    static void initializeCollisionDetection();
    //���̊֐����o�R���ēK�؂ȃI�u�W�F�N�g�̑g�ݍ��킹�̊֐����Ăяo��
    static CollisionDetectionResult detectCollision(const Object* object1, const Object* object2);

private:
    CollisionDetection() {}
    ~CollisionDetection() {}

    static CollisionDetectionResult pointAndRectangle(const XMFLOAT3& point, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4, float valueOfSinkingInto = 0.0f);
    static CollisionDetectionResult pointAndCube(const XMFLOAT3& point, const Object& cube);
    static CollisionDetectionResult pointAndSphere(const XMFLOAT3& point, const Object& sphere);
 
    static CollisionDetectionResult lineAndLine(const Object& line1, const Object& line2);
    static CollisionDetectionResult lineAndRectangle(const Object& object1, const Object& object2);
    static CollisionDetectionResult lineAndRectangle(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4);
    static CollisionDetectionResult lineAndCube(const Object& object1, const Object& object2);
    static CollisionDetectionResult lineAndCube(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Object& cube);
    static CollisionDetectionResult lineAndSphere(const Object& object1, const Object& object2);
    static CollisionDetectionResult lineAndSphere(const XMFLOAT3& lineStartPoint, const XMFLOAT3& lineEndPoint, const Object& sphere);

    static CollisionDetectionResult rectangleAndRectangle(const Object& rectangle1, const Object& rectangle2);
    static CollisionDetectionResult rectangleAndCube(const Object& object1, const Object& object2);
    static CollisionDetectionResult rectangleAndSphere(const Object& object1, const Object& object2);
    static CollisionDetectionResult rectangleAndSphere(const Vertex& vertex1, const Vertex& vertex2, const Vertex& vertex3, const Vertex& vertex4, const Object& sphere);

    static CollisionDetectionResult cubeAndCube(const Object& cube1, const Object& cube2);
    static CollisionDetectionResult cubeAndSphere(const Object& object1, const Object& object2);

    static CollisionDetectionResult sphereAndSphere(const Object& sphere1, const Object& sphere2);
};
