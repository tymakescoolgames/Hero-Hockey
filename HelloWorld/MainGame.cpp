// Ty Reid
// Hero Hockey Acorn Championship
// ------------------------------------------

/*
KUDO -  AIR - ACTIVE = BINKY (AIR DASH) - PASSIVE = FEATHER STEP (INCREASED MOVEMENT SPEED)
COSMO  - WATER - ACTIVE = WATER WALK (OBSTACLE PHASE) - PASSIVE = FLOW STATE (SCREEN WRAPPING)
TOSHI  - EARTH - ACTIVE = GFDSGFSDGS - PASSIVE = FDSFSDFAFAFA

*/

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include <ctime>

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
	int player1Helath = 5;
	int player2Health = 5;
	int player1Score = 0;
	int player2Score = 0;
	bool characterSelect = FALSE;
	bool mapSelect = FALSE;
	bool playingMatch = FALSE;
	int map = 0;
	bool matchStart = FALSE;
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
	// ------------------------------------------
	TYPE_MAP1,
	TYPE_MAP2,
	TYPE_MAP3,
	TYPE_MAP4,
	TYPE_PUCK,
	TYPE_DESTROYED,
};

void HandleAlex();
void HandleToshi();
void HandleCosmo();
void HandleKudo();
void HeroSelect();
void UpdatePuck();
void LoadingScreen();
void MainMenuScreen();
void CharacterSelectionScreen();
void MapSelectionScreen();
void ElvenForest();
void Neon();
void Prague();
void ThunderLeagueArena();

int DISPLAY_WIDTH = 1280;
int DISPLAY_HEIGHT = 720;
int DISPLAY_SCALE = 1;

// The entry point for a PlayBuffer program
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


void HeroSelect()
{
	if (gameState.player1Character == 1)
	{
		Play::CreateGameObject(TYPE_ALEX1, { 425, 477 }, 0, "spr_alex_standing_right");
	}
	if (gameState.player1Character == 2)
	{
		Play::CreateGameObject(TYPE_TOSHI1, { 425, 477 }, 0, "spr_toshi_standing_right");
	}
	if (gameState.player1Character == 3)
	{
		Play::CreateGameObject(TYPE_COSMO1, { 425, 477 }, 0, "spr_cosmo_standing_right");
	}
	if (gameState.player1Character == 4)
	{
		Play::CreateGameObject(TYPE_KUDO1, { 425, 477 }, 0, "spr_kudo_standing_right");
	}
}

void HandleAlex()
{

}

void HandleToshi()
{

}

void HandleCosmo()
{
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_PLAYER1);

	// Player controls:
	obj_player1.velocity = { 0, 0 };
	if (Play::KeyDown(VK_UP))
	{
		obj_player1.velocity = { 0, -3.0f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_right_4", 0.20f);
			obj_player1.velocity = { 3.0f, -3.0f };
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_left_4", 0.20f);
			obj_player1.velocity = { -3.0f, -3.0f };
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_cosmo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		obj_player1.velocity = { 0, 3.0f };
		if (Play::KeyDown(VK_RIGHT))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_right_4", 0.20f);
			obj_player1.velocity = { 3.0f, 3.0f };
		}
		else if (Play::KeyDown(VK_LEFT))
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_left_4", 0.20f);
			obj_player1.velocity = { -3.0f, 3.0f };
		}
		else
		{
			Play::SetSprite(obj_player1, "spr_cosmo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		Play::SetSprite(obj_player1, "spr_cosmo_right_4", 0.20f);
		obj_player1.velocity = { 3.0f, 0 };
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		Play::SetSprite(obj_player1, "spr_cosmo_left_4", 0.20f);
		obj_player1.velocity = { -3.0f, 0 };
	}
	else
	{
		Play::SetSprite(obj_player1, "spr_toshi_small_blue", 0.0f);
	}
}

void HandleKudo()
{
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_PLAYER2);

	// Player controls:
	obj_player2.velocity = { 0, 0 };
	if (Play::KeyDown('W'))
	{
		obj_player2.velocity = { 0, -3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, -3.25f };
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, -3.25f };
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_kudo_up_4", 0.20f);
		}
	}
	else if (Play::KeyDown('S'))
	{
		obj_player2.velocity = { 0, 3.5f };
		if (Play::KeyDown('D'))
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_right_4", 0.20f);
			obj_player2.velocity = { 3.25f, 3.25f };
		}
		else if (Play::KeyDown('A'))
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_left_4", 0.20f);
			obj_player2.velocity = { -3.25f, 3.25f };
		}
		else
		{
			Play::SetSprite(obj_player2, "spr_kudo_down_4", 0.20f);
		}
	}
	else if (Play::KeyDown('D'))
	{
		Play::SetSprite(obj_player2, "spr_kudo_right_4", 0.20f);
		obj_player2.velocity = { 3.5f, 0 };
	}
	else if (Play::KeyDown('A'))
	{
		Play::SetSprite(obj_player2, "spr_kudo_left_4", 0.20f);
		obj_player2.velocity = { -3.5f, 0 };
	}
	else
	{
		Play::SetSprite(obj_player2, "spr_kudo_small_blue", 0.0f);
	}
	// Binky:
	if (Play::KeyDown(VK_SHIFT))
	{
		obj_player2.velocity = (obj_player2.velocity) * 3.0;
	}
}

