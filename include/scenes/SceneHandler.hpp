/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneHandler.hpp
*/

#ifndef SCENEHANDLER_HPP_
#define SCENEHANDLER_HPP_

#include <map>
#include <memory>
#include "IScene.hpp"

#define SCREEN_WIDTH    1900
#define SCREEN_HEIGHT   1000
#define SCREEN_NAME     "BOMBERMAN"
#define FPS             60

class SceneHandler : IndieStudio::IScene {
    public:
        SceneHandler();
        SceneHandler(IndieStudio::IGraphical &lib);
        ~SceneHandler();
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        bool bomberman();

    protected:
    private:
        std::map<IndieStudio::IScene::SceneId, std::unique_ptr<IndieStudio::IScene>> _listScenes;
};

#endif /* !SCENEHANDLER_HPP_ */
