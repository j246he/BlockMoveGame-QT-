#include "blockmovegame.h"
#include "ui_blockmovegame.h"
#include <QTimerEvent>

BlockMoveGame::BlockMoveGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlockMoveGame)
{
    ui->setupUi(this);
    row=3;
    column=3;
    boxNum=row*column;//can change this for more blocks

    ui->MystackedWidget->setCurrentWidget(ui->StartPage);

    //connect(ui->ButtonExit,&QPushButton::click,this,&BlockMoveGame::close);
    ui->logo->setText(QString("<center><h1>Block Move Game</h1></center>"));
    ui->winLabel->setText(QString("<center><h1>Win!</h1></center>"));


    ButtonList << ui->Button1
               << ui->Button2
               << ui->Button3
               << ui->Button4
               << ui->Button5
               << ui->Button6
               << ui->Button7
               << ui->Button8
               << ui->Button9;

    connect(ui->Button1,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button2,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button3,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button4,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button5,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button6,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button7,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button8,&QPushButton::clicked,this,&BlockMoveGame::dealButton);
    connect(ui->Button9,&QPushButton::clicked,this,&BlockMoveGame::dealButton);

}

BlockMoveGame::~BlockMoveGame()
{
    delete ui;
}

void BlockMoveGame::buttonClick(QPushButton *b)
{
    int blank = 0;
    int j;
    bool ok;
    for(int i=0;i<boxNum;i++){
        if(ButtonList[i]->text().toInt(&ok,10)==boxNum)
        {
            blank=i;
            break;
        }
    }

    for(int i=0;i<boxNum;i++)
    {
        if(b->text()==ButtonList[i]->text())
        {
            j=i;
            break;
        }
        //qDebug()<<b->text()<<ButtonList[i]->text();
    }

    if (blankIsNeighbour(blank,j)==true) {
        changeBlock(blank,j);
        ButtonList[j]->hide();
        ButtonList[blank]->show();
    }
    if(gameFinish()==true)
    {
        ui->MystackedWidget->setCurrentWidget(ui->WinPage);
        timerId = startTimer(1000);
    }
}

void BlockMoveGame::on_ButtonStart_clicked()
{
    ui->MystackedWidget->setCurrentWidget(ui->PlayPage);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    for(int a=0;a<boxNum;a++){
        int i=qrand()%9;
        int j=qrand()%9;
        //qDebug()<<i<<j;
        changeBlock(i,j);
    }

    for(int i=0;i<boxNum;i++)
    {
        bool ok;
        if(ButtonList[i]->text().toInt(&ok,10)==boxNum)
        {
            ButtonList[i]->hide();
        }
    }

}
void BlockMoveGame::changeBlock(int i,int j){
    QString a=ButtonList[i]->text();
    QString b=ButtonList[j]->text();
    ButtonList[i]->setText(b);
    ButtonList[j]->setText(a);
}

void BlockMoveGame::on_ButtonExit_clicked()
{
    BlockMoveGame::close();
}
bool BlockMoveGame::blankIsNeighbour(int blank,int i){
    if(blank-i==1)return true;
    else if(i-blank==1)return true;
    else if(blank-i==column)return true;
    else if(i-blank==column)return true;
    else{
        QMessageBox::warning(this,"Warning!","you can't move this block!",
                                       QMessageBox::Ok,
                                       QMessageBox::NoButton);
        return false;
    }
}
bool BlockMoveGame::gameFinish()
{
    bool ok;
    for(int i=0;i<boxNum;i++) {
        if(ButtonList[i]->text().toInt(&ok,10)!=(i+1)) {
            return false;
        }
    }
    return true;
}

void BlockMoveGame::dealButton()
{
    QObject *mySender = sender();
    QPushButton *p = (QPushButton *)mySender;
    if(p!=NULL)
    {
        buttonClick(p);
    }
}
void BlockMoveGame::timerEvent(QTimerEvent *event)
{
    static int sec=3;
    ui->myLabel->setText(
                QString("<center><h3>%1 seconds to automatically jump"
                        "</h3></center>").arg(sec--));
    if(sec==-1)
    {
        killTimer(timerId);
        sec=3;
        ui->MystackedWidget->setCurrentWidget(ui->StartPage);
    }
}




