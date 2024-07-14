#include "TileManager.h"

Tile* TileManager::GetTiles() {
	return m_tiles;
}

Tile& TileManager::GetTileAt(int a_x, int a_y) {
	return m_tiles[a_y * m_tileRowAmount + a_x];
}

void TileManager::DrawTiles()
{
	for (Tile& tile : m_tiles) {
		tile.Draw();
	}
}
