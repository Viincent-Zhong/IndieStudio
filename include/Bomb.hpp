/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-pierre-alexandre.delgado-arevalo
** File description:
** Bomb.hpp
*/
#include "IGraphical.hpp"
#include "IEntity.hpp"
#include "Element/Element.hpp"
#include "Image/Image.hpp"
#include "Sound/Sound.hpp"

namespace Entity {
    class Bomb {
        public:
            Bomb();
            Bomb(IndieStudio::IGraphical &lib, std::pair<float, float> pos, std::string orientation, int range);
            ~Bomb();
            bool setBomb(IndieStudio::IGraphical &lib, std::pair<float, float> pos, std::string orientation);
            const std::pair<float, float> getBombPosition() const;
            const std::pair<float, float> getBombPositionMap() const;
            void BombOrientation(std::pair<float, float> pos, std::string orientation);
            void drawEntityAtPosition(IndieStudio::IGraphical &lib, std::pair<float, float> const pos);
            void drawEntity(IndieStudio::IGraphical &lib);
            void StartTimer();
            void UpdateTimer(IndieStudio::IGraphical &lib);
            bool TimerDone();
            bool bombCollision(RaylibElement::Element &element);
            void explodeBomb(PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, IndieStudio::IGraphical &lib);

        private:
            bool explodeCell(PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, std::pair<int, int> const &pos);
            std::string _bombs;
            std::pair<float, float> _bombPosition;
            std::pair<float, float> _bombPositionMap;
            RaylibElement::Element _bomb;
            int _bombRange;
            float LifeTime;
            RaylibSound::MySound _sound;
            RaylibSound::MySound _laugh;
    };
}
