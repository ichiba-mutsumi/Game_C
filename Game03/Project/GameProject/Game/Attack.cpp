#include "Attack.h"
#include "Map.h"

Attack::Attack(int type, const CVector2D& pos, float ang, float speed):Base(type)
{
	m_img = COPY_RESOURCE("ball", CImage);
	m_pos = pos;
	m_img.SetCenter(16, 16);
	m_ang = ang;
	m_speed = speed;
}

void Attack::Update()
{
	m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
	m_pos += m_vec;
}

void Attack::Draw()
{
	m_img.SetPos(m_pos);
	m_img.SetAng(m_ang);
	m_img.Draw();
}

void Attack::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Enemy:
		if (m_type == eType_Player && Base::CollisionCircle(this, b)) {
			//SetKill();
			b->SetKill();
		}
		break;
	}
}
