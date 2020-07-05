#include "pch.h"
#include "AssetPool.h"

AssetPool::AssetPool()
{
	this->m_fonts = {}; //initialise the fonts and textures
	this->m_textures = {};
	this->m_missingTexture.loadFromFile("resources/textures/error/missing.png");
	this->m_missingFont.loadFromFile("resources/fonts/Error/comicSans.ttf");
}

AssetPool::~AssetPool()
{
	this->m_fonts.clear(); //clear the vectors to free up memory
	this->m_textures.clear();
}

void AssetPool::LoadTexture(std::string path, std::string name)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		std::cout << "Error! Texture was not found for : " << name << std::endl; //the texture was not found for the name we provided
		return;
	}
	//check if the key was already present
	if (!(this->m_textures.find(name) == this->m_textures.end())) //not found
	{
		std::cout << "Error! Texture name already exists!" << std::endl;
		return;
	}
	this->m_textures.insert(std::pair<std::string, sf::Texture>(name, texture));
}

sf::Texture& AssetPool::GetTexture(std::string name)
{
	//Here we return the missing texture if we cant find the texture that we want, we output the error message

	if (m_textures.find(name) == this->m_textures.end())
	{
		std::cout << "Error! Either the name provided for the texture was incorrect or the texture didn't initally load correctly" << std::endl;
		return m_missingTexture;
	}
	else
		return m_textures[name];
}

void AssetPool::LoadFont(std::string path, std::string name)
{
	//Just the same as loading textures but instead fonts
	sf::Font font;
	if (!font.loadFromFile(path))
	{
		std::cout << "Error! Font was not found for : " << name << std::endl; //the texture was not found for the name we provided
		return;
	}
	//check if the key was already present
	if (!(this->m_fonts.find(name) == this->m_fonts.end())) //not found
	{
		std::cout << "Error! Texture name already exists!" << std::endl;
		return;
	}
	this->m_fonts.insert(std::pair<std::string, sf::Font>(name, font));
}

sf::Font& AssetPool::GetFont(std::string name)
{
	//Here we're trying to get the font and if we can't find it, then we just return the missing font... of course comic sans because who tf wants that shite
	if (m_fonts.find(name) == this->m_fonts.end())
	{
		std::cout << "Error! Either the name provided for the font was incorrect or the font didn't initally load correctly" << std::endl;
		return m_missingFont;
	}
	else
		return m_fonts[name];
}

bool AssetPool::operator==(const AssetPool& obj2) const
{
	if (this == &obj2)
		return true;
	else
		return false;
}
