#ifndef DIFFICULTY_H
#define DIFFICULTY_H
#include <QString>

enum Difficulty {
    Easy = 0,
    Medium,
    Hard,
    Insane
};

QString getDifficultyFile(Difficulty);

#endif // DIFFICULTY_H
