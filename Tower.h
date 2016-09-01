#include "GameObject.h"
 
class Tower: GameObject{
	public:

	Tower();
	virtual ~Tower();

	virtual void update();
	virtual void shoot();
		
	float rotation;
	float cooldown;
	float range;
	int price;
};
