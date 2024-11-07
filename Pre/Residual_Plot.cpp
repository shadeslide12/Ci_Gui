#include "Residual_Plot.h"

QT_CHARTS_USE_NAMESPACE

Residual_Plot::Residual_Plot():
        QChart(),series_con1(new QLineSeries(this)),
        series_con2(new QLineSeries(this)),
        axisX(new QValueAxis(this)),
        axisY1(new QValueAxis(this)),
        axisY2(new QValueAxis(this))
{
    setupResidualPlot();
}


void Residual_Plot::setupResidualPlot() {
    QFont titleFont("Arial",22,QFont::Bold);
    QColor titleColor(Qt::darkCyan);
    setTitle("Residual Curves");
    setTitleFont(titleFont);
    setTitleBrush(titleColor);
    QFont axisFont;
    axisFont.setPointSize(16);
    axisX->setLabelsFont(axisFont);
    axisY1->setLabelsFont(axisFont);
    axisY2->setLabelsFont(axisFont);
    QColor y1Color(Qt::red);
    QColor y2Color(Qt::blue);
    axisY1->setTitleBrush(y1Color);
    axisY2->setTitleBrush(y2Color);

    addAxis(axisX,Qt::AlignBottom);
    addAxis(axisY1,Qt::AlignLeft);
    addAxis(axisY2,Qt::AlignRight);
    addSeries(series_con1);
    addSeries(series_con2);

    series_con1->attachAxis(axisX);
    series_con1->attachAxis(axisY1);
    series_con2->attachAxis(axisX);
    series_con2->attachAxis(axisY2);

    axisX->setTitleText("Iteration");
    axisY1->setTitleText("N-S");
    axisY2->setTitleText("Turbulence");

    axisX->setRange(0,10);
    axisX->setTickCount(8);
    axisY1->setTickCount(6);
    axisY2->setTickCount(6);
}

void Residual_Plot::updateResidualPlot(const QVector<double> &iteration, const QVector<double> &convergence1,
                                       const QVector<double> &convergence2) {

    series_con1->clear();
    series_con2->clear();

    for(int i =0; i<iteration.size();++i){
        series_con1->append(iteration[i],convergence1[i]);
        series_con2->append(iteration[i],convergence2[i]);
    }

    if(!iteration.isEmpty()){
        int maxIter = *std::max_element(iteration.begin(), iteration.end());
        double maxCon1 = *std::max_element(convergence1.begin(), convergence1.end());
        double maxCon2 = *std::max_element(convergence2.begin(), convergence2.end());

        axisX->setRange(0,maxIter+4);
    }
    axisY1->setRange(-8.2,-7.8);
    axisY2->setRange(-12,-10.8);

    this->update();
}