/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** initGame
*/

#include <iostream>
#include <string.h>
#include "SceneGame.hpp"
#include "Player.hpp"
#include "IA.hpp"
#include "Error.hpp"
#include "IOBinary.hpp"

SceneGame::SceneGame(IndieStudio::IGraphical &lib)
{
}

SceneGame::~SceneGame()
{
}

static GameData::savePlayer getEntitySave(std::unique_ptr<Entity::IEntity> &entity)
{
    GameData::savePlayer save = {0};
    auto pos = entity.get()->getPosition();

    save.x = pos.first;
    save.y = pos.second;
    strcat(save.name, entity.get()->getId().c_str());
    strcat(save.texture, entity.get()->getTexture().c_str());
    save.stats = entity.get()->getStat();
    save.type = entity.get()->getType();
    save.dead = false;
    save.binds = entity.get()->getBindings();
    return save;
}

void SceneGame::saveGame()
{
    WriterSave saver(".saveplayers");
    GameData::playerMetaData metaPlayer = {(int)_playerCopy.size(), _nbPlayers, _maxNbPlayers};
    saver.writeSave<GameData::playerMetaData>(metaPlayer);

    GameData::savePlayer playerSave = {0};
    bool found = false;
    for (auto it = this->_playerCopy.begin(); it != this->_playerCopy.end(); ++it) {
        found = false;
        for (auto p = this->_players.begin(); p != this->_players.end(); ++p)
            if (p->get()->getId().compare(it->name) == 0) {
                found = true;
                playerSave = getEntitySave(*p);
                break;
            }
        if (!found) {
            playerSave = *it;
            playerSave.dead = true;
        }
        saver.writeSave<GameData::savePlayer>(playerSave);
    }
}

void SceneGame::saveMap()
{
    WriterSave saver(".savemap");
    RaylibMap::saveMap visualMapSave = {0};
    strcat(visualMapSave.map, _visualMap.getMapImage().c_str());
    strcat(visualMapSave.texture, _visualMap.getTextureFile().c_str());
    saver.writeSave<RaylibMap::saveMap>(visualMapSave);

    std::map<std::pair<int, int>, RaylibElement::Element> blocksSave = _map.getBlocks();
    saver.writeSave<int>(blocksSave.size());
    for (auto it : blocksSave)
        saver.writeSave<std::pair<int, int>>(it.first);

    std::map<std::pair<int, int>, std::pair<PlayMap::PowerUp, RaylibElement::Element>> powerupSave = _map.getPowerUps();
    saver.writeSave<int>(powerupSave.size());
    for (auto it : powerupSave) {
        saver.writeSave<std::pair<std::pair<int, int>, PlayMap::PowerUp>>({it.first, it.second.first});
    }
}

void SceneGame::readSaveGame(IndieStudio::IGraphical &lib)
{
    ReaderSave reader(".saveplayers");

    GameData::playerMetaData metaPlayer = {0};
    metaPlayer = reader.readSave<GameData::playerMetaData>();
    this->_maxNbPlayers = metaPlayer._maxNbPlayers;
    this->_nbPlayers = metaPlayer._nbPlayers;

    GameData::savePlayer playerSave = {0};
    for (int i = 0; i < metaPlayer._totalPlayers; ++i) {
        playerSave = {0};
        playerSave = reader.readSave<GameData::savePlayer>();
        _playerCopy.push_back(playerSave);
        if (playerSave.dead)
            continue;
        if (playerSave.type == Entity::Category::PLAYER)
            this->addPlayer<Entity::Player>(lib, {playerSave.x, playerSave.y}, {playerSave.name, "assets/model/player/player.iqm", playerSave.texture, "assets/animation/player/player.iqm"}, {20.0f, playerSave.stats.speed});
        else if (playerSave.type == Entity::Category::AI)
            this->addPlayer<Entity::IA>(lib, {playerSave.x, playerSave.y}, {playerSave.name, "assets/model/player/player.iqm", playerSave.texture, "assets/animation/player/player.iqm"}, {20.0f, playerSave.stats.speed});
        if (this->_players.begin() != this->_players.end()) {
            this->_players.begin()->get()->setStat(playerSave.stats);
            this->_players.begin()->get()->setBindings(playerSave.binds);
        }
    }
}

void SceneGame::readSaveMap(IndieStudio::IGraphical &lib)
{
    ReaderSave reader(".savemap");

    RaylibMap::saveMap visualMapSave = {0};

    visualMapSave = reader.readSave<RaylibMap::saveMap>();
    _visualMap.initMap(visualMapSave.map, visualMapSave.texture);
    _map.constructPlayMap(lib, _visualMap);
    _map.defaultMap(_visualMap);
    int nbrBlock = reader.readSave<int>();
    std::pair<int, int> blockPos;
    for (int i = 0; i < nbrBlock; ++i) {
        blockPos = reader.readSave<std::pair<int, int>>();
        _map.insertBlock(i, blockPos);
        _map.changeCell(blockPos, PlayMap::CellState::BLOCK);
    }
    int nbrPowerup = reader.readSave<int>();
    std::pair<std::pair<int, int>, PlayMap::PowerUp> pup;
    for (int i = 0; i < nbrPowerup; ++i) {
        pup = reader.readSave<std::pair<std::pair<int, int>, PlayMap::PowerUp>>();
        _map.insertPowerUp(pup.first, pup.second);
    }
}

