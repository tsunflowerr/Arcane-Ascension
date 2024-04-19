#include "MainObject.h"
#include "PlayerPower.h"
#include <iostream>


MainObject::MainObject()
{
	frame_ = 0; 
	x_pos_ = 0; 
	y_pos_ = 0; 
	x_val_ = 0; 
	y_val_ = 0; 
	width_frame_ = 0; 
	height_frame_ = 0; 
	status_ = WALK_NONE ;
	input_type_.left_ = 0; 
	input_type_.right_ = 0; 
	input_type_.up_ = 0; 
	input_type_.down_ = 0; 
	input_type_.jump_ = 0; 
	on_ground_ = true; 
	map_x_ = 0; 
	map_y_ = 0; 
	come_back_time_ = 0; 
	money_count = 0;
	luckky_box = 2; 
	real_time_of_game_ = 0; 
	time_attack = 0; 
	delay_attack = 0; 
	checkheart = 0; 
	
}

MainObject::~MainObject()
{

}

bool MainObject::LoadImg(std::string path , SDL_Renderer* screen ) 
{
	bool ret = BaseObject::LoadImg(path, screen); 

	if (ret == true)
	{
		width_frame_ = rect_.w / 8; 
		height_frame_ = rect_.h; 
	}

	return ret; 
}

SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect; 
	rect.x = rect_.x; 
	rect.y = rect_.y; 
	rect.w = width_frame_; 
	rect.h = height_frame_; 

	return rect; 
}

void MainObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		frame_clip_[0].x = 0; 
		frame_clip_[0].y = 0; 
		frame_clip_[0].w = width_frame_; 
		frame_clip_[0].h = height_frame_;

		frame_clip_[1].x = width_frame_; 
		frame_clip_[1].y = 0; 
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2* width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3*width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4*width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5*width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6* width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

	}
}

void MainObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;
	

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0)
		{
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if ( (val1 == STATE_MONEY) || (val2 == STATE_MONEY) )
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney();
			}
			 
			else if ((val1 == LUCKKY_BOX) || (val2 == LUCKKY_BOX))
			{
				if (luckky_box != 0)
				{
					luckky_box--;
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
					
				}
				else 
				{
					map_data.tile[y1][x2] = 0; 
					map_data.tile[y2][x2] = 0; 
				}
				std::cout << luckky_box; 
			}
			else if ((val1 == TRAP) || (val2 == TRAP ))
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else if ((val1 == TRAP2) || (val2 == TRAP2))
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else if ((val1 == HEART) || (val2 == HEART) )
			{
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				checkheart = 1;
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
				}
			}

		}
		else if (x_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == STATE_MONEY || (val2 == STATE_MONEY) )
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				IncreaseMoney();
			}
			else if ((val1 == LUCKKY_BOX) || (val2 == LUCKKY_BOX))
			{
				if (luckky_box != 0)
				{
					luckky_box--; 
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
				else  
				{
					map_data.tile[y1][x1] = 0;
					map_data.tile[y2][x1] = 0;
				}
				std::cout << luckky_box; 
			}
			else if (val1 == TRAP || (val2 == TRAP ))
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;

			}
			else if (val1 == TRAP2 || (val2 == TRAP2))
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;

			}
			else if (val1 == HEART || (val2 == HEART ))
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				checkheart = 1;

			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}
		}
	}

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (y_val_ > 0)
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreaseMoney(); 
			}
			else if ((val1 == LUCKKY_BOX) || (val2 == LUCKKY_BOX))
			{
				if (luckky_box != 0)
				{
					luckky_box--; 
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = true;
					if (status_ == WALK_NONE)
					{
						status_ = WALK_NONE;
					}
				}
				if (luckky_box == 0)
				{
					map_data.tile[y2][x1] = 0;
					map_data.tile[y2][x2] = 0;
				}
				std::cout << luckky_box; 
			}
			else if (val1 == TRAP || val2 == TRAP )
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else if (val1 == TRAP2 || val2 == TRAP2)
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
			}
			else if (val1 == HEART || val2 == HEART )
			{
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				checkheart = 1;
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= (height_frame_ + 1);
					y_val_ = 0;
					on_ground_ = true;

					if (status_ == WALK_NONE)
					{
						status_ = WALK_NONE;
					}
				}
			}
		}
		else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			if (val1 == STATE_MONEY || val2 == STATE_MONEY)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreaseMoney(); 
			}
			else if ((val1 == LUCKKY_BOX) || (val2 == LUCKKY_BOX))
			{
				if (luckky_box != 0){
					luckky_box--; 
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
				else 
				{
					map_data.tile[y1][x1] = 0;
					map_data.tile[y1][x2] = 0;
				}
				std::cout << luckky_box; 
			}
			else if ( val1 == TRAP || val2 == TRAP )
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else if (val1 == TRAP2 || val2 == TRAP2)
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
			}
			else if (val1 == HEART || val2 == HEART )
			{
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				checkheart = true;
			}
			else
			{
				if (val1 != BLANK_TILE || val2 != BLANK_TILE)
				{
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
		}
	}


	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0)
	{
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_)
	{
		come_back_time_ = 10;
	}
}

