#pragma once
#include"../Base/Base.h"

class Player :public Base {
private:
	//状態
	enum {
		eState_Idle,
		eState_Attack,
		eState_Damage,
		eState_Down,
		

	};
	//状態変数
	int m_state;

	CImage m_img;
	//反転フラグ
	bool m_flip;
	//着地フラグ
	bool m_is_ground;
	//攻撃番号
	int m_attack_no;

	//溜め時間(120)
	int Ccnt;
	//ダメージ番号
	int m_damage_no;
	//ヒットポイント
	int m_hp;
	//プレイヤー移動量
	CVector2D ver;
	//補間量
	CVector2D sc_ver;
	//各状態での挙動
	void StateIdle();
	void StateAttack();
	void StateDamage();
	void StateDown();
	

public:
	Player(const CVector2D& p, bool flip);
	void Update();
	void Draw();
	void Collision(Base* b);
	int GetFlipFlag() {
		return !m_flip;
	}
	CVector2D GetPos() {
		return m_pos;
	}
};



