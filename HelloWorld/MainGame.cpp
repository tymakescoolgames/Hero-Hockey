// Ty Reid
// Hero Hockey Acorn Championship
// ------------------------------------------

// First player to reach 7 points wins!
#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include <ctime>
#include <iostream>
enum PlayerState
{
	STATE_APPEAR,
	STATE_ALIVE,
	STATE_DEAD,
};
enum PlayState
{
	STATE_LOADING,
	STATE_MAIN_MENU,
	STATE_CHAR_SELECT,
	STATE_MAP_SELECT,
	STATE_MAP1,
	STATE_MAP2,
	STATE_MAP3,
	STATE_MAP4,
	STATE_WON,
};
struct GameState
{
	int player1Character = 0;
	int player2Character = 0;
	bool player1Right = TRUE;
	bool player2Right = FALSE;
	int player1Health = 5;
	int player2Health = 5;
	bool player1CoolDown = TRUE;
	bool player2CoolDown = TRUE;
	int player1Score = 0;
	int player2Score = 0;
	bool characterSelect = FALSE;
	bool mapSelect = FALSE;
	bool playingMatch = FALSE;
	int map = 0;
	PlayState playState = STATE_LOADING;
	PlayerState player1State = STATE_APPEAR;
	PlayerState player2State = STATE_APPEAR;
};
GameState gameState;
enum GameObjectType
{
	TYPE_NULL = -1,
	// Player characters:
	TYPE_ALEX,
	TYPE_ALEX1,
	TYPE_ALEX2,
	TYPE_TOSHI,
	TYPE_TOSHI1,
	TYPE_TOSHI2,
	TYPE_COSMO,
	TYPE_COSMO1,
	TYPE_COSMO2,
	TYPE_KUDO,
	TYPE_KUDO1,
	TYPE_KUDO2,
	TYPE_PLAYER1_PORTRAIT,
	TYPE_PLAYER2_PORTRAIT,
	TYPE_PLAYER1_HEALTH,
	TYPE_PLAYER2_HEALTH,
	TYPE_PLAYER1_MARKER,
	TYPE_PLAYER2_MARKER,
	TYPE_PLAYER1_FIREBALL,
	TYPE_PLAYER2_FIREBALL,
	TYPE_SCORE_COUNTER,
	// ------------------------------------------
	TYPE_PUCK,
	TYPE_SHADOW,
	// Maps:
	TYPE_MAP1,
	TYPE_MAP2,
	TYPE_MAP3,
	TYPE_MAP4,
	// ------------------------------------------
	TYPE_DESTROYED,
};
void HeroSelect();
void HeroUpdate();
void HandleAlex1();
void HandleToshi1();
void HandleCosmo1();
void HandleKudo1();
void HandleAlex2();
void HandleToshi2();
void HandleCosmo2();
void HandleKudo2();
void UpdateHealth();
void UpdatePuck();
void Player1Scored();
void Player2Scored();
void Fireballs();
void MapObstacles();
void LoadingScreen();
void MainMenuScreen();
void CharacterSelectionScreen();
void MapSelectionScreen();
void ElvenForest();
void Neon();
void Prague();
void ThunderLeagueArena();
void EndMatch();

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	// Loading background screens:
	Play::LoadBackground("Data\\Backgrounds\\bgr_loading.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_main_menu.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_character_selection.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_map_selection.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_elven_forest.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_neon.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_prague.png");
	Play::LoadBackground("Data\\Backgrounds\\bgr_thunder_league_arena.png");
	// Playing music:
	Play::PlayAudio("snd_loading_music");
}

