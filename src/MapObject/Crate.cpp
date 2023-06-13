#include "MapObject/Crate.h"
#include "resources_manager.h"
#include "Const.h"
#include "Physics.h"

Crate::Crate(MapVector pos, GameMap *map) :
        MovingMapObject(1, pos, map, 10)
{

}

void Crate::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    sf::Sprite sprite;
    if(onGround||isRest())
    {
        sprite.setTexture(*resources_manager::getTexture(
                "resources/images/Textures/CrateTextureNP.png"));
    }
    else
    {

        sprite.setTexture(*resources_manager::getTexture(
                "resources/images/Textures/CrateTexture.png"));
    }
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
                     sprite.getTexture()->getSize().y / 2);
    sprite.setScale(0.2, 0.2);
    sprite.setRotation(getRotation());
    target.draw(sprite, states);


}

bool Crate::collideDD1(MovingMapObject *other_object)
{


    return false;

}

std::optional<float> Crate::collisionMap()
{

    MapVector closestPoint = {-getRadius(), -getRadius()};
    float hit_angle = 0;
    int num_of_pixels = 0;

    for (int i = (int) -getRadius(); i < (int) getRadius(); ++i)
    {
        for (int j = (int) -getRadius(); j < (int) getRadius(); ++j)
        {
            if (i * i + j * j <= (int) (getRadius() * getRadius()) &&
                (i != 0 || j != 0))
            {

                sf::Vector2i pos = {(int) getPosition().x + i,
                                    (int) getPosition().y + j};
                if (pos.x < 0 ||
                    pos.y < 0 ||
                    pos.x >= (int) getMap()->getMask().getSize().x ||
                    pos.y >= (int) getMap()->getMask().getSize().y)
                {
                    continue;
                }
                if (getMap()->getMask().getPixel(pos.x, pos.y) ==
                    sf::Color::White)
                {
                    if (i * i + j * j <
                        closestPoint.x * closestPoint.x +
                        closestPoint.y * closestPoint.y)
                    {
                        closestPoint.x = (float) i;
                        closestPoint.y = (float) j;
                    }
                    hit_angle += (float) atan2(j, i);
                    num_of_pixels++;
                }
            }
        }
    }

    if (num_of_pixels == 0)
    {
        return std::nullopt;
    }

    //move to stand on the closest point
    float to_move = getRadius() - closestPoint.getMagnitude();

    setPosition(getPosition() -
                MapVector::getVectorFromAngle(closestPoint.getAngle(),
                                              to_move));
    //fix the hit angle (average hit angle)
    hit_angle /= (float) num_of_pixels;

    return hit_angle;
}

void Crate::update(const sf::Time &deltaTime)
{

    if (!isRest())
    {
        updateForces(deltaTime);
        updateVelocity(deltaTime);
        updatePosition(deltaTime);
        std::optional<float> rot = collisionMap();
        if (rot)
        {
            onGround = true;
            setRotation(*rot);
        }

    }
}

void Crate::updateVelocity(const sf::Time &deltaTime)
{
    setVelocity({0,80});
}




