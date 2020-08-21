#pragma once
#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"

class MenuState : public GameState
{
public:
	MenuState(GameContext* context);
	void Update(float deltaTime) override;
	void Draw() override;
	void ProcessEvents(sf::Event& e) override;
private:
	sf::RectangleShape rect;
	AssetPool* m_assetPool;
	Button* m_button;
	ButtonGroup* m_buttonGroup;
	Widget* m_widgetGroup;
	Slider* m_slider;
	Publisher* m_publisher;
	DropDown* m_dropDown;
	sf::Vector2f m_mousePos;
	sf::Vector2f m_prevMousePos;
	TextInput* m_textInput;
	std::string m_stringToSet;

	bool buttonState = false;
	float floatRef = 0.0f;
	bool m_boolToCheck = false;
};