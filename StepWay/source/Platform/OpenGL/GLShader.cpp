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
				std::ifstream SourceFile(vertexPath);

				std::string nextLine;
				std::string vertexSource;
				while (std::getline(SourceFile, nextLine))
				{ 
					vertexSource += nextLine + "\n";
				}
				
				SourceFile = std::ifstream(fragmentPath);
				std::string fragmentSource;
				while (std::getline(SourceFile, nextLine))
				{
					fragmentSource += nextLine + "\n";
				}
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
			}

			void GLShader::ShutDown()
			{
				glDeleteProgram(m_Program);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const int val)
			{
				glUniform1i(GetUniformLocation(name), val);
				GL_CHECK_ERRORS()
			}
			void GLShader::SetUniform(const std::string & name, const float val)
			{
				glUniform1f(GetUniformLocation(name), val);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec2 & val)
			{
				glUniform2f(GetUniformLocation(name), val.x, val.y);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec3 & val)
			{
				glUniform3f(GetUniformLocation(name), val.x, val.y, val.z);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fvec4 & val)
			{
				glUniform4f(GetUniformLocation(name), val.x, val.y, val.z, val.w);
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat2 & val)
			{
				glUniformMatrix2fv(GetUniformLocation(name), 1, false, glm::value_ptr(val));
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat3 & val)
			{
				glUniformMatrix3fv(GetUniformLocation(name), 1, false, glm::value_ptr(val));
				GL_CHECK_ERRORS();
			}
			void GLShader::SetUniform(const std::string & name, const glm::fmat4 & val)
			{
				glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(val));
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