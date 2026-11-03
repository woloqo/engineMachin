#include"../include/VAO.h"

// Constructor that generates a VAO ID
VAO::VAO(){
	glGenVertexArrays(1, &ID);
}

void VAO::LinkVBO(VBO& VBO, GLuint layout){
	VBO.Bind();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	// glEnableVertexAttribArray(1);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	VBO.Unbind();
}

void VAO::Bind(){
	glBindVertexArray(ID);
}

void VAO::Unbind(){
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete(){
	glDeleteVertexArrays(1, &ID);
}