#ifndef TYPE4CONFIGDIALOG_H
#define TYPE4CONFIGDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QLabel>
#include <vector>
#include <string>
#include "ConfigParser.h"

namespace Ui {
class Type4ConfigDialog;
}

class Type4ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Type4ConfigDialog(ConfigParser::monitor_struct& monitorConfig,
                               const std::vector<std::string>& bcNames,
                               QWidget *parent = nullptr);
    ~Type4ConfigDialog();

    // 获取用户选择的结果
    std::vector<uint32_t> getSecondaryInlets() const;
    std::vector<uint32_t> getSecondaryExits() const;
    std::vector<uint32_t> getFilmcoolingZones() const;
    std::vector<uint32_t> getTorqueWalls() const;
    std::vector<uint32_t> getMixingPlanes() const;

private slots:
    void onSecondaryInletsSelectionChanged();
    void onSecondaryExitsSelectionChanged();
    void onFilmcoolingSelectionChanged();
    void onTorqueWallsSelectionChanged();
    void onMixingPlanesSelectionChanged();

    void onClearSecondaryInlets();
    void onClearSecondaryExits();
    void onClearFilmcooling();
    void onClearTorqueWalls();
    void onClearMixingPlanes();

private:
    Ui::Type4ConfigDialog *ui;
    
    ConfigParser::monitor_struct& m_monitorConfig;
    const std::vector<std::string>& m_bcNames;

    void initializeUI();
    void populateLists();
    void restoreSelections();
    void connectSignals();
    
    // 辅助函数：从 QListWidget 获取选中项的 face_id 列表
    std::vector<uint32_t> getSelectedFaceIds(QListWidget* listWidget) const;
    
    // 辅助函数：根据 face_id 列表设置 QListWidget 的选中状态
    void setListSelection(QListWidget* listWidget, const std::vector<uint32_t>& faceIds);
    
    // 更新选中计数标签
    void updateCountLabel(QListWidget* listWidget, QLabel* countLabel);
};

#endif // TYPE4CONFIGDIALOG_H
