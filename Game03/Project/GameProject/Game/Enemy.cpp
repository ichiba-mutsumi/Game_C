#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Field.h"
#include "Slash.h"
#include "Effect.h"

Enemy::Enemy(const CVector2D& p, bool flip) :
	Base(eType_Enemy) {
	//画像複製
	m_img = COPY_RESOURCE("Enemy", CImage);
	//再生アニメーション設定
	m_img.ChangeAnimation(0);
	//座標設定
	m_pos = p;
	//中心位置設定
	m_img.SetCenter(128, 224);
	//当たり判定用矩形設定
	m_rect = CRect(-32, -128, 32, 0);
	//反転フラグ
	m_flip = flip;
	//通常状態へ
	m_state = eState_Idle;
	//着地フラグ
	m_is_ground = true;
}
void Enemy::Update() {
	switch (m_state) {
	case eState_Idle:
		StateIdle();
		break;
	case eState_Attack:
		StateAttack();
		break;
	case eState_Damage:
		StateDamage();
		break;
	case eState_Down:
		StateDown();
		break;
	case eState_Wait:
		StateWait();
		break;
	}
	//落ちていたら落下中状態へ移行
	if (m_is_ground && m_vec.y > GRAVITY * 4)
		m_is_ground = false;
	//重力による落下
	m_vec.y += GRAVITY;
	m_pos += m_vec;
	//アニメーション更新
	m_img.UpdateAnimation();
	//スクロール設定
	//m_scroll.x = m_pos.x - 1280 / 2;
}

void Enemy::Draw() {
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
	case eType_Goal:
		if (Base::CollisionRect(this, b)) {
			SetKill();
		}
		break;
	}
	switch (b->m_type) {
		//攻撃オブジェクトとの判定
	case eType_Player_Attack:
		//Slash型へキャスト、型変換できたら
		if (Slash* s = dynamic_cast<Slash*>(b)) {
			if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
				//同じ攻撃の連続ダメージ防止
				m_damage_no = s->GetAttackNo();
				m_hp -= 50;
				if (m_hp <= 0) {
					m_state = eState_Down;
				}
				else {
					m_state = eState_Damage;
				}
			}
			Base::Add(new Effect("Effect_Blood", m_pos + CVector2D(0, -128), m_flip));
		}
		break;
	case eType_Field:
		//Field型へキャスト、型変換できたら
		if (Field* f = dynamic_cast<Field*>(b)) {
			//地面より下にいったら
			if (m_pos.y > f->GetGroundY()) {
				//地面の高さに戻す
				m_pos.y = f->GetGroundY();
				//落下速度リセット
				m_vec.y = 0;
				//接地フラグON
				m_is_ground = true;

			}
		}
		break;
	}
}



void Enemy::StateIdle()
{
	//移動量
	const float move_speed = 6;
	//移動フラグ
	bool move_flag = false;
	//ジャンプ力
	const float jump_pow = 12;
	//プレイヤーを探索
	Base* player = Base::FindObject(eType_Player);
	
	//動作確認後コメント化
	if (player) {
		//左移動
		if (player->m_pos.x < m_pos.x - 64) {
			//移動量を設定
			m_pos.x += -move_speed;
			//反転フラグ
			m_flip = true;
			move_flag = true;
		}
		//右移動
		if (player->m_pos.x > m_pos.x + 64) {
			//移動量を設定
			m_pos.x += move_speed;
			//反転フラグ
			m_flip = false;
			move_flag = true;
		}
		else {
			//
			m_state = eState_Attack;
			m_attack_no++;
		}
	}
		
	if (move_flag) {
		//走るアニメーション
		m_img.ChangeAnimation(eAnimRun);
	}
	else {
		//待機アニメーション
		m_img.ChangeAnimation(eAnimIdle);
	}
	//カウント0で待機状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		m_state = eState_Wait;
	}
	
	else {
		if (player->m_pos.x > m_pos.x - 128 && player->m_pos.x < m_pos.x + 128) {
			m_state = eState_Attack;
			m_attack_no++;

		}
	}
}


void Enemy::StateAttack()
{	//攻撃アニメーションへ変更
	m_img.ChangeAnimation(eAnimAttack01, false);

	if (m_flip) {
		Base::Add(new Slash(m_pos + CVector2D(-64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
	}
	else {
		Base::Add(new Slash(m_pos + CVector2D(64, -64), m_flip, eType_Enemy_Attack, m_attack_no));
	}

	//アニメーションが終了したら
	if (m_img.CheckAnimationEnd()) {

		//通常状態へ移行
		m_state = eState_Wait;
	}
}


void Enemy::StateDamage()
{
	m_img.ChangeAnimation(eAnimDamage, false);
	if (m_img.CheckAnimationEnd()) {
		m_state = eState_Idle;
	}

}
void Enemy::StateDown()
{
	m_img.ChangeAnimation(eAnimDown, false);
	if (m_img.CheckAnimationEnd()) {
		Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, 0), m_flip));
		m_kill = true;
	}
}

void Enemy::StateWait()
{
	//待機アニメーション
	m_img.ChangeAnimation(eAnimIdle);
	//カウント0で待機状態へ
	if (--m_cnt <= 0) {
		//待機時間3秒～5秒
		m_cnt = rand() % 120 + 180;
		m_state = eState_Idle;
	}
}
