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
	ButtonGroup* m_buttonGroup;
	Widget* m_widgetGroup;
	Slider* m_slider;
	Publisher* m_publisher;
	DropDown* m_dropDown;

	bool buttonState = false;
	float floatRef = 0.0f;
	bool m_boolToCheck = false;

	bool m_mouseIsDown = false;
	bool m_mouseWasDown = false;
};