#include "Block.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	Block::Block(float x, float y, float width, float height, const sf::Color& blockColor, int blockPoints)
		: GameObject(x, y, width, height), color(blockColor), points(blockPoints)
	{
		shape.setSize(sf::Vector2f(width, height));
		shape.setPosition(x, y);
		shape.setFillColor(color);
		shape.setOutlineColor(sf::Color::Black);
		shape.setOutlineThickness(1.0f);
	}

	void Block::update(float timeDelta)
	{
		// Update shape position to match GameObject position
		shape.setPosition(position);
	}

	void Block::draw(sf::RenderWindow& window) const
	{
		if (isActive)
		{
			window.draw(shape);
		}
	}

	void Block::destroy()
	{
		isActive = false;
	}
}
