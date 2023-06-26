#pragma once
#include <SFML/Audio.hpp>

class SoundPlayer
{
public:
    SoundPlayer(bool mute, float volume);

    void play();
    void addSound(const std::string& path);
    void setVolume(float volume);
    void setMute(bool mute);
private:
    sf::SoundBuffer m_buffer;
    std::vector<std::string> m_sounds;
    sf::Sound m_sound;

    float m_volume = 100;
    bool m_mute = false;

};