#include "Raylib.h"
#include "raymath.h"

#include "Tile.h"

int main() {

	const unsigned int m_screenWidth = 1280;
	const unsigned int m_screenHeight = 720;

	Vector2 m_screenCenter;
	m_screenCenter.x = m_screenWidth / 2.0f;
	m_screenCenter.y = m_screenHeight / 2.0f;

	InitWindow(m_screenWidth, m_screenHeight, "My first window :)");

	SetTargetFPS(120);

	const float m_playAreaPadding = 0.35f;
	const float m_tilePadding = 10.0f;


	//Remember, everything is rendered from anchor point in the top-left
	const float playAreaSize = (m_screenHeight * (1.0f - m_playAreaPadding));
	const float halfPlayAreaSize = playAreaSize / 2.0f;
	Vector2 playAreaPos = Vector2AddValue(m_screenCenter, -halfPlayAreaSize);


	const float tileSize = playAreaSize / 3.0f - m_tilePadding;
	Vector2 tileArea = Vector2{ tileSize, tileSize };

	//Play Area


	Tile tiles[9];


	//Setting Up Individual Tiles
	const unsigned int tileRowAmount = 3;
	for (unsigned int x = 0; x < tileRowAmount; x++)
	{
		for (unsigned int y = 0; y < tileRowAmount; y++)
		{

			const float xPos = playAreaPos.x + tileSize * x + m_tilePadding * x + m_tilePadding / 2.0f;
			const float yPos = playAreaPos.y + tileSize * y + m_tilePadding * y + m_tilePadding / 2.0f;
			const Vector2 currentPos = { xPos, yPos };

			Tile* currentTile = &tiles[y * tileRowAmount + x];
			currentTile->SetTileData(currentPos, tileArea);

		}
	}

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
		for each (Tile& tile in tiles)
		{
			if (tile.IsHoveringOver(mousePos)) {
				targetedTile = &tile;
				break;
			}
			else {
				tile.SetBackgroundColor(YELLOW);
			}
		}

		if (targetedTile != nullptr) {

			if (targetedTile->GetTileState() == Tile::TileState::Empty)
				targetedTile->SetBackgroundColor(WHITE);
			else
				targetedTile->SetBackgroundColor(RED);

			if (mouseClick) {

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
		
		ClearBackground(PINK);
		DrawText("This is tic tac toe.", m_screenCenter.x, 100, 48, WHITE);


		

		DrawRectangleV(playAreaPos, Vector2{ playAreaSize, playAreaSize }, DARKBLUE);

		for each (Tile tile in tiles)
		{
			tile.Draw();
		}


		//Vector2 currentPos = Vector2AddValue(playAreaPos, m_tilePadding);
		//DrawRectangleV(currentPos, tileArea, YELLOW);
		
		
		//DrawRing(m_screenCenter, 100.0f, 120.0f, 0, 360, 64, GREEN);

		EndDrawing();

	}



	CloseWindow();

	return 0;
}