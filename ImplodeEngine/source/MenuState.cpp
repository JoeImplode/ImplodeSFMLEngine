#include "pch.h"
#include "GameState.h"
#include "MenuState.h"
#include "Animation.h"
#include "AssetPool.h"
#include "ImplodeEngine.h"
#include "LightingManager.h"

MenuState::MenuState(GameContext* context) : GameState(context)
{
	
}

void MenuState::Initialise()
{
	this->m_cam = new Camera(sf::Vector2f(1280.0f, 720.0f), sf::Vector2f(640.0f, 360.0f), sf::Vector2f(0.0f, 0.0f));
	this->m_smallCam = new Camera(sf::Vector2f(300.0f, 300.0f), sf::Vector2f(935.0f, 339.0f), sf::Vector2f(400.0f, 400.0f));
	this->m_cams = std::vector<Camera*>();
	this->m_soundManager = new SoundManager();
	this->m_lightingManager =  new LightingManager();
	this->m_boundaryManager = BoundaryManager();

	sf::Sound sound;
	sound.setVolume(30);
	this->m_soundManager->CreateSound("Error", sound);
	this->m_soundManager->CreateMusic("Error", "resources/sounds/error.wav");
	m_cams.push_back(m_cam);
	m_cams.push_back(m_smallCam);

	//ImplodeEngine::m_multiCams = m_cams;
	//ImplodeEngine::m_gameCam.SetCam(sf::Vector2f(1280.0f,720.0f), sf::Vector2f(640.0f,360.0f), sf::Vector2f(0.0f,0.0f));
	p = new AssetPool();

	p->LoadTexture("resources/textures/Banner.png", "Banner");
	p->LoadTexture("resources/textures/BigCrate.png", "Crate");
	p->LoadTexture("resources/textures/FountainBig.png", "Fountain");
	p->LoadTexture("resources/textures/FountainBig.png", "Fountain");
	p->LoadTexture("resources/textures/RuinedBrickFormation.png", "Bricks");
	p->LoadFont("resources/fonts/Roboto-Light.ttf", "font");
	p->LoadTexture("resources/textures/missile.jpg", "Missile");
	p->LoadTexture("resources/textures/man.png", "Man");
	p->LoadTexture("resources/textures/BigCrate.png", "crateBackground");
	p->LoadTexture("resources/textures/scottyboi.png", "pilgrim");

	backGround.setTexture(p->GetTexture("crateBackground"));
	backGround.setPosition(sf::Vector2f(-200.0f, -700.0f));
	backGround.setScale(50.0f, 50.0f);

	banner.setTexture(p->GetTexture("Banner"));
	banner.setPosition(sf::Vector2f(800, 400));

	crate.setTexture(p->GetTexture("Crate"));
	crate.setPosition(sf::Vector2f(600, 300));

	fountain.setTexture(p->GetTexture("Fountain"));
	fountain.setPosition(sf::Vector2f(1159, 287));

	bricks.setTexture(p->GetTexture("Bricks"));
	bricks.setPosition(sf::Vector2f(864, 507));

	crate2.setTexture(p->GetTexture("Crate"));
	crate2.setPosition(sf::Vector2f(1014, 386));

	crate3.setTexture(p->GetTexture("Crate"));
	crate3.setPosition(sf::Vector2f(827, 240));

	crate4.setTexture(p->GetTexture("Crate"));
	crate4.setPosition(sf::Vector2f(1014, 240));

	crate5.setTexture(p->GetTexture("Crate"));
	crate5.setPosition(sf::Vector2f(912, 311));

	crate6.setTexture(p->GetTexture("Crate"));
	crate6.setPosition(sf::Vector2f(827, 386));

	pool = new PoolExample();
	t.create(1280, 720);
	gameWorld.create(1280, 720);

	s.setPosition(0.0f, 0.0f);
	gameWorldSprite.setPosition(0.0f, 0.0f);

	txt.setCharacterSize(20);
	txt.setFont(p->GetFont("font"));
	txt.setFillColor(sf::Color::Green);
	txt.setPosition(sf::Vector2f(0.0f, 0.0f));

	this->m_particle = Particle(p->GetTexture("Missile"),sf::Vector2f(0.0f,-1.0f));
	this->m_light = Light(400.0f, sf::Vector2f(640.0f, 460.0f), true, sf::Color(0.0f, 180.0f, 180.0f,1.0f));
	this->m_emitter = new ParticleEmitter(1000, p->GetTexture("Missile"), sf::Vector2f(0.0f, -1.0f));
	Light l = Light(800.0f, sf::Vector2f(1000.0f, 300.0f), true, sf::Color(0.0f, 0.0f, 180.0f));

	this->m_shader.loadFromFile("resources/shaders/vertShader.vert","resources/shaders/fragShader.frag");

	this->m_boundaryManager.AddSprite(&banner);
	this->m_boundaryManager.AddSprite(&bricks);
	this->m_boundaryManager.AddSprite(&fountain);
	this->m_boundaryManager.AddSprite(&crate);
	this->m_boundaryManager.AddSprite(&crate2);
	this->m_boundaryManager.AddSprite(&crate3);
	this->m_boundaryManager.AddSprite(&crate4);
	this->m_boundaryManager.AddSprite(&crate5);
	this->m_boundaryManager.AddSprite(&crate6);

	this->m_animationTest = Animation(0.16, sf::Vector2f(100, 100));
	this->m_animationTest.SetAnimationSheet(p->GetTexture("pilgrim"), 2, 8);
	this->m_animationTest.SetRepeated(true);
	this->m_animationTest.SetAutomaticRowLoop(true);

	this->m_boundaryManager.AddSprite(&this->m_animationTest.GetAnimationSprite());

	this->m_lightingManager->m_boundaryManager = this->m_boundaryManager;
	this->m_lightingManager->m_lights.push_back(this->m_light);
	this->m_lightingManager->m_lights.push_back(l);
	this->m_lightingManager->m_lightSprites.push_back(this->m_lightingManager->CreateTexture(this->m_lightingManager->m_lights[0]));
	this->m_lightingManager->m_lightSprites.push_back(this->m_lightingManager->CreateTexture(this->m_lightingManager->m_lights[1]));
}

