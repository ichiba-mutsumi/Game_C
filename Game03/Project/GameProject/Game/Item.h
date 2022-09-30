#pragma once
#include "../Base/Base.h"

class Item :public Base {
private:
	//画像オブジェクト
	CImage m_img;
public:
	Item(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
};
