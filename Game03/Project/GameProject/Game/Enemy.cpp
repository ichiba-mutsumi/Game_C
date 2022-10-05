#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Effect.h"
#include "GameData.h"

Enemy::Enemy(const CVector2D& p, bool flip):
Base(eType_Enemy) {
	
	//�摜����
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.SetSize(96, 96);
	//�����蔻��p��`�ݒ�
	m_rect = CRect(-32, -64, 32, 0);
	//�Đ��A�j���[�V�����ݒ�
	m_img.ChangeAnimation(0);
	//���]�t���O
	m_flip = flip;
	//���S�ʒu�ݒ�
	m_img.SetCenter(48, 96);
	//���W�ݒ�
	m_pos_old = m_pos = p;
	//m_down = false;
	
}

void Enemy::Update()
{
	m_pos_old = m_pos;
	m_pos.x--;
	//�A�j���[�V�����X�V
	m_img.UpdateAnimation();
	//�d�͂ɂ�闎��
	m_vec.y += GRAVITY;
	
	

}

void Enemy::Draw()
{
	//�ʒu�ݒ�
	m_img.SetPos(GetScreenPos(m_pos));
	//���]�ݒ�
	m_img.SetFlipH(m_flip);
	//�`��
	m_img.Draw();
	//�����蔻���`�̕\��
	DrawRect();
}

void Enemy::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			m_img.ChangeAnimation(eAnimDown);
			//m_down = true;
			SetKill();
		Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, -128), m_flip));
		}
		break;
	}
}

