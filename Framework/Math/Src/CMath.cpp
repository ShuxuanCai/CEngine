#include "Precompiled.h"
#include "CMath.h"

using namespace CEngine::Math;

const Vector2 Vector2::Zero(0.0f);
const Vector2 Vector2::One(1.0f, 1.0f);
const Vector2 Vector2::XAxis(1.0f, 0.0f);
const Vector2 Vector2::YAxis(0.0f, 1.0f);

const Vector3 Vector3::Zero(0.0f);
const Vector3 Vector3::One(1.0f);
const Vector3 Vector3::XAxis(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZAxis(0.0f, 0.0f, 1.0f);

Matrix4 Matrix4::RotationAxis(const Vector3& axis, float rad)
{
    const Vector3 u = Normalize(axis);
    const float x = u.x;
    const float y = u.y;
    const float z = u.z;
    const float s = sin(rad);
    const float c = cos(rad);

    return {
        c + (x * x * (1.0f - c)),
        x * y * (1.0f - c) + z * s,
        x * z * (1.0f - c) - y * s,
        0.0f,

        x * y * (1.0f - c) - z * s,
        c + (y * y * (1.0f - c)),
        y * z * (1.0f - c) + x * s,
        0.0f,

        x * z * (1.0f - c) + y * s,
        y * z * (1.0f - c) - x * s,
        c + (z * z * (1.0f - c)),
        0.0f,

        0.0f, 0.0f, 0.0f, 1.0f
    };
}

const Quaternion Quaternion::Zero{ 0.0f, 0.0f, 0.0f, 0.0f };
const Quaternion Quaternion::Indentity{ 0.0f, 0.0f, 0.0f, 1.0f }; // ??? I check online, it said
// indentity Quaternion is {0,0,0,1}, but in the PPT in class, it said {1,0,0,0}, which one is right

Quaternion Quaternion::RotationAxis(const Vector3& axis, float rad)
{
    Vector3 n = Normalize(axis);
    Quaternion q = { sin(rad / 2.0f) * n.x, sin(rad / 2.0f) * n.y, sin(rad / 2.0f) * n.z, cos(rad / 2.0f) };
    return q;
}

//http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/
Quaternion Quaternion::MatrixToQuaternion(const Matrix4& m)
{
    Matrix4 matrix = Transpose(m);
    float tr = matrix._11 + matrix._22 + matrix._33;

    float qw, qx, qy, qz;
    if (tr > 0)
    {
        float w = sqrt(tr + 1.0f) * 2.0f;
        qw = 0.25f * w;
        qx = (matrix._32 - matrix._23) / w;
        qy = (matrix._13 - matrix._31) / w;
        qz = (matrix._21 - matrix._12) / w;
    }
    else if ((matrix._11 > matrix._22) && (matrix._11 > matrix._33))
    {
        float w = sqrt(1.0f + matrix._11 - matrix._22 - matrix._33) * 2.0f;
        qw = (matrix._32 - matrix._23) / w;
        qx = 0.25f * w;
        qy = (matrix._12 + matrix._21) / w;
        qz = (matrix._13 + matrix._31) / w;
    }
    else if (matrix._22 > matrix._33)
    {
        float w = sqrt(1.0f + matrix._22 - matrix._11 - matrix._33) * 2.0f;
        qw = (matrix._13 - matrix._31) / w;
        qx = (matrix._12 + matrix._21) / w;
        qy = 0.25f * w;
        qz = (matrix._23 + matrix._32) / w;
    }
    else
    {
        float w = sqrt(1.0f + matrix._33 - matrix._11 - matrix._22) * 2.0f;
        qw = (matrix._21 - matrix._12) / w;
        qx = (matrix._13 + matrix._31) / w;
        qy = (matrix._23 + matrix._32) / w;
        qz = 0.25f * w;
    }

    return Normalize(Quaternion(qx, qy, qz, qw));
}

Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& up)
{
    Vector3 z = Normalize(forward);
    Vector3 x = Normalize(Cross(up, z));
    Vector3 y = Normalize(Cross(z, x));
    Matrix4 m
    (
        x.x, x.y, x.z, 0.0f,
        y.x, y.y, y.z, 0.0f,
        z.x, z.y, z.z, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    Quaternion q = MatrixToQuaternion(m);
    return q;
}

//Matrix4 Matrix4::RotationQuaternion(const Quaternion& q)
//{
//    return
//    {
//        1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
//        (2.0f * q.x * q.y) + (2.0f * q.z * q.w),
//        (2.0f * q.x * q.z) - (2.0f * q.y * q.w),
//        0.0f,
//
//        (2.0f * q.x * q.y) - (2.0f * q.w * q.z),
//        1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
//        (2.0f * q.y * q.z) + (2.0f * q.w * q.x),
//        0.0f,
//
//        (2.0f * q.x * q.z) + (2.0f * q.w * q.y),
//        (2.0f * q.y * q.z) - (2.0f * q.w * q.x),
//        1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
//        0.0f,
//
//        0.0f, 0.0f, 0.0f, 1.0f
//    };
//}

Matrix4 Quaternion::MatrixRatationFromQuaternion(const Quaternion& q)
{
    return Matrix4
    (
        1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
        (2.0f * q.x * q.y) + (2.0f * q.z * q.w),
        (2.0f * q.x * q.z) - (2.0f * q.y * q.w),
        0.0f,

        (2.0f * q.x * q.y) - (2.0f * q.z * q.w),
        1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
        (2.0f * q.y * q.z) + (2.0f * q.x * q.w),
        0.0f,

        (2.0f * q.x * q.z) + (2.0f * q.y * q.w),
        (2.0f * q.y * q.z) - (2.0f * q.x * q.w),
        1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
        0.0f,

        0.0f,
        0.0f,
        0.0f,
        1.0f
    );
}

Quaternion Quaternion::Slerp(Quaternion q0, Quaternion q1, float t)
{
    float dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

    /*if (dot < 0.0f)
    {
        dot = -dot;
        q1.x = -q1.x;
        q1.y = -q1.y;
        q1.z = -q1.z;
        q1.w = -q1.w;
    }*/
    if (dot > 0.999f)
    {
        return Normalize(Lerp(q0, q1, t));
    }

    float angle = acosf(dot);
    float sinAngle = sinf(angle);
    float s0 = sinf(angle * (1.0f - t)) / sinAngle;
    float s1 = sinf(angle * t) / sinAngle;

    return Quaternion
    (
        (q0.x * s0) + (q1.x * s1),
        (q0.y * s0) + (q1.y * s1),
        (q0.z * s0) + (q1.z * s1),
        (q0.w * s0) + (q1.w * s1)
    );
}

Quaternion Quaternion::Invert(const Quaternion& q)
{
    return { -q.x, -q.y,-q.z, q.w };
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
    return { -q.x, -q.y,-q.z, q.w };
}

Quaternion Quaternion::QuaternionNormalize(const Quaternion& q)
{
    return q / Magnitude(q);
}

bool CEngine::Math::Intersect(const Ray& ray, const Plane& plane, float& distance)
{
    const float orgDotN = Dot(ray.origin, plane.n);
    const float dirDotN = Dot(ray.direction, plane.n);

    // Check if ray is parallel to the plane
    if (Abs(dirDotN) < 0.0001f)
    {
        if (Abs(orgDotN - plane.d) < 0.0001f)
        {
            distance = 0.0f;
            return true;
        }
        else
        {
            return false;
        }
    }

    // Compute distance
    distance = (plane.d - orgDotN) / dirDotN;
    return true;

}

bool CEngine::Math::IsContained(const Vector3& point, const AABB& aabb)
{
    auto min = aabb.Min();
    auto max = aabb.Max();
    if ((point.x < min.x) || (point.x > max.x) ||
        (point.y < min.y) || (point.y > max.y) ||
        (point.z < min.z) || (point.y > max.z))
    {
        return false;
    }
    return true;
}

//bool CEngine::Math::IsContained(const Vector3& point, const OBB& obb)
//{
//    // Compute the world-to-local matrices
//    Math::Matrix4 matTrans = Math::Matrix4::Translation(obb.center);
//    Math::Matrix4 matRot = Math::Matrix4::RotationQuaternion(obb.rot);
//    Math::Matrix4 matScale = Math::Matrix4::Scaling(obb.extend);
//    Math::Matrix4 toWorld = matScale * matRot * matTrans;
//    Math::Matrix4 toLocal = Inverse(toWorld);
//
//    // Transform the point into the OBB's local space
//    Vector3 localPoint = TransformCoord(point, toLocal);
//
//    // Test against local AABB
//    return IsContained(localPoint, AABB{ Vector3::Zero, Vector3::One });
//}
//
//bool CEngine::Math::GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal)
//{
//    // Compute the local-to-world/world-to-local matrices
//    Matrix4 matTrans = Matrix4::Translation(obb.center);
//    Matrix4 matRot = Matrix4::RotationQuaternion(obb.rot);
//    Matrix4 matWorld = matRot * matTrans;
//    Matrix4 matWorldInv = Inverse(matWorld);
//
//    // Transform the ray into the OBB's local space
//    Vector3 org = TransformCoord(ray.origin, matWorldInv);
//    Vector3 dir = TransformNormal(ray.direction, matWorldInv);
//    Ray localRay{ org, dir };
//
//    Plane planes[] =
//    {
//        { {  0.0f,  0.0f, -1.0f }, obb.extend.z },
//        { {  0.0f,  0.0f,  1.0f }, obb.extend.z },
//        { {  0.0f, -1.0f,  0.0f }, obb.extend.y },
//        { {  0.0f,  1.0f,  0.0f }, obb.extend.y },
//        { { -1.0f,  0.0f,  0.0f }, obb.extend.x },
//        { {  1.0f,  0.0f,  0.0f }, obb.extend.x }
//    };
//
//    uint32_t numIntersections = 0;
//    for (uint32_t i = 0; i < 6; ++i)
//    {
//        const float d = Dot(org, planes[i].n);
//        if (d > planes[i].d)
//        {
//            float distance = 0.0f;
//            if (Intersect(localRay, planes[i], distance) && distance >= 0.0f)
//            {
//                Vector3 pt = org + (dir * distance);
//                if (abs(pt.x) <= obb.extend.x + 0.01f &&
//                    abs(pt.y) <= obb.extend.y + 0.01f &&
//                    abs(pt.z) <= obb.extend.z + 0.01f)
//                {
//                    point = pt;
//                    normal = planes[i].n;
//                    ++numIntersections;
//                }
//            }
//        }
//    }
//
//    if (numIntersections == 0)
//    {
//        return false;
//    }
//
//    point = TransformCoord(point, matWorld);
//    normal = TransformNormal(normal, matWorld);
//    return true;
//
//}