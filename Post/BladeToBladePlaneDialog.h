#pragma once
#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class BladeToBladePlaneDialog; }
QT_END_NAMESPACE

class BladeToBladePlaneDialog : public QDialog {
Q_OBJECT

public:
    explicit BladeToBladePlaneDialog(QWidget *parent = nullptr);

    ~BladeToBladePlaneDialog() override;
private slots:
    void setParameters();

signals:
    void finishSetParameters(double);

private:
    Ui::BladeToBladePlaneDialog *ui;
    double span;  // 0-1, height percentage
};
