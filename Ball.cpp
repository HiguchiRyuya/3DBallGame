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
	// 加速度
	m_vel = Vector3(0,0,0);

	switch(m_move)
	{
	// 前進
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

	// ボールの向きに回転させる行列を作成
	Matrix rotY = Matrix::CreateRotationY(m_direction);
	// 加速度
	m_vel = Vector3::Transform(m_vel, rotY);
	// 速度に加速度を促す
	m_v += m_vel;
	// 位置に速度を促す
	m_position += m_v;

	// ボールの回転
	Vector3 axis(1, 0, 0);
	rotY = Matrix::CreateRotationY(atan2f(m_v.x, m_v.z));
	axis = Vector3::Transform(axis, rotY);
	// ボールの半径が１なので移動量が回転量になる
	m_rotation *= Quaternion::CreateFromAxisAngle(axis, m_v.Length());

	// 摩擦による減速する
	m_v *= 0.98f;

	// ワールド行列を作成
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);


	return false;
}

//void Ball::SetupEffect()
//{
//	// エフェクトのラムダ式
//	m_model.lock()->UpdateEffects([&](IEffect* effect)
//	{
//		auto lights = dynamic_cast<IEffectLights*>(effect);
//		if (lights)
//		{
//			// ピクセル単位でライトの計算をする
//			lights->SetPerPixelLighting(true);
//		}
//	});
//}
