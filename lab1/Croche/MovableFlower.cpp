#include "stdafx.h"
#include "MovableFlower.h"

void CMovableFlower::Draw() const
{
	// ������������ Model-View �������,
	// ������ ��� ����� ����������� �� ������ (x, y, 0)
	glm::vec3 offset = { m_position.x, m_position.y, 0.f };
	glm::mat4 transform = glm::translate(glm::mat4(), offset);
	// ��������� ������ ������� � ���� ������ ��������
	glPushMatrix();
	glLoadMatrixf(glm::value_ptr(transform));
	// ������ ��������� �� ���������
	CKroshe::Draw();
	// ��������� ������ ������� �� ����� ������ ��������
	glPopMatrix();
}

bool CMovableFlower::HitTest(const glm::vec2 &point) const
{
	// �������� CKroshe::HitTest �� ��������� ����������� ������.
	return CKroshe::HitTest(point - m_position);
}

const glm::vec2 &CMovableFlower::GetPosition() const
{
	return m_position;
}

void CMovableFlower::SetPosition(const glm::vec2 &position)
{
	m_position = position;
}
