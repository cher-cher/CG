#pragma once

#include "libchapter2.h"

const int TILE_SIZE = 128;
const int VERTEX_TILE_SIZE = TILE_SIZE + 1;

class CMapTile
{
public:
	CMapTile();
	~CMapTile();

	void Load(int x, int y, int columns, int rows, int step, GLfloat const* mapData);
	void Draw();

private:
	void Upload();
	void Destroy();

	GLfloat	m_heightMap[VERTEX_TILE_SIZE * VERTEX_TILE_SIZE];
	GLuint	m_displayList;
	GLuint m_textureName;
	GLuint m_detailTextureName;

	int	m_startX;
	int m_startY;
	int m_numRows;
	int m_numColumns;
	int m_mapStep;
	float m_detailStep;
};
