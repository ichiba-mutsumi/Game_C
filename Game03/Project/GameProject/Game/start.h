#pragma once
#include "../Base/Base.h"

class start :public Base {
private:
	//�摜�I�u�W�F�N�g
	CImage m_img;
public:
	bool Gstart;
	start(const CVector2D& pos);
	void Draw();
	void Collision(Base* b);
};
