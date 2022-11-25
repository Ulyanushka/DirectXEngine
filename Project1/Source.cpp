#include "Engine.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	/*
	HRESULT hr = E_ABORT;
	if (SUCCEEDED(hr))
	{
		MessageBoxA(NULL, "SUCCESS", "SUCCESS", MB_ICONINFORMATION);
	}
	if (FAILED(hr))
	{
		ErrorLogger::Log(E_INVALIDARG, "Test Message");
	}
	*/

	Engine engine;
	if (engine.Initialize(hInstance, "Title", "MyWindowClass", 800, 600))
	{
		while (engine.ProcessMessages() == true)
		{
			engine.Update();
			engine.RenderFrame();
		}
	}

	return 0;
}

/////////////////////////////////////////////////////
//1
//setting our rendering pipeline:
//INPUT ASSEMBLER - completed
//VERTEX SHADER - completed
//RASTERIZER - completed
//PIXEL SHADER - completed
//OUTPUT MERGER - completed
//
//2
//create our vertex buffer
//draw
//
//17 7:04
/////////////////////////////////////////////////////

