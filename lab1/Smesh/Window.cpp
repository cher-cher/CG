#include "stdafx.h"
#include "Window.h"


namespace
{
	
	// Рисуем контур эллипса
	void StrokeEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);

		// Эллипс представлен в виде незамкнутой ломаной линии, соединяющей
		// pointCount точек на его границе с шагом 2*PI/pointCount
		glBegin(GL_LINE_STRIP);
		for (float angle = 0; angle < float(2 * M_PI); angle += step)
		{
			const float dx = rx * cosf(angle);
			const float dy = ry * sinf(angle);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	// Рисуем закрашенный эллипс
	void FillEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI) / pointCount;

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2f(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	void PartOfEllipse(float xCenter, float yCenter, float rx, float ry, float begin, float end)
	{
		glBegin(GL_LINE_STRIP);
		for (float i = begin; i <= end; i += 0.1f)
		{
			float x = - rx * cosf(i);
			float y = - ry * sinf(i);
			glVertex2f(x + xCenter, y + yCenter);
		}
		glEnd();
	}

	void FillPartOfEllipse(float xCenter, float yCenter, float rx, float ry, float begin, float end, int pointCount = 360)
	{
		const float step = float(2 * M_PI) / pointCount;

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2f(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = begin; angle <= end; angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = - rx * cosf(a);
			const float dy = - ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	void DrawLeftEar(const glm::ivec2 &size, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);
		glColor3f(0.22f, 0.59f, 0.72f);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < float(2 * M_PI); i += step)
		{
			float x = - size.x / 13.2f * cosf(i);
			float y = - size.y / 4.13f * sinf(i);
			float dx = x * cosf(7 * float(M_PI) / 8.f) - y * sinf(7 * float(M_PI) / 8.f);
			float dy = x * sinf(7 * float(M_PI) / 8.f) + y * cosf(7 * float(M_PI) / 8.f);

			glVertex2f(dx + size.x / 2.8f, dy + size.y / 4.1f);
		}
		glEnd();

		glColor3f(0.56f, 0.88f, 0.9f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(size.x / 2.8f, size.y / 4.1f);
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float x = size.x / 13.2f * cosf(a);
			const float y = size.y / 4.13f * sinf(a);

			float dx = x * cosf(7 * float(M_PI) / 8.f) - y * sinf(7 * float(M_PI) / 8.f);
			float dy = x * sinf(7 * float(M_PI) / 8.f) + y * cosf(7 * float(M_PI) / 8.f);
			glVertex2f(dx + size.x / 2.8f, dy + size.y / 4.1f);
		}
		glEnd();
	}

	void DrawRightEar(const glm::ivec2 &size, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);
		glColor3f(0.22f, 0.59f, 0.72f);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < float(2 * M_PI); i += step)
		{
			float x = -size.x / 13.2f * cosf(i);
			float y = -size.y / 4.13f * sinf(i);
			float dx = x * cosf(17 * float(M_PI) / 8.f) - y * sinf(17 * float(M_PI) / 8.f);
			float dy = x * sinf(17 * float(M_PI) / 8.f) + y * cosf(17 * float(M_PI) / 8.f);

			glVertex2f(dx + size.x / 1.55f, dy + size.y / 4.1f);
		}
		glEnd();

		glColor3f(0.56f, 0.88f, 0.9f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(size.x / 1.55f, size.y / 4.1f);
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float x = size.x / 13.2f * cosf(a);
			const float y = size.y / 4.13f * sinf(a);

			float dx = x * cosf(17 * float(M_PI) / 8.f) - y * sinf(17 * float(M_PI) / 8.f);
			float dy = x * sinf(17 * float(M_PI) / 8.f) + y * cosf(17 * float(M_PI) / 8.f);
			glVertex2f(dx + size.x / 1.55f, dy + size.y / 4.1f);
		}
		glEnd();
	}

	void DrawLeftHand(const glm::ivec2 &size, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);
		glColor3f(0.22f, 0.59f, 0.72f);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < float(2 * M_PI); i += step)
		{
			float x = -size.x / 31.f * cosf(i);
			float y = -size.y / 12.4f * sinf(i);
			float dx = x * cosf(4 * float(M_PI) / 3.f) - y * sinf(4 * float(M_PI) / 3.f);
			float dy = x * sinf(4 * float(M_PI) / 3.f) + y * cosf(4 * float(M_PI) / 3.f);

			glVertex2f(dx + size.x / 4.2f, dy + size.y / 1.5f);
		}
		glEnd();

		glColor3f(0.56f, 0.88f, 0.9f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(size.x / 4.2f, size.y / 1.5f);
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float x = size.x / 31.f * cosf(a);
			const float y = size.y / 12.4f * sinf(a);

			float dx = x * cosf(4 * float(M_PI) / 3.f) - y * sinf(4 * float(M_PI) / 3.f);
			float dy = x * sinf(4 * float(M_PI) / 3.f) + y * cosf(4 * float(M_PI) / 3.f);
			glVertex2f(dx + size.x / 4.2f, dy + size.y / 1.5f);
		}
		glEnd();
	}

	void DrawRightHand(const glm::ivec2 &size, int pointCount = 360)
	{
		const float step = float(2 * M_PI / pointCount);
		glColor3f(0.22f, 0.59f, 0.72f);
		glBegin(GL_LINE_STRIP);
		for (float i = 0; i < float(2 * M_PI); i += step)
		{
			float x = -size.x / 31.f * cosf(i);
			float y = -size.y / 12.4f * sinf(i);
			float dx = x * cosf(2 * float(M_PI) / 3.f) - y * sinf(2 * float(M_PI) / 3.f);
			float dy = x * sinf(2 * float(M_PI) / 3.f) + y * cosf(2 * float(M_PI) / 3.f);

			glVertex2f(dx + size.x / 1.3f, dy + size.y / 1.5f);
		}
		glEnd();

		glColor3f(0.56f, 0.88f, 0.9f);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(size.x / 1.3f, size.y / 1.5f);
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float x = size.x / 31.f * cosf(a);
			const float y = size.y / 12.4f * sinf(a);

			float dx = x * cosf(2 * float(M_PI) / 3.f) - y * sinf(2 * float(M_PI) / 3.f);
			float dy = x * sinf(2 * float(M_PI) / 3.f) + y * cosf(2 * float(M_PI) / 3.f);
			glVertex2f(dx + size.x / 1.3f, dy + size.y / 1.5f);
		}
		glEnd();
	}

	void DrawLeftLeg(const glm::ivec2 &size)
	{
		glColor3f(0.56f, 0.88f, 0.9f);
		FillEllipse(size.x / 2.108f, size.y / 1.101f, size.x / 36.47f, size.y / 36.47f);//верхний
		FillEllipse(size.x / 2.48f, size.y / 1.056f, size.x / 36.47f, size.y / 36.47f);//нижний левый

		glRectf(size.x / 2.583f, size.y / 1.078f, size.x / 2.066f, size.y / 1.026f);
		glRectf(size.x / 2.36f, size.y / 1.107f, size.x / 2.f, size.y / 1.03f);

		FillEllipse(size.x / 2.38f, size.y / 1.06f, size.x / 62.f, size.y / 31.f);
		FillEllipse(size.x / 2.21f, size.y / 1.08f, size.x / 62.f, size.y / 31.f);

		glColor3f(0.22f, 0.59f, 0.72f);
		PartOfEllipse(size.x / 2.13f, size.y / 1.06f, size. x / 31.f, size.y / 31.f, float(M_PI), 3 * float(M_PI) / 2.f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 1.99f, size.y / 1.105f);
		glVertex2f(size.x / 1.99f, size.y / 1.05f);
		glEnd();
		PartOfEllipse(size.x / 2.108f, size.y / 1.101f, size.x / 36.47f, size.y / 36.47f, float(M_PI) / 3.f, float(M_PI));
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 2.06f, size.y / 1.026f);
		glVertex2f(size.x / 2.48f, size.y / 1.026f);
		glEnd();
		PartOfEllipse(size.x / 2.48f, size.y / 1.056f, size.x / 36.47f, size.y / 36.47f, 3 * float(M_PI) / 2.f, 9 * float(M_PI) / 4.f);
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 2.66f, size.y / 1.068f);
		glVertex2f(size.x / 2.14f, size.y / 1.137f);
		glEnd();		
	}

	void DrawRightLeg(const glm::ivec2 &size)
	{
		glColor3f(0.56f, 0.88f, 0.9f);
		FillEllipse(size.x / 1.808f, size.y / 1.101f, size.x / 36.47f, size.y / 36.47f);//верхний
		FillEllipse(size.x / 1.58f, size.y / 1.056f, size.x / 36.47f, size.y / 36.47f);//нижний левый
		FillEllipse(size.x / 1.79f, size.y / 1.06f, size.x / 31.f, size.y / 31.f);

		glRectf(size.x / 1.86f, size.y / 1.078f, size.x / 1.6f, size.y / 1.026f);
		FillEllipse(size.x / 1.76f, size.y / 1.095f, size.x / 31.f, size.y / 62.f);
		FillEllipse(size.x / 1.66f, size.y / 1.085f, size.x / 62.f, size.y / 62.f);

		glColor3f(0.22f, 0.59f, 0.72f);
		PartOfEllipse(size.x / 1.79f, size.y / 1.06f, size.x / 31.f, size.y / 31.f, 3 * float(M_PI) / 2.f, 2 * float(M_PI));
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 1.9f, size.y / 1.105f);
		glVertex2f(size.x / 1.9f, size.y / 1.05f);
		glEnd();
		PartOfEllipse(size.x / 1.808f, size.y / 1.101f, size.x / 36.47f, size.y / 36.47f, 0, 3 * float(M_PI) / 4.f);//верхний круг
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 1.75f, size.y / 1.125f);
		glVertex2f(size.x / 1.52f, size.y / 1.07f);
		glEnd();
		PartOfEllipse(size.x / 1.58f, size.y / 1.056f, size.x / 36.47f, size.y / 36.47f, 3 * float(M_PI) / 4.f, 3 * float(M_PI) / 2.f);//нижний правый
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 1.82f, size.y / 1.026f);
		glVertex2f(size.x / 1.55f, size.y / 1.026f);
		glEnd();
	}

	void DrawKroshe(const glm::ivec2 &size)
	{
		glLineWidth(5);
		DrawLeftEar(size);
		DrawRightEar(size);

		glLineWidth(3);
		DrawLeftLeg(size);
		DrawRightLeg(size);

		DrawLeftHand(size);
		DrawRightHand(size);

		glColor3f(0.56f, 0.88f, 0.9f);//тело
		FillEllipse(size.x / 2.f, size.y / 2.f + size.y / 6.8f, size.x / 4.2f, size.y / 4.2f);

		glColor3f(0.22f, 0.59f, 0.72f);//контур тела
		glLineWidth(3);
		StrokeEllipse(size.x / 2.f, size.y / 2.f + size.y / 6.8f, size.x / 4.2f, size.y / 4.2f);

		glColor3f(0.22f, 0.59f, 0.72f);//обводква левого глаз
		glLineWidth(4);
		StrokeEllipse(size.x / 2.29f, size.y / 1.72f, size.x / 15.8f, size.y / 13.7f);

		glColor3f(0.22f, 0.59f, 0.72f);//бровь правый глаз
		glLineWidth(5);
		PartOfEllipse(size.x / 2.29f, size.y / 1.8f, size.x / 15.8f, size.y / 13.7f, float(M_PI) / 3, 2 * float(M_PI) / 3.f);

		glColor3f(1.f, 1.f, 1.f);//левый глаз
		FillEllipse(size.x / 2.29f, size.y / 1.72f, size.x / 15.8f, size.y / 13.7f);

		glColor3f(0.22f, 0.59f, 0.72f);//обводка правого глаза
		glLineWidth(4);
		StrokeEllipse(size.x / 1.77f, size.y / 1.72f, size.x / 15.8f, size.y / 13.7f);

		glColor3f(0.22f, 0.59f, 0.72f);//бровь правый глаз
		glLineWidth(5);
		PartOfEllipse(size.x / 1.77f, size.y / 1.8f, size.x / 15.8f, size.y / 13.7f, float(M_PI) / 3, 2 * float(M_PI) / 3.f);

		glColor3f(1.f, 1.f, 1.f);//правый глаз
		FillEllipse(size.x / 1.77f, size.y / 1.72f, size.x / 15.8f, size.y / 13.7f);

		glColor3f(0, 0, 0);//зрачок левый
		FillEllipse(size.x / 2.13f, size.y / 1.71f, size.x / 56.4f, size.y / 40.f);

		glColor3f(0, 0, 0);//зрачок правый
		FillEllipse(size.x / 1.87f, size.y / 1.71f, size.x / 56.4f, size.y / 40.f);

		glColor3f(1.f, 1.f, 1.f);//блик левый
		FillEllipse(size.x / 2.1f, size.y / 1.77f, size.x / 206.6f, size.y / 206.6f);

		glColor3f(1.f, 1.f, 1.f);//блик правый
		FillEllipse(size.x / 1.85f, size.y / 1.77f, size.x / 206.6f, size.y / 206.6f);

		glColor3f(1.f, 0.27f, 0.38f);//нос
		FillEllipse(size.x / 1.99f, size.y / 1.58f, size.x / 44.2f, size.y / 44.2f);

		glColor3f(0.22f, 0.59f, 0.72f);//smile
		glLineWidth(3);
		PartOfEllipse(size.x / 1.99f, size.y / 1.75f, size.x / 6.25f, size.y / 8.56f, 7.f * float(M_PI) / 6.f, 11.f * float(M_PI) / 6.f);

		glColor3f(1.f, 1.f, 1.f);//левый зуб
		FillPartOfEllipse(size.x / 2.06f, size.y / 1.45f, size.x / 51.6f, size.y / 47.69f, float(M_PI), 2.f * float(M_PI));

		glColor3f(1.f, 1.f, 1.f);//правый зуб
		FillPartOfEllipse(size.x / 1.91f, size.y / 1.45f, size.x / 51.6f, size.y / 47.69f, float(M_PI), 2.f * float(M_PI));

		glColor3f(0.22f, 0.59f, 0.72f);//левая обводка зуба
		PartOfEllipse(size.x / 2.06f, size.y / 1.45f, size.x / 51.6f, size.y / 47.69f, float(M_PI), 17.f * float(M_PI) / 8.f);

		glColor3f(0.22f, 0.59f, 0.72f);//правая обводка зуба
		PartOfEllipse(size.x / 1.91f, size.y / 1.45f, size.x / 51.6f, size.y / 47.69f, 7.f * float(M_PI) / 8.f, 2.f * float(M_PI));

		glColor3f(0.22f, 0.59f, 0.72f);//линия от носа до улыбки
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x / 1.99f, size.y / 1.527f);
		glVertex2f(size.x / 1.99f, size.y / 1.45f);
		glEnd();
	}
}

CWindow::CWindow()
{
	SetBackgroundColor({ 1.f, 1.f, 1.f, 1.f});
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SetupView(size);

	DrawKroshe(size);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	// Матрица ортографического проецирования изображения в трёхмерном пространстве
	// из параллелипипеда с размером, равным (size.X x size.Y x 2).
	const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
	glViewport(0, 0, size.x, size.y);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(matrix));
	glMatrixMode(GL_MODELVIEW);
}
