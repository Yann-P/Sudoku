#ifndef DISPLAYER_H
#define DISPLAYER_H

/*
 * @brief Afficheur de la grille et des chiffres. Mise en surbrillance de la case sélectionnée ou erronée.
 *
 */

#include <QWidget>
#include <QPainter>
#include <vector>
#include <model.h>

class Displayer : public QWidget
{
    Q_OBJECT

public:
    explicit Displayer(QWidget *parent = 0);
    void setModel(Model * );
    void setSelectedCell(int x, int y);
    void setErrorOnCurrentCell(bool);


private:
    void paintEvent(QPaintEvent *) override;
    void drawGrid(QPainter &);
    void drawSubGrid(QPainter &, int, int);
    void drawCell(QPainter &, int , int);


    int offset = 2;
    Model* _model=nullptr;
    std::pair<int, int> _selectedCell;
    bool _errorOnSelectedCell = false;


signals:

public slots:

};

#endif // DISPLAYER_H
