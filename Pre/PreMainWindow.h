#pragma once
#ifndef PREMAINWINDOW_H
#define PREMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QComboBox>
#include <QLineEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <QIcon>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QChartView>
#include "Residual_Plot.h"
#include "Perform_Plot.h"
#include "MonitorPlot.h"

#include "PreProcessSettings.h"
#include "BCExtra.h"
#include "SelectFile.h"
#include "UtilitiesGUIPre.h"
#include "DataStructure.h"

#ifndef NO_VTK_WINDOW
#include "vtkCGNSReader.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include "vtkDataSetMapper.h"
#include <QVTKOpenGLNativeWidget.h>
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class PreMainWindow;
}
QT_END_NAMESPACE

class PreMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    PreMainWindow(QWidget *parent = nullptr);
    ~PreMainWindow();

    PreProcessSettings cfg;
    SelectFile *NewCase;

private slots:

    void handleError(QProcess::ProcessError error);

    void on_actionGeneral_triggered();
    void on_actionBC_triggered();
    void on_actionTurbo_triggered();
    void on_actionSolver_triggered();

    void on_stackedWidget_currentChanged(int i);

    void on_annular_checkbox_toggled(bool checked);

    void on_actionNew_triggered();

    void on_actionactionSaveTab_triggered();

    void on_tb_type_combo_currentTextChanged(const QString &arg1);

    void Show_BC_List(QListWidgetItem* item);
    void Show_FilmCooling_List(QListWidgetItem* item);
//    void Show_FilmCooling_Tree(int zone_id);

    void onBCComboChanged(QComboBox* cmb, QPushButton* btn, int bnd_id, int bc_id);
    void onTurboRSComboChanged(QComboBox* cmb, QLineEdit* edt, int zone_id);
    void onTurboRSValueChanged(QLineEdit* edt, int zone_id);
    void onUpstreamChanged(QComboBox* edt, QComboBox *edt2, int zone_id);
    void onDownstreamChanged(QComboBox* edt, QComboBox *edt2, int zone_id);
    void onPassageRepeatChanged(QLineEdit* edt, int zone_id);
    void onBCExtraClicked(QComboBox *bmd, int bnd_id, int bc_id);
    void onFilmComboChanged(QComboBox* cmb, QPushButton* btn, int bnd_id, int bc_id);
    void onFilmBCbuttonClicked(QComboBox *bmd, int bnd_id, int bc_id);

    void on_actionLoadMain_triggered();

    void on_conbo_rans_currentTextChanged(const QString &arg1);

    void on_check_wf_toggled(bool checked);

    void on_lineEdit_des_dx_textEdited(const QString &arg1);

    void on_lineEdit_les_dx_textEdited(const QString &arg1);

    void on_lineEdit_les_dt_textEdited(const QString &arg1);

    void on_rho_lineEdit_textEdited(const QString &arg1);
    void on_u_lineEdit_textEdited(const QString &arg1);
    void on_v_lineEdit_textEdited(const QString &arg1);
    void on_w_lineEdit_textEdited(const QString &arg1);
    void on_p_lineEdit_textEdited(const QString &arg1);
    void on_sa_lineEdit_textEdited(const QString &arg1);
    void on_k_lineEdit_textEdited(const QString &arg1);
    void on_omega_lineEdit_textEdited(const QString &arg1);
    void on_epsilon_lineEdit_textEdited(const QString &arg1);
    void on_gamma_lineEdit_textEdited(const QString &arg1);

    void on_iteration_step_lineEdit_textEdited(const QString &arg1);

    void on_CFL_lineEdit_textEdited(const QString &arg1);

    void on_CFL_ramp_lineEdit_textEdited(const QString &arg1);

    void on_residual_lineEdit_textEdited(const QString &arg1);

    void on_mg_level_spinBox_valueChanged(int arg1);

    void on_period_lineEdit_textEdited(const QString &arg1);

    void on_n_cycle_lineEdit_textEdited(const QString &arg1);

    void on_step_per_cycle_lineEdit_textEdited(const QString &arg1);

    void on_unsteady_checkbox_toggled(bool checked);

    void on_output_unsteady_lineEdit_textChanged(const QString &arg1);

    void on_output_steady_lineEdit_textChanged(const QString &arg1);

    void on_start_simulation_button_clicked();

    void on_stop_simulation_button_clicked();

    void on_gas_type_combo_currentTextChanged(const QString &arg1);

    void on_actionactionFilmCooling_triggered();

    void on_film_checkbox_toggled(bool checked);

