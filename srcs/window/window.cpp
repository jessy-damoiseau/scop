#include <window/window.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
		glViewport(0, 0, width, height);
}


Window::Window(const std::string& windowName, int windowHeight, int windowWidth){
	if(!glfwInit())
		std::cout << "glfwInit failed !" << std::endl;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), nullptr, nullptr);
	if (_window == nullptr)
		std::cout << "Failed to create GLFW window" << std::endl;

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		std::cout << "Failed to initialize GLAD" << std::endl;

	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()= default;


bool Window::shouldLoop(){
	if (glfwWindowShouldClose(_window)){
		glfwTerminate();
		return false;
	}
	return true;
}


GLFWwindow * Window::getWindow() const {
	return _window;
}

void Window::clear(){
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
}

void Window::swapBufferAndPollPvent(){
	glfwSwapBuffers(_window);
	glfwPollEvents();
}