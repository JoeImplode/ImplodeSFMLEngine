#include "pch.h"
#include "UIElement.h"

UIElement::UIElement(std::string text,sf::Vector2f elementPos, sf::Vector2f scale,bool activated)
{
	this->m_label.setString(text);
	this->m_pos = elementPos;
	this->m_scale = scale;
	this->m_enabled = activated;
}


Button::Button(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool activated, bool valToSet) : UIElement(text, elementPos, scale, activated)
{
	this->m_boolPtr = new bool();
	this->m_type = "Button";
	this->m_valToSet = valToSet;
}

Button::~Button()
{
	this->m_boolPtr = nullptr;
}

void Button::SetTexture(sf::Texture& texture)
{
	this->m_buttonSprite.setTexture(texture);
	this->m_buttonSprite.setScale(this->m_scale);
	this->m_buttonSprite.setPosition(this->m_pos);
	this->m_initclr = this->m_buttonSprite.getColor();
}

void Button::UpdatePos(sf::Vector2f position)
{
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);
	sf::Vector2f relativeButtonTextPos = sf::Vector2f(this->m_btnTxt.getPosition().x - GetOrigin().x, this->m_btnTxt.getPosition().y - GetOrigin().y);
	this->m_pos = position;
	this->m_buttonSprite.setPosition(position);
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + relativeLabelPos.x, GetOrigin().y + relativeLabelPos.y));
	this->m_btnTxt.setPosition(sf::Vector2f(relativeButtonTextPos.x + GetOrigin().x, relativeButtonTextPos.y + GetOrigin().y));
}

void Button::Update(float deltaTime)
{

}

void Button::Render(sf::RenderTexture& txtr)
{
	txtr.draw(this->m_buttonSprite);
	txtr.draw(this->m_btnTxt);
	txtr.draw(this->m_label);
}

void Button::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (sf::Mouse::getPosition(*window).x >= this->m_pos.x && sf::Mouse::getPosition(*window).x <= this->m_pos.x + this->m_buttonSprite.getLocalBounds().width * this->m_scale.x
		&& sf::Mouse::getPosition(*window).y >= this->m_pos.y && sf::Mouse::getPosition(*window).y <= this->m_pos.y + this->m_buttonSprite.getLocalBounds().height * this->m_scale.y)
	{
		if (this->m_buttonSprite.getColor() == this->m_initclr && this->m_effectEnabled)
			this->Selected();
		if (e.type == e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
			this->Notify();
	}
	else if (this->m_buttonSprite.getColor() != this->m_initclr && this->m_effectEnabled)
		this->m_buttonSprite.setColor(this->m_initclr);
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
	this->m_btnTxt = textExample;
}

Slider::Slider(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, bool activated) : UIElement(text,elementPos,scale,activated),m_selectorScle(selectorScale)
{
	this->m_type = "Slider";
}

void Slider::SetTextures(sf::Texture &barTexture, sf::Texture &selectorTexture)
{
	this->m_barSprite.setTexture(barTexture);
	this->m_barSprite.setScale(this->m_scale);
	this->m_barSprite.setPosition(this->m_pos);
	this->m_initBarClr = this->m_barSprite.getColor();

	this->m_selectorSprt.setTexture(selectorTexture);
	this->m_selectorSprt.setScale(this->m_selectorScle);
	this->m_selectorSprt.setPosition(sf::Vector2f(this->m_barSprite.getPosition().x, this->m_barSprite.getPosition().y));
	this->m_initSliderClr = this->m_selectorSprt.getColor();
}

void Slider::Update(float deltaTime)
{

}

