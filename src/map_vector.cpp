#include "map_vector.h"
float PI = acos(-1.0f);
MapVector::MapVector(float x, float y) : sf::Vector2f(x, y)
{

}

MapVector::MapVector(const sf::Vector2f &vector) : sf::Vector2f(vector)
{

}

float MapVector::get_magnitude() const
{
    return sqrt(x*x+y*y);
}
float MapVector::get_magnitude_squared() const
{
    return x*x+y*y;
}

float MapVector::get_angle() const
{
    return atan2(y,x);
}

sf::Vector2<MapVector> MapVector::get_split_vector(float angle) const
{
    float thisAngle = get_angle();
    MapVector angels =  MapVector(angle - thisAngle,-thisAngle + angle+PI/2 );
    MapVector magnitudes =
            get_magnitude() * MapVector(cos(angels.x), cos(angels.y));
    return sf::Vector2<MapVector>(get_vector_from_angle(angle, magnitudes.x),
                                  get_vector_from_angle(PI / 2 + angle,
                                                        magnitudes.y));
}

MapVector MapVector::get_vector_from_angle(float angle, float magnitude)
{
    return MapVector(cos(angle) * magnitude, sin(angle) * magnitude);
}

MapVector MapVector::get_rotated_vector(float angle) const
{
    return get_vector_from_angle(get_angle() + angle, get_magnitude());
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

