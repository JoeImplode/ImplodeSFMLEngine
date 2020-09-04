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
		if (this->m_buttonSprite.getColor() == this->m_initialColor && this->m_effectsShowing)
			this->Selected();
		if (e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
			this->Notify();
	}
	else if (this->m_buttonSprite.getColor() != this->m_initialColor && this->m_effectsShowing)
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
		if (this->m_barSprite.getColor() == m_initialBarColour && this->m_effectsShowing)
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
		if (this->m_barSprite.getColor() == m_initialBarColour && this->m_effectsShowing)
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
	else if (this->m_barSprite.getColor() != this->m_initialBarColour && this->m_selectorSprite.getColor() != this->m_initialSliderColour && this->m_effectsShowing)
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

	this->m_sendButton = new Button("", sf::Vector2f(this->m_textBoxTexture.getPosition().x + this->m_textBoxTexture.getLocalBounds().width + this->m_outlineThickness, this->m_textBoxTexture.getPosition().y), buttonScale, this->m_sendPressed, true, true);
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
		this->m_caretPos = 0;
	}
	else
		m_sendPressed = false;

	if (this->m_caretVal == "  " && this->m_timer.getElapsedTime().asSeconds() > 0.5 && this->m_focused)
	{
		if (this->m_caretPos == 0)
		{
			std::string temp = this->m_caretVal + this->m_textString;
			this->m_inputText.setString(temp);
		}
		else if (this->m_caretPos != 0)
		{
			std::string temp = this->m_textString;
			temp.insert(this->m_caretPos, this->m_caretVal);
			this->m_inputText.setString(temp);
			this->m_timer.restart();
		}
		this->m_caretVal = "_";
	}
	if (this->m_caretVal == "_" && this->m_timer.getElapsedTime().asSeconds() > 0.5 && this->m_focused)
	{
		std::string temp = this->m_textString;
		temp.insert(this->m_caretPos, this->m_caretVal);
		this->m_inputText.setString(temp);
		this->m_timer.restart();
		this->m_caretVal = "  ";
	}
	else if (m_moved)
	{
		std::string temp = this->m_textString;
		temp.insert(this->m_caretPos, this->m_caretVal);
		this->m_inputText.setString(temp);
		this->m_timer.restart();
		this->m_caretVal = "  ";
		m_moved = false;
	}
	if (!m_focused)
	{
		std::string s;
		if (this->m_caretVal == "_")
			s = std::string(this->m_inputText.getString().begin(), this->m_inputText.getString().end() - 1);
		else if (this->m_caretVal == "  ")
			s = std::string(this->m_inputText.getString());
		this->m_inputText.setString(s);
		this->m_caretVal = "  ";
	}
	
}

void TextInput::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(*window).x < this->m_textBoxTexture.getPosition().x + (this->m_textBoxTexture.getLocalBounds().width)
		&& sf::Mouse::getPosition(*window).x > this->m_textBoxTexture.getPosition().x && sf::Mouse::getPosition(*window).y > this->m_textBoxTexture.getPosition().y
		&& sf::Mouse::getPosition(*window).y < this->m_textBoxTexture.getPosition().y + this->m_textBoxTexture.getLocalBounds().height)
	{
		if(this->m_effectsShowing)
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
		if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left)
		{
			if (this->m_caretPos > 0)
			{
				this->m_caretVal = "_";
				this->m_caretPos--;
				this->m_timer.restart();
				m_moved = true;
			}
		}
		else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right)
		{
			if (this->m_caretPos < this->m_inputText.getString().getSize()-1)
			{
				this->m_caretVal = "_";
				this->m_caretPos++;
				this->m_timer.restart();
				m_moved = true;
			}
		}
		else if (e.type == sf::Event::TextEntered)
		{
			if (e.text.unicode < 128)
				this->UpdateTextBox(e.text.unicode);
		}
	}
	this->m_sendButton->ProcessInput(e, window);
}

void TextInput::UpdateTextBox(int charTyped)
{
	if (charTyped == DELETE_KEY && this->m_textString.size() > 0)
		DeleteLastChar();
	else if (charTyped == ENTER_KEY && this->m_textString.size() > 0)
	{
		this->m_inputText.setString(this->m_textString);
		this->m_caretPos = 0;
		this->m_sendPressed = true;
		return;
	}
	else if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && this->m_textString.length() < this->m_characterLimit)
	{
		//have the text string equal to the string and then the character inserted at the caret position
		char c = static_cast<char>(charTyped);
		std::string s;
		s += c;
		this->m_textString.insert(this->m_caretPos, s);
		this->m_caretPos++;
		this->m_moved = true;
		this->m_caretVal = "_";
	}

	this->m_inputText.setString(this->m_textString);
}

