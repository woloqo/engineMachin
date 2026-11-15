#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO{
public:
	GLuint ID;

	VBO();
	VBO(GLfloat* vertices, GLsizeiptr size);

	~VBO(){ Delete(); }

	void Create();
	void Bind();
	void Unbind();
	void Delete();
	
	void Update(GLfloat* v, GLsizeiptr size);
};

#endif