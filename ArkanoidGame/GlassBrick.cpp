#include "GlassBrick.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	GlassBrick::GlassBrick(float x, float y, float width, float height, int blockPoints)
		: Block(x, y, width, height, sf::Color::White, blockPoints)
	{
		setupGlassAppearance();
	}

	bool GlassBrick::OnHit()
	{
		// Glass block is destroyed immediately but doesn't bounce the ball
		destroy();
		return false; // Ball should NOT bounce (passes through)
	}

	void GlassBrick::draw(sf::RenderWindow& window) const
	{
		if (isActive)
		{
			// Draw glass block with transparency
			window.draw(shape);
			
			// Add glass reflection effect
			sf::RectangleShape reflection;
			reflection.setSize(sf::Vector2f(shape.getSize().x * 0.3f, shape.getSize().y * 0.2f));
			reflection.setPosition(shape.getPosition().x + shape.getSize().x * 0.1f, shape.getPosition().y + shape.getSize().y * 0.1f);
			reflection.setFillColor(sf::Color(255, 255, 255, 100)); // Semi-transparent white
			window.draw(reflection);
		}
	}

	void GlassBrick::setupGlassAppearance()
	{
		// Set glass-like appearance with transparency
		glassColor = sf::Color(200, 220, 255, 100); // Light blue with transparency
		shape.setFillColor(glassColor);
		shape.setOutlineColor(sf::Color(150, 180, 220, 150)); // Slightly darker outline
		shape.setOutlineThickness(1.0f);
	}
}

