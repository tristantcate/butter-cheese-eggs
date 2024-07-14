#include "Gameplay.h"

void Gameplay::SetGameState(GameState a_to)
{
	if (a_to == GameState::CircleTurn) {
		m_bottomText = "o's turn!";
	}

	if (a_to == GameState::SquareTurn) {
		m_bottomText = "x's turn!";
	}

	if (a_to == GameState::CircleWin) {
		m_bottomText = "o wins!!!";
	}

	if (a_to == GameState::SquareWin) {
		m_bottomText = "x wins!!!";
	}

	if (a_to == GameState::Draw){
		m_bottomText = "It's a draw...";
	}
	m_gameState = a_to;

}

void Gameplay::UpdateGame() {

	if (!(m_gameState == GameState::CircleTurn ||
		m_gameState == GameState::SquareTurn))
		return;

	Vector2 mousePos = GetMousePosition();

	bool mouseClick = IsMouseButtonPressed(0);

	Tile* targetedTile = {};

	for (int tileIter = 0; tileIter < 9; tileIter++)
	{
		Tile& currentTile = tiles[tileIter];

		if (currentTile.IsHoveringOver(mousePos)) {
			targetedTile = &currentTile;
		}
	}

	m_tileManager.SetAllBackgroundColor(DARKBLUE);
	targetedTile = m_tileManager.GetTileAtPos(mousePos);


	if (targetedTile != nullptr) {

		bool isTileEmpty = targetedTile->GetTileState() == Tile::TileState::Empty;

		if (isTileEmpty) targetedTile->SetBackgroundColor(WHITE);
		else targetedTile->SetBackgroundColor(RED);


		if (mouseClick && isTileEmpty) {

			if (m_gameState == GameState::CircleTurn) {
				targetedTile->SetTileState(Tile::TileState::Circle);

				std::vector<Tile*> circleWinTiles = m_tileManager.ProcessPlacementWin(Tile::TileState::Circle);
				if (circleWinTiles.size() > 0) {
					SetGameState(GameState::CircleWin);

					for (Tile* tile : circleWinTiles) {
						tile->SetBackgroundColor(GREEN);
					}

				}
				else {
					SetGameState(GameState::SquareTurn);
				}


			}
			else if (m_gameState == GameState::SquareTurn) {
				targetedTile->SetTileState(Tile::TileState::Square);

				std::vector<Tile*> squareWinTiles = m_tileManager.ProcessPlacementWin(Tile::TileState::Square);
				if (squareWinTiles.size() > 0) {
					SetGameState(GameState::SquareWin);

					for (Tile* tile : squareWinTiles) {
						tile->SetBackgroundColor(GREEN);
					}

				}
				else {
					SetGameState(GameState::CircleTurn);
				}
				
			}


		}
	}
}

const std::string& Gameplay::GetTopText()
{
	return m_topText;
}

const std::string& Gameplay::GetBottomText()
{
	return m_bottomText;
}
