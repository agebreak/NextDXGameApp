#pragma once
#include "Singleton.h"

// ������ ������ �����ϴ� ���� Ŭ����
class Renderer : public Singleton<Renderer>
{
public:
	Renderer();
	~Renderer();

	static BOOL Init(HWND hWnd);

	static LPDIRECT3DDEVICE9 GetDevice() {return GetInstance()->m_pD3DDevice;}
	static BOOL Render();

private:	
	LPDIRECT3D9			m_pD3D = nullptr;
	LPDIRECT3DDEVICE9	m_pD3DDevice = nullptr;
	HWND				m_hWnd = nullptr;;
};

