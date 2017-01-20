#include "stdafx.h"
#include "MapTile.h"
#include <stdint.h>



CMapTile::CMapTile()
{
}

void CMapTile::Load(int x, int y, int columns, int rows, int step, GLfloat const * mapData)
{
	m_startX = x;
	m_startY = y;
	m_numRows = columns;
	m_numColumns = rows;
	m_mapStep = step;
	m_displayList = 0;

	m_detailStep = 32.0f / TILE_SIZE;
	memcpy(m_heightMap, mapData, m_numRows * m_numColumns * sizeof(GLfloat));
}

void CMapTile::Upload()
{
	m_displayList = glGenLists(1);

	glNewList(m_displayList, GL_COMPILE);

	int y0 = m_startY;
	float du = 1.0f / TILE_SIZE;
	float dv = 1.0f / TILE_SIZE;
	float v = 0;
	for (int row = 0; row < m_numRows - 1; ++row, y0 += m_mapStep, v += dv)
	{
		float u = 0;
		int x0 = m_startX;
		glBegin(GL_TRIANGLE_STRIP);
		for (int column = 0; column < m_numColumns; ++column, x0 += m_mapStep, u += du)
		{
			glTexCoord2f(v + dv, u);
			glVertex3f((float)x0, m_heightMap[(row + 1) * m_numColumns + column] * 4 - 150, -(float)(y0 + m_mapStep));

			glTexCoord2f(v, u);
			glVertex3f((float)x0, m_heightMap[row * m_numColumns + column] * 4 - 150, -(float)(y0));
		}
		glEnd();
	}
	glEndList();

}

void CMapTile::Draw()
{
	if (!m_displayList)
	{
		Upload();
	}
	glCallList(m_displayList);
}

void CMapTile::Destroy()
{
	if (m_displayList != 0)
	{
		glDeleteLists(m_displayList, 1);
		m_displayList = 0;
	}

	if (m_textureName)
	{
		glDeleteTextures(1, &m_textureName);
		m_textureName = 0;
	}

	if (m_detailTextureName)
	{
		glDeleteTextures(1, &m_detailTextureName);
		m_detailTextureName = 0;
	}
}

CMapTile::~CMapTile()
{
}
