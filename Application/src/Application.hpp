#pragma once

#include "raylib.h"

#include "Button.hpp"

#include <string>
#include <vector>
#include <cstdlib>
#include <climits>
#include <iostream>

class Application {
public:
	Application(int32_t winWidth, int32_t winHeight, std::string winTitle);
	~Application();

	void handleEvents();
	void update();
	void render();

	inline const bool& isRunning() const { return m_IsRunning; }

private:
	void eval(const std::string& btnValue);
	void calculate(const std::string& op);

	void handleMouse();
	void handleKeyboard();

private:
	int32_t m_Width, m_Height;
	std::string m_Title, m_DisplayText;
	Rectangle m_DisplayBox;
	bool m_IsRunning;

	std::vector<Button> m_Buttons;

};