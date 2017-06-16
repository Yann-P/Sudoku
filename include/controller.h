#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "playcommand.h"

/*
 * @brief Contrôleur du jeu : logique métier
 *
 */

class Controller
{

public:
    Controller(const Model *);
    bool isValidMove(const PlayCommand *) const;
    bool hasNumberOnColumn(int, int) const;
    bool hasNumberOnLine(int, int) const;
    bool hasNumberOnSubgrid(int, int, int) const;
    bool hasWon() const;
private:
    const Model * const _model;
};

#endif // CONTROLLER_H
