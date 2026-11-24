#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>

dx3d::Game::Game(const GameDesc& desc)
	:Base({ *std::make_unique<Logger>(desc.logLevel).release() }),
	m_LoggerPtr{ &m_Logger }
{
	m_GraphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_Logger});
	m_Display = std::make_unique<Window>(WindowDesc{ m_Logger });

	DX3DLogInfo("Game initialized.");
}

dx3d::Game::~Game() {
	DX3DLogInfo("Game deallocation started.");
}

