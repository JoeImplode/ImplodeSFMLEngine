#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <SFML/System/Utf.hpp>
#include <queue>
#include <stack>
#include <cmath>

struct LightSprite
{
	sf::Sprite lightSprite;
	sf::RenderTexture* txtr;

	LightSprite()
	{
		lightSprite = sf::Sprite();
		txtr = new sf::RenderTexture();
	}
	~LightSprite()
	{
		txtr = nullptr;
	}
};