#include "Enemy.h"
#include "AnimData.h"
#include "Player.h"
#include "Effect.h"
#include "GameData.h"
#include "Map.h"
#include "Attack.h"

void Enemy::StateIdle()
{
    
    m_pos.x--;
}

void Enemy::StateDamage()
{
    
    cnt--;
    
    m_img.ChangeAnimation(eAnimDamage, false);
    if (cnt<=0) {
        m_img.ChangeAnimation(eAnimIdle);
        m_state = eState_Idle;
    }
}

void Enemy::StateDown()
{
    m_img.ChangeAnimation(eAnimDown);
    SetKill();
    Base::Add(new Effect("Effect_Smoke", m_pos + CVector2D(0, -128), m_flip));

}

Enemy::Enemy(const CVector2D& p, bool flip, int type):
Base(eType_Enemy) {
    
    //�摜����
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
        //�����蔻��p��`�ݒ�
        m_rect = CRect(-32, -64, 32, 0);
        //�Đ��A�j���[�V�����ݒ�
        m_img.ChangeAnimation(0);
        //���]�t���O
        m_flip = flip;
        //���S�ʒu�ݒ�
        m_img.SetCenter(48, 96);
        //���W�ݒ�
        m_pos_old = m_pos = p;
        //m_down = false;
        m_is_ground = true;
        cnt = 30;
}

void Enemy::Update()
{
    m_pos_old = m_pos;
   
    if (m_is_ground && m_vec.y > GRAVITY * 4) {
        m_is_ground = false;

    }
    //�d�͂ɂ�闎��
    m_vec.y += GRAVITY;
    m_pos += m_vec;
    switch (m_state) {
        //�ʏ���
    case eState_Idle:
        StateIdle();
        break;
        //�_���[�W���
    case eState_Damage:
        StateDamage();
        break;
        //�_�E�����
    case eState_Down:
        StateDown();
        break;


    }
    m_img.UpdateAnimation();









}

void Enemy::Draw()
{
    //�ʒu�ݒ�
    m_img.SetPos(GetScreenPos(m_pos));
    //���]�ݒ�
    m_img.SetFlipH(m_flip);
    //�`��
    m_img.Draw();

    DrawRect();
}

void Enemy::Collision(Base* b)
{
    switch (b->m_type) {
    case eType_Ball:
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
                //�����U���̘A���_���[�W�h�~
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
            if (t != 0)
                m_pos.x = m_pos_old.x;
            t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
            if (t != 0) {
                m_pos.y = m_pos_old.y;
                m_vec.y = 0;
                m_is_ground = true;
            }
        }
        break;

    }
   
}

