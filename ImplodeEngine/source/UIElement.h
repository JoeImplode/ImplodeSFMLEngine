#pragma once

class UIElement
{
public:
	UIElement(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale);
	inline virtual void Update(float deltaTime, bool notified,sf::Vector2f mousePos) { ; }
	inline virtual void Render(sf::RenderWindow* window) { ; }
	inline virtual void Notify() { ; }
	inline virtual void Selected() { ; }
	sf::Text m_label; //our label for our UI element
private:
	
protected:
	bool m_notified; //our notifier to see if the element has been notified
	sf::Font m_font; //our font for our UI element
	sf::Vector2f m_position; //our position for the UI element
	sf::Vector2f m_scale; //our Scale for the UI element
};

class Button : public UIElement
{
public:
	Button(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, bool &reference);
	void SetTexture(sf::Texture &texture);
	inline void SetBoolRef(bool& reference) { this->m_boolRef = reference; }
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos) override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override { this->m_boolRef = true; std::cout << "Button Pressed" << std::endl; } //this will be our code for if the button was notified
	void Selected() override;
	sf::Text m_buttonText;
private:
	bool& m_boolRef; //the reference variable we want to change with the button
	sf::Sprite m_buttonSprite;
	sf::Color m_initialColor;
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
	float& m_floatRef;
	sf::Vector2f m_selectorScale;
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