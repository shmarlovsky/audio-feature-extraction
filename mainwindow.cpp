#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "algorithms.h"
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
    //vector <Real> audio =
            loadAudio(qFileName.toStdString());


    vector <float> xStd(audioBuffer.size());

    for (int i=0; i<audioBuffer.size(); i++)
    {
        xStd[i] = i/44100.0;

    }
    drawGraphics(ui->signalWidjet,xStd, audioBuffer);
    }
}

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
        qDebug() <<"WindowStartPos:" << windowStartPosition;
        //vector<Real> window = makeWindow(audio, windowStartPosition);
        //drawGraphics(ui->mfccWidget, window);

        vector<Real> window;
        int windowSize = 300;
        for (int i=0; i<windowSize; i++)
        {
            window[i]=audioBuffer[windowStartPosition*44100];
        }
        vector <float> xStd(audioBuffer.size());

        for (int i=0; i<window.size(); i++)
        {
            xStd[i] = i/44100.0;

        }
       drawGraphics(ui->mfccWidget,xStd, window);
    }



void MainWindow::on_takeWindowLineEdit_returnPressed()
{

}
