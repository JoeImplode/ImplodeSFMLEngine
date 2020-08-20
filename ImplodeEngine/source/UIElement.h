#pragma once

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class UIElement
{
public:
	UIElement() {};
	UIElement(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool activated);
	inline virtual void Update(float deltaTime) { ; }
	inline virtual void Render(sf::RenderWindow* window) { ; }
	inline virtual void ProcessInput(sf::Event& e, sf::RenderWindow* window) { ; }
	inline virtual void Notify() { ; }
	inline virtual void Selected() { ; }
	inline sf::Vector2f GetPosition() { return this->m_position; }
	virtual void UpdatePosition(sf::Vector2f position) { this->m_position = position; }
	inline virtual sf::Vector2f GetOrigin() = 0;
	inline void SetLabelPos(sf::Vector2f offsetPosition) {
		this->m_label.setPosition(sf::Vector2f(GetOrigin().x + offsetPosition.x, GetOrigin().y + offsetPosition.y)); this->m_offsetPosition = offsetPosition;
	}
	inline std::string GetType() { return this->m_type; }
	void SetType(std::string type) { this->m_type = type; }
	sf::Text m_label;
	inline bool GetActivated() { return m_activated; }
	inline void SetActivated(bool activated) { this->m_activated = activated; }
	inline bool& GetActivatedAddress() { return m_activated; }
private:
	
protected:
	sf::Vector2f m_position; 
	sf::Vector2f m_scale;
	sf::Vector2f m_offsetPosition;
	std::string m_type;
	bool m_activated;
};

class Button : public UIElement
{
public:
	Button(bool& reference);
	Button(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool &reference, bool activated, bool valToSet = false);

	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Selected() override;
	void SetButtonText(sf::Text textExample); 
	void SetTexture(sf::Texture& texture);
	void UpdatePosition(sf::Vector2f position) override;
	inline sf::Vector2f GetOrigin() override { return sf::Vector2f(((this->m_position.x + (this->m_buttonSprite.getLocalBounds().width * this->m_scale.x) / 2)), (this->m_position.y + (this->m_buttonSprite.getLocalBounds().height * this->m_scale.y) / 2)); }
	inline void SetBoolRef(bool& reference) { this->m_boolRef = reference; }
	inline void Notify() override { this->m_boolRef = m_valToSet;  std::cout << "Notified!" << std::endl; }
	inline void SetValToSet(bool valToSet) { this->m_valToSet = valToSet; }
	inline void SetPos(sf::Vector2f pos) { this->m_position = pos; }
	inline float GetWidth() { return this->m_buttonSprite.getLocalBounds().width * this->m_scale.x; }
	inline float GetHeight() { return this->m_buttonSprite.getLocalBounds().height * this->m_scale.y; }
	inline bool GetValToSet() { return this->m_valToSet; }
	sf::Text m_buttonText;
private:
	sf::Sprite m_buttonSprite;
	sf::Color m_initialColor;
	bool& m_boolRef; 
	bool m_valToSet = false;
	
	
protected:
};

class Slider : public UIElement
{
public:
	Slider(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, float& reference, bool activated);
	void SetTextures(sf::Texture& barTexture, sf::Texture& selectorTexture);
	void Update(float deltaTime)override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override;
	void UpdatePosition(sf::Vector2f position) override;
	void Selected() override;

	inline void SetFloatRef(float& reference) { this->m_floatRef = reference; }
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_position.x + (this->m_barSprite.getLocalBounds().width / 2)), this->m_position.y + (this->m_barSprite.getLocalBounds().height / 2));
	}
	sf::Text m_buttonText;
private:
	sf::Sprite m_barSprite;
	sf::Sprite m_selectorSprite;
	sf::Color m_initialBarColour;
	sf::Color m_initialSliderColour;
	sf::Vector2f m_selectorScale;
	float& m_floatRef;
	bool m_dragging = false;
protected:
};

class ButtonGroup : public UIElement
{
public:
	ButtonGroup(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, bool orientation, bool& reference, sf::Texture &borderTexture, bool activated);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void SetButtons(sf::Texture& leftTexture, sf::Vector2f scaleLeft,sf::Texture& rightTexture, sf::Vector2f scaleRight);
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_position.x + (this->m_border.getLocalBounds().width / 2)), this->m_position.y + (this->m_border.getLocalBounds().height / 2));}
	void UpdatePosition(sf::Vector2f position) override;
	Button* m_leftButton; 
	Button* m_rightButton;
private:
	sf::RectangleShape m_border;
	bool m_orientation;
	bool& m_boolRef;
protected:
};

class Widget : public UIElement
{
public:
	Widget(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& widgetTexture, bool activated);
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window) override;
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_position.x + (this->m_border.getLocalBounds().width / 2)), this->m_position.y + (this->m_border.getLocalBounds().height / 2));
	}
	void AddElement(UIElement* element, sf::Vector2f percentagePos);
	std::vector<UIElement*> m_elements;
private:
	sf::RectangleShape m_border;
protected:
};

class DropDown : public UIElement
{
public:
	DropDown(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Text buttonText, sf::Texture& buttonTexture, bool &boolref, bool activated);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void AddSelection(sf::Text buttonText,std::string textString, sf::Texture& buttonTexture, sf::Vector2f buttonScale, bool& reference);
	inline sf::Vector2f GetOrigin() override { 
		return sf::Vector2f(this->m_activatorButton->GetOrigin());
	}
	void UpdatePosition(sf::Vector2f position) override;

private:
	Button * m_activatorButton;
	std::vector<Button* > m_buttons;
	bool m_dropDownShowing = false;
protected:
};

class TextInput : public UIElement
{
public:
	TextInput(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& buttonTexture, sf::Texture& textBoxTexture, sf::Vector2f buttonScale,
		std::string& stringToSet, int characterLimit, int scrollableLimit,std::string buttonLabel, bool activated, sf::Event & event,sf::RenderWindow & window, sf::Font & font);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void UpdatePosition(sf::Vector2f position) override;
	inline sf::Vector2f GetOrigin() override { return sf::Vector2f(200, 200); }
private:
	void UpdateTextBox(int charTyped);
	void DeleteLastChar();
	Button* m_sendButton;
	sf::RectangleShape m_textBoxTexture;
	sf::Text m_inputText;
	std::ostringstream m_textString;
	std::string& m_string;
	bool m_focused = false;
	bool m_wasFocused;
	int m_characterLimit;
	int m_scrollableLimit;
	bool m_sendPressed = false;
	bool m_sendWasPressed = false;
	sf::Event& m_event;
	sf::RenderWindow& m_renderWindow;
protected:
};


class Publisher
{
public:
	void Update(float deltaTime, bool notified, bool dragged,sf::Vector2f mousePos);
	void Render(sf::RenderWindow* window);
	void ProcessInput(sf::Event& event, sf::RenderWindow* window);
	inline void AddElement(UIElement* element) { this->m_elements.push_back(element); }
private:
	std::vector<UIElement*> m_elements;
protected:
};

