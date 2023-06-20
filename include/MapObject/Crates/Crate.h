#pragma once

#include "MapObject/MovingMapObject.h"
#include "Weapon/Creators/WeaponCreator.h"

class Crate : public MovingMapObject
{
public:
    Crate(const MapVector &pos,
          const sf::Texture *texture,
          const sf::IntRect &overShape,
          const GameMap &map,
          BombHandler &bombHandler);
    ~Crate() override = default;
    void update(const sf::Time &deltaTime) override;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void updateVelocity(const sf::Time &deltaTime) override;

    [[nodiscard]] bool collisionObject() const override;
private:
    bool m_onGround;
    const sf::Texture *m_overTexture;
    sf::IntRect m_overShape;

};
