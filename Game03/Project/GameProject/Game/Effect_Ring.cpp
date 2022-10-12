#include "Effect_Ring.h"



Effect_Ring::Effect_Ring(const char* name, const CVector2D& pos, bool flip) :
	Base(eType_Effect)
{
	//画像複製
	m_img = COPY_RESOURCE(name, CImage);
	//座標設定
	m_pos = pos;
	//表示サイズ設定
	m_img.SetSize(16*2, 72*2);
	//中心位置設定
	m_img.SetCenter(16, 40*2);
	//再生アニメーション設定(非ループ)
	m_img.ChangeAnimation(0, false);
	//反転フラグ
	m_flip = flip;
}


void Effect_Ring::Update()
{
	//アニメーション更新
	m_img.UpdateAnimation();
	//アニメーション終了チェック
	if (m_img.CheckAnimationEnd()) {
		//エフェクトを削除
		SetKill();
	}
}

void Effect_Ring::Draw()
{
	m_img.SetPos(GetScreenPos(m_pos));
	m_img.SetFlipH(m_flip);
	m_img.Draw();
}
