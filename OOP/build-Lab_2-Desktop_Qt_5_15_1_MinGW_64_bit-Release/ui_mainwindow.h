/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *AddButton;
    QPushButton *DeleteButton;
    QTimeEdit *timeEdit;
    QDateEdit *dateEdit;
    QCheckBox *AlarmBox;
    QListWidget *AddedList;
    QListWidget *StartedList;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(652, 652);
        MainWindow->setMinimumSize(QSize(652, 652));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        AddButton = new QPushButton(centralwidget);
        AddButton->setObjectName(QString::fromUtf8("AddButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddButton->sizePolicy().hasHeightForWidth());
        AddButton->setSizePolicy(sizePolicy);
        AddButton->setMinimumSize(QSize(90, 90));
        AddButton->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(25);
        AddButton->setFont(font);
        AddButton->setAutoFillBackground(false);
        AddButton->setIconSize(QSize(20, 20));
        AddButton->setAutoDefault(false);
        AddButton->setFlat(false);

        verticalLayout->addWidget(AddButton);

        DeleteButton = new QPushButton(centralwidget);
        DeleteButton->setObjectName(QString::fromUtf8("DeleteButton"));
        sizePolicy.setHeightForWidth(DeleteButton->sizePolicy().hasHeightForWidth());
        DeleteButton->setSizePolicy(sizePolicy);
        DeleteButton->setMinimumSize(QSize(90, 90));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(20);
        DeleteButton->setFont(font1);

        verticalLayout->addWidget(DeleteButton);


        gridLayout->addLayout(verticalLayout, 1, 2, 1, 1);

        timeEdit = new QTimeEdit(centralwidget);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setMinimumSize(QSize(0, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(16);
        timeEdit->setFont(font2);

        gridLayout->addWidget(timeEdit, 0, 1, 1, 1);

        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setEnabled(false);
        dateEdit->setMinimumSize(QSize(0, 40));
        dateEdit->setFont(font2);
        dateEdit->setDateTime(QDateTime(QDate(2020, 1, 1), QTime(0, 0, 0)));
        dateEdit->setMinimumDateTime(QDateTime(QDate(2020, 1, 1), QTime(0, 0, 0)));

        gridLayout->addWidget(dateEdit, 0, 3, 1, 1);

        AlarmBox = new QCheckBox(centralwidget);
        AlarmBox->setObjectName(QString::fromUtf8("AlarmBox"));
        AlarmBox->setMinimumSize(QSize(0, 40));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(15);
        AlarmBox->setFont(font3);

        gridLayout->addWidget(AlarmBox, 0, 2, 1, 1);

        AddedList = new QListWidget(centralwidget);
        AddedList->setObjectName(QString::fromUtf8("AddedList"));
        AddedList->setFont(font3);

        gridLayout->addWidget(AddedList, 1, 1, 1, 1);

        StartedList = new QListWidget(centralwidget);
        StartedList->setObjectName(QString::fromUtf8("StartedList"));
        StartedList->setFont(font3);

        gridLayout->addWidget(StartedList, 1, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 652, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        AddButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MyTimer", nullptr));
        AddButton->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        DeleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        AlarmBox->setText(QCoreApplication::translate("MainWindow", "Alarm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
