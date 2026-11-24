#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <d3d11.h>
#include <wrl.h>

namespace dx3d {
	class RenderSystem : public Base {
	public:
		explicit RenderSystem(const RenderSystemDesc& desc);
		virtual ~RenderSystem() override;

		SwapChainPtr CreateSwapChain(const SwapChainDesc& desc);

	private:
		GraphicsResourceDesc GetGraphicsResourceDesc() const;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_D3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_D3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> m_DxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> m_DxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> m_DxgiFactory{};
	};
}