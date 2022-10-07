#pragma once
#include"../Base/Base.h"

class Attack : public Base {
	
	
private:
//���
enum {
	eState_Idle,
	eState_Attack,
	


};

//��ԕϐ�
int m_state;

CImage m_img;
//���]�t���O
bool m_flip;
int cnt;
//�U���ԍ�
int m_attack_no;
//�_���[�W�ԍ�
int m_damage_no;
//�e��Ԃł̋���
void StateIdle();
void StateAttack();


public:
	Attack(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	
};
