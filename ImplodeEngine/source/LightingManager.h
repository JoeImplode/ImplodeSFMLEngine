#pragma once
#include "BoundaryManager.h"
#include "Light.h"

class LightingManager
{
public:
	LightingManager();
	~LightingManager();
	void CreateTexture(Light light);
	void Update(float deltaTime);
	void ProcessEvents(sf::Event& e);
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