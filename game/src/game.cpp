#include "Raylib.h"
#include "raymath.h"

#include "Tiles/TileManager.h"
#include "Gameplay.h"

int main() {

	const unsigned int m_screenWidth = 1280;
	const unsigned int m_screenHeight = 720;

	Vector2 m_screenCenter;
	m_screenCenter.x = m_screenWidth / 2.0f;
	m_screenCenter.y = m_screenHeight / 2.0f;

	InitWindow(m_screenWidth, m_screenHeight, "Butter Cheese & Eggs");

	SetTargetFPS(120);
	
	TileManager m_tileManager(m_screenHeight, m_screenCenter, 0.25f, 10.0f);
	Gameplay m_gameplay(m_tileManager);

	while (!WindowShouldClose()) {

		m_gameplay.UpdateGame();
		

		//--- DRAWING ---
		BeginDrawing();
		
		ClearBackground(SKYBLUE);
		DrawText("Butter Cheese & Eggs", 370, 20, 48, WHITE);


		DrawText(m_gameplay.GetBottomText().c_str(), 520, m_screenHeight - 80, 48, WHITE);

		if (m_gameplay.IsGameEnded()) {

			Rectangle restartRect = { 1000.0f - 10.0f, m_screenCenter.y - 40, 240, 100 };

			DrawRectanglePro(restartRect, { 0, 0}, 0, WHITE);
			DrawRectangle(1000, m_screenCenter.y - 30, 220, 80, YELLOW);
			DrawText("Restart Game", 1035, m_screenCenter.y - 10, 25, WHITE);
			DrawText("Restart Game", 1035, m_screenCenter.y - 5, 24, BLUE);

			if (CheckCollisionPointRec(GetMousePosition(), restartRect)) {

				DrawRectanglePro(restartRect, { 0, 0 }, 0, WHITE); //Overwriting to give illusion of hover.

				if (IsMouseButtonDown(0)) {
					m_tileManager.ResetGame();
					m_gameplay.ResetGame();
				}
			}
			
		}


		m_tileManager.DrawTiles();

		EndDrawing();

	}



	CloseWindow();

	return 0;
}

void UpdateGame() {

}