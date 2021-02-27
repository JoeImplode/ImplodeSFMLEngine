#include "pch.h"
#include "GameState.h"
#include "MainGame.h"
#include "Player.h"
#include "Enemy.h"
#include "ImplodeEngine.h"
MainGame::MainGame(GameContext* context) : GameState(context)
{
	
}

void MainGame::Update(float deltaTime)
{

	std::string str = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).x);
	std::string str2 = std::to_string(sf::Mouse::getPosition(*this->m_context->GetWindow()).y);
	this->m_mousePosition.setString("Mouse X: " + str + "Mouse Y: " + str2);
	this->m_player.Update(deltaTime);
	this->m_enemyColourShader.setUniform("colour", sf::Glsl::Vec4(this->m_skeleton.GetShaderColour()));
	this->m_skeleton.Update(deltaTime);
}

void MainGame::ProcessEvents(sf::Event& e)
{
	this->m_player.ProcessEvents(e);
}

void MainGame::Initialise()
{
	this->m_pool = AssetPool();
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Green/Gunner_Green_Run.png", "GreenGunnerRun");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Green/Gunner_Green_Death.png", "GreenGunnerDeath");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Green/Gunner_Green_Idle.png", "GreenGunnerIdle");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Green/Gunner_Green_Crouch.png", "GreenGunnerCrouch");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Green/Gunner_Green_Jump.png", "GreenGunnerJump");

	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Black/Gunner_Black_Run.png", "BlackGunnerRun");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Black/Gunner_Black_Death.png", "BlackGunnerDeath");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Black/Gunner_Black_Idle.png", "BlackGunnerIdle");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Black/Gunner_Black_Crouch.png", "BlackGunnerCrouch");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Black/Gunner_Black_Jump.png", "BlackGunnerJump");

	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Blue/Gunner_Blue_Run.png", "BlueGunnerRun");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Blue/Gunner_Blue_Death.png", "BlueGunnerDeath");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Blue/Gunner_Blue_Idle.png", "BlueGunnerIdle");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Blue/Gunner_Blue_Crouch.png", "BlueGunnerCrouch");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Blue/Gunner_Blue_Jump.png", "BlueGunnerJump");

	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Red/Gunner_Red_Run.png", "RedGunnerRun");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Red/Gunner_Red_Death.png", "RedGunnerDeath");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Red/Gunner_Red_Idle.png", "RedGunnerIdle");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Red/Gunner_Red_Crouch.png", "RedGunnerCrouch");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Red/Gunner_Red_Jump.png", "RedGunnerJump");

	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Yellow/Gunner_Yellow_Run.png", "YellowGunnerRun");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Yellow/Gunner_Yellow_Death.png", "YellowGunnerDeath");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Yellow/Gunner_Yellow_Idle.png", "YellowGunnerIdle");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Yellow/Gunner_Yellow_Crouch.png", "YellowGunnerCrouch");
	this->m_pool.LoadTexture("resources/textures/CHARACTER_SPRITES/Yellow/Gunner_Yellow_Jump.png", "YellowGunnerJump");

	this->m_pool.LoadTexture("resources/textures/WEAPONS/PISTOL_BULLET.png", "PISTOL_BULLET");
	this->m_pool.LoadTexture("resources/textures/WEAPONS/SHOTGUN_PELLET.png", "SHOTGUN_PELLET");
	this->m_pool.LoadTexture("resources/textures/WEAPONS/DMR_ROUND.png", "DMR_ROUND");

	this->m_pool.LoadFont("resources/fonts/Roboto-Light.ttf", "DefaultFont");

	this->m_pool.LoadTexture("resources/textures/ENEMY_SPRITES/Skeleton/skeleton.png", "SKELETON_IDLE");
	this->m_pool.LoadTexture("resources/textures/ENEMY_SPRITES/Skeleton/skeleton_attack.png", "SKELETON_ATTACK");
	this->m_pool.LoadTexture("resources/textures/ENEMY_SPRITES/Skeleton/skeleton_run.png", "SKELETON_RUN");
	this->m_pool.LoadTexture("resources/textures/ENEMY_SPRITES/Skeleton/skeleton_die.png", "SKELETON_DIE");

	this->m_player = Player();
	this->m_player.m_animationSheet = Animation(0.1, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(2.5, 2.5));
	this->m_player.m_animationSheet.SetRepeated(true);
	this->m_player.SetSpeed(sf::Vector2f(0.4, 0.4));
	this->m_player.SetScale(this->m_player.m_animationSheet.GetScale());

	this->m_mousePosition.setCharacterSize(26);
	this->m_mousePosition.setFont(this->m_pool.GetFont("DefaultFont"));
	this->m_mousePosition.setPosition(sf::Vector2f(10, 10));
	this->m_mousePosition.setFillColor(sf::Color::Green);
	this->SetupAssets();

	this->m_enemyColourShader.loadFromFile("resources/shaders/cColourChanger.vert", "resources/shaders/cColourChanger.frag");
	

}

