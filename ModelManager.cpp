#include "pch.h"
#include "ModelManager.h"
#include "DXDevice.h"

using namespace std;
using namespace DirectX;

bool ModelManager::LoadModels(std::wstring path)
{
	if (m_models.count(path) != 0)
	{
		return false;
	}

	EffectFactory fx(DXDevice::GetInstance().GetDevice());
	fx.SetDirectory(L"Resources\\Models"); // モデルのテクスチャが入っているフォルダを指定

	wstring fullpath = L"Resources\\Models\\" + path;

	// 作成したモデルをモデルデータのマップに入れる
	m_models[path] = move(Model::CreateFromCMO(DXDevice::GetInstance().GetDevice(), fullpath.c_str(), fx));

	return true;

}

bool ModelManager::SetModel(std::weak_ptr<DirectX::Model>& ptr,wstring path)
{
	if (m_models.count(path) == 0)
	{
		return false;
	}

	ptr = m_models[path];

	return true;
}
