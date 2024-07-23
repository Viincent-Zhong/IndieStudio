/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** Map
*/

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include "PlayMap.hpp"
#include "Map/Map.hpp"

PlayMap::PlayMap() : _mapSize(0, 0), _blockSize(0, 0)
{
}

PlayMap::~PlayMap()
{
}

void PlayMap::destroyMap()
{
    for (auto it = this->_blocks.begin(); it != this->_blocks.end();)
        it = this->_blocks.erase(it);
    for (auto it = this->_map.begin(); it != this->_map.end();)
        it = this->_map.erase(it);
    for (auto it = this->_powerUps.begin(); it != this->_powerUps.end();)
        it = this->_powerUps.erase(it);
}

void PlayMap::constructBlocks(RaylibMap::Map &map)
{
    std::vector<PlayMap::CellState> tmp;
    Color *pixels = map.getPixels();
    Texture2D cubicmap = map.getTexture();

    for (int i = 0, block = 0; i < cubicmap.height; ++i) {
        tmp.clear();
        for (int j = 0; j < cubicmap.width; ++j) {
            if (pixels[j + (i * cubicmap.width)].r == 255)
                tmp.push_back(WALL);
            else {
                if (std::rand() % 2 == 1 || ((i >= 1 && i <= 2 && j >= 1 && j <= 2) || (i <= cubicmap.height - 2 && i >= cubicmap.height - 3 && j <= cubicmap.width - 2 && j >= cubicmap.width - 3)
                || (i >= 1 && i <= 2 && j <= cubicmap.width - 2 && j >= cubicmap.width - 3) || (i <= cubicmap.height - 2 && i >= cubicmap.height - 3 && j >= 1 && j <= 2)))
                    tmp.push_back(SPACE);
                else {
                    tmp.push_back(BLOCK);
                    this->insertBlock(block, {j, i});
                    ++block;
                }
            }
        }
        this->_map.push_back(tmp);
    }
}

void PlayMap::defaultMap(RaylibMap::Map &map)
{
    std::vector<PlayMap::CellState> tmp;
    Color *pixels = map.getPixels();
    Texture2D cubicmap = map.getTexture();

    for (int i = 0, block = 0; i < cubicmap.height; ++i) {
        tmp.clear();
        for (int j = 0; j < cubicmap.width; ++j) {
            if (pixels[j + (i * cubicmap.width)].r == 255)
                tmp.push_back(WALL);
            else
                tmp.push_back(SPACE);
        }
        this->_map.push_back(tmp);
    }
}

void PlayMap::constructPlayMap(IndieStudio::IGraphical &lib, RaylibMap::Map &map)
{
    Texture2D cubicmap = map.getTexture();
    Vector3 mapOffset = map.getPosition();

    _powerUp.create("assets/sound/PowerUp26.wav");
    _powerUp.updateVolume(lib.getEffectLevel());
    _destroyBox.create("assets/sound/destroyBox.wav");
    _destroyBox.updateVolume(lib.getEffectLevel());
    std::srand(std::time(nullptr));
    this->_mapSize = {cubicmap.width, cubicmap.height};
    this->_mapOffset = {mapOffset.x, mapOffset.z};
    this->_blockSize = {1, 1};
}

void PlayMap::changeCell(std::pair<int, int> const &pos, CellState value)
{
    try {
        this->_map.at(pos.second).at(pos.first) = value;
    } catch (std::out_of_range &e) {
        return;
    }
}

std::pair<int, int> PlayMap::posIntoMapPos(std::pair<float, float> const &pos)
{
    std::pair<int, int> res(round(pos.first - _mapOffset.first / this->_blockSize.first), round(pos.second - _mapOffset.second / this->_blockSize.second));
    return res;
}

std::pair<float, float> PlayMap::mapPosIntoPos(std::pair<int, int> const &mapPos)
{
    std::pair<float, float> res(mapPos.first + _mapOffset.first * _blockSize.first, mapPos.second + _mapOffset.second * _blockSize.second);
    return res;
}

PlayMap::CellState PlayMap::getCellState(std::pair<int, int> const &pos)
{
    try {
        return this->_map.at(pos.second).at(pos.first);
    } catch (std::out_of_range &e) {
        return CellState::UNDEFINED;
    }
}

