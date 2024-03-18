/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *group_Move;
    QLineEdit *lineEdit_MoveX;
    QLineEdit *lineEdit_MoveY;
    QLineEdit *lineEdit_MoveZ;
    QPushButton *button_Move;
    QLabel *label_MoveX;
    QLabel *label_MoveY;
    QLabel *label_MoveZ;
    QGroupBox *group_Move_2;
    QLineEdit *lineEdit_ScaleX;
    QLineEdit *lineEdit_ScaleY;
    QLineEdit *lineEdit_ScaleZ;
    QPushButton *button_Scale;
    QLabel *label_ScaleX;
    QLabel *label_ScaleY;
    QLabel *label_ScaleZ;
    QGroupBox *group_Move_3;
    QLineEdit *lineEdit_TurnX;
    QLineEdit *lineEdit_TurnY;
    QLineEdit *lineEdit_TurnZ;
    QPushButton *button_Turn;
    QLabel *label_TurnX;
    QLabel *label_TurnY;
    QLabel *label_TurnZ;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 709);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(30, 20, 941, 461));
        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(30, 510, 941, 121));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        group_Move = new QGroupBox(horizontalLayoutWidget);
        group_Move->setObjectName("group_Move");
        QFont font;
        font.setPointSize(13);
        group_Move->setFont(font);
        group_Move->setAlignment(Qt::AlignCenter);
        lineEdit_MoveX = new QLineEdit(group_Move);
        lineEdit_MoveX->setObjectName("lineEdit_MoveX");
        lineEdit_MoveX->setGeometry(QRect(20, 60, 70, 20));
        lineEdit_MoveY = new QLineEdit(group_Move);
        lineEdit_MoveY->setObjectName("lineEdit_MoveY");
        lineEdit_MoveY->setGeometry(QRect(115, 60, 70, 20));
        lineEdit_MoveZ = new QLineEdit(group_Move);
        lineEdit_MoveZ->setObjectName("lineEdit_MoveZ");
        lineEdit_MoveZ->setGeometry(QRect(210, 60, 70, 20));
        button_Move = new QPushButton(group_Move);
        button_Move->setObjectName("button_Move");
        button_Move->setGeometry(QRect(20, 83, 260, 28));
        QFont font1;
        font1.setPointSize(15);
        button_Move->setFont(font1);
        label_MoveX = new QLabel(group_Move);
        label_MoveX->setObjectName("label_MoveX");
        label_MoveX->setGeometry(QRect(20, 38, 45, 16));
        label_MoveX->setFont(font);
        label_MoveY = new QLabel(group_Move);
        label_MoveY->setObjectName("label_MoveY");
        label_MoveY->setGeometry(QRect(120, 38, 45, 16));
        label_MoveY->setFont(font);
        label_MoveZ = new QLabel(group_Move);
        label_MoveZ->setObjectName("label_MoveZ");
        label_MoveZ->setGeometry(QRect(210, 38, 45, 16));
        label_MoveZ->setFont(font);

        horizontalLayout->addWidget(group_Move);

        group_Move_2 = new QGroupBox(horizontalLayoutWidget);
        group_Move_2->setObjectName("group_Move_2");
        group_Move_2->setFont(font);
        group_Move_2->setAlignment(Qt::AlignCenter);
        lineEdit_ScaleX = new QLineEdit(group_Move_2);
        lineEdit_ScaleX->setObjectName("lineEdit_ScaleX");
        lineEdit_ScaleX->setGeometry(QRect(20, 60, 70, 20));
        lineEdit_ScaleY = new QLineEdit(group_Move_2);
        lineEdit_ScaleY->setObjectName("lineEdit_ScaleY");
        lineEdit_ScaleY->setGeometry(QRect(115, 60, 70, 20));
        lineEdit_ScaleZ = new QLineEdit(group_Move_2);
        lineEdit_ScaleZ->setObjectName("lineEdit_ScaleZ");
        lineEdit_ScaleZ->setGeometry(QRect(210, 60, 70, 20));
        button_Scale = new QPushButton(group_Move_2);
        button_Scale->setObjectName("button_Scale");
        button_Scale->setGeometry(QRect(20, 83, 260, 28));
        button_Scale->setFont(font1);
        label_ScaleX = new QLabel(group_Move_2);
        label_ScaleX->setObjectName("label_ScaleX");
        label_ScaleX->setGeometry(QRect(20, 38, 45, 16));
        label_ScaleX->setFont(font);
        label_ScaleY = new QLabel(group_Move_2);
        label_ScaleY->setObjectName("label_ScaleY");
        label_ScaleY->setGeometry(QRect(120, 38, 45, 16));
        label_ScaleY->setFont(font);
        label_ScaleZ = new QLabel(group_Move_2);
        label_ScaleZ->setObjectName("label_ScaleZ");
        label_ScaleZ->setGeometry(QRect(210, 38, 45, 16));
        label_ScaleZ->setFont(font);

        horizontalLayout->addWidget(group_Move_2);

        group_Move_3 = new QGroupBox(horizontalLayoutWidget);
        group_Move_3->setObjectName("group_Move_3");
        group_Move_3->setFont(font);
        group_Move_3->setAlignment(Qt::AlignCenter);
        lineEdit_TurnX = new QLineEdit(group_Move_3);
        lineEdit_TurnX->setObjectName("lineEdit_TurnX");
        lineEdit_TurnX->setGeometry(QRect(20, 60, 70, 20));
        lineEdit_TurnY = new QLineEdit(group_Move_3);
        lineEdit_TurnY->setObjectName("lineEdit_TurnY");
        lineEdit_TurnY->setGeometry(QRect(115, 60, 70, 20));
        lineEdit_TurnZ = new QLineEdit(group_Move_3);
        lineEdit_TurnZ->setObjectName("lineEdit_TurnZ");
        lineEdit_TurnZ->setGeometry(QRect(210, 60, 70, 20));
        button_Turn = new QPushButton(group_Move_3);
        button_Turn->setObjectName("button_Turn");
        button_Turn->setGeometry(QRect(20, 83, 260, 28));
        button_Turn->setFont(font1);
        label_TurnX = new QLabel(group_Move_3);
        label_TurnX->setObjectName("label_TurnX");
        label_TurnX->setGeometry(QRect(20, 38, 45, 16));
        label_TurnX->setFont(font);
        label_TurnY = new QLabel(group_Move_3);
        label_TurnY->setObjectName("label_TurnY");
        label_TurnY->setGeometry(QRect(120, 38, 45, 16));
        label_TurnY->setFont(font);
        label_TurnZ = new QLabel(group_Move_3);
        label_TurnZ->setObjectName("label_TurnZ");
        label_TurnZ->setGeometry(QRect(210, 38, 45, 16));
        label_TurnZ->setFont(font);

        horizontalLayout->addWidget(group_Move_3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        menu = new QMenu(menuBar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addSeparator();
        menu->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "OOP lab1 Oolonge", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        group_Move->setTitle(QCoreApplication::translate("MainWindow", "Move", nullptr));
        lineEdit_MoveX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_MoveY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_MoveZ->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        button_Move->setText(QCoreApplication::translate("MainWindow", "Move", nullptr));
        label_MoveX->setText(QCoreApplication::translate("MainWindow", "dx:", nullptr));
        label_MoveY->setText(QCoreApplication::translate("MainWindow", "dy:", nullptr));
        label_MoveZ->setText(QCoreApplication::translate("MainWindow", "dz:", nullptr));
        group_Move_2->setTitle(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        lineEdit_ScaleX->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        lineEdit_ScaleY->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        lineEdit_ScaleZ->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        button_Scale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        label_ScaleX->setText(QCoreApplication::translate("MainWindow", "kx:", nullptr));
        label_ScaleY->setText(QCoreApplication::translate("MainWindow", "ky:", nullptr));
        label_ScaleZ->setText(QCoreApplication::translate("MainWindow", "kz:", nullptr));
        group_Move_3->setTitle(QCoreApplication::translate("MainWindow", "Turn", nullptr));
        lineEdit_TurnX->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_TurnY->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lineEdit_TurnZ->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        button_Turn->setText(QCoreApplication::translate("MainWindow", "Turn", nullptr));
        label_TurnX->setText(QCoreApplication::translate("MainWindow", "ox:", nullptr));
        label_TurnY->setText(QCoreApplication::translate("MainWindow", "oy:", nullptr));
        label_TurnZ->setText(QCoreApplication::translate("MainWindow", "oz:", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
