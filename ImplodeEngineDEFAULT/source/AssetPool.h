#pragma once

class AssetPool
{
public:
	AssetPool();
	~AssetPool();

	void LoadTexture(std::string path, std::string name); //path = path to file, name = name of texture
	sf::Texture& GetTexture(std::string name);

	void LoadFont(std::string path, std::string name);
	sf::Font& GetFont(std::string name);
	bool operator ==(const AssetPool& obj2)const;
private:
	std::map<std::string, sf::Texture> m_textures;
	std::map<std::string, sf::Font> m_fonts;
	sf::Texture m_missingTexture;
	sf::Font m_missingFont;
protected:

};