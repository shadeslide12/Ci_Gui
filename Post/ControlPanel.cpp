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
        
        //* Set Transculency
        QTableWidgetItem* transculencyItem = new QTableWidgetItem("0.5");
        transculencyItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 5, transculencyItem);
        
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
    
    // 获取对应的boundary行号
    int row = checkBox->property("boundaryRow").toInt();
    
    // 检查行号是否有效
    if (row < 0 || row >= boundaryIndices.size()) return;
    
    // 获取对应的mesh和boundary索引
    int meshNumber = boundaryIndices[row].first;
    int boundaryNumber = boundaryIndices[row].second;
    
    // 发送信号控制boundary可见性
    emit setBoundarys(meshNumber, boundaryNumber, checked);
}