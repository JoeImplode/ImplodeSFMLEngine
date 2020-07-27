#include "pch.h"
#include "UIElement.h"

UIElement::UIElement(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale)
{
	//when we construct a UI element, we want to set all the params which will be in each UI element
	this->m_label.setString(text);
	this->m_labelRelativePosition = textPos;
	this->m_label.setPosition(elementPos.x + this->m_labelRelativePosition.x, elementPos.y + this->m_labelRelativePosition.y);
	this->m_position = elementPos;
	this->m_scale = scale;
}

Button::Button(bool& reference) : m_boolRef(reference)
{
}

Button::Button(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, bool & reference, bool valToSet) : UIElement(text,textPos,elementPos,scale),m_boolRef(reference),m_valToSet(valToSet)
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
	if (mousePos.x >= this->m_position.x && mousePos.x <= this->m_position.x + this->m_buttonSprite.getLocalBounds().width *this->m_scale.x
		&& mousePos.y >= this->m_position.y && mousePos.y <= this->m_position.y + this->m_buttonSprite.getLocalBounds().height * this->m_scale.y)
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
	window->draw(this->m_buttonSprite);
	window->draw(this->m_buttonText);
	window->draw(this->m_label);
}

void Button::Selected()
{
	sf::Color c = this->m_buttonSprite.getColor();
	c.r -= 70.0f;
	c.g -= 70.0f;
	c.b -= 70.0f;
	this->m_buttonSprite.setColor(c);
}

void Button::SetButtonText(sf::Text textExample)
{
	this->m_buttonText = textExample;
}

Slider::Slider(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, float& reference) : UIElement(text,textPos,elementPos,scale),m_floatRef(reference),m_selectorScale(selectorScale)
{
}

void Slider::SetTextures(sf::Texture &barTexture, sf::Texture &selectorTexture)
{
	this->m_barSprite.setTexture(barTexture);
	this->m_barSprite.setScale(this->m_scale);
	this->m_barSprite.setPosition(this->m_position);
	this->m_initialBarColour = this->m_barSprite.getColor();

	this->m_selectorSprite.setTexture(selectorTexture);
	this->m_selectorSprite.setScale(this->m_selectorScale);
	this->m_selectorSprite.setPosition(sf::Vector2f(this->m_barSprite.getPosition().x, this->m_barSprite.getPosition().y));
	this->m_initialSliderColour = this->m_selectorSprite.getColor();
}

void Slider::Update(float deltaTime,bool notified,sf::Vector2f mousePos)
{
	/*
	- Quite messy code but is working as expected
	- Essentially, the slider value is calculated based on how much of the slider has reached the end
	- It's dynamic as the slider can be any width and the calculated float will always remain between 0 and 1
	- There is some duplication yet this is to ensure an ease of use for the bar since if we click the bar but at the end, we want to force the slider to the end of the bar
	*/

	if (mousePos.x >= this->m_barSprite.getPosition().x				//calculate if we get the position within the bounds but not at the end of the button
		&& mousePos.x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x)
		&& mousePos.y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& mousePos.y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initialBarColour)
			this->Selected();
		if (notified)
		{
			this->m_selectorSprite.setPosition(sf::Vector2f(mousePos.x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
	}
	else if (mousePos.x >= this->m_barSprite.getPosition().x			//Calculate if we get the position within the bounds but at the end
		&& mousePos.x >= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x)
		&& mousePos.x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x
		&& mousePos.y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& mousePos.y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initialBarColour)
			this->Selected();
		if (notified)
		{
			this->m_selectorSprite.setPosition(this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x), this->m_barSprite.getPosition().y);
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
	//take the width of the slider bar and calculate how much distance was traveled as a percentage

	float width = this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x);
	this->m_floatRef = (this->m_selectorSprite.getPosition().x - this->m_barSprite.getPosition().x)/width ; //here we're getting the percentage of the scale passed, so if we're at 200, and the scale is 400, we'll get 0.5
	std::cout << "Float val: " << this->m_floatRef << std::endl;
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

ButtonGroup::ButtonGroup(std::string text, sf::Vector2f textPos, sf::Vector2f elementPos, sf::Vector2f scale, float orientation, bool& reference,sf::Texture& borderTexture)
	: UIElement(text, textPos, elementPos, scale),m_orientation(orientation),m_boolRef(reference)
{
	this->m_border.setTexture(&borderTexture);
	this->m_border.setPosition(elementPos);
	this->m_border.setSize(sf::Vector2f(scale.x * borderTexture.getSize().x, scale.y * borderTexture.getSize().y));
}

void ButtonGroup::Update(float deltaTime, bool notified, sf::Vector2f mousePos)
{
	this->m_leftButton->Update(deltaTime, notified, mousePos);
	this->m_rightButton->Update(deltaTime, notified, mousePos);
}

void ButtonGroup::Render(sf::RenderWindow* window)
{
	window->draw(this->m_border);
	this->m_leftButton->Render(window);
	this->m_rightButton->Render(window);
}

void ButtonGroup::SetButtons(Button *leftButton, Button *rightButton)
{
	float totalWidth = (this->m_border.getLocalBounds().width ) - ((this->m_border.getLocalBounds().width) / 8); //we want to get a slight offset for the button height requirements so we have space
	float totalHeight = (this->m_border.getLocalBounds().height  ) - ((this->m_border.getLocalBounds().height ) / 8);

	std::cout << totalWidth << std::endl;
	std::cout << totalHeight << std::endl;

	if (m_orientation && leftButton->GetWidth() < totalWidth / 2 && rightButton->GetWidth() < totalWidth / 2
		&& leftButton->GetHeight() < totalHeight && rightButton->GetHeight() < totalHeight)
	{
		this->m_leftButton = leftButton;
		this->m_leftButton->SetBoolRef(this->m_boolRef);
		this->m_leftButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width) / 8,
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 2) - (leftButton->GetHeight())));
		this->m_leftButton->UpdateLabel(this->m_leftButton->GetPosition());

		this->m_rightButton = rightButton;
		this->m_rightButton->SetBoolRef(this->m_boolRef);
		this->m_rightButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width / 2) + ((this->m_border.getLocalBounds().width) / 8),
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 2) - (rightButton->GetHeight())));
		this->m_rightButton->UpdateLabel(this->m_rightButton->GetPosition());
	}

	else if (!m_orientation && leftButton->GetHeight() < totalHeight / 2 && rightButton->GetHeight() < totalHeight / 2
		&& leftButton->GetWidth() < totalWidth && rightButton->GetWidth() < totalWidth)
	{
		this->m_leftButton = leftButton;
		this->m_leftButton->SetBoolRef(this->m_boolRef);
		this->m_leftButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width ) / 8,
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 8)));
		this->m_leftButton->UpdateLabel(this->m_leftButton->GetPosition());

		this->m_rightButton = rightButton;
		this->m_rightButton->SetBoolRef(this->m_boolRef);
		this->m_rightButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width) / 8,
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 2) + ((this->m_border.getLocalBounds().height) / 8)));
		this->m_rightButton->UpdateLabel(this->m_rightButton->GetPosition());
	}

	else
	{
		std::cout << "ERROR: The bounds you provided for the button box are too small for the button scales!" << std::endl;
		std::cout << "-----: Try to change the orientation, resize the border or change the button sizes!" << std::endl;
	}
}