#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "algorithms.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGraphics(QCustomPlot *customPlot, std::vector<float>, std::vector<essentia::Real>);

private slots:
    void on_actionOpen_triggered();

    void on_takeWindowButton_clicked();

    void on_takeWindowLineEdit_returnPressed();


    void on_calculateSpectrumButton_clicked();

    void on_calculateMFCCButton_clicked();

private:
    Ui::MainWindow *ui;
    AudioProcess obj1;
};

#endif // MAINWINDOW_H
