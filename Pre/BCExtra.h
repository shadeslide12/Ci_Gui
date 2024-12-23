#ifndef BCEXTRA_H
#define BCEXTRA_H

#include <QDialog>
#include <QTableWidgetItem>
#include "PreProcessSettings.h"
#include "UtilitiesGUIPre.h"
#include "loadprofile.h"

namespace Ui {
class BCExtra;
}

class BCExtra : public QDialog
{
    Q_OBJECT

public:
    explicit BCExtra(PreProcessSettings* cfg_in, int zone_id_in, int bc_id_in, std::string bc_text_in, QWidget *parent = nullptr);
    ~BCExtra();

    PreProcessSettings *cfg;
    std::string current_sub_zone;
    std::string current_boundary_type;

private slots:

    void on_clostbutton_clicked();

    void on_velocity_profile_num_in_edit_textChanged(const QString &arg1);

    void on_wall_angular_velocity_lineEdit_textChanged(const QString &arg1);

    void on_wall_velocity_u_lineEdit_textChanged(const QString &arg1);

    void on_wall_velocity_v_lineEdit_textChanged(const QString &arg1);

    void on_wall_velocity_w_lineEdit_textChanged(const QString &arg1);

    void on_wall_temperature_lineEdit_textChanged(const QString &arg1);

    void on_load_profile_button_clicked();

    void onItemChanged(QTableWidgetItem *item);

private:
    Ui::BCExtra *ui;

    void SetupUI();
    void SetupProfileTable();
    void ShowHideLayout(QLayout* lay, bool flag);

    int bc_type;
    int zone_id;
    int bc_id;
    std::string bc_text;

};

#endif // BCEXTRA_H
