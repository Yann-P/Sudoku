#ifndef LEVEL_H
#define LEVEL_H
#include "model.h"
#include "controller.h"
#include "difficulty.h"

/*
 * @brief Niveau défini par une difficulté.
 *
 */

class Level {

public:
    Level(Difficulty);
    Model * model();
    Controller * controller();
    Difficulty difficulty();

    ~Level();



private:
    Model * const _model;
    Controller * const _controller;
    Difficulty _difficulty = Difficulty::Easy;


};

#endif // LEVEL_H
