#ifndef PLAYCOMMAND_H
#define PLAYCOMMAND_H
#include "model.h"
#include <QUndoCommand>

/*
 * @brief Action du joueur héritant de QUndoCommand pour utiliser le framework undo de Qt.
 *
 */

class PlayCommand: public QUndoCommand {

public:
    PlayCommand(Model *, int, int, int);
    void undo() override;
    void redo() override;
    int x() const;
    int y() const;
    int val() const;


private:
    int _x;
    int _y;
    int _val;
    int _oldVal;
    Model * _model;

};

#endif // PLAYCOMMAND_H
