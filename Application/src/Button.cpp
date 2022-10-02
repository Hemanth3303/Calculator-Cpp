#include "Button.hpp"

Button::Button(int32_t x, int32_t y, std::string name) 
	:m_Xpos(x), m_Ypos(y), m_Name(std::move(name)), m_Color({ 128, 128, 128, 255 }) {

}

Button::~Button() {

}

void Button::onClick() {
	m_Color = { 96, 96, 96, 96 };
}

std::string Button::onRelease() {
	m_Color = { 128, 128, 128, 255 };

	return m_Name;
}

void Button::render() {
	DrawRectangle(m_Xpos, m_Ypos, m_Size, m_Size, m_Color);
	DrawText(m_Name.c_str(), static_cast<int32_t>(m_Xpos + m_Size / 2.4), static_cast<int32_t>(m_Ypos + m_Size / 2.8), 24, WHITE);
}