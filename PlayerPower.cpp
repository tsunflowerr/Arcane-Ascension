#include "PlayerPower.h"

PlayerPower::PlayerPower()
{
	number_ = 0; 
}

PlayerPower::~PlayerPower()
{

}

void PlayerPower::AddPos(const int& xp)
{
	pos_list_.push_back(xp);

}

void PlayerPower::Init(SDL_Renderer* screen)
{
	LoadImg("img//heart.png", screen); 
	number_ = 3; 
	if (pos_list_.size() > 0)
	{
		pos_list_.clear(); 
	}

	AddPos(20); 
	AddPos(50); 
	AddPos(80); 
}

void PlayerPower::Show(SDL_Renderer* screen)
{
	for (int i = 0; i < pos_list_.size(); i++)
	{
		rect_.x = pos_list_.at(i);
		rect_.y = 0;
		Render(screen);
	}
}

void PlayerPower::Decrease()
{
	if (number_ >= 1)
	{
		number_--; 
	}
	pos_list_.pop_back();
}

void PlayerPower::InitCrease()
{
	if (number_ <= 5) number_++; 
	int last_pos = pos_list_.back(); 
	last_pos += 30; 
	pos_list_.push_back(last_pos); 
}

PlayerMoney::PlayerMoney()
{
	x_pos_ = 0; 
	y_pos_ = 0;
}
PlayerMoney::~PlayerMoney()
{

}

void PlayerMoney::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//coin.png", screen); 
}

void PlayerMoney::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_; 
	rect_.y = y_pos_; 
	Render(screen); 
}

Iteam1::Iteam1()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Iteam1::~Iteam1()
{

}

void Iteam1::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//def.png", screen);
}

void Iteam1::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}

Iteam2::Iteam2()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Iteam2::~Iteam2()
{

}

void Iteam2::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//str.png", screen);
}

void Iteam2::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}

Iteam3::Iteam3()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Iteam3::~Iteam3()
{

}

void Iteam3::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//jp.png", screen);
}

void Iteam3::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);

}

Iteam4::Iteam4()
{
	x_pos_ = 0;
	y_pos_ = 0;
}
Iteam4::~Iteam4()
{

}

void Iteam4::Init(SDL_Renderer* screen)
{
	bool ret = LoadImg("img//runn.png", screen);
}

void Iteam4::Show(SDL_Renderer* screen)
{
	rect_.x = x_pos_;
	rect_.y = y_pos_;
	Render(screen);
}

