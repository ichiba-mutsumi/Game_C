#pragma once
#include"../Base/Base.h"

class Attack : public Base {
	
	
private:
//状態
enum {
	eState_Idle,
	eState_Attack,
	


};

//状態変数
int m_state;

CImage m_img;
//反転フラグ
bool m_flip;
int cnt;
//攻撃番号
int m_attack_no;
//ダメージ番号
int m_damage_no;
//各状態での挙動
void StateIdle();
void StateAttack();


public:
	Attack(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	
};
