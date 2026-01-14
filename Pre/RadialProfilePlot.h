#ifndef RADIALPROFILEPLOT_H
#define RADIALPROFILEPLOT_H

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QMap>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "CustomChartView.h"
#include "DataStructure.h"

QT_CHARTS_USE_NAMESPACE

class RadialProfilePlot : public QWidget {
    Q_OBJECT

public:
    explicit RadialProfilePlot(QWidget* parent = nullptr);
    ~RadialProfilePlot();

    // Load Type 2 file
    bool loadFile(const QString& filePath);
    
    // Get available variables
    QStringList getAvailableVariables() const;

public slots:
    void onSelectFile();
    void onVariableSelectionChanged();
    void onAutoScale();
    void onManualScale();
    void setRangeX_Min(const QString& text);
    void setRangeX_Max(const QString& text);
    void setRangeY_Min(const QString& text);
    void setRangeY_Max(const QString& text);

private:
    void setupUI();
    void setupChart();
    void updateChart();
    void updateSeriesVisibility(const QStringList& selectedVariables);
    void ensureSeriesExists(const QString& varName);
    void autoRange();

    // UI Components
    QWidget* controlPanel;
    QListWidget* variableList;
    QPushButton* selectFileBtn;
    QLabel* filePathLabel;
    QPushButton* autoScaleBtn;
    QPushButton* manualScaleBtn;
    QLineEdit* xMinEdit;
    QLineEdit* xMaxEdit;
    QLineEdit* yMinEdit;
    QLineEdit* yMaxEdit;

    // Chart Components
    CustomChartView* chartView;
    QChart* chart;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QMap<QString, QLineSeries*> seriesMap;

    // Data
    MonitorType2Data profileData;
    QString currentFilePath;
    
    // State
    bool autoScale;
    double minRangeX, maxRangeX;
    double minRangeY, maxRangeY;
};

#endif // RADIALPROFILEPLOT_H
