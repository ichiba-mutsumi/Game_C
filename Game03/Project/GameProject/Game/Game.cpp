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
Game::Game() :Base(eType_Scene)
{
	//Base::Add(new Field());
	Base::Add(new Map());
	Base::Add(new Player(CVector2D(32*10, 32*19), false));
	//Base::Add(new Attack(CVector2D(1280, 560), false));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), true));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), true));
	//Base::Add(new Enemy(CVector2D(2500, 800), false,eType_Enemy1));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), false,eType_Enemy2));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 3, 540), false,eType_Enemy3));
	//Base::Add(new Enemy(CVector2D(1280 + 256 * 2, 540), false, eType_Enemy4));
	Base::Add(new Enemy(CVector2D(1280 + 256 * 5, 540), true, eType_Enemy5));
	Base::Add(new Goal(CVector2D(2048, 540)));
	Base::Add(new Item(CVector2D(2048, 940)));
	Base::Add(new start(CVector2D(2000, 1235)));
	Base::Add(new Goal2(CVector2D(2500, 1035)));
	Base::Add(new UI());
	GameData::s_score = 0;
	GameData::s_time = 60 * 60 * 10;
}


Game::~Game()
{
	//全てのオブジェクトを破棄
	Base::KillAll();
	//タイトルシーンへ
	Base::Add(new Title());
}

void Game::Update()
{
	//ゴールがなければゲームシーン終了
	if (!Base::FindObject(eType_Goal)) {
		SetKill();
	}
	//プレイヤー死亡　ボタン１でゲームシーン終了
	if (!Base::FindObject(eType_Player) && PUSH(CInput::eButton1)) {
		SetKill();
	}
}