void MainObject::Show(SDL_Renderer* des)
{
	UpdateImagePlayer(des); 
	
	if ( (input_type_.left_ == 1 || input_type_.right_ == 1) && status_ != FIGHT )
	{
		frame_++; 
	}
	else {
		frame_ = 0; 
	}

	if (frame_ >= 8)
	{
		frame_ = 0; 
	}
	if (come_back_time_ == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;

		SDL_Rect* current_clip = &frame_clip_[frame_];

		SDL_Rect renderQuad = { rect_.x , rect_.y , width_frame_ , height_frame_ };

		SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
	}
	/*if (input_type_.attack_ == 1 || status_ == FIGHT  ) 
	{
		if (delay_attack == 0)
		{
			delay_attack = SDL_GetTicks(); 
		}
		frame2_ = SDL_GetTicks();
		frame2_ = ( (frame2_ - delay_attack )/ 120) % 8;
			if(come_back_time_ == 0)
			{
				rect_.x = x_pos_ - map_x_;
				rect_.y = y_pos_ - map_y_;

				SDL_Rect* current_clip = &frame_clip_[frame2_];

				SDL_Rect renderQuad = { rect_.x , rect_.y , width_frame_ , height_frame_ };

				SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
			}
	}
	else
	{
		delay_attack = 0; 
	}*/
	/*if (frame2_ >= 8)
	{
		frame2_ = 0;
	}*/

}

void MainObject::HandelInputAction(SDL_Event events, SDL_Renderer* screen , Mix_Chunk* bullet_sound[2] ) 
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		case SDLK_d:
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 1; 
			input_type_.left_ = 0; 
			UpdateImagePlayer(screen);
		}
		break; 
		case SDLK_LEFT:
		case SDLK_a:
		{
			status_ = WALK_LEFT; 
			input_type_.left_ = 1; 
			input_type_.right_= 0; 
			UpdateImagePlayer(screen);
		}
		break;
		case SDLK_w : 
		{
			input_type_.jump_ = 1; 
		}
		break; 
		case SDLK_j:
		{
			status_ = FIGHT;
			input_type_.attack_ = 1; 
			input_type_.left_ = 0; 
			input_type_.right_ = 0;
			UpdateImagePlayer(screen);
			Mix_PlayChannel(-1, bullet_sound[0], 0); 
		}
		break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		case SDLK_d :
		{
			status_ = WALK_RIGHT;
			input_type_.right_ = 0;
			UpdateImagePlayer(screen); 
		}
		break;
		case SDLK_LEFT:
		case SDLK_a : 
		{
			status_ = WALK_LEFT;
			input_type_.left_ = 0;
			UpdateImagePlayer(screen); 
		}
		break;
		case SDLK_j : 
		{
			status_ = WALK_RIGHT;
			input_type_.attack_ = 0;
			UpdateImagePlayer(screen); 
		}
		break;
		}
	}

	/*if (input_type_.attack_ == 1 && time_attack > 0 )
	{
		time_attack -= real_time_of_game_; 
	}
	else {
		input_type_.attack_ = 0; 
		time_attack = 10000; 
	}*/
	
	if (events.type == SDL_MOUSEBUTTONDOWN || events.type == SDL_KEYDOWN  )
	{
		if (events.button.button == SDL_BUTTON_RIGHT)
		{
			input_type_.jump_ = 1;
		}
		else if (events.button.button == SDL_BUTTON_LEFT || events.key.keysym.sym == SDLK_SPACE   )
		{
			BulletObject* p_bullet = new BulletObject(); 
			p_bullet->set_bullet_type(BulletObject::SEPHERE_BULLET);
			p_bullet->LoadImgBullet(screen); 

			if (status_ == WALK_LEFT)
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_LEFT); 
				p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_ * 0.25);
				p_bullet->set_x_val(-20);
			}
			else
			{
				p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
				p_bullet->SetRect(this->rect_.x + width_frame_ - 20, rect_.y + height_frame_ * 0.25);
				p_bullet->set_x_val(20);
			}
 
			p_bullet->set_y_val(0);
			p_bullet->set_is_move(true); 

			p_bullet_list_.push_back(p_bullet); 
			Mix_PlayChannel(-1, bullet_sound[0], 0);
		}
	}
}
void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bullet_list_.size(); i++)
	{
		BulletObject* p_bullet = p_bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT); 
				p_bullet->Render(des); 
			}
			else
			{
				p_bullet_list_.erase(p_bullet_list_.begin() + i);
					if (p_bullet != NULL)
					{
						delete p_bullet; 
						p_bullet = NULL; 
					}
			}
		}
	}
}