void Slider::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (m_dragging && e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
		m_dragging = false;
	if (sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x				//calculate if we get the position within the bounds but not at the end of the button
		&&sf::Mouse::getPosition(*window).x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprt.getLocalBounds().width * this->m_selectorScle.x)
		&& sf::Mouse::getPosition(*window).y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& sf::Mouse::getPosition(*window).y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initBarClr && this->m_effectEnabled)
			this->Selected();
		if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && !m_dragging)
		{
			this->m_selectorSprt.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
			m_dragging = true;
		}
		else if (e.type == sf::Event::MouseMoved && m_dragging)
		{
			this->m_selectorSprt.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
		else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && m_dragging)
			m_dragging = false;
	}
	else if (sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x			//Calculate if we get the position within the bounds but at the end
		&& sf::Mouse::getPosition(*window).x >= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprt.getLocalBounds().width * this->m_selectorScle.x)
		&& sf::Mouse::getPosition(*window).x <= this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x
		&& sf::Mouse::getPosition(*window).y <= this->m_barSprite.getPosition().y + this->m_barSprite.getLocalBounds().height * this->m_scale.y
		&& sf::Mouse::getPosition(*window).y >= this->m_barSprite.getPosition().y)
	{
		if (this->m_barSprite.getColor() == m_initBarClr && this->m_effectEnabled)
			this->Selected();
		if (e.type == e.MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left && !m_dragging)
		{
			this->m_selectorSprt.setPosition(this->m_barSprite.getPosition().x + this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprt.getLocalBounds().width * this->m_selectorScle.x), this->m_barSprite.getPosition().y);
			this->Notify();
			m_dragging = true;
		}
		else if (e.MouseMoved && m_dragging)
		{
			this->m_selectorSprt.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, this->m_barSprite.getPosition().y));
			this->Notify();
		}
		else if (e.MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && m_dragging)
			m_dragging = false;
	}
	else if (this->m_barSprite.getColor() != this->m_initBarClr && this->m_selectorSprt.getColor() != this->m_initSliderClr && this->m_effectEnabled)
	{
		this->m_barSprite.setColor(this->m_initBarClr);
		this->m_selectorSprt.setColor(this->m_initSliderClr);
	}
}

void Slider::Render(sf::RenderTexture& txtr)
{
	txtr.draw(this->m_label);
	txtr.draw(this->m_barSprite);
	txtr.draw(this->m_selectorSprt);
}

void Slider::Notify()
{
	//take the width of the slider bar and calculate how much distance was traveled as a percentage

	float width = this->m_barSprite.getLocalBounds().width * this->m_scale.x - (this->m_selectorSprt.getLocalBounds().width * this->m_selectorScle.x);
	*this->m_floatRef = (this->m_selectorSprt.getPosition().x - this->m_barSprite.getPosition().x)/width ; 
}

void Slider::UpdatePos(sf::Vector2f position)
{
	sf::Vector2f labelRelativePos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);
	sf::Vector2f barSpriteRelativePos = sf::Vector2f(this->m_barSprite.getPosition().x - GetOrigin().x, this->m_barSprite.getPosition().y - GetOrigin().y);
	sf::Vector2f sliderSpriteRelativePos = sf::Vector2f(this->m_selectorSprt.getPosition().x - GetOrigin().x, this->m_selectorSprt.getPosition().y - GetOrigin().y);

	this->m_pos = position;
	this->m_barSprite.setPosition(sf::Vector2f(GetOrigin().x + barSpriteRelativePos.x,GetOrigin().y + barSpriteRelativePos.y));
	this->m_selectorSprt.setPosition(sf::Vector2f(GetOrigin().x + sliderSpriteRelativePos.x, GetOrigin().y +sliderSpriteRelativePos.y));
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + labelRelativePos.x, GetOrigin().y + labelRelativePos.y));
}

void Slider::Selected()
{
	sf::Color c = this->m_barSprite.getColor();
	c.r -= 70.0f;
	c.g -= 70.0f;
	c.b -= 70.0f;
	this->m_barSprite.setColor(c);

	sf::Color sc = this->m_selectorSprt.getColor();
	sc.r -= 70.0f;
	sc.g -= 70.0f;
	sc.b -= 70.0f;
	this->m_selectorSprt.setColor(sc);
}

void Publisher::Update(float deltaTime)
{
	for (auto element : this->m_elements)
	{
		if (element->GetActivated())
			element->Update(deltaTime);
	}
}

void Publisher::Render(sf::RenderTexture& txtr)
{
	for (auto element : this->m_elements)
	{
		if(element->GetActivated())
			element->Render(txtr);
	}
}

void Publisher::ProcessInput(sf::Event& event,sf::RenderWindow * window)
{
	for (auto element : this->m_elements)
		if (element->GetActivated())
			element->ProcessInput(event,window);
}

