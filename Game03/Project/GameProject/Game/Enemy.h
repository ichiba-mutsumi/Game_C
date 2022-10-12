#pragma once
#include"../Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Down,
		eState_Damage,

	};
	int m_state;

	CImage m_img;
	bool m_flip;
	bool m_down;
	bool m_is_ground;
	int m_damage_no;
	int hp;
	int cnt;
	void StateIdle();
	void StateDamage();
	void StateDown();
public:
	Enemy(const CVector2D& p, bool flip ,int type);
	void Update();
	void Draw();
	void Collision(Base* b);
};