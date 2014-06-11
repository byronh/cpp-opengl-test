#pragma once

#include "../core/Core.h"
#include "../components/RenderComponent.h"

#include <Artemis/Artemis.h>

#define NUM_INSTANCES 6

namespace astro
{
	
	class Camera;
	class Model;
	class Program;

	class RenderSystem : public artemis::EntityProcessingSystem
	{

		public:
			
			RenderSystem();
			~RenderSystem();

			virtual void initialize();
			virtual void begin();
			virtual void processEntity(artemis::Entity & e);
			virtual void end();

		private:
			
			Camera * _camera;
			Program * _program;
			Model * _model;

			Matrix4f worldMatrices[NUM_INSTANCES];
			Matrix4f modelViewProjectionMatrices[NUM_INSTANCES];
			
			artemis::ComponentMapper<RenderComponent> _renderMapper;

	};

}