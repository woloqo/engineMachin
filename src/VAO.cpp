#include"../include/VAO.h"

// Constructor that generates a VAO ID
VAO::VAO(){
	glGenVertexArrays(1, &ID);
}

void VAO::Create(){ if(ID == 0) glGenVertexArrays(1, &ID); }

void VAO::LinkAttrib(VBO& vbo, GLuint layout, GLint components, GLenum type, GLsizei stride, size_t offset){
	vbo.Bind();
	glVertexAttribPointer(layout, components, type, GL_FALSE, stride, (void*)offset);
	glEnableVertexAttribArray(layout);
	vbo.Unbind();
}

void VAO::Bind(){
	glBindVertexArray(ID);
}

void VAO::Unbind(){
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete(){
	if(ID != 0){ glDeleteVertexArrays(1, &ID); ID = 0; }
}