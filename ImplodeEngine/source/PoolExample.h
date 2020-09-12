#include "UIPool.h"

class PoolExample : public UIPool
{
public:
	PoolExample();
	PoolExample(AssetPool* pool);
	void Update(float deltaTime) override;
	virtual void Draw(sf::RenderWindow* window) override;
	virtual void ProcessEvents(sf::Event& e, sf::RenderWindow* window) override;
	Button* m_button;
	Button* m_pauseButton1;
	Button* m_pauseButton2;
	Button* m_pauseButton3;
	ButtonGroup* m_buttonGroup;
	Widget* m_widgetGroup;
	Widget* m_quitGroup;
	Slider* m_slider;
	Slider* m_volumeSlider;
	DropDown* m_dropDown;
	sf::Vector2f m_mousePos;
	sf::Vector2f m_prevMousePos;
	TextInput* m_textInput;
	std::string m_stringToSet;
	TextLog* m_textLog;
	std::string m_prevString;
	sf::Text m_tempText;

	bool buttonState = false;
	float floatRef = 0.0f;
	bool m_boolToCheck = false;
	bool m_quitBool = false;
private:
protected:
};