//    void on_add_film_pushButton_clicked();

    void GetMonitorTree();

    void on_pushButton_clicked();

    void onMonitorTypeChange(QComboBox *cmb1, QComboBox *cmb2, int id);
    void onMonitorFaceChange(QComboBox *cmb1, int id);
    void onMonitorMFaceChange(QComboBox *cmb1, int id);
    void onMonitorAverageChange(QComboBox *cmb1, int id);
    void onMonitorDeleteMonitor(int id);

    void on_continue_simulation_button_clicked();

    void on_run_pre_process_clicked();

    void on_saveYAMLButton_clicked();

    void on_checkBox_passage_repeat_clicked(bool checked);

    void on_checkBox_helicity_toggled(bool checked);

    void on_checkBox_cmott_toggled(bool checked);

    void on_checkBox_kl_toggled(bool checked);

    void on_checkBox_transition_toggled(bool checked);

    void on_comboBox_qcr_currentTextChanged(const QString &arg1);

    void on_lineEdit_axis_x_textEdited(const QString &arg1);
    void on_lineEdit_axis_y_textEdited(const QString &arg1);
    void on_lineEdit_axis_z_textEdited(const QString &arg1);
    void on_lineEdit_factor_x_textEdited(const QString &arg1);
    void on_lineEdit_factor_y_textEdited(const QString &arg1);
    void on_lineEdit_factor_z_textEdited(const QString &arg1);

    void on_checkBox_performance_toggled(bool checked);

    void on_save_p_button_clicked();

    void on_load_p_button_clicked();

    void getBackPressure();

    void on_target_p_value_editingFinished();

    void on_spinCPU_valueChanged(int arg1);

    void on_skip_pre_checkBox_toggled(bool checked);

    void on_generate_film_boundary_clicked();

private:
    Ui::PreMainWindow *ui;
    QProcess *process;

    void Setup_UI();

    void runOutputWindowReady();
    void runOutputWindowError();

    void Setup_Validators();

    void Assign_Value();
    void Assign_General();
    void Assign_Turbomachinery();
    void Assign_BC();
    void Assign_Film();
    void Assign_Run();
    void Assign_Solver();
    void Assign_VTK();

    void setIcons();

    void showFinishDialog(int exitCode, QProcess::ExitStatus exitStatus);

    int current_zone=0;

    std::string GUI_yaml="GUI.yaml";

    QTimer *timer;

    bool isVTKWindow=false;

    void EnablePerformanceCurve(bool isEnable);
    void ShowPerformanceCurve(bool isShow);
    void ShowPassageRepeatTree();

//*Residual Start Here
private:
    Residual_Plot* residualplot;
    QFile residual_DataFile;
    qint64 lastResFilePos = 0;
signals:
    void s_UpdateResidual(const int& iteration,const double& convergence1,const double convergence2);
private slots:
    void updateResidual();

//*Monitor Start Here

private slots:
    void onSelectFile();
    void onVariableSelectionChanged();

private:
    MonitorPlot* monitorplot;
    QString monitorFilePath;
    QVector<int> iteration;
    MonitorVariableTable monitorVariableTable;
    QFile inletFile;
    QFile outletFile;
    QFile perfFile;
    QList<QString> displayVariableList;
    QVector<qint64> monfilePositionTable;

    void updateMonitorData();
//*Perf Start Here
private:
    void updatePerfData();
    QChartView* performPlotView;
    Perform_Plot* performplot;

//*AutoRun Start Here
private:
    QList<double> pressureList_AutoRun;
    int currentIndex_AutoRunPressure = 0;
    bool autoRunning = 0;

    bool generatePressurePoints();
    void autoSingleRun();
    void saveCurrentOutputFile();
private slots:
    void on_Btn_Start_AutoRun_clicked();
    void on_Btn_Skip_AutoRun_clicked();
    void on_Btn_End_AutoRun_clicked();

//*Others Start Here
private:
    void setResultTableData();
    bool syncMainWindowTheme = 0 ;

    int indexResultTable = 0 ;

private slots:
    void updateInterfaceUI();

private:
//    renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
//    renderer = vtkSmartPointer<vtkRenderer>::New();
//    vtkWidget = new QVTKOpenGLNativeWidget(this);
#ifndef NO_VTK_WINDOW
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow= vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> renderer= vtkSmartPointer<vtkRenderer>::New();
    QVTKOpenGLNativeWidget *vtkWidget= new QVTKOpenGLNativeWidget(this);
#endif
};
#endif // PREMAINWINDOW_H
