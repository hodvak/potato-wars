#include <SFML/Audio.hpp>

class SoundPlayer
{
public:
    SoundPlayer();

    void play();
    void addSound(const std::string& path);
private:
    sf::SoundBuffer m_buffer;
    std::vector<std::string> m_sounds;
    sf::Sound m_sound;
    sf::SoundBuffer Buffer;
};