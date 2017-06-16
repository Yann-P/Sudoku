#include "playcommand.h"
#include <iostream>

PlayCommand::PlayCommand(Model * m, int x, int y, int val):
    QUndoCommand(QString("Jouer %1 en (%2, %3)").arg(val).arg(x + 1).arg(y + 1)) {
    _model = m;
    _x = x;
    _y = y;
    _oldVal = m->getCell(x, y);
    _val = val;
}

void PlayCommand::undo() {
    _model->setCell(_x, _y, _oldVal);
}

void PlayCommand::redo() {
    _model->setCell(_x, _y, _val);
}

int PlayCommand::x() const {
    return _x;
}

int PlayCommand::y() const {
    return _y;
}

int PlayCommand::val() const {
    return _val;
}
