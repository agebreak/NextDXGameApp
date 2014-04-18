#pragma once
#include "Singleton.h"

// 렌더러 관련을 관리하는 전역 클래스
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

