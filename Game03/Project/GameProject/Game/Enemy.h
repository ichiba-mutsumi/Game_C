#pragma once
#include"../Base/Base.h"

class Enemy :public Base {
public:
	CImage m_img;
	bool m_flip;
	bool m_down;
public:
	Enemy(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
};