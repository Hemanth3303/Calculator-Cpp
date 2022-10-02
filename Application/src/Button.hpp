#pragma once

#include "raylib.h"

#include <string>

class Button {
public:
	Button(int32_t x, int32_t y, std::string name);
	~Button();

	void onClick();
	std::string onRelease();
	void render();

	inline const int32_t getX() const { return m_Xpos; }
	inline const int32_t getY() const { return m_Ypos; }
	inline const int32_t getSize() const { return m_Size; }

	inline const std::string_view getName() const { return m_Name; }

private:
	int32_t m_Xpos, m_Ypos;
	int32_t m_Size = 80;
	std::string m_Name;
	Color m_Color;
};