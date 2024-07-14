#pragma once
#include "raylib.h"
#include "Tile.h"

class TileManager {

private:
	//const float m_playAreaPadding = 0.35f;
	//const float m_tilePadding = 10.0f;

	const float m_playAreaSize;
	const float m_halfPlayAreaSize;

	const Vector2 m_playAreaPos;

	Tile m_tiles[9] = {};
	const unsigned int m_tileRowAmount = 3;

	const float m_tileSize;


public:
	/// <summary>
	/// Initializes the Tile Manager system. This constructor builds the layout of the game.
	/// </summary>
	/// <param name="a_screenHeight">Height of the Screen in px</param>
	/// <param name="a_screenCenter">Center of the Screen in px</param>
	/// <param name="a_playAreaPadding">
	///		Percentage of the screen being padded from playarea, where 1 fills the entire screen 
	///		and 0.3f removes 30% on top and bottom of the screen.
	/// </param>
	/// <param name="a_tilePadding">Padding in between individual tiles in px.</param>
	TileManager(float a_screenHeight, const Vector2& a_screenCenter, float a_playAreaPadding, float a_tilePadding) :

		m_playAreaSize(a_screenHeight* (1.0f - a_playAreaPadding)),
		m_halfPlayAreaSize(m_playAreaSize / 2.0f),
		m_playAreaPos(Vector2AddValue(a_screenCenter, -m_halfPlayAreaSize)),
		m_tileSize(m_playAreaSize / 3.0f - a_tilePadding)

	{
	
		for (unsigned int x = 0; x < m_tileRowAmount; x++)
		{
			for (unsigned int y = 0; y < m_tileRowAmount; y++)
			{

				const float xPos = m_playAreaPos.x + m_tileSize * x + a_tilePadding * x + a_tilePadding / 2.0f;
				const float yPos = m_playAreaPos.y + m_tileSize * y + a_tilePadding * y + a_tilePadding / 2.0f;
				const Vector2 currentPos = { xPos, yPos };

				Tile* currentTile = &m_tiles[y * m_tileRowAmount + x];
				currentTile->SetTileData(currentPos, {m_tileSize, m_tileSize});

			}
		}
	};

	Tile* GetTiles();

	Tile& GetTileAt(int a_x, int a_y);

	void DrawTiles();
	

};
