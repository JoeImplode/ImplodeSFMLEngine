#pragma once
#include <SFML/Audio.hpp>
class SoundManager
{
public:
	SoundManager();
	sf::SoundBuffer& GetSoundBuffer(std::string soundBufferKey);
	sf::Sound& GetSound(std::string soundName);
	sf::Music& GetMusic(std::string musicKey);
	bool LoadSoundBuffer(std::string bufferName, std::string filePath);
	void CreateSound(std::string soundName, sf::Sound snd);
	void CreateMusic(std::string musicName, std::string filePath);
	bool PlaySound(std::string soundName, std::string soundBuffer);
	bool PlayMusic(std::string musicName);
	~SoundManager();
private:
	std::map<std::string, sf::SoundBuffer> m_soundBuffers;
	std::map<std::string, sf::Music *> m_music;
	std::map<std::string, sf::Sound>m_sounds;
protected:
};