ButtonGroup::ButtonGroup(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool orientation, sf::Texture& borderTexture, bool activated)
	: UIElement(text, elementPos, scale,activated),m_orientation(orientation)
{
	this->m_type = "ButtonGroup";
	this->m_border.setTexture(&borderTexture);
	this->m_border.setPosition(elementPos);
	this->m_border.setSize(sf::Vector2f(scale.x * borderTexture.getSize().x, scale.y * borderTexture.getSize().y));
}

ButtonGroup::~ButtonGroup()
{
	this->m_boolRef = nullptr;
	this->m_leftButton->~Button();
	this->m_rightButton->~Button();
}

void ButtonGroup::Update(float deltaTime)
{
	
}

void ButtonGroup::Render(sf::RenderTexture& txtr)
{
	txtr.draw(this->m_border);
	this->m_leftButton->Render(txtr);
	this->m_rightButton->Render(txtr);
	txtr.draw(this->m_label);
}

void ButtonGroup::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	this->m_leftButton->ProcessInput(e, window);
	this->m_rightButton->ProcessInput(e, window);
}

void ButtonGroup::SetButtons(sf::Texture& leftTexture,sf::Vector2f scaleLeft, sf::Texture& rightTexture, sf::Vector2f scaleRight)
{
	//construct the left and the right button here
	this->m_leftButton = new Button("", sf::Vector2f(0, 0), scaleLeft, this->m_enabled,true);
	this->m_rightButton = new Button("", sf::Vector2f(0, 0), scaleRight,this->m_enabled,false);

	float leftW = (leftTexture.getSize().x * scaleLeft.x);
	float rightW = (rightTexture.getSize().x * scaleRight.x);

	float leftH = (leftTexture.getSize().y * scaleLeft.y);
	float rightH = (rightTexture.getSize().y * scaleRight.y);
	
	if (m_orientation)
	{
		this->m_leftButton->SetPos(sf::Vector2f(this->m_pos.x + (this->m_border.getLocalBounds().width) / 8,
			this->m_pos.y + ((this->m_border.getLocalBounds().height) / 2) - (leftH / 2)));
		this->m_leftButton->SetTexture(leftTexture);

		this->m_rightButton->SetPos(sf::Vector2f(this->m_pos.x + (this->m_border.getLocalBounds().width - (this->m_border.getLocalBounds().width / 8) - rightW),
			this->m_pos.y + ((this->m_border.getLocalBounds().height) / 2) - (rightH /2)));
		this->m_rightButton->SetTexture(rightTexture);
	}

	else if (!m_orientation )
	{
		this->m_leftButton->SetPos(sf::Vector2f((this->m_pos.x + (this->m_border.getLocalBounds().width) / 2) - (leftW / 2),
			this->m_pos.y + (this->m_border.getLocalBounds().height) / 8));
		this->m_leftButton->SetTexture(leftTexture);

		this->m_rightButton->SetPos(sf::Vector2f((this->m_pos.x + (this->m_border.getLocalBounds().width) / 2) - (rightW /2),
			this->m_pos.y + (this->m_border.getLocalBounds().height - (this->m_border.getLocalBounds().height/8) - rightH)));
		this->m_rightButton->SetTexture(rightTexture);
	}
}

