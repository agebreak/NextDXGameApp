#include "stdafx.h"
#include "NTObject.h"
#include "NTDefine.h"
#include "Renderer.h"


NTObject::NTObject()
{
	ZeroMemory(&m_Postion, sizeof(m_Postion));
	ZeroMemory(&m_Rotation, sizeof(m_Rotation));
	D3DXMatrixIdentity(&m_matWorld);
}

NTObject::~NTObject()
{
	delete[] m_pMaterials;
	for (DWORD i = 0; i < m_NumMaterial; ++i)
	{
		NT_SAFE_RELEASE(m_pTexture[i]);
	}
	delete[] m_pTexture;	

	NT_SAFE_RELEASE(m_pMesh);
}

BOOL NTObject::LoadFromXFile(std::wstring fileName)
{
	if (fileName.empty() || !Renderer::GetDevice())
		return FALSE;	
	
	LPD3DXBUFFER D3dxMtrialBuffer;	

	//x file import
	if (FAILED(D3DXLoadMeshFromX(fileName.c_str(), D3DXMESH_MANAGED, Renderer::GetDevice(), NULL,
		&D3dxMtrialBuffer, NULL, &m_NumMaterial, &m_pMesh)))
	{
		MessageBox(NULL, L"Could not find x file", L"Meshes.exe", MB_OK);
		
		return FALSE;
	}

	//import한 mesh에 normal 값이 없는 경우 normal 계산
	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* pTempMesh = 0;
		m_pMesh->CloneMeshFVF(D3DXMESH_MANAGED, m_pMesh->GetFVF() | D3DFVF_NORMAL, Renderer::GetDevice(), &pTempMesh);

		D3DXComputeNormals(pTempMesh, 0);

		m_pMesh->Release();
		m_pMesh = pTempMesh;
	}

	// 마테리얼 카피
	D3DXMATERIAL* d3dxMarteials = (D3DXMATERIAL*)D3dxMtrialBuffer->GetBufferPointer();
	m_pMaterials = new D3DMATERIAL9[m_NumMaterial];
	m_pTexture = new LPDIRECT3DTEXTURE9[m_NumMaterial];	

	for (DWORD i = 0; i < m_NumMaterial; ++i)
	{
		m_pMaterials[i] = d3dxMarteials[i].MatD3D;

		m_pMaterials[i].Ambient = m_pMaterials[i].Diffuse;

		m_pTexture[i] = nullptr;
		if ((NULL != d3dxMarteials[i].pTextureFilename) && lstrlenA(d3dxMarteials[i].pTextureFilename)>0)
		{
			if (FAILED(D3DXCreateTextureFromFileA(Renderer::GetDevice(), d3dxMarteials[i].pTextureFilename, &m_pTexture[i])))
			{
				MessageBox(NULL, L"Could not find texture map", NULL, MB_OK);				
			}
		}
	}


	D3dxMtrialBuffer->Release();

	return TRUE;
}

void NTObject::UpdateMatrix()
{
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIX matRot, matPos;
	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matPos);

	D3DXMatrixRotationYawPitchRoll(&matRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&matPos, m_Postion.x, m_Postion.y, m_Postion.z);
	m_matWorld = matRot * matPos;
}

void NTObject::Render()
{
	UpdateMatrix();

	Renderer::GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);

	for (DWORD i = 0; i < m_NumMaterial; ++i)
	{
		Renderer::GetDevice()->SetMaterial(&m_pMaterials[i]);
		Renderer::GetDevice()->SetTexture(0, m_pTexture[i]);

		m_pMesh->DrawSubset(i);
	}
}
