#include "Effect_Ring.h"
#include"Player.h"

Effect_Ring::Effect_Ring(const char* name, const CVector2D& pos, bool flip) :
	Base(eType_AtkEffect)
{
	//�摜����
	m_img = COPY_RESOURCE(name, CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(16*2, 144);
	//m_img.SetSize(3600, 1440);
	//���S�ʒu�ݒ�
	m_img.SetCenter(16, 40*2);
	//�Đ��A�j���[�V�����ݒ�(�񃋁[�v)
	m_img.ChangeAnimation(0, false);
	//���]�t���O
	m_flip = flip;
	
}

void Effect_Ring::Update()
{
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�A�j���[�V�����I���`�F�b�N
	if (m_img.CheckAnimationEnd()|| !HOLD(CInput::eButton1)) {
		//�G�t�F�N�g���폜
		SetKill();
	}
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	m_flip = f->GetFlipFlag();
	if (m_flip) {
		m_pos = f->GetPos() + CVector2D(+60, -70);
	}
	else {
		m_pos = f->GetPos() + CVector2D(-60, -70);
	}
}

void Effect_Ring::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
