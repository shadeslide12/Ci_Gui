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
    this->setRenderHint(QPainter::Antialiasing);
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

void CustomChartView::mouseMoveEvent(QMouseEvent* event)
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

void CustomChartView::mouseReleaseEvent(QMouseEvent* event)
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

void CustomChartView::wheelEvent(QWheelEvent* event)
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

    const auto allSeries = chart()->series();
    if (allSeries.isEmpty()) return;

    bool firstVisibleFound = false;
    qreal minX = 0, maxX = 0, minY = 0, maxY = 0;

    for (const auto& series : allSeries) {
        auto lineSeries = qobject_cast<QLineSeries*>(series);
        if (!lineSeries || !lineSeries->isVisible()) continue;

        const auto points = lineSeries->points();
        if (points.isEmpty()) continue;

        if (!firstVisibleFound) {
            minX = points.first().x();
            maxX = points.first().x();
            minY = points.first().y();
            maxY = points.first().y();
            firstVisibleFound = true;
        }

        for (const auto& point : points) {
            minX = qMin(minX, point.x());
            maxX = qMax(maxX, point.x());
            minY = qMin(minY, point.y());
            maxY = qMax(maxY, point.y());
        }
    }

    if (!firstVisibleFound) return;

    const auto xAxes = chart()->axes(Qt::Horizontal);
    const auto yAxes = chart()->axes(Qt::Vertical);

    qreal xMargin = (maxX - minX) * 0.05;
    qreal yMargin = (maxY - minY) * 0.05;

    for (auto axis : xAxes) {
        if (auto valueAxis = qobject_cast<QValueAxis*>(axis)) {
            valueAxis->setRange(minX - xMargin, maxX + xMargin);
        }
    }

    for (auto axis : yAxes) {
        auto valueAxis = qobject_cast<QValueAxis*>(axis);
        if (!valueAxis) continue;

        qreal axisMinY = std::numeric_limits<qreal>::max();
        qreal axisMaxY = std::numeric_limits<qreal>::lowest();
        bool hasVisibleSeries = false;

        for (const auto& series : allSeries) {
            auto lineSeries = qobject_cast<QLineSeries*>(series);
            if (!lineSeries || !lineSeries->isVisible()) continue;

            const auto attachedAxes = lineSeries->attachedAxes();
            if (!attachedAxes.contains(valueAxis)) continue;

            hasVisibleSeries = true;
            for (const auto& point : lineSeries->points()) {
                axisMinY = qMin(axisMinY, point.y());
                axisMaxY = qMax(axisMaxY, point.y());
            }
        }

        if (hasVisibleSeries) {
            qreal yMargin = (axisMaxY - axisMinY) * 0.05;
            valueAxis->setRange(axisMinY - yMargin, axisMaxY + yMargin);
        }
    }
}

void CustomChartView::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Space) {
        resetToDataRange();
        event->accept();
    }
    QChartView::keyPressEvent(event);
}
