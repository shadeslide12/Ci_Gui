#include "ControlPanel.h"
#include "ui_ControlPanel.h"

ControlPanel::ControlPanel(QWidget *parent): QDialog(parent),ui(new Ui::ControlPanel) {
    ui->setupUi(this);

}

ControlPanel::~ControlPanel() {
    delete ui;
}

void ControlPanel::setupTable(std::vector<std::vector<vtkAesReader::Boundary>> boundarys)
{   
    ui->dataTable->setColumnWidth(0, 70);   
    ui->dataTable->setColumnWidth(1, 200);  
    ui->dataTable->setColumnWidth(2, 120);   
    ui->dataTable->setColumnWidth(3, 70);   
    ui->dataTable->setColumnWidth(4, 100);   
    ui->dataTable->setColumnWidth(5, 100);   
    ui->dataTable->setColumnWidth(6, 100);   

    //* 收集所有的boundary信息
    QStringList zoneNumbers;
    QStringList boundaryNames;
    
    int boundaryCount = 0;
    
    // 清空之前的索引信息
    boundaryIndices.clear();
    cutplaneInfos.clear();
    rowTypes.clear();
    
    for (int i = 0; i < boundarys.size(); i++) {
        for (int j = 0; j < boundarys[i].size(); j++) {
            boundaryCount++;
            
            zoneNumbers.append(QString("%1*").arg(boundaryCount));
            
            QString zoneName = QString(boundarys[i][j].zoneName.c_str()).trimmed();
            QString boundaryName = QString(boundarys[i][j].name.c_str()).trimmed();
            
            // 创建zone->boundary格式的名称
            QString combinedName = QString("%1->%2").arg(zoneName).arg(boundaryName);

            boundaryNames.append(combinedName);
            
            // 存储boundary索引信息
            boundaryIndices.push_back(std::make_pair(i, j));
            rowTypes.push_back(BOUNDARY);
        }
    }
    
    // 设置表格行数为实际的boundary数量
    ui->dataTable->setRowCount(boundaryCount);
    
    // 填充表格
    for (int row = 0; row < boundaryCount; ++row) {
        //* Set Zone Number
        QTableWidgetItem* zoneNumItem = new QTableWidgetItem(zoneNumbers[row]);
        zoneNumItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 0, zoneNumItem);
        
        //* Set Zone Name 
        QTableWidgetItem* zoneNameItem = new QTableWidgetItem(boundaryNames[row]);
        ui->dataTable->setItem(row, 1, zoneNameItem);
        
        //* Set Group Number
        QTableWidgetItem* groupNumItem = new QTableWidgetItem("Main Model");
        groupNumItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 2, groupNumItem);
        
        QWidget* checkBoxWidget = createCheckBoxWidget(true);
        QCheckBox* checkBox = checkBoxWidget->findChild<QCheckBox*>();
        if (checkBox) {
            // 设置复选框的属性，用于识别对应的boundary
            checkBox->setProperty("boundaryRow", row);
            connect(checkBox, &QCheckBox::toggled, this, &ControlPanel::onShowZoneCheckBoxToggled);
        }
        ui->dataTable->setCellWidget(row, 3, checkBoxWidget);
        
        //* Set Contour Mode 
        ui->dataTable->setCellWidget(row, 4, createComboBoxWidget());
        
        //* Set Transculency - 为Main Model行创建可编辑的SpinBox
        QWidget* transculencyWidget = new QWidget();
        QHBoxLayout* transLayout = new QHBoxLayout(transculencyWidget);
        QDoubleSpinBox* transSpinBox = new QDoubleSpinBox();
        transSpinBox->setRange(0.0, 1.0);
        transSpinBox->setSingleStep(0.1);
        transSpinBox->setValue(1.0);
        transSpinBox->setDecimals(1);
        
        // 连接透明度变化信号
        connect(transSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
                this, &ControlPanel::onMainModelTranscluencyChanged);
        
        transLayout->addWidget(transSpinBox);
        transLayout->setAlignment(Qt::AlignCenter);
        transLayout->setContentsMargins(0, 0, 0, 0);
        ui->dataTable->setCellWidget(row, 5, transculencyWidget);
        
        //* Set Delete Button
        ui->dataTable->setCellWidget(row, 6, createDeleteButtonWidget());
    }
}

QWidget* ControlPanel::createCheckBoxWidget(bool checked)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);
    QCheckBox* checkBox = new QCheckBox();
    checkBox->setChecked(checked);
    
    layout->addWidget(checkBox);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    
    return widget;
}

QWidget* ControlPanel::createComboBoxWidget()
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);
    QComboBox* comboBox = new QComboBox();
    
    comboBox->addItem("isolated");
    comboBox->addItem("sync with main");
    comboBox->setCurrentIndex(0);
    
    layout->addWidget(comboBox);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    
    return widget;
}

QWidget* ControlPanel::createDeleteButtonWidget()
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);
    QPushButton* deleteButton = new QPushButton("Delete");
    
    layout->addWidget(deleteButton);
    layout->setAlignment(Qt::AlignCenter);
    layout->setContentsMargins(0, 0, 0, 0);
    
    return widget;
}