bool MainGameUpdate( float elapsedTime ) // 60FPS
{
	switch (gameState.playState)
	{
		case STATE_LOADING:
			Play::ClearDrawingBuffer(Play::cBlue);
			LoadingScreen();
			break;
		case STATE_MAIN_MENU:
			Play::ClearDrawingBuffer(Play::cBlue);
			MainMenuScreen();
			break;
		case STATE_CHAR_SELECT:
			Play::ClearDrawingBuffer(Play::cBlue);
			CharacterSelectionScreen(); 
			break;
		case STATE_MAP_SELECT:
			Play::ClearDrawingBuffer(Play::cBlue);
			MapSelectionScreen();
			break;
		case STATE_MAP1:
			Play::ClearDrawingBuffer(Play::cBlue);
			ElvenForest();
			break;
		case STATE_MAP2:
			Play::ClearDrawingBuffer(Play::cBlue);
			Neon();
			break;
		case STATE_MAP3:
			Play::ClearDrawingBuffer(Play::cBlue);
			Prague();
			break;
		case STATE_MAP4:
			Play::ClearDrawingBuffer(Play::cBlue);
			ThunderLeagueArena();
			break;
		case STATE_WON:
			Play::ClearDrawingBuffer(Play::cBlue);
			break;
	}

	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Character functions:
void HeroSelect()
{
	// Player 1:
	if (gameState.player1Character == 1)
	{
		Play::CreateGameObject(TYPE_ALEX1, { 100, DISPLAY_HEIGHT / 2 }, 15, "spr_alex_standing_right");
		Play::CreateGameObject(TYPE_PLAYER1_PORTRAIT, { 75, 50}, 0, "spr_alex_small_blue");
	}
	if (gameState.player1Character == 2)
	{
		Play::CreateGameObject(TYPE_TOSHI1, { 100, DISPLAY_HEIGHT / 2 }, 15, "spr_toshi_standing_right");
		Play::CreateGameObject(TYPE_PLAYER1_PORTRAIT, { 75, 50 }, 0, "spr_toshi_small_blue");
	}
	if (gameState.player1Character == 3)
	{
		Play::CreateGameObject(TYPE_COSMO1, { 100, DISPLAY_HEIGHT / 2 }, 15, "spr_cosmo_standing_right");
		Play::CreateGameObject(TYPE_PLAYER1_PORTRAIT, { 75, 50 }, 0, "spr_cosmo_small_blue");
	}
	if (gameState.player1Character == 4)
	{
		Play::CreateGameObject(TYPE_KUDO1, { 100, DISPLAY_HEIGHT / 2 }, 15, "spr_kudo_standing_right");
		Play::CreateGameObject(TYPE_PLAYER1_PORTRAIT, { 75, 50 }, 0, "spr_kudo_small_blue");
	}
	Play::CreateGameObject(TYPE_PLAYER1_HEALTH, { 166, 50 }, 0, "spr_5_hp_blue");
	Play::CreateGameObject(TYPE_PLAYER1_MARKER, { 75, 30 }, 0, "spr_marker_blue");
	// Player 2:
	if (gameState.player2Character == 1)
	{
		Play::CreateGameObject(TYPE_ALEX2, { 1180, DISPLAY_HEIGHT / 2 }, 15, "spr_alex_standing_left");
		Play::CreateGameObject(TYPE_PLAYER2_PORTRAIT, { 1205, 50 }, 0, "spr_alex_small_red");
	}
	if (gameState.player2Character == 2)
	{
		Play::CreateGameObject(TYPE_TOSHI2, { 1180, DISPLAY_HEIGHT / 2 }, 15, "spr_toshi_standing_left");
		Play::CreateGameObject(TYPE_PLAYER2_PORTRAIT, { 1205, 50 }, 0, "spr_toshi_small_red");
	}
	if (gameState.player2Character == 3)
	{
		Play::CreateGameObject(TYPE_COSMO2, { 1180, DISPLAY_HEIGHT / 2 }, 15, "spr_cosmo_standing_left");
		Play::CreateGameObject(TYPE_PLAYER2_PORTRAIT, { 1205, 50 }, 0, "spr_cosmo_small_red");
	}
	if (gameState.player2Character == 4)
	{
		Play::CreateGameObject(TYPE_KUDO2, { 1180, DISPLAY_HEIGHT / 2 }, 15, "spr_kudo_standing_left");
		Play::CreateGameObject(TYPE_PLAYER2_PORTRAIT, { 1205, 50 }, 0, "spr_kudo_small_red");
	}
	Play::CreateGameObject(TYPE_PLAYER2_HEALTH, { 1114, 50 }, 0, "spr_5_hp_red");
	Play::CreateGameObject(TYPE_PLAYER2_MARKER, { 1205, 30 }, 0, "spr_marker_red");
	// Score counter:
	Play::CreateGameObject(TYPE_SCORE_COUNTER, { DISPLAY_WIDTH / 2, 50 }, 0, "spr_score");
	// Puck:
	Play::CreateGameObject(TYPE_PUCK, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 30, "spr_ball");
	Play::CreateGameObject(TYPE_SHADOW, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, 0, "spr_ball_shadow");
}

void HeroUpdate()
{
	// Player 1:
	if (gameState.player1Character == 1)
	{
		HandleAlex1();
	}
	if (gameState.player1Character == 2)
	{
		HandleToshi1();
	}
	if (gameState.player1Character == 3)
	{
		HandleCosmo1();
	}
	if (gameState.player1Character == 4)
	{
		HandleKudo1();
	}
	// Player 2:
	if (gameState.player2Character == 1)
	{
		HandleAlex2();
	}
	if (gameState.player2Character == 2)
	{
		HandleToshi2();
	}
	if (gameState.player2Character == 3)
	{
		HandleCosmo2();
	}
	if (gameState.player2Character == 4)
	{
		HandleKudo2();
	}
}

void HandleAlex1()
{
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_ALEX1);
	GameObject& obj_player1Portrait = Play::GetGameObjectByType(TYPE_PLAYER1_PORTRAIT);
	GameObject& obj_player1Marker = Play::GetGameObjectByType(TYPE_PLAYER1_MARKER);

	// Player1 controls:
	obj_player1.velocity = { 0, 0 };
	if (Play::KeyDown('W'))
	{
		obj_player1.velocity = { 0, -3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_alex_up_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, -3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_alex_up_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, -3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_alex_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown('S'))
	{
		obj_player1.velocity = { 0, 3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_alex_down_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, 3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_alex_down_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, 3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_alex_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown('D'))
	{
		Play::SetSprite(obj_player1, "spr_alex_right_4", 0.20f);
		obj_player1.velocity = { 3.5f, 0 };
		gameState.player1Right = TRUE;
	}
	else if (Play::KeyDown('A'))
	{
		Play::SetSprite(obj_player1, "spr_alex_left_4", 0.20f);
		obj_player1.velocity = { -3.5f, 0 };
		gameState.player1Right = FALSE;
	}
	else
	{
		if (gameState.player1Right == TRUE)
		{
			Play::SetSprite(obj_player1, "spr_alex_standing_right", 0.0f);
		}
		if (gameState.player1Right == FALSE)
		{
			Play::SetSprite(obj_player1, "spr_alex_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SHIFT) && gameState.player1CoolDown == TRUE)
	{
		Play::CreateGameObject(TYPE_PLAYER1_FIREBALL, { 50, 0 }, 50, "spr_fireball_5");
		Play::CreateGameObject(TYPE_PLAYER1_FIREBALL, { 300, 50 }, 50, "spr_fireball_5");
		Play::CreateGameObject(TYPE_PLAYER1_FIREBALL, { 550, 100 }, 50, "spr_fireball_5");
		Play::PlayAudio("snd_firestorm");
		gameState.player1CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player1, Play::VERTICAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player1, Play::HORIZONTAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	// Marker:
	obj_player1Marker.pos = { (obj_player1.pos.x), (obj_player1.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player1);
	Play::DrawObjectRotated(obj_player1);
	Play::UpdateGameObject(obj_player1Portrait);
	Play::DrawObjectRotated(obj_player1Portrait);
	Play::UpdateGameObject(obj_player1Marker);
	Play::DrawObjectRotated(obj_player1Marker);
}

void HandleToshi1()
{
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_TOSHI1);
	GameObject& obj_player1Portrait = Play::GetGameObjectByType(TYPE_PLAYER1_PORTRAIT);
	GameObject& obj_player1Marker = Play::GetGameObjectByType(TYPE_PLAYER1_MARKER);
	GameObject& obj_puck = Play::GetGameObjectByType(TYPE_PUCK);

	// Player1 controls:
	obj_player1.velocity = { 0, 0 };
	if (Play::KeyDown('W'))
	{
		obj_player1.velocity = { 0, -3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_toshi_up_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, -3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_toshi_up_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, -3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_toshi_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown('S'))
	{
		obj_player1.velocity = { 0, 3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_toshi_down_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, 3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_toshi_down_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, 3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_toshi_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown('D'))
	{
		Play::SetSprite(obj_player1, "spr_toshi_right_4", 0.20f);
		obj_player1.velocity = { 3.5f, 0 };
		gameState.player1Right = TRUE;
	}
	else if (Play::KeyDown('A'))
	{
		Play::SetSprite(obj_player1, "spr_toshi_left_4", 0.20f);
		obj_player1.velocity = { -3.5f, 0 };
		gameState.player1Right = FALSE;
	}
	else
	{
		if (gameState.player1Right == TRUE)
		{
			Play::SetSprite(obj_player1, "spr_toshi_standing_right", 0.0f);
		}
		if (gameState.player1Right == FALSE)
		{
			Play::SetSprite(obj_player1, "spr_toshi_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SHIFT) && gameState.player1CoolDown == TRUE)
	{
		obj_player1.pos = { (obj_puck.pos.x - 15), obj_puck.pos.y}; // Teleport to puck!
		Play::PlayAudio("snd_leaf_hop");
		gameState.player1CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player1, Play::VERTICAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player1, Play::HORIZONTAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	// Marker:
	obj_player1Marker.pos = { (obj_player1.pos.x), (obj_player1.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player1);
	Play::DrawObjectRotated(obj_player1);
	Play::UpdateGameObject(obj_player1Portrait);
	Play::DrawObjectRotated(obj_player1Portrait);
	Play::UpdateGameObject(obj_player1Marker);
	Play::DrawObjectRotated(obj_player1Marker);
}

void HandleCosmo1()
{
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_COSMO1);
	GameObject& obj_player1Portrait = Play::GetGameObjectByType(TYPE_PLAYER1_PORTRAIT);
	GameObject& obj_player1Marker = Play::GetGameObjectByType(TYPE_PLAYER1_MARKER);

	// Player1 controls:
	obj_player1.velocity = { 0, 0 };
	if (Play::KeyDown('W'))
	{
		obj_player1.velocity = { 0, -3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, -3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, -3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown('S'))
	{
		obj_player1.velocity = { 0, 3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_right_4", 0.20f);
			obj_player1.velocity = { 3.25f, 3.25f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_left_4", 0.20f);
			obj_player1.velocity = { -3.25f, 3.25f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown('D'))
	{
		Play::SetSprite(obj_player1, "spr_cosmo_right_4", 0.20f);
		obj_player1.velocity = { 3.5f, 0 };
		gameState.player1Right = TRUE;
	}
	else if (Play::KeyDown('A'))
	{
		Play::SetSprite(obj_player1, "spr_cosmo_left_4", 0.20f);
		obj_player1.velocity = { -3.5f, 0 };
		gameState.player1Right = FALSE;
	}
	else
	{
		if (gameState.player1Right == TRUE)
		{
			Play::SetSprite(obj_player1, "spr_cosmo_standing_right", 0.0f);
		}
		if (gameState.player1Right == FALSE)
		{
			Play::SetSprite(obj_player1, "spr_cosmo_standing_left", 0.0f);
		}
	}
	// Passive ability - Screen wrapping:
	int dWidth = PlayWindow::Instance().GetWidth(); // Store the width of the display area!
	int dHeight = PlayWindow::Instance().GetHeight(); // Store the height of the display area!
	Vector2f origin = PlayGraphics::Instance().GetSpriteOrigin(obj_player1.spriteId);
	if (obj_player1.pos.x - origin.x - 50 > dWidth) 
	{
		obj_player1.pos.x = 0.0f - 50 + origin.x;
	}
	else if (obj_player1.pos.x + origin.x + 50 < 0) 
	{
		obj_player1.pos.x = dWidth + 50 - origin.x;
	}
	if (obj_player1.pos.y - origin.y - 50 > dHeight) 
	{
		obj_player1.pos.y = 0.0f - 50 + origin.y;
	}
	else if (obj_player1.pos.y + origin.y + 50 < 0) 
	{
		obj_player1.pos.y = dHeight + 50 - origin.y;
	}
	// Special ability - no collisions:
	// Marker:
	obj_player1Marker.pos = { (obj_player1.pos.x), (obj_player1.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player1);
	Play::DrawObjectRotated(obj_player1);
	Play::UpdateGameObject(obj_player1Portrait);
	Play::DrawObjectRotated(obj_player1Portrait);
	Play::UpdateGameObject(obj_player1Marker);
	Play::DrawObjectRotated(obj_player1Marker);
}

void HandleKudo1()
{
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_KUDO1);
	GameObject& obj_player1Portrait = Play::GetGameObjectByType(TYPE_PLAYER1_PORTRAIT);
	GameObject& obj_player1Marker = Play::GetGameObjectByType(TYPE_PLAYER1_MARKER);

	// Player1 controls:
	obj_player1.velocity = { 0, 0 };
	if (Play::KeyDown('W'))
	{
		obj_player1.velocity = { 0, -4.0f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_kudo_up_right_4", 0.20f);
			obj_player1.velocity = { 3.5f, -3.5f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_kudo_up_left_4", 0.20f);
			obj_player1.velocity = { -3.5f, -3.5f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_kudo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown('S'))
	{
		obj_player1.velocity = { 0, 4.0f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player1, "spr_kudo_down_right_4", 0.20f);
			obj_player1.velocity = { 3.5f, 3.5f };
			gameState.player1Right = TRUE;
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player1, "spr_kudo_down_left_4", 0.20f);
			obj_player1.velocity = { -3.5f, 3.5f };
			gameState.player1Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_kudo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown('D'))
	{
		Play::SetSprite(obj_player1, "spr_kudo_right_4", 0.20f);
		obj_player1.velocity = { 4.0f, 0 };
		gameState.player1Right = TRUE;
	}
	else if (Play::KeyDown('A'))
	{
		Play::SetSprite(obj_player1, "spr_kudo_left_4", 0.20f);
		obj_player1.velocity = { -4.0f, 0 };
		gameState.player1Right = FALSE;
	}
	else
	{
		if (gameState.player1Right == TRUE)
		{
			Play::SetSprite(obj_player1, "spr_kudo_standing_right", 0.0f);
		}
		if (gameState.player1Right == FALSE)
		{
			Play::SetSprite(obj_player1, "spr_kudo_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SHIFT) && gameState.player1CoolDown == TRUE)
	{
		obj_player1.pos = { obj_player1.pos.x + ((obj_player1.velocity.x) * 70), obj_player1.pos.y + ((obj_player1.velocity.y) * 70) };
		Play::PlayAudio("snd_binky");
		gameState.player1CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player1, Play::VERTICAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player1, Play::HORIZONTAL))
	{
		obj_player1.pos = obj_player1.oldPos;
	}
	// Marker:
	obj_player1Marker.pos = { (obj_player1.pos.x), (obj_player1.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player1);
	Play::DrawObjectRotated(obj_player1);
	Play::UpdateGameObject(obj_player1Portrait);
	Play::DrawObjectRotated(obj_player1Portrait);
	Play::UpdateGameObject(obj_player1Marker);
	Play::DrawObjectRotated(obj_player1Marker);

}

void HandleAlex2()
{
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_ALEX2);
	GameObject& obj_player2Portrait = Play::GetGameObjectByType(TYPE_PLAYER2_PORTRAIT);
	GameObject& obj_player2Marker = Play::GetGameObjectByType(TYPE_PLAYER2_MARKER);

	// Player1 controls:
	obj_player2.velocity = { 0, 0 };
	if (Play::KeyDown(VK_UP))
	{
		obj_player2.velocity = { 0, -3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_alex_up_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, -3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_alex_up_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, -3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_alex_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		obj_player2.velocity = { 0, 3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_alex_down_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, 3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_alex_down_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, 3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_alex_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		Play::SetSprite(obj_player2, "spr_alex_right_4", 0.20f);
		obj_player2.velocity = { 3.5f, 0 };
		gameState.player2Right = TRUE;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		Play::SetSprite(obj_player2, "spr_alex_left_4", 0.20f);
		obj_player2.velocity = { -3.5f, 0 };
		gameState.player2Right = FALSE;
	}
	else
	{
		if (gameState.player2Right == TRUE)
		{
			Play::SetSprite(obj_player2, "spr_alex_standing_right", 0.0f);
		}
		if (gameState.player2Right == FALSE)
		{
			Play::SetSprite(obj_player2, "spr_alex_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SPACE) && gameState.player2CoolDown == TRUE)
	{
		Play::CreateGameObject(TYPE_PLAYER2_FIREBALL, { 1230, 670 }, 50, "spr_fireball_5");
		Play::CreateGameObject(TYPE_PLAYER2_FIREBALL, { 980, 620 }, 50, "spr_fireball_5");
		Play::CreateGameObject(TYPE_PLAYER2_FIREBALL, { 730, 570 }, 50, "spr_fireball_5");
		Play::PlayAudio("snd_firestorm");
		gameState.player2CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player2, Play::VERTICAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player2, Play::HORIZONTAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	// Marker:
	obj_player2Marker.pos = { (obj_player2.pos.x), (obj_player2.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player2);
	Play::DrawObjectRotated(obj_player2);
	Play::UpdateGameObject(obj_player2Portrait);
	Play::DrawObjectRotated(obj_player2Portrait);
	Play::UpdateGameObject(obj_player2Marker);
	Play::DrawObjectRotated(obj_player2Marker);
}

void HandleToshi2()
{
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_TOSHI2);
	GameObject& obj_player2Portrait = Play::GetGameObjectByType(TYPE_PLAYER2_PORTRAIT);
	GameObject& obj_player2Marker = Play::GetGameObjectByType(TYPE_PLAYER2_MARKER);
	GameObject& obj_puck = Play::GetGameObjectByType(TYPE_PUCK);

	// Player1 controls:
	obj_player2.velocity = { 0, 0 };
	if (Play::KeyDown(VK_UP))
	{
		obj_player2.velocity = { 0, -3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_toshi_up_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, -3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_toshi_up_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, -3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_toshi_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		obj_player2.velocity = { 0, 3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_toshi_down_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, 3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_toshi_down_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, 3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_toshi_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		Play::SetSprite(obj_player2, "spr_toshi_right_4", 0.20f);
		obj_player2.velocity = { 3.5f, 0 };
		gameState.player2Right = TRUE;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		Play::SetSprite(obj_player2, "spr_toshi_left_4", 0.20f);
		obj_player2.velocity = { -3.5f, 0 };
		gameState.player2Right = FALSE;
	}
	else
	{
		if (gameState.player2Right == TRUE)
		{
			Play::SetSprite(obj_player2, "spr_toshi_standing_right", 0.0f);
		}
		if (gameState.player2Right == FALSE)
		{
			Play::SetSprite(obj_player2, "spr_toshi_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SPACE) && gameState.player2CoolDown == TRUE)
	{
		obj_player2.pos = { (obj_puck.pos.x + 15), obj_puck.pos.y }; // Teleport to puck!
		Play::PlayAudio("snd_leaf_hop");
		gameState.player2CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player2, Play::VERTICAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player2, Play::HORIZONTAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	// Marker:
	obj_player2Marker.pos = { (obj_player2.pos.x), (obj_player2.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player2);
	Play::DrawObjectRotated(obj_player2);
	Play::UpdateGameObject(obj_player2Portrait);
	Play::DrawObjectRotated(obj_player2Portrait);
	Play::UpdateGameObject(obj_player2Marker);
	Play::DrawObjectRotated(obj_player2Marker);
}

void HandleCosmo2()
{
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_COSMO2);
	GameObject& obj_player2Portrait = Play::GetGameObjectByType(TYPE_PLAYER2_PORTRAIT);
	GameObject& obj_player2Marker = Play::GetGameObjectByType(TYPE_PLAYER2_MARKER);

	// Player1 controls:
	obj_player2.velocity = { 0, 0 };
	if (Play::KeyDown(VK_UP))
	{
		obj_player2.velocity = { 0, -3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_cosmo_up_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, -3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_cosmo_up_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, -3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_cosmo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		obj_player2.velocity = { 0, 3.5f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_cosmo_down_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, 3.25f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_cosmo_down_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, 3.25f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_cosmo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		Play::SetSprite(obj_player2, "spr_cosmo_right_4", 0.20f);
		obj_player2.velocity = { 3.5f, 0 };
		gameState.player2Right = TRUE;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		Play::SetSprite(obj_player2, "spr_cosmo_left_4", 0.20f);
		obj_player2.velocity = { -3.5f, 0 };
		gameState.player2Right = FALSE;
	}
	else
	{
		if (gameState.player2Right == TRUE)
		{
			Play::SetSprite(obj_player2, "spr_cosmo_standing_right", 0.0f);
		}
		if (gameState.player2Right == FALSE)
		{
			Play::SetSprite(obj_player2, "spr_cosmo_standing_left", 0.0f);
		}
	}
	// Passive ability - Screen wrapping:
	int dWidth = PlayWindow::Instance().GetWidth(); // Store the width of the display area!
	int dHeight = PlayWindow::Instance().GetHeight(); // Store the height of the display area!
	Vector2f origin = PlayGraphics::Instance().GetSpriteOrigin(obj_player2.spriteId);
	if (obj_player2.pos.x - origin.x - 50 > dWidth)
	{
		obj_player2.pos.x = 0.0f - 50 + origin.x;
	}
	else if (obj_player2.pos.x + origin.x + 50 < 0)
	{
		obj_player2.pos.x = dWidth + 50 - origin.x;
	}
	if (obj_player2.pos.y - origin.y - 50 > dHeight)
	{
		obj_player2.pos.y = 0.0f - 50 + origin.y;
	}
	else if (obj_player2.pos.y + origin.y + 50 < 0)
	{
		obj_player2.pos.y = dHeight + 50 - origin.y;
	}
	// Special ability - no collisions:
	// Marker:
	obj_player2Marker.pos = { (obj_player2.pos.x), (obj_player2.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player2);
	Play::DrawObjectRotated(obj_player2);
	Play::UpdateGameObject(obj_player2Portrait);
	Play::DrawObjectRotated(obj_player2Portrait);
	Play::UpdateGameObject(obj_player2Marker);
	Play::DrawObjectRotated(obj_player2Marker);
}

void HandleKudo2()
{
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_KUDO2);
	GameObject& obj_player2Portrait = Play::GetGameObjectByType(TYPE_PLAYER2_PORTRAIT);
	GameObject& obj_player2Marker = Play::GetGameObjectByType(TYPE_PLAYER2_MARKER);

	// Player1 controls:
	obj_player2.velocity = { 0, 0 };
	if (Play::KeyDown(VK_UP))
	{
		obj_player2.velocity = { 0, -4.0f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_right_4", 0.20f);
			obj_player2.velocity = { 3.5f, -3.5f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_left_4", 0.20f);
			obj_player2.velocity = { -3.5f, -3.5f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		obj_player2.velocity = { 0, 4.0f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_right_4", 0.20f);
			obj_player2.velocity = { 3.5f, 3.5f };
			gameState.player2Right = TRUE;
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_left_4", 0.20f);
			obj_player2.velocity = { -3.5f, 3.5f };
			gameState.player2Right = FALSE;
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		Play::SetSprite(obj_player2, "spr_kudo_right_4", 0.20f);
		obj_player2.velocity = { 4.0f, 0 };
		gameState.player2Right = TRUE;
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		Play::SetSprite(obj_player2, "spr_kudo_left_4", 0.20f);
		obj_player2.velocity = { -4.0f, 0 };
		gameState.player2Right = FALSE;
	}
	else
	{
		if (gameState.player2Right == TRUE)
		{
			Play::SetSprite(obj_player2, "spr_kudo_standing_right", 0.0f);
		}
		if (gameState.player2Right == FALSE)
		{
			Play::SetSprite(obj_player2, "spr_kudo_standing_left", 0.0f);
		}
	}
	// Special ability:
	if (Play::KeyPressed(VK_SPACE) && gameState.player2CoolDown == TRUE)
	{
		obj_player2.pos = { obj_player2.pos.x + ((obj_player2.velocity.x) * 70), obj_player2.pos.y + ((obj_player2.velocity.y) * 70) };
		Play::PlayAudio("snd_binky");
		gameState.player2CoolDown = FALSE;
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_player2, Play::VERTICAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	if (Play::IsLeavingDisplayArea(obj_player2, Play::HORIZONTAL))
	{
		obj_player2.pos = obj_player2.oldPos;
	}
	// Marker:
	obj_player2Marker.pos = { (obj_player2.pos.x), (obj_player2.pos.y - 30) };
	// Updates:
	Play::UpdateGameObject(obj_player2);
	Play::DrawObjectRotated(obj_player2);
	Play::UpdateGameObject(obj_player2Portrait);
	Play::DrawObjectRotated(obj_player2Portrait);
	Play::UpdateGameObject(obj_player2Marker);
	Play::DrawObjectRotated(obj_player2Marker);
}

void UpdateHealth()
{
	GameObject& obj_player1Health = Play::GetGameObjectByType(TYPE_PLAYER1_HEALTH);
	GameObject& obj_player2Health = Play::GetGameObjectByType(TYPE_PLAYER2_HEALTH);
	// Player1:
	if (gameState.player1Health == 5)
	{
		Play::SetSprite(obj_player1Health, "spr_5_hp_blue", 0.0f);
	}
	if (gameState.player1Health == 4)
	{
		Play::SetSprite(obj_player1Health, "spr_4_hp_blue", 0.0f);
	}
	if (gameState.player1Health == 3)
	{
		Play::SetSprite(obj_player1Health, "spr_3_hp_blue", 0.0f);
	}
	if (gameState.player1Health == 2)
	{
		Play::SetSprite(obj_player1Health, "spr_2_hp_blue", 0.0f);
	}
	if (gameState.player1Health == 1)
	{
		Play::SetSprite(obj_player1Health, "spr_1_hp_blue", 0.0f);
	}
	if (gameState.player1Health == 0)
	{
		Play::SetSprite(obj_player1Health, "spr_no_hp_blue", 0.0f);
	}
	// Player2:
	if (gameState.player2Health == 5)
	{
		Play::SetSprite(obj_player2Health, "spr_5_hp_red", 0.0f);
	}
	if (gameState.player2Health == 4)
	{
		Play::SetSprite(obj_player2Health, "spr_4_hp_red", 0.0f);
	}
	if (gameState.player2Health == 3)
	{
		Play::SetSprite(obj_player2Health, "spr_3_hp_red", 0.0f);
	}
	if (gameState.player2Health == 2)
	{
		Play::SetSprite(obj_player2Health, "spr_2_hp_red", 0.0f);
	}
	if (gameState.player2Health == 1)
	{
		Play::SetSprite(obj_player2Health, "spr_1_hp_red", 0.0f);
	}
	if (gameState.player2Health == 0)
	{
		Play::SetSprite(obj_player2Health, "spr_no_hp_red", 0.0f);
	}
	Play::UpdateGameObject(obj_player1Health);
	Play::DrawObjectRotated(obj_player1Health);
	Play::UpdateGameObject(obj_player2Health);
	Play::DrawObjectRotated(obj_player2Health);
}

void Player1Scored()
{
	gameState.player1Score += 1;
	Play::PlayAudio("snd_scored");
	gameState.player1Health = 5;
	gameState.player2Health = 5;
	gameState.player1CoolDown = TRUE;
	gameState.player2CoolDown = TRUE;

}

void Player2Scored()
{
	gameState.player2Score += 1;
	Play::PlayAudio("snd_scored");
	gameState.player1Health = 5;
	gameState.player2Health = 5;
	gameState.player1CoolDown = TRUE;
	gameState.player2CoolDown = TRUE;
}

void Fireballs()
{
	// Player1 fireballs:
	std::vector<int> vPlayer1Fireballs = Play::CollectGameObjectIDsByType(TYPE_PLAYER1_FIREBALL);
	GameObject& obj_alex2 = Play::GetGameObjectByType(TYPE_ALEX2);
	GameObject& obj_toshi2 = Play::GetGameObjectByType(TYPE_TOSHI2);
	GameObject& obj_cosmo2 = Play::GetGameObjectByType(TYPE_COSMO2);
	GameObject& obj_kudo2 = Play::GetGameObjectByType(TYPE_KUDO2);
	for (int id_player1Fireball : vPlayer1Fireballs)
	{
		GameObject& obj_fireball = Play::GetGameObject(id_player1Fireball);
		// Movement:
		Play::SetSprite(obj_fireball, "spr_fireball_5", 0.15f);
		obj_fireball.rotation = 1.0f;
		obj_fireball.velocity = { 4.5f, 4.5f };
		// Collisions:
		if (Play::IsColliding(obj_fireball, obj_alex2) || Play::IsColliding(obj_fireball, obj_toshi2) || Play::IsColliding(obj_fireball, obj_cosmo2) || Play::IsColliding(obj_fireball, obj_kudo2))
		{
			Play::PlayAudio("snd_bump");
			gameState.player2Health -= 2; // If Player2 gets hit then reduce their health!
		}
		Play::UpdateGameObject(obj_fireball);
		Play::DrawObjectRotated(obj_fireball);
		if (!Play::IsVisible(obj_fireball)) // Off-screen fireball!
		{
			Play::DestroyGameObject(id_player1Fireball);
		}
	}
	// Player2 fireballs:
	std::vector<int> vPlayer2Fireballs = Play::CollectGameObjectIDsByType(TYPE_PLAYER2_FIREBALL);
	GameObject& obj_alex1 = Play::GetGameObjectByType(TYPE_ALEX1);
	GameObject& obj_toshi1 = Play::GetGameObjectByType(TYPE_TOSHI1);
	GameObject& obj_cosmo1 = Play::GetGameObjectByType(TYPE_COSMO1);
	GameObject& obj_kudo1 = Play::GetGameObjectByType(TYPE_KUDO1);
	for (int id_player2Fireball : vPlayer2Fireballs)
	{
		GameObject& obj_fireball = Play::GetGameObject(id_player2Fireball);
		// Movement:
		Play::SetSprite(obj_fireball, "spr_fireball_5", 0.15f);
		obj_fireball.rotation = 4.0f;
		obj_fireball.velocity = { -4.5f, -4.5f };
		// Collisions:
		if (Play::IsColliding(obj_fireball, obj_alex1) || Play::IsColliding(obj_fireball, obj_toshi1) || Play::IsColliding(obj_fireball, obj_cosmo1) || Play::IsColliding(obj_fireball, obj_kudo1))
		{
			Play::PlayAudio("snd_bump");
			gameState.player1Health -= 2; // If Player1 gets hit then reduce their health!
		}
		Play::UpdateGameObject(obj_fireball);
		Play::DrawObjectRotated(obj_fireball);
		if (!Play::IsVisible(obj_fireball)) // Off-screen fireball!
		{
			Play::DestroyGameObject(id_player2Fireball);
		}
	}
	// Alex's passive ability:
	if (Play::IsColliding(obj_alex1, obj_alex2) || Play::IsColliding(obj_alex1, obj_toshi2) || Play::IsColliding(obj_alex1, obj_cosmo2) || Play::IsColliding(obj_alex1, obj_kudo2))
	{
		gameState.player2Health -= 1;
		Play::PlayAudio("snd_bump");
	}
	if (Play::IsColliding(obj_alex2, obj_alex1) || Play::IsColliding(obj_alex2, obj_toshi1) || Play::IsColliding(obj_alex2, obj_cosmo1) || Play::IsColliding(obj_alex2, obj_kudo1))
	{
		gameState.player1Health -= 1;
		Play::PlayAudio("snd_bump");
	}
}
// ------------------------------------------

// Puck:
void UpdatePuck()
{
	// Puck:
	GameObject& obj_puck = Play::GetGameObjectByType(TYPE_PUCK);
	// Shadow:
	GameObject& obj_shadow = Play::GetGameObjectByType(TYPE_SHADOW);
	// Score counter:
	GameObject& obj_scoreCounter = Play::GetGameObjectByType(TYPE_SCORE_COUNTER);
	// Player Characters and collisions:
	// Player 1:
	GameObject& obj_alex1 = Play::GetGameObjectByType(TYPE_ALEX1);
	if (Play::IsColliding(obj_puck, obj_alex1))
	{
		obj_puck.velocity = 1.75 * (obj_alex1.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_1");
	}
	GameObject& obj_toshi1 = Play::GetGameObjectByType(TYPE_TOSHI1);
	if (Play::IsColliding(obj_puck, obj_toshi1))
	{
		obj_puck.velocity = 1.75 * (obj_toshi1.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_1");
	}
	GameObject& obj_cosmo1 = Play::GetGameObjectByType(TYPE_COSMO1);
	if (Play::IsColliding(obj_puck, obj_cosmo1))
	{
		obj_puck.velocity = 1.75 * (obj_cosmo1.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_1");
	}
	GameObject& obj_kudo1 = Play::GetGameObjectByType(TYPE_KUDO1);
	if (Play::IsColliding(obj_puck, obj_kudo1))
	{
		obj_puck.velocity = 1.75* (obj_kudo1.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_1");
	}
	// Player 2:
	GameObject& obj_alex2 = Play::GetGameObjectByType(TYPE_ALEX2);
	if (Play::IsColliding(obj_puck, obj_alex2))
	{
		obj_puck.velocity = 1.75 * (obj_alex2.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_2");
	}
	GameObject& obj_toshi2 = Play::GetGameObjectByType(TYPE_TOSHI2);
	if (Play::IsColliding(obj_puck, obj_toshi2))
	{
		obj_puck.velocity = 1.75 * (obj_toshi2.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_2");
	}
	GameObject& obj_cosmo2 = Play::GetGameObjectByType(TYPE_COSMO2);
	if (Play::IsColliding(obj_puck, obj_cosmo2))
	{
		obj_puck.velocity = 1.75 * (obj_cosmo2.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_2");
	}
	GameObject& obj_kudo2 = Play::GetGameObjectByType(TYPE_KUDO2);
	if (Play::IsColliding(obj_puck, obj_kudo2))
	{
		obj_puck.velocity = 1.75 * (obj_kudo2.velocity);
		obj_puck.rotSpeed = 1.0;
		Play::PlayAudio("snd_puck_hit_2");
	}
	// Boundary collisions:
	if (Play::IsLeavingDisplayArea(obj_puck, Play::VERTICAL))
	{
		obj_puck.pos = obj_puck.oldPos;
		obj_puck.velocity.y *= -1;
		Play::PlayAudio("snd_bump");
	}
	// Obstacle collisions:
	// Shadow:
	obj_shadow.pos = obj_puck.pos;
	// Scoring a point:
	// If a Player has scored a point or one of the players had died:
	if ((Play::IsLeavingDisplayArea(obj_puck, Play::HORIZONTAL)) || gameState.player1Health <= 0 || gameState.player2Health <= 0) 
	{
		// Player1 scored:
		if ((obj_puck.pos.x > 640) || gameState.player2Health <= 0 ) // Over towards Player2's goal or Player 2 has died!
		{
			if ((obj_puck.pos.y > 225 && obj_puck.pos.y < 495) || gameState.player2Health <= 0)
			{
				Player1Scored();
				obj_puck.velocity = { 0.0f, 0.0f };
				obj_puck.pos = { DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2 };
				obj_puck.rotSpeed = 0.0f;
				// Reset players:
				obj_alex1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_toshi1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_cosmo1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_kudo1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_alex2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_toshi2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_cosmo2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_kudo2.pos = { 1180, DISPLAY_HEIGHT / 2 };
			}
			else
			{
				obj_puck.pos = obj_puck.oldPos;
				obj_puck.velocity.x *= -1;
				Play::PlayAudio("snd_bump");
			}
		}
		// Player2 scored:
		if ((obj_puck.pos.x < 640) || gameState.player1Health <= 0 ) // Over towards Player1's goal or Player 1 has died!
		{
			if ((obj_puck.pos.y > 225 && obj_puck.pos.y < 495) || gameState.player1Health <= 0 )
			{
				Player2Scored();
				obj_puck.velocity = { 0.0f, 0.0f };
				obj_puck.pos = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 };
				obj_puck.rotSpeed = 0.0f;
				// Reset players:
				obj_alex1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_toshi1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_cosmo1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_kudo1.pos = { 100, DISPLAY_HEIGHT / 2 };
				obj_alex2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_toshi2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_cosmo2.pos = { 1180, DISPLAY_HEIGHT / 2 };
				obj_kudo2.pos = { 1180, DISPLAY_HEIGHT / 2 };
			}
			else
			{
				obj_puck.pos = obj_puck.oldPos;
				obj_puck.velocity.x *= -1;
				Play::PlayAudio("snd_bump");
			}
		}
	}
	Play::UpdateGameObject(obj_puck);
	Play::DrawObjectRotated(obj_puck);
	Play::UpdateGameObject(obj_shadow);
	Play::DrawObjectRotated(obj_shadow);
	Play::UpdateGameObject(obj_scoreCounter);
	Play::DrawObjectRotated(obj_scoreCounter);
	// Draw current score:
	Play::DrawFontText("silver64px", std::to_string(gameState.player1Score), { 607, 55 }, Play::CENTRE);
	Play::DrawFontText("silver64px", std::to_string(gameState.player2Score), { 671, 55 }, Play::CENTRE);
}
// ------------------------------------------

void LoadingScreen()
{
	Play::DrawBackground(0);
	Play::DrawFontText("silver_yellow39px", "History told of an ancient power guarded closely by the Princess of the kingdom and her most trusted followers...", { DISPLAY_WIDTH / 2, 275 }, Play::CENTRE);
	Play::DrawFontText("silver_yellow39px", "... Now a new league of heroes has assembled in order to protect the resurfaced mystical acorn gems...", { DISPLAY_WIDTH / 2, 325 }, Play::CENTRE);
	Play::DrawFontText("silver_yellow39px", "... These legends battle valiantly around the kingdom in the most perilous tournament of all time...", { DISPLAY_WIDTH / 2, 375 }, Play::CENTRE);
	Play::DrawFontText("silver64px", "Press 'SPACE' or 'Q' to skip!", { DISPLAY_WIDTH / 2, 620 }, Play::CENTRE);

	if (Play::KeyPressed(VK_SPACE) || Play::KeyPressed('Q'))
	{
		Play::StopAudioLoop("snd_loading_music");
		Play::PlayAudio("snd_forward");
		Play::StartAudioLoop("snd_main_menu_music");
		gameState.playState = STATE_MAIN_MENU;
	}
}

void MainMenuScreen()
{
	Play::DrawBackground(1);
	Play::DrawFontText("silver_red137px", "HERO HOCKEY", { DISPLAY_WIDTH / 2, 225 }, Play::CENTRE);
	Play::DrawFontText("silver_yellow69px", "THE ACORN CHAMPIONSHIP", { DISPLAY_WIDTH / 2, 300 }, Play::CENTRE);
	Play::DrawFontText("silver39px", "Press 'Q' to return to loading screen!", {225, 50 }, Play::CENTRE);
	Play::DrawFontText("silver64px", "Press 'SPACE' to play!", { DISPLAY_WIDTH / 2, 620 }, Play::CENTRE);

	if (Play::KeyPressed(VK_SPACE))
	{
		Play::StopAudioLoop("snd_main_menu_music");
		Play::PlayAudio("snd_forward");
		Play::StartAudioLoop("snd_character_selection_music");
		gameState.characterSelect = TRUE;
		gameState.playState = STATE_CHAR_SELECT;
	}
	else if (Play::KeyPressed('Q'))
	{
		Play::StopAudioLoop("snd_main_menu_music");
		Play::PlayAudio("snd_back");
		Play::PlayAudio("snd_loading_music");
		gameState.playState = STATE_LOADING;
	}
}

void CharacterSelectionScreen()
{
	Play::DrawBackground(2);
	if (gameState.characterSelect == TRUE)
	{
		Play::CreateGameObject(TYPE_ALEX, { 425, 477 }, 0, "spr_toshi_large");
		Play::CreateGameObject(TYPE_TOSHI, { 575, 477 }, 0, "spr_toshi_large");
		Play::CreateGameObject(TYPE_COSMO, { 725, 475 }, 0, "spr_cosmo_large");
		Play::CreateGameObject(TYPE_KUDO, { 875, 475 }, 0, "spr_kudo_large");	
		gameState.characterSelect = FALSE;
	}
	GameObject& obj_alex = Play::GetGameObjectByType(TYPE_ALEX);
	GameObject& obj_toshi = Play::GetGameObjectByType(TYPE_TOSHI);
	GameObject& obj_cosmo = Play::GetGameObjectByType(TYPE_COSMO);
	GameObject& obj_kudo = Play::GetGameObjectByType(TYPE_KUDO);
	// Player1 controls:
	if (Play::KeyPressed('D') && gameState.player1Character < 4)
	{
		Play::PlayAudio("snd_forward");
		gameState.player1Character += 1;
	}
	else if (Play::KeyPressed('A') && gameState.player1Character > 1)
	{
		Play::PlayAudio("snd_forward");
		gameState.player1Character -= 1;
	}
	else if (Play::KeyPressed('A') && gameState.player1Character == 0)
	{
		Play::PlayAudio("snd_forward");
		gameState.player1Character = 4;
	}
	// Player2 controls:
	if (Play::KeyPressed(VK_RIGHT) && gameState.player2Character < 4)
	{
		Play::PlayAudio("snd_back");
		gameState.player2Character += 1;
	}
	else if (Play::KeyPressed(VK_LEFT) && gameState.player2Character > 1)
	{
		Play::PlayAudio("snd_back");
		gameState.player2Character -= 1;
	}
	else if (Play::KeyPressed(VK_LEFT) && gameState.player2Character == 0)
	{
		Play::PlayAudio("snd_back");
		gameState.player2Character = 4;
	}
	// Alex:
	if (gameState.player1Character == 1)
	{
		Play::SetSprite(obj_alex, "spr_alex_large_blue", 0.0f);
		Play::DrawFontText("silver_blue69px", "ALEX", { 250, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "BLAZE SHIELD", { 250, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "FIRESTORM", { 250, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "Alex is Kudo's twin sister!", { 100, 300 });
	}
	if (gameState.player2Character == 1)
	{
		Play::SetSprite(obj_alex, "spr_alex_large_red", 0.0f);
		Play::DrawFontText("silver_red69px", "ALEX", { 970, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "BLAZE SHIELD", { 970, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "FIRESTORM", { 970, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "Alex is Kudo's twin sister!", { 770, 300 });
	}
	if (gameState.player1Character == 1 && gameState.player2Character == 1)
	{
		Play::SetSprite(obj_alex, "spr_alex_large_blue_and_red", 0.0f);
	}
	if (gameState.player1Character != 1 && gameState.player2Character != 1)
	{
		Play::SetSprite(obj_alex, "spr_alex_large", 0.0f);
	}
	Play::UpdateGameObject(obj_alex);
	Play::DrawObjectRotated(obj_alex);
	// Toshi:	
	if (gameState.player1Character == 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large_blue", 0.0f);
		Play::DrawFontText("silver_blue69px", "TOSHI", { 250, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "INNER PEACE", { 250, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "LEAF HOP", { 250, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "Toshi really likes programming!", { 80, 300 });
	}
	if (gameState.player2Character == 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large_red", 0.0f);
		Play::DrawFontText("silver_red69px", "TOSHI", { 970, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "INNER PEACE", { 970, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "LEAF HOP", { 970, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "Toshi really likes programming!", { 750, 300 });
	}
	if (gameState.player1Character == 2 && gameState.player2Character == 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large_blue_and_red", 0.0f);
	}
	if (gameState.player1Character != 2 && gameState.player2Character != 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large", 0.0f);
	}
	Play::UpdateGameObject(obj_toshi);
	Play::DrawObjectRotated(obj_toshi);
	// Cosmo:
	if (gameState.player1Character == 3)
	{
		Play::SetSprite(obj_cosmo, "spr_cosmo_large_blue", 0.0f);
		Play::DrawFontText("silver_blue69px", "COSMO", { 250, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "FLOW STATE", { 250, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "WATER WALK", { 250, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "Cosmo's favourite drink is water!", { 50, 300 });
	}
	if (gameState.player2Character == 3)
	{
		Play::SetSprite(obj_cosmo, "spr_cosmo_large_red", 0.0f);
		Play::DrawFontText("silver_red69px", "COSMO", { 970, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "FLOW STATE", { 970, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "WATER WALK", { 970, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "Cosmo's favourite drink is water!", { 700, 300 });
	}
	if (gameState.player1Character == 3 && gameState.player2Character == 3)
	{
		Play::SetSprite(obj_cosmo, "spr_cosmo_large_blue_and_red", 0.0f);
	}
	if (gameState.player1Character != 3 && gameState.player2Character != 3)
	{
		Play::SetSprite(obj_cosmo, "spr_cosmo_large", 0.0f);
	}
	Play::UpdateGameObject(obj_cosmo);
	Play::DrawObjectRotated(obj_cosmo);
	// Kudo:
	if (gameState.player1Character == 4)
	{
		Play::SetSprite(obj_kudo, "spr_kudo_large_blue", 0.0f);
		Play::DrawFontText("silver_blue69px", "KUDO", { 250, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "FEATHER STEP", { 250, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "BINKY", { 250, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_blue69px", "Kudo Really likes bunnies!", { 100, 300 });
	}
	if (gameState.player2Character == 4)
	{
		Play::SetSprite(obj_kudo, "spr_kudo_large_red", 0.0f);
		Play::DrawFontText("silver_red69px", "KUDO", { 970, 150 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "FEATHER STEP", { 970, 200 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "BINKY", { 970, 250 }, Play::CENTRE);
		Play::DrawFontText("silver_red69px", "Kudo Really likes bunnies!", { 770, 300 });
	}
	if (gameState.player1Character == 4 && gameState.player2Character == 4)
	{
		Play::SetSprite(obj_kudo, "spr_kudo_large_blue_and_red", 0.0f);
	}
	if (gameState.player1Character != 4 && gameState.player2Character != 4)
	{
		Play::SetSprite(obj_kudo, "spr_kudo_large", 0.0f);
	}
	Play::UpdateGameObject(obj_kudo);
	Play::DrawObjectRotated(obj_kudo);
	// Progress game:
	if (Play::KeyPressed(VK_SPACE) && gameState.player1Character > 0 && gameState.player2Character > 0)
	{
		Play::PlayAudio("snd_forward");
		// Remove game sprites:
		obj_alex.type = TYPE_DESTROYED;
		obj_toshi.type = TYPE_DESTROYED;
		obj_cosmo.type = TYPE_DESTROYED;
		obj_kudo.type = TYPE_DESTROYED;
		std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
		for (int id_destroyed : vDestroyed)
		{
			Play::DestroyGameObject(id_destroyed);
		}
		gameState.mapSelect = TRUE;
		gameState.playState = STATE_MAP_SELECT;
	}
	else if (Play::KeyPressed(VK_SPACE) && gameState.player1Character == 0 && gameState.player2Character == 0)
	{
		Play::PlayAudio("snd_bump");
	}
	if (Play::KeyPressed('Q'))
	{
		Play::StopAudioLoop("snd_character_selection_music");
		Play::PlayAudio("snd_back");
		// Remove game sprites:
		obj_alex.type = TYPE_DESTROYED;
		obj_toshi.type = TYPE_DESTROYED;
		obj_cosmo.type = TYPE_DESTROYED;
		obj_kudo.type = TYPE_DESTROYED;
		std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
		for (int id_destroyed : vDestroyed)
		{
			Play::DestroyGameObject(id_destroyed);
		}
		gameState.playState = STATE_MAIN_MENU;
	}
}

void MapSelectionScreen()
{
	Play::DrawBackground(3);
	Play::DrawDebugText({ DISPLAY_WIDTH / 2, 50 }, "Use a and d/left and right along with spacebar to select your Rink!");

	if (gameState.mapSelect == TRUE)
	{
		Play::CreateGameObject(TYPE_MAP1, { 170, 475 }, 0, "spr_elven_forest");
		Play::CreateGameObject(TYPE_MAP2, { 485, 475 }, 0, "spr_neon");
		Play::CreateGameObject(TYPE_MAP3, { 800, 475 }, 0, "spr_prague");
		Play::CreateGameObject(TYPE_MAP4, { 1115, 475 }, 0, "spr_thunder_league_arena");	
		gameState.mapSelect = FALSE;
	}
	// Controls:
	if (Play::KeyPressed('D') || Play::KeyPressed(VK_RIGHT) && gameState.map < 4)
	{
		Play::PlayAudio("snd_forward");
		gameState.map += 1;
	}
	else if (Play::KeyPressed('A') || Play::KeyPressed(VK_LEFT) && gameState.map > 1)
	{
		Play::PlayAudio("snd_forward");
		gameState.map -= 1;
	}
	else if (Play::KeyPressed('A') || Play::KeyPressed(VK_LEFT) && gameState.map == 0)
	{
		Play::PlayAudio("snd_forward");
		gameState.map = 4;
	}
	// Sprite updates:
	GameObject& obj_map1 = Play::GetGameObjectByType(TYPE_MAP1);
	GameObject& obj_map2 = Play::GetGameObjectByType(TYPE_MAP2);
	GameObject& obj_map3 = Play::GetGameObjectByType(TYPE_MAP3);
	GameObject& obj_map4 = Play::GetGameObjectByType(TYPE_MAP4);
	if (gameState.map == 1)
	{
		Play::SetSprite(obj_map1, "spr_elven_forest_pink", 0.0f);
		Play::DrawFontText("silver_pink137px", "ELVEN FOREST", { DISPLAY_WIDTH/ 2,  200 }, Play::CENTRE);
	}
	if (gameState.map != 1)
	{
		Play::SetSprite(obj_map1, "spr_elven_forest", 0.0f);
	}
	if (gameState.map == 2)
	{
		Play::SetSprite(obj_map2, "spr_neon_pink", 0.0f);
		Play::DrawFontText("silver_pink137px", "NEON", { DISPLAY_WIDTH / 2,  200 }, Play::CENTRE);
	}
	if (gameState.map != 2)
	{
		Play::SetSprite(obj_map2, "spr_neon", 0.0f);
	}
	if (gameState.map == 3)
	{
		Play::SetSprite(obj_map3, "spr_prague_pink", 0.0f);
		Play::DrawFontText("silver_pink137px", "PRAGUE", { DISPLAY_WIDTH / 2,  200 }, Play::CENTRE);
	}
	if (gameState.map != 3)
	{
		Play::SetSprite(obj_map3, "spr_prague", 0.0f);
	}
	if (gameState.map == 4)
	{
		Play::SetSprite(obj_map4, "spr_thunder_league_arena_pink", 0.0f);
		Play::DrawFontText("silver_pink137px", "THUNDER LEAGUE ARENA", { DISPLAY_WIDTH / 2,  200 }, Play::CENTRE);
	}
	if (gameState.map != 4)
	{
		Play::SetSprite(obj_map4, "spr_thunder_league_arena", 0.0f);
	}
	Play::UpdateGameObject(obj_map1);
	Play::DrawObjectRotated(obj_map1);
	Play::UpdateGameObject(obj_map2);
	Play::DrawObjectRotated(obj_map2);
	Play::UpdateGameObject(obj_map3);
	Play::DrawObjectRotated(obj_map3);
	Play::UpdateGameObject(obj_map4);
	Play::DrawObjectRotated(obj_map4);

	if (Play::KeyPressed(VK_SPACE) && gameState.map > 0) // If a map is chosen! 
	{
		Play::StopAudioLoop("snd_character_selection_music");
		Play::PlayAudio("snd_forward");
		// Remove game sprites:
		obj_map1.type = TYPE_DESTROYED;
		obj_map2.type = TYPE_DESTROYED;
		obj_map3.type = TYPE_DESTROYED;
		obj_map4.type = TYPE_DESTROYED;
		std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
		for (int id_destroyed : vDestroyed)
		{
			Play::DestroyGameObject(id_destroyed);
		}
		gameState.playingMatch = TRUE;
		if (gameState.map == 1)
		{
			Play::StartAudioLoop("snd_elven_forest_music");
			gameState.playState = STATE_MAP1;
		}
		if (gameState.map == 2)
		{
			Play::StartAudioLoop("snd_neon_music");
			gameState.playState = STATE_MAP2;
		}
		if (gameState.map == 3)
		{
			Play::StartAudioLoop("snd_prague_music");
			gameState.playState = STATE_MAP3;
		}
		if (gameState.map == 4)
		{
			Play::StartAudioLoop("snd_thunder_league_arena_music");
			gameState.playState = STATE_MAP4;
		}
	}
	else if (Play::KeyPressed(VK_SPACE) && gameState.map == 0)
	{
		Play::PlayAudio("snd_bump");
	}
	else if (Play::KeyPressed('Q'))
	{
		Play::PlayAudio("snd_back");
		gameState.characterSelect = TRUE;
		// Remove game sprites:
		obj_map1.type = TYPE_DESTROYED;
		obj_map2.type = TYPE_DESTROYED;
		obj_map3.type = TYPE_DESTROYED;
		obj_map4.type = TYPE_DESTROYED;
		std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
		for (int id_destroyed : vDestroyed)
		{
			Play::DestroyGameObject(id_destroyed);
		}
		gameState.playState = STATE_CHAR_SELECT;
	}
}

// Maps:
void ElvenForest()
{
	// Draw Map:
	Play::DrawBackground(4);
	if (gameState.playingMatch == TRUE)
	{
		// Create Player characters and puck and health bars:
		HeroSelect();
		gameState.playingMatch = FALSE;
	}
	// Update Player characters and puck and health bars:
	UpdatePuck();
	HeroUpdate(); // Updates the player characters!
	UpdateHealth();
	Fireballs();
	EndMatch();
}

void Neon()
{
	Play::DrawBackground(5);
	if (gameState.playingMatch == TRUE)
	{
		HeroSelect();
		gameState.playingMatch = FALSE;
	}
	HeroUpdate();
	UpdatePuck();
	UpdateHealth();
	Fireballs();
	EndMatch();
}

void Prague()
{
	Play::DrawBackground(6);
	if (gameState.playingMatch == TRUE)
	{
		HeroSelect();
		gameState.playingMatch = FALSE;
	}
	HeroUpdate();
	UpdatePuck();
	UpdateHealth();
	Fireballs();
	EndMatch();
}

void ThunderLeagueArena()
{
	Play::DrawBackground(7);
	if (gameState.playingMatch == TRUE)
	{
		HeroSelect();
		gameState.playingMatch = FALSE;
	}
	HeroUpdate();
	UpdatePuck();
	UpdateHealth();
	Fireballs();
	EndMatch();
}
// ------------------------------------------

void EndMatch()
{
	if (gameState.player1Score == 7 || gameState.player2Score == 7)
	{
		Play::StopAudioLoop("snd_elven_forest_music");
		Play::StopAudioLoop("snd_neon_music");
		Play::StopAudioLoop("snd_prague_music");
		Play::StopAudioLoop("snd_thunder_league_arena_music");
		// Destroy all game objects:
		GameObject& obj_alex1 = Play::GetGameObjectByType(TYPE_ALEX1);
		GameObject& obj_toshi1 = Play::GetGameObjectByType(TYPE_TOSHI1);
		GameObject& obj_cosmo1 = Play::GetGameObjectByType(TYPE_COSMO1);
		GameObject& obj_kudo1 = Play::GetGameObjectByType(TYPE_KUDO1);
		GameObject& obj_alex2 = Play::GetGameObjectByType(TYPE_ALEX2);
		GameObject& obj_toshi2 = Play::GetGameObjectByType(TYPE_TOSHI2);
		GameObject& obj_cosmo2 = Play::GetGameObjectByType(TYPE_COSMO2);
		GameObject& obj_kudo2 = Play::GetGameObjectByType(TYPE_KUDO2);
		GameObject& obj_player1Portrait = Play::GetGameObjectByType(TYPE_PLAYER1_PORTRAIT);
		GameObject& obj_player2Portrait = Play::GetGameObjectByType(TYPE_PLAYER2_PORTRAIT);
		GameObject& obj_player1Health = Play::GetGameObjectByType(TYPE_PLAYER1_HEALTH);
		GameObject& obj_player2Health = Play::GetGameObjectByType(TYPE_PLAYER2_HEALTH);
		GameObject& obj_player1Marker = Play::GetGameObjectByType(TYPE_PLAYER1_MARKER);
		GameObject& obj_player2Marker = Play::GetGameObjectByType(TYPE_PLAYER2_MARKER);
		GameObject& obj_puck = Play::GetGameObjectByType(TYPE_PUCK);
		GameObject& obj_shadow = Play::GetGameObjectByType(TYPE_SHADOW);
		obj_alex1.type = TYPE_DESTROYED;
		obj_toshi1.type = TYPE_DESTROYED;
		obj_cosmo1.type = TYPE_DESTROYED;
		obj_kudo1.type = TYPE_DESTROYED;
		obj_alex2.type = TYPE_DESTROYED;
		obj_toshi2.type = TYPE_DESTROYED;
		obj_cosmo2.type = TYPE_DESTROYED;
		obj_kudo2.type = TYPE_DESTROYED;
		obj_player1Portrait.type = TYPE_DESTROYED;
		obj_player2Portrait.type = TYPE_DESTROYED;
		obj_player1Health.type = TYPE_DESTROYED;
		obj_player2Health.type = TYPE_DESTROYED;
		obj_player1Marker.type = TYPE_DESTROYED;
		obj_player2Marker.type = TYPE_DESTROYED;
		obj_puck.type = TYPE_DESTROYED;
		obj_shadow.type = TYPE_DESTROYED;
		std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
		for (int id_destroyed : vDestroyed)
		{
			GameObject& obj_destroyed = Play::GetGameObject(id_destroyed);
			Play::DestroyGameObject(id_destroyed);
		}
		std::vector<int> vPlayer1Fireballs = Play::CollectGameObjectIDsByType(TYPE_PLAYER1_FIREBALL);
		for (int id_fireball : vPlayer1Fireballs)
		{
			Play::DestroyGameObject(id_fireball);
		}
		std::vector<int> vPlayer2Fireballs = Play::CollectGameObjectIDsByType(TYPE_PLAYER2_FIREBALL);
		for (int id_fireball : vPlayer2Fireballs)
		{
			Play::DestroyGameObject(id_fireball);
		}
		if (gameState.player1Score == 7)
		{
			Play::DrawFontText("silver_blue137px", "PLAYER 1 WINS!", { DISPLAY_WIDTH / 2, 225 }, Play::CENTRE);
			Play::DrawFontText("silver_blue69px", "Press 'SPACE' to return to menu!", { DISPLAY_WIDTH / 2, 300 }, Play::CENTRE);
		}
		if (gameState.player2Score == 7)
		{
			Play::DrawFontText("silver_red137px", "PLAYER 2 WINS!", { DISPLAY_WIDTH / 2, 225 }, Play::CENTRE);
			Play::DrawFontText("silver_red69px", "Press 'SPACE' to return to menu!", { DISPLAY_WIDTH / 2, 300 }, Play::CENTRE);
		}
		if (Play::KeyPressed(VK_SPACE))
		{
			// Destroy score counter:
			GameObject& obj_scoreCounter = Play::GetGameObjectByType(TYPE_SCORE_COUNTER);
			obj_scoreCounter.type = TYPE_DESTROYED;
			std::vector<int> vDestroyed = Play::CollectGameObjectIDsByType(TYPE_DESTROYED);
			for (int id_destroyed : vDestroyed)
			{
				GameObject& obj_destroyed = Play::GetGameObject(id_destroyed);
				Play::DestroyGameObject(id_destroyed);
			}
			// Reset all values:
			gameState.player1Score = 0;
			gameState.player2Score = 0;
			gameState.player1Character = 0;
			gameState.player2Character = 0;
			gameState.player1Health = 5;
			gameState.player2Health = 5;
			gameState.player1Right = TRUE;
			gameState.player2Right = FALSE;
			gameState.player1CoolDown = TRUE;
			gameState.player2CoolDown = TRUE;
			gameState.map = 0;
			Play::StartAudioLoop("snd_main_menu_music");
			gameState.playState = STATE_MAIN_MENU;
		}
	}
}
// ------------------------------------------

int MainGameExit( void ) // Gets called once when the player quits the game
{
	Play::DestroyManager();
	return PLAY_OK;
}
