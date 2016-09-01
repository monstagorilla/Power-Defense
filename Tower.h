#include "GameObject.h"
 
class Tower: public GameObject{
	public:

	Tower();
	~Tower();

	virtual void update();
	virtual void shoot();
		
	float rotation;
	float cooldown;
	float range;
	int price;
};
