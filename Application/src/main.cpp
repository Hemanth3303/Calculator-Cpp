#include "Application.hpp"

int main(int argc, char** argv) {

	Application app(500, 700, "Calculator");

	while (app.isRunning()) {
		app.handleEvents();
		app.update();
		app.render();
	}

	return 0;
}