
#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include <header.hpp>

class Vertex {
	public:
		explicit Vertex(std::vector<float>, std::vector<u_int>);
		~Vertex();

		void drawElement();
	private:

		std::vector<float> _vertex;
		std::vector<u_int> _indices;

		u_int _VAO;
		u_int _VBO;
		u_int _EBO;

};

#endif
