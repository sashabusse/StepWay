#pragma once
#include "Core.h"
#include "Graphics/API/Shader.h"
#include "glad/glad.h"
#include <string>



namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{

			class GLShader : public Graphics::API::Shader
			{
			public:
				GLShader();
				void SetUpFromSource(const std::string& vertexSource, const std::string& fragmentSource) override;
				void SetUpFromFile(const std::string& vertexPath, const std::string& fragment)override;
				void ShutDown() override;

				void SetUniform(const std::string& name, const int val) override;
				void SetUniform(const std::string& name, const float val) override;
				void SetUniform(const std::string& name, const glm::fvec2& val) override;
				void SetUniform(const std::string& name, const glm::fvec3& val) override;
				void SetUniform(const std::string& name, const glm::fvec4& val) override;
				void SetUniform(const std::string& name, const glm::fmat2& val) override;
				void SetUniform(const std::string& name, const glm::fmat3& val) override;
				void SetUniform(const std::string& name, const glm::fmat4& val) override;


				void Bind() override;
				void Unbind() override;

				virtual ~GLShader() {};
			private:
				GLint GetUniformLocation(const std::string& name);
				void Compile(uint shader);
			public:
			private:
				std::unordered_map<std::string, GLint> m_UniformLocations;
				uint m_Program;
			};


		}
	}
}