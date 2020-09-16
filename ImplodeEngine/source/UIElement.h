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
	inline sf::Vector2f GetPosition() { return this->m_pos; }
	virtual void UpdatePos(sf::Vector2f position) { this->m_pos = position; }
	inline virtual sf::Vector2f GetOrigin() = 0;
	inline void SetLabelPos(sf::Vector2f offsetPosition) {
		this->m_label.setPosition(sf::Vector2f(GetOrigin().x + offsetPosition.x, GetOrigin().y + offsetPosition.y)); this->m_offsetPos = offsetPosition;
	}
	inline std::string GetType() { return this->m_type; }
	void SetType(std::string type) { this->m_type = type; }
	sf::Text m_label;
	inline bool GetActivated() { return m_enabled; }
	inline void SetActivated(bool activated) { this->m_enabled = activated; }
	inline bool& GetActivatedAddr() { return m_enabled; }
	inline virtual void SetEffectsVal(bool valToSet) { this->m_effectEnabled = valToSet; }
private:
	
protected:
	sf::Vector2f m_pos; 
	sf::Vector2f m_scale;
	sf::Vector2f m_offsetPos;
	std::string m_type;
	bool m_enabled;
	bool m_effectEnabled = true;
};

class Button : public UIElement
{
public:
	Button(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool activated,bool valToSet = true);
	~Button();
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Selected() override;
	void SetButtonText(sf::Text textExample); 
	void SetTexture(sf::Texture& texture);
	void UpdatePos(sf::Vector2f position) override;
	inline sf::Vector2f GetOrigin() override { return sf::Vector2f(((this->m_pos.x + (this->m_buttonSprite.getLocalBounds().width * this->m_scale.x) / 2)), (this->m_pos.y + (this->m_buttonSprite.getLocalBounds().height * this->m_scale.y) / 2)); }
	inline void SetBoolRef(bool& reference) { this->m_boolPtr = &reference; }
	inline void Notify() override { *this->m_boolPtr = m_valToSet;}
	inline void SetValToSet(bool valToSet) { this->m_valToSet = valToSet; }
	inline void SetPos(sf::Vector2f pos) { this->m_pos = pos; }
	inline float GetWidth() { return this->m_buttonSprite.getLocalBounds().width * this->m_scale.x; }
	inline float GetHeight() { return this->m_buttonSprite.getLocalBounds().height * this->m_scale.y; }
	inline bool GetValToSet() { return this->m_valToSet; }
	sf::Text m_btnTxt;
private:
	sf::Sprite m_buttonSprite;
	sf::Color m_initclr;
	bool* m_boolPtr;
	bool m_valToSet = false;
	
protected:
};

class Slider : public UIElement
{
public:
	Slider(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, bool activated);
	void SetTextures(sf::Texture& barTexture, sf::Texture& selectorTexture);
	void Update(float deltaTime)override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override;
	void UpdatePos(sf::Vector2f position) override;
	void Selected() override;
	inline void SetFloatRef(float& reference) { this->m_floatRef = &reference; }
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_pos.x + (this->m_barSprite.getLocalBounds().width / 2)), this->m_pos.y + (this->m_barSprite.getLocalBounds().height / 2));
	}
	sf::Text m_btnTxt;
private:
	sf::Sprite m_barSprite;
	sf::Sprite m_selectorSprt;
	sf::Color m_initBarClr;
	sf::Color m_initSliderClr;
	sf::Vector2f m_selectorScle;
	float* m_floatRef;
	bool m_dragging = false;
protected:
};

class ButtonGroup : public UIElement
{
public:
	ButtonGroup(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, bool orientation, sf::Texture &borderTexture, bool activated);
	~ButtonGroup();
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void SetButtons(sf::Texture& leftTexture, sf::Vector2f scaleLeft,sf::Texture& rightTexture, sf::Vector2f scaleRight);
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_pos.x + (this->m_border.getLocalBounds().width / 2)), this->m_pos.y + (this->m_border.getLocalBounds().height / 2));}
	void UpdatePos(sf::Vector2f position) override;
	inline void SetEffectsVal(bool valToSet)override { this->m_leftButton->SetEffectsVal(valToSet); this->m_rightButton->SetEffectsVal(valToSet);}
	inline void SetBoolRef(bool& ref) {this->m_boolRef = &ref; this->m_leftButton->SetBoolRef(ref), this->m_rightButton->SetBoolRef(ref);}
	Button* m_leftButton; 
	Button* m_rightButton;
private:
	sf::RectangleShape m_border;
	bool m_orientation;
	bool* m_boolRef;
protected:
};

