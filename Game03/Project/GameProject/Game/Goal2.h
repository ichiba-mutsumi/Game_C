#pragma once
#include "../Base/Base.h"

class Goal2 :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
public:
	bool Ggoal2;
	Goal2(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
};
