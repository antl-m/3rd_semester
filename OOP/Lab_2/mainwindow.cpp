#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
