#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "ExplotionObject.h"
#include "TextObject.h"
#include "PlayerPower.h"
#include "Geomeric.h"
#include "BossObject.h"
#include "AttackObject.h"
#include "FLyThreats.h"
#include <fstream>
#include <SDL_mixer.h>

BaseObject g_background; 
BaseObject m_background; 
BaseObject menu_background;
BaseObject l_background;
BaseObject w_background;
TTF_Font* font_time = NULL; 




bool InitData()
{
	bool success = true; 
	int ret = SDL_Init(SDL_INIT_VIDEO); 
	if (ret < 0)
	{
		return false; 
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); 

	g_window = SDL_CreateWindow("Game CPP SDL 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); 

	if (g_window == NULL)
	{
		success = false; 
	}
	else
	{
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED); 
		if (g_screen == NULL)
		{
			success = false; 
		}
		else
		{
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG; 
			if (!(IMG_Init(imgFlags) && imgFlags))
			{
				success = false; 
			}
		}

		if (TTF_Init() == -1)
		{
			success = false;
		}

		font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
		if (font_time == NULL)
		{
			success = false;
		}
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		success =  false; 
	}
	g_sound_bullet[0] = Mix_LoadWAV("mixer//Fireball+1.wav");
	g_sound_exp[0] = Mix_LoadWAV("mixer//Explosion.wav"); 
	g_sound_exp[1] = Mix_LoadWAV("mixer//Explosion.wav"); 
	get_coin[0] = Mix_LoadWAV("mixer//coin.wav"); 
	hitted[0] = Mix_LoadWAV("mixer//hitted.wav");

	if (g_sound_exp[0] == NULL || g_sound_bullet[0] == NULL || g_sound_exp[1] == NULL || get_coin[0] == NULL||hitted[0] == NULL )
	{
		success = false; 
	}
	return success; 
}

bool LoadBackground()
{
	bool ret = g_background.LoadImg("img//backgrou	nd.png", g_screen); 
	if (ret == false)
		return false; 
	return true; 
}
bool LoadmBackground()
{
	bool ret = m_background.LoadImg("img//menu.png", g_screen);

	if (ret == false)
		return false;
	return true;
}

bool Loadmenuhighscore()
{
	bool ret = menu_background.LoadImg("img//highscore.png", g_screen);

	if (ret == false)
		return false;
	return true;
}

bool LoadLoss()
{
	bool ret = l_background.LoadImg("img//lossgame.png", g_screen);
	if (ret == false)
		return false;
	return true;
}

bool Loadwin()
{
	bool ret = w_background.LoadImg("img//wingame.png", g_screen);
	if (ret == false)
		return false;
	return true;
}


int getHighScore() {
	std::ifstream file("highscore//highscore.txt");
	int highScore = 0;
	if (file) {
		file >> highScore;
		file.close();
	}
	return highScore;
}

void updateHighScore(int score) {
	int highScore = getHighScore();
	if (score > highScore) {
		std::ofstream file("highscore//highscore.txt");
		if (file) {
			file << score;
			file.close();
		}
	}
}



void close()
{
	g_background.Free(); 
	m_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL; 

	SDL_DestroyWindow(g_window);
	g_window = NULL; 

	IMG_Quit();
	SDL_Quit();
} 


std::vector<BossObject*> MakeBossList()
{
	std::vector<BossObject*> list_boss; 
	BossObject* dynamic_boss = new BossObject[1]; 
	BossObject* bossObject = (dynamic_boss + 0); 
	if (bossObject != NULL)
	{
		bossObject->LoadImg("img//boss_object.png", g_screen);
		bossObject->set_clips();
		int xPosBoss = MAX_MAP_X * TILE_SIZE - SCREEN_WIDTH * 0.6;
		bossObject->set_xpos(xPosBoss);
		bossObject->set_ypos(200);
		list_boss.push_back(bossObject); 

	}
	return list_boss; 


}

