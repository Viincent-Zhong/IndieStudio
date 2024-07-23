/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Map.cpp
*/

#include "Map.hpp"

RaylibMap::Map::Map()
{
}

RaylibMap::Map::Map(std::string const &map, std::string const &texture)
{
    Vector3 mapPos;

    _mapImage = map;
    _texturePath = texture;
    mapPos.x = 1.0f;
    mapPos.y = 1.0f;
    mapPos.z = 1.0f;
    _image = LoadImage(map.c_str());
    _cubicmap = LoadTextureFromImage(_image);
    _mesh = GenMeshCubicmap(_image, mapPos);
    _model = LoadModelFromMesh(_mesh);
    _texture = LoadTexture(texture.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _pixels = LoadImageColors(_image);
    _position = { 0.0f - (_cubicmap.width / 2), 0.0f, 0.0f - (_cubicmap.height / 2)};
    UnloadImage(_image);
    _initialised = true;
}

RaylibMap::Map::~Map()
{
    UnloadTexture(_cubicmap);
    UnloadTexture(_texture);
    if (_initialised)
        UnloadModel(_model);
}

void RaylibMap::Map::initMap(std::string const &map, std::string const &texture)
{
    Vector3 mapPos;

    _mapImage = map;
    _texturePath = texture;
    mapPos.x = 1.0f;
    mapPos.y = 1.0f;
    mapPos.z = 1.0f;
    _image = LoadImage(map.c_str());
    _cubicmap = LoadTextureFromImage(_image);
    _mesh = GenMeshCubicmap(_image, mapPos);
    _model = LoadModelFromMesh(_mesh);
    _texture = LoadTexture(texture.c_str());
    _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
    _pixels = LoadImageColors(_image);
    _position = { 0.0f - (_cubicmap.width / 2), 0.0f, 0.0f - (_cubicmap.height / 2)};
    UnloadImage(_image);
    _initialised = true;
}

void RaylibMap::Map::drawMap()
{
    DrawModel(_model, _position, 1.0f, WHITE);
}

Vector3 RaylibMap::Map::getPosition() const
{
    return _position;
}

Texture2D RaylibMap::Map::getTexture() const
{
    return _cubicmap;
}

Color *RaylibMap::Map::getPixels() const
{
    return _pixels;
}

std::string RaylibMap::Map::getMapImage() const
{
    return _mapImage;
}

std::string RaylibMap::Map::getTextureFile() const
{
    return _texturePath;
}