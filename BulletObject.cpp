#include "BulletObject.h"


BulletObject::BulletObject()
{
	x_val_ = 0; 
	y_val_ = 0; 
	is_move_ = false; 
	bullet_type_ = SEPHERE_BULLET;
}

BulletObject::~BulletObject()
{


}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
	bool ret = false;
	if (bullet_type_ == LASER_BULLET)
	{
		ret = LoadImg("img/laze.png", des);

	}
	else if(bullet_type_ = SEPHERE_BULLET )
	{
		ret = LoadImg("img/dark_fire_ball.png", des);
	}
	else
	{
		ret = LoadImg("img/fireball.png", des); 
	}
	return ret; 
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.x += x_val_;
	rect_.y += y_val_;
	if (rect_.x > x_border || rect_.x < 0 || rect_.y > y_border || rect_.y < 0)
	{
		is_move_ = false;
	}
}

void BulletObject::SetDirection1(const SDL_Rect& target_position) {

    int dx = target_position.x - rect_.x;
    int dy = target_position.y - rect_.y;

    double angle = atan2(dy, dx) * (180.0 / M_PI);

    // Đảm bảo góc nằm trong khoảng từ 0 đến 360 độ
    if (angle < 0) {
        angle += 360;
    }

    double angle_radians = angle * (M_PI / 180.0);

    const double bullet_speed = 15.0;
    x_val_ = cos(angle_radians) * bullet_speed;
    y_val_ = sin(angle_radians) * bullet_speed;
}