std::vector<FlyThreats*> MakeFlyThreats()
{
	std::vector<FlyThreats*> list_f_threats; 
	FlyThreats* fly_threats = new FlyThreats[20];
	for (int i = 0; i < 20; i++)
	{
		FlyThreats* f_threats = (fly_threats + i);
		if (f_threats != NULL)
		{
			f_threats->LoadImg("img//dragon.png", g_screen);
			f_threats->set_clips();
			f_threats->set_xpos(i * 1200 + 1600);
			f_threats->set_ypos(35);
			
			BulletObject* f_bullet = new BulletObject();
			f_threats->InitBullet(f_bullet , g_screen);
			list_f_threats.push_back(f_threats);
		}
	}
	return list_f_threats; 
}

std::vector<ThreatsObject*> MakeThreatList()
{
	std::vector<ThreatsObject*> list_threats; 

	ThreatsObject* dynamic_threats = new ThreatsObject[20];
	for (int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (dynamic_threats + i); 
		if ( p_threat != NULL)
		{
			p_threat->LoadImg("img//threat_left.png", g_screen); 
			p_threat->set_clips(); 
			p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT); 
			p_threat->set_x_pos(500 + i * 550); 
			p_threat->set_y_pos(200);


			int pos1 = p_threat->get_x_pos() - 60; 
			int pos2 = p_threat->get_x_pos() + 60; 
			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1); 

			list_threats.push_back(p_threat); 
		}
	}


	ThreatsObject* threats_objs = new ThreatsObject[20]; 

	for (int i = 0; i < 20; i++)
	{
		ThreatsObject* p_threat = (threats_objs + i); 
		if (p_threat != NULL)
		{
			p_threat->LoadImg("img/threat_level.png", g_screen);
			p_threat->set_clips(); 
			p_threat->set_x_pos(i*1200 + 1500 ); 
			p_threat->set_y_pos(250); 
			p_threat->set_type_move(ThreatsObject::STATIC_THREAT); 
			p_threat->set_input_left(0);
			BulletObject* p_bullet = new BulletObject(); 
			p_threat->InitBullet(p_bullet, g_screen); 
			list_threats.push_back(p_threat); 
		}
	}

	return list_threats;  
}

