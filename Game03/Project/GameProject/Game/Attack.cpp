#include "Attack.h"
#include "Map.h"
#include "Player.h"
#include"GameData.h"
#include"Effect_Ring.h"
void Attack::StateIdle()
{
	Ccnt--;
	if (Ccnt <= 0) {
		Ccnt = 0;
	}
	m_img.UpdateAnimation();
	m_img.SetSize(32, 8);
	m_img.SetCenter(16, 4);
	m_rect = CRect(0, 0, 0, 0);
	Base* b = Base::FindObject(eType_Player);
	if (!HOLD(CInput::eButton1)) {
		//攻撃状態へ移行
		m_state = eState_Attack;
	}
	if (HOLD(CInput::eLeft)) {
		//反転フラグ
		m_flip = false;
	}
	//右移動
	if (HOLD(CInput::eRight)) {
		//反転フラグ
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
		//Base::Add(new Effect_Ring("Effect_Ring", m_pos + CVector2D(+60, 0), true));
		m_pos += vec;
		if (Ccnt < 60) {
			m_img.SetSize(128 * 2, 32 * 2);
		}
	}
	else {
		CVector2D vec = CVector2D(10, 0);
		//Base::Add(new Effect_Ring("Effect_Ring", m_pos + CVector2D(-60, 0), false));
		m_pos -= vec;
		if (Ccnt < 60) {
			m_img.SetSize(128 * 2, 32 * 2);
		}
	}
	if (cnt <= 0) {
		SetKill();
	}
}

Attack::Attack(const CVector2D& p, bool flip,int type,int attack_no)
	:Base(eType_Flame)
{
	//画像複製
	m_img = COPY_RESOURCE("Effect_Flame", CImage);
	//m_img.SetSize(128, 32);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	//m_img.SetCenter(64, 16);
	//反転フラグ
	m_flip = flip;
	//m_rect = CRect(-16, -16, 16, 16);
	//通常状態へ
	m_state = eState_Idle;
	//弾消滅時間
	cnt = 60;
	//溜め時間
	Ccnt = 120;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
	m_damage_no = -1;
	m_attack_no = attack_no;
	//Player反転フラグ取得
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
	}


	
}
void Attack::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
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
