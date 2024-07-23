/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneGame.hpp
*/

#ifndef SCENEGAME_HPP_
#define SCENEGAME_HPP_

#include <memory>
#include "PlayMap.hpp"
#include "IScene.hpp"
#include "IEntity.hpp"
#include "Map/Map.hpp"
#include "Event/Event.hpp"
#include "Music/Music.hpp"
#include "Image/Image.hpp"
#include "Text/Text.hpp"

namespace GameData {
    struct playerMetaData {
        int _totalPlayers;
        int _nbPlayers = 0;
        int _maxNbPlayers = 0;
    };
    struct savePlayer {
        char name[50];
        char texture[50];
        Entity::Stat stats;
        float x;
        float y;
        Entity::Category type;
        Entity::Binding binds;
        bool dead;
    };
};
class SceneGame : public IndieStudio::IScene {
    public:
        SceneGame(IndieStudio::IGraphical &lib);
        SceneGame(SceneGame&&) = default;
        ~SceneGame();
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        void destroyGame();
        std::pair<IndieStudio::IScene::SceneId, bool> endGame();
        void sceneEvent(IndieStudio::IGraphical &lib);
        bool initGame(IndieStudio::IGraphical &lib);
        void saveGame();
        void readSaveGame(IndieStudio::IGraphical &lib);

    protected:
    private:
        struct infoPlayer {
            bool dead;
            std::unique_ptr<RaylibImage::Image> icons;
            std::string names;
            int nbrBomb;
            int bombMax;
            int life;
        };
        void saveMap();
        void readSaveMap(IndieStudio::IGraphical &lib);
        void infoPlayers();
        void createPlayers(IndieStudio::IGraphical &lib, IndieStudio::messageParams const &options, std::vector<std::pair<float, float>> const &pos);
        void createAi(IndieStudio::IGraphical &lib, IndieStudio::messageParams const &options, std::vector<std::pair<float, float>> const &pos);
        void isAlive(const unsigned int i);
        void updateInfo(infoPlayer &info);
        void setupGame(IndieStudio::IGraphical &lib, RaylibMap::Map &map, IndieStudio::messageParams const &options);
        template <typename T>
        void addPlayer(IndieStudio::IGraphical &lib, std::pair<float, float> const &pos, const std::vector<std::string> &textures, std::pair<float, float> const &speed);

        std::vector<std::unique_ptr<Entity::IEntity>> _players;
        std::vector<std::pair<std::string, std::string>> _playersStat;
        std::vector<GameData::savePlayer> _playerCopy;
        PlayMap _map;
        RaylibEvent::Event _event;
        RaylibMusic::MusicA _music;
        bool _init = true;
        RaylibMap::Map _visualMap;
        int _nbPlayers = 0;
        int _maxNbPlayers = 0;
        std::pair<std::string, std::string> _playersId;
        std::vector<infoPlayer> _infoPlayers;
        RaylibText::Text _text;
        RaylibGamePad::GamePad _gamepad;
};

#endif /* !SCENEGAME_HPP_ */
