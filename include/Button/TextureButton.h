#include "Button.h"

class TextureButton : public Button
{
public:
    TextureButton(const sf::Vector2f &pos,
                  const sf::Vector2f &size,
                  const std::function<void()> &function,
                  const sf::Texture *texture);

    void onHover(const sf::Vector2f &pos) override;



    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    const sf::Texture *m_texture;

    std::function<void()> m_function;

    sf::Sprite m_sprite;

};