void ControlPanel::onShowZoneCheckBoxToggled(bool checked)
{
    // 获取发送信号的复选框
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());
    if (!checkBox) return;
    
    // 获取对应的行号
    int    row = checkBox->property("boundaryRow").toInt();
    
     // 检查行号是否有效
    if (row < 0 || row >= rowTypes.size()) return;
    
    // 根据行类型发送不同的信号
    if (rowTypes[row] == BOUNDARY) {
        // 处理boundary
        if (row >= boundaryIndices.size()) return;
        
        int meshNumber = boundaryIndices[row].first;
        int boundaryNumber = boundaryIndices[row].second;
        
        // 发送信号控制boundary可见性
        emit setBoundarys(meshNumber, boundaryNumber, checked);
    }
    else if (rowTypes[row] == CUTPLANE) {
        // 处理cutplane
        int cutplaneIndex = row - boundaryIndices.size(); // cutplane在boundary之后
        if (cutplaneIndex < 0 || cutplaneIndex >= cutplaneInfos.size()) return;
        
        int cutplaneNumber = cutplaneInfos[cutplaneIndex].index;
        
        // 发送信号控制cutplane可见性
        emit setCutplaneVisiable(cutplaneNumber, checked);
    }
}

void ControlPanel::addCutplaneToTable(int cutplaneIndex, double* origin, double* normal)
{
    // 存储cutplane信息
    CutplaneInfo cutplaneInfo;
    cutplaneInfo.index = cutplaneIndex;
    for (int i = 0; i < 3; i++) {
        cutplaneInfo.origin[i] = origin[i];
        cutplaneInfo.normal[i] = normal[i];
    }
    cutplaneInfos.push_back(cutplaneInfo);
    
    // 获取当前行数
    int currentRowCount = ui->dataTable->rowCount();
    int newRow = currentRowCount;
    
    // 增加一行
    ui->dataTable->setRowCount(currentRowCount + 1);
    rowTypes.push_back(CUTPLANE);
    
    // 填充cutplane行数据
    //* Set Zone Number
    QString cutplaneNumber = QString("S%1*").arg(cutplaneIndex + 1);
    QTableWidgetItem* zoneNumItem = new QTableWidgetItem(cutplaneNumber);
    zoneNumItem->setTextAlignment(Qt::AlignCenter);
    ui->dataTable->setItem(newRow, 0, zoneNumItem);
    
    //* Set Zone Name (cutplane信息)
    QString cutplaneName = QString("Slice_%1").arg(cutplaneIndex + 1);
    QTableWidgetItem* zoneNameItem = new QTableWidgetItem(cutplaneName);
    ui->dataTable->setItem(newRow, 1, zoneNameItem);
    
    //* Set Group Type
    QTableWidgetItem* groupNumItem = new QTableWidgetItem("Slice");
    groupNumItem->setTextAlignment(Qt::AlignCenter);
    ui->dataTable->setItem(newRow, 2, groupNumItem);
    
    //* Set Show Zone checkbox
    QWidget* checkBoxWidget = createCheckBoxWidget(true);
    QCheckBox* checkBox = checkBoxWidget->findChild<QCheckBox*>();
    if (checkBox) {
        checkBox->setProperty("boundaryRow", newRow);
        connect(checkBox, &QCheckBox::toggled, this, &ControlPanel::onShowZoneCheckBoxToggled);
    }
    ui->dataTable->setCellWidget(newRow, 3, checkBoxWidget);
    
    //* Set Contour Mode - 只为slice行连接响应函数
    QWidget* comboWidget = createComboBoxWidget();
    QComboBox* comboBox = comboWidget->findChild<QComboBox*>();
    if (comboBox) {
        // 设置属性，用于识别对应的cutplane
        comboBox->setProperty("cutplaneIndex", cutplaneIndex);
        connect(comboBox, QOverload<const QString &>::of(&QComboBox::currentTextChanged), 
                this, &ControlPanel::onSliceContourModeChanged);
    }
    ui->dataTable->setCellWidget(newRow, 4, comboWidget);
    
    //* Set Transculency
    QTableWidgetItem* transculencyItem = new QTableWidgetItem("1.0");
    transculencyItem->setTextAlignment(Qt::AlignCenter);
    ui->dataTable->setItem(newRow, 5, transculencyItem);
    
    //* Set Delete Button - 只为slice行连接删除功能
    QWidget* deleteWidget = createDeleteButtonWidget();
    QPushButton* deleteButton = deleteWidget->findChild<QPushButton*>();
    if (deleteButton) {
        // 设置按钮属性，用于识别对应的cutplane
        deleteButton->setProperty("cutplaneIndex", cutplaneIndex);
        connect(deleteButton, &QPushButton::clicked, this, &ControlPanel::onSliceDeleteClicked);
    }
    ui->dataTable->setCellWidget(newRow, 6, deleteWidget);
}

