#pragma once
#ifndef MAIN_OBJECT_H_ 
#define MAIN_OBJECT_H_ 

#include <vector>
#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"


#define GRAVITY_SPEED 0.8 
#define MAX_FALL_SPEED 10 
#define PLAYER_SPEED 6
#define PLAYER_JUMP_VALUE 20

class MainObject : public BaseObject
{
public :
	MainObject();
	~MainObject(); 

	enum WalkType
	{
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_IDLE = 3, 
		FIGHT = 4, 
	};

	bool LoadImg(std::string path, SDL_Renderer* screen); 
	void Show(SDL_Renderer* des); 

	void HandelInputAction(SDL_Event events, SDL_Renderer* screen , Mix_Chunk* bullet_sound[2]);
	void set_clips(); 

	void DoPlayer(Map& map_data);

	void CheckToMap(Map& map_data); 
	void SetMapXY(const int map_x, const int map_y) { map_x_ = map_x; map_y_ = map_y; }; 
	void CenterEntityOnMap(Map& map_data); 
	void UpdateImagePlayer(SDL_Renderer* des);

	SDL_Rect GetRectFrame();

	void set_bullet_list(std::vector<BulletObject*> bullet_list)
	{
		p_bullet_list_ = bullet_list; 
	}
	std::vector<BulletObject*> get_bullet_list() const { return p_bullet_list_; }
	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx ); 
	void IncreaseMoney(); 
	void set_comeback_time(const int& cb_time) { come_back_time_ = cb_time;  }
	int GetMoneyCount() const { return money_count; };
	void set_real_time_of_game(const int& real_time) { real_time_of_game_ = real_time; }
	float getxpos() { return x_pos_;  }
	float getypos() { return y_pos_;  }
	int getheart() { return checkheart; }

private:

	int money_count; 
	int luckky_box; 
	std::vector<BulletObject*> p_bullet_list_; 
	float x_val_; 
	float y_val_; 

	float x_pos_; 
	float y_pos_; 


	int width_frame_; 
	int height_frame_; 

	SDL_Rect frame_clip_[8]; 
	Input input_type_; 

	int real_time_of_game_; 
	int frame_ ; 
	int status_;
	bool on_ground_; 
	bool hit_; 

	int map_x_; 
	int map_y_; 

	int time_attack; 
	int delay_attack; 
	

	int come_back_time_; 
	bool checkheart; 

};


#endif