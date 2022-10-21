#include "Player.h"
#include "AnimData.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"
#include "Game.h"
#include "Enemy.h"
#include "Map.h"
#include "Item.h"
#include "../Base/Base.h"
#include "../Title/Title.h"
#include "../Game/Attack.h"
#include "Effect_Ring.h" 
#include <iostream>

Player::Player(const CVector2D& p, bool flip) :
	Base(eType_Player) {
	//�摜����
	m_img = COPY_RESOURCE("Player", CImage);
	m_img.SetSize(224, 224);

	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(112, 192);
	//���]�t���O
	m_flip = flip;
	//�����蔻��
	m_rect = CRect(-28, -124, 28, 0);
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//���n�t���O
	m_is_ground = true;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
    m_damage_no = -1;
	//���ߎ���
	Ccnt = 120;
	//�q�b�g�|�C���g
	m_hp = 500;
	//�v���C���[�ړ���
	CVector2D ver(0, 0);
	//�J�����ړ���
	CVector2D sc_ver(0, 0);
	//�����X�N���[���ݒ�
	
	
	/*
	m_img.SetSize(224 / 2, 224 / 2);
	m_img.SetCenter(112 / 2, 192 / 2);
	m_rect = CRect(-28 / 2, -124 / 2, 28 / 2, 0);*/
}

void Player::Update() {

	//std::cout << "Player" << std::endl;
	m_pos_old = m_pos;
	
	//�ҋ@�A�j���[�V����
	//m_img.ChangeAnimation(eAnimIdle);
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�X�N���[���ݒ�
	//m_scroll.x = m_pos.x - 1280 / 6;
	//m_scroll.y = m_pos.y - 500;
	switch (m_state) {
		//�ʏ���
	case eState_Idle:
		StateIdle();
		break;
		//�U�����
	case eState_Attack:
		StateAttack();
		break;
		//�_���[�W���
	case eState_Damage:
		StateDamage();
		break;
		//�_�E�����
	case eState_Down:
		StateDown();
		break;
	}
	if (HOLD(CInput::eButton1)) {
		Ccnt--;
		if (Ccnt <= 0)
		{
			Ccnt = 0;
		}
	}

	//�X�N���[���␳
	//�ڕW�l
	CVector2D v3(0, 0);
	//�����Ă����痎������Ԃֈڍs
	if (m_is_ground && m_vec.y > GRAVITY * 4) {
		m_is_ground = false;
		
		//sc_ver.y += scroll_speed_add;
	}
	
	if (m_vec.y > GRAVITY * 4 || m_vec.y < -1)
	{
		v3.y = 300;
	}
	else 
	{
		v3.y = 0;
	}
	if (m_flip) {
		v3.x = -300;
	}
	else 
	{
		v3.x = +300;
	}
	
	CVector2D v2 = v3 - sc_ver;
	//�X�N���[�������x
	sc_ver += v2 * 0.05;
	//��l+�␳�l
	m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
	m_scroll.y = m_pos.y - 600 + sc_ver.y;

	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	m_pos += m_vec;
}

void Player::Draw() {
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	DrawRect();
	
}
void Player::Collision(Base* b)
{
	switch (b->m_type) {
		//�S�[������
	case eType_Goal:
		 eType_Item:
	if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;

	
		//Field�^�փL���X�g�A�^�ϊ��ł�����
		/*if (Field* f = dynamic_cast<Field*>(b)) {
			//�n�ʂ�艺�ɂ�������
			if (m_pos.y > f->GetGroundY()) {
				//�n�ʂ̍����ɖ߂�
				m_pos.y = f->GetGroundY();
				//�������x���Z�b�g
				m_vec.y = 0;
				//�ڒn�t���OON
				m_is_ground = true;

			}
		}
		break;
		*/
	case eType_Enemy_Attack:
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
		
	case eType_Enemy:
		if (Enemy* e = dynamic_cast<Enemy*>(b)) {
			if (m_damage_no != e->GetAttackNo() && Base::CollisionRect(this, e)) {
				m_damage_no = e->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
				Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
			}
		}
		break;
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t != 0)
				m_pos.x = m_pos_old.x;
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y = 0;
				m_is_ground = true;
				//��l+�␳�l
				//m_scroll.x = m_pos.x - 1280 / 2 + sc_ver.x;
				//m_scroll.y = m_pos.y - 500 + sc_ver.y;
			}
		}
		break;
	}
}