void ControlPanel::onMainModelTranscluencyChanged(double value)
{
    // 发送透明度变化信号
    emit mainModelTranscluencyChanged(value);
}

void ControlPanel::onSliceDeleteClicked()
{
    // 获取发送信号的按钮
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    // 获取对应的cutplane索引
    int cutplaneIndex = button->property("cutplaneIndex").toInt();
    
    // 发送删除请求信号
    emit sliceDeleteRequested(cutplaneIndex);
    
    // 从ControlPanel表格中删除对应行
    removeCutplaneFromTable(cutplaneIndex);
}

void ControlPanel::removeCutplaneFromTable(int cutplaneIndex)
{
    // 找到对应的行号
    int rowToRemove = -1;
    int cutplaneCount = 0;
    
    for (int i = 0; i < rowTypes.size(); i++) {
        if (rowTypes[i] == CUTPLANE) {
            if (cutplaneInfos[cutplaneCount].index == cutplaneIndex) {
                rowToRemove = i;
                break;
            }
            cutplaneCount++;
        }
    }
    
    // 如果找到对应的行，则删除
    if (rowToRemove != -1) {
        // 从表格中删除行
        ui->dataTable->removeRow(rowToRemove);
        
        // 从rowTypes中删除对应项
        rowTypes.erase(rowTypes.begin() + rowToRemove);
        
        // 从cutplaneInfos中删除对应项
        int cutplaneInfoIndex = rowToRemove - boundaryIndices.size();
        if (cutplaneInfoIndex >= 0 && cutplaneInfoIndex < cutplaneInfos.size()) {
            cutplaneInfos.erase(cutplaneInfos.begin() + cutplaneInfoIndex);
        }
        
        // 更新后续cutplane行的索引和显示名称
        int newCutplaneNumber = 1; // 重新编号从1开始
        for (int i = 0; i < rowTypes.size(); i++) {
            if (rowTypes[i] == CUTPLANE) {
                int currentCutplaneInfoIndex = i - boundaryIndices.size();
                if (currentCutplaneInfoIndex >= 0 && currentCutplaneInfoIndex < cutplaneInfos.size()) {
                    // 更新cutplaneInfo中的索引
                    cutplaneInfos[currentCutplaneInfoIndex].index = newCutplaneNumber - 1; // 内部索引从0开始
                    
                    // 更新Zone Number (S1*, S2*, S3*...)
                    QString newZoneNumber = QString("S%1*").arg(newCutplaneNumber);
                    QTableWidgetItem* zoneNumberItem = ui->dataTable->item(i, 0);
                    if (zoneNumberItem) {
                        zoneNumberItem->setText(newZoneNumber);
                    }
                    
                    // 更新Zone Name (Slice_1, Slice_2, Slice_3...)
                    QString newZoneName = QString("Slice_%1").arg(newCutplaneNumber);
                    QTableWidgetItem* zoneNameItem = ui->dataTable->item(i, 1);
                    if (zoneNameItem) {
                        zoneNameItem->setText(newZoneName);
                    }
                    
                    newCutplaneNumber++;
                }
            }
        }
    }
}

void ControlPanel::onSliceContourModeChanged(const QString &text)
{
    // 获取发送信号的下拉框
    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());
    if (!comboBox) return;
    
    // 获取对应的cutplane索引
    int cutplaneIndex = comboBox->property("cutplaneIndex").toInt();
    
    // 输出调试信息
    std::cout << "[Debug] Slice " << cutplaneIndex + 1 << " contour mode changed to: " << text.toStdString() << std::endl;
    
    // 发送contour mode变化信号
    emit sliceContourModeChanged(text);
    
    // 同步更新其他slice行的contour mode
    syncSliceContourMode(text, cutplaneIndex);
}

void ControlPanel::syncSliceContourMode(const QString &text, int excludeCutplaneIndex)
{
    // 遍历所有行，找到slice行
    for (int i = 0; i < rowTypes.size(); i++) {
        if (rowTypes[i] == CUTPLANE) {
            // 计算当前slice的cutplaneIndex
            int currentCutplaneInfoIndex = i - boundaryIndices.size();
            if (currentCutplaneInfoIndex >= 0 && currentCutplaneInfoIndex < cutplaneInfos.size()) {
                int currentCutplaneIndex = cutplaneInfos[currentCutplaneInfoIndex].index;
                
                // 跳过触发变化的slice
                if (currentCutplaneIndex == excludeCutplaneIndex) continue;
                
                // 获取对应的下拉框
                QWidget* comboWidget = ui->dataTable->cellWidget(i, 4);
                if (comboWidget) {
                    QComboBox* comboBox = comboWidget->findChild<QComboBox*>();
                    if (comboBox) {
                        // 临时阻塞信号，避免触发响应函数
                        comboBox->blockSignals(true);
                        comboBox->setCurrentText(text);
                        comboBox->blockSignals(false);
                        
                        std::cout << "[Debug] Synced Slice " << currentCutplaneIndex + 1 
                                  << " contour mode to: " << text.toStdString() << std::endl;
                    }
                }
            }
        }
    }
}