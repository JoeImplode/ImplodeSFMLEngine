#include "pch.h"
#include "PoolExample.h"

PoolExample::PoolExample()
{
	this->m_assetPool->LoadTexture("resources/textures/sliderTest.png", "button");
	this->m_assetPool->LoadTexture("resources/textures/selectorTest.png", "slider");
	this->m_assetPool->LoadTexture("resources/textures/buttonBack.png", "aporva");
	this->m_assetPool->LoadTexture("resources/textures/saveIcon.png", "save");
	this->m_assetPool->LoadTexture("resources/textures/man.png", "man");
	this->m_assetPool->LoadTexture("resources/textures/Yes.png", "yes");
	this->m_assetPool->LoadTexture("resources/textures/No.png", "no");
	this->m_assetPool->LoadTexture("resources/textures/ddSelect.png", "DropDown");
	this->m_assetPool->LoadTexture("Resources/textures/ddButton.png", "ddButton");
	this->m_assetPool->LoadFont("resources/fonts/Roboto-Light.ttf", "font");
	this->m_assetPool->LoadFont("resources/fonts/comicSans.ttf", "font2");
	this->m_assetPool->LoadTexture("resources/textures/MainPanel03.png", "Panel");
	this->m_assetPool->LoadTexture("resources/textures/MainPanel01.png", "Panel2");
	this->m_assetPool->LoadTexture("resources/textures/Button03.png", "button3");
	this->m_assetPool->LoadTexture("resources/textures/Button01.png", "button1");
	
	this->m_button = new Button("", sf::Vector2f(1200, 10), sf::Vector2f(1.0f, 1.0f), true, true);
	this->m_button->SetBoolRef(buttonState);
	this->m_button->SetTexture(m_assetPool->GetTexture("no"));
	this->m_button->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_button->SetLabelPos(sf::Vector2f(0, -100.0f));
	this->m_button->SetActivated(true);

	this->m_pauseButton1 = new Button("", sf::Vector2f(1000, 520), sf::Vector2f(0.5f, 0.3f), true, true);
	this->m_pauseButton1->SetBoolRef(m_boolToCheck);
	this->m_pauseButton1->SetTexture(m_assetPool->GetTexture("Panel"));
	this->m_pauseButton1->m_btnTxt.setFont(this->m_assetPool->GetFont("font"));
	this->m_pauseButton1->m_btnTxt.setString("Button");
	this->m_pauseButton1->m_btnTxt.setCharacterSize(20);
	this->m_pauseButton1->m_btnTxt.setPosition(sf::Vector2f(this->m_pauseButton1->GetPosition().x + (this->m_pauseButton1->GetWidth()/3.3), this->m_pauseButton1->GetPosition().y + this->m_pauseButton1->GetHeight()/6));
	this->m_pauseButton1->SetActivated(true);

	this->m_pauseButton2 = new Button("", sf::Vector2f(1000, 520), sf::Vector2f(0.5f, 0.3f), true, true);
	this->m_pauseButton2->SetBoolRef(m_boolToCheck);
	this->m_pauseButton2->SetTexture(m_assetPool->GetTexture("Panel"));
	this->m_pauseButton2->m_btnTxt.setFont(this->m_assetPool->GetFont("font"));
	this->m_pauseButton2->m_btnTxt.setString("Button 2");
	this->m_pauseButton2->m_btnTxt.setCharacterSize(20);
	this->m_pauseButton2->m_btnTxt.setPosition(sf::Vector2f(this->m_pauseButton2->GetPosition().x + (this->m_pauseButton2->GetWidth() / 3.5), this->m_pauseButton2->GetPosition().y + this->m_pauseButton2->GetHeight() / 6));
	this->m_pauseButton2->SetActivated(true);

	this->m_pauseButton3 = new Button("", sf::Vector2f(1000, 520), sf::Vector2f(0.5f, 0.3f), true, true);
	this->m_pauseButton3->SetBoolRef(m_boolToCheck);
	this->m_pauseButton3->SetTexture(m_assetPool->GetTexture("Panel"));
	this->m_pauseButton3->m_btnTxt.setFont(this->m_assetPool->GetFont("font"));
	this->m_pauseButton3->m_btnTxt.setString("Button 3");
	this->m_pauseButton3->m_btnTxt.setCharacterSize(20);
	this->m_pauseButton3->m_btnTxt.setPosition(sf::Vector2f(this->m_pauseButton3->GetPosition().x + (this->m_pauseButton3->GetWidth() / 3.5), this->m_pauseButton3->GetPosition().y + this->m_pauseButton3->GetHeight() / 6));
	this->m_pauseButton3->SetActivated(true);

	this->m_slider = new Slider("Brightness", sf::Vector2f(400, 400), sf::Vector2f(0.7f, 0.3f), sf::Vector2f(0.2f, 0.75f), true);
	this->m_slider->SetFloatRef(floatRef);
	this->m_slider->SetTextures(m_assetPool->GetTexture("Panel"), m_assetPool->GetTexture("button3"));
	this->m_slider->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_slider->SetLabelPos(sf::Vector2f(-90, -100));
	this->m_slider->m_label.setString("Brightness");
	this->m_slider->m_label.setCharacterSize(20);

	this->m_volumeSlider = new Slider("Volume", sf::Vector2f(400, 400), sf::Vector2f(0.7f, 0.3f), sf::Vector2f(0.2f, 0.75f), true);
	this->m_volumeSlider->SetFloatRef(floatRef);
	this->m_volumeSlider->SetTextures(m_assetPool->GetTexture("Panel"), m_assetPool->GetTexture("button3"));
	this->m_volumeSlider->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_volumeSlider->SetLabelPos(sf::Vector2f(-80, -100));
	this->m_volumeSlider->m_label.setString("Volume");
	this->m_volumeSlider->m_label.setCharacterSize(20);

	this->m_buttonGroup = new ButtonGroup("ARE YOU SURE YOU WANT TO QUIT?", sf::Vector2f(300, 300), sf::Vector2f(0.8f, 0.7f), true, m_assetPool->GetTexture("Panel"), true); //texture
	this->m_buttonGroup->SetButtons(m_assetPool->GetTexture("button3"), sf::Vector2f(1.3f, 1.0f), m_assetPool->GetTexture("button3"), sf::Vector2f(1.3f, 1.0f));
	this->m_buttonGroup->SetBoolRef(m_quitBool);
	this->m_buttonGroup->SetLabelPos(sf::Vector2f(-230.0f, -100.0f));
	this->m_buttonGroup->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_buttonGroup->m_label.setFillColor(sf::Color::White);

	this->m_buttonGroup->m_leftButton->m_btnTxt.setString("Yes");
	this->m_buttonGroup->m_rightButton->m_btnTxt.setString("No");
	this->m_buttonGroup->m_leftButton->m_btnTxt.setPosition(sf::Vector2f(this->m_buttonGroup->m_leftButton->GetPosition().x + this->m_buttonGroup->m_leftButton->GetWidth() / 7, this->m_buttonGroup->m_leftButton->GetPosition().y + this->m_buttonGroup->m_leftButton->GetHeight() /7));
	this->m_buttonGroup->m_rightButton->m_btnTxt.setPosition(sf::Vector2f(this->m_buttonGroup->m_rightButton->GetPosition().x + this->m_buttonGroup->m_rightButton->GetWidth() / 4, this->m_buttonGroup->m_rightButton->GetPosition().y + this->m_buttonGroup->m_rightButton->GetHeight() / 7));
	this->m_buttonGroup->m_leftButton->m_btnTxt.setFont(this->m_assetPool->GetFont("font"));
	this->m_buttonGroup->m_rightButton->m_btnTxt.setFont(this->m_assetPool->GetFont("font"));
	this->m_buttonGroup->m_leftButton->SetBoolRef(m_quitBool);
	this->m_buttonGroup->m_rightButton->SetBoolRef(buttonState);
	
	this->m_widgetGroup = new Widget("PAUSED", sf::Vector2f(250.0f, 150.0f), sf::Vector2f(2.5, 3), m_assetPool->GetTexture("Panel"), true);
	this->m_widgetGroup->m_label.setFont(this->m_assetPool->GetFont("font"));
	this->m_widgetGroup->m_label.setFillColor(sf::Color::White);
	this->m_widgetGroup->SetLabelPos(sf::Vector2f(-80, -200));
	this->m_quitGroup = new Widget("Would you like to quit?", sf::Vector2f(250.0f, 150.0f), sf::Vector2f(2.5, 3), m_assetPool->GetTexture("Panel"), false);
	
	sf::Text txt;
	txt.setFillColor(sf::Color::White);
	txt.setFont(this->m_assetPool->GetFont("font"));
	txt.setString("Video");
	txt.setPosition(561.25, 20.0f);
	this->m_tempText.setString("");
	sf::Text newTxt;
	newTxt.setFillColor(sf::Color::White);
	newTxt.setFont(this->m_assetPool->GetFont("font"));
	newTxt.setString("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");

	this->m_dropDown = new DropDown("Drop Down", sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.7f, 0.3f), txt, m_assetPool->GetTexture("Panel"),true);
	this->m_dropDown->AddSelection(newTxt, "AntiAliasing", m_assetPool->GetTexture("Panel"), sf::Vector2f(0.7f, 0.3f), &m_boolToCheck, true);
	this->m_dropDown->AddSelection(newTxt, "V-Sync", m_assetPool->GetTexture("Panel"), sf::Vector2f(0.7f, 0.3f), &m_boolToCheck,true);
	this->m_dropDown->AddSelection(newTxt, "Motion Blur...eww", m_assetPool->GetTexture("Panel"), sf::Vector2f(0.7f, 0.3f), &m_boolToCheck, true);
	this->m_dropDown->AddSelection(newTxt, "Render Distance", m_assetPool->GetTexture("Panel"), sf::Vector2f(0.7f, 0.3f), &m_boolToCheck, true);
	this->m_dropDown->AddSelection(newTxt, "Aspect Ratio", m_assetPool->GetTexture("Panel"), sf::Vector2f(0.7f, 0.3f), &m_boolToCheck, true);

	this->m_textInput = new TextInput("Text Input", sf::Vector2f(20.0f, 660.0f), sf::Vector2f(1.0f, 0.3f), this->m_assetPool->GetTexture("Panel"),
		this->m_assetPool->GetTexture("Panel"), sf::Vector2f(0.6f, 0.3f), 250, "", true, this->m_assetPool->GetFont("font"), "Enter", sf::Color::White, sf::Color::Cyan, 5);
	this->m_textInput->SetEffectsVal(false);
	this->m_textInput->SetStringRef(this->m_stringToSet);
	//this->m_widgetGroup->AddElement(this->m_textInput, sf::Vector2f(0.2f, 0.2f));

	this->m_textLog = new TextLog("Log", sf::Vector2f(20.0f, 500), sf::Vector2f(1.5f, 1.0f), this->m_assetPool->GetTexture("Panel"), this->m_assetPool->GetFont("font"), sf::Color::White, 10, true, 10, sf::Vector2f(10.0f, 10.0f), 10);

	this->m_quitGroup->AddElement(this->m_buttonGroup, sf::Vector2f(0.35f, 0.43f));

	//this->m_widgetGroup->AddElement(this->m_buttonGroup, sf::Vector2f(0.1f, 0.4f));
	//this->m_widgetGroup->AddElement(this->m_button, sf::Vector2f(0.5f, 0.5f));
	this->m_widgetGroup->AddElement(this->m_slider, sf::Vector2f(0.6f, 0.3f));
	this->m_widgetGroup->AddElement(this->m_volumeSlider, sf::Vector2f(0.6f, 0.7f));
	this->m_widgetGroup->AddElement(this->m_dropDown, sf::Vector2f(0.05f, 0.3f));
	this->m_widgetGroup->AddElement(this->m_pauseButton1, sf::Vector2f(0.37f, 0.3f));
	this->m_widgetGroup->AddElement(this->m_pauseButton2, sf::Vector2f(0.37f, 0.5f));
	this->m_widgetGroup->AddElement(this->m_pauseButton3, sf::Vector2f(0.37f, 0.7f));

	this->m_textLog->AddText(newTxt);
	this->m_textLog->AddText(newTxt);
	this->m_textLog->AddText(newTxt);

	this->m_publisher->AddElement(m_textInput);
	this->m_publisher->AddElement(m_textLog);
	this->m_publisher->AddElement(m_widgetGroup);
	this->m_publisher->AddElement(m_quitGroup);
	this->m_publisher->AddElement(m_button);
	//this->m_publisher->AddElement(m_dropDown);
	//this->m_widgetGroup->SetActivated(false);
	//this->m_quitGroup->SetActivated(false);
}

