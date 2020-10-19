#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sound = new QSound(":/sounds/alarm.wav");

    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_startedList()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}


void MainWindow::on_AddButton_clicked()
{
    QDateTime add_datetime;
    if(ui->AlarmBox->isChecked()){
        add_datetime.setTime(ui->timeEdit->time());
        add_datetime.setDate(ui->dateEdit->date());
    }else{
        add_datetime = QDateTime::currentDateTime();
        add_datetime = add_datetime.addMSecs(ui->timeEdit->time().msecsSinceStartOfDay());
    }
    ui->AddedList->addItem(add_datetime.toString());
}

void MainWindow::on_AlarmBox_stateChanged(int arg1)
{
    ui->dateEdit->setEnabled(arg1);
}

void MainWindow::on_AddedList_itemDoubleClicked(QListWidgetItem *item)
{
    ui->StartedList->addItem(item->text());
    delete item;
}

void MainWindow::update_startedList(){
    bool timeout = false;
    for(int i=0; i<ui->StartedList->count(); ++i){
        auto cur_item = ui->StartedList->item(i);
        auto item_datetime = QDateTime::fromString(cur_item->text());
        if(QDateTime::currentDateTime() >= item_datetime){
            cur_item->setBackground(QColor("Red"));
            sound->play();
            timeout = true;
        }
    }
    if(!sound->isFinished()){
        if(!timeout)
            sound->stop();
    }
}
