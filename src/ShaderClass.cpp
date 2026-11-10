#include "../include/ShaderClass.h"

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void checkCompileErrors(unsigned int shader, std::string type){
	int success;
	char infoLog[1024];
	if (type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout<<"Error al compilar el shader: "<<type<<"\n"<<infoLog<<"\n";
		}
	}
	else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error al linkear el shader: "<<type<<"\n"<<infoLog<<"\n";
		}
	}
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
	
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e){
		std::cout << "Error al leer archivos: "<<e.what()<<"\n";
	}

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	std::cout<<"vertexShader compilado correctamente.\n";

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	std::cout<<"fragmentShader compilado correctamente.\n";

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	checkCompileErrors(ID, "PROGRAM");
	std::cout<<"shaderProgram creado correctamente.\n";

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use(){ 
	glUseProgram(ID); 
}

void Shader::setBool(const std::string &name, bool value) const{         
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const{ 
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const{ 
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::Delete(){
	glDeleteProgram(ID);
}