#ifndef ControlPanel_h
#define ControlPanel_h

#include <QWidget>
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <vtkAesReader.h>

namespace Ui {class ControlPanel; }

class ControlPanel: public QDialog
{
    Q_OBJECT

public:
    ControlPanel(QWidget* parent = nullptr);
    ~ControlPanel();

    void setupTable(std::vector<std::vector<vtkAesReader::Boundary>> boundarys);
    void addCutplaneToTable(int cutplaneIndex, double* origin, double* normal);

signals:
    // 发送boundary可见性控制信号
    void setBoundarys(int meshNumber, int boundaryNumber, bool flag);
    // 发送cutplane可见性控制信号
    void setCutplaneVisiable(int cutplaneNumber, bool flag);
    // 发送Main Model透明度变化信号
    void mainModelTranscluencyChanged(double value);
    // 发送slice删除信号
    void sliceDeleteRequested(int cutplaneIndex);

private slots:
    // 处理复选框状态变化
    void onShowZoneCheckBoxToggled(bool checked);
    // 处理Main Model透明度变更
    void onMainModelTranscluencyChanged(double value);
    // 处理slice删除
    void onSliceDeleteClicked();

private:
    Ui::ControlPanel *ui;
    QWidget* createCheckBoxWidget(bool checked);
    QWidget* createComboBoxWidget();
    QWidget* createDeleteButtonWidget();
    void removeCutplaneFromTable(int cutplaneIndex);
    
    // 存储boundary索引信息
    std::vector<std::pair<int, int>> boundaryIndices;  // 存储(meshIndex, boundaryIndex)对
    
    // 存储cutplane信息
    struct CutplaneInfo {
        int index;
        double origin[3];
        double normal[3];
    };
    std::vector<CutplaneInfo> cutplaneInfos;
    
    // 标识每行的类型
    enum RowType { BOUNDARY, CUTPLANE };
    std::vector<RowType> rowTypes;

};

#endif