/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** IA
*/

#include "IA.hpp"

Entity::IA::IA()
{
    _direction = 0;
    this->_canBeDestroyed = true;
    this->_animeFrame = 0;
    this->_speed = 0;
    this->_position = {0.0f, 0.0f};
    this->_lastCell = PlayMap::CellState::SPACE;
    this->_type = AI;
    this->_nbrBomb = 0;
    this->_bombMax = 1;
    this->_hp = 1;
    this->_bombRange = 1;
    _movement = 0;
    _direction = PlayMap::Directions::UNKNOWN;
    _danger = false;
}

Entity::IA::~IA()
{
}

/**
 * @brief function that is the principal intelligence of the AI
 * 
 * @param lib 
 * @param map 
 * @param event 
 * @param libmap 
 * @param entities 
 * @return Entity::Event 
 */

Entity::Event Entity::IA::event(IndieStudio::IGraphical &lib, PlayMap &map, const int &event, RaylibMap::Map const &libmap, std::vector<std::unique_ptr<Entity::IEntity>> &entities)
{
    if (this->_hp <= 0)
        return Entity::DEATH;

    std::pair<float, float> move = {0.0f, 0.0f};
    std::vector<std::vector<PlayMap::CellState>> tmp_map = map.getMap();
    std::pair<int, int> tmp_mapSize = map.getMapSize();
    std::pair<int, int> tmp_pos = map.posIntoMapPos(_position);
    bombEvent(lib, map, entities);

    if (_actions.size() != 0 && !_movement) {
        _direction = _actions.at(0).direction;
        _last_direction = (_direction == _last_direction ? _last_direction : _direction);
        _ia_last_pos = tmp_pos;
        calculateMovement(_actions.at(0).movement);
        _actions.erase(_actions.begin());
    } else if (_bomb_pos.size() != 0 && !_movement) {
        _direction = PlayMap::Directions::UNKNOWN;
        if (tmp_map.at(_bomb_pos.at(0).second).at(_bomb_pos.at(0).first) != PlayMap::CellState::BOMB)
            _bomb_pos.erase(_bomb_pos.begin());
    } else if (!_movement) {
        findPlayer(map, tmp_map, tmp_mapSize, tmp_pos);
        algorithmAI(lib, map, tmp_map, tmp_mapSize, tmp_pos);
    }

    if (_movement) {
        switch (_direction) {
            case PlayMap::Directions::NORTH:
                move.second = -_speed;
                break;

            case PlayMap::Directions::WEST:
                move.first = -_speed;
                break;

            case PlayMap::Directions::SOUTH:
                move.second = _speed;
                break;

            case PlayMap::Directions::EST:
                move.first = _speed;
                break;

            default:
                break;
        }
        --_movement;
    }

    if (_direction == PlayMap::Directions::UNKNOWN || !_movement)
        this->stopAnimation(lib);
    else {
        movePlayer(libmap, map, entities, move);
        this->continueAnimation();
        pickPowerUp(map);
    }
    return Entity::NOTHING;
}

/**
 * @brief return the type of the AI
 * 
 * @return Entity::Category 
 */

Entity::Category Entity::IA::getType() const
{
    return this->_type;
}

/**
 * @brief find the nearest player for the AI and be his principal target
 * 
 * @param map 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 */

void Entity::IA::findPlayer(PlayMap &map, std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> &tmp_pos)
{
    std::pair<int, int> cell_pos = {0, 0};
    std::pair<int, int> closest_p = {250, 250};

    for (std::vector<PlayMap::CellState> tmp : tmp_map) {
        cell_pos.first = 0;
        for (PlayMap::CellState cell : tmp) {
            if (cell == PlayMap::CellState::PLAYER && (abs(closest_p.first - tmp_pos.first) + abs(closest_p.second - tmp_pos.second) >
            abs(cell_pos.first - tmp_pos.first) + abs(cell_pos.second - tmp_pos.second)) && cell_pos != tmp_pos) {
                closest_p = cell_pos;
            }
            ++cell_pos.first;
        }
        ++cell_pos.second;
    }

    std::pair<int, int> directions = {closest_p.first - tmp_pos.first, closest_p.second - tmp_pos.second};

    if (abs(closest_p.first - tmp_pos.first) > abs(closest_p.second - tmp_pos.second))
        _principal_direction = {(closest_p.first - tmp_pos.first > 0 ? PlayMap::Directions::EST : PlayMap::Directions::WEST),
        (closest_p.second - tmp_pos.second > 0 ? PlayMap::Directions::SOUTH : PlayMap::Directions::NORTH)};
    else
        _principal_direction = {(closest_p.second - tmp_pos.second > 0 ? PlayMap::Directions::SOUTH : PlayMap::Directions::NORTH),
        (closest_p.first - tmp_pos.first > 0 ? PlayMap::Directions::EST : PlayMap::Directions::WEST)};
}

