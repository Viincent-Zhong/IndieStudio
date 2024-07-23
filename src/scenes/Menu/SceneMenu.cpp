/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneMenu.cpp
*/

#include "SceneMenu.hpp"
#include "Parser.hpp"

void SceneMenu::parseFile(std::string const &path)
{
    Parser parser(path);

    _path.pathButtonGame = parser.getDataFromFile("BUTTONGAME");
    _path.pathButtonGameHover = parser.getDataFromFile("BUTTONGAMEHOVER");
    _path.pathButtonLoadGame = parser.getDataFromFile("BUTTONLOADGAME");
    _path.pathButtonLoadGameHover = parser.getDataFromFile("BUTTONLOADGAMEHOVER");
    _path.pathButtonExit = parser.getDataFromFile("BUTTONEXIT");
    _path.pathButtonExitHover = parser.getDataFromFile("BUTTONEXITHOVER");
    _path.pathButtonParams = parser.getDataFromFile("BUTTONPARAMS");
    _path.pathButtonParamsHover = parser.getDataFromFile("BUTTONPARAMSHOVER");
    _path.playerAnim = parser.getDataFromFile("PLAYERANIM");
    _path.playerSkelet = parser.getDataFromFile("PLAYERSKELETE");
    _path.playerOneTexture = parser.getDataFromFile("PLAYERONETEXTURE");
    _path.playerTwoTexture = parser.getDataFromFile("PLAYERTWOTEXTURE");
    _path.font = parser.getDataFromFile("FONT");
    _path.logo = parser.getDataFromFile("LOGO");
    _path.background = parser.getDataFromFile("BACKGROUND");
    _path.music = parser.getDataFromFile("MUSIC");
    _path.btnSound = parser.getDataFromFile("BTN_SOUND");
}

SceneMenu::SceneMenu(IndieStudio::IGraphical &lib) : _id(MENU)
{
    parseFile(PATH_INIT_MENU);
    for (int i = 0; i != 4; ++i)
        _buttons.push_back(std::make_unique<RaylibButton::Button>());
    for (int i = 0; i != 2; ++i)
        _elems.push_back(std::make_unique<RaylibElement::Element>());
}

void SceneMenu::initData(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    _buttons.at(GAME)->create(_path.pathButtonGame, _path.pathButtonGameHover, {windowSize.first / 4.8, windowSize.second / 1.25}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(EXIT)->create(_path.pathButtonExit, _path.pathButtonExitHover, {windowSize.first / 1.28, windowSize.second / 10.8}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(PARAM)->create(_path.pathButtonParams, _path.pathButtonParamsHover, {windowSize.first / 19.2,  windowSize.second / 10.8}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(LOAD)->create(_path.pathButtonLoadGame, _path.pathButtonLoadGameHover, {windowSize.first / 1.6, windowSize.second / 1.25}, _path.btnSound, lib.getEffectLevel());
    _elems.at(0)->create("p1", {-(windowSize.first / 128), windowSize.second / 180}, _path.playerSkelet, _path.playerOneTexture, _path.playerAnim);
    _elems.at(0)->setElemRotation(-145.0f, 0.0f, -180.0f, 90.0f);
    _elems.at(1)->create("p2", {windowSize.first / 128, windowSize.second / 216}, _path.playerSkelet, _path.playerTwoTexture, _path.playerAnim);
    _elems.at(1)->setElemRotation(45.0f, -90.0f, 90.0f, 0.0f);
    for (auto &elem : _elems) {
        elem->setElemSize(5.0f, 5.0f, 5.0f);
        elem->setAnimationModel(3);
    }
    _music.initMusic(_path.music, lib.getMusicVolume());
    _logo.create(_path.logo);
    _background.create(_path.background);
    _text.loadFont(_path.font);
}

SceneMenu::~SceneMenu()
{
}


std::pair<IndieStudio::IScene::SceneId, bool> SceneMenu::run(IndieStudio::IGraphical &lib)
{
    IndieStudio::IScene::SceneId event;

    initData(lib);
    while (!lib.endGame()) {
        _music.updateMusicStream();
        event = sceneEvents(lib);
        if (event != _id)
            return {event, true};
        drawElems(lib);
    }
    return {END, true};
}

IndieStudio::IScene::SceneId SceneMenu::sceneEvents(IndieStudio::IGraphical &lib)
{
    if (_event.getKeyInput() == KEY_ENTER || _gamepad.isPadKeyDown(0, PAD_A) || _buttons.at(GAME)->isPress())
        return SELECTION;
    if (_buttons.at(EXIT)->isPress() || _gamepad.isPadKeyDown(0, PAD_B))
        return END;
    if (_buttons.at(PARAM)->isPress() || _gamepad.isPadKeyDown(0, PAD_Y))
        return PARAMS;
    if (_buttons.at(LOAD)->isPress() || _gamepad.isPadKeyDown(0, PAD_X)) {
        lib.setLoadGame(true);
        return IndieStudio::IScene::GAME;
    }
    return _id;
}

void SceneMenu::drawElems(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    lib.startDrawing(true);
    _background.display({0.0f, 0.0f}, 1.0f);
    _logo.display({windowSize.first / 3.84, windowSize.second / 7.2}, 0.7f);
    lib.start3d();
    for (auto &elem : _elems) {
        elem->anim();
        elem->display();
    }
    lib.end3d();
    if (getBlinkCounter() < 35)
        _text.printText("Press enter to start the game", {windowSize.first / 2.65, windowSize.second / 2.16}, WHITE, 1.0f);
    else if (getBlinkCounter() > 70)
        resetBlinkCounter();
    incrementBlinkCounter();
    _text.printText("Press escape to leave", {windowSize.first / 2.45, windowSize.second / 1.8}, WHITE, 1.0f);
    for (auto &button : _buttons) {
        button->animation();
        button->display();
    }
    lib.endDrawing();
}

void SceneMenu::initScene()
{
}

void SceneMenu::incrementBlinkCounter()
{
    _blinkCounter++;
}

void SceneMenu::resetBlinkCounter()
{
    _blinkCounter = 0;
}

int SceneMenu::getBlinkCounter()
{
    return _blinkCounter;
}