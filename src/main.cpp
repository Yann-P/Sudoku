#include "sudokumainwindow.h"
#include <QApplication>
#include <QtWidgets>
int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(":/langs/sudoku_" + locale);
    app.installTranslator(&translator);

    SudokuMainWindow w;

    w.setWindowIcon(QIcon(":/assets/icon.png"));
    w.show();
    return app.exec();
}
