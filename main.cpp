#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "word.h"

class DuolingoApp : public QWidget {
    Q_OBJECT // Necessary for signals/slots if using separate files
public:
    DuolingoApp(QWidget *parent = nullptr) : QWidget(parent) {
        setupData();
        setupUI();
        updateTable();
    }

private:
    std::vector<Word> words;
    int currentPracticeIdx = -1;
    QTableWidget *statsTable;
    QLabel *questionLabel;
    QLineEdit *answerInput;

    void setupData() {
        words.push_back({"Bonjour", "Hello", 0.25, QDateTime::currentSecsSinceEpoch()});
        words.push_back({"Pain", "Bread", 0.25, QDateTime::currentSecsSinceEpoch()});
        words.push_back({"Eau", "Water", 0.25, QDateTime::currentSecsSinceEpoch()});
    }

    void setupUI() {
        setWindowTitle("Vocab HLR Tracker");
        resize(650, 450);
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Practice Bar
        QHBoxLayout *bar = new QHBoxLayout();
        questionLabel = new QLabel("Ready?");
        answerInput = new QLineEdit();
        QPushButton *subBtn = new QPushButton("Check");
        QPushButton *nextBtn = new QPushButton("Next Due");
        
        bar->addWidget(questionLabel);
        bar->addWidget(answerInput);
        bar->addWidget(subBtn);
        bar->addWidget(nextBtn);
        layout->addLayout(bar);

        // Stats Table
        statsTable = new QTableWidget(0, 3);
        statsTable->setHorizontalHeaderLabels({"Word", "Recall %", "Half-Life"});
        statsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        layout->addWidget(statsTable);

        connect(nextBtn, &QPushButton::clicked, this, &DuolingoApp::nextWord);
        connect(subBtn, &QPushButton::clicked, this, &DuolingoApp::checkAnswer);
    }

    void updateTable() {
        statsTable->setRowCount(0);
        for (const auto &w : words) {
            int r = statsTable->rowCount();
            statsTable->insertRow(r);
            statsTable->setItem(r, 0, new QTableWidgetItem(w.foreign));
            statsTable->setItem(r, 1, new QTableWidgetItem(QString::number(w.getProbability()*100, 'f', 1) + "%"));
            statsTable->setItem(r, 2, new QTableWidgetItem(QString::number(w.halfLife, 'f', 2) + "d"));
        }
    }

    void nextWord() {
        for (int i = 0; i < (int)words.size(); ++i) {
            if (words[i].getProbability() < 0.90) {
                currentPracticeIdx = i;
                questionLabel->setText("Translate: " + words[i].foreign);
                answerInput->clear();
                return;
            }
        }
        QMessageBox::information(this, "Success", "Your memory is currently 100% stable!");
    }

    void checkAnswer() {
        if (currentPracticeIdx == -1) return;
        Word &w = words[currentPracticeIdx];
        if (answerInput->text().trimmed().toLower() == w.native.toLower()) {
            w.halfLife *= 2.0;
        } else {
            w.halfLife *= 0.5;
            QMessageBox::warning(this, "Oops", "Correct answer: " + w.native);
        }
        w.lastSeen = QDateTime::currentSecsSinceEpoch();
        currentPracticeIdx = -1;
        updateTable();
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    DuolingoApp w;
    w.show();
    return a.exec();
}