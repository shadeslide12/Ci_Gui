#ifndef CUSTOMCHARTVIEW_H
#define CUSTOMCHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE

class CustomChartView : public QChartView
{
Q_OBJECT
public:
    explicit CustomChartView(QChart *chart, QWidget *parent = nullptr);
    void setInitialAxisRanges();
    void resetToDataRange();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool m_isMidMousePressed = false;
    QPoint m_lastMousePos;
    bool m_isLeftMousePressed = false;
    QRubberBand *m_rubberBand = nullptr;
    QPoint m_rubberBandOrigin;

    QRectF m_initialPlotArea;

    void getSeriesRange(QLineSeries* series, qreal& minY, qreal& maxY);

};

#endif // CUSTOMCHARTVIEW_H
