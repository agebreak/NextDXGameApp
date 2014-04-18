#include "stdafx.h"
#include "NextDXGameLib.h"
#include "Renderer.h"

NextDXGameLib::NextDXGameLib()
{

}

NextDXGameLib::~NextDXGameLib()
{

}

BOOL NextDXGameLib::Init(HWND hWnd)
{
	Renderer::Init(hWnd);

	return TRUE;
}

BOOL NextDXGameLib::Update()
{
	return TRUE;
}

BOOL NextDXGameLib::Render()
{


	return TRUE;
}
