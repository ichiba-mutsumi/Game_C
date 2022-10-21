#include "Game.h"
#include "Field.h"
#include "Player.h"
#include "Enemy.h"
#include "Goal.h"
#include "Map.h"
#include "Item.h"
#include "../Title/Title.h"
#include "UI.h"
#include "start.h"
#include "Goal2.h"
#include"GameData.h"
#include"Attack.h"
#include <iostream>
Game::Game() :Base(eType_Scene)
{
	//Base::Add(new Field());
	Base::Add(new Map());
	
	//Base::Add(new Attack(CVector2D(1280, 560), false));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//Base::Add(new Enemy(CVector2D(2500, 800), false,eType_Enemy1));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), false,eType_Enemy2));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), false,eType_Enemy3));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), false, eType_Enemy4));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 5, 540), true, eType_Enemy5));
	Base::Add(new Enemy(CVector2D(3500, 800), false, eType_Enemy6));
	Base::Add(new Enemy(CVector2D(3900, 800), false, eType_Enemy7));
	Base::Add(new Enemy(CVector2D(2500 + 256 * 2, 540), false, eType_Enemy8));
	Base::Add(new Enemy(CVector2D(4500, 1900), false, eType_Enemy9));
	Base::Add(new Goal(CVector2D(2048, 540)));
	Base::Add(new Item(CVector2D(2048, 940)));
	Base::Add(new start(CVector2D(2000, 1235)));
	Base::Add(new Goal2(CVector2D(2500, 1035)));
	Base::Add(new UI());
	GameData::s_score = 0;
	GameData::s_time = 60 * 60 * 10;
	Base::Add(new Player(CVector2D(32 * 10, 32 * 19), false));
}


Game::~Game()
{
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�^�C�g���V�[����
	Base::Add(new Title());
}

void Game::Update()
{
	//std::cout << "game" << std::endl;
	//�S�[�����Ȃ���΃Q�[���V�[���I��
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
