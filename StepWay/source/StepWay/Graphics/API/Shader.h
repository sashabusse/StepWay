#pragma once
#include "Core.h"
#include "Context.h"
#include <string>
#include "glm/glm.hpp"
//Just not written yet

namespace StepWay
{
	namespace Graphics
	{
		namespace API
		{
			
			class Shader
			{
			public:
				virtual void SetUpFromSource(const std::string& vertexSource, const std::string& fragmentSource) = 0;
				//create later ability for some other type of creation
				virtual void SetUpFromFile(const std::string& vertexPath, const std::string& fragmentPath) = 0;
				//virtual void SetUpFromStream(...)
				virtual void ShutDown() = 0;

				virtual void Bind() = 0;
				virtual void Unbind() = 0;

				virtual void SetUniform(const std::string& name, const int val) = 0;
				virtual void SetUniform(const std::string& name, const float val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fvec2& val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fvec3& val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fvec4& val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fmat2& val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fmat3& val) = 0;
				virtual void SetUniform(const std::string& name, const glm::fmat4& val) = 0;

				static Shader* Create(GAPI_TYPE api);
				virtual ~Shader() {};
			private:
			public:
			private:
			};

		}
	}
}
