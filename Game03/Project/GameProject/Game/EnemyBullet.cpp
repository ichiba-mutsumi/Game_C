#include "EnemyBullet.h"
#include "Map.h"
#include "Effect_Ring.h"
#include "Player.h"
EnemyBullet::EnemyBullet(int type, const CVector2D& pos, float ang, float speed)
	:Base(eType_Bullet){
	
	m_rect = CRect(-16, -16, 16, 16);
	m_img = COPY_RESOURCE("ball", CImage);
	m_pos = pos;
	m_img.SetCenter(8, 8);
	m_ang = ang;
	m_speed = speed;
	cnt = 0;
}
void EnemyBullet::Update(){
	cnt++;
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	if (b) {
		CVector2D Plpos = f->GetPos();
		CVector2D diff = Plpos - m_pos;
		m_ang = atan2(diff.x, diff.y);
		m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
		m_pos += m_vec;
		if (cnt >= 180) {
			SetKill();
		}
	}
}
void EnemyBullet::Draw(){
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetAng(m_ang);
	m_img.Draw();
}
void EnemyBullet::Collision(Base* b){
	switch (b->m_type) {
		
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			//const CVector2D& pos, const CRect& rect
			int t = m->CollisionMap(m_pos,m_rect);
			if (t != 0)
				m_vec = CVector2D(sin(m_ang) * -1, cos(m_ang));
		}
		break;
	case eType_Player:
		if (Base::CollisionCircle(this, b)) {
			
		}
		break;
		/*
	case eType_Enemy:
		if (m_type == eType_Player_Bullet && Base::CollisionCircle(this, b)) {
			SetKill();
			b->SetKill();
		}
		break;*/
	}
}
