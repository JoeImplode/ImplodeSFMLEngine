#pragma once
#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"
#include "PoolExample.h"
#include "Camera.h"
#include "Particle.h"
#include "ParticleEmitter.h"
#include "Light.h"
#include "SoundManager.h"
#include "BoundaryManager.h"
#include "LightingManager.h"

class MenuState : public GameState
{
public:
	MenuState(GameContext* context);
	void Update(float deltaTime) override;
	void Draw() override;
	void ProcessEvents(sf::Event& e) override;
	void SetBools();
	void Initialise() override;
	~MenuState();
private:
	PoolExample* pool;
	bool m_myBool = false;
	std::string m_myString;

	sf::Shader m_shader;
	sf::RenderTexture t;
	sf::RenderTexture gameWorld;

	sf::Sprite gameWorldSprite;
	sf::Sprite s;
	sf::Sprite banner;
	sf::Sprite crate;
	sf::Sprite fountain;
	sf::Sprite bricks;
	sf::Sprite crate2;
	sf::Sprite crate3;
	sf::Sprite crate4;
	sf::Sprite crate5;
	sf::Sprite crate6;
	sf::Sprite backGround;

	AssetPool* p;

	sf::Text txt;

	Camera * m_cam;
	Camera* m_smallCam;

	std::vector<Camera*> m_cams;
	std::vector<sf::Sprite> m_camSprites;

	Particle m_particle;
	ParticleEmitter* m_emitter;

	BoundaryManager m_boundaryManager;

	LightingManager* m_lightingManager;
	Light m_light;
	Light m_light2;

	SoundManager *m_soundManager;
	sf::SoundBuffer m_soundBuffer;
	
	Animation m_animationTest;
};