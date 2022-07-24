#include "ShaderRender.h"

#include <iostream>


namespace Renderer
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if (!CreateShaderProgram(GL_VERTEX_SHADER, vertexShader, vertexShaderID))
        {
            std::cerr << "Cant create vertex shader" << std::endl;
            return;
        }

        GLuint fragmentShaderID;

        if (!CreateShaderProgram(GL_FRAGMENT_SHADER, fragmentShader, fragmentShaderID))
        {
            glDeleteShader(vertexShaderID);
            std::cerr << "Cant create fragment shader" << std::endl;
            return;
        }

        ID = glCreateProgram();
        glAttachShader(ID, vertexShaderID);
        glAttachShader(ID, fragmentShaderID);
        glLinkProgram(ID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        GLint success;

        glGetProgramiv(ID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            is_compiled = false;
            GLchar errLog[1024];
            glGetProgramInfoLog(ID, 1024, nullptr, errLog);
            std::cerr << "ERROR program: Compile time error\n" << errLog << std::endl;
        }
        else
        {
            is_compiled = true;
        }
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        ID = shaderProgram.ID;
        is_compiled = shaderProgram.is_compiled;

        shaderProgram.ID = NULL;
        shaderProgram.is_compiled = false;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(ID);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        // TODO: insert return statement here
        glDeleteProgram(ID);
        ID = shaderProgram.ID;
        is_compiled = shaderProgram.is_compiled;

        shaderProgram.ID = NULL;
        shaderProgram.is_compiled = false;

        return *this;
    }

    void ShaderProgram::Use()
    {
        glUseProgram(ID);
    }

    void ShaderProgram::SetIn(const std::string& name, const GLint value)
    {
    }

    bool ShaderProgram::CreateShaderProgram(const GLenum& shaderType, const std::string& source_shader, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* source_code = source_shader.c_str();
        glShaderSource(shaderID, 1, &source_code, nullptr);
        glCompileShader(shaderID);


        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLchar errLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, errLog);
            std::cerr << "ERROR shader: Compile time error\n" << errLog << std::endl;
        }

        return success;
    }
}