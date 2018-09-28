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
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / 50 - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		distAngle += rnd;
	}

	{
		// ���@�̊p�x����]������
		Vector3 rotv = this->GetRotation();

		float angle = distAngle - rotv.y;

		// 180�x�𒴂��Ă����ꍇ�A�t���̕����߂�
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// ���
		rotv.y += angle * 0.05f;
		
		
		this->SetRotation(Quaternion::CreateFromYawPitchRoll(rotv.y, rotv.x, rotv.z));
	}


	// �@�̂������Ă�������ɐi��
	{
		static float sin_pos = 0;
		sin_pos += 0.02f;
		// �ړ��ʂ̃x�N�g��
		Vector3 moveV(0,0, -0.1f);
		// �ړ��ʃx�N�g�������@�̊p�x����]������
		float angle = this->GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�������
		Vector3 pos = this->GetPosition();
		this->SetPosition(pos + moveV);
	}
}
