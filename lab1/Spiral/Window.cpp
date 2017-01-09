#include "stdafx.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "Window.h"

namespace
{
	void DrawCoordinates(const glm::ivec2 & size)
	{
		const glm::vec2 halfSize = 0.5f * glm::vec2(size);

		//система координат
		glBegin(GL_LINES);
		glVertex2f(0.0f, halfSize.y);
		glVertex2f(float(size.x), halfSize.y);

		glVertex2f(halfSize.x, 0.0f);
		glVertex2f(halfSize.x, float(size.y));

		glVertex2f(size.x / 4.f, 0.0f);
		glVertex2f(float(size.x) - size.x / 4.f, float(size.y));

		glVertex2f(size.x - size.x / 4.f, 0.0f);
		glVertex2f(size.x / 4.f, float(size.y));

		glVertex2f(0.0f, size.y / 4.f);
		glVertex2f(float(size.x), size.y - size.y / 4.f);

		glVertex2f(float(size.x), size.y / 4.f);
		glVertex2f(0.0f, size.y - size.y / 4.f);
		glEnd();

		glBegin(GL_LINE_STRIP);//стрелки
		glVertex2f(halfSize.x - 5.f, size.y / 32.f);
		glVertex2f(halfSize.x, 0.0f);

		glVertex2f(halfSize.x, 0.0f);
		glVertex2f(halfSize.x + 5.f, size.y / 32.f);

		glEnd();

		//стрелки
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x - size.x / 32.f, size.y / 2.f - 5.f);
		glVertex2f(float(size.x), size.y / 2.f);

		glVertex2f(float(size.x), halfSize.y);
		glVertex2f(size.x - size.x / 32.f, halfSize.y + 5.f);
		glEnd();


		//окружности для полярной системы координат
		size_t n = 40;
		for (size_t k = 0; k <= 5; k++)
		{
			glBegin(GL_LINE_LOOP);
			for (size_t i = 0; i < n; i++)
			{
				float angle = 2.0f * float(M_PI) * float(i) / float(n);
				float dx = k * 2.f * float(M_PI) * 8.f * cosf(angle);
				float dy = k * 2.f * float(M_PI) * 8.f * sinf(angle);
				glVertex2f(size.x / 2.f + dx, size.y / 2.f + dy);
			}
			glEnd();
		}
	}

	void DrawLogSpiral(const glm::ivec2 & size)
	{
		float segment = 10.f * float(M_PI);
		glBegin(GL_LINE_STRIP);

		for (float i = 0.0f; i <= segment; i += 0.1f)
		{
			// TODO: simplify expressions
			const glm::vec2 halfSize = 0.5f * glm::vec2(size);
			const glm::vec2 numberOfTurns = glm::vec2(size) * 0.03125f;
			const float radius = std::exp(0.0824f * i);
			const glm::vec2 direction = { -std::cos(i), std::sin(i) };
			const glm::vec2 pos = numberOfTurns * radius * direction + halfSize;
			glVertex2f(pos.x, pos.y);
		}
		glEnd();
	}
}

CWindow::CWindow()
{
}


CWindow::~CWindow()
{
}

void CWindow::OnWindowEvent(const SDL_Event &event)
{

}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	(void)deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 & size)
{
	SetupView(size);
	glColor3f(1, 1, 1);
	glLineWidth(1);
	DrawCoordinates(size);
	glColor3f(1, 0, 0);
	glLineWidth(2);
	DrawLogSpiral(size);	
}

void CWindow::SetupView(const glm::ivec2 & size)
{
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}