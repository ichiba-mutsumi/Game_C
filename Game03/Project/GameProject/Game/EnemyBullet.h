#pragma once
#include"../Base/Base.h"

class EnemyBullet :public Base {
	CImage m_img;
	float m_speed;
	int cnt;
public:
	EnemyBullet(int type, const CVector2D& pos, float ang, float speed);
	void Update();
	void Draw();
	void Collision(Base*b);
};
