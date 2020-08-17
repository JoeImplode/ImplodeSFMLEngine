#include "pch.h"
#include "UIElement.h"

UIElement::UIElement(std::string text,sf::Vector2f elementPos, sf::Vector2f scale,bool activated)
{
	this->m_label.setString(text);
	this->m_position = elementPos;
	this->m_scale = scale;
	this->m_activated = activated;
}

Button::Button(bool& reference) : m_boolRef(reference)
{

}

Button::Button(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, bool & reference, bool valToSet, bool activated) : UIElement(text,elementPos,scale,activated),m_boolRef(reference),m_valToSet(valToSet)
{
	this->m_type = "Button";
}

void Button::SetTexture(sf::Texture& texture)
{
	this->m_buttonSprite.setTexture(texture);
	this->m_buttonSprite.setScale(this->m_scale);
	this->m_buttonSprite.setPosition(this->m_position);
	this->m_initialColor = this->m_buttonSprite.getColor();
	
}

void Button::UpdatePosition(sf::Vector2f position)
{
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);
	sf::Vector2f relativeButtonTextPos = sf::Vector2f(this->m_buttonText.getPosition().x - GetOrigin().x, this->m_buttonText.getPosition().y - GetOrigin().y);
	this->m_position = position;
	this->m_buttonSprite.setPosition(position);
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + relativeLabelPos.x, GetOrigin().y + relativeLabelPos.y));
	this->m_buttonText.setPosition(sf::Vector2f(relativeButtonTextPos.x + GetOrigin().x, relativeButtonTextPos.y + GetOrigin().y));
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

Slider::Slider(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, float& reference, bool activated) : UIElement(text,elementPos,scale,activated),m_floatRef(reference),m_selectorScale(selectorScale)
{
	this->m_type = "Slider";
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
	this->m_floatRef = (this->m_selectorSprite.getPosition().x - this->m_barSprite.getPosition().x)/width ; 
}

void Slider::UpdatePosition(sf::Vector2f position)
{
	sf::Vector2f labelRelativePos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);
	sf::Vector2f barSpriteRelativePos = sf::Vector2f(this->m_barSprite.getPosition().x - GetOrigin().x, this->m_barSprite.getPosition().y - GetOrigin().y);
	sf::Vector2f sliderSpriteRelativePos = sf::Vector2f(this->m_selectorSprite.getPosition().x - GetOrigin().x, this->m_selectorSprite.getPosition().y - GetOrigin().y);

	this->m_position = position;
	this->m_barSprite.setPosition(sf::Vector2f(GetOrigin().x + barSpriteRelativePos.x,GetOrigin().y + barSpriteRelativePos.y));
	this->m_selectorSprite.setPosition(sf::Vector2f(GetOrigin().x + sliderSpriteRelativePos.x, GetOrigin().y +sliderSpriteRelativePos.y));
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

void Publisher::Update(float deltaTime, bool notified, bool dragged,sf::Vector2f mousePos)
{
	if (!dragged)
	{
		for (int i = 0; i < this->m_elements.size(); i++)
		{
			if (this->m_elements[i]->GetActivated())
			{
				if (this->m_elements[i]->GetType() == "Slider")
				{
					this->m_elements[i]->Update(deltaTime, false, mousePos);
				}
				if (this->m_elements[i]->GetType() == "Widget")
				{
					Widget* tempWgt;
					tempWgt = dynamic_cast <Widget*>(this->m_elements[i]);
					tempWgt->Update(deltaTime, dragged, notified, mousePos);
				}
				else
					this->m_elements[i]->Update(deltaTime, notified, mousePos);
			}
		}
	}

	else if (dragged)
	{
		for (int i = 0; i < this->m_elements.size(); i++)
		{
			if (this->m_elements[i]->GetActivated())
			{
				if (this->m_elements[i]->GetType() == "Slider")
				{
					this->m_elements[i]->Update(deltaTime, notified, mousePos);
				}
				if (this->m_elements[i]->GetType() == "Widget")
				{
					Widget* tempWgt;
					tempWgt = dynamic_cast <Widget*>(this->m_elements[i]);
					tempWgt->Update(deltaTime, dragged, notified, mousePos);
				}
			}

		}
	}
}

void Publisher::Render(sf::RenderWindow* window)
{
	for (auto element : this->m_elements)
	{
		if(element->GetActivated())
			element->Render(window);
	}
}

