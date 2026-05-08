#include "CutplaneDialog.h"
#include "ui_CutplaneDialog.h"
#include "ColorMapPreset.h"
#include <string>
#include <iostream>
#include <QButtonGroup>
#include <QColorDialog>
#include <QCoreApplication>
#include <QDir>
using std::cout;
using std::endl;

CutplaneDialog::CutplaneDialog(QWidget *parent): QDialog(parent), ui(new Ui::CutplaneDialog)
{
    ui->setupUi(this);
    currentTextColor = Qt::black;

    connect(ui->Combo_SLiceLocation, SIGNAL(currentIndexChanged(int)), this, SLOT(onSliceLocationChanged(int)));
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderValueChanged(int)));
    connect(ui->Combo_SekectMapVariable, SIGNAL(currentIndexChanged(int)), this, SLOT(onVariableSelectionChanged(int)));

    // 连接 buttonBox 的 accepted 信号到颜色映射更新
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &CutplaneDialog::onColorMappingChanged);
    
    // 连接 Apply 按钮：应用参数但不关闭对话框
    QPushButton* applyBtn = ui->buttonBox->button(QDialogButtonBox::Apply);
    if (applyBtn) {
        connect(applyBtn, &QPushButton::clicked, this, &CutplaneDialog::onColorMappingChanged);
    }

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

    ui->Combo_ContourType->blockSignals(false);
    ui->checkReverseColorMap->blockSignals(false);

    initializeLegendControls();
    connectLegendSignals();

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

    if (minValue >= maxValue) {
        std::cout << "[Warning] Min value must be less than max value" << std::endl;
        return;
    }

    emit colorMappingChanged(minValue, maxValue, isBaned);

    std::cout << "[Debug] Cutplane color mapping changed: range["
              << minValue << ", " << maxValue << "]" << std::endl;
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

