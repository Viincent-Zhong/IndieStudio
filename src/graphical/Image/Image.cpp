/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Image.cpp
*/

#include "Image.hpp"

RaylibImage::Image::Image()
{
    _init = false;
}

RaylibImage::Image::~Image()
{
    if (_init)
        UnloadTexture(_image);
}

RaylibImage::Image::Image(std::string const &path)
{
    _image = LoadTexture(path.c_str());
    _init = true;
}

void RaylibImage::Image::create(std::string const &path)
{
    _image = LoadTexture(path.c_str());
    _init = true;
}

void RaylibImage::Image::display(std::pair<float, float> const &pos, const float size)
{
    Vector2 vec = {pos.first, pos.second};
    DrawTextureEx(_image, vec, 0.0f, size, WHITE);
}
