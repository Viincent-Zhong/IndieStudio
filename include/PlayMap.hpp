/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** Map
*/

#ifndef PLAYMAP_HPP_
#define PLAYMAP_HPP_

#include "Display.hpp"
#include "Map/Map.hpp"
#include "Element/Element.hpp"
#include "Sound/Sound.hpp"

class PlayMap {
    public:
        enum Directions {
            NORTH = 1,
            WEST = 2,
            SOUTH = 4,
            EST = 8,
            UNKNOWN = 0
        };
        
        enum CellState {
            SPACE,
            WALL,
            BLOCK,
            PLAYER,
            BOMB,
            POWERUP,
            UNDEFINED
        };
        
        enum PowerUp {
            RANGE,
            BOMBMAX,
            SPEED,
            NO
        };
        PlayMap();
        ~PlayMap();
        void destroyMap();
        void defaultMap(RaylibMap::Map &map);
        void setBonus(const bool bonus);
        void constructPlayMap(IndieStudio::IGraphical &lib, RaylibMap::Map &map);
        void constructBlocks(RaylibMap::Map &map);
        void changeCell(std::pair<int, int> const &pos, CellState value);
        std::pair<int, int> posIntoMapPos(std::pair<float, float> const &pos);
        std::pair<float, float> mapPosIntoPos(std::pair<int, int> const &mapPos);
        CellState getCellState(std::pair<int, int> const &pos);
        std::vector<std::pair<float, float>> getSpawnPoints();
        void drawMap(IndieStudio::IGraphical &lib) const;
        bool collisionBlocks(RaylibElement::Element &element);
        PowerUp collisionPowerUp(RaylibElement::Element &element);
        bool destroyBlocks(std::pair<int, int> const &blockPos);
        void insertBlock(int index, std::pair<int, int> const &pos);
        std::map<std::pair<int, int>, RaylibElement::Element> const &getBlocks();
        std::map<std::pair<int, int>, std::pair<PowerUp, RaylibElement::Element>> const &getPowerUps();
        void insertPowerUp(std::pair<int, int> const &blockPos, PowerUp const &type);
        std::pair<int, int> getMapSize() const;
        std::vector<std::vector<PlayMap::CellState>> getMap() const;

    private:
        std::map<std::pair<int, int>, RaylibElement::Element> _blocks;
        std::map<std::pair<int, int>, std::pair<PowerUp, RaylibElement::Element>> _powerUps;
        std::vector<std::vector<CellState>> _map;
        std::pair<int, int> _blockSize;
        std::pair<int, int> _mapSize;
        std::pair<float, float> _mapOffset;
        bool _bonus = true;
        void spawnPowerUp(std::pair<int, int> const &blockPos);
        RaylibSound::MySound _powerUp;
        RaylibSound::MySound _destroyBox;
};

#endif /* !PLAYMAP_HPP_ */
