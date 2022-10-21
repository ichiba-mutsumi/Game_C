#pragma once
#include"../Base/Base.h"

class Attack : public Base {
	
	
private:
//���
enum {
	eState_Idle,
	eState_Attack,
	eState_Attack2,
	eState_Attack3,

};

//��ԕϐ�
int m_state;

CImage m_img;
//���]�t���O
bool m_flip;
//�e���Ŏ���
int cnt;
//���ߎ���(120)
int Ccnt;
//�U���ԍ�
int m_attack_no;
//�_���[�W�ԍ�
int m_damage_no;
//�e��Ԃł̋���
void StateIdle();
void StateAttack();
void StateAttack2();
void StateAttack3();

public:
	Attack(const CVector2D& p, bool flip,int type,int attack_no);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetAttackNo() {
		return m_attack_no;
	}
	
};
