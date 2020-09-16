#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"

class UIPool
{
public:
	UIPool();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderTexture & txtr) = 0;
	virtual void ProcessEvents(sf::Event& e, sf::RenderWindow* window) = 0;
	//UI Elements
private:
protected:
	AssetPool* m_assetPool;
	Publisher* m_publisher;
};