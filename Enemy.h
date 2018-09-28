#pragma once
#include "Obj3D.h"

class Enemy :public Obj3D
{
private:
public:
	Enemy();
	bool Update(float elapsedTime) override;

	// プレイヤーを感知していないとき
	void NotSensed();

public:

};