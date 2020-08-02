#pragma once

class UIElement
{
public:
	UIElement() {};
	UIElement(std::string text, sf::Vector2f elementPos, sf::Vector2f scale);
	inline virtual void Update(float deltaTime, bool notified,sf::Vector2f mousePos) { ; }
	inline virtual void Render(sf::RenderWindow* window) { ; }
	inline virtual void Notify() { ; }
	inline virtual void Selected() { ; }
	inline sf::Vector2f GetPosition() { return this->m_position; }
	virtual void UpdatePosition(sf::Vector2f position) { ; }
	inline virtual sf::Vector2f GetOrigin() = 0;
	inline void SetLabelPos(sf::Vector2f offsetPosition) {
		this->m_label.setPosition(sf::Vector2f(GetOrigin().x + offsetPosition.x, GetOrigin().y + offsetPosition.y)); this->m_offsetPosition = offsetPosition;
	}
	sf::Text m_label;
private:
	
protected:
	sf::Vector2f m_position; 
	sf::Vector2f m_scale; 
	sf::Vector2f m_offsetPosition;
};

class Button : public UIElement
{
public:
	Button(bool& reference);
	Button(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, bool &reference, bool valToSet = false);

	void Update(float deltaTime, bool notified, sf::Vector2f mousePos) override;
	void Render(sf::RenderWindow* window) override;
	void Selected() override;
	void SetButtonText(sf::Text textExample); 
	void SetTexture(sf::Texture& texture);
	inline void UpdatePosition(sf::Vector2f position) override { this->m_position = position; this->m_label.setPosition(sf::Vector2f(this->m_offsetPosition.x + GetOrigin().x, this->m_offsetPosition.y + GetOrigin().y)); }
	inline sf::Vector2f GetOrigin() override { return sf::Vector2f(((this->m_position.x + (this->m_buttonSprite.getLocalBounds().width * this->m_scale.x) / 2)), (this->m_position.y + (this->m_buttonSprite.getLocalBounds().height * this->m_scale.y) / 2)); }
	inline void SetBoolRef(bool& reference) { this->m_boolRef = reference; }
	inline void Notify() override { this->m_boolRef = m_valToSet; }
	inline void SetValToSet(bool valToSet) { this->m_valToSet = valToSet; }
	inline void SetPos(sf::Vector2f pos) { this->m_position = pos; }
	inline float GetWidth() { return this->m_buttonSprite.getLocalBounds().width * this->m_scale.x; }
	inline float GetHeight() { return this->m_buttonSprite.getLocalBounds().height * this->m_scale.y; }
	
	sf::Text m_buttonText;
private:
	sf::Sprite m_buttonSprite;
	sf::Color m_initialColor;
	bool& m_boolRef; 
	bool m_valToSet = false;
protected:
};

class Slider : public UIElement
{
public:
	Slider(std::string text, sf::Vector2f elementPos, sf::Vector2f scale, sf::Vector2f selectorScale, float& reference);

	void SetTextures(sf::Texture& barTexture, sf::Texture& selectorTexture);
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos)override;
	void Render(sf::RenderWindow* window) override;
	void Notify() override;
	void Selected() override;
	inline void SetFloatRef(float& reference) { this->m_floatRef = reference; }
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_position.x + (this->m_barSprite.getLocalBounds().width / 2)), this->m_position.y + (this->m_barSprite.getLocalBounds().height / 2));
	}
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
	ButtonGroup(std::string text,sf::Vector2f elementPos, sf::Vector2f scale, float orientation, bool& reference, sf::Texture &borderTexture);
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos) override;
	void Render(sf::RenderWindow* window) override;
	void SetButtons(sf::Texture& leftTexture, sf::Vector2f scaleLeft,sf::Texture& rightTexture, sf::Vector2f scaleRight);
	inline sf::Vector2f GetOrigin() override {
		return sf::Vector2f((this->m_position.x + (this->m_border.getLocalBounds().width / 2)), this->m_position.y + (this->m_border.getLocalBounds().height / 2));}
	Button* m_leftButton; 
	Button* m_rightButton;
private:
	sf::RectangleShape m_border;
	float m_orientation;
	bool& m_boolRef;
protected:
};

class Publisher
{
public:
	void Update(float deltaTime, bool notified, sf::Vector2f mousePos);
	void Render(sf::RenderWindow* window);

	inline void AddElement(UIElement* element) { this->m_elements.push_back(element); }
private:
	std::vector<UIElement*> m_elements;
protected:
};

