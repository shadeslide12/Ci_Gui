#include "Type4ConfigDialog.h"
#include "ui_Type4ConfigDialog.h"
#include <QLabel>

Type4ConfigDialog::Type4ConfigDialog(ConfigParser::monitor_struct& monitorConfig,
                                     const std::vector<std::string>& bcNames,
                                     QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Type4ConfigDialog)
    , m_monitorConfig(monitorConfig)
    , m_bcNames(bcNames)
{
    ui->setupUi(this);
    initializeUI();
    populateLists();
    restoreSelections();
    connectSignals();
}

Type4ConfigDialog::~Type4ConfigDialog()
{
    delete ui;
}

void Type4ConfigDialog::initializeUI()
{
    // 设置 Monitor 基本信息
    ui->fileNameValue->setText(QString::fromStdString(m_monitorConfig.filename));
    
    // 显示 Stage Inlet (face_id) 和 Stage Exit (match_face_id)
    if (m_monitorConfig.face_id > 0 && m_monitorConfig.face_id <= m_bcNames.size()) {
        ui->stageInletValue->setText(QString::fromStdString(m_bcNames[m_monitorConfig.face_id - 1]));
    }
    if (m_monitorConfig.match_face_id > 0 && m_monitorConfig.match_face_id <= m_bcNames.size()) {
        ui->stageExitValue->setText(QString::fromStdString(m_bcNames[m_monitorConfig.match_face_id - 1]));
    }
}

void Type4ConfigDialog::populateLists()
{
    // 为所有 5 个列表填充相同的边界面选项
    // 每个 item 的 data 存储 face_id (1-indexed)
    for (size_t i = 0; i < m_bcNames.size(); ++i) {
        QString bcName = QString::fromStdString(m_bcNames[i]);
        uint32_t faceId = static_cast<uint32_t>(i + 1);  // face_id 是 1-indexed
        
        // Secondary Inlets
        QListWidgetItem* item1 = new QListWidgetItem(bcName);
        item1->setData(Qt::UserRole, faceId);
        ui->secondaryInletsList->addItem(item1);
        
        // Secondary Exits
        QListWidgetItem* item2 = new QListWidgetItem(bcName);
        item2->setData(Qt::UserRole, faceId);
        ui->secondaryExitsList->addItem(item2);
        
        // Film Cooling Zones
        QListWidgetItem* item3 = new QListWidgetItem(bcName);
        item3->setData(Qt::UserRole, faceId);
        ui->filmcoolingList->addItem(item3);
        
        // Torque Walls
        QListWidgetItem* item4 = new QListWidgetItem(bcName);
        item4->setData(Qt::UserRole, faceId);
        ui->torqueWallsList->addItem(item4);
        
        // Mixing Planes
        QListWidgetItem* item5 = new QListWidgetItem(bcName);
        item5->setData(Qt::UserRole, faceId);
        ui->mixingPlanesList->addItem(item5);
    }
}

void Type4ConfigDialog::restoreSelections()
{
    // 恢复之前保存的选择状态
    setListSelection(ui->secondaryInletsList, m_monitorConfig.secondary_inlets);
    setListSelection(ui->secondaryExitsList, m_monitorConfig.secondary_exits);
    setListSelection(ui->filmcoolingList, m_monitorConfig.filmcooling_zones);
    setListSelection(ui->torqueWallsList, m_monitorConfig.torque_walls);
    setListSelection(ui->mixingPlanesList, m_monitorConfig.mixing_planes);
    
    // 更新计数标签
    updateCountLabel(ui->secondaryInletsList, ui->secondaryInletsCount);
    updateCountLabel(ui->secondaryExitsList, ui->secondaryExitsCount);
    updateCountLabel(ui->filmcoolingList, ui->filmcoolingCount);
    updateCountLabel(ui->torqueWallsList, ui->torqueWallsCount);
    updateCountLabel(ui->mixingPlanesList, ui->mixingPlanesCount);
}

