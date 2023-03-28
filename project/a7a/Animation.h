#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


Vector2u ImageCount;
Vector2u CurrentImage;
float switchTime, totalTime = 0.f;
IntRect uvRect;

bool animationEnd = false;

void Animation(Texture texture, float switchTime, Vector2u ImageCount);
void updateImage(unsigned row, float deltaTime,bool faceRight);



void Animation(Texture texture, float switchTime, Vector2u ImageCount)
{
	CurrentImage.x = 0;
	uvRect.width = texture.getSize().x / float(ImageCount.x);
	uvRect.height = texture.getSize().y / float(ImageCount.y);

}

void updateImage(unsigned row, float deltaTime,bool faceRight)
{
	CurrentImage.y = row;

	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		CurrentImage.x++;
		if (CurrentImage.x >= ImageCount.x)

		{
			CurrentImage.x = 0;

		}
	}

	uvRect.top = uvRect.height * CurrentImage.y;
	if (faceRight)
	{
		uvRect.left = uvRect.width * CurrentImage.x;
		uvRect.width = abs(uvRect.width);
	}
	else

	{
		uvRect.left = abs(uvRect.width) * (CurrentImage.x+1);
		uvRect.width = -abs(uvRect.width);

	}

}