void MainGame::SetupAssets()
{
	std::map<PLAYER_STATE, Animation> playerAnimations;
	Animation ConstructAnimation = Animation(0.1, sf::Vector2f(400.0f, 400.0f), sf::Vector2f(2.5, 2.5));

	Animation pIdleAnimation;
	pIdleAnimation = ConstructAnimation;
	pIdleAnimation.SetAnimationSheet(this->m_pool.GetTexture("GreenGunnerIdle"),1, 5);
	pIdleAnimation.SetRepeated(true);
	playerAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::IDLE, pIdleAnimation));

	Animation pRunAnimation;
	pRunAnimation = ConstructAnimation;
	pRunAnimation.SetAnimationSheet(this->m_pool.GetTexture("GreenGunnerRun"), 1, 6);
	pRunAnimation.SetRepeated(true);
	playerAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::RUN, pRunAnimation));
	
	Animation pDeathAnimation;
	pDeathAnimation = ConstructAnimation;
	pDeathAnimation.SetAnimationSheet(this->m_pool.GetTexture("GreenGunnerDeath"), 1, 8);
	playerAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::DEATH, pDeathAnimation));

	Animation pJumpAnimation;
	pJumpAnimation = ConstructAnimation;
	pJumpAnimation.SetAnimationSheet(this->m_pool.GetTexture("GreenGunnerJump"), 1, 2);
	playerAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::JUMP, pJumpAnimation));

	Animation pCrouchAnimation;
	pCrouchAnimation = ConstructAnimation;
	pCrouchAnimation.SetAnimationSheet(this->m_pool.GetTexture("GreenGunnerCrouch"), 1, 3);
	playerAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::CROUCH, pCrouchAnimation));

	//---------------------------------------------------------------------------------------------------------
	std::map<PLAYER_STATE, Animation> playerBlueAnimations;

	Animation pbIdleAnimation;
	pbIdleAnimation = ConstructAnimation;
	pbIdleAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlueGunnerIdle"), 1, 5);
	pbIdleAnimation.SetRepeated(true);
	playerBlueAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::IDLE, pbIdleAnimation));

	Animation pbRunAnimation;
	pbRunAnimation = ConstructAnimation;
	pbRunAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlueGunnerRun"), 1, 6);
	pbRunAnimation.SetRepeated(true);
	playerBlueAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::RUN, pbRunAnimation));

	Animation pbDeathAnimation;
	pbDeathAnimation = ConstructAnimation;
	pbDeathAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlueGunnerDeath"), 1, 8);
	playerBlueAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::DEATH, pbDeathAnimation));

	Animation pbJumpAnimation;
	pbJumpAnimation = ConstructAnimation;
	pbJumpAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlueGunnerJump"), 1, 2);
	playerBlueAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::JUMP, pbJumpAnimation));

	Animation pbCrouchAnimation;
	pbCrouchAnimation = ConstructAnimation;
	pbCrouchAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlueGunnerCrouch"), 1, 3);
	playerBlueAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::CROUCH, pbCrouchAnimation));

	//---------------------------------------------------------------------------------------------------------
	std::map<PLAYER_STATE, Animation> playerBlackAnimations;

	Animation pblIdleAnimation;
	pblIdleAnimation = ConstructAnimation;
	pblIdleAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlackGunnerIdle"), 1, 5);
	pblIdleAnimation.SetRepeated(true);
	playerBlackAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::IDLE, pblIdleAnimation));

	Animation pblRunAnimation;
	pblRunAnimation = ConstructAnimation;
	pblRunAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlackGunnerRun"), 1, 6);
	pblRunAnimation.SetRepeated(true);
	playerBlackAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::RUN, pblRunAnimation));

	Animation pblDeathAnimation;
	pblDeathAnimation = ConstructAnimation;
	pblDeathAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlackGunnerDeath"), 1, 8);
	playerBlackAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::DEATH, pblDeathAnimation));

	Animation pblJumpAnimation;
	pblJumpAnimation = ConstructAnimation;
	pblJumpAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlackGunnerJump"), 1, 2);
	playerBlackAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::JUMP, pblJumpAnimation));

	Animation pblCrouchAnimation;
	pblCrouchAnimation = ConstructAnimation;
	pblCrouchAnimation.SetAnimationSheet(this->m_pool.GetTexture("BlackGunnerCrouch"), 1, 3);
	playerBlackAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::CROUCH, pblCrouchAnimation));

	//---------------------------------------------------------------------------------------------------------

	std::map<PLAYER_STATE, Animation> playerRedAnimations;

	Animation predIdleAnimation;
	predIdleAnimation = ConstructAnimation;
	predIdleAnimation.SetAnimationSheet(this->m_pool.GetTexture("RedGunnerIdle"), 1, 5);
	predIdleAnimation.SetRepeated(true);
	playerRedAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::IDLE, predIdleAnimation));

	Animation predRunAnimation;
	predRunAnimation = ConstructAnimation;
	predRunAnimation.SetAnimationSheet(this->m_pool.GetTexture("RedGunnerRun"), 1, 6);
	predRunAnimation.SetRepeated(true);
	playerRedAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::RUN, predRunAnimation));

	Animation predDeathAnimation;
	predDeathAnimation = ConstructAnimation;
	predDeathAnimation.SetAnimationSheet(this->m_pool.GetTexture("RedGunnerDeath"), 1, 8);
	playerRedAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::DEATH, predDeathAnimation));

	Animation predJumpAnimation;
	predJumpAnimation = ConstructAnimation;
	predJumpAnimation.SetAnimationSheet(this->m_pool.GetTexture("RedGunnerJump"), 1, 2);
	playerRedAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::JUMP, predJumpAnimation));

	Animation predCrouchAnimation;
	predCrouchAnimation = ConstructAnimation;
	predCrouchAnimation.SetAnimationSheet(this->m_pool.GetTexture("RedGunnerCrouch"), 1, 3);
	playerRedAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::CROUCH, predCrouchAnimation));

	//---------------------------------------------------------------------------------------------------------
	std::map<PLAYER_STATE, Animation> playerYellowAnimations;

	Animation pylwIdleAnimation;
	pylwIdleAnimation = ConstructAnimation;
	pylwIdleAnimation.SetAnimationSheet(this->m_pool.GetTexture("YellowGunnerIdle"), 1, 5);
	pylwIdleAnimation.SetRepeated(true);
	playerYellowAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::IDLE, pylwIdleAnimation));

	Animation pylwRunAnimation;
	pylwRunAnimation = ConstructAnimation;
	pylwRunAnimation.SetAnimationSheet(this->m_pool.GetTexture("YellowGunnerRun"), 1, 6);
	pylwRunAnimation.SetRepeated(true);
	playerYellowAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::RUN, pylwRunAnimation));

	Animation pylwDeathAnimation;
	pylwDeathAnimation = ConstructAnimation;
	pylwDeathAnimation.SetAnimationSheet(this->m_pool.GetTexture("YellowGunnerDeath"), 1, 8);
	playerYellowAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::DEATH, pylwDeathAnimation));

	Animation pylwJumpAnimation;
	pylwJumpAnimation = ConstructAnimation;
	pylwJumpAnimation.SetAnimationSheet(this->m_pool.GetTexture("YellowGunnerJump"), 1, 2);
	playerYellowAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::JUMP, pylwJumpAnimation));

	Animation pylwCrouchAnimation;
	pylwCrouchAnimation = ConstructAnimation;
	pylwCrouchAnimation.SetAnimationSheet(this->m_pool.GetTexture("YellowGunnerCrouch"), 1, 3);
	playerYellowAnimations.insert(std::pair<PLAYER_STATE, Animation>(PLAYER_STATE::CROUCH, pylwCrouchAnimation));

	//---------------------------------------------------------------------------------------------------------
	Animation skeletonAnimationRunning;
	skeletonAnimationRunning.SetAnimationSheet(this->m_pool.GetTexture("SKELETON_RUN"),1,8);

	Animation skeletonAnimationAttacking;
	skeletonAnimationAttacking.SetAnimationSheet(this->m_pool.GetTexture("SKELETON_ATTACK"), 1, 3);

	Animation skeletonAnimationDying;
	skeletonAnimationDying.SetAnimationSheet(this->m_pool.GetTexture("SKELETON_DIE"), 1, 5);

	Animation skeletonAnimationIDLE;
	skeletonAnimationIDLE.SetAnimationSheet(this->m_pool.GetTexture("SKELETON_IDLE"), 1, 8);
	skeletonAnimationIDLE.SetScale(sf::Vector2f(2.3, 2.3));

	this->m_player.m_colours.insert(std::pair<std::string, std::map <PLAYER_STATE, Animation>>("Green", playerAnimations));
	this->m_player.m_colours.insert(std::pair<std::string, std::map <PLAYER_STATE, Animation>>("Blue", playerBlueAnimations));
	this->m_player.m_colours.insert(std::pair<std::string, std::map <PLAYER_STATE, Animation>>("Black", playerBlackAnimations));
	this->m_player.m_colours.insert(std::pair<std::string, std::map <PLAYER_STATE, Animation>>("Red", playerRedAnimations));
	this->m_player.m_colours.insert(std::pair<std::string, std::map <PLAYER_STATE, Animation>>("Yellow", playerYellowAnimations));

	this->m_player.m_animationSheet = this->m_player.m_animations[PLAYER_STATE::IDLE];
	this->m_player.SetSpeed(sf::Vector2f(0.2,0.2));
	this->m_player.UpdateColours();
	this->m_player.SetUpEmitters(this->m_pool.GetTexture("PISTOL_BULLET"), this->m_pool.GetTexture("SHOTGUN_PELLET"), this->m_pool.GetTexture("PISTOL_BULLET"), this->m_pool.GetTexture("DMR_ROUND"));

	this->m_skeleton = Skeleton(sf::Vector2f(360.0f, 200.0f), 10, ENEMY_STATE::IDLE, true, skeletonAnimationIDLE,this->m_player.GetParticleEmitters(),sf::Color(255,0,0),false);
	this->m_skeleton.SetUpAnimations(skeletonAnimationIDLE, skeletonAnimationRunning, skeletonAnimationAttacking, skeletonAnimationDying);
	this->m_skeleton.m_animationSheet.SetRepeated(true);
	this->m_skeleton.m_animationSheet.SetScale(sf::Vector2f(2.3, 2.3));
	this->m_skeleton.m_animationSheet.SetSpeed(0.16);
	this->m_player.SetScale(this->m_player.m_animationSheet.GetScale());

	//this->m_player.m_pistolEmitter.SetParticleTxtr()
}

void MainGame::Draw()
{
	ImplodeEngine::m_gameWorldTxtr.draw(this->m_mousePosition);
	ImplodeEngine::m_gameWorldTxtr.draw(this->m_player.m_animationSheet.GetAnimationSprite());
	this->m_player.m_pistolEmitter.Draw(ImplodeEngine::m_gameWorldTxtr);
	this->m_player.m_shotgunEmitter.Draw(ImplodeEngine::m_gameWorldTxtr);
	this->m_player.m_dmrEmitter.Draw(ImplodeEngine::m_gameWorldTxtr);
	this->m_player.m_machineGunEmitter.Draw(ImplodeEngine::m_gameWorldTxtr);
	ImplodeEngine::m_gameWorldTxtr.draw(this->m_skeleton.m_animationSheet.GetAnimationSprite(),&this->m_enemyColourShader);
}

MainGame::~MainGame()
{
}