void ButtonGroup::UpdatePos(sf::Vector2f position)
{
	sf::Vector2f relativeLeftButtonPos = sf::Vector2f(this->m_leftButton->GetPosition().x - GetOrigin().x, this->m_leftButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeRightButtonPos = sf::Vector2f(this->m_rightButton->GetPosition().x - GetOrigin().x, this->m_rightButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);

	this->m_pos = position;
	this->m_leftButton->UpdatePos(sf::Vector2f(relativeLeftButtonPos.x + GetOrigin().x,GetOrigin().y + relativeLeftButtonPos.y));
	this->m_rightButton->UpdatePos(sf::Vector2f(GetOrigin().x + relativeRightButtonPos.x, GetOrigin().y + relativeRightButtonPos.y));
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

void Widget::Render(sf::RenderTexture& txtr)
{
	txtr.draw(this->m_border);
	txtr.draw(this->m_label);
	for (auto element : this->m_elements)
	{
		if(element->GetActivated())
			element->Render(txtr);
	}
}

void Widget::AddElement(UIElement* element, sf::Vector2f percentagePos)
{
	if (percentagePos.x < 0 || percentagePos.x > 1 || percentagePos.y < 0 || percentagePos.y > 1)
	{
		std::cout << "Error, please provide floats from 0-1 so 80% = 0.8!" << std::endl;
		return;
	}
	element->UpdatePos(sf::Vector2f(this->m_pos.x + (this->m_border.getLocalBounds().width * percentagePos.x), this->m_pos.y + (this->m_border.getLocalBounds().height * percentagePos.y)));
	this->m_elements.push_back(element);
}

DropDown::DropDown(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Text buttonText, sf::Texture & buttonTexture, bool activated) : UIElement(text, elementPos, scale,activated)
{
	this->m_type = "DropDown";
	this->m_activatorButton = new Button("", elementPos, scale, false, true);
	this->m_dropDwnShw = false;
	this->m_activatorButton->SetBoolRef(this->m_dropDwnShw);
	this->m_activatorButton->SetTexture(buttonTexture);
	this->m_activatorButton->m_btnTxt = buttonText;
	this->m_activatorButton->m_btnTxt.setCharacterSize(this->m_activatorButton->GetHeight() / 2);
	this->m_activatorButton->m_btnTxt.setPosition(sf::Vector2f((this->m_activatorButton->GetPosition().x + (this->m_activatorButton->GetWidth() / 2)) - (this->m_activatorButton->m_btnTxt.getLocalBounds().width/2),
		(this->m_activatorButton->GetPosition().y + (this->m_activatorButton->GetHeight() / 2)) - (this->m_activatorButton->m_btnTxt.getLocalBounds().height /2)));
}

DropDown::~DropDown()
{
	this->m_activatorButton = nullptr;
	for (int i = 0; i < this->m_buttons.size();i++)
	{
		this->m_buttons[i]->~Button();
	}
}

void DropDown::Update(float deltaTime)
{
	
}

void DropDown::Render(sf::RenderTexture& txtr)
{
	this->m_activatorButton->Render(txtr);
	if (this->m_dropDwnShw)
	{
		for (int i = 0; i < this->m_buttons.size(); i++)
			this->m_buttons[i]->Render(txtr);
	}
}

void DropDown::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	this->m_activatorButton->ProcessInput(e,window);
	if (this->m_dropDwnShw)
	{
		for (int i = 0; i < this->m_buttons.size(); i++)
			this->m_buttons[i]->ProcessInput(e, window);
		this->m_activatorButton->SetValToSet(false);
	}
	if (!this->m_dropDwnShw && !this->m_activatorButton->GetValToSet())
		this->m_activatorButton->SetValToSet(true);
}

void DropDown::AddSelection(sf::Text buttonText, std::string textString, sf::Texture& buttonTexture, sf::Vector2f buttonScale, bool * reference, bool valToSet)
{
	Button * btn = new Button("", sf::Vector2f(0, 0), buttonScale,this->m_enabled,valToSet);
	btn->SetBoolRef(*reference);
	btn->SetPos(sf::Vector2f(this->m_activatorButton->GetPosition().x, this->m_activatorButton->GetPosition().y + (this->m_activatorButton->GetHeight() * (this->m_buttons.size()+1))));
	btn->m_btnTxt = buttonText;
	btn->m_btnTxt.setString(textString);
	btn->SetTexture(buttonTexture);
	btn->m_btnTxt.setCharacterSize(this->m_activatorButton->GetHeight() / 2);
	btn->m_btnTxt.setPosition(sf::Vector2f((btn->GetPosition().x + (btn->GetWidth()/2)) - (btn->m_btnTxt.getLocalBounds().width / 2), (btn->GetPosition().y + (btn->GetHeight() / 2)) - (btn->m_btnTxt.getLocalBounds().height/2)));
	this->m_buttons.push_back(new Button(*btn));
}

void DropDown::UpdatePos(sf::Vector2f position)
{
	sf::Vector2f relativeActivatorButtonPos = sf::Vector2f(this->m_activatorButton->GetPosition().x - GetOrigin().x, this->m_activatorButton->GetPosition().y - GetOrigin().y);
	sf::Vector2f relativeLabelPos = sf::Vector2f(this->m_label.getPosition().x - GetOrigin().x, this->m_label.getPosition().y - GetOrigin().y);

	this->m_pos = position;
	this->m_activatorButton->UpdatePos(sf::Vector2f(relativeActivatorButtonPos.x + GetOrigin().x, GetOrigin().y + relativeActivatorButtonPos.y));
	this->m_label.setPosition(sf::Vector2f(GetOrigin().x + relativeLabelPos.x, GetOrigin().y + relativeLabelPos.y));
	for (int i = 0; i < this->m_buttons.size(); i++)
	{
		this->m_buttons[i]->UpdatePos(sf::Vector2f(position.x, position.y + (this->m_activatorButton->GetHeight() * (i+1))));
	}
	this->m_activatorButton->UpdatePos(position);
}

TextInput::TextInput(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& buttonTexture, sf::Texture& textBoxTexture, sf::Vector2f buttonScale, int characterLimit, std::string buttonLabel, bool activated,sf::Font & font,std::string buttonText, sf::Color textColor, sf::Color outlineColor, int outlineThickness) : UIElement(text, elementPos, scale, activated), m_charLim(characterLimit), m_outLnThick(outlineThickness)
{
	this->m_type = "TextInput";
	this->m_str = new std::string();
	this->m_textBoxTxtre.setTexture(&textBoxTexture);
	this->m_textBoxTxtre.setPosition(elementPos);
	this->m_textBoxTxtre.setSize(sf::Vector2f(scale.x * textBoxTexture.getSize().x, scale.y * textBoxTexture.getSize().y));

	this->m_inputTxt.setFont(font);
	this->m_inputTxt.setCharacterSize(scale.y * textBoxTexture.getSize().y / 2);
	this->m_inputTxt.setPosition(elementPos.x,elementPos.y + ((scale.y * textBoxTexture.getSize().y) / 2) - ((scale.y * textBoxTexture.getSize().y / 2)/2));
	this->m_inputTxt.setFillColor(textColor);
	
	this->m_checkText = this->m_inputTxt;

	float width = this->m_textBoxTxtre.getLocalBounds().width * this->m_scale.x;

	this->m_sndBtn = new Button("", sf::Vector2f(this->m_textBoxTxtre.getPosition().x + this->m_textBoxTxtre.getLocalBounds().width + this->m_outLnThick, this->m_textBoxTxtre.getPosition().y), buttonScale, true, true);
	this->m_sndBtn->SetBoolRef(this->m_sndPressed);
	this->m_sndBtn->SetTexture(buttonTexture);
	this->m_sndBtn->SetButtonText(this->m_inputTxt);
	this->m_sndBtn->m_btnTxt.setCharacterSize(this->m_sndBtn->GetHeight() / 2);
	this->m_sndBtn->m_btnTxt.setFillColor(textColor);
	this->m_sndBtn->m_btnTxt.setString(buttonText);	
	this->m_sndBtn->m_btnTxt.setPosition(sf::Vector2f(this->m_sndBtn->GetPosition().x + ((this->m_sndBtn->GetWidth() / 2) - (this->m_sndBtn->m_btnTxt.getLocalBounds().width/2)),
		this->m_sndBtn->GetPosition().y + ((this->m_sndBtn->GetHeight() / 2) - (this->m_sndBtn->GetHeight() / 2)/2)));
	this->m_textBoxTxtre.setOutlineColor(outlineColor);
}

TextInput::~TextInput()
{
	this->m_sndBtn->~Button();
}

void TextInput::Update(float deltaTime)
{
	if (this->m_sndPressed && this->m_textStr.size() > 0)
	{
		*this->m_str = this->m_textStr;
		this->m_sndPressed = false;
		this->m_textStr = "";
		this->m_showStr = "";
		this->m_inputTxt.setString("");
		this->m_caretPos = 0;
		this->m_lowBound = 0;
		this->m_highBound = 0;
	}
	if(this->m_sndPressed)
		this->m_sndPressed = false;
}

void TextInput::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left && sf::Mouse::getPosition(*window).x < this->m_textBoxTxtre.getPosition().x + (this->m_textBoxTxtre.getLocalBounds().width)
		&& sf::Mouse::getPosition(*window).x > this->m_textBoxTxtre.getPosition().x && sf::Mouse::getPosition(*window).y > this->m_textBoxTxtre.getPosition().y
		&& sf::Mouse::getPosition(*window).y < this->m_textBoxTxtre.getPosition().y + this->m_textBoxTxtre.getLocalBounds().height)
	{
		if(this->m_effectEnabled)
			this->m_textBoxTxtre.setOutlineThickness(this->m_outLnThick);
		if (!this->m_focused && !m_wasFocused)
			this->m_focused = true;
		else if (this->m_focused && m_wasFocused)
			this->m_focused = false;
	}
	else if (e.type == sf::Event::MouseButtonReleased && e.mouseButton.button == sf::Mouse::Left)
	{
		this->m_textBoxTxtre.setOutlineThickness(0);
		this->m_focused = false;
	}
	else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left)
	{
		if (this->m_caretPos > 0)
		{
			this->m_caretPos--;
			CheckBounds();
		}
	}
	else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right)
	{
		if (this->m_caretPos < this->m_textStr.size())
		{
			this->m_caretPos++;
			CheckBounds();
		}
	}
	if (this->m_focused)
	{
		
		if (e.type == sf::Event::TextEntered && e.key.code != sf::Keyboard::LControl)
		{
			if (e.text.unicode < 128)
				this->UpdateTextBox(e.text.unicode);
		}
	}
	CheckBounds();
	this->m_sndBtn->ProcessInput(e, window);
}