void MainObject::RemoveBullet(const int& idx )
{
	int size = p_bullet_list_.size(); 
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bullet_list_.at(idx); 
		p_bullet_list_.erase(p_bullet_list_.begin() + idx); 

		if (p_bullet)
		{
			delete p_bullet; 
			p_bullet = NULL; 
		}
	}
}

void MainObject::DoPlayer(Map& map_data)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += 0.8;
		if (y_val_ >= MAX_FALL_SPEED)
		{
			y_val_ = MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)
		{
			x_val_ -= PLAYER_SPEED;
		}
		else if (input_type_.right_ == 1)
		{
			x_val_ += PLAYER_SPEED;
		}

		if (input_type_.jump_ == 1)
		{
			if (on_ground_ == true)
			{
				y_val_ = -PLAYER_JUMP_VALUE;
			}
			on_ground_ = false;
			input_type_.jump_ = 0;
		}

		CheckToMap(map_data);
		CenterEntityOnMap(map_data);
	}

	if (come_back_time_ > 0)
	{
		come_back_time_--; 
		if (come_back_time_ == 0)
		{
			on_ground_ = false; 
			if (x_pos_ > 256)
			{
				x_pos_ -= 256; 
			}
			else
			{
				x_pos_ = 0; 
			}
			y_pos_ = 0;
			x_val_ = 0; 
			y_val_ = 0; 
			
		}
	}
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2); 
	if (map_data.start_x_ < 0)
	{
		map_data.start_x_ = 0; 
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_)
	{
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH; 
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2); 
	if (map_data.start_y_ < 0)
	{
		map_data.start_y_ = 0; 
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.start_y_)
	{
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT; 
	}
}

void MainObject::IncreaseMoney()
{
	money_count++; 
}

void MainObject::UpdateImagePlayer(SDL_Renderer* des)
{
	if (on_ground_ == true)
	{
		bool isWalking = (input_type_.left_ == 0 && input_type_.right_ == 0);
		if (isWalking && status_ == WALK_LEFT) {
			LoadImg("img//Idle_left.png", des); 
		}
		else if (isWalking && status_ == WALK_RIGHT)
		{
			LoadImg("img//Idle_right.png", des); 
		}
		else if (status_ == WALK_LEFT)
		{
			LoadImg("img//player_left.png",des); 
		}
		else if ( status_ == WALK_RIGHT )
		{
			LoadImg("img//player_right.png", des);
		}
		else if ( status_ == FIGHT )
		{
		    LoadImg("map//sdad.png", des);
		}
	}
	else
	{
		if (status_ == WALK_LEFT)
		{
			LoadImg("img//jump_left.png", des); 
		}
		else {
			LoadImg("img//jump_right.png", des); 
		}
	}
}