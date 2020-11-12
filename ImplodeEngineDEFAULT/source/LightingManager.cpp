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

LightSprite LightingManager::CreateTexture(Light & light)
{
	//Firstly add the light and set the light sprite position
	LightSprite lightSpr;
	
	lightSpr.lightSprite.setPosition(light.GetPosition().x - light.GetIntensity() / 2, light.GetPosition().y - light.GetIntensity() / 2);

	//Create our first texture which will conduct lighting calculations
	sf::RenderTexture txtr;
	txtr.create(light.GetIntensity(),light.GetIntensity());
	txtr.clear(sf::Color::Transparent);

	sf::Texture texture;
	sf::Sprite sprite;

	//For each sprite in the sprites list, we check if it is within the boundary of the light
	for (int i = 0; i < this->m_boundaryManager.m_sprites.size(); i++)
	{
		if (this->m_boundaryManager.m_sprites[i]->getPosition().x < light.GetPosition().x + light.GetIntensity() / 2 + this->m_boundaryManager.m_sprites[i]->getLocalBounds().width
			&& this->m_boundaryManager.m_sprites[i]->getPosition().x > light.GetPosition().x - light.GetIntensity() / 2 - this->m_boundaryManager.m_sprites[i]->getLocalBounds().width
			&& this->m_boundaryManager.m_sprites[i]->getPosition().y < light.GetPosition().y + light.GetIntensity() / 2 + this->m_boundaryManager.m_sprites[i]->getLocalBounds().height
			&& this->m_boundaryManager.m_sprites[i]->getPosition().y > light.GetPosition().y - light.GetIntensity() / 2 - this->m_boundaryManager.m_sprites[i]->getLocalBounds().height)
		{
			//if it is, draw it to a texture
			sf::Sprite sp;
			sp = *this->m_boundaryManager.m_sprites[i];
			sp.setPosition(sp.getPosition().x - light.GetPosition().x + light.GetIntensity() / 2, sp.getPosition().y - light.GetPosition().y + light.GetIntensity() / 2);
			txtr.draw(sp,&this->m_occlusionShader);
		}
	}
	txtr.display();

	texture = txtr.getTexture();
	sprite.setTexture(texture);

	//Firstly we create a shadow texture and calculate distances from rays to each boundary object

	this->m_1dSdwMapShader.setUniform("resolution", sf::Glsl::Vec2(light.GetIntensity(), light.GetIntensity()));
	this->m_1dSdwMapShader.setUniform("vColor", sf::Glsl::Vec4(light.GetColor()));
	
	txtr.draw(sprite,&this->m_1dSdwMapShader);
	txtr.display();
	texture = txtr.getTexture();

	sprite.setTexture(texture);
	//Next we create our light texture and using the shadow texture, we calculate from it the distance of each light ray.
	lightSpr.txtr->create(light.GetIntensity(), light.GetIntensity());
	lightSpr.txtr->clear(sf::Color::Transparent);

	this->m_blurShader.setUniform("resolution", sf::Glsl::Vec2(light.GetIntensity(), light.GetIntensity()));
	
	lightSpr.txtr->draw(sprite, &this->m_blurShader);

	//finally we set the light texture and the light sprite.
	sprite.setTexture(lightSpr.txtr->getTexture());

	lightSpr.lightSprite = sprite;
	lightSpr.lightSprite.setPosition(light.GetPosition().x - light.GetIntensity()/2, light.GetPosition().y - light.GetIntensity() / 2);
	lightSpr.lightSprite.setColor(light.GetColor());
	lightSpr.light = &light;
	return lightSpr;
}

void LightingManager::Update(float deltaTime)
{

}


void LightingManager::ProcessEvents(sf::Event& e)
{

}

void LightingManager::UpdateLightSprite(LightSprite & ls, float intensity, sf::Vector2f position, bool activated, sf::Color color)
{
	ls.txtr->~RenderTexture();
	Light *l = new Light(intensity, position, activated, color);
	ls = this->CreateTexture(*l);
}

