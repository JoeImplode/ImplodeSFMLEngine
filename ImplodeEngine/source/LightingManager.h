#pragma once
#include "BoundaryManager.h"
#include "Light.h"

class LightingManager
{
public:
	LightingManager();
	~LightingManager();
	LightSprite CreateTexture(Light & light);
	void Update(float deltaTime);
	void ProcessEvents(sf::Event& e);
	void UpdateLightSprite(LightSprite &ls, float intensity, sf::Vector2f position, bool activated, sf::Color color);
	void UpdateFromSprite(std::vector<sf::Sprite*> s);
	void AddBoundary(sf::Sprite& s);
	void RemoveBoundary(sf::Sprite& s);
	std::vector<Light> m_lights;
	BoundaryManager m_boundaryManager;
	std::vector<sf::RenderTexture> m_lightTextures;
	std::vector<LightSprite> m_lightSprites;
private:
	sf::Shader m_occlusionShader;
	sf::Shader m_1dSdwMapShader; //1 dimension ShaDoW map texture
	sf::Shader m_blurShader;
protected:
};