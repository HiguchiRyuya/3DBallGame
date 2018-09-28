#include "pch.h"
#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player()
	:Obj3D(), m_direction(0.0f)
{
	ModelManager::GetInstance().LoadModels(L"Player.cmo");
	ModelManager::GetInstance().SetModel(m_model, L"Player.cmo");
	m_isMoveObj = true;
}

bool Player::Update(float elapsedTime)
{
	Obj3D::Update(elapsedTime);
	return false;
}

