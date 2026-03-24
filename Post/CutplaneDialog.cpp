#include "CutplaneDialog.h"
#include "ui_CutplaneDialog.h"
#include "ColorMapPreset.h"
#include <string>
#include <iostream>
#include <QButtonGroup>
#include <QCoreApplication>
#include <QDir>
using std::cout;
using std::endl;

CutplaneDialog::CutplaneDialog(QWidget *parent): QDialog(parent), ui(new Ui::CutplaneDialog)
{
    ui->setupUi(this);

    connect(ui->Combo_SLiceLocation, SIGNAL(currentIndexChanged(int)), this, SLOT(onSliceLocationChanged(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
    connect(ui->Combo_SekectMapVariable, SIGNAL(currentIndexChanged(int)), this, SLOT(onVariableSelectionChanged(int)));

    // 初始化颜色映射预设（从 JSON 加载）
    currentColorMapIndex = 0;
    initializeColorMapPresets();

    // 连接颜色映射 ComboBox 和 Reverse CheckBox
    ui->Combo_ContourType->blockSignals(true);
    ui->checkReverseColorMap->blockSignals(true);

    connect(ui->Combo_ContourType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CutplaneDialog::onColorMapPresetChanged);
    connect(ui->checkReverseColorMap, &QCheckBox::toggled,
            this, &CutplaneDialog::onReverseColorMapToggled);

    // 连接 cutplane scalar bar 方向控制
    connect(ui->cp_radioVertical, &QRadioButton::toggled,
            this, &CutplaneDialog::onCutplaneOrientationChanged);
    connect(ui->cp_radioHorizontal, &QRadioButton::toggled,
            this, &CutplaneDialog::onCutplaneOrientationChanged);

    ui->Combo_ContourType->blockSignals(false);
    ui->checkReverseColorMap->blockSignals(false);

    // 初始化
    currentAxis = 0;
    currentFlowNumber = 0;
    for (int i = 0; i < 6; i++)
        modelBounds[i] = 0.0;

    // 设置滑块初始范围
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setValue(50);

    updateValueLabel(0.0);

    //* Set Group Of Color Method
    QButtonGroup *group_ColorMethod = new QButtonGroup(this);
    group_ColorMethod->setExclusive(true);
    group_ColorMethod->addButton(ui->Check_Banded);
    group_ColorMethod->addButton(ui->Check_Continuous);
}

CutplaneDialog::~CutplaneDialog()
{
    delete ui;
}

void CutplaneDialog::setModelBounds(double* bounds)
{
    if (bounds != nullptr) {
        for (int i = 0; i < 6; i++)
            modelBounds[i] = bounds[i];
        updateSliderRange();
    }
}

// 处理平面类型变化
void CutplaneDialog::onSliceLocationChanged(int index)
{
    currentAxis = index;
    updateSliderRange();
}

// 处理滑块值变化，直接更新预览切片参数
void CutplaneDialog::onSliderValueChanged(int value)
{
    double min = 0.0, max = 1.0;
    switch (currentAxis) {
    case 0: min = modelBounds[0]; max = modelBounds[1]; break;
    case 1: min = modelBounds[2]; max = modelBounds[3]; break;
    case 2: min = modelBounds[4]; max = modelBounds[5]; break;
    }

    double actualValue = min + (max - min) * value / 100.0;
    updateValueLabel(actualValue);

    // 直接更新预览切片参数
    switch (currentAxis) {
    case 0: // X轴 - YZ平面
        curOrigin[0] = actualValue; curOrigin[1] = 0.0; curOrigin[2] = 0.0;
        curNormal[0] = 1.0;        curNormal[1] = 0.0; curNormal[2] = 0.0;
        break;
    case 1: // Y轴 - XZ平面
        curOrigin[0] = 0.0; curOrigin[1] = actualValue; curOrigin[2] = 0.0;
        curNormal[0] = 0.0; curNormal[1] = 1.0;        curNormal[2] = 0.0;
        break;
    case 2: // Z轴 - XY平面
        curOrigin[0] = 0.0; curOrigin[1] = 0.0; curOrigin[2] = actualValue;
        curNormal[0] = 0.0; curNormal[1] = 0.0; curNormal[2] = 1.0;
        break;
    }

    // 发送信号，通知 MainWindow 更新预览平面位置（仅在 checkbox 选中时）
    if (ui->Btn_showPrimarySlice->isChecked())
        emit sliceLocation(actualValue, currentAxis);
}

// 更新滑块范围
void CutplaneDialog::updateSliderRange()
{
    ui->horizontalSlider->setValue(50); // 默认在中间位置
    onSliderValueChanged(50);
}

// 根据滑块值更新标签显示
void CutplaneDialog::updateValueLabel(double value)
{
    QString axisName;
    switch (currentAxis) {
        case 0: axisName = "X"; break;
        case 1: axisName = "Y"; break;
        case 2: axisName = "Z"; break;
    }
    ui->label_ValueLocation->setText(QString("%1 : %2").arg(axisName).arg(value, 0, 'f', 4));
}

// 点击 Extract Slices 按钮，用当前预览参数创建真正的 slice
void CutplaneDialog::on_Btn_AddNew_clicked()
{
    std::cout << "[Debug] Creating new cutplane with origin: ("
              << curOrigin[0] << ", " << curOrigin[1] << ", " << curOrigin[2]
              << ") normal: (" << curNormal[0] << ", " << curNormal[1] << ", " << curNormal[2] << ")" << std::endl;
    emit createNewCutplane(curOrigin, curNormal);
}

void CutplaneDialog::on_Btn_showPrimarySlice_toggled(bool checked)
{
    if (checked) {
        // 重新触发一次，恢复当前滑块位置的预览平面
        onSliderValueChanged(ui->horizontalSlider->value());
    } else {
        emit hidePreview();
    }
}

void CutplaneDialog::onColorMappingChanged()
{
    bool ok;
    double minValue = ui->LnEdit_Min->text().toDouble(&ok);
    if (!ok) {
        std::cout << "[Warning] Invalid min value: " << ui->LnEdit_Min->text().toStdString() << std::endl;
        return;
    }

    double maxValue = ui->LnEdit_Max->text().toDouble(&ok);
    if (!ok) {
        std::cout << "[Warning] Invalid max value: " << ui->LnEdit_Max->text().toStdString() << std::endl;
        return;
    }

    int numberOfColors = ui->LnEdit_Numbers->text().toInt(&ok);
    if (!ok || numberOfColors <= 0) {
        std::cout << "[Warning] Invalid number of colors: " << ui->LnEdit_Numbers->text().toStdString() << std::endl;
        return;
    }

    if (minValue >= maxValue) {
        std::cout << "[Warning] Min value must be less than max value" << std::endl;
        return;
    }

    emit colorMappingChanged(minValue, maxValue, numberOfColors, isBaned);

    std::cout << "[Debug] Shared cutplane color mapping changed: range["
              << minValue << ", " << maxValue
              << "], colors=" << numberOfColors << std::endl;
}

void CutplaneDialog::onColorMapPresetChanged(int comboIndex)
{
    if (comboIndex < 0) return;

    currentColorMapIndex = ui->Combo_ContourType->itemData(comboIndex).toInt();
    bool reverse = ui->checkReverseColorMap->isChecked();

    QString name = ui->Combo_ContourType->currentText();
    std::cout << "[CutplaneDialog] Color map preset changed: " << name.toStdString()
              << ", presetIndex=" << currentColorMapIndex
              << ", reverse=" << (reverse ? "true" : "false") << std::endl;

    emit colorSchemeChanged(currentColorMapIndex, reverse);
}

void CutplaneDialog::onReverseColorMapToggled(bool checked)
{
    std::cout << "[CutplaneDialog] Reverse color map toggled: " << (checked ? "true" : "false") << std::endl;
    updateColorMapPreviewIcons();
    emit colorSchemeChanged(currentColorMapIndex, checked);
}

void CutplaneDialog::initializeColorMapPresets()
{
    ColorMapPreset& preset = ColorMapPreset::instance();

    QString appDir = QCoreApplication::applicationDirPath();
    QString currentDir = QDir::currentPath();

    QStringList searchPaths = {
        "F:/Linux_Files/ZJU/zjui-cfd-pre-wsl/GUI/Post/ColorMaps.json",
        appDir + "/ColorMaps.json",
        appDir + "/../ColorMaps.json",
        appDir + "/../../GUI/Post/ColorMaps.json",
        currentDir + "/ColorMaps.json",
        currentDir + "/GUI/Post/ColorMaps.json",
        "F:/Linux_Files/ZJU/zjui-cfd-pre-wsl/Doc/Others/ColorMap/ColorMaps.json"
    };

    if (!preset.isLoaded()) {
        for (const QString& path : searchPaths) {
            if (QFile::exists(path)) {
                if (preset.loadFromJson(path)) {
                    std::cout << "[CutplaneDialog] Loaded color maps from: " << path.toStdString() << std::endl;
                    break;
                }
            }
        }
    }

    ui->Combo_ContourType->clear();

    if (preset.isLoaded()) {
        auto defaultIndices = preset.getDefaultMapIndices();
        for (int idx : defaultIndices) {
            QString name = preset.getName(idx);
            QPixmap preview = preset.generatePreview(idx, 200, 20, false);
            ui->Combo_ContourType->addItem(QIcon(preview), name, idx);
        }
        std::cout << "[CutplaneDialog] Added " << defaultIndices.size() << " default color maps to combo box" << std::endl;
    } else {
        ui->Combo_ContourType->addItem("Rainbow (default)", -1);
        ui->Combo_ContourType->addItem("Viridis", -2);
        ui->Combo_ContourType->addItem("Gray", -3);
    }

    if (ui->Combo_ContourType->count() > 0) {
        ui->Combo_ContourType->setCurrentIndex(0);
        currentColorMapIndex = ui->Combo_ContourType->itemData(0).toInt();
    }
}

void CutplaneDialog::updateColorMapPreviewIcons()
{
    ColorMapPreset& preset = ColorMapPreset::instance();
    if (!preset.isLoaded()) return;

    bool reverse = ui->checkReverseColorMap->isChecked();

    for (int i = 0; i < ui->Combo_ContourType->count(); ++i) {
        int presetIndex = ui->Combo_ContourType->itemData(i).toInt();
        if (presetIndex >= 0) {
            QPixmap preview = preset.generatePreview(presetIndex, 200, 20, reverse);
            ui->Combo_ContourType->setItemIcon(i, QIcon(preview));
        }
    }
}

void CutplaneDialog::on_Check_Banded_toggled(bool checked)
{
    if (checked)
        isBaned = 1;
}

void CutplaneDialog::on_Check_Continuous_toggled(bool checked)
{
    if (checked)
        isBaned = 0;
}

// 设置流场变量数据
void CutplaneDialog::setFlowVariables(const std::vector<vtkAesReader::FlowData>& flows, int currentFlowNum)
{
    flowVariables = flows;
    this->currentFlowNumber = currentFlowNum;

    ui->Combo_SekectMapVariable->clear();
    for (size_t i = 0; i < flowVariables.size(); i++)
        ui->Combo_SekectMapVariable->addItem(QString::fromStdString(flowVariables[i].name));

    if (currentFlowNumber >= 0 && currentFlowNumber < static_cast<int>(flowVariables.size())) {
        ui->Combo_SekectMapVariable->setCurrentIndex(currentFlowNumber);
        updateRangeFromCurrentVariable();
    }

    std::cout << "[Debug] Flow variables set: " << flowVariables.size()
              << " variables, current: " << currentFlowNumber << std::endl;
}

// 处理变量选择变化
void CutplaneDialog::onVariableSelectionChanged(int index)
{
    if (index >= 0 && index < static_cast<int>(flowVariables.size())) {
        currentFlowNumber = index;
        updateRangeFromCurrentVariable();
        emit variableSelectionChanged(currentFlowNumber);

        std::cout << "[Debug] Variable selection changed to: " << index
                  << " (" << flowVariables[index].name << ")" << std::endl;
    }
}

// 根据当前选择的变量更新范围值
void CutplaneDialog::updateRangeFromCurrentVariable()
{
    if (currentFlowNumber >= 0 && currentFlowNumber < static_cast<int>(flowVariables.size())) {
        const vtkAesReader::FlowData& currentFlow = flowVariables[currentFlowNumber];
        ui->LnEdit_Min->setText(QString::number(currentFlow.range[0], 'f', 6));
        ui->LnEdit_Max->setText(QString::number(currentFlow.range[1], 'f', 6));

        std::cout << "[Debug] Updated range for " << currentFlow.name
                  << ": [" << currentFlow.range[0] << ", " << currentFlow.range[1] << "]" << std::endl;
    }
}

void CutplaneDialog::setMappingControlEnabled(bool enabled)
{
    std::cout << "[Debug] Setting mapping control enabled to " << enabled << std::endl;
    if (enabled)
        ui->MappingControl->setEnabled(true);
    else
        ui->MappingControl->setDisabled(true);
}

void CutplaneDialog::onCutplaneOrientationChanged()
{
    bool isVertical = ui->cp_radioVertical->isChecked();
    std::cout << "[CutplaneDialog] Cutplane scalar bar orientation changed to: "
              << (isVertical ? "Vertical" : "Horizontal") << std::endl;
    emit cutplaneOrientationChanged(isVertical);
}
