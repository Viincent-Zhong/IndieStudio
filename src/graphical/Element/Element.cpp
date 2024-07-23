/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Element.cpp
*/

#include "Element.hpp"

RaylibElement::Element::Element() : _animation(0), _init(false)
{
}

RaylibElement::Element::Element(std::string const &elemName, std::pair<float, float> const &pos,
            std::string const &model, std::string const &texture, std::string const &animation)
: _animation(0), _animFrameCounter(0), _animsCount(0), _rotationAngle(0.0f), _color(GREEN), _collision(false), _init(true)
{
    _position = { pos.first, 0.0f, pos.second };
    _size = { 0.5f, 1.0f, 0.5f };
    _rotation = {0.0f, 0.0f, 0.0f};
    _scale = {1.0f, 1.0f, 1.0f};
    _model = LoadModel(model.c_str());
    _texture = LoadTexture(texture.c_str());
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _anims = LoadModelAnimations(animation.c_str(), &_animsCount);
}

RaylibElement::Element::~Element()
{
   // UnloadTexture(_texture);
   // UnloadModel(_model);
}

void RaylibElement::Element::create(std::string const &elemName, std::pair<float, float> const &pos,
            std::string const &model, std::string const &texture, std::string const &animation)
{
    _collision = false;
    _position = { pos.first, 0.0f, pos.second };
    _size = { 0.5f, 1.0f, 0.5f };
    _color = GREEN;
    _rotation = {0.0f, 0.0f, 0.0f};
    _scale = {0.8f, 0.8f, 0.8f};
    _rotationAngle = 0.0f;
    _model = LoadModel(model.c_str());
    _texture = LoadTexture(texture.c_str());
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
    _animsCount = 0;
    _animFrameCounter = 0;
    _anims = LoadModelAnimations(animation.c_str(), &_animsCount);
    _init = true;
}

void RaylibElement::Element::displayAtPos(std::pair<float, float> const &pos)
{
    _position.x = pos.first;
    _position.z = pos.second;
    DrawModelEx(_model, _position, _rotation, _rotationAngle, _scale, WHITE);
}

void RaylibElement::Element::display() const
{
    DrawModelEx(_model, _position, _rotation, _rotationAngle, _scale, WHITE);
}

void RaylibElement::Element::anim()
{
    ++_animFrameCounter;
    UpdateModelAnimation(_model, _anims[_animation], _animFrameCounter);
    if (_animFrameCounter >= _anims[_animation].frameCount)
        _animFrameCounter = 0;
}

bool RaylibElement::Element::move(std::pair<float, float> const &move, RaylibMap::Map const &map)
{
    changeDirection(move);
    _position.x += move.first;
    _position.z += move.second;
    if (_collision || collisionWall(map)) {
        _position.x -= move.first;
        _position.z -= move.second;
        return false;
    }
    return true;
}

void RaylibElement::Element::substractMove(std::pair<float, float> const &move)
{
    this->_position.x -= move.first;
    this->_position.z -= move.second;
}

static void setBox(BoundingBox &box, Vector3 const &pos, Vector3 const &size)
{
    Vector3 vec1;
    Vector3 vec2;

    vec1.x = pos.x - size.x / 2 - 0.15f;
    vec1.y = pos.y - size.y / 2 - 0.15f;
    vec1.z = pos.z - size.z / 2 - 0.15f;
    vec2.x = pos.x + size.x / 2;
    vec2.y = pos.y + size.y / 2;
    vec2.z = pos.z + size.z / 2;
    box.min = vec1;
    box.max = vec2;
}

bool RaylibElement::Element::checkCollision(Element &elem)
{
    BoundingBox box1;
    BoundingBox box2;

    setBox(box1, _position, _size);
    setBox(box2, elem._position, elem._size);
    if (CheckCollisionBoxes(box1, box2)) {
        return true;
    }

    return false;
}

void RaylibElement::Element::changeDirection(std::pair<float, float> const &move)
{
    if (move.first > 0) {
        _rotation = {0.0f, 180.0f, 0.0f};
        _rotationAngle = -180.0f;
    } else if (move.first < 0) {
        _rotation = {0.0f, 0.0f, 0.0f};
        _rotationAngle = 0.0f;
    } else if (move.second > 0) {
        _rotation = {0.0f, 180.0f, 0.0f};
        _rotationAngle = 90.0f;
    } else if (move.second < 0) {
        _rotation = {0.0f, -180.0f, 0.0f};
        _rotationAngle = 90.0f;
    }
}

void RaylibElement::Element::setElemSize(const float x, const float y, const float z)
{
    _scale.x = x;
    _scale.y = y;
    _scale.z = z;
}

void RaylibElement::Element::setElemRotation(const float rotation, const float x, const float y, const float z)
{
    _rotationAngle = rotation;
    _rotation.x = x;
    _rotation.y = y;
    _rotation.z = z;
}

void RaylibElement::Element::updateElemTexture(std::string const &path)
{
    _texture = LoadTexture(path.c_str());
    SetMaterialTexture(&_model.materials[0], MATERIAL_MAP_DIFFUSE, _texture);
}

bool RaylibElement::Element::collisionWall(RaylibMap::Map const &map)
{
    const Vector2 playerPos = { _position.x,  _position.z };
    const float playerRadius = 0.15f;
    Texture2D texture = map.getTexture();
    Vector3 position = map.getPosition();
    Color *pixels = map.getPixels();
    Rectangle rec;

    rec.height = 1.0f;
    rec.width = 1.0f;
    for (int y = 0; y < texture.height; y++)
        for (int x = 0; x < texture.width; x++) {
            rec.x = position.x - 0.5f + x*1.0f;
            rec.y = position.z - 0.5f + y*1.0f;
            if ((pixels[y * texture.width + x].r == 255) &&
                (CheckCollisionCircleRec(playerPos, playerRadius, rec)))
                return true;
        }
    return false;
}

void RaylibElement::Element::setAnimation(unsigned int const &anim)
{
    if (anim <= _anims[0].frameCount) {
        _animFrameCounter = anim;
        UpdateModelAnimation(_model, _anims[0], _animFrameCounter);
    }
}

void RaylibElement::Element::setAnimationModel(const unsigned int id)
{
    _animation = id;
}
