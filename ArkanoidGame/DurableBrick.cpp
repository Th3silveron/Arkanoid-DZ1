#include "DurableBrick.h"
#include "GameSettings.h"

namespace ArkanoidGame
{
	DurableBrick::DurableBrick(float x, float y, float width, float height, const sf::Color& blockColor, int blockPoints, int hitsRequired)
		: Block(x, y, width, height, blockColor, blockPoints), maxHits(hitsRequired), currentHits(0), originalColor(blockColor)
	{
		// Calculate damaged color (darker version of original)
		damagedColor = sf::Color(
			std::max(0, originalColor.r - 80),
			std::max(0, originalColor.g - 80),
			std::max(0, originalColor.b - 80),
			originalColor.a
		);
	}

	bool DurableBrick::OnHit()
	{
		currentHits++;
		
		// Update visual appearance
		updateVisualAppearance();
		
		// Check if block should be destroyed
		if (currentHits >= maxHits)
		{
			destroy();
			return true; // Ball should bounce on final hit
		}
		
		// Block is still alive, ball should bounce
		return true;
	}

	void DurableBrick::draw(sf::RenderWindow& window) const
	{
		if (isActive)
		{
			// Draw the block with current visual state
			window.draw(shape);
			
			// Draw damage indicator (cracks or different pattern)
			if (currentHits > 0)
			{
				// Create a simple crack effect using lines
				sf::RectangleShape crack1, crack2;
				crack1.setSize(sf::Vector2f(2.0f, shape.getSize().y * 0.6f));
				crack2.setSize(sf::Vector2f(2.0f, shape.getSize().y * 0.4f));
				
				crack1.setPosition(shape.getPosition().x + shape.getSize().x * 0.3f, shape.getPosition().y + shape.getSize().y * 0.2f);
				crack2.setPosition(shape.getPosition().x + shape.getSize().x * 0.7f, shape.getPosition().y + shape.getSize().y * 0.3f);
				
				crack1.setFillColor(sf::Color::Black);
				crack2.setFillColor(sf::Color::Black);
				
				window.draw(crack1);
				window.draw(crack2);
			}
		}
	}

	void DurableBrick::updateVisualAppearance()
	{
		// Change color based on damage level
		if (currentHits == 0)
		{
			shape.setFillColor(originalColor);
		}
		else if (currentHits < maxHits)
		{
			// Interpolate between original and damaged color
			float damageRatio = static_cast<float>(currentHits) / static_cast<float>(maxHits);
			sf::Color currentColor(
				static_cast<sf::Uint8>(originalColor.r - (originalColor.r - damagedColor.r) * damageRatio),
				static_cast<sf::Uint8>(originalColor.g - (originalColor.g - damagedColor.g) * damageRatio),
				static_cast<sf::Uint8>(originalColor.b - (originalColor.b - damagedColor.b) * damageRatio),
				originalColor.a
			);
			shape.setFillColor(currentColor);
		}
	}
}
