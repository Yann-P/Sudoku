#include "sudokumainwindow.h"
#include "ui_sudokuwindow.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QStringList>
#include <QMessageBox>
#include <QUrl>
#include "sudokuedit.h"
#include <iostream>
#include <QRegExp>
#include <QUndoStack>
#include "controller.h"
#include "playcommand.h"
#include "scoremanager.h"


SudokuMainWindow::SudokuMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuWindow)
{
    ui->setupUi(this);
    createSudokuEdits();
    getDifficultyFile(Difficulty::Easy);

    _undoStack = new QUndoStack(this);

    ui->actionUndo->setShortcuts(QKeySequence::Undo);
    ui->actionRedo->setShortcuts(QKeySequence::Redo);

    connect(ui->actionUndo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(ui->actionRedo, SIGNAL(triggered()), this, SLOT(redo()));
    connect(ui->actionNewGame, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionControls, SIGNAL(triggered()), this, SLOT(displayControls()));
    connect(ui->actionView_Scores, SIGNAL(triggered()), this, SLOT(displayScores()));

    ui->actionUndo->setIcon(QIcon(":/assets/undo-icon.png"));
    ui->actionRedo->setIcon(QIcon(":/assets/redo-icon.png"));
    ui->mainToolBar->addAction(ui->actionUndo);
    ui->mainToolBar->addAction(ui->actionRedo);

    connect(ui->newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));

    QStringList items;
    items.append(tr("Easy"));
    items.append(tr("Medium"));
    items.append(tr("Hard"));
    items.append(tr("Insane"));
    ui->difficultyComboBox->addItems(items);

    connect(ui->difficultyComboBox, SIGNAL(activated(int)),this,SLOT(changeDifficulty(int)));

    ui->clockTimeEdit->setDisplayFormat("hh:mm:ss");
    ui->clockTimeEdit->setReadOnly(true);


    newGame(Difficulty::Easy);
}

void SudokuMainWindow::closeEvent(QCloseEvent *event) {
    quit();
    event->ignore();
}

void SudokuMainWindow::displayControls() {
    QMessageBox::information(this, tr("Controls"), tr("Use UP, DOWN, LEFT, RIGHT keys to move the cursor and the numpad to write numbers.\n\nYou can undo and redo your plays by using Ctrl+Z and Ctrl+Shift+Z.\n\nInvalid moves will not be displayed."));
}

void SudokuMainWindow::displayScores() {
    QMessageBox::information(this, tr("Scores"), _scores);
}

void SudokuMainWindow::undo() {
    _undoStack->undo();
    ui->displayer->repaint();
}

void SudokuMainWindow::redo() {
    _undoStack->redo();
    ui->displayer->repaint();
}

void SudokuMainWindow::createSudokuEdits() {
    QGridLayout * inputLayout = new QGridLayout(ui->inputWidget);

    inputLayout->setHorizontalSpacing(0);
    inputLayout->setVerticalSpacing(0);
    inputLayout->setMargin(0);

    for(int y = 0; y < 9; y++) {
        for(int x = 0; x < 9; x++) {
            SudokuEdit * edit = new SudokuEdit(this, x, y);
            connect(edit, SIGNAL(changed(SudokuEdit * const, int)), this, SLOT(playerMove(SudokuEdit * const, int)));
            connect(edit, SIGNAL(selected(const SudokuEdit * const)), this, SLOT(cellSelected(const SudokuEdit * const)));
            connect(edit, SIGNAL(undoSignal()), this, SLOT(undo()));
            connect(edit, SIGNAL(directionSignal(int, int, int)), this, SLOT(direction(int, int, int)));
            connect(edit, SIGNAL(redoSignal()), this, SLOT(redo()));
            inputLayout->addWidget(edit, y, x);
            _inputs[x][y] = edit;
        }
    }

    ui->inputWidget->setLayout(inputLayout);
}

void SudokuMainWindow::direction(int x, int y, int key) {
    int newX = x;
    int newY = y;
    if(key == Qt::Key_Up)
        newY--;
    if(key == Qt::Key_Down)
        newY++;
    if(key == Qt::Key_Left)
        newX--;
    if(key == Qt::Key_Right)
        newX++;

    newX %= 9;
    newY %= 9;

    if(newX < 0)
        newX += 9;
    if(newY < 0)
        newY += 9;

    SudokuEdit * edit = _inputs[newX][newY];
    edit->setFocus();
    cellSelected(edit);

}

void SudokuMainWindow::cellSelected(const SudokuEdit * const edit ) {
    ui->displayer->setErrorOnCurrentCell(false);
    ui->displayer->setSelectedCell(-1, -1);
    ui->displayer->setSelectedCell(edit->x(), edit->y());
}

void SudokuMainWindow::showVictoryBox() {
    QTime finalTime = ui->clockTimeEdit->time();

    bool ok;
    QString text = QInputDialog::getText(this, tr("Please enter your name"),
                                         tr("User name:"), QLineEdit::Normal,
                                         "", &ok);
    if(ok && !text.isEmpty()) {
        _scores.putScore(text, finalTime);
        displayScores();
        newGame();
    }

}

void SudokuMainWindow::quit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Quit ?"), tr("Do you really wish to quit ?"), QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        qApp->quit();
    }


}

void SudokuMainWindow::playerMove(SudokuEdit * const edit, int val) {
    PlayCommand * command = new PlayCommand(_level->model(), edit->x(), edit->y(), val);

    if(_level->controller()->isValidMove(command)) {
        _undoStack->push(command);
        ui->displayer->setErrorOnCurrentCell(false);
        if (_level->controller()->hasWon()) {
            showVictoryBox();
        }
    } else {
        ui->displayer->setErrorOnCurrentCell(true);
    }

    ui->displayer->repaint();
    edit->setText("");
}


void SudokuMainWindow::changeDifficulty(int enumValue)
{
    newGame((Difficulty)enumValue);
}

void SudokuMainWindow::newGame(Difficulty diff)
{
    if(_level)
        delete _level;
    _undoStack->clear();
    _level = new Level(diff);
    ui->displayer->setModel(_level->model());
    ui->displayer->repaint();
    if (_timer)
    {
        delete _timer;
    }
    ui->clockTimeEdit->setTime(QTime(0,0,0));
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    _timer->start(1000);
}

void SudokuMainWindow::updateTimer()
{
    QTime newTime = ui->clockTimeEdit->time().addSecs(1);
    ui->clockTimeEdit->setTime(newTime);
}

void SudokuMainWindow::newGame()
{
    newGame(_level->difficulty());
}


SudokuMainWindow::~SudokuMainWindow()
{
    delete ui;
}