std::vector<std::pair<float, float>> PlayMap::getSpawnPoints()
{
    std::vector<std::pair<float, float>> res;

    res.push_back({1 + _mapOffset.first, 1 + _mapOffset.second}); // en haut gauche
    res.push_back({1 + _mapOffset.first, _mapSize.second - 2 + _mapOffset.second}); // en bas gauche
    res.push_back({_mapSize.first - 2 + _mapOffset.first, _mapSize.second - 2 + _mapOffset.second}); // en bas droite
    res.push_back({_mapSize.first - 2 + _mapOffset.first, 1 + _mapOffset.second}); // en haut droite
    return res;
}

void PlayMap::insertBlock(int index, std::pair<int, int> const &pos)
{
    std::string id("block" + std::to_string(index));

    _blocks.emplace(pos, RaylibElement::Element(id, {(pos.first + _mapOffset.first) / _blockSize.first, (pos.second + _mapOffset.second) / _blockSize.second}, "", "assets/texture/map/wall.png", ""));
}

void PlayMap::drawMap(IndieStudio::IGraphical &lib) const
{
    for (auto it : this->_blocks)
        it.second.display();
    for (auto it : this->_powerUps) {
        it.second.second.anim();
        it.second.second.display();
    }
}

bool PlayMap::collisionBlocks(RaylibElement::Element &element)
{
    for (auto it : this->_blocks)
        if (it.second.checkCollision(element))
            return true;
    return false;
}

bool PlayMap::destroyBlocks(std::pair<int, int> const &blockPos)
{
    auto block = this->_blocks.find(blockPos);

    if (block == this->_blocks.end())
        return false;
    this->changeCell(blockPos, PlayMap::CellState::SPACE);
    if (_bonus)
        spawnPowerUp(blockPos);
    this->_blocks.erase(block);
    _destroyBox.playSound();
    return true;
}

std::vector<std::vector<PlayMap::CellState>> PlayMap::getMap() const
{
    return _map;
}

std::pair<int, int> PlayMap::getMapSize() const
{
    return _mapSize;
}

const std::vector<std::pair<PlayMap::PowerUp, std::string>> powerUpsList = {
    {PlayMap::PowerUp::RANGE, "assets/texture/powerups/range_powerup.png"},
    {PlayMap::PowerUp::BOMBMAX, "assets/texture/powerups/bomb_powerup.png"},
    {PlayMap::PowerUp::SPEED, "assets/texture/powerups/speed_powerup.png"},
};

void PlayMap::spawnPowerUp(std::pair<int, int> const &blockPos)
{
    if (std::rand() % 4 != 1)
        return;
    std::pair<PlayMap::PowerUp, std::string> type = powerUpsList.at(std::rand() % powerUpsList.size());
    std::pair<PowerUp, RaylibElement::Element> newPowerUp(type.first, RaylibElement::Element("pup", {mapPosIntoPos(blockPos)}, "assets/model/bonus.iqm", type.second, "assets/animation/bonus_anim.iqm"));

    this->changeCell(blockPos, PlayMap::CellState::POWERUP);
    this->_powerUps.emplace(blockPos, newPowerUp);
}

void PlayMap::insertPowerUp(std::pair<int, int> const &blockPos, PlayMap::PowerUp const &type)
{
    std::string texture;

    for (auto it : powerUpsList)
        if (it.first == type)
            texture = it.second;
    if (texture.size() == 0)
        texture = "assets/texture/powerups/range_powerup.png";
    std::pair<PowerUp, RaylibElement::Element> newPowerUp(type, RaylibElement::Element("pup", {mapPosIntoPos(blockPos)}, "assets/model/bonus.iqm", texture, "assets/animation/bonus_anim.iqm"));

    this->_powerUps.emplace(blockPos, newPowerUp);
    this->changeCell(blockPos, CellState::POWERUP);
}

PlayMap::PowerUp PlayMap::collisionPowerUp(RaylibElement::Element &element)
{
    PlayMap::PowerUp stock = NO;
    for (auto it = _powerUps.begin(); it != _powerUps.end(); ++it) {
        if (it->second.second.checkCollision(element)) {
            this->changeCell(it->first, PlayMap::CellState::PLAYER);
            _powerUp.playSound();
            stock = it->second.first;
            _powerUps.erase(it);
            return stock;
        }
    }
    return PlayMap::PowerUp::NO;
}

void PlayMap::setBonus(const bool bonus)
{
    _bonus = bonus;
}

std::map<std::pair<int, int>, RaylibElement::Element> const &PlayMap::getBlocks()
{
    return _blocks;
}

std::map<std::pair<int, int>, std::pair<PlayMap::PowerUp, RaylibElement::Element>> const &PlayMap::getPowerUps()
{
    return _powerUps;
}
