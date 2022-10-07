#pragma once
#include"../Base/Base.h"

class Enemy :public Base {
public:
	CImage m_img;
	bool m_flip;
	bool m_down;
	int hp;
public:
	Enemy(const CVector2D& p, bool flip ,int type);
	void Update();
	void Draw();
	void Collision(Base* b);
};