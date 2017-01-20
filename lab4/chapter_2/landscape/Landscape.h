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
	~CLandscape();
	void Draw();

private:
	bool LoadRawFile();

	BYTE m_heightMap[VERTEX_TILE_SIZE*VERTEX_TILE_SIZE]; 
	CMapTile m_map;
	CTexture2DUniquePtr m_pEarthTexture;
	SMeshP3NT2 m_mesh;

	bool m_isDirty = true;
};
