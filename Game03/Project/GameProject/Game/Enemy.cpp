#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Effect.h"
#include "GameData.h"

Enemy::Enemy(const CVector2D& p, bool flip):
Base(eType_Enemy) {
	
	//画像複製
	m_img = COPY_RESOURCE("Enemy", CImage);
	m_img.SetSize(96, 96);
	//当たり判定用矩形設定
	m_rect = CRect(-32, -64, 32, 0);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//反転フラグ
	m_flip = flip;
	//中心位置設定
	m_img.SetCenter(48, 96);
	//座標設定
	m_pos_old = m_pos = p;
	m_down = false;
}

void Enemy::Update()
{
	m_pos_old = m_pos;
	m_pos.x--;
	
	//重力による落下
	m_vec.y += GRAVITY;
	
	
	int i = 0;
	/*
	while (m_down && i < 3000) {
		int s = i % 60;
		m_img.SetAng(s);
		
		i++;
		
	}*/
	
	//アニメーション更新
	m_img.UpdateAnimation();
}

void Enemy::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	
	DrawRect();
}

void Enemy::Collision(Base* b)
{
	switch (b->m_type) {
	case eType_Player:
		if (Base::CollisionRect(this, b)) {
			m_img.ChangeAnimation(eAnimDown);
			m_down = true;
			
		}
		break;
	}
}

