/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** IA
*/

#ifndef IA_HPP_
#define IA_HPP_

#include "Player.hpp"
#include "IGraphical.hpp"
#include "IEntity.hpp"
#include "Element/Element.hpp"
#include "PlayMap.hpp"

namespace Entity {
    struct Actions {
        PlayMap::Directions direction;
        int movement;
    };

    class IA : public Player {
        public:
            IA();
            ~IA();
            Event event(IndieStudio::IGraphical &lib, PlayMap &map, const int &event, RaylibMap::Map const &libmap, std::vector<std::unique_ptr<Entity::IEntity>> &entities) override;
            IA(const IA&) = delete;
            IA(IA&&) = default;
            Category getType() const;
            PlayMap::Directions getRightDirection(PlayMap::Directions direction);
            PlayMap::Directions getOppositeDirection(PlayMap::Directions direction);
            PlayMap::Directions getOppositeDirection(char direction);
            void calculateMovement(int move_to_block);
            void calculateNewMovement(std::pair<int, int> &new_pos, PlayMap::Directions direction);
            void possibleMovement(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos);
            void possibleNewMovement(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos);
            void findPlayer(PlayMap &map, std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> &tmp_pos);
            void algorithmAI(IndieStudio::IGraphical &lib, PlayMap &map, std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> &tmp_pos);
            bool searchBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos, PlayMap::Directions direction);
            bool searchBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> tmp_pos);
            void escapeBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos);

        private:
            char _possible_direction;
            char _dangerous_direction;
            char _direction;
            char _last_direction;
            bool _danger;
            int _movement;
            std::pair<PlayMap::Directions, PlayMap::Directions> _principal_direction;
            std::vector<std::pair<int, int>> _bomb_pos;
            std::pair<int, int> _ia_last_pos;
            std::vector<Actions> _actions;
    };
}

#endif /* !IA_HPP_ */
