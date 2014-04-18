#pragma once

/// 모델 오브젝트 클래스
class NTObject
{
public:
	NTObject();
	~NTObject();

	BOOL LoadFromXFile(std::wstring fileName);

	void SetPosition(const D3DXVECTOR3& pos) { m_Postion = pos; }
	void SetRotation(const D3DXVECTOR3& rot) { m_Rotation = rot; }
	void UpdateMatrix();
	
	void Render();

protected:
	LPD3DXMESH			m_pMesh = nullptr;
	D3DMATERIAL9*		m_pMaterials = nullptr;
	LPDIRECT3DTEXTURE9* m_pTexture = nullptr;
	DWORD				m_NumMaterial = 0;

	// 위치 관련
	D3DXVECTOR3			m_Postion;
	D3DXVECTOR3			m_Rotation;
	D3DXMATRIX			m_matWorld;
};

