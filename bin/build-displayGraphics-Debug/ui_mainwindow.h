/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *exportTofileButton;
    QLineEdit *windowSizeLineEdit;
    QLabel *windowSizeLabel;
    QLabel *startPosLabel;
    QPushButton *calculateAllButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *takeWindowButton;
    QPushButton *calculateMFCCButton;
    QVBoxLayout *verticalLayout;
    QCustomPlot *mfccWidget;
    QVBoxLayout *signalLayout;
    QCustomPlot *signalWidget;
    QLineEdit *takeWindowLineEdit;
    QPushButton *calculateGFCCButton;
    QPushButton *calculateWaveletButton;
    QPushButton *calculateSpectrumButton;
    QPushButton *openButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(612, 409);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        exportTofileButton = new QPushButton(centralWidget);
        exportTofileButton->setObjectName(QStringLiteral("exportTofileButton"));

        gridLayout->addWidget(exportTofileButton, 1, 7, 1, 1);

        windowSizeLineEdit = new QLineEdit(centralWidget);
        windowSizeLineEdit->setObjectName(QStringLiteral("windowSizeLineEdit"));

        gridLayout->addWidget(windowSizeLineEdit, 2, 1, 1, 1);

        windowSizeLabel = new QLabel(centralWidget);
        windowSizeLabel->setObjectName(QStringLiteral("windowSizeLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(windowSizeLabel->sizePolicy().hasHeightForWidth());
        windowSizeLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(windowSizeLabel, 1, 1, 1, 1);

        startPosLabel = new QLabel(centralWidget);
        startPosLabel->setObjectName(QStringLiteral("startPosLabel"));

        gridLayout->addWidget(startPosLabel, 1, 0, 1, 1);

        calculateAllButton = new QPushButton(centralWidget);
        calculateAllButton->setObjectName(QStringLiteral("calculateAllButton"));

        gridLayout->addWidget(calculateAllButton, 1, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(326, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 7, 1, 1);

        takeWindowButton = new QPushButton(centralWidget);
        takeWindowButton->setObjectName(QStringLiteral("takeWindowButton"));

        gridLayout->addWidget(takeWindowButton, 1, 3, 1, 1);

        calculateMFCCButton = new QPushButton(centralWidget);
        calculateMFCCButton->setObjectName(QStringLiteral("calculateMFCCButton"));

        gridLayout->addWidget(calculateMFCCButton, 1, 5, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        mfccWidget = new QCustomPlot(centralWidget);
        mfccWidget->setObjectName(QStringLiteral("mfccWidget"));
        sizePolicy.setHeightForWidth(mfccWidget->sizePolicy().hasHeightForWidth());
        mfccWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(mfccWidget);


        gridLayout->addLayout(verticalLayout, 4, 0, 1, 8);

        signalLayout = new QVBoxLayout();
        signalLayout->setSpacing(6);
        signalLayout->setObjectName(QStringLiteral("signalLayout"));
        signalWidget = new QCustomPlot(centralWidget);
        signalWidget->setObjectName(QStringLiteral("signalWidget"));
        sizePolicy.setHeightForWidth(signalWidget->sizePolicy().hasHeightForWidth());
        signalWidget->setSizePolicy(sizePolicy);

        signalLayout->addWidget(signalWidget);


        gridLayout->addLayout(signalLayout, 0, 0, 1, 8);

        takeWindowLineEdit = new QLineEdit(centralWidget);
        takeWindowLineEdit->setObjectName(QStringLiteral("takeWindowLineEdit"));

        gridLayout->addWidget(takeWindowLineEdit, 2, 0, 1, 1);

        calculateGFCCButton = new QPushButton(centralWidget);
        calculateGFCCButton->setObjectName(QStringLiteral("calculateGFCCButton"));

        gridLayout->addWidget(calculateGFCCButton, 2, 5, 1, 1);

        calculateWaveletButton = new QPushButton(centralWidget);
        calculateWaveletButton->setObjectName(QStringLiteral("calculateWaveletButton"));

        gridLayout->addWidget(calculateWaveletButton, 2, 6, 1, 1);

        calculateSpectrumButton = new QPushButton(centralWidget);
        calculateSpectrumButton->setObjectName(QStringLiteral("calculateSpectrumButton"));

        gridLayout->addWidget(calculateSpectrumButton, 2, 3, 1, 1);

        openButton = new QPushButton(centralWidget);
        openButton->setObjectName(QStringLiteral("openButton"));

        gridLayout->addWidget(openButton, 3, 5, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 612, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        exportTofileButton->setText(QApplication::translate("MainWindow", "ExportToFIle", 0));
        windowSizeLabel->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\276\320\272\320\275\320\260:", 0));
        startPosLabel->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\207. \320\277\320\276\320\267\320\270\321\206\320\270\321\217:", 0));
        calculateAllButton->setText(QApplication::translate("MainWindow", "Calc All", 0));
        takeWindowButton->setText(QApplication::translate("MainWindow", "Take Window", 0));
        calculateMFCCButton->setText(QApplication::translate("MainWindow", "Calc MFCC", 0));
        calculateGFCCButton->setText(QApplication::translate("MainWindow", "Calc GFCC", 0));
        calculateWaveletButton->setText(QApplication::translate("MainWindow", "CalcWave", 0));
        calculateSpectrumButton->setText(QApplication::translate("MainWindow", "Calc Spectrum", 0));
        openButton->setText(QApplication::translate("MainWindow", "Open", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
