#pragma once

#define NT_SAFE_RELEASE(x) if(x) x->Release(); x = nullptr;
	
	