PoolExample::PoolExample(AssetPool* pool)
{
	this->m_assetPool = pool;
}

void PoolExample::Update(float deltaTime)
{
	this->m_publisher->Update(deltaTime);

	if (buttonState && !m_boolToCheck)
	{
		this->m_button->SetValToSet(false);
		this->m_quitGroup->SetActivated(true);
		this->m_widgetGroup->SetActivated(false);
	}
	if (!buttonState)
	{
		this->m_button->SetValToSet(true);
		this->m_quitGroup->SetActivated(false);
	}
	if (m_boolToCheck && !buttonState)
	{
		this->m_widgetGroup->SetActivated(true);
		this->m_quitGroup->SetActivated(false);
	}
	if (!buttonState && !m_boolToCheck)
	{
		this->m_textInput->SetActivated(true);
		this->m_textLog->SetActivated(true);
	}
	if (!m_boolToCheck)
	{
		this->m_widgetGroup->SetActivated(false);
	}
	if (m_quitBool == true)
		exit(1);
	if (this->m_stringToSet != this->m_prevString)
	{
		sf::Text t;
		t.setString(this->m_stringToSet);
		this->m_textLog->AddText(t);
		this->m_prevString = this->m_stringToSet;
	}
}

void PoolExample::Draw(sf::RenderTexture& txtr)
{
	this->m_publisher->Render(txtr);
}

void PoolExample::ProcessEvents(sf::Event& e, sf::RenderWindow* window)
{
	if (e.key.code == sf::Keyboard::F3 && e.type == sf::Event::KeyPressed)
	{
		if (m_boolToCheck == false)
		{
			m_boolToCheck = true;
			return;
		}
		else if (m_boolToCheck == true)
		{
			m_boolToCheck = false;
			return;
		}
	}
	this->m_publisher->ProcessInput(e, window);
}
