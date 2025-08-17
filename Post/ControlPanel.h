#ifndef ControlPanel_h
#define ControlPanel_h

#include <QWidget>
#include <QDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <vtkAesReader.h>

namespace Ui {class ControlPanel; }

class ControlPanel: public QDialog
{
    Q_OBJECT

public:
    ControlPanel(QWidget* parent = nullptr);
    ~ControlPanel();

    void setupTable(std::vector<std::vector<vtkAesReader::Boundary>> boundarys);

signals:
    // 发送boundary可见性控制信号
    void setBoundarys(int meshNumber, int boundaryNumber, bool flag);

private slots:
    // 处理复选框状态变化
    void onShowZoneCheckBoxToggled(bool checked);

private:
    Ui::ControlPanel *ui;
    QWidget* createCheckBoxWidget(bool checked);
    QWidget* createComboBoxWidget();
    QWidget* createDeleteButtonWidget();
    
    // 存储boundary索引信息
    std::vector<std::pair<int, int>> boundaryIndices;  // 存储(meshIndex, boundaryIndex)对

};

#endif