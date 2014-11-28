#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algorithms.h"

using namespace std;
using namespace essentia;
using namespace essentia::standard;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));
    if(qFileName!=NULL)
    {

    obj1.loadAudio(qFileName.toStdString());

    int bufferSize = obj1.getAudioBuffer().size();
    vector <float> xStd(bufferSize);

    for (int i=0; i<bufferSize; i++)
    {
        xStd[i] = i/44100.0;

    }

    drawGraphics(ui->signalWidget,xStd, obj1.getAudioBuffer());

    }
}

// displaying vector on specified Plot
void MainWindow::drawGraphics(QCustomPlot *customPlot, vector<float> xStd, vector <Real> audio)
{

    customPlot->addGraph();
    customPlot->graph(0)->setData(xStd, audio);
    customPlot->xAxis->setRange(-2,20);
    customPlot->yAxis->setRange(-2,2);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::on_takeWindowButton_clicked()
{

        float  windowStartPosition = ui->takeWindowLineEdit->text().toFloat();
        float inputSize = ui->windowSizeLineEdit->text().toFloat();
        qDebug() <<"WindowStartPos: " << windowStartPosition;
         qDebug() <<"InputSize: " << inputSize;
        obj1.makeFrame(windowStartPosition,inputSize);

        int windowSize = obj1.getAudioBuffer().size();
        vector <float> xStd2(windowSize);

        for (int i=0; i<windowSize; i++)
        {
            xStd2[i] = i/44100.0;

        }

        drawGraphics(ui->mfccWidget,xStd2 ,obj1.getFrame());

    }


void MainWindow::on_takeWindowLineEdit_returnPressed()
{

}
