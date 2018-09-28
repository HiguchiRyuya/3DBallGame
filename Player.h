#pragma once

#include "Obj3D.h"
#include <SimpleMath.h>

class Player : public Obj3D
{
public:
private:
	float m_direction;
	DirectX::SimpleMath::Vector3 m_pos;

public:
	Player();
	bool Update(float elapsedTime) override;

public:
	float GetDirection() { return m_direction; }
	DirectX::SimpleMath::Vector3 GetPos(){ return m_pos; }

	void SetPos(DirectX::SimpleMath::Vector3 pos) { m_pos = pos; }

};