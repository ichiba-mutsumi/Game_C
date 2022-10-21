#pragma once
#include<GLLibrary.h>
//�d�͉����x
#define GRAVITY (9.8f/20)

enum {
	eType_Scene,
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Flame,
	eType_Enemy1,
	eType_Enemy2,
	eType_Enemy3,
	eType_Enemy4,
	eType_Enemy5,
	eType_Enemy6,
	eType_Enemy7,
	eType_Enemy8,
	eType_Enemy9,	eType_Bullet,
	eType_Goal,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
	eType_AtkEffect,
	eType_UI,
	eType_Item,

	eType_start,
	eType_Goal2,
};

class Base {
public:
	//���W�f�[�^
	CVector2D m_pos;
	CVector2D m_pos_old;
	static std::list<Base*> m_list;
	//�I�u�W�F�N�g�̎��
	int m_type;
	//���a
	float m_rad;
	//�ړ��x�N�g��
	CVector2D m_vec;
	//��]�l
	float m_ang;
	//�X�N���[���l
	static CVector2D m_scroll;

	bool m_kill;
	Base* Base::FindObject(int type);
	//��`
	CRect m_rect;


public:
	//type�I�u�W�F�N�g�̎��
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//�폜�t���OON
	void SetKill() { m_kill = true; }
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g�̓�����̔��茟��
	static void CollisionAll();
	//�I�u�W�F�N�g�̒ǉ�
	static void Add(Base*b);
	//�S�I�u�W�F�N�g�̍폜
	static void KillAll();
	//�~���m�̏Փ�
	static bool CollisionCircle(Base* b1, Base* b2);
	//�폜�`�F�b�N
	static void CheckKillAll();
	
	//type�̃I�u�W�F�N�g��T���i�����j
	static std::list<Base*> FindObjects(int type);

	static CVector2D GetScreenPos(const CVector2D& pos);

	//��`���m�̔���
	static bool CollisionRect(Base* b1, Base* b2);
	//��`�̕\��
	void DrawRect();
};