// 设置流场变量数据
void CutplaneDialog::setFlowVariables(const std::vector<vtkAesReader::FlowData>& flows, 
                                      int currentFlowNum,
                                      double customMin,
                                      double customMax,
                                      bool hasCustomRange)
{
    flowVariables = flows;
    this->currentFlowNumber = currentFlowNum;

    ui->Combo_SekectMapVariable->clear();
    for (size_t i = 0; i < flowVariables.size(); i++)
        ui->Combo_SekectMapVariable->addItem(QString::fromStdString(flowVariables[i].name));

    if (currentFlowNumber >= 0 && currentFlowNumber < static_cast<int>(flowVariables.size())) {
        ui->Combo_SekectMapVariable->setCurrentIndex(currentFlowNumber);
        if (ui->cp_checkShowTitle->isChecked() && ui->cp_comboTitleMode->currentIndex() == 0) {
            emit cutplaneLegendTitleTextChanged(
                QString::fromStdString(flowVariables[currentFlowNumber].name), true);
        }
        
        // 如果有自定义范围，使用自定义范围；否则使用原始范围
        if (hasCustomRange) {
            ui->LnEdit_Min->setText(QString::number(customMin, 'f', 6));
            ui->LnEdit_Max->setText(QString::number(customMax, 'f', 6));
            std::cout << "[Debug] Using custom range: [" << customMin << ", " << customMax << "]" << std::endl;
        } else {
            updateRangeFromCurrentVariable();
        }
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
        if (ui->cp_checkShowTitle->isChecked() && ui->cp_comboTitleMode->currentIndex() == 0) {
            emit cutplaneLegendTitleTextChanged(
                QString::fromStdString(flowVariables[currentFlowNumber].name), true);
        }

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

void CutplaneDialog::initializeLegendControls()
{
    currentTextColor = Qt::black;
    ui->cp_btnTextColor->setStyleSheet("QPushButton { background-color: black; color: white; }");
    ui->cp_btnTextColor->setText("Black");

    // Match vtkDisplayWindow::InitializeCutplaneScalarBar defaults.
    ui->cp_textScalarBarWidth->setText("0.60");
    ui->cp_textScalarBarHeight->setText("0.06");
    ui->cp_textLegendXPosition->setText("20");
    ui->cp_textLegendYPosition->setText("10");

    ui->cp_checkShowLegend->setChecked(true);
    ui->cp_checkShowTitle->setChecked(true);
    ui->cp_comboTitleMode->setCurrentIndex(0);
    ui->cp_textTitleText->setEnabled(false);
    ui->cp_labelTitleText->setEnabled(false);
}

void CutplaneDialog::connectLegendSignals()
{
    connect(ui->cp_checkShowLegend, &QCheckBox::toggled,
            this, &CutplaneDialog::onCutplaneShowLegendToggled);

    connect(ui->cp_checkShowTitle, &QCheckBox::toggled,
            this, &CutplaneDialog::onCutplaneShowTitleToggled);
    connect(ui->cp_comboTitleMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &CutplaneDialog::onCutplaneTitleModeChanged);

    connect(ui->cp_textTitleText, &QLineEdit::editingFinished, [this]() {
        if (ui->cp_comboTitleMode->currentIndex() == 1) {
            QString customTitle = ui->cp_textTitleText->text();
            if (!customTitle.isEmpty()) {
                emit cutplaneLegendTitleTextChanged(customTitle, false);
            }
        }
    });

    connect(ui->cp_btnTextColor, &QPushButton::clicked,
            this, &CutplaneDialog::onCutplaneTextColorClicked);

    connect(ui->cp_textLegendXPosition, &QLineEdit::editingFinished,
            this, &CutplaneDialog::onCutplanePositionOrSizeChanged);
    connect(ui->cp_textLegendYPosition, &QLineEdit::editingFinished,
            this, &CutplaneDialog::onCutplanePositionOrSizeChanged);
    connect(ui->cp_textScalarBarWidth, &QLineEdit::editingFinished,
            this, &CutplaneDialog::onCutplanePositionOrSizeChanged);
    connect(ui->cp_textScalarBarHeight, &QLineEdit::editingFinished,
            this, &CutplaneDialog::onCutplanePositionOrSizeChanged);

    connect(ui->cp_comboFontFamily, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this]() {
                emit cutplaneLegendFontChanged(
                    ui->cp_comboFontFamily->currentText(),
                    ui->cp_spinFontSize->value(),
                    ui->cp_checkBold->isChecked(),
                    ui->cp_checkItalic->isChecked());
            });

    connect(ui->cp_spinFontSize, QOverload<int>::of(&QSpinBox::valueChanged),
            [this]() {
                emit cutplaneLegendFontChanged(
                    ui->cp_comboFontFamily->currentText(),
                    ui->cp_spinFontSize->value(),
                    ui->cp_checkBold->isChecked(),
                    ui->cp_checkItalic->isChecked());
            });

    connect(ui->cp_checkBold, &QCheckBox::toggled,
            [this]() {
                emit cutplaneLegendFontChanged(
                    ui->cp_comboFontFamily->currentText(),
                    ui->cp_spinFontSize->value(),
                    ui->cp_checkBold->isChecked(),
                    ui->cp_checkItalic->isChecked());
            });

    connect(ui->cp_checkItalic, &QCheckBox::toggled,
            [this]() {
                emit cutplaneLegendFontChanged(
                    ui->cp_comboFontFamily->currentText(),
                    ui->cp_spinFontSize->value(),
                    ui->cp_checkBold->isChecked(),
                    ui->cp_checkItalic->isChecked());
            });
}

void CutplaneDialog::onCutplaneShowLegendToggled(bool checked)
{
    std::cout << "[CutplaneDialog] Legend visibility changed: "
              << (checked ? "visible" : "hidden") << std::endl;
    emit cutplaneLegendVisibilityChanged(checked);
}

void CutplaneDialog::onCutplaneShowTitleToggled(bool checked)
{
    ui->cp_comboTitleMode->setEnabled(checked);
    ui->cp_labelTitleMode->setEnabled(checked);

    bool useCustomText = (ui->cp_comboTitleMode->currentIndex() == 1);
    ui->cp_textTitleText->setEnabled(checked && useCustomText);
    ui->cp_labelTitleText->setEnabled(checked && useCustomText);

    emit cutplaneLegendTitleVisibilityChanged(checked);
    if (checked) {
        onCutplaneTitleModeChanged(ui->cp_comboTitleMode->currentIndex());
    }
}

void CutplaneDialog::onCutplaneTitleModeChanged(int index)
{
    bool useCustomText = (index == 1);
    ui->cp_textTitleText->setEnabled(useCustomText && ui->cp_checkShowTitle->isChecked());
    ui->cp_labelTitleText->setEnabled(useCustomText && ui->cp_checkShowTitle->isChecked());

    if (useCustomText) {
        QString customTitle = ui->cp_textTitleText->text();
        if (customTitle.isEmpty()) {
            customTitle = "Slice";
            ui->cp_textTitleText->setText(customTitle);
        }
        emit cutplaneLegendTitleTextChanged(customTitle, false);
    } else {
        QString varName;
        if (currentFlowNumber >= 0 && currentFlowNumber < static_cast<int>(flowVariables.size())) {
            varName = QString::fromStdString(flowVariables[currentFlowNumber].name);
        }
        emit cutplaneLegendTitleTextChanged(varName, true);
    }
}

void CutplaneDialog::onCutplaneTextColorClicked()
{
    QColor color = QColorDialog::getColor(currentTextColor, this, "Select Cutplane Legend Text Color");
    if (!color.isValid()) {
        return;
    }

    currentTextColor = color;
    QString colorName = color.name();
    QString textColor = (color.lightness() > 128) ? "black" : "white";
    ui->cp_btnTextColor->setStyleSheet(
        QString("QPushButton { background-color: %1; color: %2; }")
            .arg(colorName).arg(textColor));
    ui->cp_btnTextColor->setText(colorName);

    emit cutplaneLegendTextColorChanged(color.redF(), color.greenF(), color.blueF());
}

void CutplaneDialog::onCutplanePositionOrSizeChanged()
{
    bool okX = false;
    bool okY = false;
    bool okW = false;
    bool okH = false;

    double xPos = ui->cp_textLegendXPosition->text().toDouble(&okX) / 100.0;
    double yPos = ui->cp_textLegendYPosition->text().toDouble(&okY) / 100.0;
    double width = ui->cp_textScalarBarWidth->text().toDouble(&okW);
    double height = ui->cp_textScalarBarHeight->text().toDouble(&okH);

    if (!okX || !okY || !okW || !okH) {
        std::cout << "[CutplaneDialog] Invalid legend position/size value" << std::endl;
        return;
    }

    if (xPos < 0.0 || xPos > 1.0 || yPos < 0.0 || yPos > 1.0) {
        std::cout << "[CutplaneDialog] Position values should be between 0 and 100" << std::endl;
        return;
    }

    if (width < 0.01 || width > 1.0 || height < 0.01 || height > 1.0) {
        std::cout << "[CutplaneDialog] Size values should be between 0.01 and 1.0" << std::endl;
        return;
    }

    emit cutplaneLegendPositionChanged(xPos, yPos);
    emit cutplaneLegendSizeChanged(width, height);
}
