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


private slots:

private:
    Ui::ControlPanel *ui;
    QWidget* createCheckBoxWidget(bool checked);
    QWidget* createComboBoxWidget();
    QWidget* createDeleteButtonWidget();

};

#endif