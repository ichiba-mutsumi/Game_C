#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Effect.h"
#include "GameData.h"

Enemy::Enemy(const CVector2D& p, bool flip, int type):
Base(eType_Enemy) {
    
    //画像複製
    switch (type)
    {
    case eType_Enemy:
        m_img = COPY_RESOURCE("Enemy", CImage);
        hp = 50;
        break;
    case eType_Enemy2:
        m_img = COPY_RESOURCE("Enemy2", CImage);
        hp = 100;
        break;
    case eType_Enemy3:
        m_img = COPY_RESOURCE("Enemy3", CImage);
        hp = 150;
        break;
    }

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

    DrawRect();
}

void Enemy::Collision(Base* b)
{
    switch (b->m_type) {
    case eType_Player_Attack:
        if (Base::CollisionRect(this, b)) {
           
            //m_down = true;
            if (hp=0) 
            m_img.ChangeAnimation(eAnimDown);
            SetKill();
            Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, -128), m_flip));
        }
        break;
    }
   
}

