#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include <unordered_map>
#include <memory>

namespace ArkanoidGame
{
	enum GameOptions: std::uint8_t
	{
		InfiniteLives = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteLives | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Win,
		ExitDialog,
		Records,
		NameInput,
	};

	// Forward declaration
	class Game;

	// Base class for all game states
	class GameStateBase
	{
	public:
		GameStateBase() : game(nullptr) {}
		virtual ~GameStateBase() = default;
		virtual void handleWindowEvent(const sf::Event& event) = 0;
		virtual void update(float timeDelta) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
		
		void setGame(Game* gameInstance) { game = gameInstance; }
		
	protected:
		Game* game;
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		std::unique_ptr<GameStateBase> data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		// Game session data
		void SetCurrentScore(int score) { currentScore = score; }
		int GetCurrentScore() const { return currentScore; }
		void SetGameResult(bool won) { gameWon = won; }
		bool GetGameResult() const { return gameWon; }
		bool IsScoreHighEnough() const;
		void AddRecord(const std::string& playerName, int score);

		// Records persistence
		void SaveRecordsToFile();
		void LoadRecordsFromFile();

		// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		// Remove current game state from the stack
		void PopState();

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);

		
	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;
		
		// Current game session data
		int currentScore = 0;
		bool gameWon = false;
	};

	std::unique_ptr<GameStateBase> CreateGameState(GameStateType stateType);
}