ButtonGroup::ButtonGroup(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool orientation, bool& reference,sf::Texture& borderTexture, bool activated)
	: UIElement(text, elementPos, scale,activated),m_orientation(orientation),m_boolRef(reference)
{
	this->m_type = "ButtonGroup";
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
	window->draw(this->m_label);
}

void ButtonGroup::SetButtons(sf::Texture& leftTexture,sf::Vector2f scaleLeft, sf::Texture& rightTexture, sf::Vector2f scaleRight)
{
	//construct the left and the right button here
	this->m_leftButton = new Button("", sf::Vector2f(0, 0), scaleLeft, this->m_boolRef, true);
	this->m_rightButton = new Button("", sf::Vector2f(0, 0), scaleRight, this->m_boolRef, false);

	float leftW = (leftTexture.getSize().x * scaleLeft.x);
	float rightW = (rightTexture.getSize().x * scaleRight.x);

	float leftH = (leftTexture.getSize().y * scaleLeft.y);
	float rightH = (rightTexture.getSize().y * scaleRight.y);
	
	if (m_orientation)
	{
		this->m_leftButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width) / 8,
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 2) - (leftH / 2)));
		this->m_leftButton->SetTexture(leftTexture);

		this->m_rightButton->SetPos(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width - (this->m_border.getLocalBounds().width / 8) - rightW),
			this->m_position.y + ((this->m_border.getLocalBounds().height) / 2) - (rightH /2)));
		this->m_rightButton->SetTexture(rightTexture);
	}

	else if (!m_orientation )
	{
		this->m_leftButton->SetPos(sf::Vector2f((this->m_position.x + (this->m_border.getLocalBounds().width) / 2) - (leftW / 2),
			this->m_position.y + (this->m_border.getLocalBounds().height) / 8));
		this->m_leftButton->SetTexture(leftTexture);

		this->m_rightButton->SetPos(sf::Vector2f((this->m_position.x + (this->m_border.getLocalBounds().width) / 2) - (rightW /2),
			this->m_position.y + (this->m_border.getLocalBounds().height - (this->m_border.getLocalBounds().height/8) - rightH)));
		this->m_rightButton->SetTexture(rightTexture);
	}
}

void ButtonGroup::UpdatePosition(sf::Vector2f position)
{
	sf::Vector2f relativeLeftButtonPos = sf::Vector2f(this->m_leftButton->GetPosition().x - GetOrigin().x, this->m_leftButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeRightButtonPos = sf::Vector2f(this->m_rightButton->GetPosition().x - GetOrigin().x, this->m_rightButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);

	this->m_position = position;
	this->m_leftButton->UpdatePosition(sf::Vector2f(relativeLeftButtonPos.x + GetOrigin().x,GetOrigin().y + relativeLeftButtonPos.y));
	this->m_rightButton->UpdatePosition(sf::Vector2f(GetOrigin().x + relativeRightButtonPos.x, GetOrigin().y + relativeRightButtonPos.y));
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + relativeLabelPos.x, GetOrigin().y + relativeLabelPos.y));
	this->m_border.setPosition(position);
}

Widget::Widget(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& widgetTexture, bool activated) : UIElement(text, elementPos, scale,activated)
{
	this->m_type = "Widget";
	this->m_border.setTexture(&widgetTexture);
	this->m_border.setPosition(elementPos);
	this->m_border.setSize(sf::Vector2f(scale.x * widgetTexture.getSize().x, scale.y * widgetTexture.getSize().y));
}

void Widget::Update(float deltaTime, bool dragged,bool notified, sf::Vector2f mousePos)
{
	if (!dragged)
	{
		for (int i = 0; i < this->m_elements.size(); i++)
		{
			if (this->m_elements[i]->GetActivated())
			{
				if (this->m_elements[i]->GetType() == "Slider")
				{
					this->m_elements[i]->Update(deltaTime, false, mousePos);
				}
				if (this->m_elements[i]->GetType() == "Widget")
				{
					Widget* tempWgt;
					tempWgt = dynamic_cast <Widget*>(this->m_elements[i]);
					tempWgt->Update(deltaTime, dragged, false, mousePos);
				}
				else
					this->m_elements[i]->Update(deltaTime, notified, mousePos);
			}
		}
	}

	else if (dragged)
	{
		for (int i = 0; i < this->m_elements.size(); i++)
		{
			if (this->m_elements[i]->GetActivated())
			{
				if (this->m_elements[i]->GetType() == "Slider")
				{
					this->m_elements[i]->Update(deltaTime, notified, mousePos);
				}
				if (this->m_elements[i]->GetType() == "Widget")
				{
					Widget* tempWgt;
					tempWgt = dynamic_cast <Widget*>(this->m_elements[i]);
					tempWgt->Update(deltaTime, dragged, notified, mousePos);
				}
			}

		}
	}
}

