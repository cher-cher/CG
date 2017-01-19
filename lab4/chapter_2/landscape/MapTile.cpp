#include "stdafx.h"
#include "MapTile.h"
#include <stdint.h>

CMapTile::CMapTile()
{
}

void CMapTile::Load(int x, int y, int columns, int rows, int step, GLfloat const * mapData)
{
	startX = x;
	startY = y;
	numRows = columns;
	numColumns = rows;
	mapStep = step;
	displayList = 0;

	detailStep = 32.0f / TILE_SIZE;
	memcpy(heightMap, mapData, numRows * numColumns * sizeof(GLfloat));
}

void CMapTile::Upload()
{
	displayList = glGenLists(1);

	glNewList(displayList, GL_COMPILE);

	int y0 = startY;
	float du = 1.0f / TILE_SIZE;
	float dv = 1.0f / TILE_SIZE;
	float v = 0;
	for (int row = 0; row < numRows - 1; ++row, y0 += mapStep, v += dv)
	{
		float u = 0;
		int x0 = startX;
		glBegin(GL_TRIANGLE_STRIP);
		for (int column = 0; column < numColumns; ++column, x0 += mapStep, u += du)
		{
			glTexCoord2f(v + dv, u);
			glVertex3f((float)x0, heightMap[(row + 1) * numColumns + column] * 4 - 150, -(float)(y0 + mapStep));

			glTexCoord2f(v, u);
			glVertex3f((float)x0, heightMap[row * numColumns + column] * 4 - 150, -(float)(y0));
		}
		glEnd();
	}
	glEndList();

}

void CMapTile::Draw()
{
	if (!displayList)
	{
		Upload();
	}
	glCallList(displayList);
}

void CMapTile::Destroy()
{
	if (displayList != 0)
	{
		glDeleteLists(displayList, 1);
		displayList = 0;
	}

	if (textureName)
	{
		glDeleteTextures(1, &textureName);
		textureName = 0;
	}

	if (detailTextureName)
	{
		glDeleteTextures(1, &detailTextureName);
		detailTextureName = 0;
	}
}

CMapTile::~CMapTile()
{
}
