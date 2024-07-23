/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <iostream>
#include "IEntity.hpp"
#include "Element/Element.hpp"
#include "GamePad/GamePad.hpp"
#include "Event/Event.hpp"
#include "Bomb.hpp"

namespace Entity {
    class Player : public IEntity {
        public:
            Player();
            ~Player();
            Player(const Player&) = delete;
            Player(Player&&) = default;
            std::string getId() const;
            bool setTextures(IndieStudio::IGraphical &lib, const std::pair<float, float> &pos, std::vector<std::string> const &textures);
            Event event(IndieStudio::IGraphical &lib, PlayMap &map, const int &event, RaylibMap::Map const &libmap, std::vector<std::unique_ptr<Entity::IEntity>> &entities);
            void setAnimationFrame(const unsigned int frame);
            void stopAnimation(IndieStudio::IGraphical &lib);
            void continueAnimation();
            void drawEntity(IndieStudio::IGraphical &lib);
            void destroyEntity(IndieStudio::IGraphical &lib);
            void setSpeed(const float speed);
            void setSize(IndieStudio::IGraphical &lib, const float x, const float y, const float z);
            void setRotation(IndieStudio::IGraphical &lib, const float rotation, const float x, const float y, const float z);
            const std::pair<float, float> getPosition() const;
            const std::string getOrientation() const;
            void updateTexture(std::string const &path);
            bool checkCollision(RaylibElement::Element &element);
            RaylibElement::Element getEntity() const;
            void setBindings(Binding const &binds);
            Binding const &getBindings() const;
            Category getType() const;
            std::string getTexture() const;
            Stat getStat() const;
            void setStat(Stat const &stat);
            int getNbrBomb() const;

        protected:
            Category _type;
            std::string _id;
            bool _canBeDestroyed;
            int _hp;
            int _nbrBomb;
            int _bombMax;
            int _bombRange;
            int _animeFrame;
            int _animation;
            float _speed;
            bool _dancing;
            std::string _texture;
            std::string _orientation;
            std::pair<float, float> _position;
            RaylibElement::Element _element;
            RaylibEvent::Event _event;
            PlayMap::CellState _lastCell;
            bool movePlayer(RaylibMap::Map const &libmap, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, std::pair<float, float> move);
            void bombEvent(IndieStudio::IGraphical &lib, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities);
            void placeBomb(IndieStudio::IGraphical &lib, PlayMap &map);
            void damageEntity();
            void pickPowerUp(PlayMap &map);
            void dance();
        private:
            RaylibGamePad::GamePad _gamepad;
            Entity::Binding _bindings = {KEY_SPACE, KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_N, 0};
            bool playerMovement(IndieStudio::IGraphical &lib, RaylibMap::Map const &libmap, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities);
            std::vector<std::unique_ptr<Entity::Bomb>> _bomb;
    };
};

#endif /* !PLAYER_HPP_ */
