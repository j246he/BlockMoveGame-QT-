#ifndef BLOCKMOVEGAME_H
#define BLOCKMOVEGAME_H

#include <QWidget>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QtGlobal>
#include <QTime>
#include <QDebug>
#include <QList>
#include <QString>
#include <QObject>
#include <QMouseEvent>
#include <QMessageBox>

namespace Ui {
class BlockMoveGame;
}

class BlockMoveGame : public QWidget
{
    Q_OBJECT

public:
    explicit BlockMoveGame(QWidget *parent = 0);
    ~BlockMoveGame();
    int row;
    int column;
    int boxNum;
    QList<QPushButton*> ButtonList;

private slots:
    void on_ButtonExit_clicked();

    void on_ButtonStart_clicked();

    void dealButton();

private:
    Ui::BlockMoveGame *ui;
    void changeBlock(int,int);
    bool blankIsNeighbour(int blank,int i);
    bool gameFinish();
    void buttonClick(QPushButton *);
    int timerId;

protected:
    void timerEvent(QTimerEvent *event);

};

#endif // BLOCKMOVEGAME_H
