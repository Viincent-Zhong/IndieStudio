/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneGame.cpp
*/

#include <iostream>
#include <string.h>
#include "SceneGame.hpp"
#include "Player.hpp"
#include "IA.hpp"
#include "Error.hpp"
#include "IOBinary.hpp"

static IndieStudio::messageParams readSelectedOptions()
{
    IndieStudio::messageParams options = {0};

    try {
        options = IOBinary::readFile<IndieStudio::messageParams>(".gameoption.dat");
        remove(".gameoption.dat");
    } catch (const FileIOError &e) {
        std::cerr << e.what() << std::endl;
    }
    return options;
}

void SceneGame::updateInfo(infoPlayer &info)
{
    if (info.dead)
        return;
    for (auto &player : _players) {
        if (player->getId() == info.names) {
            info.bombMax = player->getStat().bombMax;
            info.nbrBomb = player->getStat().bombMax - player->getNbrBomb();
            info.life = player->getStat().hp;
            return;
        }
    }
    info.icons.get()->create("assets/image/none.png");
    info.nbrBomb = -1;
    info.bombMax = 0;
    info.life = 0;
    info.dead = true;
}

static const std::vector<std::pair<float, float>> presetIcon = {{0.0f, 0.0f}, {0.0f, 840.0f}, {1700.0f, 0.0f}, {1700.0f, 840.0f}};
static const std::vector<std::pair<float, float>> presetName = {{200.0f, 40.0f}, {200.0f, 900.0f}, {1550.0f, 40.0f}, {1550.0f, 900.0f}};
static const std::vector<std::pair<float, float>> presetBomb = {{200.0f, 60.0f}, {200.0f, 920.0f}, {1550.0f, 60.0f}, {1550.0f, 920.0f}};
static const std::vector<std::pair<float, float>> presetLife = {{200.0f, 80.0f}, {200.0f, 940.0f}, {1550.0f, 80.0f}, {1550.0f, 940.0f}};

void SceneGame::infoPlayers()
{
    int i = 0;

    for (auto it = _infoPlayers.begin(); it != _infoPlayers.end(); ++it, ++i) {
        updateInfo(*it);
        it->icons.get()->display(presetIcon.at(i), 1.0f);
        _text.printText(it->names, presetName.at(i), BLUE, 2.0f);
        _text.printText("Bomb: " + std::to_string(it->nbrBomb) + "/" + std::to_string(it->bombMax), presetBomb.at(i), BLUE, 2.0f);
        _text.printText("Life: " + std::to_string(it->life), presetLife.at(i), BLUE, 2.0f);
    }
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneGame::run(IndieStudio::IGraphical &lib)
{
    if (!this->initGame(lib))
        return {END, true};

    while (this->_nbPlayers != 0 && this->_players.size() > 1) {
        if (lib.endGame() || _gamepad.isPadKeyReleased(0, PAD_B))
            return {END, true};
        if (_event.getKeyInput() == KEY_ENTER || _gamepad.isPadKeyReleased(0, PAD_SELECT))
            return {PAUSE, true};
        _music.updateMusicStream();
        lib.startDrawing(true);
        lib.start3d();
        this->sceneEvent(lib);
        _visualMap.drawMap();
        this->_map.drawMap(lib);
        lib.end3d();
        infoPlayers();
        lib.endDrawing();
    }
    return endGame();
}

void SceneGame::initScene()
{
    this->_init = true;
}

void SceneGame::destroyGame()
{
    for (auto it = this->_players.begin(); it != this->_players.end();) {
        it = this->_players.erase(it);
    }
    for (auto it = this->_playerCopy.begin(); it != this->_playerCopy.end();)
        it = this->_playerCopy.erase(it);
    for (auto it = this->_infoPlayers.begin(); it != this->_infoPlayers.end();)
        it = this->_infoPlayers.erase(it);
    this->_map.destroyMap();
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneGame::endGame()
{
    IndieStudio::recapParams recap = {0};
    int i = 0;

    recap.nbrPlayers = this->_maxNbPlayers;
    for (auto it : this->_playerCopy) {
        if (i >= _maxNbPlayers + 1)
            break;
        strcat(recap.players[i].playerName, it.name);
        strcat(recap.players[i].playerTexture , it.texture);
        ++i;
    }
    if (this->_nbPlayers == 0)
        recap.winner = 1;
    if (this->_players.size() == 1) {
        auto lastPlayerId = this->_players.back().get()->getId();
        i = 0;
        for (auto it : _playerCopy) {
            if (it.name == lastPlayerId) {
                recap.winner = i;
                break;
            }
            ++i;
        }
    }
    if (this->_players.size() == 0)
        recap.winner = -1;
    IOBinary::writeFile<IndieStudio::recapParams>(recap, ".recap.dat");
    return {RECAP, true};
}

void SceneGame::sceneEvent(IndieStudio::IGraphical &lib)
{
    _music.updateMusicStream();
    try
    {
        for (auto it = this->_players.begin(); it != this->_players.end();) {
            if (it->get()->event(lib, this->_map, 0, _visualMap, this->_players) == Entity::DEATH) {
                if (it->get()->getType() == Entity::Category::PLAYER)
                    _nbPlayers--;
                it = this->_players.erase(it);
                continue;
            }
            it->get()->drawEntity(lib);
            ++it;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool SceneGame::initGame(IndieStudio::IGraphical &lib)
{
    if (lib.getSave()) {
        saveGame();
        saveMap();
        lib.setSave(false);
        return false;
    }
    _music.initMusic("assets/music/game_three.mp3", lib.getMusicVolume());
    if (!_init)
        return true;
    this->destroyGame();
    if (lib.getLoad()) {
        try {
            readSaveMap(lib);
            readSaveGame(lib);
        } catch (const FileIOError &error) {
            this->_visualMap.initMap("assets/model/map/cubicmap_1.png", "assets/texture/map/cubicmap_atlas_mc.png");
            this->setupGame(lib, _visualMap, {0});
        }
        lib.setLoadGame(false);
        _init = false;
    } else if (_init) {
        IndieStudio::messageParams options = readSelectedOptions();
        this->_visualMap.initMap(options.map[0] == 0 ? "assets/model/map/cubicmap_1.png" : options.map,
        "assets/texture/map/cubicmap_atlas_mc.png");
        this->setupGame(lib, _visualMap, options);
    }
    _text.loadFont("assets/fonts/setBack.png");
    for (auto it = _playerCopy.begin(); it != _playerCopy.end(); ++it) {
        _infoPlayers.push_back({false, std::make_unique<RaylibImage::Image>(), it->name, 0, 0, 1});
        _infoPlayers.back().icons.get()->create("assets/image/icon_player.png");
    }
    return true;
}