#pragma once
#include"../Base/Base.h"

class Enemy :public Base {
private:
	enum {
		eState_Idle,
		eState_Down,
		eState_Damage,
		eState_Attack,
		eState_Wait,


	};
	int m_state;

	CImage m_img;
	bool m_flip;
	bool m_down;
	bool m_is_ground;
	int m_damage_no;
	int m_attack_no;
	int hp;
	int cnt;
	int bcnt;
	int EnemyType;
	
	CVector2D v;
	//Šeó‘Ô‚Å‚Ì‹““®
	void StateIdle(int type);
	void StateDamage(int type);
	void StateDown(int type);
	void StateAttack(int type);
	void StateWait(int type);
public:
	Enemy(const CVector2D& p, bool flip ,int type);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
};