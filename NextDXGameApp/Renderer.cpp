#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
	NT_SAFE_RELEASE(m_pD3DDevice);
	NT_SAFE_RELEASE(m_pD3D);
}

BOOL Renderer::Init(HWND hWnd)
{
	if (nullptr == (GetInstance()->m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		// ¿À·ù
		MessageBox(NULL, L"Could not Create D3D", NULL, MB_OK);
		return FALSE;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	LPDIRECT3DDEVICE9 pDevice = nullptr;
	if (FAILED(GetInstance()->m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice)))
	{
		MessageBox(NULL, L"Could not CreateDevice", NULL, MB_OK);
		return FALSE;
	}

	GetInstance()->m_hWnd = hWnd;
	GetInstance()->m_pD3DDevice = pDevice;

	return TRUE;
}

BOOL Renderer::Render()
{
	GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	if (FAILED(GetDevice()->BeginScene()))
		return FALSE;


	GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);

	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);


	GetDevice()->EndScene();

	GetDevice()->Present(NULL, NULL, NULL, NULL);

	return TRUE;
}
