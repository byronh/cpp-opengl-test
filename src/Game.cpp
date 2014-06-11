#include "Game.h"

#include "components/RenderComponent.h"

#include "systems/RenderSystem.h"

namespace astro
{

	void Game::setup()
	{
		artemis::SystemManager * sm = world.getSystemManager();
		renderSystem = (RenderSystem*)sm->setSystem(new RenderSystem());
		sm->initializeAll();

		player = &world.createEntity();
		player->addComponent(new RenderComponent());
		player->refresh();		
	}

	void Game::update(float delta)
	{
		world.loopStart();
		world.setDelta(delta);
	}

	void Game::render()
	{
		renderSystem->process();
	}

	void Game::shutdown()
	{
		
	}
}