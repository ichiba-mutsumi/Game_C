#include "Goal.h"

Goal::Goal(const CVector2D& pos) :Base(eType_Goal)
{
	//画像複製
	m_img = COPY_RESOURCE("Goal", CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(64, 128);
	//中心位置設定
	m_img.SetCenter(32,128);
	//当たり判定用矩形
	m_rect = CRect(-32, -128, 32, 0);
}

void Goal::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.Draw();
	DrawRect();

}

void Goal::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			b->SetKill();
		}
		break;
	}
}
