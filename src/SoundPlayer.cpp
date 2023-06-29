#include "SoundPlayer.h"
#include "resources_manager.h"

SoundPlayer::SoundPlayer(bool mute, float volume) :
        m_buffer(),
        m_sounds(),
        m_sound(),
        m_volume(volume),
        m_mute(mute)
{

}

void SoundPlayer::play()
{

    if (!m_mute)
    {
        for (auto &sound: m_sounds)
        {

            m_sound.setBuffer(resources_manager::get<sf::SoundBuffer>(sound));
            m_sound.setVolume(m_volume);
            m_sound.play();
        }
    }
    m_sounds.clear();

}

void SoundPlayer::addSound(const std::string &path)
{
    m_sounds.push_back(path);
}

void SoundPlayer::setVolume(float volume)
{
    m_volume = volume;
    if (m_volume < 0)
    {
        m_volume = 0;
    }
    if (m_volume > 100)
    {
        m_volume = 100;
    }
}

void SoundPlayer::setMute(bool mute)
{
    this->m_mute = mute;
}

void SoundPlayer::changeVolume(float delta)
{
    setVolume(m_volume + delta);
    m_volume += delta;

}
