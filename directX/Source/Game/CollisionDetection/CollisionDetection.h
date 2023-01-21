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
    static const float insideOutsideDetectionAngle;   //今は四角形用。その他の多角形が増えれば追加する。
    static const float correctionMagnificationOfCubeAndSphere;

private:
    //各衝突検知の関数を入れる関数ポインターの配列
    static CollisionDetectionResult(*collisionDetectionArray[OBJECT_TYPE_NUM][OBJECT_TYPE_NUM])(const Object& object1, const Object& object2);

public:
    static void initializeCollisionDetection();
    //この関数を経由して適切なオブジェクトの組み合わせの関数を呼び出す
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
