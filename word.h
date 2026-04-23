#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QDateTime>
#include <cmath>

struct Word {
    QString foreign;
    QString native;
    double halfLife; // In days
    qint64 lastSeen; // Unix timestamp

    // Duolingo HLR Formula: p = 2^(-delta / h)
    double getProbability() const {
        double delta = (QDateTime::currentSecsSinceEpoch() - lastSeen) / 86400.0;
        return std::pow(2.0, -delta / halfLife);
    }
};

#endif // WORD_H