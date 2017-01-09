#include "stdafx.h"
#include "Bodies.h"
#include <stdint.h>

namespace
{

	typedef glm::vec3 Vertex;

	// Вершины куба служат материалом для формирования треугольников,
	// составляющих грани куба.
	const Vertex CUBE_VERTICIES[] = {

		{ 0.204, -0.691, -0.376 }, // 1
		{ 0.691, -0.204, 0.376 }, // 2
		{ 0.691, -0.376, -0.204 },// 3
		{ 0.204, -0.376, 0.691 },// 4

		{ 0.376, 0.204, 0.691 },// 5
		{ 0.376, -0.691, 0.204 },// 6
		{ 0.204, 0.691, 0.376 },// 7
		{ -0.204, 0.691, -0.376 },// 8
		{ -0.691, 0.376, -0.204 },// 9
		{ -0.691, -0.204, -0.371 },// 10
		{ -0.376, 0.204, -0.691 },// 11
		{ -0.376, -0.691, -0.204 },// 12

		{ -0.204, -0.376, -0.691 }, // 13
		{ 0.376, -0.204, -0.691 }, // 14
		{ -0.204, -0.691, 0.376 }, // 15
		{ 0.691, 0.376, 0.204 }, // 16
		{ -0.376, -0.204, 0.691 }, // 17
		{ -0.691, -0.376, 0.204 }, // 18
		{ -0.691, 0.204, 0.376 }, // 19
		{ -0.376, 0.691, 0.204 }, // 20

		{ -0.204, 0.376, 0.691 },// 21
		{ 0.204, 0.376, -0.691 },// 22
		{ 0.376, 0.691, -0.204 },// 23
		{ 0.691, 0.204, -0.376 }// 24
	};


	struct STriangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t colorIndex;
	};

	// Привыкаем использовать 16-битный unsigned short,
	// чтобы экономить память на фигурах с тысячами вершин.
	const STriangleFace CUBE_FACES[] = {
		{ 4, 20, 16, static_cast<uint16_t>(SnubCube::Right) }, //квадрат оранжевый
		{ 16, 3, 4, static_cast<uint16_t>(SnubCube::Right) }, //квадрат 

		{ 5, 14, 11, static_cast<uint16_t>(SnubCube::Front) }, //квадрат нижний
		{ 11, 0, 5, static_cast<uint16_t>(SnubCube::Front) }, //квадрат

		{ 15, 1, 2, static_cast<uint16_t>(SnubCube::Left) }, //квадрат зеленый
		{ 2, 23, 15, static_cast<uint16_t>(SnubCube::Left) }, //квадрат

		{ 10, 21, 13, static_cast<uint16_t>(SnubCube::Bottom) }, //квадрат белый
		{ 13, 12, 10, static_cast<uint16_t>(SnubCube::Bottom) }, //квадрат

		{ 19, 6, 22, static_cast<uint16_t>(SnubCube::Top) }, //квадрат верхний
		{ 22, 7, 19, static_cast<uint16_t>(SnubCube::Top) }, //квадрат

		{ 17, 18, 8, static_cast<uint16_t>(SnubCube::Back) }, //квадрат красный
		{ 8, 9, 17, static_cast<uint16_t>(SnubCube::Back) }, //квадрат

		{ 14, 3, 16, static_cast<uint16_t>(SnubCube::Back) },
		{ 14, 5, 3, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 3, 5, 1, static_cast<uint16_t>(SnubCube::Top) },
		{ 3, 1, 4, static_cast<uint16_t>(SnubCube::Front) },
		{ 4, 1, 15, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 5, 2, 1, static_cast<uint16_t>(SnubCube::Right) },
		{ 5, 0, 2, static_cast<uint16_t>(SnubCube::Left) },
		{ 7, 22, 21, static_cast<uint16_t>(SnubCube::Back) },
		{ 7, 21, 10, static_cast<uint16_t>(SnubCube::Left) },
		{ 8, 7, 10, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 8, 10, 9, static_cast<uint16_t>(SnubCube::Top) },
		{ 9, 10, 12, static_cast<uint16_t>(SnubCube::Left) },
		{ 13, 0, 12, static_cast<uint16_t>(SnubCube::Front) },
		{ 12, 0, 11, static_cast<uint16_t>(SnubCube::Left) },
		{ 23, 2, 13, static_cast<uint16_t>(SnubCube::Right) },
		{ 21, 23, 13, static_cast<uint16_t>(SnubCube::Top) },
		{ 13, 2, 0, static_cast<uint16_t>(SnubCube::Back) },
		{ 11, 14, 17, static_cast<uint16_t>(SnubCube::Left) },
		{ 20, 6, 19, static_cast<uint16_t>(SnubCube::Right) },
		{ 6, 20, 4, static_cast<uint16_t>(SnubCube::Front) },
		{ 22, 15, 23, static_cast<uint16_t>(SnubCube::Top) },
		{ 6, 15, 22, static_cast<uint16_t>(SnubCube::Left) },
		{ 6, 4, 15, static_cast<uint16_t>(SnubCube::Back) },
		{ 14, 16, 17, static_cast<uint16_t>(SnubCube::Right) },
		{ 18, 17, 16, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 18, 16, 20, static_cast<uint16_t>(SnubCube::Front) },
		{ 12, 11, 9, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 8, 19, 7, static_cast<uint16_t>(SnubCube::Top) },
		{ 18, 19, 8, static_cast<uint16_t>(SnubCube::Left) },
		{ 20, 19, 18, static_cast<uint16_t>(SnubCube::Bottom) },
		{ 11, 17, 9, static_cast<uint16_t>(SnubCube::Front) },
		{ 21, 22, 23, static_cast<uint16_t>(SnubCube::Right) },
	};

}

CIdentityCube::CIdentityCube()
	: m_alpha(1)
{
	// Используем белый цвет по умолчанию.
	for (glm::vec3 &color : m_colors)
	{
		color.x = 1;
		color.y = 1;
		color.z = 1;
	}
}

void CIdentityCube::Update(float deltaTime)
{
	(void)deltaTime;
}

void CIdentityCube::Draw() const
{
	if (m_alpha < 0.99f)
	{
		glFrontFace(GL_CW);
		OutputFaces();
		glFrontFace(GL_CCW);
	}
	OutputFaces();
}

void CIdentityCube::SetFaceColor(SnubCube face, const glm::vec3 &color)
{
	const size_t index = static_cast<size_t>(face);
	assert(index < COLORS_COUNT);
	m_colors[index] = color;
}


void CIdentityCube::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void CIdentityCube::DrawObject()
{

}

void CIdentityCube::OutputFaces() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : CUBE_FACES)
	{
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();

	//glEnable(GL_LIGHTING);
	glCullFace(GL_FRONT_AND_BACK);
	glBegin(GL_TRIANGLES);
	for (const STriangleFace &face : CUBE_FACES)
	{
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = m_colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
	}
	glEnd();
	/*glDisable(GL_LIGHTING);*/

	// TODO: draw edges without blending
	glColor4f(0, 0, 0, 1);
	for (const STriangleFace &face : CUBE_FACES)
	{
		glBegin(GL_LINE_STRIP);
		const Vertex &v1 = CUBE_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = CUBE_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = CUBE_VERTICIES[face.vertexIndex3];

		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
		glEnd();
	}
}


