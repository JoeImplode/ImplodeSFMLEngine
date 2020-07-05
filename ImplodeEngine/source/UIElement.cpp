#include "pch.h"
#include "UIElement.h"

UIElement::UIElement(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale)
{
	//when we construct a UI element, we want to set all the params which will be in each UI element
	this->m_label.setString(text);
	this->m_label.setPosition(textPos);
	this->m_position = elementPos;
	this->m_scale = scale;
	this->m_notified = false;
}

Button::Button(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, bool & reference) : UIElement(text,textPos,elementPos,scale),m_boolRef(reference)
{

}

void Button::SetTexture(sf::Texture& texture)
{
	this->m_buttonSprite.setTexture(texture);
	this->m_buttonSprite.setScale(this->m_scale);
	this->m_buttonSprite.setPosition(this->m_position);
	this->m_initialColor = this->m_buttonSprite.getColor();

}

void Button::Update(float deltaTime, bool notified, sf::Vector2f mousePos)
{
	if (mousePos.x >= this->m_position.x && mousePos.x <= this->m_position.x + this->m_buttonSprite.getLocalBounds().width
		&& mousePos.y >= this->m_position.y && mousePos.y <= this->m_position.y + this->m_buttonSprite.getLocalBounds().height)
	{
		if(this->m_buttonSprite.getColor() == this->m_initialColor)
			this->Selected();
		if (notified)
			this->Notify();
	}
	else if (this->m_buttonSprite.getColor() != this->m_initialColor)
		this->m_buttonSprite.setColor(this->m_initialColor);
}

void Button::Render(sf::RenderWindow* window)
{
	window->draw(this->m_buttonText);
	window->draw(this->m_buttonSprite);
}

void Button::Selected()
{
	sf::Color c = this->m_buttonSprite.getColor();
	c.r -= 70.0f;
	c.g -= 70.0f;
	c.b -= 70.0f;
	this->m_buttonSprite.setColor(c);
}

Slider::Slider(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, float& reference) : UIElement(text,textPos,elementPos,scale),m_floatRef(reference)
{
}

void Slider::SetTextures(sf::Texture &barTexture, sf::Texture &selectorTexture)
{
	this->m_barSprite.setTexture(barTexture);
	this->m_barSprite.setScale(this->m_scale);
	this->m_barSprite.setPosition(this->m_position);
	this->m_initialBarColour = this->m_barSprite.getColor();

	this->m_selectorSprite.setTexture(selectorTexture);
	this->m_selectorSprite.setScale(sf::Vector2f(this->m_scale.x / 10, this->m_scale.y / 2));
	this->m_selectorSprite.setPosition(this->m_scale);
	this->m_initialSliderColour = this->m_selectorSprite.getColor();
}

void Slider::Update(float deltaTime,bool notified,sf::Vector2f mousePos)
{

	if (mousePos.x >= this->m_barSprite.getPosition().x
		&& mousePos.x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x
		&& mousePos.y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height
		&& mousePos.y >= this->m_barSprite.getPosition().y)
	{
		if(this->m_barSprite.getColor() == m_initialBarColour)
			this->Selected();
		if (notified)
		{
			this->m_selectorSprite.setPosition(sf::Vector2f(mousePos.x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
	}
	else if (this->m_barSprite.getColor() != this->m_initialBarColour && this->m_selectorSprite.getColor() != this->m_initialSliderColour)
	{
		this->m_barSprite.setColor(this->m_initialBarColour);
		this->m_selectorSprite.setColor(this->m_initialSliderColour);
	}
}

void Slider::Render(sf::RenderWindow* window)
{
	window->draw(this->m_label);
	window->draw(this->m_barSprite);
	window->draw(this->m_selectorSprite);
}

void Slider::Notify()
{
	//x position of the bar sprite
	//x position of the slider
	//slider position needs to be out of the width
	float startPos = this->m_barSprite.getPosition().x - this->m_barSprite.getLocalBounds().width * this->m_scale.x;
	float endPos = this->m_barSprite.getPosition().x + (this->m_barSprite.getLocalBounds().width) * this->m_scale.x;
	float width = startPos + endPos;
	
	this->m_floatRef = (this->m_selectorSprite.getPosition().x) / endPos * 100 ; //here we're getting the percentage of the scale passed, so if we're at 200, and the scale is 400, we'll get 0.5
	std::cout << "FloatRef: " << this->m_floatRef << std::endl;
}

void Slider::Selected()
{
	sf::Color c = this->m_barSprite.getColor();
	c.r -= 70.0f;
	c.g -= 70.0f;
	c.b -= 70.0f;
	this->m_barSprite.setColor(c);

	sf::Color sc = this->m_selectorSprite.getColor();
	sc.r -= 70.0f;
	sc.g -= 70.0f;
	sc.b -= 70.0f;
	this->m_selectorSprite.setColor(sc);
}

void Publisher::Update(float deltaTime, bool notified, sf::Vector2f mousePos)
{
	for (auto element : this->m_elements)
	{
		element->Update(deltaTime, notified, mousePos);
	}
}

void Publisher::Render(sf::RenderWindow* window)
{
	for (auto element : this->m_elements)
	{
		element->Render(window);
	}
}
