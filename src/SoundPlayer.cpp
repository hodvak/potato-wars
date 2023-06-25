#include "SoundPlayer.h"


SoundPlayer::SoundPlayer():
    m_buffer(),
    m_sounds(),
    m_sound(),
    Buffer()
{

}

void SoundPlayer::play()
{

    for (auto &sound : m_sounds)
    {
        m_buffer.loadFromFile(sound);
        m_sound.setBuffer(m_buffer);
        m_sound.play();
    }

    m_sounds.clear();

}

void SoundPlayer::addSound(const std::string& path)
{
    m_sounds.push_back(path);
}
