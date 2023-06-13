#pragma once
#include "Weapon/Creators/WeaponCreator.h"
#include <vector>
#include <memory>
#include <optional>
class WeaponCreatorContainer : public sf::Drawable
{
public:
    WeaponCreatorContainer(const MapVector &size, const MapVector &position);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void AddWeaponCreator(std::unique_ptr<WeaponCreator> &&weaponCreator);
    WeaponCreator * GetWeaponCreator(sf::Vector2f mousePosition);
    
private:
    std::vector<std::unique_ptr<WeaponCreator>> m_weaponCreators;
    MapVector m_size;
    MapVector m_position;
    
};