#include "CustomChartView.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

CustomChartView::CustomChartView(QChart *chart, QWidget *parent)
        : QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
    setDragMode(QGraphicsView::NoDrag);
    m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    setInitialAxisRanges();
}

void CustomChartView::setInitialAxisRanges()
{
    if (chart()) {
        m_initialPlotArea = chart()->plotArea();
    }
}

void CustomChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_isMidMousePressed = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else if (event->button() == Qt::LeftButton) {
        m_isLeftMousePressed = true;
        m_rubberBandOrigin = event->pos();
        m_rubberBand->setGeometry(QRect(m_rubberBandOrigin, QSize()));
        m_rubberBand->show();
    }
    QChartView::mousePressEvent(event);
}

void CustomChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isMidMousePressed) {
        QPoint delta = event->pos() - m_lastMousePos;
        chart()->scroll(-delta.x(), delta.y());
        m_lastMousePos = event->pos();
        event->accept();
    } else if (m_isLeftMousePressed) {
        m_rubberBand->setGeometry(QRect(m_rubberBandOrigin, event->pos()).normalized());
    }
    QChartView::mouseMoveEvent(event);
}

void CustomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_isMidMousePressed = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else if (event->button() == Qt::LeftButton) {
        m_isLeftMousePressed = false;
        m_rubberBand->hide();

        if (m_rubberBand->geometry().width() > 10 && m_rubberBand->geometry().height() > 10) {
            QRectF rect = m_rubberBand->geometry();
            QPointF p1 = chart()->mapToValue(rect.topLeft());
            QPointF p2 = chart()->mapToValue(rect.bottomRight());
            chart()->zoomIn(QRectF(p1, p2));
        }
    }
    QChartView::mouseReleaseEvent(event);
}

void CustomChartView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0) {
        chart()->zoom(1.1);
    } else {
        chart()->zoom(0.9);
    }
    event->accept();
}

void CustomChartView::resetToDataRange()
{
    if (!chart()) return;

    const auto series = chart()->series();
    if (series.isEmpty()) return;

    auto firstSeries = qobject_cast<QLineSeries*>(series.first());
    if (!firstSeries) return;

    const auto points = firstSeries->points();
    if (points.isEmpty()) return;

    qreal minX = points.first().x();
    qreal maxX = points.first().x();
    qreal minY = points.first().y();
    qreal maxY = points.first().y();

    for (const auto& point : points) {
        minX = qMin(minX, point.x());
        maxX = qMax(maxX, point.x());
        minY = qMin(minY, point.y());
        maxY = qMax(maxY, point.y());
    }

    auto axisX = qobject_cast<QValueAxis*>(chart()->axes(Qt::Horizontal).first());
    auto axisY = qobject_cast<QValueAxis*>(chart()->axes(Qt::Vertical).first());

    if (axisX && axisY) {
        qreal xMargin = (maxX - minX) * 0.05;
        qreal yMargin = (maxY - minY) * 0.05;

        axisX->setRange(minX - xMargin, maxX + xMargin);
        axisY->setRange(minY - yMargin, maxY + yMargin);
    }
}

void CustomChartView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space) {
        resetToDataRange();
        event->accept();
    }
    QChartView::keyPressEvent(event);
}
