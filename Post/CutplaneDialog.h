#pragma once

#include <QDialog>

#include <vector>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>

namespace Ui {
class CutplaneDialog;
}

class CutplaneDialog: public QDialog
{
    Q_OBJECT
    
public:
    CutplaneDialog(QWidget *parent = nullptr);
    ~CutplaneDialog();

    void setCutplaneDialog(std::vector<vtkSmartPointer<vtkPlane>> planes);
    void setModelBounds(double* bounds);

private slots:
    void setParameters();
    void createSignal();
    void changeCutplaneNumber(int number);

    void onSliceLocationChanged(int index); // 处理平面类型变化
    void onSliderValueChanged(int value);   // 处理滑块值变化
    void onExtractSliceClicked();           // 处理提取切片按钮点击
    void onColorSchemeChanged(int index);   // 处理颜色方案变化
    void on_Btn_SetPosition_clicked();
    void on_Btn_AddNew_clicked();

signals:
    void finishSetParameters(double*, double*, int);
    void createNewCutplane(double*, double*);
    void sliceLocation(double,int);
    void colorMappingChanged(double minValue, double maxValue, int numberOfColors);
    void colorSchemeChanged(int schemeIndex);  // 颜色方案变化信号

private:
    Ui::CutplaneDialog *ui;

    std::vector<double*> origin;
    std::vector<double*> normal;
    double curOrigin[3];
    double curNormal[3];
    bool createFlag = false;

    double modelBounds[6]; // [xmin, xmax, ymin, ymax, zmin, zmax]
    int currentAxis;       // 当前选择的轴：0=X轴, 1=Y轴, 2=Z轴
    
    // 设置滑块范围和当前值
    void updateSliderRange();
    // 根据滑块值更新标签显示
    void updateValueLabel(double value);
    // 根据滑块值设置切面位置
    void setPlanePosition(double value);
    void onColorMappingChanged();
};