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

//load audiofile
void MainWindow::on_actionOpen_triggered()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)")); if(qFileName!=NULL)
    {

        obj1.loadAudio(qFileName.toStdString());

        int bufferSize = obj1.getAudioBuffer().size();
        vector <float> x(bufferSize);

        for (int i=0; i<bufferSize; i++)
        {
            x[i] = i/44100.0;

        }

        drawGraphics(ui->signalWidget,x, obj1.getAudioBuffer());

    }
}

// displaying vector on specified Plot
void MainWindow::drawGraphics(QCustomPlot *customPlot, vector<float> xStd, vector <Real> audio)
{
    customPlot->addGraph();
    customPlot->graph(0)->setData(xStd, audio);
    customPlot->xAxis->setRange(-2,20, Qt::AlignLeft);
    customPlot->yAxis->setRange(-2,2);

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    customPlot->axisRect()->setRangeZoom(Qt::Horizontal);
    customPlot->graph(0)->rescaleAxes();
    //connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    //connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

}

void MainWindow::on_takeWindowButton_clicked()
{

    float  windowStartPosition = ui->takeWindowLineEdit->text().toFloat();
    float inputSize = ui->windowSizeLineEdit->text().toFloat();
    qDebug() <<"WindowStartPos: " << windowStartPosition;
    qDebug() <<"InputSize: " << inputSize;
    obj1.makeFrame(windowStartPosition,inputSize);

    int windowSize = obj1.getAudioBuffer().size();
    vector <float> x(windowSize);

    for (int i=0; i<windowSize; i++)
    {
        x[i] = i/44100.0;

    }

    drawGraphics(ui->mfccWidget,x, obj1.getFrame());

}


void MainWindow::on_takeWindowLineEdit_returnPressed()
{

}

void MainWindow::on_calculateSpectrumButton_clicked()
{
    obj1.calculateSpectrum();
    int specSize = obj1.getSpectrum().size();
    vector<float> x(specSize);
    for (int i=0; i<specSize; i++)
    {
        x[i] = i/44100.0;

    }
    drawGraphics(ui->mfccWidget,x,obj1.getSpectrum());

}

void MainWindow::on_calculateMFCCButton_clicked()
{
    obj1.calculateMFCC();
    int mfccSize = obj1.getMfcc().size();
    vector<float> x(mfccSize);
    for (int i=0; i<mfccSize; i++)
    {
        x[i] = i;

    }
    drawGraphics(ui->mfccWidget,x,obj1.getMfcc());
}
