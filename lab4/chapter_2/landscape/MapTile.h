#if !defined(AFX_MAPTILE_H__08423551_D9BE_4B22_A4F9_0F5B7E09EDFA__INCLUDED_)
#define AFX_MAPTILE_H__08423551_D9BE_4B22_A4F9_0F5B7E09EDFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "libchapter2.h"

#define TILE_SIZE 128
#define VERTEX_TILE_SIZE (TILE_SIZE + 1)

class CMapTile
{
public:
	GLfloat	heightMap[VERTEX_TILE_SIZE * VERTEX_TILE_SIZE];

	int	startX, startY;
	int numRows, numColumns;
	int mapStep;
	float detailStep;

	GLuint	displayList;
	GLuint textureName;
	GLuint detailTextureName;

	CMapTile();
	void Load(int x, int y, int columns, int rows, int step, GLfloat const* mapData);
	void Upload();
	void Draw();
	void Destroy();
	~CMapTile();

};


#endif 