int main(int argc, char* argv[])
{

	


	ImpTimer fps_timer;
	ImpTimer real_time_of_game;
	bool pause_game = false; 
	real_time_of_game.start();
	if (InitData() == false)
		return -1;
	if (LoadBackground() == false)
		return -1;
	if (LoadmBackground() == false)
		return -1;
	if (Loadmenuhighscore() == false)
		return -1;
	if (LoadLoss() == false)
	{
		return -1; 
	}
	if (Loadwin() == false) return -1; 

	srand(time(NULL)); 
	Mix_Music* g_music = Mix_LoadMUS("mixer//sound.mp3");
	if (g_music == NULL)
	{
		return -1;
	}

	Mix_PlayMusic(g_music, -1);

	int hpboss = 20; 

	GameMap game_map;
	game_map.LoadMap("map/map01.dat");
	game_map.LoadTiles(g_screen);

	MainObject p_player;
	p_player.LoadImg("img//player_right.png", g_screen);
	p_player.set_clips();

	AttackObject attack_player;
	attack_player.LoadImg("img//Attack2.png", g_screen);
	attack_player.set_clips();


	PlayerPower player_power;
	player_power.Init(g_screen);

	PlayerMoney player_money;
	player_money.Init(g_screen);
	player_money.SetPos(SCREEN_WIDTH * 0.5 - 280, 8);


	std::vector<ThreatsObject*> threats_list = MakeThreatList();

	std::vector<FlyThreats*> fly_threats = MakeFlyThreats(); 
	// Boss Threat 
	std::vector<BossObject*> boss_list = MakeBossList(); 


	ExplosionObject exp_threat;
	bool tRet = exp_threat.LoadImg("img//exp3.png", g_screen);
	if (!tRet) return -1;
	exp_threat.set_clip();


	TextObject time_game;
	time_game.SetColor(TextObject::WHITE_TEXT);

	TextObject mark_game;
	mark_game.SetColor(TextObject::WHITE_TEXT);
	UINT mark_value = 0;

	TextObject money_game;
	money_game.SetColor(TextObject::BLACK_TEXT);

	TextObject start_button;
	TextObject quit_button;
	TextObject guide_button;
	TextObject end; 
	TextObject highscore; 
	TextObject highscoreval; 
	TextObject continuee; 


	bool is_quit = false;
	bool start = true;



	while (start && !is_quit) {
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				start = false;
				is_quit = true;
			}
			p_player.HandelInputAction(g_event, g_screen , g_sound_bullet );
			attack_player.HandelInputAction(g_event, g_screen,g_sound_bullet );
		}

		//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
		//SDL_RenderClear(g_screen);

		m_background.Render(g_screen, NULL);

		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		start_button.SetText("START");
		guide_button.SetText("HIGH SCORE");
		quit_button.SetText("QUIT");

		start_button.LoadFromRenderText(font_time, g_screen);
		if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 -80  - 15 && mouseY <= 480 -80  + 37 - 15) {
			start_button.SetColor(TextObject::BLACK_TEXT);
			if (g_event.type == SDL_MOUSEBUTTONDOWN) {
				if (g_event.button.button = SDL_BUTTON_RIGHT)
				{
					start = false;
				}
			}
		}
		else {
			start_button.SetColor(TextObject::RED_TEXT);
		}

		start_button.RenderText(g_screen, 1280 / 2 - 40, 480 - 80  );

		guide_button.LoadFromRenderText(font_time, g_screen);
		if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 - 80 - 15 + 50 && mouseY <= 480 - 80  + 37 - 15 + 50) {
			guide_button.SetColor(TextObject::BLACK_TEXT);
			if (g_event.type == SDL_MOUSEBUTTONDOWN) {
				if (g_event.button.button = SDL_BUTTON_RIGHT)
				{
					while (!is_quit) {
						while (SDL_PollEvent(&g_event) != 0)
						{
							if (g_event.type == SDL_QUIT)
							{
								is_quit = true;
							}
							p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
							attack_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
						}

						//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
						//SDL_RenderClear(g_screen);

						menu_background.Render(g_screen, NULL);
						quit_button.SetText("QUIT");

						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);

						int maxscore = getHighScore();
						std::string maxhighscore = std::to_string(maxscore);
						std::string strhs("");
						strhs += maxhighscore;

						highscoreval.SetText(strhs);
						highscoreval.LoadFromRenderText(font_time, g_screen);
						highscoreval.RenderText(g_screen, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT / 2);

						quit_button.LoadFromRenderText(font_time, g_screen);
						if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 120 && mouseY <= 480 / 2 + 37 - 15 + 120) {
							quit_button.SetColor(TextObject::BLACK_TEXT);
							if (g_event.type == SDL_MOUSEBUTTONDOWN) {
								if (g_event.button.button = SDL_BUTTON_RIGHT)
								{
									is_quit = true;
								}
							}
						}
						else {
							quit_button.SetColor(TextObject::RED_TEXT);
						}
						quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 / 2 + 114);

						SDL_RenderPresent(g_screen);
						SDL_Delay(10);

					}
				}
			}

		}
		else {
			guide_button.SetColor(TextObject::RED_TEXT);
		}
		guide_button.RenderText(g_screen, 1280 / 2 - 40 , 480 - 80 + 40 );

		quit_button.LoadFromRenderText(font_time, g_screen);
		if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480  - 15  && mouseY <= 480  + 45 - 15 ) {
			quit_button.SetColor(TextObject::BLACK_TEXT);
			if (g_event.type == SDL_MOUSEBUTTONDOWN) {
				if (g_event.button.button = SDL_BUTTON_RIGHT)
				{
					is_quit = true;
				}
			}
		}
		else {
			quit_button.SetColor(TextObject::RED_TEXT);
		}
		quit_button.RenderText(g_screen, 1280 / 2 - 40 , 480 );

		SDL_RenderPresent(g_screen);
		SDL_Delay(10);

	}

	while (!is_quit)
	{
		fps_timer.start();
		while (SDL_PollEvent(&g_event) != 0)
		{
			if (g_event.type == SDL_QUIT)
			{
				start = false;
				is_quit = true;
			}
			p_player.HandelInputAction(g_event, g_screen,g_sound_bullet);
			attack_player.set_pos(p_player.getxpos(), p_player.getypos());
			attack_player.HandelInputAction(g_event, g_screen,g_sound_bullet);
		}

		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);
		Map map_data = game_map.getMap();

		p_player.HandleBullet(g_screen);
		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);



		attack_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		attack_player.Show(g_screen);


		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);
		int x = p_player.getheart();
		int y = p_player.gettrap(); 

		if (x == 1)
		{
			player_power.InitCrease();
		}
		if (y == 1)
		{
			player_power.Decrease() ;
		}
		if (p_player.checkfall() == 1)
		{
			player_power.Decrease(); 

		}

		if (g_event.type == SDL_KEYDOWN )
		{
			if ( g_event.key.keysym.sym = SDLK_ESCAPE )
				pause_game = true;

		}


		while ( pause_game ) {
			while (SDL_PollEvent(&g_event) != 0)
			{
				if (g_event.type == SDL_QUIT)
				{
					start = false;
					is_quit = true;
				}
				p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
			}

			//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
			//SDL_RenderClear(g_screen);

			m_background.Render(g_screen, NULL);

			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			continuee.SetText("CONTINUE");
			quit_button.SetText("QUIT");

			continuee.LoadFromRenderText(font_time, g_screen);
			if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 - 80 - 15 && mouseY <= 480 - 80 + 37 - 15) {
				continuee.SetColor(TextObject::BLACK_TEXT);
				if (g_event.type == SDL_MOUSEBUTTONDOWN) {
					if (g_event.button.button = SDL_BUTTON_RIGHT)
					{
						pause_game = false ;
					}
				}
			}
			else {
				continuee.SetColor(TextObject::RED_TEXT);
			}

			continuee.RenderText(g_screen, 1280 / 2 - 40, 480 - 80);
			quit_button.LoadFromRenderText(font_time, g_screen);
			if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 - 15 && mouseY <= 480 + 45 - 15) {
				quit_button.SetColor(TextObject::BLACK_TEXT);
				if (g_event.type == SDL_MOUSEBUTTONDOWN) {
					if (g_event.button.button = SDL_BUTTON_RIGHT)
					{
						is_quit = true;
					}
				}
			}
			else {
				quit_button.SetColor(TextObject::RED_TEXT);
			}
			quit_button.RenderText(g_screen, 1280 / 2 - 40, 480);

			SDL_RenderPresent(g_screen);
			SDL_Delay(10);

		}



		//draw geometric 
		GeometricFormat rectangle_size(0, 0, SCREEN_WIDTH, 40);
		ColorData color_data(0, 80, 150);
		Geometric::RenderRectangle(rectangle_size, color_data, g_screen);

		GeometricFormat outLineSize(1, 1, SCREEN_WIDTH - 1, 38);
		ColorData color_data2(0, 80, 150);

		Geometric::RenderOutline(outLineSize, color_data2, g_screen);
		

		player_power.Show(g_screen);
		player_money.Show(g_screen);

		if ( player_power.getnumber() == 0 ) 
		{
			while (!is_quit) {
				while (SDL_PollEvent(&g_event) != 0)
				{
					if (g_event.type == SDL_QUIT)
					{
						is_quit = true;
					}
					p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
					attack_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
				}

				//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
				//SDL_RenderClear(g_screen);
				updateHighScore(mark_value);

				l_background.Render(g_screen, NULL);

				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				quit_button.SetText("QUIT");
				highscore.SetText("High Score");
				highscore.LoadFromRenderText(font_time, g_screen);
				if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 - 15 && mouseY <= 480  + 37 - 15) {
					highscore.SetColor(TextObject::BLACK_TEXT);
					if (g_event.type == SDL_MOUSEBUTTONDOWN) {
						if (g_event.button.button = SDL_BUTTON_RIGHT)
						{
							break;

						}
					}
				}
				else {
					highscore.SetColor(TextObject::RED_TEXT);
				}

				highscore.RenderText(g_screen, 1280 / 2 - 40, 480 );

				quit_button.LoadFromRenderText(font_time, g_screen);
				if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480  - 15 + 30 && mouseY <= 480  + 37 - 15 + 30) {
					quit_button.SetColor(TextObject::BLACK_TEXT);
					if (g_event.type == SDL_MOUSEBUTTONDOWN) {
						if (g_event.button.button = SDL_BUTTON_RIGHT)
						{
							is_quit = true;
						}
					}
				}
				else {
					quit_button.SetColor(TextObject::RED_TEXT);
				}
				quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 + 30);

				SDL_RenderPresent(g_screen);
				SDL_Delay(10);

			}
			while (!is_quit) {
				while (SDL_PollEvent(&g_event) != 0)
				{
					if (g_event.type == SDL_QUIT)
					{
						is_quit = true;
					}
					p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
					attack_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
				}

				//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
				//SDL_RenderClear(g_screen);

				menu_background.Render(g_screen, NULL);
				quit_button.SetText("QUIT");

				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				int maxscore = getHighScore();
				std::string maxhighscore = std::to_string(maxscore);
				std::string strhs("");
				strhs += maxhighscore;

				highscoreval.SetText(strhs);
				highscoreval.LoadFromRenderText(font_time, g_screen);
				highscoreval.RenderText(g_screen, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT / 2);

				quit_button.LoadFromRenderText(font_time, g_screen);
				if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 120 && mouseY <= 480 / 2 + 37 - 15 + 120) {
					quit_button.SetColor(TextObject::BLACK_TEXT);
					if (g_event.type == SDL_MOUSEBUTTONDOWN) {
						if (g_event.button.button = SDL_BUTTON_RIGHT)
						{
							is_quit = true;
						}
					}
				}
				else {
					quit_button.SetColor(TextObject::RED_TEXT);
				}
				quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 / 2 + 114);

				SDL_RenderPresent(g_screen);
				SDL_Delay(10);

			}

		}

		
		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			int val2 = abs(p_player.getxpos() - p_threat->get_x_pos());
			if (p_threat != NULL && val2 <= SCREEN_WIDTH + 500 )
			{
					p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
					p_threat->ImpMoveType(g_screen); 
					p_threat->DoPlayer(map_data);
					p_threat->get_player_rect(p_player.GetRect());
					p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
					p_threat->Show(g_screen);


					SDL_Rect rect_player = p_player.GetRectFrame();
					bool bCol1 = false;
					std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
					for (int jj = 0; jj < tBullet_list.size(); ++jj)
					{
						BulletObject* pt_bullet = tBullet_list.at(jj);
						if (pt_bullet)
						{
							bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
							if (bCol1)
							{
								p_threat->SetBulletRect(jj);
							}
						}	
					}

					SDL_Rect rect_threat = p_threat->GetRectFrame();
					bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
					if (bCol2 || bCol1)
					{
						if ( player_power.getnumber() > 0 )
						{
							p_player.SetRect(0, 0);
							p_player.set_comeback_time(9);
							SDL_Delay(400);
							player_power.Decrease();
							player_power.Render(g_screen);
							Mix_PlayChannel(-1, hitted[0], 0);
							continue;
						}
						else
						{
							if ((MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK))
							{
								p_threat->Free();
								close();
								SDL_Quit();
								return 0;
								updateHighScore(mark_value); 
							}

						}
					}
			}
		}


		int frame_exp_width = exp_threat.get_frame_width_();
		int frame_exp_height = exp_threat.get_frame_height_();
		std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
		for (int r = 0; r < bullet_arr.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < threats_list.size(); t++)
				{
					ThreatsObject* obj_threat = threats_list.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_width_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{
							mark_value++;
							for (int ex = 0; ex < 8; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}

							p_player.RemoveBullet(r);
							obj_threat->Free();
							threats_list.erase(threats_list.begin() + t);
							Mix_PlayChannel(-1, g_sound_exp[0], 0); 

						}
					}
				}
			}
		}


		for (int i = 0; i < fly_threats.size(); i++)
		{
			FlyThreats* f_threat = fly_threats.at(i);
			int val2 = abs(p_player.getxpos() - f_threat->get_x_pos());
			if (f_threat != NULL && val2 <= SCREEN_WIDTH )
			{
				f_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				f_threat->DoPlayer(map_data);
				f_threat->get_player_rect(p_player.GetRect());
				f_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				f_threat->Show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				std::vector<BulletObject*> tBullet_list = f_threat->get_bullet_list();
				for (int jj = 0; jj < tBullet_list.size(); ++jj)
				{
					BulletObject* pt_bullet = tBullet_list.at(jj);
					if (pt_bullet)
					{
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
						if (bCol1)
						{
							break;
						}
					}
				}

				SDL_Rect rect_threat = f_threat->GetRect();
				if ( bCol1)
				{
					if (player_power.getnumber() > 0)
					{
						p_player.SetRect(0, 0);
						p_player.set_comeback_time(9);
						SDL_Delay(400);
						player_power.Decrease();
						player_power.Render(g_screen);
						Mix_PlayChannel(-1, hitted[0], 0);
						continue;
					}
					else
					{
						if ((MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK))
						{
							f_threat->Free();
							close();
							SDL_Quit();
							return 0;
							updateHighScore(mark_value);
						}

					}
				}
			}
		}
		int frame_exp_width2 = exp_threat.get_frame_width_();
		int frame_exp_height2 = exp_threat.get_frame_height_();
		std::vector<BulletObject*> bullet_arr2 = p_player.get_bullet_list();
		for (int r = 0; r < bullet_arr2.size(); r++)
		{
			BulletObject* p_bullet = bullet_arr2.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < fly_threats.size(); t++)
				{
					FlyThreats* obj_threat = fly_threats.at(t);
					if (obj_threat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = obj_threat->GetRect().x;
						tRect.y = obj_threat->GetRect().y;
						tRect.w = obj_threat->get_width_frame();
						tRect.h = obj_threat->get_width_frame();

						SDL_Rect bRect = p_bullet->GetRect();

						bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

						if (bCol)
						{
							mark_value++;
							for (int ex = 0; ex < 8; ex++)
							{
								int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
								int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

								exp_threat.set_frame(ex);
								exp_threat.SetRect(x_pos, y_pos);
								exp_threat.Show(g_screen);
							}

							p_player.RemoveBullet(r);
							obj_threat->Free();
							fly_threats.erase(fly_threats.begin() + t);
							Mix_PlayChannel(-1, g_sound_exp[0], 0);

						}
					}
				}
			}
		}


		// Show game time 

		std::string str_time = " Time: ";
		Uint32 time_val = SDL_GetTicks() / 1000;
		Uint32 val_time = 300 - time_val;
		if (val_time <= 0)
		{
			if ((MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK))
			{
				is_quit = true;
				break;
				updateHighScore(mark_value); 
			}

		}

		else
		{
			std::string str_val = std::to_string(val_time);
			str_time += str_val;

			time_game.SetText(str_time);
			time_game.LoadFromRenderText(font_time, g_screen);
			time_game.RenderText(g_screen, SCREEN_WIDTH - 200, 15);
		}

		std::string val_str_mark = std::to_string(mark_value);
		std::string strMark("Mark: ");
		strMark += val_str_mark;

		mark_game.SetText(strMark);
		mark_game.LoadFromRenderText(font_time, g_screen);
		mark_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 50, 15);

		int money_countt = p_player.GetMoneyCount();
		std::string money_str = std::to_string(money_countt);

		money_game.SetText(money_str);
		money_game.LoadFromRenderText(font_time, g_screen);
		money_game.RenderText(g_screen, SCREEN_WIDTH * 0.5 - 250, 15);

		//Show Boss 
		int val = MAX_MAP_X * TILE_SIZE - (map_data.start_x_ + p_player.GetRect().x);
		if (val <= SCREEN_WIDTH)
		{
			for (int i = 0; i < boss_list.size(); i++)
			{
				BossObject* b_threat = boss_list.at(i);
				if (b_threat != NULL)
				{
					b_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
					b_threat->DoPlayer(map_data);
					b_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
					b_threat->Show(g_screen);

					SDL_Rect rect_player = p_player.GetRectFrame();
					bool bCol1 = false;
					std::vector<BulletObject*> tBullet_list = b_threat->get_bullet_list();
					for (int jj = 0; jj < tBullet_list.size(); ++jj)
					{
						BulletObject* pt_bullet = tBullet_list.at(jj);
						if (pt_bullet)
						{
							bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
							if (bCol1)
							{
								break;
							}
						}
					}

					SDL_Rect rect_threat = b_threat->GetRect();
					bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
					if (bCol2 || bCol1)
					{
						if (player_power.getnumber() > 0)
						{
							p_player.SetRect(0, 0);
							p_player.set_comeback_time(9);
							SDL_Delay(400);
							player_power.Decrease();
							player_power.Render(g_screen);
							Mix_PlayChannel(-1, hitted[0], 0);
							continue;
						}
						else
						{
							if ((MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK))
							{
								b_threat->Free();
								close();
								SDL_Quit();
								return 0;
								updateHighScore(mark_value); 
							}

						}
					}

				}
			}


			int frame_exp_width = exp_threat.get_frame_width_();
			int frame_exp_height = exp_threat.get_frame_height_();
			std::vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
			for (int r = 0; r < bullet_arr.size(); r++)
			{
				BulletObject* p_bullet = bullet_arr.at(r);
				if (p_bullet != NULL)
				{
					for (int t = 0; t < boss_list.size(); t++)
					{
						BossObject* obj_threat = boss_list.at(t);
						if (obj_threat != NULL)
						{
							SDL_Rect tRect;
							tRect.x = obj_threat->GetRect().x;
							tRect.y = obj_threat->GetRect().y;
							tRect.w = obj_threat->get_width_frame();
							tRect.h = obj_threat->get_width_frame();

							SDL_Rect bRect = p_bullet->GetRect();

							bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);

							if (bCol)
							{
								hpboss--; 
								p_player.RemoveBullet(r);
								if (hpboss == 0)
								{
									for (int ex = 0; ex < 8; ex++)
									{
										int x_pos = p_bullet->GetRect().x - frame_exp_width * 0.5;
										int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

										exp_threat.set_frame(ex);
										exp_threat.SetRect(x_pos, y_pos);
										exp_threat.Show(g_screen);
									}
									obj_threat->Free();
									boss_list.erase(boss_list.begin() + t);
									while (!is_quit) {
										while (SDL_PollEvent(&g_event) != 0)
										{
											if (g_event.type == SDL_QUIT)
											{
												is_quit = true;
											}
											p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
											attack_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
										}

										//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
										//SDL_RenderClear(g_screen);
										updateHighScore(mark_value);

										l_background.Render(g_screen, NULL);

										int mouseX, mouseY;
										SDL_GetMouseState(&mouseX, &mouseY);
										quit_button.SetText("QUIT");
										highscore.SetText("High Score");
										highscore.LoadFromRenderText(font_time, g_screen);
										if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 && mouseY <= 480 / 2 + 37 - 15) {
											highscore.SetColor(TextObject::BLACK_TEXT);
											if (g_event.type == SDL_MOUSEBUTTONDOWN) {
												if (g_event.button.button = SDL_BUTTON_RIGHT)
												{
													break;

												}
											}
										}
										else {
											highscore.SetColor(TextObject::RED_TEXT);
										}

										highscore.RenderText(g_screen, 1280 / 2 - 40, 480 / 2);

										quit_button.LoadFromRenderText(font_time, g_screen);
										if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 120 && mouseY <= 480 / 2 + 37 - 15 + 120) {
											quit_button.SetColor(TextObject::BLACK_TEXT);
											if (g_event.type == SDL_MOUSEBUTTONDOWN) {
												if (g_event.button.button = SDL_BUTTON_RIGHT)
												{
													is_quit = true;
												}
											}
										}
										else {
											quit_button.SetColor(TextObject::RED_TEXT);
										}
										quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 / 2 + 114);

										SDL_RenderPresent(g_screen);
										SDL_Delay(10);

									}
									while (!is_quit) {
										while (SDL_PollEvent(&g_event) != 0)
										{
											if (g_event.type == SDL_QUIT)
											{
												is_quit = true;
											}
											p_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
											attack_player.HandelInputAction(g_event, g_screen, g_sound_bullet);
										}

										//SDL_SetRenderDrawColor(g_screen, 210, 210, 210, 210);
										//SDL_RenderClear(g_screen);

										menu_background.Render(g_screen, NULL);
										quit_button.SetText("QUIT");

										int mouseX, mouseY;
										SDL_GetMouseState(&mouseX, &mouseY);

										int maxscore = getHighScore();
										std::string maxhighscore = std::to_string(maxscore);
										std::string strhs("");
										strhs += maxhighscore;

										highscoreval.SetText(strhs);
										highscoreval.LoadFromRenderText(font_time, g_screen);
										highscoreval.RenderText(g_screen, SCREEN_WIDTH * 0.5, SCREEN_HEIGHT / 2);

										quit_button.LoadFromRenderText(font_time, g_screen);
										if (mouseX >= 1280 / 2 - 40 && mouseX <= 1280 / 2 - 40 + 90 && mouseY >= 480 / 2 - 15 + 120 && mouseY <= 480 / 2 + 37 - 15 + 120) {
											quit_button.SetColor(TextObject::BLACK_TEXT);
											if (g_event.type == SDL_MOUSEBUTTONDOWN) {
												if (g_event.button.button = SDL_BUTTON_RIGHT)
												{
													is_quit = true;
												}
											}
										}
										else {
											quit_button.SetColor(TextObject::RED_TEXT);
										}
										quit_button.RenderText(g_screen, 1280 / 2 - 40 + 5, 480 / 2 + 114);

										SDL_RenderPresent(g_screen);
										SDL_Delay(10);

									}
								}


								

							}
						}
					}
				}
			}
		}

			SDL_RenderPresent(g_screen);

			int time_of_game = real_time_of_game.get_ticks();
			attack_player.set_real_time_of_game(time_of_game);
			int real_imp_time = fps_timer.get_ticks();
			int time_one_frame = 1000 / FPS;
			if (real_imp_time < time_one_frame)
			{
				int delay_time = time_one_frame - real_imp_time;
				if (delay_time >= 0) SDL_Delay(delay_time);
			}
		}

		Mix_HaltMusic();
		Mix_FreeMusic(g_music);
		Mix_CloseAudio();

		for (int i = 0; i < threats_list.size(); i++)
		{
			ThreatsObject* p_threat = threats_list.at(i);
			if (p_threat)
			{
				p_threat->Free();
				p_threat = NULL;
			}

		}
		threats_list.clear();

		close();

		return 0;
}