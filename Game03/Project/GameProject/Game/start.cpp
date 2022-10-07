#include "start.h"
#include "GameData.h"

start::start(const CVector2D& pos) :Base(eType_start)
{
	//�摜����
	m_img = COPY_RESOURCE("start", CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64, 128);
	//���S�ʒu�ݒ�
	m_img.SetCenter(32, 128);
	//�����蔻��p��`
	m_rect = CRect(-32, -128, 32, 0);
}

void start::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();

}

void start::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			//GameData::s_score += 1;
			SetKill();
			Gstart = true;
		}
		break;
	}
}