void TextInput::UpdateTextBox(int charTyped)
{
	if (charTyped == DELETE_KEY && this->m_textStr.size() > 0)
		DeleteLastChar();
	else if (charTyped == ENTER_KEY && this->m_textStr.size() > 0)
	{
		this->m_caretPos = 0;
		this->m_sndPressed = true;
		return;
	}
	else if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && this->m_textStr.length() < this->m_charLim)
	{
		//have the text string equal to the string and then the character inserted at the caret position
		char c = static_cast<char>(charTyped);
		std::string s;
		s += c;
		this->m_textStr.insert(this->m_caretPos, s);
		this->m_checkText.setString(this->m_textStr);
		this->m_caretPos++;
		if (this->m_caretPos == 0 && this->m_lowBound > 0)
			this->m_lowBound--;
		if (this->m_highBound < this->m_showStr.size())
			this->m_highBound++;
		CheckBounds();
	}
}

void TextInput::DeleteLastChar()
{
	if (this->m_textStr.size() > 0 && this->m_caretPos > 0)
	{
		std::string str = std::string(this->m_textStr.begin(),this->m_textStr.begin() + this->m_caretPos - 1);
		std::string str2 = std::string(this->m_textStr.begin() + this->m_caretPos, this->m_textStr.end());

		this->m_textStr = str += str2;
		this->m_caretPos--;
		if(this->m_lowBound >0)
			this->m_lowBound--;
		this->m_highBound--;
		if (this->m_showStr.size() < (this->m_textBoxTxtre.getLocalBounds().width / this->m_avgWidth))
			if(this->m_highBound < this->m_textStr.size())
				this->m_highBound++;
		CheckBounds();
	}
}

