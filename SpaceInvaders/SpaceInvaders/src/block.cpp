#include "../include/block.hpp"

Block::Block(Vector2 position)
{
	this->position = position;
	blockState = ACTIVE;
}

void Block::Draw()
{
	if (blockState == ACTIVE) {
		DrawRectangle((int)position.x, (int)position.y, 3, 3, GREEN);
	}
}

Rectangle Block::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;

}
