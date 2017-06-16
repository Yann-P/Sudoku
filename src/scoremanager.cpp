#include <scoremanager.h>


ScoreManager::ScoreManager() {
    load();
}


void ScoreManager::putScore(const QString & name, QTime score) {
    _scores[name] = score;
    save();
}

bool ScoreManager::scoreExists(const QString & name) const {
    return _scores.contains(name);
}

// private

void ScoreManager::load() {
    QFile file("scores.dat");
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        in >> _scores;
        file.close();
    }
}

void ScoreManager::save() {
    QFile file("scores.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << _scores;
        file.close();
    }
}

ScoreManager::operator QString() {

    QString res = "";
    for(std::pair<const QString &, const QTime & > score: _scores.toStdMap()) {
        res += QString(QObject::tr("%1 -> %2h %3m %4s \n")).arg(score.first ).arg(score.second.hour()).arg(score.second.minute()).arg(score.second.second());
    }

    if(res == "")
        res = QObject::tr("No score yet.");

    return res;
}
