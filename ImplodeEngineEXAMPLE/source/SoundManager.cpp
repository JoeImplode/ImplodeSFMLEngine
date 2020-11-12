#include "pch.h"
#include "SoundManager.h"

SoundManager::SoundManager()
{
	this->m_music = std::map <std::string, sf::Music *>();
	this->m_music.insert(std::pair<std::string, sf::Music*>("error", new sf::Music()));
	this->m_music["error"]->openFromFile("resources/sounds/error.wav");

	this->m_soundBuffers = std::map <std::string, sf::SoundBuffer>();
	this->m_soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("error", sf::SoundBuffer()));
	this->m_soundBuffers["error"].loadFromFile("resources/sounds/error.wav");

	this->m_sounds = std::map <std::string, sf::Sound>();
	this->m_sounds.insert(std::pair<std::string, sf::Sound>("error", sf::Sound()));
	this->m_sounds["error"].setBuffer(this->m_soundBuffers["error"]);
}

sf::SoundBuffer& SoundManager::GetSoundBuffer(std::string soundBufferKey)
{
	if ((this->m_soundBuffers.find(soundBufferKey) == this->m_soundBuffers.end())) //not found
	{
		std::cout << "Error! Sound buffer key could not be found!" << std::endl;
		return this->m_soundBuffers["error"];
	}
	else
		return this->m_soundBuffers[soundBufferKey];
}

sf::Sound& SoundManager::GetSound(std::string soundName)
{
	if ((this->m_sounds.find(soundName) == this->m_sounds.end())) //not found
	{
		std::cout << "Error! Sound key could not be found!" << std::endl;
		return this->m_sounds["error"];
	}
	else
		return this->m_sounds[soundName];
}

sf::Music& SoundManager::GetMusic(std::string musicKey)
{
	if ((this->m_music.find(musicKey) == this->m_music.end())) //not found
	{
		std::cout << "Error! Sound key could not be found!" << std::endl;
		return *this->m_music["error"];
	}
	else
		return *this->m_music[musicKey];
}

bool SoundManager::LoadSoundBuffer(std::string soundName, std::string filePath)
{
	sf::SoundBuffer sBuffer;
	if (!sBuffer.loadFromFile(filePath))
	{
		std::cout << "Couldn't find/load the file specified!" << std::endl;
		return false;
	}
	else
	{
		//check if the key was already present
		if (!(this->m_soundBuffers.find(soundName) == this->m_soundBuffers.end())) //not found
		{
			std::cout << "Error! Sound buffer key already exists!" << std::endl;
			return false;
		}
		else
			this->m_soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>(soundName, sBuffer));
		return true;
	}
	return true;
}

void SoundManager::CreateSound(std::string soundName, sf::Sound snd)
{
	//check if the key was already present
	if (!(this->m_sounds.find(soundName) == this->m_sounds.end()))
	{
		std::cout << "Error! Sound key already exists!" << std::endl;
		return;
	}
	else
		this->m_sounds.insert(std::pair<std::string, sf::Sound>(soundName, snd));
}

void SoundManager::CreateMusic(std::string musicName, std::string filePath)
{
	//check if the key was already present
	if (!(this->m_music.find(musicName) == this->m_music.end()))
	{
		std::cout << "Error! Sound key already exists!" << std::endl;
		return;
	}
	else
		this->m_music.insert(std::pair<std::string, sf::Music*>(musicName, new sf::Music()));
	
	if (!this->m_music[musicName]->openFromFile(filePath))
	{
		std::cout << "Couldn't find/load the file specified!" << std::endl;
		return;
	}

}

bool SoundManager::PlaySound(std::string soundKey, std::string soundBufferKey)
{
	//check if the key was already present
	if ((this->m_soundBuffers.find(soundBufferKey) == this->m_soundBuffers.end())) //not found
	{
		std::cout << "Error! Sound buffer key could not be found!" << std::endl;
		return false;
	}
	if ((this->m_sounds.find(soundKey) == this->m_sounds.end()))
	{
		std::cout << "Error, sound key could not be found!" << std::endl;
		return false;
	}
	else
	{
		this->m_sounds[soundKey].setBuffer(this->m_soundBuffers[soundBufferKey]);
		this->m_sounds[soundKey].play();
		return true;
	}
	return true;
}

bool SoundManager::PlayMusic(std::string musicName)
{
	if ((this->m_music.find(musicName) == this->m_music.end())) //not found
	{
		std::cout << "Error! music key could not be found!" << std::endl;
		return false;
	}
	this->m_music[musicName]->play();
	return false;
}

SoundManager::~SoundManager()
{
	for (std::pair<std::string, sf::Sound> element : this->m_sounds)
	{
		element.second.~Sound();
		this->m_sounds.erase(element.first);
	}
	this->m_sounds.empty();

	for (std::pair<std::string, sf::SoundBuffer> element : this->m_soundBuffers)
	{
		element.second.~SoundBuffer();
		this->m_soundBuffers.erase(element.first);
	}

	for (std::pair<std::string, sf::Music*> element : this->m_music)
	{
		element.second->~Music();
		this->m_music.erase(element.first);
	}
}

