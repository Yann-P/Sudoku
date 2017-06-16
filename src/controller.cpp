#include "controller.h"

Controller::Controller(const Model * m): _model(m)
{

}

bool Controller::hasNumberOnColumn(int val, int x) const {
    for(int y = 0; y < 9; y++) {
        if(_model->getCell(x, y) == val)
            return true;
    }
    return false;
}

bool Controller::hasNumberOnLine(int val, int y) const {
    for(int x = 0; x < 9; x++) {
        if(_model->getCell(x, y) == val)
            return true;
    }
    return false;
}

bool Controller::hasNumberOnSubgrid(int val, int x, int y) const {
    int topLeftX = (int)(x/3.) * 3;
    int topLeftY = (int)(y/3.) * 3;
    for(int x = topLeftX; x < topLeftX + 3; x++) {
        for(int y = topLeftY; y < topLeftY + 3; y++) {
            if(_model->getCell(x, y) == val) {
                return true;
            }
        }
    }
    return false;
}

bool Controller::hasWon() const {
    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 9; y++) {
            if(_model->getCell(x, y) == 0) {
               return false;
            }
        }
    }
    return true;
}


bool Controller::isValidMove(const PlayCommand * cmd) const {

    int x = cmd->x();
    int y = cmd->y();
    int val = cmd->val();


    if(!_model->isEditable(x, y))
        return false;

    if(val != 0 && val != _model->getCell(x, y)) {

        if(hasNumberOnLine(val, y))
            return false;

        if(hasNumberOnColumn(val, x))
            return false;

        if(hasNumberOnSubgrid(val, x, y))
            return false;
    }
    return true;
}
