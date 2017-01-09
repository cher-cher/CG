#pragma once

#include <glm/vec3.hpp>
#include <boost/noncopyable.hpp>

class CKroshe : private boost::noncopyable
{
public:
	CKroshe() = default;
	virtual ~CKroshe();

	void SetupShape(float minRadius, float maxRadius, int petalCount);
	void SetCenterColor(const glm::vec3 &centerColor);
	void SetPetalColor(const glm::vec3 &petalColor);

	virtual void Draw()const;
	virtual bool HitTest(const glm::vec2 &point)const;

private:
	void DeleteList();
	void Redraw()const;
	float GetRadiusByAngle(float angle) const;

	mutable unsigned m_displayList = 0;
	float m_minRadius = 0;
	float m_maxRadius = 0;
	int m_petalCount = 0;
	glm::vec3 m_centerColor;
	glm::vec3 m_petalColor;
};