void LightingManager::UpdateFromSprite(std::vector<sf::Sprite*> s)
{
	for (int i = 0; i < this->m_lightSprites.size(); i++)
	{
		for (int j = 0; j < s.size(); j++)
		{
			if (s[j]->getPosition().x < m_lightSprites[i].light->GetPosition().x + m_lightSprites[i].light->GetIntensity() / 2 + s[j]->getLocalBounds().width
				&& s[j]->getPosition().x > m_lightSprites[i].light->GetPosition().x - m_lightSprites[i].light->GetIntensity() / 2 - s[j]->getLocalBounds().width
				&& s[j]->getPosition().y < m_lightSprites[i].light->GetPosition().y + m_lightSprites[i].light->GetIntensity() / 2 + s[j]->getLocalBounds().height
				&& s[j]->getPosition().y > m_lightSprites[i].light->GetPosition().y - m_lightSprites[i].light->GetIntensity() / 2 - s[j]->getLocalBounds().height)
			{
				this->UpdateLightSprite(m_lightSprites[i], m_lightSprites[i].light->GetIntensity(), m_lightSprites[i].light->GetPosition(), m_lightSprites[i].light->GetActivated(), m_lightSprites[i].light->GetColor());
			}
		}
	}
}

void LightingManager::AddBoundary(sf::Sprite &s)
{
	this->m_boundaryManager.AddSprite(&s);

	for (int i = 0; i < this->m_lightSprites.size(); i++)
	{
		if (m_lightSprites[i].light->GetPosition().x < this->m_totalLightingBound.width
			&& m_lightSprites[i].light->GetPosition().x > this->m_totalLightingBound.left
			&& m_lightSprites[i].light->GetPosition().y < this->m_totalLightingBound.height
			&& m_lightSprites[i].light->GetPosition().y > this->m_totalLightingBound.top)
		{
			break;
		}
		if (s.getPosition().x < m_lightSprites[i].light->GetPosition().x + m_lightSprites[i].light->GetIntensity() / 2 + s.getLocalBounds().width
			&& s.getPosition().x > m_lightSprites[i].light->GetPosition().x  - m_lightSprites[i].light->GetIntensity() / 2 - s.getLocalBounds().width
			&& s.getPosition().y < m_lightSprites[i].light->GetPosition().y + m_lightSprites[i].light->GetIntensity() / 2 + s.getLocalBounds().height
			&& s.getPosition().y > m_lightSprites[i].light->GetPosition().y - m_lightSprites[i].light->GetIntensity() / 2 - s.getLocalBounds().height)
		{
			this->UpdateLightSprite(m_lightSprites[i], m_lightSprites[i].light->GetIntensity(), m_lightSprites[i].light->GetPosition(), m_lightSprites[i].light->GetActivated(), m_lightSprites[i].light->GetColor());
		}
	}
}

void LightingManager::RemoveBoundary(sf::Sprite& s)
{
	for (int i = 0; i < this->m_boundaryManager.m_sprites.size(); i++)
	{
		if (this->m_boundaryManager.m_sprites[i] == &s)
			this->m_boundaryManager.m_sprites.erase(this->m_boundaryManager.m_sprites.begin() + i);
	}
}

void LightingManager::CalculateLightingBound()
{
	float left = this->m_lightSprites[0].lightSprite.getPosition().x;
	float right = this->m_lightSprites[0].lightSprite.getPosition().x + this->m_lightSprites[0].lightSprite.getLocalBounds().width;
	float top = this->m_lightSprites[0].lightSprite.getPosition().y;
	float bottom = this->m_lightSprites[0].lightSprite.getPosition().y + this->m_lightSprites[0].lightSprite.getLocalBounds().height;

	for (int i = 1; i < this->m_lightSprites.size(); i++)
	{
		if (this->m_lightSprites[i].lightSprite.getPosition().x < left)
			left = this->m_lightSprites[i].lightSprite.getPosition().x;

		if (this->m_lightSprites[i].lightSprite.getPosition().x + this->m_lightSprites[i].lightSprite.getLocalBounds().width > right)
			right = this->m_lightSprites[i].lightSprite.getPosition().x;

		if (this->m_lightSprites[i].lightSprite.getPosition().y < top)
			top = this->m_lightSprites[i].lightSprite.getPosition().y;

		if (this->m_lightSprites[i].lightSprite.getPosition().y + this->m_lightSprites[0].lightSprite.getLocalBounds().height > bottom)
			bottom = this->m_lightSprites[i].lightSprite.getPosition().y + this->m_lightSprites[i].lightSprite.getLocalBounds().height;
	}
	this->m_totalLightingBound.height = bottom;
	this->m_totalLightingBound.top = top;
	this->m_totalLightingBound.width = right;
	this->m_totalLightingBound.left = left;

	std::cout << left << std::endl;
	std::cout << right << std::endl;
	std::cout << top << std::endl;
	std::cout << bottom << std::endl;

}
