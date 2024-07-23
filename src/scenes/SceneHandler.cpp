/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneHandler.cpp
*/

#include "SceneHandler.hpp"
#include "SceneGame.hpp"
#include "SceneMenu.hpp"
#include "SceneParams.hpp"
#include "ScenePause.hpp"
#include "SceneSelection.hpp"
#include "SceneRecap.hpp"
#include <iostream>

SceneHandler::SceneHandler(IndieStudio::IGraphical &lib)
{
    this->_listScenes.insert({MENU, std::make_unique<SceneMenu>(SceneMenu(lib))});
    this->_listScenes.insert({GAME, std::make_unique<SceneGame>(SceneGame(lib))});
    this->_listScenes.insert({PARAMS, std::make_unique<SceneParams>(SceneParams(lib))});
    this->_listScenes.insert({PAUSE, std::make_unique<ScenePause>(ScenePause(lib))});
    this->_listScenes.insert({SELECTION, std::make_unique<SceneSelection>(SceneSelection(lib))});
    this->_listScenes.insert({RECAP, std::make_unique<SceneRecap>(SceneRecap(lib))});
}

SceneHandler::SceneHandler()
{
}

SceneHandler::~SceneHandler()
{
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneHandler::run(IndieStudio::IGraphical &lib)
{
    std::pair<IndieStudio::IScene::SceneId, bool> actualScene = this->_listScenes.find(MENU)->second->run(lib);

    while (actualScene.first != END) {
        try {
            auto scene = this->_listScenes.find(actualScene.first);
            if (actualScene.second)
                scene->second->initScene();
            actualScene = scene->second->run(lib);
            // ! en attente de la class erreur
        } catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
            return {ERROR, true};
        }
    }
    return actualScene;
}

void SceneHandler::initScene()
{
}
