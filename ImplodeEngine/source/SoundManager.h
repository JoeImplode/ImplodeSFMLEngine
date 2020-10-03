#pragma once

class SoundManager
{
public:
	SoundManager();
private:
	std::vector<sf::Sound> m_sounds;
	std::vector<sf::Music> m_music;
protected:
};