void TextInput::DeleteLastChar()
{
	std::string t = this->m_textString;
	std::string newTxtString = "";

	if (this->m_caretPos > 0)
	{
		newTxtString = std::string(t.begin(), t.begin() + this->m_caretPos - 1);
		newTxtString += std::string(t.begin() + this->m_caretPos, t.end());
		this->m_caretPos--;
		this->m_caretVal = "_";
		this->m_timer.restart();
		this->m_moved = true;
	}
	else
		return;

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

TextLog::TextLog(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& textLogtexture, sf::Font& textFont, sf::Color textColor, int charSize, bool activated, int lineSpacing,sf::Vector2f padding,int textObjLim) : UIElement(text, elementPos, scale, activated),m_padding(padding)
{
	this->m_type = "TextLog";

	m_textLogTexture.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_textLogTexture.setTexture(&textLogtexture);
	m_textLogTexture.setSize(sf::Vector2f(scale.x * textLogtexture.getSize().x, scale.y * textLogtexture.getSize().y));

	this->m_text.setFont(textFont);
	this->m_text.setCharacterSize(20);
	this->m_text.setPosition(sf::Vector2f(0, 0));
	this->m_text.setFillColor(textColor);

	this->m_sprite.setPosition(elementPos);

	this->m_textObjLim = textObjLim;

	this->m_renderTexture.create(this->m_textLogTexture.getLocalBounds().width, this->m_textLogTexture.getLocalBounds().height);

	this->m_lineSpacing = lineSpacing;
}

void TextLog::AddText(sf::Text text)
{
	sf::Text txt = text;
	sf::Text placeHolderText = text;
	sf::Text nextText;

	txt.setFont(*this->m_text.getFont());
	txt.setCharacterSize(this->m_text.getCharacterSize());
	txt.setFillColor(this->m_text.getFillColor());
	txt.setString(text.getString());
	placeHolderText = txt;

	std::string finalString;
	std::string finalText;

	if (txt.getLocalBounds().width > this->m_renderTexture.getSize().x - this->m_padding.x)
	{
		while (true)
		{
			if (placeHolderText.getLocalBounds().width > this->m_renderTexture.getSize().x - (this->m_padding.x*2))
			{
				int avgWidthPerChar = (placeHolderText.getLocalBounds().width) / placeHolderText.getString().getSize();
				int charsToAdd = 0;
				charsToAdd = ((this->m_renderTexture.getSize().x - (this->m_padding.x*2)) / avgWidthPerChar);
				sf::Text temp;
				temp = txt;
				temp.setString(std::string(placeHolderText.getString().begin(), placeHolderText.getString().begin() + charsToAdd));
				while (temp.getLocalBounds().width < this->m_renderTexture.getSize().x - (this->m_padding.x * 2))
				{
					charsToAdd++;
					temp.setString(std::string(placeHolderText.getString().begin(), placeHolderText.getString().begin() + charsToAdd));
				}
				char checkChar = temp.getString()[charsToAdd];
				int noCharsToAdd = charsToAdd;
				while (checkChar != ' ')
				{
					if (charsToAdd == 0)
					{
						charsToAdd = noCharsToAdd;
						charsToAdd -= 5;
						break;
					}
					charsToAdd--;
					checkChar = temp.getString()[charsToAdd];
				}
				charsToAdd++;
				std::string addStr = std::string(placeHolderText.getString().begin(), placeHolderText.getString().begin() + charsToAdd);
				placeHolderText.setString(std::string(placeHolderText.getString().begin() + charsToAdd, placeHolderText.getString().end()));
				addStr += "\n";
				finalString += addStr;
			}
			else
			{
				finalString += placeHolderText.getString();
				break;
			}
		}
		txt.setString(finalString);
	}
	else
		txt.setString(text.getString());
	
	
	if (this->m_textList.size() == this->m_textObjLim)
	{
		this->m_textList.insert(this->m_textList.begin(), txt);
		this->m_textList.erase(this->m_textList.end()-1);
	}

	else if (this->m_textList.size() < this->m_textObjLim)
		this->m_textList.insert(this->m_textList.begin(), txt);

	if (this->m_textList.size() == 1)
		this->m_textList[0].setPosition(m_padding.x,((this->m_textLogTexture.getPosition().y + this->m_textLogTexture.getLocalBounds().height) - this->m_textList[0].getLocalBounds().height) - this->m_lineSpacing - m_scrollAmount);
	else if (this->m_textList.size() > 1)
	{
		for (int i = 0; i <= this->m_textList.size()-1; i++)
		{
			if (i == 0)
				this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[i].getLocalBounds().height) - this->m_lineSpacing - m_padding.y));
			if (i != 0)
				this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textList[i - 1].getPosition().y - this->m_textList[i].getLocalBounds().height) - this->m_lineSpacing));
		}
	}
	int totalHeight = 0;
	totalHeight = (this->m_textList[0].getPosition().y + this->m_textList[0].getLocalBounds().height) - this->m_textList[this->m_textList.size() - 1].getPosition().y;
	if (totalHeight > this->m_textLogTexture.getLocalBounds().height - this->m_padding.y)
		this->m_maxScrollAmount = totalHeight - this->m_textLogTexture.getLocalBounds().height;
	
}

