#include "TileManager.h"





Tile* TileManager::GetTiles() {
	return m_tiles;
}

Tile& TileManager::GetTileAt(unsigned int a_x, unsigned int a_y) {
	return m_tiles[a_y * m_tileRowAmount + a_x];
}

Tile& TileManager::GetTileAt(Vector2 a_at)
{
	unsigned int x = static_cast<unsigned int>(a_at.x + 0.5f);
	unsigned int y = static_cast<unsigned int>(a_at.y + 0.5f);

	return GetTileAt(x, y);
}

Tile* TileManager::GetTileAtPos(const Vector2& a_pos)
{
	for (Tile& tile : m_tiles) {
		if (tile.IsHoveringOver(a_pos)) {
			return &tile;
		}
	}
	return nullptr;
}

bool TileManager::IsBoardFull()
{
	for (Tile& tile : m_tiles) {
		if (tile.GetTileState() == Tile::TileState::Empty) {
			return false;
		}
	}

	return true;
}

void TileManager::SetAllBackgroundColor(const Color& a_color)
{
	for (Tile& tile : m_tiles) {
		tile.SetBackgroundColor(a_color);
	}
}

void TileManager::ResetAllBackgroundColor()
{
	for (Tile& tile : m_tiles) {
		tile.ResetBackgroundColor();
	}
}

std::vector<Tile*> TileManager::ProcessPlacementWin(Tile::TileState a_state)
{ 
	std::vector <Tile*> winningTiles;

	//Verticals
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,0 }, { 0,1 }, { 0,2 });
	TileManager::AddWinningTiles(winningTiles, a_state, { 1,0 }, { 1,1 }, { 1,2 });
	TileManager::AddWinningTiles(winningTiles, a_state, { 2,0 }, { 2,1 }, { 2,2 });

	//Horizontals
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,0 }, { 1,0 }, { 2,0 });
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,1 }, { 1,1 }, { 2,1 });
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,2 }, { 1,2 }, { 2,2 });

	//Diagonals
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,0 }, { 1,1 }, { 2,2 });
	TileManager::AddWinningTiles(winningTiles, a_state, { 0,2 }, { 1,1 }, { 2,0 });

	return winningTiles;
}

void TileManager::AddWinningTiles(std::vector<Tile*>& a_winningTiles, Tile::TileState a_tileState, Vector2 a_tile1, Vector2 a_tile2, Vector2 a_tile3)
{
	std::vector<Tile*> tiles = { &GetTileAt(a_tile1), &GetTileAt(a_tile2), &GetTileAt(a_tile3) };

	if (tiles[0]->GetTileState() == a_tileState &&
		tiles[1]->GetTileState() == a_tileState &&
		tiles[2]->GetTileState() == a_tileState) {
		a_winningTiles.insert(a_winningTiles.end(), tiles.begin(), tiles.end());
	}
}

void TileManager::DrawTiles()
{
	for (Tile& tile : m_tiles) {
		tile.Draw();
	}
}

void TileManager::ResetGame()
{
	for (Tile& tile : m_tiles) {
		tile.SetTileState(Tile::TileState::Empty);
		tile.ResetBackgroundColor();
	}
}
