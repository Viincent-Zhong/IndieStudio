/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Text.cpp
*/

#include "Text.hpp"

RaylibText::Text::Text()
{
    _init = false;
}

RaylibText::Text::Text(std::string const &path)
{
    this->_font = LoadFont(path.c_str());
    _init = true;
}

RaylibText::Text::~Text()
{
    if (_init)
        UnloadFont(this->_font);
}

void RaylibText::Text::loadFont(std::string const &path)
{
    this->_font = LoadFont(path.c_str());
    _init = true;
}

void RaylibText::Text::printText(std::string const &text, std::pair<float, float> const &pos, Color const color, const unsigned int size) const
{
    const unsigned int spacing = 4;
    Vector2 textPos;
    textPos.x = pos.first;
    textPos.y = pos.second;
    DrawTextEx(this->_font, text.c_str(), textPos, this->_font.baseSize * size, spacing, color);
}
