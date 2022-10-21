#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Effect.h"
#include "GameData.h"
#include "Map.h"
#include "Attack.h"
#include"EnemyBullet.h"
#include <iostream>
void Enemy::StateIdle(int type)
{
    m_pos.x--;

    //const float move_speed = 4;

    //bool move_flag = false;

    m_img.ChangeAnimation(0);
    switch (EnemyType) {

    case eType_Enemy1:
    case eType_Enemy2:
    case eType_Enemy3:
    case eType_Enemy6:
    case eType_Enemy7:
    case eType_Enemy9:

        break;
    case eType_Enemy4:
    case eType_Enemy8:
        if (abs(v.x) <= 300) {
            m_state = eState_Attack;
        }

        break;

    case eType_Enemy5:
        //m_img.ChangeAnimation(0,false);
        if (abs(v.x) <= 300) {
            m_state = eState_Attack;
        }

        break;
    }

}

void Enemy::StateDamage(int type)
{
    
    cnt--;
    
    m_img.ChangeAnimation(0, false);
    if (cnt<=0) {
        m_img.ChangeAnimation(eAnimIdle);
        m_state = eState_Damage;
    }
}

void Enemy::StateDown(int type)
{
    m_img.ChangeAnimation(0);
    SetKill();
    Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, -128), m_flip));

}

void Enemy::StateAttack(int type)
{
   
    m_img.ChangeAnimation(2, false);
    
    
    //int type, const CVector2D& pos, float ang, float speed
    Base* b = Base::FindObject(eType_Bullet);
    if (!b) {
        Base::Add(new EnemyBullet(eType_Bullet, m_pos, m_ang, 4));
    }
    

    if (m_img.CheckAnimationEnd()) {

        m_state = eState_Wait;
    }
}

void Enemy::StateWait(int type)
{

    if (--bcnt<=0) {
        bcnt = 180;
        m_state = eState_Idle;
    }
}



Enemy::Enemy(const CVector2D& p, bool flip, int type):
Base(eType_Enemy) {
    
    //画像複製
    switch (type)
    {
    case eType_Enemy1:
        m_img = COPY_RESOURCE("Enemy", CImage);
        m_img.SetSize(96, 96);
        m_rect = CRect(-32, -64, 32, 0);
        m_img.SetCenter(48, 96);
        hp = 50;
        break;
    case eType_Enemy2:
        m_img = COPY_RESOURCE("Enemy2", CImage);
        m_img.SetSize(96, 96);
        m_rect = CRect(-32, -64, 32, 0);
        m_img.SetCenter(48, 96);
        hp = 100;
        break;
    case eType_Enemy3:
        m_img = COPY_RESOURCE("Enemy3", CImage);
        m_img.SetSize(96, 96);
        m_rect = CRect(-32, -64, 32, 0);
        m_img.SetCenter(48, 96);
        hp = 150;
        break;
    case eType_Enemy4:
        m_img = COPY_RESOURCE("Witch", CImage);
        m_img.SetSize(262, 264);
        m_rect = CRect(-64, -128, 64, 0);
        m_img.SetCenter(133, 226);
        hp = 250;
        break;
    case eType_Enemy5:
        m_img = COPY_RESOURCE("Dragon", CImage);
        m_img.SetSize(460, 250);
        m_rect = CRect(-98, -190, 188, 0);
        m_img.SetCenter(190, 238);
        hp = 400;
        break;
    case eType_Enemy6:
        m_img = COPY_RESOURCE("Enemy", CImage);
        m_img.SetSize(160,162);
        m_rect = CRect(-35, -110, 75, 0);
        m_img.SetCenter(60, 150);
        hp = 150;
        break;
    case eType_Enemy7:
        m_img = COPY_RESOURCE("Enemy2", CImage);
        m_img.SetSize(160, 162);
        m_rect = CRect(-35, -110, 75, 0);
        m_img.SetCenter(60, 150);
        hp = 200;
        break;
     break; case eType_Enemy8:
        m_img = COPY_RESOURCE("Witch2", CImage);
        m_img.SetSize(262, 264);
        m_rect = CRect(-64, -128, 64, 0);
        m_img.SetCenter(133, 226);
        hp = 250;
        break;
    case eType_Enemy9:
        m_img = COPY_RESOURCE("Enemy3", CImage);
        m_img.SetSize(160, 162);
        m_rect = CRect(-35, -110, 75, 0);
        m_img.SetCenter(60, 150);
        hp = 200;
        break;    }

       //m_img.SetSize(96, 96);
        
        //当たり判定用矩形設定
       // m_rect = CRect(-32, -64, 32, 0);
        //再生アニメーション設定
        m_img.ChangeAnimation(0);
        //反転フラグ
        m_flip = flip;
        //中心位置設定
       // m_img.SetCenter(48, 96);
        //座標設定
        m_pos_old = m_pos = p;
        m_attack_no = rand();
        //ダメージ番号
        m_damage_no = -1;
        //m_down = false;
        m_is_ground = true;
        CVector2D v(0, 0);
        cnt = 30;
        bcnt = 180;
        EnemyType=type;
        m_vec.x--;
}

void Enemy::Update()
{
    //std::cout << "Enemy" << std::endl;
    m_pos_old = m_pos;
   
    if (m_is_ground && m_vec.y > GRAVITY * 4) {
        m_is_ground = false;

    }
    switch (EnemyType) {
    case eType_Enemy1:
    case eType_Enemy2:
    case eType_Enemy3:
    case eType_Enemy5:
    case eType_Enemy6:
    case eType_Enemy7:
    case eType_Enemy9:
        //重力による落下
         m_vec.y += GRAVITY;
         break;

    }
   
    m_pos += m_vec;
    switch (m_state) {
        //通常状態
    case eState_Idle:
        StateIdle(0);
        break;
        //ダメージ状態
    case eState_Damage:
        StateDamage(0);
        break;
        //ダウン状態
    case eState_Down:
        StateDown(0);
        break;
    case eState_Attack:
        StateAttack(0);
        break;
    case eState_Wait:
        StateWait(0);
        break;
    }
    m_img.UpdateAnimation();

    Base* b = Base::FindObject(eType_Player);
    if (b) {
        Player* f = dynamic_cast<Player*>(b);
        v = f->m_pos - m_pos; 
    }
    if (m_vec.x < 0) {
        m_flip = false;
    }
    else if (m_vec.x > 0) {
        m_flip = true;
    }





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
    case eType_Flame:
        /*if (Base::CollisionRect(this, b)) {
            hp = -50;
            //m_down = true;
            if (hp=0) 
            m_img.ChangeAnimation(eAnimDown);
            SetKill();
            Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, -128), m_flip));
        }
        break;*/
        if (Attack* s = dynamic_cast<Attack*>(b)) {
            if (m_damage_no != s->GetAttackNo() && Base::CollisionRect(this, s)) {
                //同じ攻撃の連続ダメージ防止
                m_damage_no = s->GetAttackNo();
                hp -= 50;
                if (hp <= 0) {
                    m_state = eState_Down;
                }
                else {
                    m_state = eState_Damage;
                }
            }
        }
        break;

    case eType_Field:
        if (Map* m = dynamic_cast<Map*>(b)) {
            int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
            
            if (t != 0) {
                m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
                
            }            t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
            if (t != 0) {
                m_pos.y = m_pos_old.y;
                m_vec.y = 0;
                m_is_ground = true;
            }
        }
        break;

    }
   
}

