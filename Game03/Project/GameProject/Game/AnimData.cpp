#include "AnimData.h"


static TexAnim playerIdle[] = {
	{ 0,20 },
	{ 1,20 },
	{ 2,20 },
};
static TexAnim playerRun[] = {
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
	{ 10,4 },
	{ 14,4 },
	{ 15,4 },
	{ 16,4 },
	{ 17,4 },
};
static TexAnim playerJumpUp[] = {
	{ 21,4 },
	{ 22,4 },
	{ 23,4 },
	
};
static TexAnim playerJumpDown[] = {
	{ 24,4 },
	{ 25,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
	{ 26,4 },
	{ 27,4 },
};
static TexAnim playerAttack01[] = {
	{ 40,3 },
	{ 41,3 },
	{ 42,3 },
	{ 43,2 },
	{ 44,2 },
	{ 45,3 },
	{ 46,4 },
};
static TexAnim playerAttack01End[] = {
	{ 48,4 },
	{ 49,4 },
	{ 50,4 },
	{ 51,4 },
	{ 52,4 },
};
static TexAnim playerAttack02[] = {
	{ 56,6 },
	{ 57,6 },
	{ 58,4 },
	{ 59,2 },
	{ 60,2 },
	{ 61,2 },
	{ 62,4 },
};
static TexAnim playerAttack02End[] = {
	{ 64,4 },
	{ 65,4 },
	{ 66,4 },
	{ 67,4 },
	{ 68,4 },
};
static TexAnim playerAttack03[] = {
	{ 72,6 },
	{ 73,6 },
	{ 74,4 },
	{ 75,4 },
	{ 76,3 },
	{ 77,2 },
	{ 78,2 },
	{ 79,4 },
};
static TexAnim playerAttack03End[] = {
	{ 80,4 },
	{ 81,4 },
	{ 82,4 },
	{ 83,4 },
};

static TexAnim playerDamage[] = {
	{ 88,2 },
	{ 89,2 },
	{ 90,2 },
	{ 91,2 },
};
static TexAnim playerDamageEnd[] = {
	{ 92,2 },
	{ 93,2 },
	{ 94,2 },
	{ 95,2 },
};
static TexAnim playerDeath[] = {
	{ 96,4 },
	{ 97,4 },
	{ 98,8 },
	{ 99,4 },
	{ 100,4 },
	{ 101,4 },
	{ 102,4 },
	{ 103,4 },
};

static TexAnim playerDown[] = {
	{ 104,4 },
	{ 105,4 },
	{ 106,4 },
	{ 107,4 },
	{ 108,4 },
};
static TexAnim playerDownGround[] = {
	{ 109,4 },
	{ 110,4 },
	{ 111,4 },
};
static TexAnim playerWakeup[] = {
	{ 112,4 },
	{ 113,4 },
	{ 114,4 },
	{ 115,4 },
	{ 116,4 },
	{ 117,4 },
	{ 118,4 },
};
static TexAnim playerGuard[] = {
	//	{ 120,4 },
	//	{ 121,4 },
	{ 122,4 },
};
static TexAnim playerGuardEnd[] = {
	{ 122,4 },
	{ 121,4 },
	{ 120,4 },
};
static TexAnim playerCrash[] = {
	{ 128,4 },
	{ 129,4 },
	{ 130,4 },
	{ 131,90 },
};
static TexAnim playerCrash01End[] = {
	{ 131,4 },
	{ 130,4 },
	{ 129,4 },
	{ 128,4 },
};
static TexAnim playerExtAttack01[] = {
	{ 144,4 },
	{ 145,4 },
	{ 146,12 },
	{ 147,2 },
	{ 148,2 },
	{ 149,2 },
	{ 150,16 },
};
static TexAnim playerExtAttack01End[] = {
	{ 151,4 },
	{ 152,4 },
};
static TexAnim playerExtAttack02[] = {
	{ 160,2 },
	{ 161,2 },
	{ 162,2 },
	{ 163,2 },
	{ 164,2 },
	{ 165,2 },
	{ 166,2 },
	{ 167,2 },
	{ 168,2 },
};
static TexAnim playerExtAttack02End[] = {
	{ 169,16 },
	{ 170,4 },
	{ 171,4 },
};
static TexAnim playerStep[] = {
	{ 120,4 },
	{ 121,4 },
	{ 122,4 },
};
TexAnimData player_anim_data[] = {
	ANIMDATA(playerIdle),
	ANIMDATA(playerRun),
	ANIMDATA(playerJumpUp),
	ANIMDATA(playerJumpDown),
	ANIMDATA(playerAttack01),
	ANIMDATA(playerAttack01End),
	ANIMDATA(playerAttack02),
	ANIMDATA(playerAttack02End),
	ANIMDATA(playerAttack03),
	ANIMDATA(playerAttack03End),
	ANIMDATA(playerDamage),
	ANIMDATA(playerDamageEnd),
	ANIMDATA(playerDeath),
	ANIMDATA(playerDown),
	ANIMDATA(playerDownGround),
	ANIMDATA(playerWakeup),
	ANIMDATA(playerGuard),
	ANIMDATA(playerGuardEnd),
	ANIMDATA(playerCrash),
	ANIMDATA(playerCrash01End),
	ANIMDATA(playerExtAttack01),
	ANIMDATA(playerExtAttack01End),
	ANIMDATA(playerExtAttack02),
	ANIMDATA(playerExtAttack02End),
	ANIMDATA(playerStep),
};

static TexAnim enemyIdle[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	
};
static TexAnim enemy_witch_move[] = {
	{ 0,8 },
	{ 1,8 },
	{ 2,8 },
	{ 3,8 },
	{ 4,8 },
	{ 5,8 },
};
static TexAnim enemy_witch_attack[] = {
	{ 6,8 },
	{ 7,8 },
	{ 8,8 },
	{ 9,8 },
};
static TexAnim enemy_witch_stand[] = {
	{ 12,8 },
	{ 13,8 },
	{14,8},
	{15,8},
};
TexAnimData enemy_witch_anim_data[] = {
	ANIMDATA(enemy_witch_stand),
	ANIMDATA(enemy_witch_move),
	ANIMDATA(enemy_witch_attack),
};
TexAnimData enemy_anim_data[] = {
	ANIMDATA(enemyIdle),
	ANIMDATA(enemyIdle),
	ANIMDATA(enemyIdle),
};




static TexAnim _effect_blood[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
};
TexAnimData effect_blood_anim_data[] = {
	ANIMDATA(_effect_blood),
};
static TexAnim _effect_smoke[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
};
TexAnimData effect_smoke_anim_data[] = {
	ANIMDATA(_effect_smoke),
};

static TexAnim _effect_bomb[] = {
	{ 0,2 },
	{ 1,2 },
	{ 2,2 },
	{ 3,2 },
	{ 4,2 },
}; 
TexAnimData effect_bomb_anim_data[] = {
	ANIMDATA(_effect_smoke),
};
static TexAnim _effect_slash[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
};
TexAnimData effect_slash_anim_data[] = {
	ANIMDATA(_effect_slash),
};
static TexAnim _effect_flame[] = {
	{ 0,4 },
	{ 1,4 },
	{ 2,4 },
	{ 3,4 },
	{ 4,4 },
	{ 5,4 },
	{ 6,4 },
	{ 7,4 },
	{ 8,4 },
	{ 9,4 },
};
TexAnimData effect_flame_anim_data[] = {
	ANIMDATA(_effect_flame),
};
static TexAnim _effect_ring[] = {
	{ 0,1 },
	{ 1,1 },
	{ 2,1 },
	{ 3,1 },
	{ 4,1 },
	{ 5,1 },
	{ 6,1 },
	{ 7,1 },
	{ 8,1 },
	{ 9,1 },
	{ 10,1 },
	{ 11,1 },
	{ 12,1 },
	{ 13,1 },
	{ 14,1 },
	{ 15,1 },
	{ 16,1 },
	{ 17,1 },
	{ 18,1 },
	{ 19,1 },
	{ 20,1 },
	{ 21,1 },
	{ 22,1 },
	{ 23,1 },
	{ 24,1 },
	{ 25,1 },
	{ 26,1 },
	{ 27,1 },
	{ 28,1 },
	{ 29,1 },
};
TexAnimData effect_ring_anim_data[] = {
	ANIMDATA(_effect_ring),
};