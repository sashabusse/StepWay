#include "StepWayPCH.h"
#include "GLShader.h"
#include "ErrorHandling.h"
#include "glm/gtc/type_ptr.hpp"
//remove 
#include <iostream>
#include <fstream>



namespace StepWay
{
	namespace Graphics
	{
		namespace OpenGL
		{
			GLShader::GLShader():
				m_Program(NULL)
			{
			}
			void GLShader::SetUpFromSource(const std::string& vertexSource, const std::string& fragmentSource)
			{
				m_Program = glCreateProgram();

				uint vertexShader = ProcessShaderSource(GL_VERTEX_SHADER, vertexSource);
				uint fragmentShader = ProcessShaderSource(GL_FRAGMENT_SHADER, fragmentSource);

				glAttachShader(m_Program, vertexShader);
				glAttachShader(m_Program, fragmentShader);
				GL_CHECK_ERRORS();

				glLinkProgram(m_Program);
				glValidateProgram(m_Program);
				GL_CHECK_ERRORS();

				glDetachShader(m_Program, vertexShader);
				glDetachShader(m_Program, fragmentShader);
				GL_CHECK_ERRORS();

				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);
				GL_CHECK_ERRORS();
			}

			void GLShader::SetUpFromFile(const std::string & vertexPath, const std::string & fragmentPath)
			{
				std::string vertexSource = ReadFile(vertexPath);
				std::string fragmentSource = ReadFile(fragmentPath);
				SetUpFromSource(vertexSource, fragmentSource);
			}
			
			GLint GLShader::GetUniformLocation(const std::string& name)
			{
				auto iter = m_UniformLocations.find(name);
				if (iter != m_UniformLocations.end())
					return iter->second;
				GLint location = glGetUniformLocation(m_Program, name.c_str());
				GL_CHECK_ERRORS();
				m_UniformLocations[name] = location;
				return location;
			}

			void GLShader::Compile(uint shader)
			{
				glCompileShader(shader);

				GLint result;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
				if (result == GL_FALSE)
				{
					GLint length;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
					char* error = new char[length + 1];
					glGetShaderInfoLog(shader, length, &length, &error[0]);
					glDeleteShader(shader);
					SW_CORE_ASSERT(false, error);
				}
				GL_CHECK_ERRORS();
			}

			uint GLShader::ProcessShaderSource(GLenum shader_type, const std::string& source)
			{
				uint shader = glCreateShader(shader_type);
				GL_CHECK_ERRORS();

				const char* tmpS = source.c_str();
				glShaderSource(shader, 1, &(tmpS), NULL);
				GL_CHECK_ERRORS();
				SW_CORE_TRACE("Compiling vertex shader. Source:\n" + source);
				Compile(shader);
				return shader;
			}

			std::string GLShader::ReadFile(const std::string& filePath)
			{
				std::ifstream file_stream(filePath);

				std::string nextLine;
				std::string text;
				while (std::getline(file_stream, nextLine))
				{
					text += nextLine + "\n";
				}
				return text;
			}

			void GLShader::ShutDown()
			{
				glDeleteProgram(m_Program);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUpAsComputeShader(const std::string& filePath)
			{
				std::string source = ReadFile(filePath);
				SetUpAsComputeShaderFromSource(source);
			}

			void GLShader::SetUpAsComputeShaderFromSource(const std::string& source)
			{
				m_Program = glCreateProgram();

				uint shader_id = ProcessShaderSource(GL_COMPUTE_SHADER, source);

				glAttachShader(m_Program, shader_id);
				GL_CHECK_ERRORS();

				glLinkProgram(m_Program);
				glValidateProgram(m_Program);
				GL_CHECK_ERRORS();

				glDetachShader(m_Program, shader_id);
				GL_CHECK_ERRORS();

				glDeleteShader(shader_id);
				GL_CHECK_ERRORS();
			}

			//now it's needed to bind before set uniform may be later do it some other way
			void GLShader::SetUniform(const std::string & name, const int val)
			{
				Bind();
				glUniform1i(GetUniformLocation(name), val);
				GL_CHECK_ERRORS()
			}

			void GLShader::SetUniform(const std::string & name, const float val)
			{
				Bind();
				glUniform1f(GetUniformLocation(name), val);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec2 & val)
			{
				Bind();
				glUniform2f(GetUniformLocation(name), val.x, val.y);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec3 & val)
			{
				Bind();
				glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec4 & val)
			{
				Bind();
				glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat2 & val)
			{
				Bind();
				glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(val));
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat3 & val)
			{
				Bind();
				glUniformMatrix3fv(GetUniformLocation(name), 1, false, glm::value_ptr(val));
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat4 & val)
			{
				Bind();
				GLint res = GetUniformLocation(name);
				GL_CHECK_ERRORS();
				glUniformMatrix4fv(res, 1, false, glm::value_ptr(val));
				GL_CHECK_ERRORS();
			}

			void GLShader::Bind()
			{
				glUseProgram(m_Program);
				GL_CHECK_ERRORS()
			}
			void GLShader::Unbind()
			{
				glUseProgram(NULL);
				GL_CHECK_ERRORS()
			}


		}
	}
}