MenuState::~MenuState()
{
	this->m_soundManager->~SoundManager();
}

void MenuState::Update(float deltaTime)
{
	this->pool->Update(deltaTime);
	this->m_particle.Update(deltaTime);
	//this->m_cam->Update(deltaTime, sf::Vector2f(sf::Mouse::getPosition(*this->m_context->GetWindow()).x, sf::Mouse::getPosition(*this->m_context->GetWindow()).y));
	this->m_smallCam->Update(deltaTime);
	std::string str = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).x);
	std::string str2 = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).y);
	txt.setString(std::string("X position: " + str + "Y position: " + str2 ));
	this->m_emitter->Update(deltaTime,*this->m_lightingManager);
	if (this->m_soundManager->GetMusic("Error").getStatus() == sf::SoundStream::Stopped)
		this->m_soundManager->GetMusic("Error").stop();
	this->m_animationTest.Update(deltaTime);
	
	this->m_lightingManager->UpdateLightSprite(this->m_lightingManager->m_lightSprites[0], 800.0f,
		sf::Vector2f(sf::Mouse::getPosition(*this->m_context->GetWindow()).x, sf::Mouse::getPosition(*this->m_context->GetWindow()).y),true, sf::Color(0.0f, 0.0f, 180.0f));
}

void MenuState::Draw()
{
	sf::Sprite mySprite;
	sf::Sprite mapSprite;
	mySprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	t.clear(sf::Color(50, 50, 50, 0));
	gameWorld.clear(sf::Color(50, 50, 50, 0));
	gameWorld.draw(backGround,&this->m_shader);
	gameWorld.draw(banner);
	gameWorld.draw(crate);
	gameWorld.draw(crate2);
	gameWorld.draw(crate3);
	gameWorld.draw(crate4);
	gameWorld.draw(crate5);
	gameWorld.draw(crate6);
	gameWorld.draw(fountain);
	gameWorld.draw(bricks);
	this->m_particle.Draw(gameWorld);
	this->m_emitter->Draw(gameWorld);
	gameWorld.draw(this->m_lightingManager->m_lightSprites[0].lightSprite);
	gameWorld.draw(this->m_lightingManager->m_lightSprites[1].lightSprite);
	this->m_animationTest.Render(gameWorld);
	gameWorld.display();

	gameWorldSprite.setTexture(gameWorld.getTexture());
	//mySprite = this->m_cam->Draw(gameWorldSprite,sf::Color::Green);
	//mapSprite = this->m_smallCam->Draw(gameWorldSprite, sf::Color::Blue);
	this->pool->Draw(t);
	t.display();
	s.setTexture(t.getTexture());

	ImplodeEngine::m_gameWorldTxtr.draw(gameWorldSprite);
	ImplodeEngine::m_uiTxtr.draw(s);
	ImplodeEngine::m_uiTxtr.draw(txt);
	
}

void MenuState::ProcessEvents(sf::Event& e)
{
	this->pool->ProcessEvents(e, this->m_context->GetWindow());
	this->m_cam->ProcessInput(e);
	if (e.type == sf::Event::KeyPressed )
	{
  		float randX = rand()%1280;
		float randY = rand() % 720;

		float endX = rand() % 2560 + (-1280);
		float endY = rand() % 1440 + (-720);

		float randVelX = rand() % 19 + (-9);
		float randVelY = rand()% 19 + (-9);
		
		float randSpd = rand()& 40 + 200;

		float randTimeLim = rand()%100;
		if (e.key.code == sf::Keyboard::Space)
		{
			this->m_emitter->CreateParticle(sf::Vector2f(rand() % 1280, rand() % 720), sf::Vector2f(rand() % 2560 + (-1280), rand() % 1440 + (-720)), sf::Vector2f(1.0f, 2.0f), rand() & 40 + 200, randTimeLim, p->GetTexture("Missile"), sf::Vector2f(0.0f, -1.0f), *this->m_lightingManager,true);
		}
		if(e.key.code == sf::Keyboard::B)
			this->m_emitter->CreateParticle(sf::Vector2f(rand() % 1280, rand() % 720), sf::Vector2f(rand() % 2560 + (-1280), rand() % 1440 + (-720)), sf::Vector2f(1.0f, 2.0f), rand() & 40 + 200, randTimeLim, p->GetTexture("Man"), sf::Vector2f(0.0f, -1.0f), *this->m_lightingManager,true);
		if (e.key.code == sf::Keyboard::G)
			this->m_soundManager->PlayMusic("Error");
	}
}


