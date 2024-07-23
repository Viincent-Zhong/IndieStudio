/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-pierre-alexandre.delgado-arevalo
** File description:
** Bomb.cpp
*/
#include "Bomb.hpp"

Entity::Bomb::Bomb()
{
    this->_bombs = "bomb";
    this->_bombPosition = {0.0f, 0.0f};
    this->_bombPositionMap = {0.0f, 0.0f};
    this->LifeTime = 0;
    this->_bombRange = 1;
    _sound.create("assets/sound/explosion.wav");
    _sound.updateVolume(1.0f);
    _laugh.create("assets/sound/laugh.wav");
    _laugh.updateVolume(1.0f);
}

Entity::Bomb::Bomb(IndieStudio::IGraphical &lib, std::pair<float, float> pos, std::string orientation, int range)
{
    this->_bombs = "bomb";
    this->_bombRange = range;
    this->_bombPosition = {0.0f, 0.0f};
    this->_bombPositionMap = {0.0f, 0.0f};
    this->LifeTime = 0;

    this->_bombPosition = pos;
    this->_bombPositionMap = pos;
    this->BombOrientation(pos, orientation);
    _bomb.create(_bombs, this->getBombPosition(), "assets/model/player/bomb.iqm", "assets/texture/player/Bomb.png", "assets/animation/player/player.iqm");
    this->StartTimer();
    _sound.create("assets/sound/explosion.wav");
    _sound.updateVolume(lib.getEffectLevel());
    _laugh.create("assets/sound/laugh.wav");
    _laugh.updateVolume(lib.getEffectLevel());
}

Entity::Bomb::~Bomb()
{}

const std::pair<float, float> Entity::Bomb::getBombPosition() const
{
    return this->_bombPosition;
}

const std::pair<float, float> Entity::Bomb::getBombPositionMap() const
{
    return this->_bombPositionMap;
}

bool Entity::Bomb::setBomb(IndieStudio::IGraphical &lib, std::pair<float, float> pos, std::string orientation)
{
    _sound.updateVolume(lib.getEffectLevel());
    _laugh.updateVolume(lib.getEffectLevel());
    this->_bombPosition = pos;
    this->_bombPositionMap = pos;
    this->BombOrientation(pos, orientation);
    _bomb.create(_bombs, this->getBombPosition(), "assets/model/player/bomb.iqm", "assets/texture/player/Bomb.png", "assets/animation/player/player.iqm");
    return true;
}

void Entity::Bomb::BombOrientation(std::pair<float, float> pos, std::string orientation)
{
    if (orientation == "UP") {
        this->_bombPosition.second += 1;
    }
    else if (orientation == "DOWN") {
        this->_bombPosition.second += 1;
    }
    else if (orientation == "LEFT") {
        this->_bombPosition.second += 1;
    }
    else if (orientation == "RIGHT") {
        this->_bombPosition.second += 1;
    }
}

void Entity::Bomb::drawEntityAtPosition(IndieStudio::IGraphical &lib, std::pair<float, float> const pos)
{
    _bomb.displayAtPos(pos);
}

void Entity::Bomb::drawEntity(IndieStudio::IGraphical &lib)
{
    _bomb.displayAtPos(this->_bombPosition);
}


void Entity::Bomb::StartTimer()
{
    this->LifeTime = 2.0f;
}

void Entity::Bomb::UpdateTimer(IndieStudio::IGraphical &lib)
{
    if (this->LifeTime > 0)
        this->LifeTime -= lib.getFrameTime();
}

bool Entity::Bomb::TimerDone()
{
    if (this->LifeTime <= 0) {
        _sound.playSound();
        return this->LifeTime <= 0;
    }
    return false;
}

bool Entity::Bomb::bombCollision(RaylibElement::Element &element)
{
    return element.checkCollision(_bomb);
}

bool Entity::Bomb::explodeCell(PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, std::pair<int, int> const &pos)
{
    if (map.destroyBlocks(pos))
        return true;
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (map.posIntoMapPos(it->get()->getPosition()) == pos) {
            _laugh.playSound();
            it->get()->damageEntity();
        }
    }
    return false;
}

void displayExplosion(PlayMap &map, std::pair<int, int> epicenter, std::pair<int, int> horizontalBar, std::pair<int, int> verticalBar, std::pair<int, int> explosionSize)
{
    RaylibElement::Element _explosion;

    _explosion.create("explosion", epicenter, "", "assets/texture/player/explosion_bomb.png", "");
    for (int i = 0; i < explosionSize.first; verticalBar.second++) {
        _explosion.displayAtPos({verticalBar.first, verticalBar.second});
        i++;
    }
    for (int i = 0; i < explosionSize.second; horizontalBar.first++) {
        _explosion.displayAtPos({horizontalBar.first, horizontalBar.second});
        i++;
    }
}

void Entity::Bomb::explodeBomb(PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, IndieStudio::IGraphical &lib)
{
    std::pair<int, int> epicenter = map.posIntoMapPos(this->_bombPositionMap);
    PlayMap::CellState state;
    std::pair<int, int> explosionSize = {1, 1};
    std::pair<int, int> verticalBar = epicenter;
    std::pair<int, int> horizontalBar = epicenter;
    int i = 0;

    explodeCell(map, entities, epicenter);
    for (std::pair<int, int> tmp = epicenter; i < this->_bombRange; ++i, ++explosionSize.second) {
        tmp.first--;
        state = map.getCellState(tmp);
        if (state == PlayMap::CellState::WALL || state == PlayMap::CellState::UNDEFINED)
            break;
        if (explodeCell(map, entities, tmp)) {
            break;
        }
    }
    horizontalBar.first -= i;
    i = 0;
    for (std::pair<int, int> tmp = epicenter; i < this->_bombRange; ++i, ++explosionSize.second) {
        tmp.first++;
        state = map.getCellState(tmp);
        if (state == PlayMap::CellState::WALL || state == PlayMap::CellState::UNDEFINED)
            break;
        if (explodeCell(map, entities, tmp)) {
            break;
        }
    }
    i = 0;
    for (std::pair<int, int> tmp = epicenter; i < this->_bombRange; ++i, ++explosionSize.first) {
        tmp.second--;
        state = map.getCellState(tmp);
        if (state == PlayMap::CellState::WALL || state == PlayMap::CellState::UNDEFINED)
            break;
        if (explodeCell(map, entities, tmp)) {
            break;
        }
    }
    verticalBar.second -= i;
    i = 0;
    for (std::pair<int, int> tmp = epicenter; i < this->_bombRange; ++i, ++explosionSize.first) {
        tmp.second++;
        state = map.getCellState(tmp);
        if (state == PlayMap::CellState::WALL || state == PlayMap::CellState::UNDEFINED)
            break;
        if (explodeCell(map, entities, tmp)) {
            break;
        }
    }
    displayExplosion(map, epicenter, map.mapPosIntoPos(horizontalBar), map.mapPosIntoPos(verticalBar), explosionSize);
}
