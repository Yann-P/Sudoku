#include "model.h"

using namespace std;

Model::Model() {

}

Model::Model(const QString & path) {

    QFile fichier(":/levels/" + path);
    if (!fichier.open(QIODevice::ReadOnly))
    {
        throw "Erreur ouverture du fichier";
        return;
    }



    QTextStream in(&fichier);
    QString nbGrid = in.readLine();
    QStringList tokens;
    int randomLine = qrand()%((nbGrid.toInt(0,10)+1)-1)+1;
    for (int i=0; i<randomLine;i++)
    {
        tokens = in.readLine().split(QRegExp(" "));
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            _grid[i][j] = tokens.takeFirst().toInt(0,10);
            _editable[i][j] = _grid[i][j]==0;
        }
    }

}

int Model::getCell(int x, int y) const {
    if(outOfBounds(x, y))
        throw "ouf of bounds";
    return _grid[x][y];
}

void Model::setCell(int x, int y, int val) {
    if(outOfBounds(x, y))
        throw "ouf of bounds";
    if(val < 0 || val > 9) {
        std::cerr << QString("Tentative de définir une case à la valeur invalide %1").arg(val).toStdString() << std::endl;
    }
    _grid[x][y] = val;
}

bool Model::isEditable(int x, int y) const {
    if(outOfBounds(x, y))
        throw "ouf of bounds";
    return _editable[x][y];
}

bool Model::outOfBounds(int x, int y) const {
    return x < 0 || y < 0 || x >= 9 || y >= 9;
}
