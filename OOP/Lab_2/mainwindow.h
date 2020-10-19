#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddButton_clicked();

    void on_AlarmBox_stateChanged(int arg1);

    void update_startedList(){
        return;
    }
private:
    QTimer* timer;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
