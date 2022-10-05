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
	//m_down = false;
	
}

void Enemy::Update()
{
	m_pos_old = m_pos;
	m_pos.x--;
	//アニメーション更新
	m_img.UpdateAnimation();
	//重力による落下
	m_vec.y += GRAVITY;
	
	

}

void Enemy::Draw()
{
	//位置設定
	m_img.SetPos(GetScreenPos(m_pos));
	//反転設定
	m_img.SetFlipH(m_flip);
	//描画
	m_img.Draw();
	//当たり判定矩形の表示
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

