#ifndef SUDOKUWINDOW_H
#define SUDOKUWINDOW_H

#include <QMainWindow>
#include <QMargins>
#include <QPalette>

#include <QInputDialog>
#include <QTimer>
#include <model.h>
#include <QCloseEvent>
#include "controller.h"
#include "ui_sudokuwindow.h"
#include "sudokuedit.h"
#include "level.h"
#include "scoremanager.h"

/*
 * @brief Fenêtre principale.
 *
 */

class SudokuMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SudokuMainWindow(QWidget *parent = 0);
    ~SudokuMainWindow();

private:
    Ui::SudokuWindow * ui;
    Level * _level = nullptr;
    QUndoStack * _undoStack = nullptr;
    SudokuEdit * _inputs[9][9];
    ScoreManager _scores;
    QTimer *_timer = nullptr;

    void showVictoryBox();
    void createSudokuEdits();
    void closeEvent(QCloseEvent *);


private slots:
    void playerMove(SudokuEdit * const, int);
    void cellSelected(const SudokuEdit * const);
    void newGame(Difficulty);
    void newGame();
    void changeDifficulty(int);
    void undo();
    void redo();
    void direction(int, int, int);
    void displayControls();
    void displayScores();
    void quit();
    void updateTimer();
};

namespace Ui {
    class SudokuWindow;
}

#endif // SUDOKUWINDOW_H
