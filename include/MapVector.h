#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * a sf::Vector2f with some extra functions.
 */
class MapVector : public sf::Vector2f
{
public:
    /**
     * @brief Construct a new MapVector object form 2 floats
     * @param x the x value
     * @param y the y value
     */
    MapVector(float x, float y);

    /**
     * Construct a new MapVector object from a sf::Vector2f
     * (can also be used as a copy constructor)
     * @param vector the vector to copy
     */
    MapVector(const sf::Vector2f &vector);

    /**
     * Construct a new MapVector object from a angle and a magnitude
     * not used as constructor because it can be confusing
     * @param angle the angle of the vector
     * @param magnitude the magnitude of the vector
     * @return new MapVector object
     */
    static MapVector getVectorFromAngle(float angle, float magnitude = 1);

    /**
     * get the magnitude of the vector (the length of the vector)
     * @return the magnitude of the vector
     */
    [[nodiscard]] float getMagnitude() const;

    /**
     * get the angle of the vector (from the with x axis) in radians
     * the angle is in the range (-PI, PI]
     * @return the angle of the vector
     */
    [[nodiscard]] float getAngle() const;

    /**
     * split the vector to 2 vectors that are perpendicular to each other
     * by the given angle, the sum of them is the original vector
     * 
     * first vector is the vector with the given angle.
     * second vector is the vector with the given angle + PI/2.
     * 
     * @param angle the angle to split the vector by
     * @return the 2 vectors
     */
    [[nodiscard]] sf::Vector2<MapVector> getSplitVector(float angle) const;

    /**
     * rotate the vector by the given angle
     * @param angle the angle to rotate the vector by
     * @return the rotated vector
     */
    [[nodiscard]] MapVector getRotatedVector(float angle) const;

    /**
     * get the magnitude of the vector squared (the length of the vector squared)
     * good for comparing magnitudes (more efficient than getMagnitude())
     * @return the magnitude of the vector squared
     */
    [[nodiscard]] float getMagnitudeSquared() const;
    
    /**
     * change the magnitude of the vector to the given magnitude (keep the angle)
     * @param magnitude the new magnitude of the vector
     */
    void normalize(float magnitude = 1);

    MapVector getNormalized(float magnitude = 1) const;
};

/** all math operators for MapVector doing the operation on both x and y
 *  and returning a new MapVector with the result
 */
//=============================================================================
[[nodiscard]] MapVector operator*(const MapVector &vector1,
                                  const MapVector &vector2);

MapVector &operator*=(MapVector &vector1, const MapVector &vector2);

[[nodiscard]] MapVector operator*(const MapVector &vector, float scalar);

[[nodiscard]] MapVector operator*(float scalar, const MapVector &vector);

[[nodiscard]] MapVector operator/(const MapVector &vector, float scalar);

MapVector &operator+=(MapVector &vector, float scalar);

[[nodiscard]] MapVector operator+(float scalar, const MapVector &vector);

[[nodiscard]] MapVector operator+(const MapVector &vector, float scalar);

[[nodiscard]] MapVector operator+(const MapVector &vector1,
                                  const MapVector &vector2);

MapVector &operator-=(MapVector &vector1, const MapVector &vector2);

[[nodiscard]] MapVector operator-(const MapVector &vector1,
                                  const MapVector &vector2);

[[nodiscard]] MapVector operator-(const MapVector &vector);
//=============================================================================

/**
 * print the vector to the given ostream
 * @param file the ostream to print to
 * @param vector the vector to print
 * @return the ostream after printing
 */
std::ostream &operator<<(std::ostream &file, const MapVector &vector);
