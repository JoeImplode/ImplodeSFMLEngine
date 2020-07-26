#pragma once
#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"

class MenuState : public GameState
{
public:
	MenuState();
	void Update(float deltaTime) override;
	void Draw() override;
private:
	sf::RectangleShape rect;
	AssetPool* m_assetPool;
	Button* m_button;
	Button* m_yesButton;
	Button* m_noButton;
	ButtonGroup* m_buttonGroup;

	Slider* m_slider;
	Publisher* m_publisher;
	bool buttonState = false;
	float floatRef = 0.0f;
	bool m_boolToCheck = false;
};