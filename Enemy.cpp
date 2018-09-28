#include "pch.h"
#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy()
	:Obj3D()
{
	m_position = Vector3(0, 0, 0);
	ModelManager::GetInstance().LoadModels(L"Eye.cmo");
	ModelManager::GetInstance().SetModel(m_model, L"Eye.cmo");
	m_isMoveObj = true;
}

bool Enemy::Update(float elapsedTime)
{
	Obj3D::Update(elapsedTime);
	this->NotSensed();
	return false;
}

void Enemy::NotSensed()
{
	static int timer = 60;
	static float distAngle = 0.0f;

	timer--;

	if (timer < 0)
	{
		timer = 60;
		// -0.5～+0.5の乱数
		float rnd = (float)rand() / 50 - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		distAngle += rnd;
	}

	{
		// 自機の角度を回転させる
		Vector3 rotv = this->GetRotation();

		float angle = distAngle - rotv.y;

		// 180度を超えていた場合、逆回りの方が近い
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// 補間
		rotv.y += angle * 0.05f;
		
		
		this->SetRotation(Quaternion::CreateFromYawPitchRoll(rotv.y, rotv.x, rotv.z));
	}


	// 機体が向いている方向に進む
	{
		static float sin_pos = 0;
		sin_pos += 0.02f;
		// 移動量のベクトル
		Vector3 moveV(0,0, -0.1f);
		// 移動量ベクトルを自機の角度分回転させる
		float angle = this->GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動させる
		Vector3 pos = this->GetPosition();
		this->SetPosition(pos + moveV);
	}
}
