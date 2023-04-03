#include "Animation.h"

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	CurrentImage.x = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation()
{

}

void Animation::updateImage(unsigned row, float deltaTime, bool faceRight)
{
	CurrentImage.y = row;

	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		CurrentImage.x++;
		if (CurrentImage.x >= imageCount.x)

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
		uvRect.left = (CurrentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);

	}
}  