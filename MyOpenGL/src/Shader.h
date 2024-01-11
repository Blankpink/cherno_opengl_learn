#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

struct ShaderProgramSource;

class Shader
{
private:
	unsigned int m_RendererID;
	const std::string m_FilePath;
	//caching for uniforms
	mutable std::unordered_map <std::string, GLint> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	//int GetUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	GLint GetUniformLocation(const std::string& name) const;

};