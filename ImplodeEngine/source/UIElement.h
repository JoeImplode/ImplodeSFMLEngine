#pragma once

class UIElement
{
public:
	UIElement() {};
	UIElement(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale);
	inline virtual void Update(float deltaTime, bool notified,sf::Vector2f mousePos) { ; }
	inline virtual void Render(sf::RenderWindow* window) { ; }
	inline virtual void Notify() { ; }
	inline virtual void Selected() { ; }
	inline sf::Vector2f GetPosition() { return this->m_position; }
	inline void UpdateLabel(sf::Vector2f position) { this->m_label.setPosition(sf::Vector2f(position.x + m_labelRelativePosition.x, position.y + m_labelRelativePosition.y)); }
	inline virtual sf::Vector2f GetOrigin() { return sf::Vector2f(0, 0); };+
	sf::Text m_label; //our label for our UI element
private:
	
protected:
	sf::Vector2f m_position; //our position for the UI element
	sf::Vector2f m_scale; //our Scale for the UI element
	sf::Vector2f m_labelRelativePosition; //our relative position for the text, we use this to ensure that we're just linking the text with the element position - useful for widgets e.t.c
};

class Button : public UIElement
{
public:
	Button(bool& reference);
	Button(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, bool &reference, bool valToSet = false);
	inline void SetBoolRef(bool& reference) { this->m_boolRef = reference; }
	inline sf::Vector2f GetOrigin() override { return sf::Vector2f(((this->m_buttonSprite.getLocalBounds().width * this->m_scale.x) / 2), (this->m_buttonSprite.getLocalBounds().height* this->m_scale.y) / 2); }
	void SetTexture(sf::Texture& texture);

	void Update(float deltaTime, bool notified, sf::Vector2f mousePos) override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override { this->m_boolRef = m_valToSet; std::cout << m_boolRef << std::endl; } //this will be our code for if the button was notified
	void Selected() override;

	void SetButtonText(sf::Text textExample); //scalars for x,y offset and size, change these values round to get preferred orientation
	void SetValToSet(bool valToSet) { this->m_valToSet = valToSet; }
	void SetPos(sf::Vector2f pos) { this->m_position = pos; }
	float GetWidth() { return this->m_buttonSprite.getLocalBounds().width * this->m_scale.x; }
	float GetHeight() { return this->m_buttonSprite.getLocalBounds().height * this->m_scale.y; }
	sf::Text m_buttonText;
private:
	sf::Sprite m_buttonSprite;
	sf::Color m_initialColor;
	bool& m_boolRef; //the reference variable we want to change with the button
	bool m_valToSet = false;
protected:
};

class Slider : public UIElement
{
public:
	Slider(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, float& reference); //strictly speaking, the same as the button but here we use the slider as a button
	void SetTextures(sf::Texture& barTexture, sf::Texture& selectorTexture);
	inline void SetFloatRef(float& reference) { this->m_floatRef = reference; }

	void Update(float deltaTime, bool notified, sf::Vector2f mousePos)override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override;
	void Selected() override;

	sf::Text m_buttonText;
private:
	sf::Sprite m_barSprite;
	sf::Sprite m_selectorSprite;
	sf::Color m_initialBarColour;
	sf::Color m_initialSliderColour;
	sf::Vector2f m_selectorScale;
	float& m_floatRef;
protected:
};

class ButtonGroup : public UIElement
{
public:
	ButtonGroup(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, float orientation, bool& reference, sf::Texture &borderTexture);
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos) override;
	void Render(sf::RenderWindow* window) override;
	void SetButtons(Button *leftButton, Button * rightButton);
private:
	Button * m_leftButton; //buttons for yes and no
	Button * m_rightButton;
	sf::RectangleShape m_border;
	float m_orientation;
	bool& m_boolRef;
protected:
};

class Publisher
{
public:
	inline void AddElement(UIElement* element) { this->m_elements.push_back(element); }
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos);
	void Render(sf::RenderWindow* window);
private:
	std::vector<UIElement*> m_elements;
protected:
};

