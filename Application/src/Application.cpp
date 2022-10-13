#include "Application.hpp"

Application::Application(int32_t winWidth, int32_t winHeight, std::string winTitle)
	:m_Width(winWidth), m_Height(winHeight), m_Title(std::move(winTitle)), m_DisplayText(""), m_IsRunning(true) {
	
	InitWindow(m_Width, m_Height, m_Title.c_str());
	SetTargetFPS(60);

	m_DisplayBox = { 20, 20, 460, 200 };

	//numbers in numpad order
	m_Buttons.emplace_back(20, 280, "7");
	m_Buttons.emplace_back(120, 280, "8");
	m_Buttons.emplace_back(220, 280, "9");
	m_Buttons.emplace_back(20, 380, "4");
	m_Buttons.emplace_back(120, 380, "5");
	m_Buttons.emplace_back(220, 380, "6");
	m_Buttons.emplace_back(20, 480, "1");
	m_Buttons.emplace_back(120, 480, "2");
	m_Buttons.emplace_back(220, 480, "3");

	//zero
	m_Buttons.emplace_back(20, 580, "0");

	//+, - and .
	m_Buttons.emplace_back(120, 580, ".");
	m_Buttons.emplace_back(220, 580, "+");
	m_Buttons.emplace_back(310, 580, "-");

	//Clear, *, / and =
	m_Buttons.emplace_back(310, 280, "C");
	m_Buttons.emplace_back(400, 280, "CE");
	m_Buttons.emplace_back(400, 380, "*");
	m_Buttons.emplace_back(400, 480, "/");
	m_Buttons.emplace_back(400, 580, "=");

}

Application::~Application() {
	CloseWindow();
}

void Application::handleEvents() {
	handleMouse();
	handleKeyboard();
}

void Application::update() {
	if (WindowShouldClose()) {
		m_IsRunning = false;
	}
}

void Application::render() {
	BeginDrawing();
	ClearBackground({ 18, 18, 18, 255 });

	DrawRectangleRec(m_DisplayBox, { 64, 64, 64, 255 });
	DrawText(m_DisplayText.c_str(), static_cast<int32_t>(m_DisplayBox.x) + 10, static_cast<int32_t>(m_DisplayBox.y) + 140, 32, WHITE);

	for (auto& button : m_Buttons) {
		button.render();
	}

	EndDrawing();
}

void Application::eval(const std::string& btnValue) {
	if (btnValue == "CE") {
		m_DisplayText = "";
	}
	else if (btnValue == "C") {
		if (m_DisplayText.length() != 0) {
			m_DisplayText.erase(m_DisplayText.length() - 1);
		}
	}
	else if (btnValue != "=") {
		m_DisplayText += btnValue;
	}
	else if (btnValue == "=") {
		if (m_DisplayText.find("/") != std::string::npos) {
			calculate("/");
		}
		else if (m_DisplayText.find("*") != std::string::npos) {
			calculate("*");
		}
		else if (m_DisplayText.find("+") != std::string::npos) {
			calculate("+");
		}
		else if (m_DisplayText.find("-") != std::string::npos) {
			calculate("-");
		}
	}
}

void Application::calculate(const std::string& op) {
	std::string lstr = m_DisplayText.substr(0, m_DisplayText.find(op));
	std::string rstr = m_DisplayText.substr(m_DisplayText.find(op) + 1, m_DisplayText.length());

	//std::cout << lstr << ", " << op << ", " << rstr << "\n";

	double left = std::atof(lstr.c_str());
	double right = std::atof(rstr.c_str());

	//std::cout << left << ", " << op << ", " << right << "\n";

	double result = INT_MIN;

	if (op == "+") {
		result = left + right;
	}
	else if (op == "-") {
		result = left - right;
	}
	else if (op == "*") {
		result = left * right;
	}
	else if (op == "/") {
		result = right!=0?left/right:INT_MIN;
	}

	m_DisplayText = result!=INT_MIN?std::to_string(result):"MATH ERROR";
}

void Application::handleMouse() {
	for (auto& button : m_Buttons) {
		if (GetMouseX() > button.getX() && GetMouseX() < button.getX() + button.getSize() &&
			GetMouseY() > button.getY() && GetMouseY() < button.getY() + button.getSize()) {
			//std::cout << "collision with button: " << button.getName() << "\n";
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				button.onClick();
			}
			else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				eval(button.onRelease());
			}
		}
	}
}

void Application::handleKeyboard() {
	
}