template <typename T>
void SceneGame::addPlayer(IndieStudio::IGraphical &lib, std::pair<float, float> const &pos, const std::vector<std::string> &textures,
std::pair<float, float> const &speed)
{
    auto player = this->_players.insert(this->_players.begin(), std::make_unique<T>(T()));

    player->get()->setTextures(lib, pos, textures);
    player->get()->setAnimationFrame(speed.first);
    player->get()->setSpeed(speed.second);
}

void SceneGame::createPlayers(IndieStudio::IGraphical &lib, IndieStudio::messageParams const &options, std::vector<std::pair<float, float>> const &pos)
{
    std::vector<std::string> presetTextures = {"assets/texture/player/red.png", "assets/texture/player/red.png"};
    std::vector<std::string> presetName = {"Player1", "Player2", "Player3", "Player4"};
    std::vector<Entity::Binding> presetBinds = {{KEY_SPACE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_N, 0}, {KEY_Q, KEY_D, KEY_A, KEY_S, KEY_W, KEY_E, 1}, {KEY_T, KEY_J, KEY_G, KEY_H, KEY_Y, KEY_U, 2}, {KEY_I, KEY_SEMICOLON, KEY_K, KEY_L, KEY_O, KEY_P, 3}};

    if (options.playerOneName[0] != 0)
        presetName.at(0) = options.playerOneName;
    if (options.textureOne[0] != 0)
        presetTextures.at(0) = options.textureOne;
    for (int i = 0, end = pos.size(); i < 2 && i < end; ++i) {
        this->addPlayer<Entity::Player>(lib, pos.at(i), {presetName.at(i), "assets/model/player/player.iqm", presetTextures.at(0), "assets/animation/player/player.iqm"}, {20, 0.1f});
        this->_players.begin()->get()->setBindings(presetBinds.at(i));
    }

    if (options.playerTwoName[0] != 0)
        presetName.at(2) = options.playerTwoName;
    if (options.textureTwo[0] != 0)
        presetTextures.at(1) = options.textureTwo;
    for (int i = 2, end = pos.size(); i < end; ++i) {
        this->addPlayer<Entity::Player>(lib, pos.at(i), {presetName.at(i), "assets/model/player/player.iqm", presetTextures.at(1), "assets/animation/player/player.iqm"}, {20, 0.1f});
        this->_players.begin()->get()->setBindings(presetBinds.at(i));
    }
    _nbPlayers = 4;
}

void SceneGame::createAi(IndieStudio::IGraphical &lib, IndieStudio::messageParams const &options, std::vector<std::pair<float, float>> const &pos)
{
    std::string texturePlayer = "assets/texture/player/red.png";
    std::string textureAi = "assets/texture/player/blue.png";
    std::vector<std::string> presetName = {"Player1", "Ia", "Ia2", "Ia3"};

    if (options.playerOneName[0] != 0)
        presetName.at(0) = options.playerOneName;
    if (options.textureOne[0] != 0)
        texturePlayer = options.textureOne;
    this->addPlayer<Entity::Player>(lib, pos.at(0), {presetName.at(0), "assets/model/player/player.iqm", texturePlayer, "assets/animation/player/player.iqm"}, {20, 0.1f});

    if (options.playerTwoName[0] != 0)
        presetName.at(1) = options.playerTwoName;
    if (options.textureTwo[0] != 0)
        textureAi = options.textureTwo;
    if (options.againstAi) {
        for (int i = 1, end = pos.size(); i < end; ++i)
            this->addPlayer<Entity::IA>(lib, pos.at(i), {presetName.at(i), "assets/model/player/player.iqm", textureAi, "assets/animation/player/player.iqm"}, {20, 0.1f});
        _nbPlayers = 1;
    }
}

void SceneGame::setupGame(IndieStudio::IGraphical &lib, RaylibMap::Map &map, IndieStudio::messageParams const &options)
{
    std::vector<std::pair<float, float>> pos;

    this->_map.constructPlayMap(lib, map);
    this->_map.constructBlocks(map);
    pos = this->_map.getSpawnPoints();

    this->_playersId = {options.playerOneName, options.playerTwoName};
    for (auto it : pos)
        this->_map.changeCell(this->_map.posIntoMapPos(it), PlayMap::CellState::PLAYER);
    this->_map.setBonus(options.bonus);

    if (options.againstAi)
        createAi(lib, options, pos);
    else
        createPlayers(lib, options, pos);
    for (auto it = this->_players.begin(); it != this->_players.end(); ++it) {
        this->_playerCopy.insert(_playerCopy.begin(), getEntitySave(*it));
    }
    _maxNbPlayers = 4;
    _init = false;
}
