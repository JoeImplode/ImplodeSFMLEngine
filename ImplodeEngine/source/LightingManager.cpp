#include "pch.h"
#include "LightingManager.h"
#include "Light.h"
#include "BoundaryManager.h"

LightingManager::LightingManager()
{
	this->m_lights = std::vector<Light>{};
	this->m_boundaryManager = BoundaryManager();
	this->m_occlusionShader.loadFromFile("resources/shaders/occlusionMap.vert", "resources/shaders/occlusionMap.frag");
	this->m_1dSdwMapShader.loadFromFile("resources/shaders/1dSdwMap.vert", "resources/shaders/1dSdwMap.frag");
	this->m_blurShader.loadFromFile("resources/shaders/blurLight.vert", "resources/shaders/blurLight.frag");
	this->m_lightSprites = std::vector<LightSprite>{};
}

LightingManager::~LightingManager()
{
}

void LightingManager::CreateTexture(Light light)
{
	//Firstly add the light and set the light sprite position
	this->m_lightSprites.push_back(LightSprite());
	this->m_lightSprites[this->m_lightSprites.size() - 1].lightSprite.setPosition(light.GetPosition().x - light.GetIntensity() / 2, light.GetPosition().y - light.GetIntensity() / 2);

	//Create our first texture which will conduct lighting calculations
	sf::RenderTexture txtr;
	txtr.create(light.GetIntensity(),light.GetIntensity());
	txtr.clear(sf::Color::Transparent);

	sf::Sprite sprite;
	//For each sprite in the sprites list, we check if it is within the boundary of the light
	for (int i = 0; i < this->m_boundaryManager.m_sprites.size(); i++)
	{
		if (this->m_boundaryManager.m_sprites[i]->getPosition().x < light.GetPosition().x + light.GetIntensity() / 2 + this->m_boundaryManager.m_sprites[i]->getLocalBounds().width
			&& this->m_boundaryManager.m_sprites[i]->getPosition().x > light.GetPosition().x - this->m_boundaryManager.m_sprites[i]->getLocalBounds().width - light.GetIntensity() / 2
			&& this->m_boundaryManager.m_sprites[i]->getPosition().y < light.GetPosition().y + this->m_boundaryManager.m_sprites[i]->getLocalBounds().height + light.GetIntensity() / 2
			&& this->m_boundaryManager.m_sprites[i]->getPosition().y > light.GetPosition().y - this->m_boundaryManager.m_sprites[i]->getLocalBounds().height - light.GetIntensity() / 2)
		{
			//if it is, draw it to a texture
			sf::Sprite sp;
			sp = *this->m_boundaryManager.m_sprites[i];
			sp.setPosition(sp.getPosition().x - light.GetPosition().x + light.GetIntensity() / 2, sp.getPosition().y - light.GetPosition().y + light.GetIntensity() / 2);
			txtr.draw(sp,&this->m_occlusionShader);
		}
	}
	txtr.display();

	sprite.setTexture(txtr.getTexture());

	//Firstly we create a shadow texture and calculate distances from rays to each boundary object
	sf::RenderTexture sdwTxtr;
	sdwTxtr.create(light.GetIntensity(), light.GetIntensity());
	sdwTxtr.clear(sf::Color::Transparent);

	sf::Sprite lSprite;
	this->m_1dSdwMapShader.setUniform("resolution", sf::Glsl::Vec2(light.GetIntensity(), light.GetIntensity()));

	this->m_lightSprites[this->m_lightSprites.size() - 1].lightSprite.setPosition(0.0f, 0.0f);

	sdwTxtr.draw(sprite,&this->m_1dSdwMapShader);
	sdwTxtr.display();

	lSprite.setTexture(sdwTxtr.getTexture());
	//Next we create our light texture and using the shadow texture, we calculate from it the distance of each light ray.
	this->m_lightSprites[this->m_lightSprites.size() - 1].txtr->create(light.GetIntensity(), light.GetIntensity());
	this->m_lightSprites[this->m_lightSprites.size() - 1].txtr->clear(sf::Color::Transparent);

	this->m_blurShader.setUniform("resolution", sf::Glsl::Vec2(light.GetIntensity(), light.GetIntensity()));

	this->m_lightSprites[this->m_lightSprites.size() - 1].txtr->draw(lSprite, &this->m_blurShader);

	//finally we set the light texture and the light sprite.
	lSprite.setTexture(this->m_lightSprites[this->m_lightSprites.size() - 1].txtr->getTexture());

	this->m_lightSprites[this->m_lightSprites.size() - 1].lightSprite = lSprite;
	this->m_lightSprites[this->m_lightSprites.size() - 1].lightSprite.setPosition(light.GetPosition().x - light.GetIntensity()/2, light.GetPosition().y - light.GetIntensity() / 2);
}

void LightingManager::Update(float deltaTime)
{
}


void LightingManager::ProcessEvents(sf::Event& e)
{
}
