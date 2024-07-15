#pragma once

#include "Tiles/TileManager.h"
#include <string>

class Gameplay {
	
	TileManager& m_tileManager;
	Tile* tiles = m_tileManager.GetTiles();

	enum class GameState {
		CircleTurn,
		SquareTurn,
		CircleWin,
		SquareWin,
		Draw
	};

	GameState m_gameState = GameState::CircleTurn;

	std::string m_topText;
	std::string m_bottomText;

	

public:

	bool IsGameEnded();

	void SetGameState(GameState a_to);
	GameState GetGameState() { return m_gameState; }

	Gameplay(TileManager& a_tileManager) :
		m_tileManager(a_tileManager) 
	{
		SetGameState(GameState::CircleTurn);
	}

	void UpdateGame();

	const std::string& GetTopText();
	const std::string& GetBottomText();

	void ResetGame();
};