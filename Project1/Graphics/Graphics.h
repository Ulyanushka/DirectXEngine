#pragma once
#include "AdapterReader.h"
#include "Shaders.h"
#include "Vertex.h"

#include <SpriteBatch.h>
#include <SpriteFont.h>


class Graphics
{
public:

	bool Initialize(HWND hwnd, int width, int height);

	void RenderFrame();

private:

	bool InitializeDirectX(HWND hwnd, int width, int height);

	bool InitializeShaders();
	bool InitializeScene();

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext; //rendering
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain; //buffers for frames
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

	VertexShader vertexShader;
	PixelShader pixelShader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer2;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;

	std::unique_ptr<DirectX::SpriteBatch> spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> spriteFont;
};
