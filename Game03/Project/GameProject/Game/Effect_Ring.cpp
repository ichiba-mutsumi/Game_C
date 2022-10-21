#include "Effect_Ring.h"
#include"Player.h"
#include "Attack.h"
Effect_Ring::Effect_Ring(const char* name, const CVector2D& pos, bool flip, float ang) :
	Base(eType_AtkEffect)
{
	//画像複製
	m_img = COPY_RESOURCE(name, CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(16*2, 144);
	//m_img.SetSize(3600, 1440);
	//中心位置設定
	m_img.SetCenter(16, 40*2);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//反転フラグ
	m_flip = flip;
	m_ang = ang;
	
}

void Effect_Ring::Update()
{
	Base* b = Base::FindObject(eType_Player);
	Player* f = dynamic_cast<Player*>(b);
	
	//アニメーション更新
	m_img.UpdateAnimation();
	//GetAttack2Flag()
	/*
	if () {
		m_img.SetAng(DtoR(90));
	}*/
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd() || !HOLD(CInput::eButton1)) {
		//エフェクトを削除
		SetKill();
	}
	m_flip = f->GetFlipFlag();
	if (m_flip) {
		m_pos = f->GetPos() + CVector2D(+60, -70);
	}
	else {
		m_pos = f->GetPos() + CVector2D(-60, -70);
	}
	
	
}

void Effect_Ring::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
