#include <vertexArray/vertexArray.hpp>

Vertex::Vertex(std::vector<float> vertex, std::vector<u_int> indices) : _vertex(vertex), _indices(indices){
	glGenVertexArrays(1, &_VAO); 
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);
	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(_vertex.size() * sizeof(_vertex[0])), _vertex.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLsizeiptr(_indices.size() * sizeof(_indices[0])), _indices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
}

Vertex::~Vertex(){
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteBuffers(1, &_EBO);
}

void Vertex::drawElement(){
	glBindVertexArray(_VAO);
	glDisable(GL_BLEND);
	glDrawElements(GL_TRIANGLES, int(_indices.size()), GL_UNSIGNED_INT, nullptr);
}
