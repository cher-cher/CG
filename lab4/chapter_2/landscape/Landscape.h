#pragma once

#include "MeshP3NT2.h"
#include "libchapter2.h"
#include "MapTile.h"
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>


class CLandscape
{
public:
	CLandscape();
	void Draw();

private:
	BYTE m_heightMap[VERTEX_TILE_SIZE*VERTEX_TILE_SIZE]; //карта высот
	CMapTile m_map;
	CTexture2DUniquePtr m_pEarthTexture;
	float scaleValue = 0.15f;

	bool LoadRawFile();

	SMeshP3NT2 m_mesh;
	bool m_isDirty = true;
	void Triangulate();

};