/**
 * @brief calculate the new theoric position of the player to run away from the bomb
 * 
 * @param new_pos 
 * @param direction 
 */

void Entity::IA::calculateNewMovement(std::pair<int, int> &new_pos, PlayMap::Directions direction)
{
    switch (direction) {
        case PlayMap::Directions::NORTH:
            new_pos.second += -1;
            break;
        case PlayMap::Directions::SOUTH:
            new_pos.second += 1;
            break;
        case PlayMap::Directions::WEST:
            new_pos.first += -1;
            break;
        case PlayMap::Directions::EST:
            new_pos.first += 1;
            break;
        default:
            break;
    }   
}

/**
 * @brief calculate the movement for the AI to move block to block
 * 
 * @param move_to_block 
 */

void Entity::IA::calculateMovement(int move_to_block)
{
    _movement = (move_to_block) / _speed;
}

/**
 * @brief return the direction on the right 
 * 
 * @param direction 
 * @return PlayMap::Directions 
 */

PlayMap::Directions Entity::IA::getRightDirection(PlayMap::Directions direction)
{
    switch (direction) {
        case PlayMap::Directions::NORTH:
            return PlayMap::Directions::EST;
        case PlayMap::Directions::EST:
            return PlayMap::Directions::SOUTH;
        case PlayMap::Directions::SOUTH:
            return PlayMap::Directions::WEST;
        case PlayMap::Directions::WEST:
            return PlayMap::Directions::NORTH;
        default:
            return PlayMap::Directions::UNKNOWN;
    }   
}

/**
 * @brief return the opposite direction from the given parameter
 * 
 * @param direction 
 * @return PlayMap::Directions 
 */

PlayMap::Directions Entity::IA::getOppositeDirection(PlayMap::Directions direction)
{
    switch (direction) {
        case PlayMap::Directions::NORTH:
            return PlayMap::Directions::SOUTH;
        case PlayMap::Directions::SOUTH:
            return PlayMap::Directions::NORTH;
        case PlayMap::Directions::WEST:
            return PlayMap::Directions::EST;
        case PlayMap::Directions::EST:
            return PlayMap::Directions::WEST;
        default:
            return PlayMap::Directions::SOUTH;
    }
}

/**
 * @brief return the opposite direction from the given parameter
 * 
 * @param direction 
 * @return PlayMap::Directions 
 */

PlayMap::Directions Entity::IA::getOppositeDirection(char direction)
{
    switch (direction) {
        case PlayMap::Directions::NORTH:
            return PlayMap::Directions::SOUTH;
        case PlayMap::Directions::SOUTH:
            return PlayMap::Directions::NORTH;
        case PlayMap::Directions::WEST:
            return PlayMap::Directions::EST;
        case PlayMap::Directions::EST:
            return PlayMap::Directions::WEST;
        default:
            return PlayMap::Directions::UNKNOWN;
    }
}

/**
 * @brief get which Directions the AI can go to run away from his own bomb 
 * 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 */

void Entity::IA::possibleNewMovement(std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos)
{
    _possible_direction = 0;

    if (tmp_pos.first - 1 >= 0 && tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB)
        _possible_direction += PlayMap::Directions::WEST;

    if (tmp_pos.second - 1 >= 0 && tmp_map.at(tmp_pos.second - 1).at(tmp_pos.first) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second - 1).at(tmp_pos.first) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB)
        _possible_direction += PlayMap::Directions::NORTH;

    if (tmp_pos.first + 1 <= tmp_mapSize.first && tmp_map.at(tmp_pos.second).at(tmp_pos.first + 1) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first + 1) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB)
        _possible_direction += PlayMap::Directions::EST;

    if (tmp_pos.second + 1 <= tmp_mapSize.second && tmp_map.at(tmp_pos.second + 1).at(tmp_pos.first) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second + 1).at(tmp_pos.first) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB)
        _possible_direction += PlayMap::Directions::SOUTH;
}

