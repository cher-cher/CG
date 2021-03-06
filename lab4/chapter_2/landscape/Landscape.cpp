#include "stdafx.h"
#include "Landscape.h"
#include "MapTile.h"
#include <stdint.h>

namespace
{
	// ��������� ������������ 16-������ unsigned short,
	// ����� ��������� ������ �� ������� � �������� ������.

	const char HIGHT_MAP_PATH[] = "res/galaxy/height.raw";
	const size_t STEP_SIZE = 6;
	const float SCALE_VALUE = 0.15f;
}
using namespace std;


CLandscape::CLandscape()
{
	LoadRawFile();
}

void CLandscape::Draw()
{
	m_map.Draw();
}


bool CLandscape::LoadRawFile()
{
	ifstream inputFile(HIGHT_MAP_PATH, ios_base::binary);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("Cannot open file for reading: " + string(HIGHT_MAP_PATH, sizeof(HIGHT_MAP_PATH)));
	}
	char depth;
	size_t i = 0;
	while (inputFile.get(depth) && i != VERTEX_TILE_SIZE * VERTEX_TILE_SIZE)
	{
		m_heightMap[i++] = static_cast<BYTE>(depth);
	}
	inputFile.close();

	static const float HEIGHT_SCALE = 90 / 255.0f;
	static const float HEIGHT_OFFSET = HEIGHT_SCALE / 2;
	GLfloat heightMap[VERTEX_TILE_SIZE * VERTEX_TILE_SIZE];

	for (size_t j = 0; j < sizeof(m_heightMap); j++)
	{
		heightMap[j] = m_heightMap[j] * HEIGHT_SCALE + HEIGHT_OFFSET;
	}

	m_map.Load(-VERTEX_TILE_SIZE * 3, -VERTEX_TILE_SIZE * 3, VERTEX_TILE_SIZE, VERTEX_TILE_SIZE, STEP_SIZE, &heightMap[0]);

	return true;
}

CLandscape::~CLandscape() 
{
}