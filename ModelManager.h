#pragma once
#include "Utility\SingletonBase.h"
#include "DeviceResources.h"
#include <map>
#include <memory>
#include <Model.h>
#include <string>

class ModelManager :public SingletonBase<ModelManager>
{
	friend SingletonBase<ModelManager>;
	
private:
	DirectX::CommonStates* m_states;
	DirectX::SimpleMath::Matrix* m_view;
	DirectX::SimpleMath::Matrix* m_projection;

	std::map<std::wstring,std::shared_ptr<DirectX::Model>> m_models;

public:
	//コモンステートを取得する関数
	DirectX::CommonStates* GetStates() { return m_states; }

	//ビュー行列を取得する関数
	DirectX::SimpleMath::Matrix* GetView() { return m_view; }

	//射影行列を取得する関数
	DirectX::SimpleMath::Matrix* GetProjcton() { return m_projection; }

	//コモンステートを取得する関数
	void SetStates(DirectX::CommonStates* states) { m_states = states; }

	//ビュー行列を取得する関数
	void SetView(DirectX::SimpleMath::Matrix* view) { m_view = view; }

	//射影行列を取得する関数
	void SetProjcton(DirectX::SimpleMath::Matrix* projection) { m_projection = projection; }


	bool LoadModels(std::wstring path);

	bool SetModel(std::weak_ptr<DirectX::Model>& ptr,std::wstring path);

private:
	ModelManager(){}
	~ModelManager(){}
};