void TextLog::Update(float deltaTime)
{
}

void TextLog::Render(sf::RenderWindow* window)
{
	this->m_renderTexture.clear();
	this->m_renderTexture.draw(this->m_textLogTexture);

	if (this->m_textList.size() > 0)
	{
		if (this->m_textList.size() < 2)
		{
			this->m_renderTexture.draw(this->m_textList[0]);
		}
		
		else if (this->m_textList.size() > 1)
		{
			for (int i = this->m_textList.size()-1; i >= 0; i--)
			{
				this->m_renderTexture.draw(this->m_textList[i]);
			}
		}
	}
	this->m_renderTexture.display();
	this->m_sprite.setTexture(this->m_renderTexture.getTexture());
	window->draw(this->m_sprite);

}

void TextLog::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (e.type == e.MouseWheelScrolled)
	{
		if (sf::Mouse::getPosition(*window).x > this->m_position.x && sf::Mouse::getPosition(*window).x < this->m_position.x + this->m_textLogTexture.getLocalBounds().width
			&& sf::Mouse::getPosition(*window).y > this->m_position.y && sf::Mouse::getPosition(*window).y < this->m_position.y + this->m_textLogTexture.getLocalBounds().height)
		{
			if (this->m_maxScrollAmount > 0)
			{
				if (e.mouseWheelScroll.delta < 0.0f && this->m_scrollAmount * this->m_mouseScrollSensitivity >0)
				{
					this->m_scrollAmount--;
					if (this->m_scrollAmount < 0)
						this->m_scrollAmount = 0;
					for (int i = 0; i < this->m_textList.size(); i++)
					{
						this->m_textList[i].setPosition(sf::Vector2f(this->m_textList[i].getPosition().x, this->m_textList[i].getPosition().y - this->m_mouseScrollSensitivity));
					}
				}
				else if (e.mouseWheelScroll.delta > 0.0f && this->m_scrollAmount * this->m_mouseScrollSensitivity < this->m_maxScrollAmount)
				{
					this->m_scrollAmount++;
					if (this->m_scrollAmount > this->m_maxScrollAmount)
						this->m_scrollAmount = this->m_maxScrollAmount;
					for (int i = 0; i < this->m_textList.size(); i++)
					{
						this->m_textList[i].setPosition(sf::Vector2f(this->m_textList[i].getPosition().x, this->m_textList[i].getPosition().y + this->m_mouseScrollSensitivity));
					}

				}
			}
		}
		
	}
}

void TextLog::UpdatePosition(sf::Vector2f newPos)
{
	sf::Vector2f labelPos = sf::Vector2f(this->m_label.getPosition().x - this->GetOrigin().x, this->m_label.getPosition().y - this->GetOrigin().y);
	std::vector<sf::Vector2f> relativePositions;
	this->m_position = newPos;
	this->m_sprite.setPosition(newPos);
	this->m_label.setPosition(sf::Vector2f(labelPos.x + this->GetOrigin().x, labelPos.y + this->GetOrigin().y));

	this->m_textList[0].setPosition(sf::Vector2f(this->m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[0].getLocalBounds().height) - this->m_lineSpacing - m_padding.y));
	for (int i = 0; i <= this->m_textList.size() - 1; i++)
	{
		if (i == 0)
			this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[i].getLocalBounds().height) - this->m_lineSpacing - m_padding.y));
		if (i != 0)
			this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textList[i - 1].getPosition().y - this->m_textList[i].getLocalBounds().height) - this->m_lineSpacing));
	}
	
}

