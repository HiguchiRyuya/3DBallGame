//--------------------------------------------------------------------------------------
// File: Obj3D.cpp
//
// �R�c���f����\������N���X
//
// Date: 2018.6.15
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Obj3D.h"
#include "Game.h"

#include "ModelManager.h"
#include "DXDevice.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Max�G���A
const float Obj3D::MAX_AREA (5.0f);

Obj3D::Obj3D()
	:  m_model(std::weak_ptr<Model>()),m_isMoveObj(false),m_prevPos(0, 0, 0)
{
	
}

bool Obj3D::Update(float elapsedTime)
{
	// ���[���h�s����쐬
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	// �����I�u�W�F�N�g�̏���
	if (m_isMoveObj == true)
	{
		NotOutside();
	}

	m_prevPos = m_position;

	return true;
}

void Obj3D::Render()
{
	// ���f���̕`��
	m_model.lock()->Draw(DXDevice::GetInstance().GetContext(),
		*ModelManager::GetInstance().GetStates(), 
		m_world, 
		*ModelManager::GetInstance().GetView(),
		*ModelManager::GetInstance().GetProjcton());	
}

void Obj3D::NotOutside()
{
	if (m_position.y > MAX_AREA)
	{
		m_vel.z = 0.0f;
		m_vel.x = 0.0f;
		m_position.z += 0.5f;
		
	}
}
