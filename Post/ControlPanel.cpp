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

    // 收集所有的boundary信息
    QStringList zoneNumbers;
    QStringList boundaryNames;
    QStringList zoneNames;
    
    int boundaryCount = 0;
    
    // 遍历所有Zone
    for (int i = 0; i < boundarys.size(); i++) {
        // 遍历每个Zone内的所有Boundary
        for (int j = 0; j < boundarys[i].size(); j++) {
            boundaryCount++;
            
            // Zone Number - 使用连续编号
            zoneNumbers.append(QString("%1*").arg(boundaryCount));
            
            // Boundary Name - 使用实际的boundary名称（第二层），使用c_str()方法
            QString boundaryName = QString(boundarys[i][j].name.c_str()).trimmed();

            boundaryNames.append(boundaryName);
            
            // Zone Name - 使用Zone名称（第一层），使用c_str()方法
            QString zoneName = QString(boundarys[i][j].zoneName.c_str()).trimmed();

            zoneNames.append(zoneName);

            // 在循环中添加调试输出
            std::cout << "Zone " << i << ", Boundary " << j 
            << ": name='" << boundarys[i][j].name 
            << "', zoneName='" << boundarys[i][j].zoneName << "'" << std::endl;
        }
    }
    
    // 设置表格行数为实际的boundary数量
    ui->dataTable->setRowCount(boundaryCount);
    
    // 填充表格
    for (int row = 0; row < boundaryCount; ++row) {
        // Zone Number
        QTableWidgetItem* zoneNumItem = new QTableWidgetItem(zoneNumbers[row]);
        zoneNumItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 0, zoneNumItem);
        
        // Zone Name - 显示实际的boundary名称
        QTableWidgetItem* zoneNameItem = new QTableWidgetItem(boundaryNames[row]);
        ui->dataTable->setItem(row, 1, zoneNameItem);
        
        // Group Number
        QTableWidgetItem* groupNumItem = new QTableWidgetItem("Main Model");
        groupNumItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 2, groupNumItem);
        
        // Show Zone (复选框)
        ui->dataTable->setCellWidget(row, 3, createCheckBoxWidget(true));
        
        // Contour Mode (下拉框)
        ui->dataTable->setCellWidget(row, 4, createComboBoxWidget());
        
        // Transculency
        QTableWidgetItem* transculencyItem = new QTableWidgetItem("0.5");
        transculencyItem->setTextAlignment(Qt::AlignCenter);
        ui->dataTable->setItem(row, 5, transculencyItem);
        
        // Zone Delete (按钮)
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