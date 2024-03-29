#include <numbers>
#include "MapObject/Crates/Crate.h"
#include "resources_manager.h"

#include "Physics.h"



static const int RADIUS = 10;
static const int MASS = 100;
Crate::Crate(const MapVector &pos,
             const sf::Texture &texture,
             const sf::IntRect &overShape,
             GameHelperData &gameHelperData):

        MovingMapObject(pos, RADIUS, MASS, gameHelperData),
        m_overTexture(texture),
        m_overShape(overShape),
        m_onGround(false)
{

}

void Crate::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform.translate(getPosition());
    sf::Sprite sprite;
    sf::Sprite overTexture;

    overTexture.setTexture(m_overTexture);
    overTexture.setScale(
            getRadius() * 2 / m_overShape.width,
            getRadius() * 2 / m_overShape.height);
    overTexture.setTextureRect(m_overShape);
    overTexture.setOrigin(m_overShape.width / 2,
                          m_overShape.height / 2);
    overTexture.setRotation(getRotation());
    const sf::Texture *texture = &resources_manager::get<sf::Texture>(
            resources_manager::IMG_CRATENP_PATH);
    sf::Vector2f scale = {
            getRadius() * 2 / texture->getSize().x,
            getRadius() * 2 / texture->getSize().y
    };


    if (m_onGround || isRest())
    {
        sprite.setTexture(resources_manager::get<sf::Texture>(resources_manager::IMG_CRATENP_PATH));
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
                         sprite.getTexture()->getSize().y / 2);


    }
    else
    {

        sprite.setTexture(resources_manager::get<sf::Texture>(
                resources_manager::IMG_CRATE_PATH));
        sprite.setOrigin(sprite.getTexture()->getSize().x / 2,
                         sprite.getTexture()->getSize().y - getRadius());
        overTexture.setPosition(0, -getRadius());

    }

    sprite.setScale(scale);

    sprite.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);
    overTexture.setRotation(getRotation() * 180 / std::numbers::pi_v<float>);


    target.draw(sprite, states);
    target.draw(overTexture, states);


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
            getGameHelperData().addSound(resources_manager::SOUND_CRATEIMPACT_PATH);
            setVelocity({0, 0});
            stop();
            m_onGround = true;

            setRotation(*rot - std::numbers::pi_v<float> / 2);
        }

    }
}

void Crate::updateVelocity(const sf::Time &deltaTime)
{
    setVelocity({0, 80});
}


bool Crate::collisionObject() const
{
    return false;
}
