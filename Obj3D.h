//--------------------------------------------------------------------------------------
// File: Obj3D.h
//
// �R�c���f����\������N���X
//
// Date: 2018.6.15
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ModelManager.h"


class Game;

class Obj3D
{
protected:

	// �萔
	static const float MAX_AREA;

	// �����x
	DirectX::SimpleMath::Vector3 m_vel;

	// ���f���n���h��
	std::weak_ptr<DirectX::Model> m_model;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;

	// ��]
	DirectX::SimpleMath::Quaternion m_rotation;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	// �����I�u�W�F�N�g���̕ϐ�
	bool m_isMoveObj;

	// �O�̃|�W�V������ۊ�
	DirectX::SimpleMath::Vector3 m_prevPos;

public:
	// �R���X�g���N�^
	Obj3D();

	// �X�V
	virtual bool Update(float elapsedTime);

	// �`��
	virtual void Render();

	// �ʒu��ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// ��]��ݒ肷��֐�
	void SetRotation(DirectX::SimpleMath::Quaternion rotation) { m_rotation = rotation; }

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	DirectX::SimpleMath::Quaternion GetRotation() { return m_rotation; }

	void IsMoveObject(bool isMove) { m_isMoveObj = isMove; }
	
	// �����Ă���I�u�W�F�N�g����O����o�Ȃ��悤�ɂ���֐�
	void NotOutside();
};
