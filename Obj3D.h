//--------------------------------------------------------------------------------------
// File: Obj3D.h
//
// ３Ｄモデルを表示するクラス
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

	// 定数
	static const float MAX_AREA;

	// 加速度
	DirectX::SimpleMath::Vector3 m_vel;

	// モデルハンドル
	std::weak_ptr<DirectX::Model> m_model;

	// 位置
	DirectX::SimpleMath::Vector3 m_position;

	// 回転
	DirectX::SimpleMath::Quaternion m_rotation;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// 動くオブジェクトかの変数
	bool m_isMoveObj;

	// 前のポジションを保管
	DirectX::SimpleMath::Vector3 m_prevPos;

public:
	// コンストラクタ
	Obj3D();

	// 更新
	virtual bool Update(float elapsedTime);

	// 描画
	virtual void Render();

	// 位置を設定する関数
	void SetPosition(DirectX::SimpleMath::Vector3 position) { m_position = position; }

	// 回転を設定する関数
	void SetRotation(DirectX::SimpleMath::Quaternion rotation) { m_rotation = rotation; }

	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }

	DirectX::SimpleMath::Quaternion GetRotation() { return m_rotation; }

	void IsMoveObject(bool isMove) { m_isMoveObj = isMove; }
	
	// 動いているオブジェクトを場外から出ないようにする関数
	void NotOutside();
};
