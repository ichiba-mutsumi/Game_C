#include "Item.h"
#include "GameData.h"

Item::Item(const CVector2D& pos) :Base(eType_Item)
{
	//�摜����
	m_img = COPY_RESOURCE("Goal", CImage);
	//���W�ݒ�
	m_pos = pos;
	//�\���T�C�Y�ݒ�
	m_img.SetSize(64, 128);
	//���S�ʒu�ݒ�
	m_img.SetCenter(32, 128);
	//�����蔻��p��`
	m_rect = CRect(-32, -128, 32, 0);

}

void Item::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();
}

void Item::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			GameData::s_score += 1;
			SetKill();
		}
	break;
	}
}

void Item::Update()
{
	

	
}
