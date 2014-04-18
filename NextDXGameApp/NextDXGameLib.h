#pragma once

class NextDXGameLib
{
public:
	NextDXGameLib();
	~NextDXGameLib();

	virtual BOOL Init(HWND hWnd);
	virtual BOOL Update();
	virtual BOOL Render();

private:

};