void Type4ConfigDialog::connectSignals()
{
    // 选择变化时更新计数
    connect(ui->secondaryInletsList, &QListWidget::itemSelectionChanged,
            this, &Type4ConfigDialog::onSecondaryInletsSelectionChanged);
    connect(ui->secondaryExitsList, &QListWidget::itemSelectionChanged,
            this, &Type4ConfigDialog::onSecondaryExitsSelectionChanged);
    connect(ui->filmcoolingList, &QListWidget::itemSelectionChanged,
            this, &Type4ConfigDialog::onFilmcoolingSelectionChanged);
    connect(ui->torqueWallsList, &QListWidget::itemSelectionChanged,
            this, &Type4ConfigDialog::onTorqueWallsSelectionChanged);
    connect(ui->mixingPlanesList, &QListWidget::itemSelectionChanged,
            this, &Type4ConfigDialog::onMixingPlanesSelectionChanged);
    
    // Clear 按钮
    connect(ui->clearSecondaryInletsBtn, &QPushButton::clicked,
            this, &Type4ConfigDialog::onClearSecondaryInlets);
    connect(ui->clearSecondaryExitsBtn, &QPushButton::clicked,
            this, &Type4ConfigDialog::onClearSecondaryExits);
    connect(ui->clearFilmcoolingBtn, &QPushButton::clicked,
            this, &Type4ConfigDialog::onClearFilmcooling);
    connect(ui->clearTorqueWallsBtn, &QPushButton::clicked,
            this, &Type4ConfigDialog::onClearTorqueWalls);
    connect(ui->clearMixingPlanesBtn, &QPushButton::clicked,
            this, &Type4ConfigDialog::onClearMixingPlanes);
}

void Type4ConfigDialog::setListSelection(QListWidget* listWidget, const std::vector<uint32_t>& faceIds)
{
    // 清除所有选择
    listWidget->clearSelection();
    
    // 根据 faceIds 设置选中状态
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* item = listWidget->item(i);
        uint32_t itemFaceId = item->data(Qt::UserRole).toUInt();
        
        for (uint32_t faceId : faceIds) {
            if (itemFaceId == faceId) {
                item->setSelected(true);
                break;
            }
        }
    }
}

std::vector<uint32_t> Type4ConfigDialog::getSelectedFaceIds(QListWidget* listWidget) const
{
    std::vector<uint32_t> result;
    QList<QListWidgetItem*> selectedItems = listWidget->selectedItems();
    
    for (QListWidgetItem* item : selectedItems) {
        uint32_t faceId = item->data(Qt::UserRole).toUInt();
        result.push_back(faceId);
    }
    
    return result;
}

void Type4ConfigDialog::updateCountLabel(QListWidget* listWidget, QLabel* countLabel)
{
    int count = listWidget->selectedItems().count();
    countLabel->setText(QString("Selected: %1").arg(count));
}

// Selection changed slots
void Type4ConfigDialog::onSecondaryInletsSelectionChanged()
{
    updateCountLabel(ui->secondaryInletsList, ui->secondaryInletsCount);
}

void Type4ConfigDialog::onSecondaryExitsSelectionChanged()
{
    updateCountLabel(ui->secondaryExitsList, ui->secondaryExitsCount);
}

void Type4ConfigDialog::onFilmcoolingSelectionChanged()
{
    updateCountLabel(ui->filmcoolingList, ui->filmcoolingCount);
}

void Type4ConfigDialog::onTorqueWallsSelectionChanged()
{
    updateCountLabel(ui->torqueWallsList, ui->torqueWallsCount);
}

void Type4ConfigDialog::onMixingPlanesSelectionChanged()
{
    updateCountLabel(ui->mixingPlanesList, ui->mixingPlanesCount);
}

// Clear button slots
void Type4ConfigDialog::onClearSecondaryInlets()
{
    ui->secondaryInletsList->clearSelection();
}

void Type4ConfigDialog::onClearSecondaryExits()
{
    ui->secondaryExitsList->clearSelection();
}

void Type4ConfigDialog::onClearFilmcooling()
{
    ui->filmcoolingList->clearSelection();
}

void Type4ConfigDialog::onClearTorqueWalls()
{
    ui->torqueWallsList->clearSelection();
}

void Type4ConfigDialog::onClearMixingPlanes()
{
    ui->mixingPlanesList->clearSelection();
}

// Getter functions
std::vector<uint32_t> Type4ConfigDialog::getSecondaryInlets() const
{
    return getSelectedFaceIds(ui->secondaryInletsList);
}

std::vector<uint32_t> Type4ConfigDialog::getSecondaryExits() const
{
    return getSelectedFaceIds(ui->secondaryExitsList);
}

std::vector<uint32_t> Type4ConfigDialog::getFilmcoolingZones() const
{
    return getSelectedFaceIds(ui->filmcoolingList);
}

std::vector<uint32_t> Type4ConfigDialog::getTorqueWalls() const
{
    return getSelectedFaceIds(ui->torqueWallsList);
}

std::vector<uint32_t> Type4ConfigDialog::getMixingPlanes() const
{
    return getSelectedFaceIds(ui->mixingPlanesList);
}
