#include "MapVector.h"
#include <numbers>

MapVector::MapVector(float x, float y) : sf::Vector2f(x, y)
{

}

MapVector::MapVector(const sf::Vector2f &vector) : sf::Vector2f(vector)
{

}

float MapVector::getMagnitude() const
{
    return sqrt(x * x + y * y);
}

float MapVector::getMagnitudeSquared() const
{
    return x * x + y * y;
}

float MapVector::getAngle() const
{
    return atan2(y, x);
}

sf::Vector2<MapVector> MapVector::getSplitVector(float angle) const
{
    float thisAngle = getAngle();
    MapVector angels = MapVector(angle - thisAngle,
                                 -thisAngle + angle + std::numbers::pi_v<float> / 2);
    MapVector magnitudes =
            getMagnitude() * MapVector(cos(angels.x), cos(angels.y));
    return sf::Vector2<MapVector>(getVectorFromAngle(angle, magnitudes.x),
                                  getVectorFromAngle(std::numbers::pi_v<float> / 2 + angle,
                                                     magnitudes.y));
}

MapVector MapVector::getVectorFromAngle(float angle, float magnitude)
{
    return MapVector(cos(angle) * magnitude, sin(angle) * magnitude);
}

MapVector MapVector::getRotatedVector(float angle) const
{
    return getVectorFromAngle(getAngle() + angle, getMagnitude());
}

void MapVector::normalize(float magnitude)
{
    float currentMagnitude = getMagnitude();
    if (currentMagnitude == 0)
    {
        return;
    }
    x *= magnitude / currentMagnitude;
    y *= magnitude / currentMagnitude;

}

MapVector MapVector::getNormalized(float magnitude) const
{
    MapVector result(*this);
    result.normalize(magnitude);
    return result;
}

MapVector operator*(const MapVector &vector1, const MapVector &vector2)
{
    MapVector result(vector1);
    result *= vector2;
    return result;
}

MapVector &operator*=(MapVector &vector1, const MapVector &vector2)
{
    vector1.x *= vector2.x;
    vector1.y *= vector2.y;
    return vector1;
}

MapVector operator*(const MapVector &vector, float scalar)
{
    MapVector result(vector);
    result *= scalar;
    return result;
}

MapVector operator*(float scalar, const MapVector &vector)
{
    return vector * scalar;
}

MapVector operator/(const MapVector &vector, float scalar)
{
    MapVector result(vector);
    result /= scalar;
    return result;
}

MapVector operator+(float scalar, const MapVector &vector)
{
    return vector + scalar;
}

MapVector operator+(const MapVector &vector, float scalar)
{
    MapVector result(vector);
    result += scalar;
    return result;
}

MapVector &operator+=(MapVector &vector, float scalar)
{
    vector.x += scalar;
    vector.y += scalar;
    return vector;
}

std::ostream &operator<<(std::ostream &file, const MapVector &vector)
{
    file << "(" << vector.x << "," << vector.y << ")";
    return file;
}

MapVector operator+(const MapVector &vector1, const MapVector &vector2)
{
    MapVector result(vector1);
    result += vector2;
    return result;
}

MapVector &operator-=(MapVector &vector1, const MapVector &vector2)
{
    vector1.x -= vector2.x;
    vector1.y -= vector2.y;
    return vector1;
}

MapVector operator-(const MapVector &vector1, const MapVector &vector2)
{
    MapVector result(vector1);
    result -= vector2;
    return result;
}

MapVector operator-(const MapVector &vector)
{
    return MapVector(-vector.x, -vector.y);
}

