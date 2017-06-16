#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QMap>
#include <QDataStream>
#include <QFile>
#include <iostream>
#include <map>
#include <utility>
#include <QTime>
#include <algorithm>


class ScoreManager {

public:
    ScoreManager();
    void putScore(const QString &, QTime);
    bool scoreExists(const QString &) const;
    operator QString();



private:
    QMap<QString, QTime> _scores;
    void load();
    void save();

};


#endif // SCOREMANAGER_H
