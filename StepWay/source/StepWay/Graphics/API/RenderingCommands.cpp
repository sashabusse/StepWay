#include "StepWayPCH.h"
#include "RenderingCommands.h"


#include "glad/glad.h"


namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{

			std::unique_ptr<RenderingAPI> RenderingCommands::m_API;

			void Renderer::BeginScene(glm::mat4& projection, glm::mat4& cam_transform)
			{
				m_view_projection = projection * glm::inverse(cam_transform);
				m_shader->Bind();
			}

		}
	}
}