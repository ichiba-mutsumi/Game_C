#include "Game.h"
#include "Field.h"
#include "Player.h"
//#include "Enemy.h"
#include "Goal.h"
#include "Map.h"
#include "Item.h"
#include "../Title/Title.h"
#include "UI.h"

#include "start.h"
#include "Goal2.h"
Game::Game() :Base(eType_Scene)
{
	//Base::Add(new Field());
	Base::Add(new Map());
	Base::Add(new Player(CVector2D(1280, 540), false));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 1, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	Base::Add(new Goal(CVector2D(2048, 540)));
	Base::Add(new Item(CVector2D(2048, 940)));
	Base::Add(new start(CVector2D(3000, 1035)));
	Base::Add(new Goal2(CVector2D(3500, 1035)));
	Base::Add(new UI());
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
	//�S�[�����Ȃ���΃Q�[���V�[���I��
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//�v���C���[���S�@�{�^���P�ŃQ�[���V�[���I��
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
