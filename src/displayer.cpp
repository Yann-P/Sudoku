#include "displayer.h"
#include <QColor>

using namespace std;

Displayer::Displayer(QWidget *parent) :
    QWidget(parent),
    _selectedCell(std::make_pair(-1, -1))
{
}


void Displayer::setModel(Model * model)
{
    _model = model;
}


void Displayer::drawGrid(QPainter &p)
{
    QRect pos(offset, offset, 450, 450);
    QPainterPath path;
    path.addRect(pos);
    p.strokePath(path, QPen(Qt::black, 3));
}

void Displayer::drawSubGrid(QPainter &p, int posX, int posY)
{
    QRect pos(posX*150+offset, posY*150+offset, 150, 150);
    QPainterPath path;
    path.addRect(pos);
    p.strokePath(path, QPen(Qt::black, 3));
}


void Displayer::drawCell(QPainter &p, int x, int y)
{
    QRect pos(x*50+offset, y*50+offset, 50, 50);
    QPainterPath path;
    int val = _model->getCell(x, y);


    path.addRect(pos);
    p.strokePath(path, QPen(Qt::black, 1));

    if(_selectedCell.first == x && _selectedCell.second == y) {
        if(_errorOnSelectedCell)
            p.fillRect(pos, QColor(255, 0, 0, 100));
        else
            p.fillRect(pos, QColor(255, 255, 0, 100));
    }

    QPen pen;
    QFont font;

    if(_model->isEditable(x, y)) {
        pen = QColor("#447799");
        font = QFont("arial", 13);
    } else {
        pen = QColor("#000000");
        font = QFont("ubuntu", 15);
    }

    p.setFont(font);
    p.setPen(pen);


    if (val != 0) {
        p.drawText(pos, Qt::AlignCenter, QString::number(val));
    } else{
        p.drawText(pos, Qt::AlignCenter, "");
    }

}

void Displayer::paintEvent(QPaintEvent *e)
{
    if(!_model)
        return;

    QPainter painter(this);
    painter.fillRect(QRect(0, 0, width(), height()), QBrush(Qt::white));

    drawGrid(painter);
    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3;j++)
        {
            drawSubGrid(painter, i, j);
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            drawCell(painter, i, j);
        }
    }


}

void Displayer::setSelectedCell(int x, int y) {
    _selectedCell.first = x;
    _selectedCell.second = y;
    repaint();
}

void Displayer::setErrorOnCurrentCell(bool hasError) {
    _errorOnSelectedCell = hasError;
    repaint();
}
