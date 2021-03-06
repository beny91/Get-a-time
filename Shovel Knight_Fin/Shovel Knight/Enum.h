
#ifndef _ENUM_H_
#define _ENUM_H_

enum eOBJ_TYPE
{
	OBJ_BACKGROUND,
	OBJ_OTHER,
	OBJ_PLAYER,
	OBJ_MONSTER,
	OBJ_BULLET,
	OBJ_EFFECT,
	OBJ_UI,
	OBJ_ITEM,
	OBJ_CURSOR,

	OBJ_END,
};

enum eBLACK_PATTERN
{
	STAND,
	LAUGH,
	ATTACK,
	DARKBALL,
	THRUST,
};
enum eSTATE_TYPE
{
	STATE_UP =0,
	STATE_DOWN,
	STATE_STOP,
	STATE_END
};


enum eSCENE_TYPE
{
	SCENE_LOGO,
	SCENE_EDIT,
	SCENE_STAGE,
	SCENE_GAMEMENU,
	SCENE_END,
};

enum eSTAGE_TYPE
{
	STAGE_1,
	STAGE_2,
	STAGE_End
};

enum eDIR_TYPE
{
	DIR_LEFT =0,
	DIR_RIGHT ,
	DIR_UP,
	DIR_DOWN,
	DIR_END
};

enum eDRAKE_PATTERN
{
	DRAKE_TURNAROUND = 0,
	DRAKE_UPDOWN,
	DRAKE_SHORTTURNAROUND
};

enum eTREASURES
{
	TREASURES_GRAY,
	TREASURES_BLUE,
	TREASURES_GREEN,
	TREASURES_YELLOW,
	TREASURES_RED,
	TREASURES_VIOLET
};

enum eRECOVER_ITEM
{
	RECOVER_ITEM_CARROT,
	RECOVER_ITEM_APPLE,
	RECOVER_ITEM_CHICKEN,
	RECOVER_ITEM_SMALL_MANA,
	RECOVER_ITEM_TALL_MANA,
	RECOVER_ITEM_HP_MEAL,
	RECOVER_ITEM_MP_MEAL
};

enum eDIRT_TYPE
{
	DIRT_SMALL,
	DIRT_BIG
};

enum eEFFECT_TYPE
{
	EFFECT_DIRT_POORF,
	EFFECT_DIRTPILE_POORF,
	EFFECT_ATTTECK_DOWN
};

#endif