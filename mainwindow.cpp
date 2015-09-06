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
    ui->takeWindowButton->setEnabled(false);
    ui->calculateSpectrumButton->setEnabled(false);
    ui->calculateMFCCButton->setEnabled(false);
    ui->calculateGFCCButton->setEnabled(false);
    ui->exportTofileButton->setEnabled(false);
    ui->calculateAllButton->setEnabled(false);
    ui->calculateWaveletButton->setEnabled(false);


    //////// temp wavelet//////////////
//    int size = 2000;
//    vector <float> x(size);
//    vector <float> sinVect(size);
//    vector <float> result(size);
//    int i;
//    float k=-10;
//    for (i=0; i<size; i++)
//    {
//        x[i] = k;
//        sinVect[i] = sin(2*3.14*k);
//        k+=0.01;
//    }

//    std::vector <float> wavelet(size);
//    //int g=3;
//    for (int i=0; i<size; i++)
//    {
//        // morlet
//        wavelet[i] = (1-x[i]*x[i])*exp(-x[i]*x[i]/2.);
//        // wave
//        //wavelet[i] = x[i]*exp(-x[i]*x[i]/2.);

//    }

//    for (int i=0; i<size; i++)
//    {

//        result[i] = sinVect[i]*wavelet[size- i];
//    }

//    drawGraphics(ui->signalWidget,x, wavelet);
//    drawGraphics(ui->mfccWidget,x,result);

    ////////////////////////////////////////////////

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

        obj1.setFileName(qFileName.toStdString());
        obj1.loadAudio(obj1.getFileName());

        int bufferSize = obj1.getAudioBuffer().size();
        vector <float> x(bufferSize);

        for (int i=0; i<bufferSize; i++)
        {
            x[i] = i/44100.0;

        }

        drawGraphics(ui->signalWidget, x, obj1.getAudioBuffer());

        if(obj1.getAudioBuffer().size() != 0)
        {
            ui->takeWindowButton->setEnabled(true);
            ui->calculateAllButton->setEnabled(true);
            ui->calculateWaveletButton->setEnabled(true);
            ui->exportTofileButton->setEnabled(true);

        }
    }
}

// displaying vector on specified Plot
void MainWindow::drawGraphics(QCustomPlot *customPlot, vector<float> xStd, vector <Real> audio)
{
    customPlot->addGraph();

    customPlot->graph(0)->setData(xStd, audio);

    customPlot->xAxis->setRange(-10,10, Qt::AlignLeft);
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
    int inputSize = ui->windowSizeLineEdit->text().toInt();

    qDebug() <<"WindowStartPos: " << windowStartPosition;
    
    statusBar()->showMessage("WindowStartPosition: ", windowStartPosition);
    qDebug() <<"InputSize: " << inputSize;
    //obj1.makeFrame(windowStartPosition,inputSize);
    obj1.frameCutter(inputSize);

    int windowSize = obj1.getFrame().size();
   // qDebug() <<
    vector <float> x(windowSize);

    for (int i=0; i<windowSize; i++)
    {
        x[i] = i/44100.0;

    }

    if(obj1.getFrame().size() >= 1)
    {
        ui->calculateSpectrumButton->setEnabled(true);

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
        x[i] = i/100.0;

    }

    if(obj1.getSpectrum().size() >= 1)
    {
        ui->calculateMFCCButton->setEnabled(true);
        ui->calculateGFCCButton->setEnabled(true);
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

void MainWindow::on_calculateGFCCButton_clicked()
{
    obj1.calculateGFCC();
    int gfccSize = obj1.getGfcc().size();
    vector<float> x(gfccSize);
    for (int i=0; i<gfccSize; i++)
    {
        x[i] = i;

    }
    drawGraphics(ui->mfccWidget,x,obj1.getGfcc());
}

void MainWindow::on_calculateAllButton_clicked()
{
    int inputSize = ui->windowSizeLineEdit->text().toInt();
    qDebug() << "inputSize: " << inputSize << endl;
    if(inputSize==0)
        inputSize=1024;
    obj1.calculateWholeAudio(inputSize);

    int mfccSize = obj1.getMfcc().size();
    vector<float> x(mfccSize);
    for (int i=0; i<mfccSize; i++)
    {
        x[i] = i;

    }


    drawGraphics(ui->mfccWidget,x,obj1.getMfcc());


}

void MainWindow::on_calculateWaveletButton_clicked()
{
    obj1.calculateWavelet();
    //int waveSize = obj1.getWaveletResult().size();
    int waveSize = 13;
    vector<float> result(waveSize);
    vector<float> resultFloat(waveSize);
    //result = obj1.getWaveletResult();
    vector<float> x(waveSize);
    for (int i=0; i<waveSize; i++)
    {
        x[i] = i;
        result[i]=(float)obj1.getWaveletResult()[i];
        //resultFloat[i]=(float)result[i];
    }

    for(int i=0; i<13; i++)
    {

    }
    drawGraphics(ui->mfccWidget,x,result);
}

void MainWindow::on_exportTofileButton_clicked()
{
    obj1.exportToFile();
}

void MainWindow::on_openButton_clicked()
{
    on_actionOpen_triggered();
}