/**
 * @brief get which Directions the AI can go to and the directions that are safe for the AI
 * 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 */

void Entity::IA::possibleMovement(std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos)
{
    _possible_direction = 0;

    if (tmp_pos.first - 1 >= 0 && tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB
    && !searchBomb(tmp_map, tmp_mapSize, {tmp_pos.first -1, tmp_pos.second}, PlayMap::Directions::WEST))
        _possible_direction += PlayMap::Directions::WEST;

    if (tmp_pos.second - 1 >= 0 && tmp_map.at(tmp_pos.second - 1).at(tmp_pos.first) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second - 1).at(tmp_pos.first) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB
    && !searchBomb(tmp_map, tmp_mapSize, {tmp_pos.first, tmp_pos.second -1}, PlayMap::Directions::NORTH))
        _possible_direction += PlayMap::Directions::NORTH;

    if (tmp_pos.first + 1 <= tmp_mapSize.first && tmp_map.at(tmp_pos.second).at(tmp_pos.first + 1) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first + 1) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB
    && !searchBomb(tmp_map, tmp_mapSize, {tmp_pos.first +1, tmp_pos.second}, PlayMap::Directions::EST))
        _possible_direction += PlayMap::Directions::EST;

    if (tmp_pos.second + 1 <= tmp_mapSize.second && tmp_map.at(tmp_pos.second + 1).at(tmp_pos.first) == PlayMap::CellState::SPACE
    || tmp_map.at(tmp_pos.second + 1).at(tmp_pos.first) == PlayMap::CellState::POWERUP
    || tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB
    && !searchBomb(tmp_map, tmp_mapSize, {tmp_pos.first, tmp_pos.second +1}, PlayMap::Directions::SOUTH))
        _possible_direction += PlayMap::Directions::SOUTH;
    
}

/**
 * @brief the main algorithmAI for the AI
 * 
 * @param lib 
 * @param map 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 */

void Entity::IA::algorithmAI(IndieStudio::IGraphical &lib, PlayMap &map, std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> &tmp_pos)
{
    possibleMovement(tmp_map, tmp_mapSize, tmp_pos);
    _dangerous_direction = 0;
    _danger = searchBomb(tmp_map, tmp_pos);

    char tmp = _direction;

    if (_danger) {
        _direction = getOppositeDirection(_direction);
        _last_direction = (tmp != _direction && tmp != PlayMap::Directions::UNKNOWN ? tmp : _last_direction);
        _ia_last_pos = tmp_pos;
        calculateMovement(1);
        return;

    } else if (!(_direction & _possible_direction) || !_movement) {
        if (_principal_direction.first & _possible_direction && !(_principal_direction.first & _dangerous_direction)) {
            _direction = _principal_direction.first & _possible_direction;
            _last_direction = (tmp == _direction && tmp != PlayMap::Directions::UNKNOWN ? _last_direction : tmp);
            _ia_last_pos = tmp_pos;
            calculateMovement(1);
        } else if (_principal_direction.second & _possible_direction && !(_principal_direction.second & _dangerous_direction)) {
            _direction = _principal_direction.second & _possible_direction;
            _last_direction = (tmp == _direction && tmp != PlayMap::Directions::UNKNOWN ? _last_direction : tmp);
            _ia_last_pos = tmp_pos;
            calculateMovement(1);
        } else if (_possible_direction == 1 || _possible_direction == 2 || _possible_direction == 4 || _possible_direction == 8 || _nbrBomb + 1 == _bombMax) {
            placeBomb(lib, map);
            _bomb_pos.push_back(tmp_pos);
            escapeBomb(tmp_map, tmp_mapSize, tmp_pos);
        } else {
            _direction = PlayMap::Directions::UNKNOWN;
            _last_direction = (tmp == _direction && tmp != PlayMap::Directions::UNKNOWN ? _last_direction : tmp);
            _ia_last_pos = tmp_pos;
            calculateMovement(1);
        }
    }
}

/**
 * @brief A small pathFinding for the AI to run away from the bomb he just put on the map
 * 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 */

