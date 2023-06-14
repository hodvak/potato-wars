#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <optional>
#include "MapVector.h"
#include "Weapon/Creators/WeaponCreator.h"

class WeaponCreatorContainer : public sf::Drawable
{
public:
    WeaponCreatorContainer(const MapVector &size, const MapVector &position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void addWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);
    WeaponCreator * getWeaponCreator(sf::Vector2f mousePosition);
    
private:
    std::vector<std::unique_ptr<WeaponCreator>> m_weaponCreators;
    MapVector m_size;
    MapVector m_position;
    
};