void TextInput::CheckBounds()
{
	if (this->m_checkText.getLocalBounds().width > (this->m_textBoxTxtre.getLocalBounds().width))//added a bit of padding here
	{
		if (this->m_caretPos < this->m_lowBound || this->m_caretPos > this->m_highBound)
		{
			this->m_avgWidth = this->m_checkText.getLocalBounds().width / this->m_checkText.getString().getSize();
			this->m_totalChars = this->m_textBoxTxtre.getLocalBounds().width / m_avgWidth;

			if(this->m_caretPos < this->m_lowBound)
			{
				if (this->m_lowBound > 0)
					this->m_lowBound--;
				this->m_highBound = this->m_lowBound + this->m_totalChars;
				if (this->m_highBound > this->m_textStr.size())
					this->m_highBound = this->m_textStr.size();
			}
			else if (this->m_caretPos > this->m_highBound)
			{
				if (this->m_highBound <= this->m_textStr.size() - 1)
					this->m_highBound++;
				this->m_lowBound = this->m_highBound - this->m_totalChars;
				if (this->m_lowBound < 0)
					this->m_lowBound = 0;
			}
		}
	}
	else
	{
		this->m_lowBound = 0;
		this->m_highBound = this->m_textStr.size();
	}
	std::string s = this->m_textStr;
	if (m_focused)
	{
		s.insert(this->m_caretPos, "|");
		this->m_showStr = std::string(s.begin() + m_lowBound, s.begin() + this->m_highBound + 1);
	}
	else
	{
		this->m_showStr = std::string(s.begin() + m_lowBound, s.begin() + this->m_highBound);
	}
	this->m_inputTxt.setString(this->m_showStr);
	while (true)
	{
		if (this->m_inputTxt.getLocalBounds().width > this->m_textBoxTxtre.getLocalBounds().width)
		{
			if (this->m_caretPos <= this->m_lowBound)
				this->m_highBound--;
			else if (this->m_caretPos > this->m_lowBound)
				this->m_lowBound++;
			this->m_showStr = std::string(s.begin() + m_lowBound, s.begin() + this->m_highBound);
			this->m_inputTxt.setString(this->m_showStr);
		}
		else
			break;
	}
}