void Entity::IA::escapeBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos)
{
    std::pair<int, int> new_pos = tmp_pos;
    PlayMap::Directions bomb_direction;
    int max_actions = 9;

    if (tmp_pos.second > _ia_last_pos.second) {
        _actions.push_back(Entity::Actions{.direction = PlayMap::Directions::NORTH, .movement = 1});
        new_pos.second += -1;
        bomb_direction = PlayMap::Directions::SOUTH;
    } else if (tmp_pos.second < _ia_last_pos.second) {
        _actions.push_back(Entity::Actions{.direction = PlayMap::Directions::SOUTH, .movement = 1});
        new_pos.second += 1;
        bomb_direction = PlayMap::Directions::NORTH;
    } else if (tmp_pos.first > _ia_last_pos.first) {
        _actions.push_back(Entity::Actions{.direction = PlayMap::Directions::EST, .movement = 1});
        new_pos.first += -1;
        bomb_direction = PlayMap::Directions::WEST;
    } else {
        _actions.push_back(Entity::Actions{.direction = PlayMap::Directions::WEST, .movement = 1});
        new_pos.first += 1;
        bomb_direction = PlayMap::Directions::EST;
    }

    while ((new_pos.first != tmp_pos.first || new_pos.second != tmp_pos.second)
    && abs(new_pos.first - tmp_pos.first) <= _bombRange + 1
    && abs(new_pos.second - tmp_pos.second) <= _bombRange + 1
    && max_actions > 0) {
        possibleNewMovement(tmp_map, tmp_mapSize, new_pos);
        _possible_direction |= bomb_direction;
        if (getOppositeDirection(bomb_direction) & _possible_direction) {
            _actions.push_back(Entity::Actions{.direction = getOppositeDirection(bomb_direction), .movement = 1});
            calculateNewMovement(std::ref(new_pos), getOppositeDirection(bomb_direction));
        } else if (getRightDirection(bomb_direction) & _possible_direction) {
            _actions.push_back(Entity::Actions{.direction = getRightDirection(bomb_direction), .movement = 1});
            calculateNewMovement(std::ref(new_pos), getRightDirection(bomb_direction));
        } else if (getOppositeDirection(getRightDirection(bomb_direction)) & _possible_direction) {
            _actions.push_back(Entity::Actions{.direction = getOppositeDirection(getRightDirection(bomb_direction)), .movement = 1});
            calculateNewMovement(std::ref(new_pos), getOppositeDirection(getRightDirection(bomb_direction)));
        } else
            break;
        --max_actions;
    }
}

/**
 * @brief Search other player's bomb to dodge them at a range of 2
 * 
 * @param tmp_map 
 * @param tmp_mapSize 
 * @param tmp_pos 
 * @param direction 
 * @return true 
 * @return false 
 */

bool Entity::IA::searchBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map,
std::pair<int, int> &tmp_mapSize, std::pair<int, int> tmp_pos, PlayMap::Directions direction)
{
    if (tmp_pos.first - 1 >= 0 && tmp_pos.first + 1 <= tmp_mapSize.first &&
    tmp_pos.second - 1 >= 0 && tmp_pos.second + 1 <= tmp_mapSize.second &&
    tmp_map.at(tmp_pos.second + 1).at(tmp_pos.first) == PlayMap::CellState::BOMB ||
    tmp_map.at(tmp_pos.second - 1).at(tmp_pos.first) == PlayMap::CellState::BOMB ||
    tmp_map.at(tmp_pos.second).at(tmp_pos.first - 1) == PlayMap::CellState::BOMB ||
    tmp_map.at(tmp_pos.second).at(tmp_pos.first + 1) == PlayMap::CellState::BOMB ||
    tmp_map.at(tmp_pos.second).at(tmp_pos.first) == PlayMap::CellState::BOMB) {
        _dangerous_direction += direction;
        return true;
    }
    return false;
}

/**
 * @brief Search if a bomb is on the player
 * 
 * @param tmp_map map in text
 * @param tmp_pos position of the player on the map text
 * @return true 
 * @return false 
 */

bool Entity::IA::searchBomb(std::vector<std::vector<PlayMap::CellState>> &tmp_map, std::pair<int, int> tmp_pos)
{
    if (tmp_map.at(tmp_pos.second).at(tmp_pos.first) == PlayMap::CellState::BOMB)
        return true;
    return false;
}
