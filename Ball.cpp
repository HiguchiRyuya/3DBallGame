#include "pch.h"
#include "Ball.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Ball::Ball()
	:Obj3D(), m_move(STOP), m_direction(0.0f)
{
	ModelManager::GetInstance().LoadModels(L"Ball.cmo");
	ModelManager::GetInstance().SetModel(m_model, L"Ball.cmo");
	m_isMoveObj = true;
}

bool Ball::Update(float elapsedTime)
{
	// �����x
	m_vel = Vector3(0,0,0);

	switch(m_move)
	{
	// �O�i
	case FORWARD:
		m_vel.z = -0.01f;
		break;
	case BACK:
		m_vel.z = 0.01f;
		break;
	case TURN_LEFT:
		m_vel.x = -0.01;
		//m_direction += XMConvertToRadians(1);
		break;
	case TURN_RIGHT:
		m_vel.x = 0.01;
		//m_direction -= XMConvertToRadians(1);
		break;

	default:
		break;
	}

	m_move = STOP;

	// �{�[���̌����ɉ�]������s����쐬
	Matrix rotY = Matrix::CreateRotationY(m_direction);
	// �����x
	m_vel = Vector3::Transform(m_vel, rotY);
	// ���x�ɉ����x�𑣂�
	m_v += m_vel;
	// �ʒu�ɑ��x�𑣂�
	m_position += m_v;

	// �{�[���̉�]
	Vector3 axis(1, 0, 0);
	rotY = Matrix::CreateRotationY(atan2f(m_v.x, m_v.z));
	axis = Vector3::Transform(axis, rotY);
	// �{�[���̔��a���P�Ȃ̂ňړ��ʂ���]�ʂɂȂ�
	m_rotation *= Quaternion::CreateFromAxisAngle(axis, m_v.Length());

	// ���C�ɂ�錸������
	m_v *= 0.98f;

	// ���[���h�s����쐬
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);


	return false;
}

//void Ball::SetupEffect()
//{
//	// �G�t�F�N�g�̃����_��
//	m_model.lock()->UpdateEffects([&](IEffect* effect)
//	{
//		auto lights = dynamic_cast<IEffectLights*>(effect);
//		if (lights)
//		{
//			// �s�N�Z���P�ʂŃ��C�g�̌v�Z������
//			lights->SetPerPixelLighting(true);
//		}
//	});
//}
