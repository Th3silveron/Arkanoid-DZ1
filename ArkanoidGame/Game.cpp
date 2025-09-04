#include "Game.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStateWin.h"
#include "GameStateExitDialog.h"
#include "GameStateRecords.h"
#include <algorithm>

namespace ArkanoidGame
{
	Game::Game()
	{
		// Generate fake records table
		recordsTable =
		{
			{"Player1", 1500},
			{"Player2", 1200},
			{"Player3", 1000},
			{"Player4", 800},
			{"Player5", 600},
		};

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().data->handleWindowEvent(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Clear all game states
			stateStack.clear();
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Remove only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			auto newState = CreateGameState(pendingGameStateType);
			if (newState)
			{
				newState->setGame(this);
				stateStack.push_back({ pendingGameStateType, std::move(newState), pendingGameStateIsExclusivelyVisible });
			}
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().data->update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->data->draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		stateStack.clear();
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		return (options & option) == option;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = static_cast<GameOptions>(static_cast<int>(options) | static_cast<int>(option));
		}
		else
		{
			options = static_cast<GameOptions>(static_cast<int>(options) & ~static_cast<int>(option));
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return (it != recordsTable.end()) ? it->second : 0;
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = score;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		stateChangeType = GameStateChangeType::Push;
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
	}

	void Game::PopState()
	{
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		stateChangeType = GameStateChangeType::Switch;
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
	}

	std::unique_ptr<GameStateBase> CreateGameState(GameStateType stateType)
	{
		switch (stateType)
		{
		case GameStateType::MainMenu:
			return std::make_unique<GameStateMainMenu>();
		case GameStateType::Playing:
			return std::make_unique<GameStatePlaying>();
		case GameStateType::GameOver:
			return std::make_unique<GameStateGameOver>();
		case GameStateType::Win:
			return std::make_unique<GameStateWin>();
		case GameStateType::ExitDialog:
			return std::make_unique<GameStateExitDialog>();
		case GameStateType::Records:
			return std::make_unique<GameStateRecords>();
		default:
			return nullptr;
		}
	}
}