void TextInput::Render(sf::RenderTexture& txtr)
{
	txtr.draw(this->m_textBoxTxtre);
	txtr.draw(this->m_inputTxt);
	this->m_sndBtn->Render(txtr);
}

void TextInput::UpdatePos(sf::Vector2f position)
{
	sf::Vector2f relativeButtonPos = sf::Vector2f(this->m_sndBtn->GetPosition().x - this->GetOrigin().x, this->m_sndBtn->GetPosition().y - this->GetOrigin().y);
	sf::Vector2f relativeTextPos = sf::Vector2f(this->m_inputTxt.getPosition().x - this->GetOrigin().x, this->m_inputTxt.getPosition().y - this->GetOrigin().y);

	this->m_textBoxTxtre.setPosition(position);
	this->m_sndBtn->UpdatePos(sf::Vector2f(relativeButtonPos.x + this->GetOrigin().x, relativeButtonPos.y + this->GetOrigin().y));
	this->m_inputTxt.setPosition(sf::Vector2f(this->GetOrigin().x + relativeTextPos.x, this->GetOrigin().y + relativeTextPos.y));
}

TextLog::TextLog(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& textLogtexture, sf::Font& textFont, sf::Color textColor, int charSize, bool activated, int lineSpacing,sf::Vector2f padding,int textObjLim) : UIElement(text, elementPos, scale, activated),m_padding(padding)
{
	this->m_type = "TextLog";

	m_textLogTexture.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_textLogTexture.setTexture(&textLogtexture);
	m_textLogTexture.setSize(sf::Vector2f(scale.x * textLogtexture.getSize().x, scale.y * textLogtexture.getSize().y));

	this->m_text.setFont(textFont);
	this->m_text.setCharacterSize(charSize);
	this->m_text.setPosition(sf::Vector2f(0, 0));
	this->m_text.setFillColor(textColor);

	this->m_sprite.setPosition(elementPos);

	this->m_textObjLim = textObjLim;

	this->m_renderTexture.create(this->m_textLogTexture.getLocalBounds().width, this->m_textLogTexture.getLocalBounds().height);

	this->m_lnSpace = lineSpacing;
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
				int paddingForChar = this->m_padding.x / avgWidthPerChar;
				int charsToAdd = 0;
				charsToAdd = ((this->m_renderTexture.getSize().x - (this->m_padding.x*2)) / avgWidthPerChar) - paddingForChar;
				sf::Text temp;
				temp = txt;
				if (charsToAdd > placeHolderText.getString().getSize() -1 - paddingForChar)
					charsToAdd = placeHolderText.getString().getSize() - 1 - paddingForChar;
				temp.setString(std::string(placeHolderText.getString().begin(), placeHolderText.getString().begin() + charsToAdd));
				while (temp.getLocalBounds().width > this->m_renderTexture.getSize().x - (this->m_padding.x * 2))
				{
					charsToAdd--;
					temp.setString(std::string(placeHolderText.getString().begin(), placeHolderText.getString().begin() + charsToAdd));
				}
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
						charsToAdd -= this->m_padding.x;
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
		this->m_textList[0].setPosition(m_padding.x,((this->m_textLogTexture.getPosition().y + this->m_textLogTexture.getLocalBounds().height) - this->m_textList[0].getLocalBounds().height) - this->m_lnSpace);
	else if (this->m_textList.size() > 1)
	{
		for (int i = 0; i <= this->m_textList.size()-1; i++)
		{
			if (i == 0)
				this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[i].getLocalBounds().height) - this->m_lnSpace - m_padding.y));
			if (i != 0)
				this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textList[i - 1].getPosition().y - this->m_textList[i].getLocalBounds().height) - this->m_lnSpace));
		}
	}
	int totalHeight = 0;
	totalHeight = (this->m_textList[0].getPosition().y + this->m_textList[0].getLocalBounds().height) - this->m_textList[this->m_textList.size() - 1].getPosition().y;
	if (totalHeight > this->m_textLogTexture.getLocalBounds().height - this->m_padding.y)
	{
		this->m_scrollAmount = 0;
		this->m_maxScrollAmount = totalHeight - (this->m_textLogTexture.getLocalBounds().height - (this->m_padding.y*2));
	}
}

