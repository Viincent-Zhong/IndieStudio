/*
** EPITECH PROJECT, 2022
** indiestudio
** File description:
** Player
*/

#include "Player.hpp"
#include "PlayMap.hpp"

Entity::Player::Player()
{
    this->_canBeDestroyed = true;
    this->_animeFrame = 0;
    this->_speed = 0;
    this->_position = {0.0f, 0.0f};
    this->_lastCell = PlayMap::CellState::SPACE;
    this->_nbrBomb = 0;
    this->_bombMax = 1;
    this->_hp = 1;
    this->_bombRange = 1;
    this->_animation = 3;
    this->_type = PLAYER;
    _dancing = false;
}

Entity::Player::~Player()
{
}

std::string Entity::Player::getId() const
{
    return this->_id;
}

void Entity::Player::setSpeed(const float speed)
{
    this->_speed = speed;
}

bool Entity::Player::setTextures(IndieStudio::IGraphical &lib, const std::pair<float, float> &pos, std::vector<std::string> const &textures)
{
    this->_position = {pos.first, pos.second};
    if (textures.size() != 4)
        return false;
    this->_texture = textures[2];
    this->_id = textures[0];
    _element.create(this->_id, pos, textures[1], textures[2], textures[3]);
    return true;
}

bool Entity::Player::movePlayer(RaylibMap::Map const &libmap, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities, std::pair<float, float> move)
{
    if (!_element.move(move, libmap))
        return false;
    if (map.collisionBlocks(this->_element)) {
        _element.substractMove(move);
        return false;
    }
    for (auto it = entities.begin(); it != entities.end(); ++it) {
        if (it->get()->getId() != this->_id && it->get()->checkCollision(_element)) {
            _element.substractMove(move);
            return false;
        }
    }

    map.changeCell(map.posIntoMapPos(this->_position), this->_lastCell);

    this->_position.first += move.first;
    this->_position.second += move.second;

    std::pair<int, int> playerPos = map.posIntoMapPos(this->_position);
    PlayMap::CellState tmp = map.getCellState(map.posIntoMapPos(this->_position));
    if (tmp != PlayMap::CellState::UNDEFINED) {
        this->_lastCell = tmp;
        if (tmp != PlayMap::CellState::BOMB && tmp != PlayMap::CellState::POWERUP)
            map.changeCell(playerPos, PlayMap::PLAYER);
    }
    return true;
}

bool Entity::Player::playerMovement(IndieStudio::IGraphical &lib, RaylibMap::Map const &libmap, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities)
{
    std::pair<float, float> move = {0.0f, 0.0f};

    if (_event.isKeyDown(_bindings.right) || _gamepad.isPadKeyDown(_bindings.gamePad, PAD_RIGHT)) {
        move.first = this->_speed;
        this->_orientation = "RIGHT";
    }
    else if (_event.isKeyDown(_bindings.left) || _gamepad.isPadKeyDown(_bindings.gamePad, PAD_LEFT)) {
        move.first = -this->_speed;
        this->_orientation = "LEFT";
    }
    else if (_event.isKeyDown(_bindings.down) || _gamepad.isPadKeyDown(_bindings.gamePad, PAD_DOWN)) {
        move.second = this->_speed;
        this->_orientation = "DOWN";
    }
    else if (_event.isKeyDown(_bindings.up) || _gamepad.isPadKeyDown(_bindings.gamePad, PAD_UP)) {
        move.second = -this->_speed;
        this->_orientation = "UP";
    }
    if (move.first == 0.0 && move.second == 0.0)
        return false;
    if (!movePlayer(libmap, map, entities, move))
        return false;
    pickPowerUp(map);
    return true;
}

void Entity::Player::bombEvent(IndieStudio::IGraphical &lib, PlayMap &map, std::vector<std::unique_ptr<Entity::IEntity>> &entities)
{
    if (this->_bomb.size() == 0)
        return;
    for (auto it = this->_bomb.begin(); it != this->_bomb.end();) {
        it->get()->UpdateTimer(lib);
        if (it->get()->TimerDone()) {
            std::pair<int, int> bombPos = map.posIntoMapPos(it->get()->getBombPositionMap());
            this->_nbrBomb--;
            it->get()->explodeBomb(map, entities, lib);
            it = this->_bomb.erase(it);
            if (map.posIntoMapPos(this->_position) == bombPos)
                this->_lastCell = PlayMap::CellState::SPACE;
            else
                map.changeCell(bombPos, PlayMap::CellState::SPACE);
            continue;
        }
        it->get()->drawEntity(lib);
        ++it;
    }
}

