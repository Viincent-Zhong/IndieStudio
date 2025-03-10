/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneSelection.cpp
*/

#include <iostream>
#include <string.h>
#include "SceneSelection.hpp"
#include "Parser.hpp"
#include "Player.hpp"
#include "IOBinary.hpp"

SceneSelection::SceneSelection(IndieStudio::IGraphical &lib) : _id(SELECTION), _indexMap(0)
{
    getPath("src/scenes/Selection/init.txt");
    initButtons(lib);
    initElems(lib);
    _gameParam.playerOneName = "DARK PA";
    _gameParam.playerTwoName = "DARK HEPHEL";
    _gameParam.texture_one = _path.texture.at(0);
    _gameParam.texture_two = _path.texture.at(1);
    _gameParam.againstAi = true;
    _gameParam.bonus = true;
    _gameParam.map = _path.map.at(0);
    for (int i = 0; i != _path.map.size(); ++i) {
        _map.push_back(std::make_unique<RaylibImage::Image>());
        _map.at(i)->create(_path.map.at(i));
    }
}

SceneSelection::~SceneSelection()
{
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneSelection::run(IndieStudio::IGraphical &lib)
{
    IndieStudio::IScene::SceneId event;

    _music.initMusic(_path.music, lib.getMusicVolume());
    _text.loadFont(_path.font);
    _background.create(_path.background);
    for (auto &button : _buttons)
        button->setEffectLevel(lib.getEffectLevel());
    while (conditionEnd(lib)) {
        _music.updateMusicStream();
        event = sceneEvents(lib);
        if (event != this->_id)
            return {event, true};
        drawElems(lib);
    }
    return {END, true};
}

void SceneSelection::drawElems(IndieStudio::IGraphical &lib)
{
    lib.startDrawing(true);
    _background.display({0.0f, 0.0f}, 1.0f);
    lib.start3d();
    for (auto &elem : _elems) {
        elem->anim();
        elem->display();
    }
    lib.end3d();
    for (auto &button : _buttons) {
        button->animation();
        button->display();
    }
    printStatusParams(lib);
    lib.endDrawing();
}

void SceneSelection::textInput(IndieStudio::IGraphical &lib, std::string &input, const int keyInput, std::vector<float> const &rec)
{
    if (_event.mouseOnText(rec.at(0), rec.at(1), rec.at(2), rec.at(3))) {
        if (keyInput >= KEY_A && keyInput <= KEY_Z && input.size() != NAME_SIZE)
            input.push_back(keyInput);
        if (keyInput == DELETE && input.size() != 0)
            input.pop_back();
    }
}

void SceneSelection::updateSkin(IndieStudio::IGraphical &lib, const int incr, const int max, const int min, const unsigned int idButton, const unsigned int id)
{
    if (_buttons.at(idButton)->isPress()) {
        if (_textureElem.find(_elemName.at(id))->second == max)
            _textureElem.find(_elemName.at(id))->second = min;
        _textureElem.find(_elemName.at(id))->second += incr;
        _elems.at(id)->updateElemTexture(_path.texture.at(_textureElem.find(_elemName.at(id))->second));
        if (id == 0)
            _gameParam.texture_one = _path.texture.at(_textureElem.find(_elemName.at(id))->second);
        else
            _gameParam.texture_two = _path.texture.at(_textureElem.find(_elemName.at(id))->second);
    }
}

IndieStudio::IScene::SceneId SceneSelection::sceneEvents(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    const int keyInput = _event.getKeyInput();

    textInput(lib, _gameParam.playerOneName, keyInput, {(float)(windowSize.first / 6.4), (float)(windowSize.second / 5.4), 100, 100});
    textInput(lib, _gameParam.playerTwoName, keyInput, {(float)(windowSize.first / 2.133333), (float)(windowSize.second / 5.4), 100, 100});
    updateSkin(lib, 1, _path.texture.size() - 1, -1, COLORUPONE, 0);
    updateSkin(lib, -1, 0, _path.texture.size(), COLORDOWNONE, 0);
    updateSkin(lib, 1, _path.texture.size() - 1, -1, COLORUPTWO, 1);
    updateSkin(lib, -1, 0, _path.texture.size(), COLORDOWNTWO, 1);
    handleButtonCheckBox(lib, _gameParam.againstAi, AI, {windowSize.first / 1.066666, windowSize.second / 2.16});
    handleButtonCheckBox(lib, _gameParam.bonus, BONUS, {windowSize.first / 1.066666, windowSize.second / 1.8});
    if (_buttons.at(SIZEUP)->isPress() || _gamepad.isPadKeyReleased(0, PAD_UP)) {
        ++_indexMap;
        if (_indexMap == _map.size())
            _indexMap = 0;
        _gameParam.map = _path.map.at(_indexMap);
    }
    if (_buttons.at(SIZEDOWN)->isPress() || _gamepad.isPadKeyReleased(0, PAD_DOWN)) {
        --_indexMap;
        if (_indexMap == -1)
            _indexMap = _map.size() - 1;
        _gameParam.map = _path.map.at(_indexMap);
    }
    if (_buttons.at(BACK)->isPress() || _gamepad.isPadKeyReleased(0, PAD_B))
        return MENU;
    if (_buttons.at(STARTGAME)->isPress() || _gamepad.isPadKeyDown(0, PAD_START)) {
        saveParams();
        return GAME;
    }
    return this->_id;
}

void SceneSelection::handleButtonCheckBox(IndieStudio::IGraphical &lib, bool &status, const unsigned int id, std::pair<float, float> const &pos)
{
    if (_buttons.at(id)->isPress()) {
        if (status) {
            status = false;
            _buttons.at(id)->update(_path.buttons.at(11), pos);
        } else {
            status = true;
            _buttons.at(id)->update(_path.buttons.at(10), pos);
        }
    }
    if (id == AI && _gamepad.isPadKeyReleased(0, PAD_Y)) {
        if (status) {
            status = false;
            _buttons.at(id)->update(_path.buttons.at(11), pos);
        } else {
            status = true;
            _buttons.at(id)->update(_path.buttons.at(10), pos);
        }
    }
    if (id == BONUS && _gamepad.isPadKeyReleased(0, PAD_X)) {
        if (status) {
            status = false;
            _buttons.at(id)->update(_path.buttons.at(11), pos);
        } else {
            status = true;
            _buttons.at(id)->update(_path.buttons.at(10), pos);
        }
    }
}

bool SceneSelection::conditionEnd(IndieStudio::IGraphical &lib)
{
    return !lib.endGame();
}

void SceneSelection::getPath(std::string const &file)
{
    Parser parser(file);

    _path.buttons.push_back(parser.getDataFromFile("BUTTONGAME"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONGAMEHOVER"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONEXIT"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONEXITHOVER"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONPLUS"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONPLUSHOVER"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONMINUS"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONMINUSHOVER"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONBACK"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONBACKHOVER"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONTRUE"));
    _path.buttons.push_back(parser.getDataFromFile("BUTTONFALSE"));
    _path.playerAnim = parser.getDataFromFile("PLAYERANIM");
    _path.playerSkelet = parser.getDataFromFile("PLAYERSKELETE");
    _path.texture.push_back(parser.getDataFromFile("PLAYERTEXTUREONE"));
    _path.texture.push_back(parser.getDataFromFile("PLAYERTEXTURETWO"));
    _path.texture.push_back(parser.getDataFromFile("PLAYERTEXTURETHREE"));
    _path.texture.push_back(parser.getDataFromFile("PLAYERTEXTUREFOUR"));
    _path.texture.push_back(parser.getDataFromFile("PLAYERTEXTUREFIVE"));
    _path.map.push_back(parser.getDataFromFile("MAP_ONE"));
    _path.map.push_back(parser.getDataFromFile("MAP_TWO"));
    _path.map.push_back(parser.getDataFromFile("MAP_THREE"));
    _path.map.push_back(parser.getDataFromFile("MAP_FOUR"));
    _path.font = parser.getDataFromFile("FONT");
    _path.music = parser.getDataFromFile("MUSIC");
    _path.background = parser.getDataFromFile("BACKGROUND");
    _path.btnSound = parser.getDataFromFile("BTN_SOUND");
}

void SceneSelection::initButtons(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();

    for (int i = 0; i != 10; ++i)
        _buttons.push_back(std::make_unique<RaylibButton::Button>());
    _buttons.at(STARTGAME)->create(_path.buttons.at(0), _path.buttons.at(1), {windowSize.first / 1.28, windowSize.second / 1.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(COLORUPONE)->create(_path.buttons.at(4), _path.buttons.at(5), {windowSize.first / 9.6, windowSize.second / 1.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(COLORDOWNONE)->create(_path.buttons.at(6), _path.buttons.at(7), {windowSize.first / 4.8, windowSize.second / 1.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(COLORUPTWO)->create(_path.buttons.at(4), _path.buttons.at(5), {windowSize.first / 2.4, windowSize.second / 1.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(COLORDOWNTWO)->create(_path.buttons.at(6), _path.buttons.at(7), {windowSize.first / 1.92, windowSize.second / 1.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(BACK)->create(_path.buttons.at(8), _path.buttons.at(9), {windowSize.first / 19.2, windowSize.second / 21.6}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(AI)->create(_path.buttons.at(10), _path.buttons.at(10), {windowSize.first / 1.06666, windowSize.second / 2.16}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(BONUS)->create(_path.buttons.at(10), _path.buttons.at(10), {windowSize.first / 1.06666, windowSize.second / 1.8}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(SIZEUP)->create(_path.buttons.at(4), _path.buttons.at(5), {windowSize.first / 1.28, windowSize.second / 3.6}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(SIZEDOWN)->create(_path.buttons.at(6), _path.buttons.at(7), {windowSize.first / 1.06666, windowSize.second / 3.6}, _path.btnSound, lib.getEffectLevel());
}

void SceneSelection::initElems(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();

    _elemName.push_back("selectionCPlayerOne");
    _elemName.push_back("selectionCPlayerTwo");
    _textureElem.insert({_elemName.at(0), 0});
    _textureElem.insert({_elemName.at(1), 1});
    for (int i = 0; i != 2; ++i)
        _elems.push_back(std::make_unique<RaylibElement::Element>());
    _elems.at(0)->create("p1", {-(windowSize.first / 147.69), windowSize.second / 180}, _path.playerSkelet, _path.texture.at(_textureElem.find(_elemName.at(0))->second), _path.playerAnim);
    _elems.at(1)->create("p2", {0.0f, windowSize.second / 180}, _path.playerSkelet, _path.texture.at(_textureElem.find(_elemName.at(1))->second), _path.playerAnim);
    for (auto &elem : _elems) {
        elem->setElemSize(5.0f, 5.0f, 5.0f);
        elem->setElemRotation(-90.0f, 90.0f, -180.0f, 90.0f);
        elem->setAnimationModel(1);
    }
}

void SceneSelection::printStatusParams(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    const std::vector<Color> listColors = {RED, BLUE, GREEN, PURPLE, YELLOW, BLUE};

    _text.printText("Play against AI: ", {windowSize.first / 1.379709, windowSize.second / 2.03773}, BLACK, 3.0f);
    _text.printText("Bonus: ", {windowSize.first / 1.238709, windowSize.second / 1.71428}, BLACK, 3.0f);
    _text.printText("Select map", {windowSize.first / 1.2, windowSize.second / 4.695652}, BLACK, 3.0f);
    _map.at(_indexMap)->display({windowSize.first / 1.18518519, windowSize.second / 3.48387}, 5.0f);
    _text.printText("Player: " + _gameParam.playerOneName, {windowSize.first / 6.4, windowSize.second / 5.4}, listColors.at(_textureElem.find(_elemName.at(0))->second), 2.0f);
    _text.printText("Player: " + _gameParam.playerTwoName, {windowSize.first / 2.133333, windowSize.second / 5.4}, listColors.at(_textureElem.find(_elemName.at(1))->second), 2.0f);
}

void SceneSelection::saveParams()
{
    IndieStudio::messageParams message = {0};

    message.againstAi = _gameParam.againstAi;
    message.bonus = _gameParam.bonus;
    strcat(message.map, _gameParam.map.c_str());
    strcat(message.playerOneName, _gameParam.playerOneName.c_str());
    strcat(message.playerTwoName, _gameParam.playerTwoName.c_str());
    strcat(message.textureOne, _gameParam.texture_one.c_str());
    strcat(message.textureTwo, _gameParam.texture_two.c_str());

    IOBinary::writeFile<IndieStudio::messageParams>(message, ".gameoption.dat");
}

void SceneSelection::initScene()
{
}
