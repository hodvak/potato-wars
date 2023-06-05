#include "Physics.h"
#include "MapVector.h"
#include "Const.h"

float getDiffAngle(float a1, float a2)
{
    float diff = a1 - a2;
    while (diff > Consts::PI)
    {
        diff -= 2 * Consts::PI;
    }
    while (diff < -Consts::PI)
    {
        diff += 2 * Consts::PI;
    }
    return std::abs(diff);
}


std::pair<float, float>
Physics::elasticCollision(float m1, float m2, float v1, float v2)
{
    float v1f = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
    float v2f = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);
    return {v1f, v2f};
}

std::pair<MapVector, MapVector>
Physics::elasticCollision(float m1,
                          float m2,
                          const MapVector &v1,
                          const MapVector &v2,
                          float hitAngle)
{
    auto [v1Perpendicular, v1Parallel] = v1.getSplitVector(hitAngle);
    auto [v2Perpendicular, v2Parallel] = v2.getSplitVector(hitAngle);
    
    float v1PerpendicularSpeed = v1Perpendicular.getMagnitude();
    float v2PerpendicularSpeed = v2Perpendicular.getMagnitude();

    if (getDiffAngle(v1Perpendicular.getAngle(), hitAngle) > Consts::PI / 2)
    {
        v1PerpendicularSpeed *= -1.0f;
    }
    if (getDiffAngle(v2Perpendicular.getAngle(), hitAngle) > Consts::PI / 2)
    {
        v2PerpendicularSpeed *= -1.0f;
    }
    
    auto [v1fPerpendicular, v2fPerpendicular] =
            elasticCollision(m1,
                             m2,
                             v1PerpendicularSpeed,
                             v2PerpendicularSpeed);

    auto v1f = v1Parallel +
               MapVector::getVectorFromAngle(hitAngle, v1fPerpendicular);
    auto v2f = v2Parallel +
               MapVector::getVectorFromAngle(hitAngle, v2fPerpendicular);
    return {v1f, v2f};
}

