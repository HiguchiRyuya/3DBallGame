
#pragma once

#include "Obj3D.h"

class Ball :public Obj3D
{
public:
	enum MOVE
	{
		STOP,
		FORWARD,
		BACK,
		TURN_LEFT,
		TURN_RIGHT,
		JAMP,
	};

private:
	// 移動ステート
	MOVE m_move;

	// 向き(ラジアン)
	float m_direction;

	// 速度
	DirectX::SimpleMath::Vector3 m_v;

public:
	Ball();
	bool Update(float elapsedTime) override;


public:
	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns></returns>
	
	// 向き
	float GetDirection() { return m_direction; }

public:
	/// <summary>
	/// セッター
	/// </summary>
	
	// 移動
	void Move(MOVE move) { m_move = move; }
	
public:
	/// <summary>
	/// ファンクション
	/// </summary>
	
	//void SetupEffect();


};