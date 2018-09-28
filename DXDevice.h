#pragma once
#include <d3d11.h>
#include "Utility\SingletonBase.h"

class DXDevice : public SingletonBase<DXDevice>
{

	friend SingletonBase<DXDevice>;

private:
	ID3D11DeviceContext*	m_context;
	ID3D11Device*			m_device;
	

public:
	void SetContext(ID3D11DeviceContext* context) { m_context = context; };
	void SetDevice(ID3D11Device* device) { m_device = device; };

	ID3D11DeviceContext*	GetContext() { return m_context; };
	ID3D11Device*			GetDevice() { return m_device; };

private:
	DXDevice() {};
	~DXDevice() {};
};