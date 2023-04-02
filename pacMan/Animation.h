#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32
#define DIRECTION_Y_DOWN_INITAL 0
#define DIRETION_Y_LEFT_INITAL 1
#define DIRECTION_Y_RIGHT_INITAL 2
#define DIRECTION_Y_UP_INITAL 3

#define DIRECTION_X_DOWN_INITAL 0
#define DIRECTION_X_LEFT_INITAL 0
#define DIRECTION_X_RIGHT_INITAL 0
#define DIRECTION_X_UP_INITAL 0


class Animation
{
public:
	Animation(Texture* texture,Vector2u imageCount,float switchTime);
	~Animation();
	void updateImage(unsigned row, float deltaTime, bool faceRight);

public:
	IntRect uvRect;


private:
	Vector2u imageCount;
	Vector2u CurrentImage;
	float switchTime;
		float totalTime;
};











