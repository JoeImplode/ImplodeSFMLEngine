#include "Animation.h"
#include "AssetPool.h"
#include "UIElement.h"

class UIPool
{
public:
	UIPool();
	inline void SetAssetPool(AssetPool pool) { *this->m_assetPool = pool; }
	void Update(float deltaTime);
	void Draw(sf::RenderWindow* window) ;
	void ProcessEvents(sf::Event& e, sf::RenderWindow* window);

	//UI Elements
private:
	AssetPool* m_assetPool;
	Publisher* m_publisher;
protected:
};