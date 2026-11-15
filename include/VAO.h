#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include <utility>
#include <cstddef>
#include"VBO.h"

class VAO{
public:
	GLuint ID;

	VAO();
	~VAO(){ Delete(); }

	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;
	VAO(VAO&& o) noexcept : ID(std::exchange(o.ID, 0)) {}
	VAO& operator=(VAO&& o) noexcept {
		if(this != &o){ Delete(); ID = std::exchange(o.ID, 0); }
		return *this;
	}

	void LinkVBO(VBO& VBO, GLuint layout);
	
	void Create();
	void LinkAttrib(VBO& vbo, GLuint layout, GLint components,
	                GLenum type, GLsizei stride, size_t offset);
	void Bind();
	void Unbind();
	void Delete();
};
#endif