class Widget : public UIElement
{
public:
	Widget(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& widgetTexture, bool activated);
	void Update(float deltaTime) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Render(sf::RenderWindow* window) override;
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_pos.x + (this->m_border.getLocalBounds().width / 2)), this->m_pos.y + (this->m_border.getLocalBounds().height / 2));
	}
	void AddElement(UIElement* element, sf::Vector2f percentagePos);
	std::vector<UIElement*> m_elements;
	void SetActivated(bool activated) { this->m_enabled = activated; for (int i = 0; i < this->m_elements.size(); i++) this->m_elements[i]->SetActivated(activated); }
private:
	sf::RectangleShape m_border;
protected:
};

class DropDown : public UIElement
{
public:
	DropDown(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Text buttonText, sf::Texture& buttonTexture, bool activated);
	~DropDown();
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window)override;
	inline void SetRefVal(int index, bool* ref) { 
		if (index >= 0 && index < this->m_buttons.size())
			this->m_buttons[index]->SetBoolRef(*ref); }
	void AddSelection(sf::Text buttonText,std::string textString, sf::Texture& buttonTexture, sf::Vector2f buttonScale, bool* reference, bool valToSet);
	inline sf::Vector2f GetOrigin() override { 
		return sf::Vector2f(this->m_activatorButton->GetOrigin());
	}
	void UpdatePos(sf::Vector2f position) override;
	inline void SetEffectsVal(bool valToSet) { for (int i = 0; i < this->m_buttons.size(); i++) { this->m_buttons[i]->SetEffectsVal(valToSet); } }
private:
	Button * m_activatorButton;
	std::vector<Button*> m_buttons;
	bool m_dropDwnShw;
protected:
};

class TextInput : public UIElement
{
public:
	TextInput(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& buttonTexture, sf::Texture& textBoxTexture, sf::Vector2f buttonScale, int characterLimit,std::string buttonLabel, bool activated, sf::Font & font,std::string buttonText,sf::Color textColor, sf::Color outlineColor,int outlineThickness);
	~TextInput();
	void Update(float deltaTime) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	void Render(sf::RenderWindow* window) override;
	void UpdatePos(sf::Vector2f position) override;
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f(this->m_textBoxTxtre.getPosition().x + (this->m_textBoxTxtre.getLocalBounds().width / 2),
			this->m_textBoxTxtre.getPosition().y + (this->m_textBoxTxtre.getLocalBounds().height / 2));}
	inline void SetEffectsVal(bool valToSet) { this->m_sndBtn->SetEffectsVal(valToSet); this->m_effectEnabled = valToSet; }
	inline void SetStringRef(std::string& reference) { this->m_str = &reference; }
private:
	void UpdateTextBox(int charTyped);
	void DeleteLastChar();
	void CheckBounds();
	Button* m_sndBtn;
	sf::RectangleShape m_textBoxTxtre;
	sf::Text m_inputTxt;
	std::string m_textStr;
	std::string* m_str;
	std::string m_showStr;
	bool m_focused = false;
	bool m_wasFocused;
	int m_charLim;
	bool m_sndPressed = false;
	int m_outLnThick;
	std::string m_caretVal = "";
	int m_caretPos = 0;
	float m_avgWidth = 0.0f;
	float m_totalChars = 0.0f;
	int m_lowBound;
	int m_highBound;
	sf::Text m_checkText;
protected:
};

class TextLog : public UIElement
{
public:
	TextLog(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Texture& textLogtexture, sf::Font& textFont, sf::Color textColor, int charSize,bool activated, int lineSpacing,sf::Vector2f padding,int textObjLim = 50);
	void AddText(sf::Text text);
	void Update(float deltaTime) override;
	void Render(sf::RenderWindow* window) override;
	void ProcessInput(sf::Event& e, sf::RenderWindow* window) override;
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_sprite.getPosition().x + this->m_sprite.getLocalBounds().width) / 2,
			(this->m_sprite.getPosition().y + this->m_sprite.getLocalBounds().height) / 2);
	}
	void UpdatePos(sf::Vector2f newPos) override;
private:
	sf::RectangleShape m_textLogTexture;
	sf::Text m_text;
	std::vector<sf::Text> m_textList;
	int m_textObjLim;
	sf::RenderTexture m_renderTexture;
	sf::Sprite m_sprite;
	int m_lnSpace;
	int m_scrollAmount = 0;
	int m_maxScrollAmount = 0;
	int m_mouseWheelY = 0;
	int m_scrllSensitivity = 10;
	sf::Vector2f m_padding;
protected:
};

class Publisher
{
public:
	void Update(float deltaTime);
	void Render(sf::RenderWindow* window);
	void ProcessInput(sf::Event& event, sf::RenderWindow* window);
	inline void AddElement(UIElement* element) { this->m_elements.push_back(element); }
private:
	std::vector<UIElement*> m_elements;
protected:
};