void Widget::Render(sf::RenderWindow* window)
{
	window->draw(this->m_border);
	window->draw(this->m_label);
	for (auto element : this->m_elements)
	{
		if(element->GetActivated())
			element->Render(window);
	}
}

void Widget::AddElement(UIElement* element, sf::Vector2f percentagePos)
{
	if (percentagePos.x < 0 || percentagePos.x > 1 || percentagePos.y < 0 || percentagePos.y > 1)
	{
		std::cout << "Error, please provide floats from 0-1 so 80% = 0.8!" << std::endl;
		return;
	}
	element->UpdatePosition(sf::Vector2f(this->m_position.x + (this->m_border.getLocalBounds().width * percentagePos.x), this->m_position.y + (this->m_border.getLocalBounds().height * percentagePos.y)));
	this->m_elements.push_back(element);
}

DropDown::DropDown(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Text buttonText, sf::Texture & buttonTexture, bool& reference, bool activated) : UIElement(text, elementPos, scale,activated)
{
	this->m_type = "DropDown";
	this->m_activatorButton = new Button("", elementPos, scale, this->m_dropDownShowing, true);
	this->m_activatorButton->SetTexture(buttonTexture);
	this->m_activatorButton->m_buttonText = buttonText;
	this->m_activatorButton->m_buttonText.setCharacterSize(this->m_activatorButton->GetHeight() / 2);
	this->m_activatorButton->m_buttonText.setPosition(sf::Vector2f((this->m_activatorButton->GetPosition().x + (this->m_activatorButton->GetWidth() / 2)) - (this->m_activatorButton->m_buttonText.getLocalBounds().width/2),
		(this->m_activatorButton->GetPosition().y + (this->m_activatorButton->GetHeight() / 2)) - (this->m_activatorButton->m_buttonText.getLocalBounds().height /2)));
}

void DropDown::Update(float deltaTime, bool notified, sf::Vector2f mousePos)
{
	this->m_activatorButton->Update(deltaTime, notified, mousePos);
	if (this->m_dropDownShowing)
	{
		for (int i = 0; i < this->m_buttons.size(); i++)
			this->m_buttons[i]->Update(deltaTime, notified, mousePos);
		this->m_activatorButton->SetValToSet(false);
	}
	if (!this->m_dropDownShowing && !this->m_activatorButton->GetValToSet())
		this->m_activatorButton->SetValToSet(true);
}

void DropDown::Render(sf::RenderWindow* window)
{
	this->m_activatorButton->Render(window);
	if (this->m_dropDownShowing)
	{
		for (int i = 0; i < this->m_buttons.size(); i++)
			this->m_buttons[i]->Render(window);
	}
}

void DropDown::AddSelection(sf::Text buttonText, std::string textString, sf::Texture& buttonTexture, sf::Vector2f buttonScale, bool & reference)
{
	Button * btn = new Button("", sf::Vector2f(0, 0), buttonScale, reference,true,false);
	btn->SetPos(sf::Vector2f(this->m_activatorButton->GetPosition().x, this->m_activatorButton->GetPosition().y + (this->m_activatorButton->GetHeight() * (this->m_buttons.size()+1))));
	btn->m_buttonText = buttonText;
	btn->m_buttonText.setString(textString);
	btn->SetTexture(buttonTexture);
	btn->m_buttonText.setCharacterSize(this->m_activatorButton->GetHeight() / 2);
	btn->m_buttonText.setPosition(sf::Vector2f((btn->GetPosition().x + (btn->GetWidth()/2)) - (btn->m_buttonText.getLocalBounds().width / 2), (btn->GetPosition().y + (btn->GetHeight() / 2)) - (btn->m_buttonText.getLocalBounds().height/2)));
	this->m_buttons.push_back(new Button(*btn));
}

