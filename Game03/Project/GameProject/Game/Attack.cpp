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

		//攻撃状態へ移行
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
	//画像複製
	m_img = COPY_RESOURCE("ball", CImage);
	m_img.SetSize(64, 64);
	//再生アニメーション設定
	//m_img.ChangeAnimation(0);
	//座標設定
	m_pos_old = m_pos = p;
	//中心位置設定
	m_img.SetCenter(34, 32);
	//反転フラグ
	m_flip = flip;
	m_rect = CRect(-16, -16, 16, 16);
	//通常状態へ
	m_state = eState_Idle;
	cnt = 0;
	//攻撃番号
	m_attack_no = rand();
	//ダメージ番号
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
}
