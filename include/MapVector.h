#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class MapVector : public sf::Vector2f
{
public:
    /**
     * @brief Construct a new Map Vector object
     * @param x
     * @param y
     */
    MapVector(float x, float y);

    /**
     * @brief Construct a new Map Vector object
     *
     * @param vector
     */
    MapVector(const sf::Vector2f &vector);


    /**
     * @brief get the norma of the vector
     *
     * @param vector
     */
    float getMagnitude() const;

    float getAngle() const;

static MapVector getVectorFromAngle(float angle , float magnitude = 1);

    sf::Vector2<MapVector> getSplitVector(float angle) const;

    MapVector getRotatedVector(float angle) const;
    
    float getMagnitudeSquared() const;
};

MapVector operator*(const MapVector &vector1, const MapVector &vector2);

MapVector &operator*=( MapVector &vector1, const MapVector &vector2);

MapVector operator*(const MapVector &vector, float scalar);

MapVector operator*(float scalar, const MapVector &vector);

MapVector operator/(const MapVector &vector, float scalar);

MapVector &operator+=( MapVector &vector, float scalar);

MapVector operator+(float scalar, const MapVector &vector);

MapVector operator+(const MapVector &vector, float scalar);

MapVector operator+(const MapVector &vector1, const MapVector &vector2);
//
MapVector &operator-=(MapVector &vector1, const MapVector &vector2);

MapVector operator-(const MapVector &vector1, const MapVector &vector2);

MapVector operator-(const MapVector &vector);

std::ostream &operator<<(std::ostream &file, const MapVector &vector);
