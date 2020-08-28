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

void Button::Update(float deltaTime)
{

}

void Button::Render(sf::RenderWindow* window)
{
	window->draw(this->m_buttonSprite);
	window->draw(this->m_buttonText);
	window->draw(this->m_label);
}

void Button::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (sf::Mouse::getPosition(*window).x >= this->m_position.x && sf::Mouse::getPosition(*window).x <= this->m_position.x + this->m_buttonSprite.getLocalBounds().width * this->m_scale.x
		&& sf::Mouse::getPosition(*window).y >= this->m_position.y && sf::Mouse::getPosition(*window).y <= this->m_position.y + this->m_buttonSprite.getLocalBounds().height * this->m_scale.y)
	{
		if (this->m_buttonSprite.getColor() == this->m_initialColor)
			this->Selected();
		if (e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
			this->Notify();
	}
	else if (this->m_buttonSprite.getColor() != this->m_initialColor)
		this->m_buttonSprite.setColor(this->m_initialColor);
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

void Slider::Update(float deltaTime)
{

}

void Slider::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (m_dragging && e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
		m_dragging = false;
	if (sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x				//calculate if we get the position within the bounds but not at the end of the button
		&&sf::Mouse::getPosition(*window).x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x)
		&& sf::Mouse::getPosition(*window).y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& sf::Mouse::getPosition(*window).y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initialBarColour)
			this->Selected();
		if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && !m_dragging)
		{
			this->m_selectorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
			m_dragging = true;
		}
		else if (e.type == sf::Event::MouseMoved && m_dragging)
		{
			this->m_selectorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
		else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && m_dragging)
			m_dragging = false;
	}
	else if (sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x			//Calculate if we get the position within the bounds but at the end
		&& sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x)
		&& sf::Mouse::getPosition(*window).x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x
		&& sf::Mouse::getPosition(*window).y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& sf::Mouse::getPosition(*window).y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initialBarColour)
			this->Selected();
		if (e.type == e.MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && !m_dragging)
		{
			this->m_selectorSprite.setPosition(this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprite.getLocalBounds().width * this->m_selectorScale.x), this->m_barSprite.getPosition().y);
			this->Notify();
			m_dragging = true;
		}
		else if (e.MouseMoved && m_dragging)
		{
			this->m_selectorSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
		else if (e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && m_dragging)
			m_dragging = false;
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

void Publisher::Update(float deltaTime)
{
	for (auto element : this->m_elements)
	{
		if (element->GetActivated())
			element->Update(deltaTime);
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

void Publisher::ProcessInput(sf::Event& event,sf::RenderWindow * window)
{
	for (auto element : this->m_elements)
		if (element->GetActivated())
			element->ProcessInput(event,window);
}

ButtonGroup::ButtonGroup(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool orientation, bool& reference,sf::Texture& borderTexture, bool activated)
	: UIElement(text, elementPos, scale,activated),m_orientation(orientation),m_boolRef(reference)
{
	this->m_type = "ButtonGroup";
	this->m_border.setTexture(&borderTexture);
	this->m_border.setPosition(elementPos);
	this->m_border.setSize(sf::Vector2f(scale.x * borderTexture.getSize().x, scale.y * borderTexture.getSize().y));
}

void ButtonGroup::Update(float deltaTime)
{
	
}

void ButtonGroup::Render(sf::RenderWindow* window)
{
	window->draw(this->m_border);
	this->m_leftButton->Render(window);
	this->m_rightButton->Render(window);
	window->draw(this->m_label);
}

void ButtonGroup::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	this->m_leftButton->ProcessInput(e, window);
	this->m_rightButton->ProcessInput(e, window);
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

void Widget::Update(float deltaTime)
{
	for (auto element : this->m_elements)
		if (element->GetActivated())
			element->Update(deltaTime);
}

void Widget::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	for (auto element : this->m_elements)
		if (element->GetActivated())
			element->ProcessInput(e, window);
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

void DropDown::Update(float deltaTime)
{
	
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

void DropDown::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	this->m_activatorButton->ProcessInput(e,window);
	if (this->m_dropDownShowing)
	{
		for (int i = 0; i < this->m_buttons.size(); i++)
			this->m_buttons[i]->ProcessInput(e, window);
		this->m_activatorButton->SetValToSet(false);
	}
	if (!this->m_dropDownShowing && !this->m_activatorButton->GetValToSet())
		this->m_activatorButton->SetValToSet(true);
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

TextInput::TextInput(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& buttonTexture, sf::Texture& textBoxTexture, sf::Vector2f buttonScale,
	std::string& stringToSet, int characterLimit, std::string buttonLabel, bool activated,sf::Font & font,std::string buttonText, sf::Color textColor, sf::Color outlineColor, int outlineThickness) : UIElement(text, elementPos, scale, activated), m_characterLimit(characterLimit), m_string(stringToSet),m_outlineThickness(outlineThickness)
{
	this->m_type = "TextInput";
	this->m_textBoxTexture.setTexture(&textBoxTexture);
	this->m_textBoxTexture.setPosition(elementPos);
	this->m_textBoxTexture.setSize(sf::Vector2f(scale.x * textBoxTexture.getSize().x, scale.y * textBoxTexture.getSize().y));

	this->m_inputText.setFont(font);
	this->m_inputText.setCharacterSize(scale.y * textBoxTexture.getSize().y / 2);
	this->m_inputText.setPosition(elementPos.x,elementPos.y + ((scale.y * textBoxTexture.getSize().y) / 2) - ((scale.y * textBoxTexture.getSize().y / 2)/2));
	this->m_inputText.setFillColor(textColor);
	
	float width = this->m_textBoxTexture.getLocalBounds().width * this->m_scale.x;
	float endPos = textBoxTexture.getSize().x + width;

	this->m_sendButton = new Button("", sf::Vector2f(endPos + (width / 20), this->m_textBoxTexture.getPosition().y), buttonScale, this->m_sendPressed, true, true);
	this->m_sendButton->SetTexture(buttonTexture);
	this->m_sendButton->SetButtonText(this->m_inputText);
	this->m_sendButton->m_buttonText.setCharacterSize(this->m_sendButton->GetHeight() / 2);
	this->m_sendButton->m_buttonText.setFillColor(textColor);
	this->m_sendButton->m_buttonText.setString(buttonText);	
	this->m_sendButton->m_buttonText.setPosition(sf::Vector2f(this->m_sendButton->GetPosition().x + ((this->m_sendButton->GetWidth() / 2) - (this->m_sendButton->m_buttonText.getLocalBounds().width/2)),
		this->m_sendButton->GetPosition().y + ((this->m_sendButton->GetHeight() / 2) - (this->m_sendButton->GetHeight() / 2)/2)));
	this->m_textBoxTexture.setOutlineColor(outlineColor);
	this->m_placement = 0;
}

void TextInput::Update(float deltaTime)
{
	if (this->m_sendPressed && this->m_textString.size() > 0)
	{
		this->m_string = this->m_textString;
		this->m_inputText.setString("");
		this->m_caretVal = "";
		this->m_textString = "";
		this->m_sendPressed = false;
	}
	else
		m_sendPressed = false;

	if (this->m_caretVal == "" && this->m_timer.getElapsedTime().asSeconds() > 0.5 && this->m_focused)
	{
		this->m_caretVal = "|";
		this->m_inputText.setString(this->m_textString + "|");
		this->m_timer.restart();
	}
	if (this->m_caretVal == "|" && this->m_timer.getElapsedTime().asSeconds() > 0.5 && this->m_focused)
	{
		this->m_inputText.setString(this->m_textString);
		this->m_caretVal = "";
		this->m_timer.restart();
	}
	if (!m_focused)
	{
		std::string s;
		if (this->m_caretVal == "|")
			s = std::string(this->m_inputText.getString().begin(), this->m_inputText.getString().end() - 1);
		else if (this->m_caretVal == "")
			s = std::string(this->m_inputText.getString());
		this->m_inputText.setString(s);
		this->m_caretVal = "";
	}
	
}

void TextInput::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(*window).x < this->m_textBoxTexture.getPosition().x + (this->m_textBoxTexture.getLocalBounds().width)
		&& sf::Mouse::getPosition(*window).x > this->m_textBoxTexture.getPosition().x && sf::Mouse::getPosition(*window).y > this->m_textBoxTexture.getPosition().y
		&& sf::Mouse::getPosition(*window).y < this->m_textBoxTexture.getPosition().y + this->m_textBoxTexture.getLocalBounds().height)
	{
		this->m_textBoxTexture.setOutlineThickness(this->m_outlineThickness);
		if (!this->m_focused && !m_wasFocused)
			this->m_focused = true;
		else if (this->m_focused && m_wasFocused)
			this->m_focused = false;
	}
	else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
	{
		this->m_textBoxTexture.setOutlineThickness(0);
		this->m_focused = false;
	}

	if (this->m_focused)
	{
		if (e.type == sf::Event::TextEntered)
			if (e.text.unicode < 128)
				this->UpdateTextBox(e.text.unicode);
	}
	this->m_sendButton->ProcessInput(e, window);
}

void TextInput::UpdateTextBox(int charTyped)
{
	if (charTyped != DELETE_KEY && this->m_textString.length() < this->m_characterLimit)
		this->m_textString += static_cast<char>(charTyped);

	else if (charTyped == DELETE_KEY && this->m_textString.size() > 0)
		DeleteLastChar();

	this->m_inputText.setString(this->m_textString);
}

void TextInput::DeleteLastChar()
{
	std::string t = this->m_textString;
	std::string newTxtString = "";

	for (int i = 0; i < t.length() - 1; i++)
		newTxtString += t[i];

	this->m_textString = "";
	this->m_textString = newTxtString;
}

void TextInput::Render(sf::RenderWindow* window)
{
	window->draw(this->m_textBoxTexture);
	window->draw(this->m_inputText);
	this->m_sendButton->Render(window);
}

void TextInput::UpdatePosition(sf::Vector2f position)
{
	sf::Vector2f relativeButtonPos = sf::Vector2f(this->m_sendButton->GetPosition().x - this->GetOrigin().x, this->m_sendButton->GetPosition().y - this->GetOrigin().y);
	sf::Vector2f relativeTextPos = sf::Vector2f(this->m_inputText.getPosition().x - this->GetOrigin().x, this->m_inputText.getPosition().y - this->GetOrigin().y);

	this->m_textBoxTexture.setPosition(position);

	this->m_sendButton->UpdatePosition(sf::Vector2f(relativeButtonPos.x + this->GetOrigin().x, relativeButtonPos.y + this->GetOrigin().y));
	this->m_inputText.setPosition(sf::Vector2f(this->GetOrigin().x + relativeTextPos.x, this->GetOrigin().y + relativeTextPos.y));
}

TextLog::TextLog(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& textLogtexture, sf::Font& textFont, sf::Color textColor, int charSize, bool activated, int textObjLim) : UIElement(text, elementPos, scale, activated)
{
	this->m_type = "TextLog";
	this->m_textLogTexture.setTexture(&textLogtexture);
	this->m_textLogTexture.setPosition(sf::Vector2f(0.0f,0.0f));
	this->m_textLogTexture.setSize(sf::Vector2f(scale.x * textLogtexture.getSize().x, scale.y * textLogtexture.getSize().y));

	this->m_rect = new sf::RectangleShape(sf::Vector2f(100, 100));
	this->m_rect->setFillColor(sf::Color::Blue);
	//this->m_rect->setPosition(sf::Vector2f(0.0f, 0.0f));

	this->m_text.setFont(textFont);
	this->m_text.setCharacterSize(20);
	this->m_text.setPosition(sf::Vector2f(0, 0));
	this->m_text.setFillColor(textColor);
	this->m_text.setString("This is text for a text box!\nAs you can see, the text only stays within\nthe bounds!\nThere are also new lines in this text to\nstart new lines!\nYou'll notice if I keep typing, then the text\ngoes out of bounds\n @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

	this->m_sprite.setPosition(elementPos);

	this->m_textObjLim = textObjLim;

	this->m_renderTexture.create(this->m_textLogTexture.getLocalBounds().width, this->m_textLogTexture.getLocalBounds().height);

}

void TextLog::AddText(sf::Text text)
{
	sf::Text txt = text;
	sf::Text placeHolderText = text;
	txt.setFont(*this->m_text.getFont());
	txt.setCharacterSize(this->m_text.getCharacterSize());
	std::string finalString;
	std::string finalText;
	if (txt.getLocalBounds().width > this->m_textLogTexture.getLocalBounds().width)
	{
		while (true)
		{
			if (placeHolderText.getLocalBounds().width > this->m_textLogTexture.getLocalBounds().width)
			{
				int widthPerChar = placeHolderText.getLocalBounds().width / placeHolderText.getString().getSize();
				int charsToAdd = this->m_textLogTexture.getLocalBounds().width / widthPerChar;
				std::string addStr = std::string(placeHolderText.getString().begin(), placeHolderText.getString().end() - charsToAdd);
				placeHolderText.setString(addStr);
				addStr += "\n";
				finalString += addStr;
			}
			else
			{
				finalString += "\n";
				finalString += placeHolderText.getString();
				break;
			}
		}
		txt.setString(finalString);
	}
	else
		txt.setString(text.getString());
	
	if (this->m_textList.size() <= this->m_textObjLim)
	{
		this->m_textList.push_back(txt);
	}
	if (this->m_textList.size() > this->m_textObjLim)
	{
		for (int i = this->m_textObjLim; i > 0; i--)
		{
			this->m_textList[i-1] = this->m_textList[i];
		}
		this->m_textList.push_back(txt);
	}
	if (this->m_textList.size() == 1)
		//this->m_textList[0].setPosition(0.0f,0.0f);
		
	for (int i = 0; i < this->m_textList.size(); i++)
	{
		//bottom y position
		//x position is the same

	}
	
}

void TextLog::Update(float deltaTime)
{
}

void TextLog::Render(sf::RenderWindow* window)
{
	sf::RectangleShape r;
	r.setPosition(sf::Vector2f(0.0f,0.0f));
	r.setTexture(this->m_textLogTexture.getTexture());
	//r.setFillColor(sf::Color::White);
	r.setSize(this->m_textLogTexture.getSize());

	this->m_renderTexture.clear();
	this->m_renderTexture.draw(r);
	this->m_renderTexture.draw(this->m_text);
	this->m_renderTexture.display();
	this->m_sprite.setTexture(this->m_renderTexture.getTexture());

	if (this->m_textList.size() > 0)
	{
		if (this->m_textList.size() < 2)
		{
			
		}
		
		else if (this->m_textList.size() > 2)
		{
			for (int i = this->m_textObjLim; i > 0; i--)
			{
				this->m_renderTexture.draw(this->m_textList[i]);
			}
		}
	}
	
	//m_sprite.setPosition(200.0f, 200.0f);
	this->m_textLogTexture.setPosition(this->m_sprite.getPosition());
	window->draw(this->m_sprite);
	//window->draw(this->m_textLogTexture);
	
	//window->draw(this->m_text);

}

void TextLog::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{

}

void TextLog::UpdatePosition(sf::Vector2f newPos)
{

}

std::string TextLog::FormatStrings(std::string s1, std::string s2)
{

	return std::string();
}
