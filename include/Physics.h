#pragma once

#include "MapObject/MovingMapObject.h"
#include "GameMap.h"

namespace Physics
{
    const float GRAVITY = 130.0f;
    const float FRICTION = 0.2f;
    
    /**
     * regular elastic collision between two objects in 1D
     * @param m1 mass of first object
     * @param m2 mass of second object
     * @param v1 velocity of first object
     * @param v2 velocity of second object
     * @return pair of velocities after collision ([v1, v2])
     */
    std::pair<float, float> elasticCollision(float m1, 
                                             float m2, 
                                             float v1, 
                                             float v2);
    
    /**
     * elastic collision between two objects in 2D
     * @param m1 mass of first object
     * @param m2 mass of second object
     * @param v1 velocity of first object
     * @param v2 velocity of second object
     * @param hitAngle angle of collision (from first object to second)
     * @return pair of velocities after collision ([v1, v2])
     */
    std::pair<MapVector, MapVector> elasticCollision(float m1,
                                                     float m2,
                                                     const MapVector &v1,
                                                     const MapVector &v2,
                                                     float hitAngle);

}