#include <header.hpp>

int main(int ac, char **av){
	if (ac != 2){
		std::cout << "incorrect number of arguments" << std::endl;
		return -1;
	}
	// Parser parser = Parser(av[1]);
	Window window = Window("scop");
	Shader shader = Shader("shaders/default");
	// Input input = Input();
	// Texture texture = Texture("42srcs/poney.jpg");
	shader.use();
	// Vertex vertex = Vertex(parser.getVertex(), parser.getIndices());
	// shader->setBool("isColor", true);
	while(window.shouldLoop()){
		window.clear();
		shader->setBool("iscolor", input->getIsColor());
		shader->setMat4("model", input->createTransform());
	// 	vertex.drawElement();
	// 	input.checkInput(window.getWindow());
		window.swapBufferAndPollEvent();
	}
	return 0;
}