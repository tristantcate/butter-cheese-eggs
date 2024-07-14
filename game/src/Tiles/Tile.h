#pragma once

#include "raylib.h"
#include "raymath.h"

class Tile {

public:
	Tile() = default;
	Tile(Vector2 a_anchorPos, Vector2 a_size);
	void SetTileData(Vector2 a_anchorPos, Vector2 a_size);

	enum class TileState
	{
		Empty,
		Circle,
		Square
	};

	TileState GetTileState() { return m_currentTileState; }
	void SetTileState(TileState a_tileState) { m_currentTileState = a_tileState; }


	bool IsHoveringOver(Vector2 a_pos);

	void SetBackgroundColor(Color a_color);

	void Draw();

private:
	
	Vector2 m_topLeftAnchorPos;
	Vector2 m_size;
	Vector2 m_center;

	Rectangle m_tileRect;

	TileState m_currentTileState;
	Color m_backgroundColor;

};