#include "level.h"
#include "difficulty.h"

Level::Level(Difficulty difficulty):
    _model(new Model(getDifficultyFile(difficulty))),
    _controller(new Controller(_model)),_difficulty(difficulty){


}

Model * Level::model() {
    return _model;
}

Controller * Level::controller() {
    return _controller;
}

Difficulty Level::difficulty()
{
    return _difficulty;
}

Level::~Level() {
    delete _model;
    delete _controller;
}
