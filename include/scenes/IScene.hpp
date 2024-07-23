/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "IGraphical.hpp"

/**
 * @brief namespace for indie studio
 * @author Pierre-Alexandre Delgado
 * @version 0.5
 * @date 14/05/2022
 * 
 */
namespace IndieStudio {
    /**
     * @brief
     * 
     * Structure to send to game scene when setting up game options
     */
    struct messageParams {
        bool againstAi;
        bool bonus;
        char map[50];
        char playerOneName[50];
        char playerTwoName[50];
        char textureOne[50];
        char textureTwo[50];
    };
    struct playerRecap {
        char playerName[50];
        char playerTexture[50];
    };
    struct recapParams {
        int winner;
        int nbrPlayers;
        playerRecap players[4];
    };
    /**
     * @brief interface for all scene in indie studio
     * 
     */
    class IScene {
        protected:
            enum SceneId {
                GAME = 1,
                MENU = 2,
                PARAMS = 3,
                PAUSE = 4,
                SELECTION = 5,
                RECAP = 6,
                END = 0,
                ERROR = -1
            };
        public:
            /**
             * @brief Destroy the IScene object
             * 
             */
            virtual ~IScene() = default;
            /**
             * @brief Run the ask scene
             * 
             * @return IndieStudio::IScene::SceneId : ID of the next scene to run
             */
            virtual void initScene() = 0;
            virtual std::pair<IndieStudio::IScene::SceneId, bool> run(IGraphical &lib) = 0;
    };
}

#endif /* !ISCENE_HPP_ */
