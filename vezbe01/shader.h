#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {

public:
	unsigned int ID;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
