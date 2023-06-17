#include "Weapon/Jump.h"

Jump::Jump(Character &character,
           const std::function<void(std::unique_ptr<MovingMapObject> &&)>
           &addMapObjectFunc) :
        ThrowWeapon(character,
                    std::make_unique<Character>(character.getPosition(),
                                                character.getMap(),
                                                character.getBombHandler(),
                                                character.getColor()),
                    addMapObjectFunc), m_character(character)
{

}

void Jump::handleMousePressed(const MapVector &mousePosition)
{
    MapVector velocity = m_character.getPosition() - mousePosition;
    if (velocity.getMagnitude() > MAX_MOUSE_DISTANCE)
    {
        velocity.normalize(MAX_MOUSE_DISTANCE);
    }
    setDirectionTexture(velocity);
    fixPosition();
    m_character.setVelocity(velocity * 3);
    m_character.unrest();

    die();
}