void Entity::Player::placeBomb(IndieStudio::IGraphical &lib, PlayMap &map)
{
    if (this->_bombMax >= this->_nbrBomb + 1) {
        this->_bomb.push_back(std::make_unique<Entity::Bomb>(Bomb(lib, this->getPosition(), this->getOrientation(), this->_bombRange)));
        this->_lastCell = PlayMap::CellState::BOMB;
        map.changeCell(map.posIntoMapPos(_bomb.back().get()->getBombPositionMap()), PlayMap::CellState::BOMB);
        this->_nbrBomb++;
    }
}


Entity::Event Entity::Player::event(IndieStudio::IGraphical &lib, PlayMap &map, const int &event, RaylibMap::Map const &libmap, std::vector<std::unique_ptr<Entity::IEntity>> &entities)
{
    if (this->_hp <= 0) {
        return Entity::DEATH;
    }
    if (!_dancing && !this->playerMovement(lib, libmap, map, entities))
        this->stopAnimation(lib);
    else {
        this->continueAnimation();
    }
    bombEvent(lib, map, entities);
    if (_event.isKeyReleased(_bindings.bomb) || _gamepad.isPadKeyReleased(_bindings.gamePad, PAD_A))
        placeBomb(lib, map);
    this->dance();
    return Entity::NOTHING;
}

void Entity::Player::setAnimationFrame(const unsigned int frame)
{
    this->_animeFrame = frame;
}

void Entity::Player::stopAnimation(IndieStudio::IGraphical &lib)
{
    _element.setAnimation(_animeFrame);
}

void Entity::Player::continueAnimation()
{
    _element.anim();
}

void Entity::Player::drawEntity(IndieStudio::IGraphical &lib)
{
    _element.display();
}

void Entity::Player::destroyEntity(IndieStudio::IGraphical &lib)
{
}

void Entity::Player::setSize(IndieStudio::IGraphical &lib, const float x, const float y, const float z)
{
    _element.setElemSize(x, y, z);
}

void Entity::Player::setRotation(IndieStudio::IGraphical &lib, const float rotation, const float x, const float y, const float z)
{
    _element.setElemRotation(rotation, x, y, z);
}

const std::pair<float, float> Entity::Player::getPosition() const
{
    return this->_position;
}

const std::string Entity::Player::getOrientation() const
{
    return this->_orientation;
}

void Entity::Player::updateTexture(std::string const &path)
{
    _element.updateElemTexture(path);
}

bool Entity::Player::checkCollision(RaylibElement::Element &element)
{
    if (element.checkCollision(_element))
        return true;
    return false;
}

RaylibElement::Element Entity::Player::getEntity() const
{
    return _element;
}

void Entity::Player::setBindings(Binding const &binds)
{
    this->_bindings.bomb = binds.bomb;
    this->_bindings.down = binds.down;
    this->_bindings.up = binds.up;
    this->_bindings.left = binds.left;
    this->_bindings.right = binds.right;
    this->_bindings.animation = binds.animation;
    this->_bindings.gamePad = binds.gamePad;
}

void Entity::Player::damageEntity()
{
    --this->_hp;
}

Entity::Category Entity::Player::getType() const
{
    return this->_type;
}

std::string Entity::Player::getTexture() const
{
    return this->_texture;
}

Entity::Stat Entity::Player::getStat() const
{
    return {_hp, _bombRange, _bombMax, _speed};
}

void Entity::Player::pickPowerUp(PlayMap &map)
{
    PlayMap::PowerUp pup = map.collisionPowerUp(_element);

    switch (pup) {
        case PlayMap::PowerUp::BOMBMAX:
            _bombMax++;
            break;
        case PlayMap::PowerUp::RANGE:
            _bombRange++;
            break;
        case PlayMap::PowerUp::SPEED:
            _speed += 0.005f;
            break;
    }
    if (pup != PlayMap::PowerUp::NO)
        this->_lastCell = PlayMap::CellState::SPACE;
}

void Entity::Player::setStat(Stat const &stat)
{
    _bombMax = stat.bombMax;
    _bombRange = stat.bombRange;
    _hp = stat.hp;
    _speed = stat.speed;
}

int Entity::Player::getNbrBomb() const
{
    return _nbrBomb;
}

void Entity::Player::dance()
{
    if (IsKeyDown(_bindings.animation) || _gamepad.isPadKeyDown(_bindings.gamePad, PAD_Y)) {
        if (_gamepad.isPadKeyReleased(_bindings.gamePad, PAD_TRIGGER_LEFT) && _animation < 5)
            _animation++;
        else if (_gamepad.isPadKeyReleased(_bindings.gamePad, PAD_TRIGGER_RIGHT) && _animation > 3)
            _animation--;
        _element.setAnimationModel(_animation);
        _dancing = true;
    } else {
        _element.setAnimationModel(0);
        _dancing = false;
    }
}

Entity::Binding const &Entity::Player::getBindings() const
{
    return _bindings;
}
