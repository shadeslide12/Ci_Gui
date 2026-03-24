#pragma once

#include <QDialog>
#include <QColor>

#include <vector>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>
#include "vtkAesReader.h"

namespace Ui {
class CutplaneDialog;
}

class CutplaneDialog: public QDialog
{
    Q_OBJECT

public:
    CutplaneDialog(QWidget *parent = nullptr);
    ~CutplaneDialog();

    void setModelBounds(double* bounds);
    void setFlowVariables(const std::vector<vtkAesReader::FlowData>& flows, int currentFlowNumber);
    void updateRangeFromCurrentVariable();
    void setMappingControlEnabled(bool enabled);

private slots:
    void onSliceLocationChanged(int index);
    void onSliderValueChanged(int value);
    void onColorMapPresetChanged(int index);
    void onReverseColorMapToggled(bool checked);
    void onVariableSelectionChanged(int index);
    void onCutplaneOrientationChanged();
    void on_Btn_AddNew_clicked();
    void on_Btn_showPrimarySlice_toggled(bool checked);

    void on_Check_Banded_toggled(bool checked);
    void on_Check_Continuous_toggled(bool checked);

signals:
    void createNewCutplane(double*, double*);
    void sliceLocation(double value, int axis); // 滑块移动时实时发送，用于预览平面位置
    void hidePreview();                         // 隐藏预览平面
    void colorMappingChanged(double minValue, double maxValue, int numberOfColors, bool isBanded);
    void colorSchemeChanged(int presetIndex, bool reverse);
    void variableSelectionChanged(int flowNumber);
    void cutplaneOrientationChanged(bool isVertical);

private:
    Ui::CutplaneDialog *ui;

    // 预览切片参数，滑块调整时实时更新，点击 Btn_AddNew 时创建真正的 slice
    double curOrigin[3];
    double curNormal[3];

    double modelBounds[6]; // [xmin, xmax, ymin, ymax, zmin, zmax]
    int currentAxis;       // 当前选择的轴：0=X轴, 1=Y轴, 2=Z轴

    std::vector<vtkAesReader::FlowData> flowVariables;
    int currentFlowNumber;

    int currentColorMapIndex;
    void initializeColorMapPresets();
    void updateColorMapPreviewIcons();

    void updateSliderRange();
    void updateValueLabel(double value);
    void onColorMappingChanged();
    bool isBaned = 1;
};
