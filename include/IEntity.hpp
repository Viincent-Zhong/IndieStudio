/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-pierre-alexandre.delgado-arevalo
** File description:
** IEntity
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include "IGraphical.hpp"
#include "PlayMap.hpp"

namespace Entity {
    struct Binding {
        int bomb;
        int right;
        int left;
        int down;
        int up;
        int animation;
        int gamePad;
    };
    enum Event {
        DEATH,
        NOTHING
    };
    enum Category {
        PLAYER,
        AI
    };

    struct Stat {
        int hp;
        int bombRange;
        int bombMax;
        float speed;
    };

    class IEntity {
        public:
            ~IEntity() = default;
            virtual std::string getId() const = 0;
            virtual bool setTextures(IndieStudio::IGraphical &lib, const std::pair<float, float> &pos, std::vector<std::string> const &textures) = 0;
            virtual Event event(IndieStudio::IGraphical &lib, PlayMap &map, const int &event, RaylibMap::Map const &libmap, std::vector<std::unique_ptr<Entity::IEntity>> &entities) = 0;
            virtual void setAnimationFrame(const unsigned int frame) = 0;
            virtual void stopAnimation(IndieStudio::IGraphical &lib) = 0;
            virtual void continueAnimation() = 0;
            virtual void drawEntity(IndieStudio::IGraphical &lib) = 0;
            virtual void destroyEntity(IndieStudio::IGraphical &lib) = 0;
            virtual void setSpeed(const float speed) = 0;
            virtual void setSize(IndieStudio::IGraphical &lib, const float x, const float y, const float z) = 0;
            virtual void setRotation(IndieStudio::IGraphical &lib, const float rotation, const float x, const float y, const float z) = 0;
            virtual const std::pair<float, float> getPosition() const = 0;
            virtual const std::string getOrientation() const = 0;
            virtual void updateTexture(std::string const &path) = 0;
            virtual bool checkCollision(RaylibElement::Element &element) = 0;
            virtual RaylibElement::Element getEntity() const = 0;
            virtual void setBindings(Binding const &binds) = 0;
            virtual void damageEntity() = 0;
            virtual Category getType() const = 0;
            virtual std::string getTexture() const = 0;
            virtual Stat getStat() const = 0;
            virtual void setStat(Stat const &stat) = 0;
            virtual int getNbrBomb() const = 0;
            virtual Entity::Binding const &getBindings() const = 0;
    };
}

#endif /* !ENTITY_HPP_ */
