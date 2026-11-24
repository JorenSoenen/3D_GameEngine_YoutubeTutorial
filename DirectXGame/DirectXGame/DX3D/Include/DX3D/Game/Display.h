#pragma once
#include <DX3D/Window/Window.h>
//#include <DX3D/Core/Common.h>

namespace dx3d {
	class Display final : public Window {
	public:
		explicit Display(const DisplayDesc& desc);

	private:
		SwapChainPtr m_SwapChain{};
	};
}