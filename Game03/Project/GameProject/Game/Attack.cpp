#include "Attack.h"
#include "Map.h"
#include "Player.h"
#include"GameData.h"
void Attack::StateIdle()
{
	Base* b = Base::FindObject(eType_Player);
	if (b) {
		m_pos = b->m_pos + CVector2D(-60, -60);
	}
	if (PUSH(CInput::eButton1)) {

		//�U����Ԃֈڍs
		m_state = eState_Attack;
		m_attack_no++;
	}
}

void Attack::StateAttack()
{
	cnt = 30;
	cnt--;
	//Base* b = Base::FindObject(eType_Player);
	m_pos_old = m_pos;
	float l = GameData::s_score;
	if (m_flip) {
		CVector2D vec = CVector2D(10, 0);
		m_pos += vec;
		//m_pos = m_pos_old;
	}
	else {
		CVector2D vec = CVector2D(-10, 0);
		m_pos += vec;
		//m_pos = m_pos_old;
	}
	if (cnt <= 0) {
		cnt = 0;
		m_state = eState_Idle;
	}
}
Attack::Attack(const CVector2D& p, bool flip)
	:Base(eType_Ball)
{
	//�摜����
	m_img = COPY_RESOURCE("ball", CImage);
	m_img.SetSize(64, 64);
	//�Đ��A�j���[�V�����ݒ�
	//m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	m_img.SetCenter(34, 32);
	//���]�t���O
	m_flip = flip;
	m_rect = CRect(-16, -16, 16, 16);
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	cnt = 0;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_attack_no = -1;
}
void Attack::Update()
{
	m_pos_old = m_pos;
	//m_scroll.x = m_pos.x - 1280 / 6;
	//m_scroll.y = m_pos.y - 600;
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	}
	
}
void Attack::Draw()
{
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	DrawRect();
}
void Attack::Collision(Base* b)
{
}