void UpdatePuck()
{
	GameObject& obj_puck = Play::GetGameObjectByType(TYPE_PUCK);
	// Get both players to test for collision:
	GameObject& obj_player1 = Play::GetGameObjectByType(TYPE_PLAYER1);
	GameObject& obj_player2 = Play::GetGameObjectByType(TYPE_PLAYER2);

	Play::SetSprite(obj_puck, "spr_puck_4", 0.20f);

	if (Play::IsColliding(obj_player1, obj_puck))
	{
		//Play::PlayAudio("snd_puck_hit_1");
		obj_puck.velocity = 1.75*obj_player1.velocity;
	}
	else if (Play::IsColliding(obj_player2, obj_puck))
	{
		//Play::PlayAudio("snd_puck_hit_2");
		obj_puck.velocity = 1.75 * obj_player2.velocity;
	}
	
	if (Play::IsLeavingDisplayArea(obj_puck, Play::VERTICAL))
	{
		Play::PlayAudio("snd_bump");
		obj_puck.pos = obj_puck.oldPos;
		obj_puck.velocity.y *= -1;
	}
	else if (Play::IsLeavingDisplayArea(obj_puck, Play::HORIZONTAL))
	{
		Play::PlayAudio("snd_bump");
		obj_puck.pos = obj_puck.oldPos;
		obj_puck.velocity.x *= -1;
	}
}

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
		Play::SetSprite(obj_alex, "spr_toshi_large_blue", 0.0f);
	}
	if (gameState.player2Character == 1)
	{
		Play::SetSprite(obj_alex, "spr_toshi_large_red", 0.0f);
	}
	if (gameState.player1Character == 1 && gameState.player2Character == 1)
	{
		Play::SetSprite(obj_alex, "spr_toshi_large_blue_and_red", 0.0f);
	}
	if (gameState.player1Character != 1 && gameState.player2Character != 1)
	{
		Play::SetSprite(obj_alex, "spr_toshi_large", 0.0f);
	}
	Play::UpdateGameObject(obj_alex);
	Play::DrawObjectRotated(obj_alex);
	// Toshi:	
	if (gameState.player1Character == 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large_blue", 0.0f);
	}
	if (gameState.player2Character == 2)
	{
		Play::SetSprite(obj_toshi, "spr_toshi_large_red", 0.0f);
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
	}
	if (gameState.player2Character == 3)
	{
		Play::SetSprite(obj_cosmo, "spr_cosmo_large_red", 0.0f);
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
	}
	if (gameState.player2Character == 4)
	{
		Play::SetSprite(obj_kudo, "spr_kudo_large_red", 0.0f);
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
	Play::DrawDebugText({ DISPLAY_WIDTH / 2, 50 }, "Use a and d/left and right along with c/spacebar to select your Rink!");

	if (gameState.mapSelect == TRUE)
	{
		Play::CreateGameObject(TYPE_MAP1, { 190, 475 }, 0, "spr_elven_forest");
		Play::CreateGameObject(TYPE_MAP2, { 505, 475 }, 0, "spr_neon");
		Play::CreateGameObject(TYPE_MAP3, { 820, 475 }, 0, "spr_prague");
		Play::CreateGameObject(TYPE_MAP4, { 1125, 475 }, 0, "spr_thunder_league_arena");	
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
	}
	if (gameState.map != 1)
	{
		Play::SetSprite(obj_map1, "spr_elven_forest", 0.0f);
	}
	if (gameState.map == 2)
	{
		Play::SetSprite(obj_map2, "spr_neon_pink", 0.0f);
	}
	if (gameState.map != 2)
	{
		Play::SetSprite(obj_map2, "spr_neon", 0.0f);
	}
	if (gameState.map == 3)
	{
		Play::SetSprite(obj_map3, "spr_prague_pink", 0.0f);
	}
	if (gameState.map != 3)
	{
		Play::SetSprite(obj_map3, "spr_prague", 0.0f);
	}
	if (gameState.map == 4)
	{
		Play::SetSprite(obj_map4, "spr_thunder_league_arena_pink", 0.0f);
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
			gameState.playState = STATE_MAP1;
		}
		if (gameState.map == 2)
		{
			gameState.playState = STATE_MAP2;
		}
		if (gameState.map == 3)
		{
			gameState.playState = STATE_MAP3;
		}
		if (gameState.map == 4)
		{
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

void ElvenForest()
{
	Play::DrawBackground(4);



	if (gameState.playingMatch == TRUE)
	{
		// Create Player characters:
		HeroSelect();

		// Create map obstacles:


		
		gameState.playingMatch = FALSE;
	}

}

void Neon()
{

}

void Prague()
{

}

void ThunderLeagueArena()
{

}

int MainGameExit( void ) // Gets called once when the player quits the game
{
	Play::DestroyManager();
	return PLAY_OK;
}
