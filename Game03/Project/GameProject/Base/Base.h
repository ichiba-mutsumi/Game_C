#pragma once
#include<GLLibrary.h>
//重力加速度
#define GRAVITY (9.8f/20)

enum {
	eType_Scene,
	eType_Field,
	eType_Player,
	eType_Enemy,
	eType_Flame,
	eType_Enemy1,
	eType_Enemy2,
	eType_Enemy3,
	eType_Enemy4,
	eType_Enemy5,
	eType_Enemy6,
	eType_Enemy7,
	eType_Enemy8,
	eType_Enemy9,	eType_Bullet,
	eType_Goal,
	eType_Player_Attack,
	eType_Enemy_Attack,
	eType_Effect,
	eType_AtkEffect,
	eType_UI,
	eType_Item,

	eType_start,
	eType_Goal2,
};

class Base {
public:
	//座標データ
	CVector2D m_pos;
	CVector2D m_pos_old;
	static std::list<Base*> m_list;
	//オブジェクトの種類
	int m_type;
	//半径
	float m_rad;
	//移動ベクトル
	CVector2D m_vec;
	//回転値
	float m_ang;
	//スクロール値
	static CVector2D m_scroll;

	bool m_kill;
	Base* Base::FindObject(int type);
	//矩形
	CRect m_rect;


public:
	//typeオブジェクトの種類
	Base(int type);
	virtual ~Base();
	virtual void Update();
	virtual void Draw();
	virtual void Collision(Base* b);
	//削除フラグON
	void SetKill() { m_kill = true; }
	//全てのオブジェクトの更新
	static void UpdateAll();
	//全てのオブジェクトの描画
	static void DrawAll();
	//全てのオブジェクトの当たりの判定検証
	static void CollisionAll();
	//オブジェクトの追加
	static void Add(Base*b);
	//全オブジェクトの削除
	static void KillAll();
	//円同士の衝突
	static bool CollisionCircle(Base* b1, Base* b2);
	//削除チェック
	static void CheckKillAll();
	
	//typeのオブジェクトを探索（複数）
	static std::list<Base*> FindObjects(int type);

	static CVector2D GetScreenPos(const CVector2D& pos);

	//矩形同士の判定
	static bool CollisionRect(Base* b1, Base* b2);
	//矩形の表示
	void DrawRect();
};


