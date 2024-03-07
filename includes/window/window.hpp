#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <header.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 920

class Window {
	public:
		explicit Window(const std::string&, int = WINDOW_HEIGHT, int = WINDOW_WIDTH);
		~Window();

		bool shouldLoop();
		void clear();
		void swapBufferAndPollEvent();
		[[nodiscard]] GLFWwindow * getWindow() const;

	private:
		GLFWwindow *_window;
		
};




#endif