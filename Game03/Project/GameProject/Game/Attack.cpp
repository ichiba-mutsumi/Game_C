#include "Attack.h"
#include "Map.h"
#include "Player.h"
#include"GameData.h"
#include"Effect_Ring.h"
void Attack::StateIdle()
{
	Ccnt++;
	if (Ccnt >= 120) {
		Ccnt = 120;
	}
	m_img.UpdateAnimation();
	m_img.SetSize(32, 8);
	m_img.SetCenter(16, 4);
	m_rect = CRect(0, 0, 0, 0);
	Base* b = Base::FindObject(eType_Player);
	if (!HOLD(CInput::eButton1)) {
		//�U����Ԃֈڍs
		
		
		if (Ccnt < 60){
			m_state = eState_Attack;
		}
		else if(Ccnt >= 60 && Ccnt <= 119) 
		{
			m_state = eState_Attack2;
		}
		else if (Ccnt == 120)
		{
			m_state = eState_Attack3;
		}
		
	}
	if (HOLD(CInput::eLeft)) {
		//���]�t���O
		m_flip = false;
	}
	//�E�ړ�
	if (HOLD(CInput::eRight)) {
		//���]�t���O
		m_flip = true;
	}
	
	if (b) {
		if (m_flip) {
			m_pos = b->m_pos + CVector2D(+60, -75);
		}
		else {
			m_pos = b->m_pos + CVector2D(-60, -75);
		}
	}
}

void Attack::StateAttack()
{
	m_img.UpdateAnimation();
	m_img.SetSize(128, 32);
	m_img.SetCenter(64, 16);
	cnt--;
	m_rect = CRect(-16, -16*2, 16, 16*2);	
	if (m_flip) {
		CVector2D vec = CVector2D(10, 0);
		m_pos += vec;
	}
	else {
		CVector2D vec = CVector2D(10, 0);
		m_pos -= vec;
	}
	if (cnt <= 0) {
		SetKill();
	}
}

void Attack::StateAttack2()
{
	m_img.UpdateAnimation();
	m_img.SetSize(16 * 2, 144);
	//m_img.SetAng(DtoR(90));
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	m_pos = f->GetPos() + CVector2D(0, -20);
	//m_img.SetCenter(128, 0);
	cnt--;
	if (cnt == 59) {
		//Base::Add(new Effect_Ring("Effect_Ring2", m_pos + CVector2D(60, 0), m_flip, m_ang));
		m_rect = CRect(-16 * 7, -16 * 2, 16 * 7, 16 * 2);
		
	}
	if (cnt == 30) {
		m_rect = CRect(-16 * 10, -16 * 2, 16 * 10, 16 * 2);
	}
	if (cnt <= 0) {
		SetKill();
	}
}

void Attack::StateAttack3()
{
	m_img.UpdateAnimation();
	m_img.SetSize(128, 32);
	m_img.SetCenter(64, 16);
	cnt--;
	m_rect = CRect(-16, -16 * 2, 16, 16 * 2);
	if (m_flip) {
		CVector2D vec = CVector2D(10, 0);
		m_pos += vec;
		m_img.SetSize(128 * 3, 32 * 2);
	}
	else {
		CVector2D vec = CVector2D(10, 0);
		m_pos -= vec;
		m_img.SetSize(128 * 3, 32 * 2);
	}
	if (cnt <= 0) {
		SetKill();
	}
}

Attack::Attack(const CVector2D& p, bool flip,int type,int attack_no)
	:Base(eType_Flame)
{
	//�摜����
	m_img = COPY_RESOURCE("Effect_Flame", CImage);
	//m_img.SetSize(128, 32);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//���S�ʒu�ݒ�
	//m_img.SetCenter(64, 16);
	//���]�t���O
	m_flip = flip;

	//m_rect = CRect(-16, -16, 16, 16);
	//�ʏ��Ԃ�
	m_state = eState_Idle;
	//�e���Ŏ���
	cnt = 60;
	//���ߎ���
	Ccnt = 0;
	//�U���ԍ�
	m_attack_no = rand();
	//�_���[�W�ԍ�
	m_damage_no = -1;
	m_attack_no = attack_no;
	//Player���]�t���O�擾
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	m_flip = f->GetFlipFlag();
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
	case eState_Attack2:
		StateAttack2();
		break;
	case eState_Attack3:
		StateAttack3();
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
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			int t = m->CollisionMap(m_pos, m_rect);
			if (t != 0)
				m_vec = CVector2D(sin(m_ang) * -1, cos(m_ang));
		}
		break;
	//case eType_Enemy:
		//SetKill();

	}
}
