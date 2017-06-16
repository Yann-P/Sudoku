#include <QWidget>
#include <QSize>
#include <QMargins>
#include <QEvent>
#include <QKeyEvent>
#include "sudokuedit.h"
#include <iostream>

SudokuEdit::SudokuEdit(QWidget * const parent, int x, int y) :
    QLineEdit(parent),
    _x(x),
    _y(y)
{
    setFixedSize(QSize(50, 50));
    setTextMargins(QMargins(5, 5, 5, 5));
    setStyleSheet("border: 0px solid white; background-color: rgba(0, 0, 0, 0); color: rgba(0, 0, 0, 0);");
    connect(this, SIGNAL(textChanged(const QString &)), this, SLOT(onTextChanged(const QString &)));

}

void SudokuEdit::focusInEvent(QFocusEvent * evt) {
    emit selected(this);
}

void SudokuEdit::keyPressEvent(QKeyEvent * evt) {
    if(evt->key() == Qt::Key_Delete || evt->key() == Qt::Key_Backspace)
        emit changed(this, 0);

    if(evt->key() == Qt::Key_Z) {
        if (evt->modifiers() & Qt::ShiftModifier)
            emit redoSignal();
        else
            emit undoSignal();
    }

    if(evt->key() == Qt::Key_Up || evt->key() == Qt::Key_Down || evt->key() == Qt::Key_Left || evt->key() == Qt::Key_Right) {
        emit directionSignal(_x, _y, evt->key());
    }

    QLineEdit::keyPressEvent(evt);
}

void SudokuEdit::onTextChanged(const QString & val) {
    if(val == "")
        return;
    emit changed(this, val.toInt(0, 10));
}

int SudokuEdit::x() const {
    return _x;
}

int SudokuEdit::y() const {
    return _y;
}
