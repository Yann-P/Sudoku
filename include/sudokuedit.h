#ifndef SUDOKUEDIT_H
#define SUDOKUEDIT_H
#include <QWidget>
#include <QLineEdit>
#include <QEvent>

/*
 * @brief Sous classe de QLineEdit qui gère les entrées utilisateur
 *
 */

class SudokuEdit : public QLineEdit {
    Q_OBJECT
public:
    SudokuEdit(QWidget * const, int, int);
    int x() const;
    int y() const;

signals:
    void selected(const SudokuEdit * const);
    void changed(SudokuEdit * const, int);
    void undoSignal();
    void redoSignal();
    void directionSignal(int, int, int);

private:
    int _x;
    int _y;

    void focusInEvent(QFocusEvent *) override;
    void keyPressEvent(QKeyEvent * evt) override;


private slots:
    void onTextChanged(const QString &);





};


#endif // SUDOKUEDIT_H