void Player::StateIdle()
{
	Ccnt = 120;
	//�ő呬�x
	const float move_speed_max = 12;
	//�����x
	const float move_speed_add = 0.5f;
	//�W�����v��
	const float jump_pow = 20;
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		ver.x -= move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;*/
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		ver.x += move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;*/
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	if (HOLD(CInput::eButton1)) {
		m_state = eState_Attack;
		m_attack_no++;
	}
	
	if (ver.x < -move_speed_max) {
		ver.x = -move_speed_max;
	}
	if (ver.x > move_speed_max) {
		ver.x = move_speed_max;
	}
	m_pos.x += ver.x;
	/*
	//�U��
	if (HOLD(CInput::eButton1)) {
		Base* b = Base::FindObject(eType_Ball);
		if (!b) {
			Base::Add(new Attack(CVector2D(1280, 560), m_flip, eType_Ball, m_attack_no));
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
		
		else if (!b && !m_flip) {

			Base::Add(new Attack(CVector2D(1280, 560), true, eType_Ball,m_attack_no));
		}
		//�U����Ԃֈڍs
		//m_state = eState_Attack;
		//m_attack_no++;
	}*/
	
	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpUp, false);
		else
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimJumpDown, false);
	}
	//�ړ����Ȃ�
	else {
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimRun);
		}
		else {
			ver.x = 0;
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimIdle);
		}
	}	
	
}

void Player::StateAttack()
{
	//�ő呬�x
	const float move_speed_max = 12;
	//�����x
	const float move_speed_add = 0.5f;
	//�W�����v��
	const float jump_pow = 20;
	//�ړ��t���O
	bool move_flag = false;
	//���ړ�
	if (HOLD(CInput::eLeft)) {
		ver.x -= move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += -move_speed;*/
		//���]�t���O
		m_flip = true;
		move_flag = true;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		ver.x += move_speed_add;
		/*
		//�ړ��ʂ�ݒ�
		m_pos.x += move_speed;*/
		//���]�t���O
		m_flip = false;
		move_flag = true;
	}
	//�W�����v
	if (m_is_ground && PUSH(CInput::eButton2)) {
		m_vec.y = -jump_pow;
		m_is_ground = false;
	}
	if (HOLD(CInput::eButton1)) {
		m_state = eState_Attack;
		m_attack_no++;
	}
	if (ver.x < -move_speed_max) {
		ver.x = -move_speed_max;
	}
	if (ver.x > move_speed_max) {
		ver.x = move_speed_max;
	}
	m_pos.x += ver.x;

	if (HOLD(CInput::eButton1)) {
		Base* b = Base::FindObject(eType_Flame);
		if (!b) {
			Base::Add(new Attack(CVector2D(1280, 560), m_flip, eType_Flame, m_attack_no));
			Base::Add(new Effect_Ring("Effect_Ring", m_pos, m_flip, m_ang));
			
		}
		if (Ccnt == 60)
		{
			Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip, m_ang));	
		}
		/*
		if (Ccnt <= 60 && Ccnt > 0) {
			Attack2 = true;
		}*/
	}
		/*
		if (!b && m_flip)
		{
			Base::Add(new Attack(CVector2D(1280, 560), m_flip, eType_Ball, m_attack_no));
			Base::Add(new Effect_Ring("Effect_Ring", m_pos, m_flip));
			if (Ccnt > 60) {
				Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip));
			}
		}
		else if (!b && !m_flip)
		{
			Base::Add(new Attack(CVector2D(1280, 560), true, eType_Ball, m_attack_no));
			Base::Add(new Effect_Ring("Effect_Ring", m_pos, m_flip));
			if (Ccnt > 60) {
				Base::Add(new Effect_Ring("Effect_Ring2", m_pos, m_flip));
			}
		}*/
	else 
	{
		m_state = eState_Idle;
	}
		//�U����Ԃֈڍs
		//m_state = eState_Attack;
		//m_attack_no++;
	
	
	//m_img.ChangeAnimation()
	/*
	//�U���A�j���[�V�����֕ύX
	m_img.ChangeAnimation(eAnimAttack01, false);
	//3�Ԗڂ̃p�^�[���Ȃ�
	if (m_img.GetIndex() == 3) {
		if (m_flip) {
			
		}
		else {

		}
	}
	//�A�j���[�V�������I��������
	if (m_img.CheckAnimationEnd()) {
		//�ʏ��Ԃֈڍs
		m_state = eState_Idle;
	}
	*/
	//�W�����v���Ȃ�
	if (!m_is_ground) {
		if (m_vec.y < 0)
			//�㏸�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkJumpUp, false);
		else
			//���~�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkJumpDown, false);
	}
	//�ړ����Ȃ�
	else {
		if (move_flag) {
			//����A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkRun);
		}
		else {
			ver.x = 0;
			//�ҋ@�A�j���[�V����
			m_img.ChangeAnimation(eAnimAtkIdle);
		}
	}
}
void Player::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);

	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}
}
void Player::StateDown()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_kill = true;
	}
}





