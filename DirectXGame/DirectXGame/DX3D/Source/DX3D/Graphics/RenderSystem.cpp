#include <DX3D/Graphics/RenderSystem.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/SwapChain.h>
using namespace dx3d;

dx3d::RenderSystem::RenderSystem(const RenderSystemDesc& desc)
	:Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	DX3DGrraphicsLogErrorAndThrow(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
		NULL, 0, D3D11_SDK_VERSION,
		&m_D3dDevice, &featureLevel, &m_D3dContext),
		"Direct3D11 initialization failed.");

	DX3DGrraphicsLogErrorAndThrow(
		m_D3dDevice->QueryInterface(IID_PPV_ARGS(&m_DxgiDevice)),
		"QueryInterface failed to retrieve IDXGIDevice."
	);
	DX3DGrraphicsLogErrorAndThrow(
		m_DxgiDevice->GetParent(IID_PPV_ARGS(&m_DxgiAdapter)),
		"QueryInterface failed to retrieve IDXGIAdapter."
	);
	DX3DGrraphicsLogErrorAndThrow(
		m_DxgiAdapter->GetParent(IID_PPV_ARGS(&m_DxgiFactory)),
		"QueryInterface failed to retrieve IDXGIFactory."
	);
}

dx3d::RenderSystem::~RenderSystem() {

}

SwapChainPtr dx3d::RenderSystem::CreateSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, GetGraphicsResourceDesc());
}

GraphicsResourceDesc dx3d::RenderSystem::GetGraphicsResourceDesc() const noexcept
{
	return { {m_Logger}, shared_from_this(), *m_D3dDevice.Get(), *m_DxgiFactory.Get()};
}
