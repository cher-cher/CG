#include "stdafx.h"
#include "Kroshe.h"
#include <cmath>

CKroshe::~CKroshe()
{
	DeleteList();
}

void CKroshe::SetupShape(float minRadius, float maxRadius, int petalCount)
{
	DeleteList();
	m_minRadius = minRadius;
	m_maxRadius = maxRadius;
	m_petalCount = petalCount;
}

void CKroshe::SetCenterColor(const glm::vec3 &centerColor)
{
	m_centerColor = centerColor;
}

void CKroshe::SetPetalColor(const glm::vec3 &petalColor)
{
	m_petalColor = petalColor;
}

void CKroshe::Draw() const
{
	// ���� ���������� ������ ��� �� ��� ������, �� ��� ������ ������� ���
	if (!m_displayList)
	{
		// ���������� ����� ���������� ������ ��� ������
		m_displayList = glGenLists(1);
		glNewList(m_displayList, GL_COMPILE);
		// ��� ���������� ������ �������� redraw.
		Redraw();
		// ��������� ���������� ������
		glEndList();
	}

	// �������� ����� ��������� ���������� ������
	glCallList(m_displayList);
}

bool CKroshe::HitTest(const glm::vec2 &point) const
{
	// ����� ������ � ����� (0, 0), ��� ��� ������ �� ������
	// � point ����� point; ��������� �������� ���� ����� �������.
	const float angle = std::atan2(point.y, point.x);
	const float radius = GetRadiusByAngle(angle);

	// ���� ����� ������� ������ �������, ���� ���������.
	// �� ���������� `glm::length` ������ point.length(), ������ ���
	// point.length() ����� ����� ����������� �������, �. �. ����� 2.
	return (glm::length(point) < radius);
}

void CKroshe::DeleteList()
{
	if (m_displayList)
	{
		glDeleteLists(m_displayList, 1);
		m_displayList = 0;
	}
}

void CKroshe::Redraw() const
{
	glColor3f(m_centerColor.x, m_centerColor.y, m_centerColor.z);
	glVertex2f(30, 30);

	// ������� ��� (��� ��������� ������� ��������
	// ��� ����������� ��� ������� 20 ������)
	const float step = float(2 * M_PI) / float(m_petalCount * 20);

	glBegin(GL_TRIANGLE_FAN);

	// ����������� ������� ����� ����� ���� m_centerColor
	glColor3f(m_centerColor.x, m_centerColor.y, m_centerColor.z);
	glVertex2f(0, 0);

	// ������� �������� ����� ����� ���� m_petalColor
	glColor3f(m_petalColor.x, m_petalColor.y, m_petalColor.z);
	for (float angle = 0; angle <= float(2 * M_PI) + 0.5f * step; angle += step)
	{
		// � ���������� ���� ����������� sin(2 * PI) ����� ����������
		// �� sin(0). ������� ���� angle ������� ������ � 2*PI,
		// ������� ��� ������ 0
		// ��� ����� ��� ����, ����� ������ � ����� �����
		// ������� � ����� �����
		float fixedAngle = (fabsf(angle - float(2 * M_PI)) < 1e-4f) ? 0 : angle;

		// ��������� ������ ������������ ���������� ��� ������� ����
		float radius = GetRadiusByAngle(fixedAngle);
		float x = radius * cosf(fixedAngle);
		float y = radius * sinf(fixedAngle);

		// ������� ����� �������
		glVertex2f(x, y);
	}

	glEnd();
}

float CKroshe::GetRadiusByAngle(float angle)const
{
	// ��������� ������ ������������ ���������� ��� ������� ����.
	return 0.5f * (m_maxRadius - m_minRadius)
		* cosf(angle * m_petalCount) + m_minRadius;
}
