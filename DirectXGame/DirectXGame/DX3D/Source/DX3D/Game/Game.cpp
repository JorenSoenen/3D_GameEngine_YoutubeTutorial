#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc)
	:Base({ *std::make_unique<Logger>(desc.logLevel).release() }),
	m_LoggerPtr{ &m_Logger }
{
	m_GraphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_Logger});
	m_Display = std::make_unique<Display>(DisplayDesc{ {m_Logger, desc.windowSize}, m_GraphicsEngine->GetRenderSystem() });

	DX3DLogInfo("Game initialized.");
}

dx3d::Game::~Game() {
	DX3DLogInfo("Game deallocation started.");
}

