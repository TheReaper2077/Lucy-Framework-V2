#include <LucyGL/Shader.h>

#include <glad/glad.h>
#include <assert.h>

#ifndef SHADER_TEXTUREARRAY
#define SHADER_TEXTUREARRAY "u_texturearray"
#endif

#ifndef SHADER_TEXTURES
#define SHADER_TEXTURES "u_textures"
#endif

#ifndef SHADER_LIGHT
#define SHADER_LIGHT
#endif

#include <fstream>
#include <iostream>

static std::string read_file(const std::string &filename) {
	std::string line, text;
	std::fstream file(filename);

	while (std::getline(file, line)) text += (line + '\n');

	file.close();

	return text;
}

// extern std::shared_ptr<OpenGLContext> gl_context;

void Compile(unsigned int &program, const std::string &filename, unsigned int target, bool file) {
	unsigned int shader = glCreateShader(target);
	std::string text;
	if (file) text = read_file(filename);
	else text = filename;
	const char* src = text.c_str();
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	unsigned int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, (GLint*)&result);

	if (!result) {
		unsigned int logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, (GLint*)&logLength);
		GLchar* message = (GLchar*)alloca(logLength*sizeof(char));
		glGetShaderInfoLog(shader, logLength, (GLsizei*)&logLength, message);
		std::cout << message << std::endl;
	}

	assert(result);

	glAttachShader(program, shader);
	glDeleteShader(shader);
};

lgl::Shader::~Shader() {
	glDeleteProgram(program);
}

lgl::Shader::Shader(std::string name, const std::string &vs_filename, const std::string &fs_filename, bool file) {
	program = glCreateProgram();

	Compile(program, vs_filename, GL_VERTEX_SHADER, file);
	Compile(program, fs_filename, GL_FRAGMENT_SHADER, file);

	glLinkProgram(program);

	this->name = name;

	this->Bind();

	if (this->GetUniformLoc(SHADER_TEXTUREARRAY)) {
		this->texture_array = true;

		// for (int i = 0; i < 32; i++) {
		// 	glActiveTexture(GL_TEXTURE0 + i);
		// 	auto tmp = std::string(SHADER_TEXTUREARRAY) + std::to_string(i);
		// 	Shader_SetUniformi(this, tmp, i);
		// }
		glActiveTexture(GL_TEXTURE0);
		this->SetUniformi(SHADER_TEXTUREARRAY, 0);
	}
	if (this->GetUniformLoc(SHADER_TEXTURES)) {
		this->textures = true;
		
		for (int i = 0; i < 32; i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			auto tmp = std::string(SHADER_TEXTURES) + std::to_string(i);
			this->SetUniformi(tmp, i);
		}
	}
	if (this->GetUniformLoc("light")) {
		this->light = true;
	}
	if (this->GetUniformLoc("material")) {
		this->material = true;
	}
}

void lgl::Shader::Bind() {
	glUseProgram(program);
}

void lgl::Shader::UnBind() {
	glUseProgram(0);
}

void lgl::Shader::BindUniformBlock(std::string name, unsigned int index) {
	glUniformBlockBinding(program, glGetUniformBlockIndex(program, name.c_str()), index);
}

unsigned int lgl::Shader::GetUniformLoc(std::string name) {
	if (this->uniform_location_map.find(name) == this->uniform_location_map.end())
		this->uniform_location_map[name] = glGetUniformLocation(program, name.c_str());
		
	return this->uniform_location_map[name];
}

bool lgl::Shader::SetUniformMat4(std::string uniform, const float* matrix) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, matrix);

	return (location > 0);
}

bool lgl::Shader::SetUniformi(std::string uniform, int v0) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniform1i(location, v0);

	return (location > 0);
}

bool lgl::Shader::SetUniformf(std::string uniform, float v0) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniform1f(location, v0);

	return (location > 0);
}

bool lgl::Shader::SetUniformVec3(std::string uniform, const float *v) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniform3fv(location, 1, v);

	return (location > 0);
}

bool lgl::Shader::SetUniformVec4(std::string uniform, const float *v) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniform4fv(location, 1, v);

	return (location > 0);
}

bool lgl::Shader::SetUniformArray(std::string uniform, std::size_t count, const float *v) {
	this->Bind();
	auto location = this->GetUniformLoc(uniform);
	glUniform1fv(location, count, v);

	return (location > 0);
}
