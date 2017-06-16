#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>

/*
 * @brief Structure de données qui contient la grille.
 *
 */

class Model
{

public:
    Model();
    Model(const QString & path);
    int getCell(int, int) const;
    void setCell(int, int, int);
    bool isEditable(int, int) const;

private:
    int _grid[9][9];
    bool _editable[9][9];
    bool outOfBounds(int, int) const;

};

#endif // MODEL_H