void TextLog::Update(float deltaTime)
{
}

void TextLog::Render(sf::RenderTexture& txtr)
{
	this->m_renderTexture.clear(sf::Color::Transparent);
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
	txtr.draw(this->m_sprite);

}

void TextLog::ProcessInput(sf::Event& e, sf::RenderWindow* window)
{
	if (e.type == e.MouseWheelScrolled)
	{
		if (sf::Mouse::getPosition(*window).x > this->m_pos.x && sf::Mouse::getPosition(*window).x < this->m_pos.x + this->m_textLogTexture.getLocalBounds().width
			&& sf::Mouse::getPosition(*window).y > this->m_pos.y && sf::Mouse::getPosition(*window).y < this->m_pos.y + this->m_textLogTexture.getLocalBounds().height)
		{
			if (this->m_maxScrollAmount > 0)
			{
				if (e.mouseWheelScroll.delta < 0.0f && this->m_scrollAmount * this->m_scrllSensitivity >0)
				{
					this->m_scrollAmount--;
					if (this->m_scrollAmount < 0)
						this->m_scrollAmount = 0;
					for (int i = 0; i < this->m_textList.size(); i++)
					{
						this->m_textList[i].setPosition(sf::Vector2f(this->m_textList[i].getPosition().x, this->m_textList[i].getPosition().y - this->m_scrllSensitivity));
					}
				}
				else if (e.mouseWheelScroll.delta > 0.0f && this->m_scrollAmount * this->m_scrllSensitivity < this->m_maxScrollAmount)
				{
					this->m_scrollAmount++;
					if (this->m_scrollAmount > this->m_maxScrollAmount)
						this->m_scrollAmount = this->m_maxScrollAmount;
					for (int i = 0; i < this->m_textList.size(); i++)
					{
						this->m_textList[i].setPosition(sf::Vector2f(this->m_textList[i].getPosition().x, this->m_textList[i].getPosition().y + this->m_scrllSensitivity));
					}

				}
			}
		}
		
	}
}

void TextLog::UpdatePos(sf::Vector2f newPos)
{
	sf::Vector2f labelPos = sf::Vector2f(this->m_label.getPosition().x - this->GetOrigin().x, this->m_label.getPosition().y - this->GetOrigin().y);
	std::vector<sf::Vector2f> relativePositions;
	this->m_pos = newPos;
	this->m_sprite.setPosition(newPos);
	this->m_label.setPosition(sf::Vector2f(labelPos.x + this->GetOrigin().x, labelPos.y + this->GetOrigin().y));

	this->m_textList[0].setPosition(sf::Vector2f(this->m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[0].getLocalBounds().height) - this->m_lnSpace - m_padding.y));
	for (int i = 0; i <= this->m_textList.size() - 1; i++)
	{
		if (i == 0)
			this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textLogTexture.getLocalBounds().height - this->m_textList[i].getLocalBounds().height) - this->m_lnSpace - m_padding.y));
		if (i != 0)
			this->m_textList[i].setPosition(sf::Vector2f(m_padding.x, (this->m_textList[i - 1].getPosition().y - this->m_textList[i].getLocalBounds().height) - this->m_lnSpace));
	}
	
}
