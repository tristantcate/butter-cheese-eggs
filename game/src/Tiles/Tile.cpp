#include "Tile.h"

Tile::Tile(Vector2 a_anchorPos, Vector2 a_size)
{
	SetTileData(a_anchorPos, a_size);
}

void Tile::SetTileData(Vector2 a_anchorPos, Vector2 a_size)
{
	m_topLeftAnchorPos = a_anchorPos;
	m_size = a_size;
	m_center = Vector2 { a_anchorPos.x + a_size.x / 2.0f,  a_anchorPos.y + a_size.y / 2.0f };

	m_tileRect.x = a_anchorPos.x;
	m_tileRect.y = a_anchorPos.y;
	m_tileRect.width = a_size.x;
	m_tileRect.height = a_size.y;

	m_backgroundColor = DARKBLUE;
	m_currentTileState = TileState::Empty;
	m_objectColor = ORANGE;
}



void Tile::Draw()
{
	DrawRectangleV(m_topLeftAnchorPos, m_size, m_currentBGColor);

	if (m_currentTileState == TileState::Circle) 
	{
		DrawRing(m_center, 50.0f, 60.0f, 0, 360, 64, m_objectColor);
	}
	else if (m_currentTileState == TileState::Square)
	{
		float crossToBoxMargin = 30.0f;
		float lineSize = 10.0f;
		float halfLineSize = lineSize/2.0f;

		float minX = m_center.x - m_size.x / 2.0f + crossToBoxMargin;
		float minY = m_center.y - m_size.y / 2.0f + crossToBoxMargin;

		float maxX = m_center.x + m_size.x / 2.0f - crossToBoxMargin;
		float maxY = (m_center.y + m_size.y / 2.0f + lineSize * 1.25f) - crossToBoxMargin ; //Not sure why we need linesize multiplied by 1.25.

		float crossSize = Vector2Distance({ minX, minY }, { maxX, maxY });

		Rectangle rect = { minX, minY, lineSize, crossSize };
		Rectangle rect2 = { maxX, minY, lineSize, crossSize };
		
		Vector2 halfSize = { -m_size.x / 2.0f, -m_size.y / 2.0f };

		DrawRectanglePro(rect, {halfLineSize, halfLineSize }, -45, m_objectColor);
		DrawRectanglePro(rect2, { halfLineSize, halfLineSize }, 45, m_objectColor);
		//DrawLineBezier(Vector2Subtract(m_center, m_size), Vector2Add(m_center, m_size), 10.0f, GREEN);
	}
}

bool Tile::IsHoveringOver(Vector2 a_pos)
{
	return CheckCollisionPointRec(a_pos, m_tileRect);
}

void Tile::SetBackgroundColor(Color a_color)
{
	m_currentBGColor = a_color;
}

void Tile::ResetBackgroundColor()
{
	m_currentBGColor = m_backgroundColor;
}

