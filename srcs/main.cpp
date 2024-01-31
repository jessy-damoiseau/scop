#include <header.hpp>

int main(int ac, char **av){
	if (ac != 2){
		std::cout << "incorrect number of arguments" << std::endl;
		return -1;
	}
	auto *parser = new Parser(av[1]);
	auto *window = new Window("scop");
	auto *shader = new Shader("shaders/default");
	auto *input = new Input();
	auto *texture = new Texture("42srcs/poney.jpg");
	shader->use();
	auto *vertex = new Vertex(parser->getVertex(), parser->getIndices());
	shader->setBool("isColor", true);
	while(window->shouldLoop()){
		window->clear();
		shader->setBool("iscolor", input->getIsColor());
		shader->setMat4("model", input->createTransform());
		vertex->drawElement();
		input->checkInput(window->getWindow());
		window->swapBufferAndPollPvent();
	}
	return 0;
}