#pragma once
#include"../Base/Base.h"
 
class Attack :public Base {
	CImage m_img;
	float m_speed;
public:
	Attack(int type, const CVector2D& pos, float ang, float speed);
    void Update();
	void Draw();
	void Collision(Base* b);
};