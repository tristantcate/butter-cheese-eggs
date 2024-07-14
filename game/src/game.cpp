#include "Raylib.h"
#include "raymath.h"

#include "Tiles/Tile.h"
#include "Tiles/TileManager.h"

int main() {

	const unsigned int m_screenWidth = 1280;
	const unsigned int m_screenHeight = 720;

	Vector2 m_screenCenter;
	m_screenCenter.x = m_screenWidth / 2.0f;
	m_screenCenter.y = m_screenHeight / 2.0f;

	InitWindow(m_screenWidth, m_screenHeight, "My first window :)");

	SetTargetFPS(120);
	
	TileManager m_tileManager(m_screenHeight, m_screenCenter, 0.25f, 10.0f);
	Tile* tiles = m_tileManager.GetTiles();

	enum class GameState {
		CircleTurn,
		SquareTurn,
		GameOver
	};

	GameState m_gameState = GameState::CircleTurn;

	while (!WindowShouldClose()) {

		Vector2 mousePos = GetMousePosition();

		bool mouseClick = IsMouseButtonPressed(0);

		Tile* targetedTile = {};


		//--- Update Functionality ---

		for (int tileIter = 0; tileIter < 9; tileIter++)
		{
			Tile& currentTile = tiles[tileIter];
			currentTile.SetBackgroundColor(YELLOW);

			if (currentTile.IsHoveringOver(mousePos)) {
				targetedTile = &currentTile;
			}
		}


		if (targetedTile != nullptr) {


			bool isTileEmpty = targetedTile->GetTileState() == Tile::TileState::Empty;

			if (isTileEmpty) targetedTile->SetBackgroundColor(WHITE);
			else targetedTile->SetBackgroundColor(RED);
			

			if (mouseClick && isTileEmpty) {

				if (m_gameState == GameState::CircleTurn) {
					targetedTile->SetTileState(Tile::TileState::Circle);

					m_gameState = GameState::SquareTurn;
				}
				else if (m_gameState == GameState::SquareTurn) {
					targetedTile->SetTileState(Tile::TileState::Square);

					m_gameState = GameState::CircleTurn;
				}
				

			}

		}
		
		


		//--- DRAWING ---
		BeginDrawing();
		
		ClearBackground(SKYBLUE);
		DrawText("This is tic tac toe.", m_screenCenter.x, 100, 48, WHITE);

		m_tileManager.DrawTiles();

		EndDrawing();

	}



	CloseWindow();

	return 0;
}