#include "difficulty.h"
#include <QString>

QString getDifficultyFile(Difficulty difficulty)
{
    switch (difficulty)
    {
    case Difficulty::Easy:
        return "easy.txt";
    case Difficulty::Medium:
        return "medium.txt";
    case Difficulty::Hard:
        return "hard.txt";
    default:
        return "insane.txt";
    }
}