void DropDown::UpdatePosition(sf::Vector2f position)
{
	sf::Vector2f relativeActivatorButtonPos = sf::Vector2f(this->m_activatorButton->GetPosition().x - GetOrigin().x, this->m_activatorButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);

	this->m_position = position;
	this->m_activatorButton->UpdatePosition(sf::Vector2f(relativeActivatorButtonPos.x + GetOrigin().x, GetOrigin().y + relativeActivatorButtonPos.y));
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + relativeLabelPos.x, GetOrigin().y + relativeLabelPos.y));
	for (int i = 0; i < this->m_buttons.size(); i++)
	{
		this->m_buttons[i]->UpdatePosition(sf::Vector2f(position.x, position.y + (this->m_activatorButton->GetHeight() * (i+1))));
	}
	this->m_activatorButton->UpdatePosition(position);
}

TextInput::TextInput(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& buttonTexture, sf::Texture& textBoxTexture, sf::Vector2f buttonScale,
	std::string& stringToSet, int characterLimit, int scrollableLimit, std::string buttonLabel, bool activated, sf::Event & event,sf::RenderWindow & window,sf::Font & font) : UIElement(text, elementPos, scale, activated), m_characterLimit(characterLimit), m_scrollableLimit(scrollableLimit), m_string(stringToSet),m_event(event),m_renderWindow(window)
{
	this->m_type = "TextInput";
	this->m_textBoxTexture.setTexture(&textBoxTexture);
	this->m_textBoxTexture.setPosition(elementPos);
	this->m_textBoxTexture.setSize(sf::Vector2f(scale.x * textBoxTexture.getSize().x, scale.y * textBoxTexture.getSize().y));

	this->m_inputText.setFont(font);
	this->m_inputText.setCharacterSize(scale.y * textBoxTexture.getSize().y / 2);
	this->m_inputText.setPosition(elementPos.x,elementPos.y + ((scale.y * textBoxTexture.getSize().y) / 2) - ((scale.y * textBoxTexture.getSize().y / 2)/2));
	this->m_inputText.setFillColor(sf::Color::Black);
	
	float width = this->m_textBoxTexture.getLocalBounds().width * this->m_scale.x;
	float endPos = textBoxTexture.getSize().x + width;

	this->m_sendButton = new Button(buttonLabel, sf::Vector2f(endPos + (width / 8), this->m_textBoxTexture.getPosition().y), buttonScale, this->m_sendPressed, true, true);
	this->m_sendButton->SetTexture(buttonTexture);
}

void TextInput::Update(float deltaTime, bool notified, sf::Vector2f mousePos)
{
	//check if the mouse is clicked within the rect bounds
	//change focused to true if set to false then clicked, otherwise set to false if clicked off
	//if typing during focused, we just update the text that is being inputted until if the character length is not what we set it as
	//if send is clicked, we call the send function, wipe the text

	if (notified && mousePos.x < this->m_textBoxTexture.getPosition().x + (this->m_textBoxTexture.getLocalBounds().width)
		&& mousePos.x > this->m_textBoxTexture.getPosition().x && mousePos.y > this->m_textBoxTexture.getPosition().y
		&& mousePos.y < this->m_textBoxTexture.getPosition().y + this->m_textBoxTexture.getLocalBounds().height)
	{
		if (!this->m_focused && !m_wasFocused)
			this->m_focused = true;
		else if (this->m_focused && m_wasFocused)
			this->m_focused = false;
	}
	else if (notified)
		this->m_focused = false;

	if (this->m_focused)
	{
		while (this->m_renderWindow.pollEvent(this->m_event))
		{
			if (this->m_event.TextEntered)
				if (this->m_event.text.unicode >= 33 && this->m_event.text.unicode < 128)
					this->UpdateTextBox(this->m_event.text.unicode);
		}
	}
	this->m_sendButton->Update(deltaTime, notified, mousePos);
}

void TextInput::UpdateTextBox(int charTyped)
{
	if (charTyped != DELETE_KEY)
		this->m_textString << static_cast<char>(charTyped);

	else if (charTyped == DELETE_KEY)
		if (this->m_textString.str().length() > 0)
			DeleteLastChar();

	this->m_inputText.setString(this->m_textString.str() + "_");
}

void TextInput::DeleteLastChar()
{
	std::string t = this->m_textString.str();
	std::string newTxtString = "";

	for (int i = 0; i < t.length(); i++)
		newTxtString += t[i];

	this->m_textString.str("");
	this->m_textString << newTxtString;
}

void TextInput::Render(sf::RenderWindow* window)
{
	window->draw(this->m_textBoxTexture);
	window->draw(this->m_inputText);
	this->m_sendButton->Render(window);
}

void TextInput::UpdatePosition(sf::Vector2f position)
{
}
