/********************************************************************************
** Form generated from reading UI file 'PreMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREMAINWINDOW_H
#define UI_PREMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreMainWindow
{
public:
    QAction *actionGeneral;
    QAction *actionTurbo;
    QAction *actionSolver;
    QAction *actionBC;
    QAction *actionMonitor;
    QAction *actionNew;
    QAction *actionLoadMain;
    QAction *actionactionSaveTab;
    QAction *actionactionFilmCooling;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *general;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_general;
    QVBoxLayout *verticalLayout;
    QCheckBox *unsteady_checkbox;
    QCheckBox *annular_checkbox;
    QCheckBox *film_checkbox;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *Turbulence_area;
    QLabel *label_turbulence_model;
    QHBoxLayout *horizontalLayout;
    QLabel *tb_name_label;
    QComboBox *tb_type_combo;
    QGridLayout *rans_layout;
    QLabel *label_rans1;
    QCheckBox *check_wf;
    QCheckBox *checkBox_transition;
    QLabel *label_kl;
    QLabel *label_wf1;
    QComboBox *conbo_rans;
    QLabel *label_transition;
    QCheckBox *checkBox_helicity;
    QCheckBox *checkBox_cmott;
    QComboBox *comboBox_qcr;
    QCheckBox *checkBox_kl;
    QLabel *label_cmott;
    QLabel *label_qcr;
    QLabel *label_helicity;
    QHBoxLayout *DES_area;
    QLabel *label_des_dx;
    QLineEdit *lineEdit_des_dx;
    QGridLayout *LES_area;
    QLineEdit *lineEdit_les_dx;
    QLabel *label_les_dx;
    QLabel *label_7;
    QGridLayout *LES_area_2;
    QLabel *gas_friction_label;
    QLabel *gas_type_label;
    QLineEdit *gas_friction_lineEdit;
    QComboBox *gas_type_combo;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *DES_area_2;
    QLabel *label_10;
    QGridLayout *LES_area_4;
    QLabel *label_12;
    QLineEdit *lineEdit_factor_x;
    QLabel *gas_friction_label_3;
    QLineEdit *lineEdit_factor_y;
    QLabel *gas_friction_label_5;
    QLabel *label;
    QLineEdit *lineEdit_axis_x;
    QLineEdit *lineEdit_axis_y;
    QLabel *gas_friction_label_6;
    QLabel *gas_friction_label_4;
    QLabel *gas_friction_label_7;
    QLineEdit *lineEdit_axis_z;
    QLabel *gas_friction_label_8;
    QLineEdit *lineEdit_factor_z;
    QLabel *label_13;
    QSpacerItem *verticalSpacer_2;
    QWidget *turbomachinery;
    QLabel *label_turbomachinery;
    QLabel *label_3;
    QLabel *label_4;
    QTreeWidget *turbo_zone_tree;
    QTreeWidget *turbo_interface_tree;
    QLabel *passage_label;
    QTreeWidget *passage_repeat_tree;
    QCheckBox *checkBox_passage_repeat;
    QLabel *interface_type_label;
    QWidget *solver;
    QWidget *gridLayoutWidget_2;
    QGridLayout *GridLayoutFlow;
    QLabel *gamma_label;
    QLineEdit *p_lineEdit;
    QLabel *k_unit_label;
    QLabel *v_label;
    QLabel *sa_label;
    QLineEdit *v_lineEdit;
    QLabel *label_unit_w;
    QLabel *omega_label;
    QLabel *pressure_unit_label;
    QLabel *label_unit_v;
    QLineEdit *epsilon_lineEdit;
    QSpacerItem *verticalSpacer_4;
    QLineEdit *gamma_lineEdit;
    QLineEdit *k_lineEdit;
    QLineEdit *rho_lineEdit;
    QLabel *omega_unit_label;
    QLabel *label_unit_u;
    QLabel *rho_label;
    QLabel *epsilon_label;
    QLabel *sa_unit_label;
    QLabel *label_unit_density;
    QLabel *u_label;
    QLabel *k_label;
    QLabel *p_label;
    QLineEdit *u_lineEdit;
    QLabel *w_labe;
    QLineEdit *omega_lineEdit;
    QLabel *epsilon_unit_label;
    QLineEdit *w_lineEdit;
    QLineEdit *sa_lineEdit;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_advanced;
    QLabel *period_match_label;
    QLabel *residual_unit;
    QLineEdit *period_match_lineEdit;
    QLabel *CFL_ramp_label;
    QLabel *label_5;
    QLabel *MG_level_label;
    QPushButton *run_pre_process;
    QPushButton *saveYAMLButton;
    QSpinBox *mg_level_spinBox;
    QLineEdit *CFL_ramp_lineEdit;
    QLineEdit *residual_lineEdit;
    QLabel *CFL_ramp_label_2;
    QSpacerItem *verticalSpacer_5;
    QCheckBox *skip_pre_checkBox;
    QLabel *label_monitor;
    QPushButton *load_steady_flow;
    QWidget *boundary_conditions;
    QLabel *label_bc;
    QListWidget *Zone_list;
    QListWidget *BC_list;
    QLabel *label_bc_2;
    QWidget *filmCool;
    QLabel *label_2;
    QListWidget *Zone_list_2;
    QLabel *label_8;
    QLabel *label_11;
    QListWidget *FilmCooling_List;
    QPushButton *generate_film_boundary;
    QWidget *savetab;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *unstead_simulation_layout_2;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QSpinBox *spinCPU;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *unstead_simulation_layout_3;
    QPushButton *start_simulation_button;
    QPushButton *continue_simulation_button;
    QPushButton *stop_simulation_button;
    QCheckBox *checkBox_performance;
    QGridLayout *curve_grid_layout;
    QLabel *current_p_label;
    QLineEdit *target_p_value;
    QLabel *current_p_value;
    QLabel *target_p_label;
    QPushButton *save_p_button;
    QPushButton *load_p_button;
    QLabel *unsteady_simulation_label;
    QGridLayout *unstead_simulation_layout;
    QLineEdit *step_per_cycle_lineEdit;
    QLineEdit *period_lineEdit;
    QLabel *output_unsteady_label;
    QLineEdit *output_unsteady_lineEdit;
    QLabel *period_label;
    QLabel *label_les_dt;
    QLineEdit *n_cycle_lineEdit;
    QLabel *step_per_cycle_label;
    QLineEdit *lineEdit_les_dt;
    QLabel *n_cycle_label;
    QLabel *period_unit_label;
    QLabel *steady_iteration_label;
    QLabel *unsteady_inner_label;
    QGridLayout *steady_simulation_layout;
    QLineEdit *CFL_lineEdit;
    QLineEdit *iteration_step_lineEdit;
    QLabel *iteration_step_label;
    QLabel *CFL_label;
    QLineEdit *output_steady_lineEdit;
    QLabel *output_steady_label;
    QGridLayout *steady_simulation_layout_2;
    QLabel *monitor_label;
    QPushButton *pushButton;
    QTreeWidget *monitor_tree;
    QWidget *widget_13;
    QGridLayout *gridLayout;
    QLabel *label_44;
    QLabel *label_14;
    QLineEdit *LEdit_EndPressure_AutoRun;
    QPushButton *Btn_Skip_AutoRun;
    QPushButton *Btn_End_AutoRun;
    QLineEdit *LEdit_StartPressure_AutoRun;
    QLabel *label_15;
    QLabel *label_43;
    QLineEdit *LEdit_NumPoints_AutoRun;
    QPushButton *Btn_Start_AutoRun;
    QSpacerItem *verticalSpacer_7;
    QTabWidget *Show_MainWindow;
    QWidget *Show_Model;
    QVBoxLayout *RunGraphLayout;
    QWidget *vtkPlaceHolder;
    QTextEdit *runOutputWindow;
    QWidget *Show_Convergence;
    QHBoxLayout *horizontalLayout_14;
    QWidget *Panel_Conver;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_27;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_17;
    QPushButton *Btn_AutoScale_Res;
    QPushButton *Btn_ManualScale_Res;
    QWidget *control_panel_Range_Res;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_29;
    QWidget *Widget_Res_RangeX;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_25;
    QLineEdit *Line_RangeX_Res_Min;
    QLabel *label_26;
    QLineEdit *Line_RangeX_Res_Max;
    QLabel *label_28;
    QWidget *Widget_Res_RangeY1;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_23;
    QLineEdit *Line_RangeY1_Res_Min;
    QLabel *label_24;
    QLineEdit *Line_RangeY1_Res_Max;
    QLabel *label_33;
    QWidget *Widget_Res_RangeY1_2;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_31;
    QLineEdit *Line_RangeY2_Res_Min;
    QLabel *label_32;
    QLineEdit *Line_RangeY2_Res_Max;
    QWidget *widget_14;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_45;
    QWidget *Widget_History;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *CBtn_History;
    QPushButton *Btn_ClearHistory;
    QWidget *panel_Theme;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_34;
    QComboBox *CBox_Theme;
    QPushButton *Btn_SyncWindowTheme;
    QSpacerItem *verticalSpacer_6;
    QWidget *Plot_Convergence;
    QVBoxLayout *LayoutforConverPlot;
    QWidget *Show_Monitor;
    QHBoxLayout *horizontalLayout_9;
    QWidget *Panel_Monitor;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_22;
    QPushButton *Btn_SelectMonitor;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_30;
    QListWidget *List_Variable;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *Btn_AutoScale_Mon;
    QPushButton *Btn_ManualScale_Mon;
    QWidget *control_panel_Range_Mon;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_16;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_18;
    QLineEdit *Line_RangeX_Mon_Min;
    QLabel *label_19;
    QLineEdit *Line_RangeX_Mon_Max;
    QLabel *label_17;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_20;
    QLineEdit *Line_RangeY_Mon_Min;
    QLabel *label_21;
    QLineEdit *Line_RangeY_Mon_Max;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_11;
    QWidget *Monitor;
    QHBoxLayout *Lay_MonitorPlot;
    QWidget *Show_Performance;
    QHBoxLayout *horizontalLayout_24;
    QWidget *Panel_Monitor_2;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_35;
    QWidget *widget_12;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_36;
    QComboBox *CBtn_SelectPerfVariable;
    QWidget *control_panel_Range_Mon_2;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_37;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_38;
    QLineEdit *Line_RangeX_Perf_Min;
    QLabel *label_39;
    QLineEdit *Line_RangeX_Perf_Max;
    QLabel *label_40;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_41;
    QLineEdit *Line_RangeY_Perf_Min;
    QLabel *label_42;
    QLineEdit *Line_RangeY_Perf_Max;
    QWidget *widget_7;
    QPushButton *Btn_ClearPerformData;
    QPushButton *pushButton_7;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_23;
    QWidget *Plot_Performance;
    QVBoxLayout *LayoutforPerform;
    QWidget *Show_Result;
    QVBoxLayout *verticalLayout_9;
    QTableWidget *Result_Table;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;

    void setupUi(QMainWindow *PreMainWindow)
    {
        if (PreMainWindow->objectName().isEmpty())
            PreMainWindow->setObjectName(QString::fromUtf8("PreMainWindow"));
        PreMainWindow->setEnabled(true);
        PreMainWindow->resize(1920, 1109);
        QFont font;
        font.setPointSize(10);
        PreMainWindow->setFont(font);
        actionGeneral = new QAction(PreMainWindow);
        actionGeneral->setObjectName(QString::fromUtf8("actionGeneral"));
        actionTurbo = new QAction(PreMainWindow);
        actionTurbo->setObjectName(QString::fromUtf8("actionTurbo"));
        actionTurbo->setEnabled(false);
        actionSolver = new QAction(PreMainWindow);
        actionSolver->setObjectName(QString::fromUtf8("actionSolver"));
        actionSolver->setCheckable(false);
        actionBC = new QAction(PreMainWindow);
        actionBC->setObjectName(QString::fromUtf8("actionBC"));
        actionMonitor = new QAction(PreMainWindow);
        actionMonitor->setObjectName(QString::fromUtf8("actionMonitor"));
        actionNew = new QAction(PreMainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionLoadMain = new QAction(PreMainWindow);
        actionLoadMain->setObjectName(QString::fromUtf8("actionLoadMain"));
        actionactionSaveTab = new QAction(PreMainWindow);
        actionactionSaveTab->setObjectName(QString::fromUtf8("actionactionSaveTab"));
        actionactionSaveTab->setMenuRole(QAction::NoRole);
        actionactionFilmCooling = new QAction(PreMainWindow);
        actionactionFilmCooling->setObjectName(QString::fromUtf8("actionactionFilmCooling"));
        actionactionFilmCooling->setMenuRole(QAction::NoRole);
        centralwidget = new QWidget(PreMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setEnabled(true);
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        scrollArea = new QScrollArea(widget_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(350, 700));
        scrollArea->setMaximumSize(QSize(350, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setEnabled(true);
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 348, 993));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_4 = new QWidget(scrollAreaWidgetContents_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout_3->addWidget(widget_4);

        stackedWidget = new QStackedWidget(scrollAreaWidgetContents_2);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setEnabled(true);
        QFont font1;
        font1.setFamily(QString::fromUtf8(".AppleSystemUIFont"));
        font1.setPointSize(10);
        stackedWidget->setFont(font1);
        general = new QWidget();
        general->setObjectName(QString::fromUtf8("general"));
        verticalLayoutWidget_3 = new QWidget(general);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(10, 0, 241, 141));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_general = new QLabel(verticalLayoutWidget_3);
        label_general->setObjectName(QString::fromUtf8("label_general"));

        verticalLayout_5->addWidget(label_general);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        unsteady_checkbox = new QCheckBox(verticalLayoutWidget_3);
        unsteady_checkbox->setObjectName(QString::fromUtf8("unsteady_checkbox"));

        verticalLayout->addWidget(unsteady_checkbox);

        annular_checkbox = new QCheckBox(verticalLayoutWidget_3);
        annular_checkbox->setObjectName(QString::fromUtf8("annular_checkbox"));
        annular_checkbox->setEnabled(true);

        verticalLayout->addWidget(annular_checkbox);

        film_checkbox = new QCheckBox(verticalLayoutWidget_3);
        film_checkbox->setObjectName(QString::fromUtf8("film_checkbox"));

        verticalLayout->addWidget(film_checkbox);


        verticalLayout_5->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        verticalLayoutWidget_2 = new QWidget(general);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(10, 150, 301, 571));
        Turbulence_area = new QVBoxLayout(verticalLayoutWidget_2);
        Turbulence_area->setObjectName(QString::fromUtf8("Turbulence_area"));
        Turbulence_area->setContentsMargins(0, 0, 0, 0);
        label_turbulence_model = new QLabel(verticalLayoutWidget_2);
        label_turbulence_model->setObjectName(QString::fromUtf8("label_turbulence_model"));

        Turbulence_area->addWidget(label_turbulence_model);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tb_name_label = new QLabel(verticalLayoutWidget_2);
        tb_name_label->setObjectName(QString::fromUtf8("tb_name_label"));

        horizontalLayout->addWidget(tb_name_label);

        tb_type_combo = new QComboBox(verticalLayoutWidget_2);
        tb_type_combo->addItem(QString());
        tb_type_combo->addItem(QString());
        tb_type_combo->addItem(QString());
        tb_type_combo->setObjectName(QString::fromUtf8("tb_type_combo"));

        horizontalLayout->addWidget(tb_type_combo);


        Turbulence_area->addLayout(horizontalLayout);

        rans_layout = new QGridLayout();
        rans_layout->setObjectName(QString::fromUtf8("rans_layout"));
        label_rans1 = new QLabel(verticalLayoutWidget_2);
        label_rans1->setObjectName(QString::fromUtf8("label_rans1"));

        rans_layout->addWidget(label_rans1, 0, 0, 1, 1);

        check_wf = new QCheckBox(verticalLayoutWidget_2);
        check_wf->setObjectName(QString::fromUtf8("check_wf"));

        rans_layout->addWidget(check_wf, 2, 1, 1, 1);

        checkBox_transition = new QCheckBox(verticalLayoutWidget_2);
        checkBox_transition->setObjectName(QString::fromUtf8("checkBox_transition"));

        rans_layout->addWidget(checkBox_transition, 1, 1, 1, 1);

        label_kl = new QLabel(verticalLayoutWidget_2);
        label_kl->setObjectName(QString::fromUtf8("label_kl"));

        rans_layout->addWidget(label_kl, 3, 0, 1, 1);

        label_wf1 = new QLabel(verticalLayoutWidget_2);
        label_wf1->setObjectName(QString::fromUtf8("label_wf1"));

        rans_layout->addWidget(label_wf1, 2, 0, 1, 1);

        conbo_rans = new QComboBox(verticalLayoutWidget_2);
        conbo_rans->addItem(QString());
        conbo_rans->addItem(QString());
        conbo_rans->addItem(QString());
        conbo_rans->addItem(QString());
        conbo_rans->setObjectName(QString::fromUtf8("conbo_rans"));

        rans_layout->addWidget(conbo_rans, 0, 1, 1, 1);

        label_transition = new QLabel(verticalLayoutWidget_2);
        label_transition->setObjectName(QString::fromUtf8("label_transition"));

        rans_layout->addWidget(label_transition, 1, 0, 1, 1);

        checkBox_helicity = new QCheckBox(verticalLayoutWidget_2);
        checkBox_helicity->setObjectName(QString::fromUtf8("checkBox_helicity"));

        rans_layout->addWidget(checkBox_helicity, 5, 1, 1, 1);

        checkBox_cmott = new QCheckBox(verticalLayoutWidget_2);
        checkBox_cmott->setObjectName(QString::fromUtf8("checkBox_cmott"));

        rans_layout->addWidget(checkBox_cmott, 4, 1, 1, 1);

        comboBox_qcr = new QComboBox(verticalLayoutWidget_2);
        comboBox_qcr->addItem(QString());
        comboBox_qcr->addItem(QString());
        comboBox_qcr->addItem(QString());
        comboBox_qcr->setObjectName(QString::fromUtf8("comboBox_qcr"));

        rans_layout->addWidget(comboBox_qcr, 6, 1, 1, 1);

        checkBox_kl = new QCheckBox(verticalLayoutWidget_2);
        checkBox_kl->setObjectName(QString::fromUtf8("checkBox_kl"));

        rans_layout->addWidget(checkBox_kl, 3, 1, 1, 1);

        label_cmott = new QLabel(verticalLayoutWidget_2);
        label_cmott->setObjectName(QString::fromUtf8("label_cmott"));

        rans_layout->addWidget(label_cmott, 4, 0, 1, 1);

        label_qcr = new QLabel(verticalLayoutWidget_2);
        label_qcr->setObjectName(QString::fromUtf8("label_qcr"));

        rans_layout->addWidget(label_qcr, 6, 0, 1, 1);

        label_helicity = new QLabel(verticalLayoutWidget_2);
        label_helicity->setObjectName(QString::fromUtf8("label_helicity"));

        rans_layout->addWidget(label_helicity, 5, 0, 1, 1);


        Turbulence_area->addLayout(rans_layout);

        DES_area = new QHBoxLayout();
        DES_area->setObjectName(QString::fromUtf8("DES_area"));
        label_des_dx = new QLabel(verticalLayoutWidget_2);
        label_des_dx->setObjectName(QString::fromUtf8("label_des_dx"));

        DES_area->addWidget(label_des_dx);

        lineEdit_des_dx = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_des_dx->setObjectName(QString::fromUtf8("lineEdit_des_dx"));

        DES_area->addWidget(lineEdit_des_dx);


        Turbulence_area->addLayout(DES_area);

        LES_area = new QGridLayout();
        LES_area->setObjectName(QString::fromUtf8("LES_area"));
        lineEdit_les_dx = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_les_dx->setObjectName(QString::fromUtf8("lineEdit_les_dx"));

        LES_area->addWidget(lineEdit_les_dx, 0, 1, 1, 1);

        label_les_dx = new QLabel(verticalLayoutWidget_2);
        label_les_dx->setObjectName(QString::fromUtf8("label_les_dx"));

        LES_area->addWidget(label_les_dx, 0, 0, 1, 1);


        Turbulence_area->addLayout(LES_area);

        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        Turbulence_area->addWidget(label_7);

        LES_area_2 = new QGridLayout();
        LES_area_2->setObjectName(QString::fromUtf8("LES_area_2"));
        gas_friction_label = new QLabel(verticalLayoutWidget_2);
        gas_friction_label->setObjectName(QString::fromUtf8("gas_friction_label"));

        LES_area_2->addWidget(gas_friction_label, 1, 0, 1, 1);

        gas_type_label = new QLabel(verticalLayoutWidget_2);
        gas_type_label->setObjectName(QString::fromUtf8("gas_type_label"));

        LES_area_2->addWidget(gas_type_label, 0, 0, 1, 1);

        gas_friction_lineEdit = new QLineEdit(verticalLayoutWidget_2);
        gas_friction_lineEdit->setObjectName(QString::fromUtf8("gas_friction_lineEdit"));

        LES_area_2->addWidget(gas_friction_lineEdit, 1, 1, 1, 1);

        gas_type_combo = new QComboBox(verticalLayoutWidget_2);
        gas_type_combo->addItem(QString());
        gas_type_combo->addItem(QString());
        gas_type_combo->setObjectName(QString::fromUtf8("gas_type_combo"));

        LES_area_2->addWidget(gas_type_combo, 0, 1, 1, 1);


        Turbulence_area->addLayout(LES_area_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));

        Turbulence_area->addLayout(horizontalLayout_4);

        DES_area_2 = new QHBoxLayout();
        DES_area_2->setObjectName(QString::fromUtf8("DES_area_2"));

        Turbulence_area->addLayout(DES_area_2);

        label_10 = new QLabel(verticalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        Turbulence_area->addWidget(label_10);

        LES_area_4 = new QGridLayout();
        LES_area_4->setObjectName(QString::fromUtf8("LES_area_4"));
        label_12 = new QLabel(verticalLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        LES_area_4->addWidget(label_12, 0, 2, 1, 1);

        lineEdit_factor_x = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_factor_x->setObjectName(QString::fromUtf8("lineEdit_factor_x"));

        LES_area_4->addWidget(lineEdit_factor_x, 1, 3, 1, 1);

        gas_friction_label_3 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_3->setObjectName(QString::fromUtf8("gas_friction_label_3"));

        LES_area_4->addWidget(gas_friction_label_3, 1, 0, 1, 1);

        lineEdit_factor_y = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_factor_y->setObjectName(QString::fromUtf8("lineEdit_factor_y"));

        LES_area_4->addWidget(lineEdit_factor_y, 2, 3, 1, 1);

        gas_friction_label_5 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_5->setObjectName(QString::fromUtf8("gas_friction_label_5"));

        LES_area_4->addWidget(gas_friction_label_5, 2, 0, 1, 1);

        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        LES_area_4->addWidget(label, 0, 0, 1, 1);

        lineEdit_axis_x = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_axis_x->setObjectName(QString::fromUtf8("lineEdit_axis_x"));

        LES_area_4->addWidget(lineEdit_axis_x, 1, 1, 1, 1);

        lineEdit_axis_y = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_axis_y->setObjectName(QString::fromUtf8("lineEdit_axis_y"));

        LES_area_4->addWidget(lineEdit_axis_y, 2, 1, 1, 1);

        gas_friction_label_6 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_6->setObjectName(QString::fromUtf8("gas_friction_label_6"));

        LES_area_4->addWidget(gas_friction_label_6, 2, 2, 1, 1);

        gas_friction_label_4 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_4->setObjectName(QString::fromUtf8("gas_friction_label_4"));

        LES_area_4->addWidget(gas_friction_label_4, 1, 2, 1, 1);

        gas_friction_label_7 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_7->setObjectName(QString::fromUtf8("gas_friction_label_7"));

        LES_area_4->addWidget(gas_friction_label_7, 3, 0, 1, 1);

        lineEdit_axis_z = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_axis_z->setObjectName(QString::fromUtf8("lineEdit_axis_z"));

        LES_area_4->addWidget(lineEdit_axis_z, 3, 1, 1, 1);

        gas_friction_label_8 = new QLabel(verticalLayoutWidget_2);
        gas_friction_label_8->setObjectName(QString::fromUtf8("gas_friction_label_8"));

        LES_area_4->addWidget(gas_friction_label_8, 3, 2, 1, 1);

        lineEdit_factor_z = new QLineEdit(verticalLayoutWidget_2);
        lineEdit_factor_z->setObjectName(QString::fromUtf8("lineEdit_factor_z"));

        LES_area_4->addWidget(lineEdit_factor_z, 3, 3, 1, 1);

        label_13 = new QLabel(verticalLayoutWidget_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        LES_area_4->addWidget(label_13, 0, 1, 1, 1);


        Turbulence_area->addLayout(LES_area_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        Turbulence_area->addItem(verticalSpacer_2);

        stackedWidget->addWidget(general);
        turbomachinery = new QWidget();
        turbomachinery->setObjectName(QString::fromUtf8("turbomachinery"));
        label_turbomachinery = new QLabel(turbomachinery);
        label_turbomachinery->setObjectName(QString::fromUtf8("label_turbomachinery"));
        label_turbomachinery->setGeometry(QRect(0, 0, 151, 31));
        label_3 = new QLabel(turbomachinery);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 40, 121, 16));
        label_4 = new QLabel(turbomachinery);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 280, 141, 16));
        turbo_zone_tree = new QTreeWidget(turbomachinery);
        turbo_zone_tree->setObjectName(QString::fromUtf8("turbo_zone_tree"));
        turbo_zone_tree->setGeometry(QRect(0, 70, 311, 192));
        turbo_zone_tree->header()->setDefaultSectionSize(70);
        turbo_interface_tree = new QTreeWidget(turbomachinery);
        turbo_interface_tree->setObjectName(QString::fromUtf8("turbo_interface_tree"));
        turbo_interface_tree->setGeometry(QRect(0, 310, 311, 192));
        turbo_interface_tree->header()->setDefaultSectionSize(100);
        passage_label = new QLabel(turbomachinery);
        passage_label->setObjectName(QString::fromUtf8("passage_label"));
        passage_label->setGeometry(QRect(20, 520, 141, 20));
        passage_repeat_tree = new QTreeWidget(turbomachinery);
        passage_repeat_tree->setObjectName(QString::fromUtf8("passage_repeat_tree"));
        passage_repeat_tree->setGeometry(QRect(0, 550, 311, 151));
        passage_repeat_tree->header()->setDefaultSectionSize(70);
        checkBox_passage_repeat = new QCheckBox(turbomachinery);
        checkBox_passage_repeat->setObjectName(QString::fromUtf8("checkBox_passage_repeat"));
        checkBox_passage_repeat->setGeometry(QRect(0, 520, 85, 20));
        interface_type_label = new QLabel(turbomachinery);
        interface_type_label->setObjectName(QString::fromUtf8("interface_type_label"));
        interface_type_label->setGeometry(QRect(180, 280, 141, 16));
        stackedWidget->addWidget(turbomachinery);
        solver = new QWidget();
        solver->setObjectName(QString::fromUtf8("solver"));
        gridLayoutWidget_2 = new QWidget(solver);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 60, 309, 334));
        GridLayoutFlow = new QGridLayout(gridLayoutWidget_2);
        GridLayoutFlow->setObjectName(QString::fromUtf8("GridLayoutFlow"));
        GridLayoutFlow->setContentsMargins(0, 0, 0, 0);
        gamma_label = new QLabel(gridLayoutWidget_2);
        gamma_label->setObjectName(QString::fromUtf8("gamma_label"));

        GridLayoutFlow->addWidget(gamma_label, 22, 0, 1, 1);

        p_lineEdit = new QLineEdit(gridLayoutWidget_2);
        p_lineEdit->setObjectName(QString::fromUtf8("p_lineEdit"));

        GridLayoutFlow->addWidget(p_lineEdit, 17, 1, 1, 1);

        k_unit_label = new QLabel(gridLayoutWidget_2);
        k_unit_label->setObjectName(QString::fromUtf8("k_unit_label"));

        GridLayoutFlow->addWidget(k_unit_label, 19, 2, 1, 1);

        v_label = new QLabel(gridLayoutWidget_2);
        v_label->setObjectName(QString::fromUtf8("v_label"));

        GridLayoutFlow->addWidget(v_label, 15, 0, 1, 1);

        sa_label = new QLabel(gridLayoutWidget_2);
        sa_label->setObjectName(QString::fromUtf8("sa_label"));

        GridLayoutFlow->addWidget(sa_label, 18, 0, 1, 1);

        v_lineEdit = new QLineEdit(gridLayoutWidget_2);
        v_lineEdit->setObjectName(QString::fromUtf8("v_lineEdit"));

        GridLayoutFlow->addWidget(v_lineEdit, 15, 1, 1, 1);

        label_unit_w = new QLabel(gridLayoutWidget_2);
        label_unit_w->setObjectName(QString::fromUtf8("label_unit_w"));

        GridLayoutFlow->addWidget(label_unit_w, 16, 2, 1, 1);

        omega_label = new QLabel(gridLayoutWidget_2);
        omega_label->setObjectName(QString::fromUtf8("omega_label"));

        GridLayoutFlow->addWidget(omega_label, 20, 0, 1, 1);

        pressure_unit_label = new QLabel(gridLayoutWidget_2);
        pressure_unit_label->setObjectName(QString::fromUtf8("pressure_unit_label"));

        GridLayoutFlow->addWidget(pressure_unit_label, 17, 2, 1, 1);

        label_unit_v = new QLabel(gridLayoutWidget_2);
        label_unit_v->setObjectName(QString::fromUtf8("label_unit_v"));

        GridLayoutFlow->addWidget(label_unit_v, 15, 2, 1, 1);

        epsilon_lineEdit = new QLineEdit(gridLayoutWidget_2);
        epsilon_lineEdit->setObjectName(QString::fromUtf8("epsilon_lineEdit"));

        GridLayoutFlow->addWidget(epsilon_lineEdit, 21, 1, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        GridLayoutFlow->addItem(verticalSpacer_4, 28, 0, 1, 1);

        gamma_lineEdit = new QLineEdit(gridLayoutWidget_2);
        gamma_lineEdit->setObjectName(QString::fromUtf8("gamma_lineEdit"));

        GridLayoutFlow->addWidget(gamma_lineEdit, 22, 1, 1, 1);

        k_lineEdit = new QLineEdit(gridLayoutWidget_2);
        k_lineEdit->setObjectName(QString::fromUtf8("k_lineEdit"));

        GridLayoutFlow->addWidget(k_lineEdit, 19, 1, 1, 1);

        rho_lineEdit = new QLineEdit(gridLayoutWidget_2);
        rho_lineEdit->setObjectName(QString::fromUtf8("rho_lineEdit"));

        GridLayoutFlow->addWidget(rho_lineEdit, 1, 1, 1, 1);

        omega_unit_label = new QLabel(gridLayoutWidget_2);
        omega_unit_label->setObjectName(QString::fromUtf8("omega_unit_label"));

        GridLayoutFlow->addWidget(omega_unit_label, 20, 2, 1, 1);

        label_unit_u = new QLabel(gridLayoutWidget_2);
        label_unit_u->setObjectName(QString::fromUtf8("label_unit_u"));

        GridLayoutFlow->addWidget(label_unit_u, 14, 2, 1, 1);

        rho_label = new QLabel(gridLayoutWidget_2);
        rho_label->setObjectName(QString::fromUtf8("rho_label"));

        GridLayoutFlow->addWidget(rho_label, 1, 0, 1, 1);

        epsilon_label = new QLabel(gridLayoutWidget_2);
        epsilon_label->setObjectName(QString::fromUtf8("epsilon_label"));

        GridLayoutFlow->addWidget(epsilon_label, 21, 0, 1, 1);

        sa_unit_label = new QLabel(gridLayoutWidget_2);
        sa_unit_label->setObjectName(QString::fromUtf8("sa_unit_label"));

        GridLayoutFlow->addWidget(sa_unit_label, 18, 2, 1, 1);

        label_unit_density = new QLabel(gridLayoutWidget_2);
        label_unit_density->setObjectName(QString::fromUtf8("label_unit_density"));

        GridLayoutFlow->addWidget(label_unit_density, 1, 2, 1, 1);

        u_label = new QLabel(gridLayoutWidget_2);
        u_label->setObjectName(QString::fromUtf8("u_label"));

        GridLayoutFlow->addWidget(u_label, 14, 0, 1, 1);

        k_label = new QLabel(gridLayoutWidget_2);
        k_label->setObjectName(QString::fromUtf8("k_label"));

        GridLayoutFlow->addWidget(k_label, 19, 0, 1, 1);

        p_label = new QLabel(gridLayoutWidget_2);
        p_label->setObjectName(QString::fromUtf8("p_label"));

        GridLayoutFlow->addWidget(p_label, 17, 0, 1, 1);

        u_lineEdit = new QLineEdit(gridLayoutWidget_2);
        u_lineEdit->setObjectName(QString::fromUtf8("u_lineEdit"));

        GridLayoutFlow->addWidget(u_lineEdit, 14, 1, 1, 1);

        w_labe = new QLabel(gridLayoutWidget_2);
        w_labe->setObjectName(QString::fromUtf8("w_labe"));

        GridLayoutFlow->addWidget(w_labe, 16, 0, 1, 1);

        omega_lineEdit = new QLineEdit(gridLayoutWidget_2);
        omega_lineEdit->setObjectName(QString::fromUtf8("omega_lineEdit"));

        GridLayoutFlow->addWidget(omega_lineEdit, 20, 1, 1, 1);

        epsilon_unit_label = new QLabel(gridLayoutWidget_2);
        epsilon_unit_label->setObjectName(QString::fromUtf8("epsilon_unit_label"));

        GridLayoutFlow->addWidget(epsilon_unit_label, 21, 2, 1, 1);

        w_lineEdit = new QLineEdit(gridLayoutWidget_2);
        w_lineEdit->setObjectName(QString::fromUtf8("w_lineEdit"));

        GridLayoutFlow->addWidget(w_lineEdit, 16, 1, 1, 1);

        sa_lineEdit = new QLineEdit(gridLayoutWidget_2);
        sa_lineEdit->setObjectName(QString::fromUtf8("sa_lineEdit"));

        GridLayoutFlow->addWidget(sa_lineEdit, 18, 1, 1, 1);

        gridLayoutWidget = new QWidget(solver);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 410, 311, 210));
        gridLayout_advanced = new QGridLayout(gridLayoutWidget);
        gridLayout_advanced->setObjectName(QString::fromUtf8("gridLayout_advanced"));
        gridLayout_advanced->setContentsMargins(0, 0, 0, 0);
        period_match_label = new QLabel(gridLayoutWidget);
        period_match_label->setObjectName(QString::fromUtf8("period_match_label"));

        gridLayout_advanced->addWidget(period_match_label, 1, 0, 1, 1);

        residual_unit = new QLabel(gridLayoutWidget);
        residual_unit->setObjectName(QString::fromUtf8("residual_unit"));

        gridLayout_advanced->addWidget(residual_unit, 2, 2, 1, 1);

        period_match_lineEdit = new QLineEdit(gridLayoutWidget);
        period_match_lineEdit->setObjectName(QString::fromUtf8("period_match_lineEdit"));

        gridLayout_advanced->addWidget(period_match_lineEdit, 1, 1, 1, 1);

        CFL_ramp_label = new QLabel(gridLayoutWidget);
        CFL_ramp_label->setObjectName(QString::fromUtf8("CFL_ramp_label"));

        gridLayout_advanced->addWidget(CFL_ramp_label, 3, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_advanced->addWidget(label_5, 0, 0, 1, 1);

        MG_level_label = new QLabel(gridLayoutWidget);
        MG_level_label->setObjectName(QString::fromUtf8("MG_level_label"));

        gridLayout_advanced->addWidget(MG_level_label, 4, 0, 1, 1);

        run_pre_process = new QPushButton(gridLayoutWidget);
        run_pre_process->setObjectName(QString::fromUtf8("run_pre_process"));

        gridLayout_advanced->addWidget(run_pre_process, 6, 1, 1, 1);

        saveYAMLButton = new QPushButton(gridLayoutWidget);
        saveYAMLButton->setObjectName(QString::fromUtf8("saveYAMLButton"));

        gridLayout_advanced->addWidget(saveYAMLButton, 6, 0, 1, 1);

        mg_level_spinBox = new QSpinBox(gridLayoutWidget);
        mg_level_spinBox->setObjectName(QString::fromUtf8("mg_level_spinBox"));
        mg_level_spinBox->setMinimum(1);
        mg_level_spinBox->setMaximum(10);

        gridLayout_advanced->addWidget(mg_level_spinBox, 4, 1, 1, 1);

        CFL_ramp_lineEdit = new QLineEdit(gridLayoutWidget);
        CFL_ramp_lineEdit->setObjectName(QString::fromUtf8("CFL_ramp_lineEdit"));

        gridLayout_advanced->addWidget(CFL_ramp_lineEdit, 3, 1, 1, 1);

        residual_lineEdit = new QLineEdit(gridLayoutWidget);
        residual_lineEdit->setObjectName(QString::fromUtf8("residual_lineEdit"));

        gridLayout_advanced->addWidget(residual_lineEdit, 2, 1, 1, 1);

        CFL_ramp_label_2 = new QLabel(gridLayoutWidget);
        CFL_ramp_label_2->setObjectName(QString::fromUtf8("CFL_ramp_label_2"));

        gridLayout_advanced->addWidget(CFL_ramp_label_2, 2, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_advanced->addItem(verticalSpacer_5, 7, 1, 1, 1);

        skip_pre_checkBox = new QCheckBox(gridLayoutWidget);
        skip_pre_checkBox->setObjectName(QString::fromUtf8("skip_pre_checkBox"));

        gridLayout_advanced->addWidget(skip_pre_checkBox, 5, 0, 1, 1);

        label_monitor = new QLabel(solver);
        label_monitor->setObjectName(QString::fromUtf8("label_monitor"));
        label_monitor->setGeometry(QRect(0, 0, 108, 53));
        load_steady_flow = new QPushButton(solver);
        load_steady_flow->setObjectName(QString::fromUtf8("load_steady_flow"));
        load_steady_flow->setGeometry(QRect(150, 10, 131, 32));
        stackedWidget->addWidget(solver);
        boundary_conditions = new QWidget();
        boundary_conditions->setObjectName(QString::fromUtf8("boundary_conditions"));
        label_bc = new QLabel(boundary_conditions);
        label_bc->setObjectName(QString::fromUtf8("label_bc"));
        label_bc->setGeometry(QRect(10, 10, 121, 16));
        Zone_list = new QListWidget(boundary_conditions);
        Zone_list->setObjectName(QString::fromUtf8("Zone_list"));
        Zone_list->setGeometry(QRect(10, 50, 291, 161));
        BC_list = new QListWidget(boundary_conditions);
        BC_list->setObjectName(QString::fromUtf8("BC_list"));
        BC_list->setGeometry(QRect(10, 270, 291, 401));
        label_bc_2 = new QLabel(boundary_conditions);
        label_bc_2->setObjectName(QString::fromUtf8("label_bc_2"));
        label_bc_2->setGeometry(QRect(20, 240, 211, 16));
        stackedWidget->addWidget(boundary_conditions);
        filmCool = new QWidget();
        filmCool->setObjectName(QString::fromUtf8("filmCool"));
        label_2 = new QLabel(filmCool);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 0, 141, 41));
        Zone_list_2 = new QListWidget(filmCool);
        Zone_list_2->setObjectName(QString::fromUtf8("Zone_list_2"));
        Zone_list_2->setGeometry(QRect(20, 70, 291, 91));
        label_8 = new QLabel(filmCool);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 30, 141, 41));
        label_11 = new QLabel(filmCool);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 160, 161, 41));
        FilmCooling_List = new QListWidget(filmCool);
        FilmCooling_List->setObjectName(QString::fromUtf8("FilmCooling_List"));
        FilmCooling_List->setGeometry(QRect(20, 200, 291, 381));
        generate_film_boundary = new QPushButton(filmCool);
        generate_film_boundary->setObjectName(QString::fromUtf8("generate_film_boundary"));
        generate_film_boundary->setGeometry(QRect(20, 590, 291, 32));
        stackedWidget->addWidget(filmCool);
        savetab = new QWidget();
        savetab->setObjectName(QString::fromUtf8("savetab"));
        verticalLayout_7 = new QVBoxLayout(savetab);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        unstead_simulation_layout_2 = new QGridLayout();
        unstead_simulation_layout_2->setObjectName(QString::fromUtf8("unstead_simulation_layout_2"));

        verticalLayout_7->addLayout(unstead_simulation_layout_2);

        label_6 = new QLabel(savetab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_7->addWidget(label_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(savetab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_5->addWidget(label_9);

        spinCPU = new QSpinBox(savetab);
        spinCPU->setObjectName(QString::fromUtf8("spinCPU"));
        spinCPU->setMaximum(9999);

        horizontalLayout_5->addWidget(spinCPU);


        verticalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));

        verticalLayout_7->addLayout(horizontalLayout_6);

        unstead_simulation_layout_3 = new QGridLayout();
        unstead_simulation_layout_3->setObjectName(QString::fromUtf8("unstead_simulation_layout_3"));
        start_simulation_button = new QPushButton(savetab);
        start_simulation_button->setObjectName(QString::fromUtf8("start_simulation_button"));

        unstead_simulation_layout_3->addWidget(start_simulation_button, 2, 0, 1, 1);

        continue_simulation_button = new QPushButton(savetab);
        continue_simulation_button->setObjectName(QString::fromUtf8("continue_simulation_button"));

        unstead_simulation_layout_3->addWidget(continue_simulation_button, 2, 1, 1, 1);

        stop_simulation_button = new QPushButton(savetab);
        stop_simulation_button->setObjectName(QString::fromUtf8("stop_simulation_button"));

        unstead_simulation_layout_3->addWidget(stop_simulation_button, 2, 2, 1, 1);


        verticalLayout_7->addLayout(unstead_simulation_layout_3);

        checkBox_performance = new QCheckBox(savetab);
        checkBox_performance->setObjectName(QString::fromUtf8("checkBox_performance"));

        verticalLayout_7->addWidget(checkBox_performance);

        curve_grid_layout = new QGridLayout();
        curve_grid_layout->setObjectName(QString::fromUtf8("curve_grid_layout"));
        current_p_label = new QLabel(savetab);
        current_p_label->setObjectName(QString::fromUtf8("current_p_label"));

        curve_grid_layout->addWidget(current_p_label, 1, 0, 1, 1);

        target_p_value = new QLineEdit(savetab);
        target_p_value->setObjectName(QString::fromUtf8("target_p_value"));

        curve_grid_layout->addWidget(target_p_value, 2, 1, 1, 1);

        current_p_value = new QLabel(savetab);
        current_p_value->setObjectName(QString::fromUtf8("current_p_value"));

        curve_grid_layout->addWidget(current_p_value, 1, 1, 1, 1);

        target_p_label = new QLabel(savetab);
        target_p_label->setObjectName(QString::fromUtf8("target_p_label"));

        curve_grid_layout->addWidget(target_p_label, 2, 0, 1, 1);

        save_p_button = new QPushButton(savetab);
        save_p_button->setObjectName(QString::fromUtf8("save_p_button"));

        curve_grid_layout->addWidget(save_p_button, 3, 0, 1, 1);

        load_p_button = new QPushButton(savetab);
        load_p_button->setObjectName(QString::fromUtf8("load_p_button"));

        curve_grid_layout->addWidget(load_p_button, 3, 1, 1, 1);


        verticalLayout_7->addLayout(curve_grid_layout);

        unsteady_simulation_label = new QLabel(savetab);
        unsteady_simulation_label->setObjectName(QString::fromUtf8("unsteady_simulation_label"));

        verticalLayout_7->addWidget(unsteady_simulation_label);

        unstead_simulation_layout = new QGridLayout();
        unstead_simulation_layout->setObjectName(QString::fromUtf8("unstead_simulation_layout"));
        step_per_cycle_lineEdit = new QLineEdit(savetab);
        step_per_cycle_lineEdit->setObjectName(QString::fromUtf8("step_per_cycle_lineEdit"));

        unstead_simulation_layout->addWidget(step_per_cycle_lineEdit, 4, 1, 1, 1);

        period_lineEdit = new QLineEdit(savetab);
        period_lineEdit->setObjectName(QString::fromUtf8("period_lineEdit"));

        unstead_simulation_layout->addWidget(period_lineEdit, 2, 1, 1, 1);

        output_unsteady_label = new QLabel(savetab);
        output_unsteady_label->setObjectName(QString::fromUtf8("output_unsteady_label"));

        unstead_simulation_layout->addWidget(output_unsteady_label, 5, 0, 1, 1);

        output_unsteady_lineEdit = new QLineEdit(savetab);
        output_unsteady_lineEdit->setObjectName(QString::fromUtf8("output_unsteady_lineEdit"));

        unstead_simulation_layout->addWidget(output_unsteady_lineEdit, 5, 1, 1, 1);

        period_label = new QLabel(savetab);
        period_label->setObjectName(QString::fromUtf8("period_label"));

        unstead_simulation_layout->addWidget(period_label, 2, 0, 1, 1);

        label_les_dt = new QLabel(savetab);
        label_les_dt->setObjectName(QString::fromUtf8("label_les_dt"));

        unstead_simulation_layout->addWidget(label_les_dt, 6, 0, 1, 1);

        n_cycle_lineEdit = new QLineEdit(savetab);
        n_cycle_lineEdit->setObjectName(QString::fromUtf8("n_cycle_lineEdit"));

        unstead_simulation_layout->addWidget(n_cycle_lineEdit, 3, 1, 1, 1);

        step_per_cycle_label = new QLabel(savetab);
        step_per_cycle_label->setObjectName(QString::fromUtf8("step_per_cycle_label"));

        unstead_simulation_layout->addWidget(step_per_cycle_label, 4, 0, 1, 1);

        lineEdit_les_dt = new QLineEdit(savetab);
        lineEdit_les_dt->setObjectName(QString::fromUtf8("lineEdit_les_dt"));

        unstead_simulation_layout->addWidget(lineEdit_les_dt, 6, 1, 1, 1);

        n_cycle_label = new QLabel(savetab);
        n_cycle_label->setObjectName(QString::fromUtf8("n_cycle_label"));

        unstead_simulation_layout->addWidget(n_cycle_label, 3, 0, 1, 1);

        period_unit_label = new QLabel(savetab);
        period_unit_label->setObjectName(QString::fromUtf8("period_unit_label"));

        unstead_simulation_layout->addWidget(period_unit_label, 2, 2, 1, 1);


        verticalLayout_7->addLayout(unstead_simulation_layout);

        steady_iteration_label = new QLabel(savetab);
        steady_iteration_label->setObjectName(QString::fromUtf8("steady_iteration_label"));

        verticalLayout_7->addWidget(steady_iteration_label);

        unsteady_inner_label = new QLabel(savetab);
        unsteady_inner_label->setObjectName(QString::fromUtf8("unsteady_inner_label"));

        verticalLayout_7->addWidget(unsteady_inner_label);

        steady_simulation_layout = new QGridLayout();
        steady_simulation_layout->setObjectName(QString::fromUtf8("steady_simulation_layout"));
        CFL_lineEdit = new QLineEdit(savetab);
        CFL_lineEdit->setObjectName(QString::fromUtf8("CFL_lineEdit"));

        steady_simulation_layout->addWidget(CFL_lineEdit, 3, 1, 1, 1);

        iteration_step_lineEdit = new QLineEdit(savetab);
        iteration_step_lineEdit->setObjectName(QString::fromUtf8("iteration_step_lineEdit"));

        steady_simulation_layout->addWidget(iteration_step_lineEdit, 2, 1, 1, 1);

        iteration_step_label = new QLabel(savetab);
        iteration_step_label->setObjectName(QString::fromUtf8("iteration_step_label"));

        steady_simulation_layout->addWidget(iteration_step_label, 2, 0, 1, 1);

        CFL_label = new QLabel(savetab);
        CFL_label->setObjectName(QString::fromUtf8("CFL_label"));

        steady_simulation_layout->addWidget(CFL_label, 3, 0, 1, 1);

        output_steady_lineEdit = new QLineEdit(savetab);
        output_steady_lineEdit->setObjectName(QString::fromUtf8("output_steady_lineEdit"));

        steady_simulation_layout->addWidget(output_steady_lineEdit, 4, 1, 1, 1);

        output_steady_label = new QLabel(savetab);
        output_steady_label->setObjectName(QString::fromUtf8("output_steady_label"));

        steady_simulation_layout->addWidget(output_steady_label, 4, 0, 1, 1);


        verticalLayout_7->addLayout(steady_simulation_layout);

        steady_simulation_layout_2 = new QGridLayout();
        steady_simulation_layout_2->setObjectName(QString::fromUtf8("steady_simulation_layout_2"));
        monitor_label = new QLabel(savetab);
        monitor_label->setObjectName(QString::fromUtf8("monitor_label"));

        steady_simulation_layout_2->addWidget(monitor_label, 2, 0, 1, 1);

        pushButton = new QPushButton(savetab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        steady_simulation_layout_2->addWidget(pushButton, 2, 1, 1, 1);


        verticalLayout_7->addLayout(steady_simulation_layout_2);

        monitor_tree = new QTreeWidget(savetab);
        monitor_tree->setObjectName(QString::fromUtf8("monitor_tree"));

        verticalLayout_7->addWidget(monitor_tree);

        widget_13 = new QWidget(savetab);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        gridLayout = new QGridLayout(widget_13);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_44 = new QLabel(widget_13);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        QFont font2;
        font2.setFamily(QString::fromUtf8(".AppleSystemUIFont"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        label_44->setFont(font2);

        gridLayout->addWidget(label_44, 0, 0, 1, 1);

        label_14 = new QLabel(widget_13);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout->addWidget(label_14, 1, 0, 1, 1);

        LEdit_EndPressure_AutoRun = new QLineEdit(widget_13);
        LEdit_EndPressure_AutoRun->setObjectName(QString::fromUtf8("LEdit_EndPressure_AutoRun"));

        gridLayout->addWidget(LEdit_EndPressure_AutoRun, 2, 2, 1, 2);

        Btn_Skip_AutoRun = new QPushButton(widget_13);
        Btn_Skip_AutoRun->setObjectName(QString::fromUtf8("Btn_Skip_AutoRun"));

        gridLayout->addWidget(Btn_Skip_AutoRun, 4, 1, 1, 2);

        Btn_End_AutoRun = new QPushButton(widget_13);
        Btn_End_AutoRun->setObjectName(QString::fromUtf8("Btn_End_AutoRun"));

        gridLayout->addWidget(Btn_End_AutoRun, 4, 3, 1, 1);

        LEdit_StartPressure_AutoRun = new QLineEdit(widget_13);
        LEdit_StartPressure_AutoRun->setObjectName(QString::fromUtf8("LEdit_StartPressure_AutoRun"));

        gridLayout->addWidget(LEdit_StartPressure_AutoRun, 1, 2, 1, 2);

        label_15 = new QLabel(widget_13);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout->addWidget(label_15, 2, 0, 1, 1);

        label_43 = new QLabel(widget_13);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout->addWidget(label_43, 3, 0, 1, 2);

        LEdit_NumPoints_AutoRun = new QLineEdit(widget_13);
        LEdit_NumPoints_AutoRun->setObjectName(QString::fromUtf8("LEdit_NumPoints_AutoRun"));

        gridLayout->addWidget(LEdit_NumPoints_AutoRun, 3, 2, 1, 2);

        Btn_Start_AutoRun = new QPushButton(widget_13);
        Btn_Start_AutoRun->setObjectName(QString::fromUtf8("Btn_Start_AutoRun"));

        gridLayout->addWidget(Btn_Start_AutoRun, 4, 0, 1, 1);


        verticalLayout_7->addWidget(widget_13);

        verticalSpacer_7 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_7);

        stackedWidget->addWidget(savetab);

        verticalLayout_3->addWidget(stackedWidget);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_3->addWidget(scrollArea);

        Show_MainWindow = new QTabWidget(widget_2);
        Show_MainWindow->setObjectName(QString::fromUtf8("Show_MainWindow"));
        Show_Model = new QWidget();
        Show_Model->setObjectName(QString::fromUtf8("Show_Model"));
        RunGraphLayout = new QVBoxLayout(Show_Model);
        RunGraphLayout->setObjectName(QString::fromUtf8("RunGraphLayout"));
        vtkPlaceHolder = new QWidget(Show_Model);
        vtkPlaceHolder->setObjectName(QString::fromUtf8("vtkPlaceHolder"));
        vtkPlaceHolder->setMinimumSize(QSize(0, 0));

        RunGraphLayout->addWidget(vtkPlaceHolder);

        runOutputWindow = new QTextEdit(Show_Model);
        runOutputWindow->setObjectName(QString::fromUtf8("runOutputWindow"));
        runOutputWindow->setMaximumSize(QSize(16777215, 750));

        RunGraphLayout->addWidget(runOutputWindow);

        Show_MainWindow->addTab(Show_Model, QString());
        Show_Convergence = new QWidget();
        Show_Convergence->setObjectName(QString::fromUtf8("Show_Convergence"));
        horizontalLayout_14 = new QHBoxLayout(Show_Convergence);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(9, 9, 9, 9);
        Panel_Conver = new QWidget(Show_Convergence);
        Panel_Conver->setObjectName(QString::fromUtf8("Panel_Conver"));
        Panel_Conver->setMinimumSize(QSize(300, 0));
        Panel_Conver->setMaximumSize(QSize(300, 16777215));
        verticalLayout_11 = new QVBoxLayout(Panel_Conver);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        label_27 = new QLabel(Panel_Conver);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setMaximumSize(QSize(16777215, 20));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(75);
        font3.setStrikeOut(false);
        label_27->setFont(font3);

        verticalLayout_11->addWidget(label_27);

        widget_9 = new QWidget(Panel_Conver);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_9->sizePolicy().hasHeightForWidth());
        widget_9->setSizePolicy(sizePolicy2);
        horizontalLayout_17 = new QHBoxLayout(widget_9);
        horizontalLayout_17->setSpacing(15);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        Btn_AutoScale_Res = new QPushButton(widget_9);
        Btn_AutoScale_Res->setObjectName(QString::fromUtf8("Btn_AutoScale_Res"));

        horizontalLayout_17->addWidget(Btn_AutoScale_Res);

        Btn_ManualScale_Res = new QPushButton(widget_9);
        Btn_ManualScale_Res->setObjectName(QString::fromUtf8("Btn_ManualScale_Res"));

        horizontalLayout_17->addWidget(Btn_ManualScale_Res);


        verticalLayout_11->addWidget(widget_9);

        control_panel_Range_Res = new QWidget(Panel_Conver);
        control_panel_Range_Res->setObjectName(QString::fromUtf8("control_panel_Range_Res"));
        sizePolicy2.setHeightForWidth(control_panel_Range_Res->sizePolicy().hasHeightForWidth());
        control_panel_Range_Res->setSizePolicy(sizePolicy2);
        control_panel_Range_Res->setMinimumSize(QSize(0, 350));
        verticalLayout_13 = new QVBoxLayout(control_panel_Range_Res);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        label_29 = new QLabel(control_panel_Range_Res);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMaximumSize(QSize(16777215, 20));

        verticalLayout_13->addWidget(label_29);

        Widget_Res_RangeX = new QWidget(control_panel_Range_Res);
        Widget_Res_RangeX->setObjectName(QString::fromUtf8("Widget_Res_RangeX"));
        horizontalLayout_16 = new QHBoxLayout(Widget_Res_RangeX);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(-1, 0, -1, 0);
        label_25 = new QLabel(Widget_Res_RangeX);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_16->addWidget(label_25);

        Line_RangeX_Res_Min = new QLineEdit(Widget_Res_RangeX);
        Line_RangeX_Res_Min->setObjectName(QString::fromUtf8("Line_RangeX_Res_Min"));

        horizontalLayout_16->addWidget(Line_RangeX_Res_Min);

        label_26 = new QLabel(Widget_Res_RangeX);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_16->addWidget(label_26);

        Line_RangeX_Res_Max = new QLineEdit(Widget_Res_RangeX);
        Line_RangeX_Res_Max->setObjectName(QString::fromUtf8("Line_RangeX_Res_Max"));

        horizontalLayout_16->addWidget(Line_RangeX_Res_Max);


        verticalLayout_13->addWidget(Widget_Res_RangeX);

        label_28 = new QLabel(control_panel_Range_Res);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setMaximumSize(QSize(16777215, 20));

        verticalLayout_13->addWidget(label_28);

        Widget_Res_RangeY1 = new QWidget(control_panel_Range_Res);
        Widget_Res_RangeY1->setObjectName(QString::fromUtf8("Widget_Res_RangeY1"));
        horizontalLayout_15 = new QHBoxLayout(Widget_Res_RangeY1);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(-1, 0, -1, 0);
        label_23 = new QLabel(Widget_Res_RangeY1);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_15->addWidget(label_23);

        Line_RangeY1_Res_Min = new QLineEdit(Widget_Res_RangeY1);
        Line_RangeY1_Res_Min->setObjectName(QString::fromUtf8("Line_RangeY1_Res_Min"));

        horizontalLayout_15->addWidget(Line_RangeY1_Res_Min);

        label_24 = new QLabel(Widget_Res_RangeY1);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_15->addWidget(label_24);

        Line_RangeY1_Res_Max = new QLineEdit(Widget_Res_RangeY1);
        Line_RangeY1_Res_Max->setObjectName(QString::fromUtf8("Line_RangeY1_Res_Max"));

        horizontalLayout_15->addWidget(Line_RangeY1_Res_Max);


        verticalLayout_13->addWidget(Widget_Res_RangeY1);

        label_33 = new QLabel(control_panel_Range_Res);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMaximumSize(QSize(16777215, 20));

        verticalLayout_13->addWidget(label_33);

        Widget_Res_RangeY1_2 = new QWidget(control_panel_Range_Res);
        Widget_Res_RangeY1_2->setObjectName(QString::fromUtf8("Widget_Res_RangeY1_2"));
        horizontalLayout_18 = new QHBoxLayout(Widget_Res_RangeY1_2);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(-1, 0, -1, 0);
        label_31 = new QLabel(Widget_Res_RangeY1_2);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        horizontalLayout_18->addWidget(label_31);

        Line_RangeY2_Res_Min = new QLineEdit(Widget_Res_RangeY1_2);
        Line_RangeY2_Res_Min->setObjectName(QString::fromUtf8("Line_RangeY2_Res_Min"));

        horizontalLayout_18->addWidget(Line_RangeY2_Res_Min);

        label_32 = new QLabel(Widget_Res_RangeY1_2);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        horizontalLayout_18->addWidget(label_32);

        Line_RangeY2_Res_Max = new QLineEdit(Widget_Res_RangeY1_2);
        Line_RangeY2_Res_Max->setObjectName(QString::fromUtf8("Line_RangeY2_Res_Max"));

        horizontalLayout_18->addWidget(Line_RangeY2_Res_Max);


        verticalLayout_13->addWidget(Widget_Res_RangeY1_2);


        verticalLayout_11->addWidget(control_panel_Range_Res);

        widget_14 = new QWidget(Panel_Conver);
        widget_14->setObjectName(QString::fromUtf8("widget_14"));
        widget_14->setMaximumSize(QSize(16777215, 80));
        verticalLayout_8 = new QVBoxLayout(widget_14);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_45 = new QLabel(widget_14);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setMaximumSize(QSize(16777215, 20));

        verticalLayout_8->addWidget(label_45);

        Widget_History = new QWidget(widget_14);
        Widget_History->setObjectName(QString::fromUtf8("Widget_History"));
        Widget_History->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_7 = new QHBoxLayout(Widget_History);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        CBtn_History = new QComboBox(Widget_History);
        CBtn_History->setObjectName(QString::fromUtf8("CBtn_History"));

        horizontalLayout_7->addWidget(CBtn_History);

        Btn_ClearHistory = new QPushButton(Widget_History);
        Btn_ClearHistory->setObjectName(QString::fromUtf8("Btn_ClearHistory"));

        horizontalLayout_7->addWidget(Btn_ClearHistory);


        verticalLayout_8->addWidget(Widget_History);


        verticalLayout_11->addWidget(widget_14);

        panel_Theme = new QWidget(Panel_Conver);
        panel_Theme->setObjectName(QString::fromUtf8("panel_Theme"));
        panel_Theme->setMinimumSize(QSize(40, 0));
        panel_Theme->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_19 = new QHBoxLayout(panel_Theme);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(-1, -1, 0, -1);
        label_34 = new QLabel(panel_Theme);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_19->addWidget(label_34);

        CBox_Theme = new QComboBox(panel_Theme);
        CBox_Theme->setObjectName(QString::fromUtf8("CBox_Theme"));
        CBox_Theme->setMinimumSize(QSize(40, 0));

        horizontalLayout_19->addWidget(CBox_Theme);

        Btn_SyncWindowTheme = new QPushButton(panel_Theme);
        Btn_SyncWindowTheme->setObjectName(QString::fromUtf8("Btn_SyncWindowTheme"));
        Btn_SyncWindowTheme->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_19->addWidget(Btn_SyncWindowTheme);


        verticalLayout_11->addWidget(panel_Theme);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_6);


        horizontalLayout_14->addWidget(Panel_Conver);

        Plot_Convergence = new QWidget(Show_Convergence);
        Plot_Convergence->setObjectName(QString::fromUtf8("Plot_Convergence"));
        LayoutforConverPlot = new QVBoxLayout(Plot_Convergence);
        LayoutforConverPlot->setSpacing(0);
        LayoutforConverPlot->setObjectName(QString::fromUtf8("LayoutforConverPlot"));
        LayoutforConverPlot->setSizeConstraint(QLayout::SetMaximumSize);
        LayoutforConverPlot->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_14->addWidget(Plot_Convergence);

        Show_MainWindow->addTab(Show_Convergence, QString());
        Show_Monitor = new QWidget();
        Show_Monitor->setObjectName(QString::fromUtf8("Show_Monitor"));
        horizontalLayout_9 = new QHBoxLayout(Show_Monitor);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        Panel_Monitor = new QWidget(Show_Monitor);
        Panel_Monitor->setObjectName(QString::fromUtf8("Panel_Monitor"));
        Panel_Monitor->setMinimumSize(QSize(300, 0));
        Panel_Monitor->setMaximumSize(QSize(300, 16777215));
        verticalLayout_10 = new QVBoxLayout(Panel_Monitor);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        label_22 = new QLabel(Panel_Monitor);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setMaximumSize(QSize(16777215, 20));
        label_22->setFont(font3);

        verticalLayout_10->addWidget(label_22);

        Btn_SelectMonitor = new QPushButton(Panel_Monitor);
        Btn_SelectMonitor->setObjectName(QString::fromUtf8("Btn_SelectMonitor"));
        Btn_SelectMonitor->setMaximumSize(QSize(11111111, 16777215));

        verticalLayout_10->addWidget(Btn_SelectMonitor);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_10->addItem(verticalSpacer_3);

        label_30 = new QLabel(Panel_Monitor);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setMaximumSize(QSize(16777215, 20));

        verticalLayout_10->addWidget(label_30);

        List_Variable = new QListWidget(Panel_Monitor);
        List_Variable->setObjectName(QString::fromUtf8("List_Variable"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(List_Variable->sizePolicy().hasHeightForWidth());
        List_Variable->setSizePolicy(sizePolicy3);
        List_Variable->setMinimumSize(QSize(0, 435));
        List_Variable->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_10->addWidget(List_Variable);

        widget_5 = new QWidget(Panel_Monitor);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        horizontalLayout_12 = new QHBoxLayout(widget_5);
        horizontalLayout_12->setSpacing(15);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        Btn_AutoScale_Mon = new QPushButton(widget_5);
        Btn_AutoScale_Mon->setObjectName(QString::fromUtf8("Btn_AutoScale_Mon"));

        horizontalLayout_12->addWidget(Btn_AutoScale_Mon);

        Btn_ManualScale_Mon = new QPushButton(widget_5);
        Btn_ManualScale_Mon->setObjectName(QString::fromUtf8("Btn_ManualScale_Mon"));

        horizontalLayout_12->addWidget(Btn_ManualScale_Mon);


        verticalLayout_10->addWidget(widget_5);

        control_panel_Range_Mon = new QWidget(Panel_Monitor);
        control_panel_Range_Mon->setObjectName(QString::fromUtf8("control_panel_Range_Mon"));
        verticalLayout_4 = new QVBoxLayout(control_panel_Range_Mon);
        verticalLayout_4->setSpacing(20);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_16 = new QLabel(control_panel_Range_Mon);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(label_16);

        widget = new QWidget(control_panel_Range_Mon);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_10 = new QHBoxLayout(widget);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, 0, -1, 0);
        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_10->addWidget(label_18);

        Line_RangeX_Mon_Min = new QLineEdit(widget);
        Line_RangeX_Mon_Min->setObjectName(QString::fromUtf8("Line_RangeX_Mon_Min"));

        horizontalLayout_10->addWidget(Line_RangeX_Mon_Min);

        label_19 = new QLabel(widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_10->addWidget(label_19);

        Line_RangeX_Mon_Max = new QLineEdit(widget);
        Line_RangeX_Mon_Max->setObjectName(QString::fromUtf8("Line_RangeX_Mon_Max"));

        horizontalLayout_10->addWidget(Line_RangeX_Mon_Max);


        verticalLayout_4->addWidget(widget);

        label_17 = new QLabel(control_panel_Range_Mon);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(label_17);

        widget_6 = new QWidget(control_panel_Range_Mon);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        horizontalLayout_13 = new QHBoxLayout(widget_6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(-1, 0, -1, 0);
        label_20 = new QLabel(widget_6);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        horizontalLayout_13->addWidget(label_20);

        Line_RangeY_Mon_Min = new QLineEdit(widget_6);
        Line_RangeY_Mon_Min->setObjectName(QString::fromUtf8("Line_RangeY_Mon_Min"));

        horizontalLayout_13->addWidget(Line_RangeY_Mon_Min);

        label_21 = new QLabel(widget_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        horizontalLayout_13->addWidget(label_21);

        Line_RangeY_Mon_Max = new QLineEdit(widget_6);
        Line_RangeY_Mon_Max->setObjectName(QString::fromUtf8("Line_RangeY_Mon_Max"));

        horizontalLayout_13->addWidget(Line_RangeY_Mon_Max);


        verticalLayout_4->addWidget(widget_6);


        verticalLayout_10->addWidget(control_panel_Range_Mon);

        widget_3 = new QWidget(Panel_Monitor);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_11 = new QHBoxLayout(widget_3);
        horizontalLayout_11->setSpacing(50);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);

        verticalLayout_10->addWidget(widget_3);


        horizontalLayout_9->addWidget(Panel_Monitor);

        Monitor = new QWidget(Show_Monitor);
        Monitor->setObjectName(QString::fromUtf8("Monitor"));
        Lay_MonitorPlot = new QHBoxLayout(Monitor);
        Lay_MonitorPlot->setObjectName(QString::fromUtf8("Lay_MonitorPlot"));

        horizontalLayout_9->addWidget(Monitor);

        Show_MainWindow->addTab(Show_Monitor, QString());
        Show_Performance = new QWidget();
        Show_Performance->setObjectName(QString::fromUtf8("Show_Performance"));
        horizontalLayout_24 = new QHBoxLayout(Show_Performance);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        Panel_Monitor_2 = new QWidget(Show_Performance);
        Panel_Monitor_2->setObjectName(QString::fromUtf8("Panel_Monitor_2"));
        Panel_Monitor_2->setMinimumSize(QSize(300, 0));
        Panel_Monitor_2->setMaximumSize(QSize(300, 16777215));
        verticalLayout_12 = new QVBoxLayout(Panel_Monitor_2);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        label_35 = new QLabel(Panel_Monitor_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setMaximumSize(QSize(16777215, 20));
        label_35->setFont(font3);

        verticalLayout_12->addWidget(label_35);

        widget_12 = new QWidget(Panel_Monitor_2);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        widget_12->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_25 = new QHBoxLayout(widget_12);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        horizontalLayout_25->setContentsMargins(-1, -1, 20, -1);
        label_36 = new QLabel(widget_12);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        horizontalLayout_25->addWidget(label_36, 0, Qt::AlignLeft);

        CBtn_SelectPerfVariable = new QComboBox(widget_12);
        CBtn_SelectPerfVariable->setObjectName(QString::fromUtf8("CBtn_SelectPerfVariable"));

        horizontalLayout_25->addWidget(CBtn_SelectPerfVariable);


        verticalLayout_12->addWidget(widget_12);

        control_panel_Range_Mon_2 = new QWidget(Panel_Monitor_2);
        control_panel_Range_Mon_2->setObjectName(QString::fromUtf8("control_panel_Range_Mon_2"));
        verticalLayout_6 = new QVBoxLayout(control_panel_Range_Mon_2);
        verticalLayout_6->setSpacing(20);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_37 = new QLabel(control_panel_Range_Mon_2);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(label_37);

        widget_8 = new QWidget(control_panel_Range_Mon_2);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        horizontalLayout_21 = new QHBoxLayout(widget_8);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_21->setContentsMargins(-1, 0, -1, 0);
        label_38 = new QLabel(widget_8);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        horizontalLayout_21->addWidget(label_38);

        Line_RangeX_Perf_Min = new QLineEdit(widget_8);
        Line_RangeX_Perf_Min->setObjectName(QString::fromUtf8("Line_RangeX_Perf_Min"));

        horizontalLayout_21->addWidget(Line_RangeX_Perf_Min);

        label_39 = new QLabel(widget_8);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        horizontalLayout_21->addWidget(label_39);

        Line_RangeX_Perf_Max = new QLineEdit(widget_8);
        Line_RangeX_Perf_Max->setObjectName(QString::fromUtf8("Line_RangeX_Perf_Max"));

        horizontalLayout_21->addWidget(Line_RangeX_Perf_Max);


        verticalLayout_6->addWidget(widget_8);

        label_40 = new QLabel(control_panel_Range_Mon_2);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setMaximumSize(QSize(16777215, 20));

        verticalLayout_6->addWidget(label_40);

        widget_10 = new QWidget(control_panel_Range_Mon_2);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        horizontalLayout_22 = new QHBoxLayout(widget_10);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalLayout_22->setContentsMargins(-1, 0, -1, 0);
        label_41 = new QLabel(widget_10);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        horizontalLayout_22->addWidget(label_41);

        Line_RangeY_Perf_Min = new QLineEdit(widget_10);
        Line_RangeY_Perf_Min->setObjectName(QString::fromUtf8("Line_RangeY_Perf_Min"));

        horizontalLayout_22->addWidget(Line_RangeY_Perf_Min);

        label_42 = new QLabel(widget_10);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        horizontalLayout_22->addWidget(label_42);

        Line_RangeY_Perf_Max = new QLineEdit(widget_10);
        Line_RangeY_Perf_Max->setObjectName(QString::fromUtf8("Line_RangeY_Perf_Max"));

        horizontalLayout_22->addWidget(Line_RangeY_Perf_Max);


        verticalLayout_6->addWidget(widget_10);


        verticalLayout_12->addWidget(control_panel_Range_Mon_2);

        widget_7 = new QWidget(Panel_Monitor_2);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        Btn_ClearPerformData = new QPushButton(widget_7);
        Btn_ClearPerformData->setObjectName(QString::fromUtf8("Btn_ClearPerformData"));
        Btn_ClearPerformData->setGeometry(QRect(10, 30, 101, 31));
        pushButton_7 = new QPushButton(widget_7);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(160, 30, 101, 31));

        verticalLayout_12->addWidget(widget_7);

        widget_11 = new QWidget(Panel_Monitor_2);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        horizontalLayout_23 = new QHBoxLayout(widget_11);
        horizontalLayout_23->setSpacing(50);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);

        verticalLayout_12->addWidget(widget_11);


        horizontalLayout_24->addWidget(Panel_Monitor_2);

        Plot_Performance = new QWidget(Show_Performance);
        Plot_Performance->setObjectName(QString::fromUtf8("Plot_Performance"));
        LayoutforPerform = new QVBoxLayout(Plot_Performance);
        LayoutforPerform->setObjectName(QString::fromUtf8("LayoutforPerform"));

        horizontalLayout_24->addWidget(Plot_Performance);

        Show_MainWindow->addTab(Show_Performance, QString());
        Show_Result = new QWidget();
        Show_Result->setObjectName(QString::fromUtf8("Show_Result"));
        verticalLayout_9 = new QVBoxLayout(Show_Result);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        Result_Table = new QTableWidget(Show_Result);
        if (Result_Table->columnCount() < 6)
            Result_Table->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        Result_Table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (Result_Table->rowCount() < 25)
            Result_Table->setRowCount(25);
        Result_Table->setObjectName(QString::fromUtf8("Result_Table"));
        Result_Table->setRowCount(25);
        Result_Table->setColumnCount(6);
        Result_Table->horizontalHeader()->setDefaultSectionSize(210);
        Result_Table->verticalHeader()->setDefaultSectionSize(40);

        verticalLayout_9->addWidget(Result_Table);

        Show_MainWindow->addTab(Show_Result, QString());

        horizontalLayout_3->addWidget(Show_MainWindow);


        horizontalLayout_2->addWidget(widget_2);

        PreMainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(PreMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PreMainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(PreMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        PreMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        menubar = new QMenuBar(PreMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1920, 24));
        QFont font4;
        font4.setPointSize(12);
        menubar->setFont(font4);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font4);
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuTools->setFont(font4);
        PreMainWindow->setMenuBar(menubar);

        toolBar->addAction(actionGeneral);
        toolBar->addAction(actionTurbo);
        toolBar->addAction(actionactionFilmCooling);
        toolBar->addAction(actionBC);
        toolBar->addAction(actionSolver);
        toolBar->addAction(actionactionSaveTab);
        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionLoadMain);

        retranslateUi(PreMainWindow);

        stackedWidget->setCurrentIndex(5);
        Show_MainWindow->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(PreMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PreMainWindow)
    {
        PreMainWindow->setWindowTitle(QCoreApplication::translate("PreMainWindow", "Cipher v1.0", nullptr));
        actionGeneral->setText(QCoreApplication::translate("PreMainWindow", "General", nullptr));
#if QT_CONFIG(tooltip)
        actionGeneral->setToolTip(QCoreApplication::translate("PreMainWindow", "General ", nullptr));
#endif // QT_CONFIG(tooltip)
        actionTurbo->setText(QCoreApplication::translate("PreMainWindow", "Turbomachinery", nullptr));
#if QT_CONFIG(tooltip)
        actionTurbo->setToolTip(QCoreApplication::translate("PreMainWindow", "Turbomachinery", nullptr));
#endif // QT_CONFIG(tooltip)
        actionSolver->setText(QCoreApplication::translate("PreMainWindow", "Initial Conditions", nullptr));
#if QT_CONFIG(tooltip)
        actionSolver->setToolTip(QCoreApplication::translate("PreMainWindow", "Solver setup", nullptr));
#endif // QT_CONFIG(tooltip)
        actionBC->setText(QCoreApplication::translate("PreMainWindow", "Boundary Conditions", nullptr));
#if QT_CONFIG(tooltip)
        actionBC->setToolTip(QCoreApplication::translate("PreMainWindow", "Boundary conditions", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMonitor->setText(QCoreApplication::translate("PreMainWindow", "Monitor", nullptr));
#if QT_CONFIG(tooltip)
        actionMonitor->setToolTip(QCoreApplication::translate("PreMainWindow", "Monitor", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNew->setText(QCoreApplication::translate("PreMainWindow", "New", nullptr));
        actionLoadMain->setText(QCoreApplication::translate("PreMainWindow", "Load", nullptr));
        actionactionSaveTab->setText(QCoreApplication::translate("PreMainWindow", "Run Simulation", nullptr));
        actionactionFilmCooling->setText(QCoreApplication::translate("PreMainWindow", "FilmCooling", nullptr));
#if QT_CONFIG(tooltip)
        actionactionFilmCooling->setToolTip(QCoreApplication::translate("PreMainWindow", "Film Cooling", nullptr));
#endif // QT_CONFIG(tooltip)
        label_general->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">General Setup</span></p></body></html>", nullptr));
        unsteady_checkbox->setText(QCoreApplication::translate("PreMainWindow", "Unsteady", nullptr));
        annular_checkbox->setText(QCoreApplication::translate("PreMainWindow", "Annular", nullptr));
        film_checkbox->setText(QCoreApplication::translate("PreMainWindow", "Film Cooling", nullptr));
        label_turbulence_model->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Turbulence Model</span></p></body></html>", nullptr));
        tb_name_label->setText(QCoreApplication::translate("PreMainWindow", "Turbulence Type", nullptr));
        tb_type_combo->setItemText(0, QCoreApplication::translate("PreMainWindow", "RANS", nullptr));
        tb_type_combo->setItemText(1, QCoreApplication::translate("PreMainWindow", "LES", nullptr));
        tb_type_combo->setItemText(2, QCoreApplication::translate("PreMainWindow", "DES", nullptr));

        label_rans1->setText(QCoreApplication::translate("PreMainWindow", "RANS Model", nullptr));
        check_wf->setText(QString());
        checkBox_transition->setText(QString());
        label_kl->setText(QCoreApplication::translate("PreMainWindow", "Near Wall KL Model", nullptr));
        label_wf1->setText(QCoreApplication::translate("PreMainWindow", "Wall Function", nullptr));
        conbo_rans->setItemText(0, QCoreApplication::translate("PreMainWindow", "Spalart-Allmaras(SA)", nullptr));
        conbo_rans->setItemText(1, QCoreApplication::translate("PreMainWindow", "k-epsilon(k-\316\265)", nullptr));
        conbo_rans->setItemText(2, QCoreApplication::translate("PreMainWindow", "k-omega(k-\317\211)", nullptr));
        conbo_rans->setItemText(3, QCoreApplication::translate("PreMainWindow", "laminar", nullptr));

        label_transition->setText(QCoreApplication::translate("PreMainWindow", "Transition Model", nullptr));
        checkBox_helicity->setText(QString());
        checkBox_cmott->setText(QString());
        comboBox_qcr->setItemText(0, QCoreApplication::translate("PreMainWindow", "none", nullptr));
        comboBox_qcr->setItemText(1, QCoreApplication::translate("PreMainWindow", "2000", nullptr));
        comboBox_qcr->setItemText(2, QCoreApplication::translate("PreMainWindow", "2020", nullptr));

        checkBox_kl->setText(QString());
        label_cmott->setText(QCoreApplication::translate("PreMainWindow", "Realizable", nullptr));
        label_qcr->setText(QCoreApplication::translate("PreMainWindow", "QCR Model", nullptr));
        label_helicity->setText(QCoreApplication::translate("PreMainWindow", "Helicity Model", nullptr));
        label_des_dx->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>DES C<span style=\" vertical-align:sub;\">s</span></p></body></html>", nullptr));
        label_les_dx->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>LES C<span style=\" vertical-align:sub;\">s</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Gas model</span></p></body></html>", nullptr));
        gas_friction_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>Fuel Fraction </p></body></html>", nullptr));
        gas_type_label->setText(QCoreApplication::translate("PreMainWindow", "Gas Type", nullptr));
        gas_friction_lineEdit->setText(QCoreApplication::translate("PreMainWindow", "0.0", nullptr));
        gas_type_combo->setItemText(0, QCoreApplication::translate("PreMainWindow", "Ideal gas", nullptr));
        gas_type_combo->setItemText(1, QCoreApplication::translate("PreMainWindow", "Real gas", nullptr));

        label_10->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Coordinate Transformation</span></p></body></html>", nullptr));
        label_12->setText(QCoreApplication::translate("PreMainWindow", "Scale", nullptr));
        lineEdit_factor_x->setText(QCoreApplication::translate("PreMainWindow", "1.0", nullptr));
        gas_friction_label_3->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>axis x</p></body></html>", nullptr));
        lineEdit_factor_y->setText(QCoreApplication::translate("PreMainWindow", "1.0", nullptr));
        gas_friction_label_5->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>axis y</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("PreMainWindow", "Rotation", nullptr));
        lineEdit_axis_x->setText(QCoreApplication::translate("PreMainWindow", "1.0", nullptr));
        lineEdit_axis_y->setText(QCoreApplication::translate("PreMainWindow", "0.0", nullptr));
        gas_friction_label_6->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>factor y</p></body></html>", nullptr));
        gas_friction_label_4->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>factor x</p></body></html>", nullptr));
        gas_friction_label_7->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>axis z</p></body></html>", nullptr));
        lineEdit_axis_z->setText(QCoreApplication::translate("PreMainWindow", "0.0", nullptr));
        gas_friction_label_8->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>factor z</p></body></html>", nullptr));
        lineEdit_factor_z->setText(QCoreApplication::translate("PreMainWindow", "1.0", nullptr));
        label_13->setText(QCoreApplication::translate("PreMainWindow", "Axis Vector", nullptr));
        label_turbomachinery->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Turbomachinery setup</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Blade Row Setting</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Rotor-stator interface</span></p></body></html>", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = turbo_zone_tree->headerItem();
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("PreMainWindow", "Angular Velocity (rad/s)", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("PreMainWindow", "Rotor/Stator", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("PreMainWindow", "Name", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = turbo_interface_tree->headerItem();
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("PreMainWindow", "Downstream", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("PreMainWindow", "Upstream", nullptr));
        passage_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Passage repeat</span></p></body></html>", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = passage_repeat_tree->headerItem();
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("PreMainWindow", "Num repeat", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("PreMainWindow", "Angle", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("PreMainWindow", "Name", nullptr));
        checkBox_passage_repeat->setText(QString());
        interface_type_label->setText(QCoreApplication::translate("PreMainWindow", "type: mixing plane", nullptr));
        gamma_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Gamma (\316\263)</p></body></html>", nullptr));
        p_lineEdit->setText(QString());
        k_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m<span style=\" vertical-align:super;\">2</span>/s<span style=\" vertical-align:super;\">2</span></p></body></html>", nullptr));
        v_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Velocity (v)</p></body></html>", nullptr));
        sa_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">SA eddy viscocity</p></body></html>", nullptr));
        v_lineEdit->setText(QString());
        label_unit_w->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m/s </p></body></html>", nullptr));
        omega_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Omega (\317\211)</p></body></html>", nullptr));
        pressure_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>Pa </p></body></html>", nullptr));
        label_unit_v->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m/s </p></body></html>", nullptr));
        epsilon_lineEdit->setText(QString());
        gamma_lineEdit->setText(QString());
        k_lineEdit->setText(QString());
        rho_lineEdit->setText(QString());
        omega_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>1/s</p></body></html>", nullptr));
        label_unit_u->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m/s </p></body></html>", nullptr));
        rho_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Density (\317\201)</p></body></html>", nullptr));
        epsilon_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Epsilon (\316\265)</p></body></html>", nullptr));
        sa_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m<span style=\" vertical-align:super;\">2</span>/s</p></body></html>", nullptr));
        label_unit_density->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>Kg/m<span style=\" vertical-align:super;\">3</span></p></body></html>", nullptr));
        u_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Velocity (u)</p></body></html>", nullptr));
        k_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">turublence-model(k)</p></body></html>", nullptr));
        p_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Pressure (p)</p></body></html>", nullptr));
        u_lineEdit->setText(QString());
        w_labe->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Velocity (w)</p></body></html>", nullptr));
        omega_lineEdit->setText(QString());
        epsilon_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>m<span style=\" vertical-align:super;\">2</span>/s<span style=\" vertical-align:super;\">3</span></p></body></html>", nullptr));
        w_lineEdit->setText(QString());
        sa_lineEdit->setText(QString());
        period_match_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">periodic match tol</p></body></html>", nullptr));
        residual_unit->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-family:'Arial','sans-serif'; font-size:13px; color:#333333; background-color:#ffffff;\">1\303\22710</span><span style=\" font-family:'Arial','sans-serif'; font-size:13px; color:#333333; background-color:#ffffff; vertical-align:super;\">-N</span></p></body></html>", nullptr));
        period_match_lineEdit->setText(QString());
        CFL_ramp_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">CFL rampup</p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Advanced</span></p></body></html>", nullptr));
        MG_level_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Multi-Grid level</p></body></html>", nullptr));
        run_pre_process->setText(QCoreApplication::translate("PreMainWindow", "Run Preprocess", nullptr));
        saveYAMLButton->setText(QCoreApplication::translate("PreMainWindow", "Save YAML", nullptr));
        CFL_ramp_lineEdit->setText(QString());
        residual_lineEdit->setText(QString());
        CFL_ramp_label_2->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Residual level N </p></body></html>", nullptr));
        skip_pre_checkBox->setText(QCoreApplication::translate("PreMainWindow", "skip_pre", nullptr));
        label_monitor->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Initial condition</span></p></body></html>", nullptr));
        load_steady_flow->setText(QCoreApplication::translate("PreMainWindow", "Load Initial Flow", nullptr));
        label_bc->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Zones</span></p></body></html>", nullptr));
        label_bc_2->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Boundary conditions in zone</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Film Cooling Setup</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Zone list</span></p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Film coolling in zone</span></p></body></html>", nullptr));
        generate_film_boundary->setText(QCoreApplication::translate("PreMainWindow", "Generate film cooling boundary", nullptr));
        label_6->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Run Simulation</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("PreMainWindow", "CPU Cores", nullptr));
        start_simulation_button->setText(QCoreApplication::translate("PreMainWindow", "Start ", nullptr));
        continue_simulation_button->setText(QCoreApplication::translate("PreMainWindow", "Continue", nullptr));
        stop_simulation_button->setText(QCoreApplication::translate("PreMainWindow", "Stop", nullptr));
        checkBox_performance->setText(QCoreApplication::translate("PreMainWindow", "Performance curve (For steady simulation)", nullptr));
        current_p_label->setText(QCoreApplication::translate("PreMainWindow", "Previous back P (Pa)", nullptr));
        current_p_value->setText(QCoreApplication::translate("PreMainWindow", "0.0", nullptr));
        target_p_label->setText(QCoreApplication::translate("PreMainWindow", "Current back P (Pa)", nullptr));
        save_p_button->setText(QCoreApplication::translate("PreMainWindow", "Save", nullptr));
        load_p_button->setText(QCoreApplication::translate("PreMainWindow", "Load", nullptr));
        unsteady_simulation_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Unsteady Simulation Setup</span></p></body></html>", nullptr));
        step_per_cycle_lineEdit->setText(QString());
        period_lineEdit->setText(QString());
        output_unsteady_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Output Step</p></body></html>", nullptr));
        output_unsteady_lineEdit->setText(QString());
        period_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Time per revolution</p></body></html>", nullptr));
        label_les_dt->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">LES \316\224t<span style=\" vertical-align:sub;\">max</span></p></body></html>", nullptr));
        n_cycle_lineEdit->setText(QString());
        step_per_cycle_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Steps per revolution</p></body></html>", nullptr));
        n_cycle_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Number of revolutions</p></body></html>", nullptr));
        period_unit_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p>(s)</p></body></html>", nullptr));
        steady_iteration_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Steady Simulation Setup</span></p></body></html>", nullptr));
        unsteady_inner_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">Inner Iteration Setup</span></p></body></html>", nullptr));
        CFL_lineEdit->setText(QString());
        iteration_step_lineEdit->setText(QString());
        iteration_step_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Max iteration steps</p></body></html>", nullptr));
        CFL_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">CFL</p></body></html>", nullptr));
        output_steady_lineEdit->setText(QString());
        output_steady_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p align=\"right\">Output Step</p></body></html>", nullptr));
        monitor_label->setText(QCoreApplication::translate("PreMainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">Monitors</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("PreMainWindow", "Add monitor", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = monitor_tree->headerItem();
        ___qtreewidgetitem3->setText(4, QCoreApplication::translate("PreMainWindow", "delete", nullptr));
        ___qtreewidgetitem3->setText(3, QCoreApplication::translate("PreMainWindow", "average type", nullptr));
        ___qtreewidgetitem3->setText(2, QCoreApplication::translate("PreMainWindow", "match face", nullptr));
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("PreMainWindow", "face ", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("PreMainWindow", "type", nullptr));
        label_44->setText(QCoreApplication::translate("PreMainWindow", "Auto Run", nullptr));
        label_14->setText(QCoreApplication::translate("PreMainWindow", "Start Pressure:", nullptr));
        Btn_Skip_AutoRun->setText(QCoreApplication::translate("PreMainWindow", "Skip", nullptr));
        Btn_End_AutoRun->setText(QCoreApplication::translate("PreMainWindow", "End", nullptr));
        label_15->setText(QCoreApplication::translate("PreMainWindow", "End Pressure:", nullptr));
        label_43->setText(QCoreApplication::translate("PreMainWindow", "Number of Points:", nullptr));
        LEdit_NumPoints_AutoRun->setText(QString());
        Btn_Start_AutoRun->setText(QCoreApplication::translate("PreMainWindow", "Start", nullptr));
        Show_MainWindow->setTabText(Show_MainWindow->indexOf(Show_Model), QCoreApplication::translate("PreMainWindow", "Model", nullptr));
        label_27->setText(QCoreApplication::translate("PreMainWindow", "Graph Options", nullptr));
        Btn_AutoScale_Res->setText(QCoreApplication::translate("PreMainWindow", "AutoScale", nullptr));
        Btn_ManualScale_Res->setText(QCoreApplication::translate("PreMainWindow", "ManualScale", nullptr));
        label_29->setText(QCoreApplication::translate("PreMainWindow", "Range X:", nullptr));
        label_25->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_26->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        label_28->setText(QCoreApplication::translate("PreMainWindow", "Range Y1:", nullptr));
        label_23->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_24->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        label_33->setText(QCoreApplication::translate("PreMainWindow", "Range Y2:", nullptr));
        label_31->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_32->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        label_45->setText(QCoreApplication::translate("PreMainWindow", "AutoRun History:", nullptr));
        Btn_ClearHistory->setText(QCoreApplication::translate("PreMainWindow", "Clear", nullptr));
        label_34->setText(QCoreApplication::translate("PreMainWindow", "Theme:", nullptr));
        Btn_SyncWindowTheme->setText(QCoreApplication::translate("PreMainWindow", "Sync", nullptr));
        Show_MainWindow->setTabText(Show_MainWindow->indexOf(Show_Convergence), QCoreApplication::translate("PreMainWindow", "Convergence", nullptr));
        label_22->setText(QCoreApplication::translate("PreMainWindow", "Graph Options", nullptr));
        Btn_SelectMonitor->setText(QCoreApplication::translate("PreMainWindow", "Select MonitorFile", nullptr));
        label_30->setText(QCoreApplication::translate("PreMainWindow", "Variable List :", nullptr));
        Btn_AutoScale_Mon->setText(QCoreApplication::translate("PreMainWindow", "AutoScale", nullptr));
        Btn_ManualScale_Mon->setText(QCoreApplication::translate("PreMainWindow", "ManualScale", nullptr));
        label_16->setText(QCoreApplication::translate("PreMainWindow", "Range X:", nullptr));
        label_18->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_19->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        label_17->setText(QCoreApplication::translate("PreMainWindow", "Range Y:", nullptr));
        label_20->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_21->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        Show_MainWindow->setTabText(Show_MainWindow->indexOf(Show_Monitor), QCoreApplication::translate("PreMainWindow", "Monitor", nullptr));
        label_35->setText(QCoreApplication::translate("PreMainWindow", "Graph Options", nullptr));
        label_36->setText(QCoreApplication::translate("PreMainWindow", "Select Variable :", nullptr));
        label_37->setText(QCoreApplication::translate("PreMainWindow", "Range X:", nullptr));
        label_38->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_39->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        label_40->setText(QCoreApplication::translate("PreMainWindow", "Range Y:", nullptr));
        label_41->setText(QCoreApplication::translate("PreMainWindow", "Min", nullptr));
        label_42->setText(QCoreApplication::translate("PreMainWindow", "Max", nullptr));
        Btn_ClearPerformData->setText(QCoreApplication::translate("PreMainWindow", "Clear Data", nullptr));
        pushButton_7->setText(QCoreApplication::translate("PreMainWindow", "Export Picture", nullptr));
        Show_MainWindow->setTabText(Show_MainWindow->indexOf(Show_Performance), QCoreApplication::translate("PreMainWindow", "Perform_Curve", nullptr));
        QTableWidgetItem *___qtablewidgetitem = Result_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("PreMainWindow", "Run Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = Result_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("PreMainWindow", "Pressure", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = Result_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("PreMainWindow", "Mass Flow", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = Result_Table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("PreMainWindow", "Pressure Ratio", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = Result_Table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("PreMainWindow", "Temperature Ratio", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = Result_Table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("PreMainWindow", "Efficiency", nullptr));
        Show_MainWindow->setTabText(Show_MainWindow->indexOf(Show_Result), QCoreApplication::translate("PreMainWindow", "Result_Table", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("PreMainWindow", "toolBar", nullptr));
        menuFile->setTitle(QCoreApplication::translate("PreMainWindow", "&File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("PreMainWindow", "&Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PreMainWindow: public Ui_PreMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREMAINWINDOW_H
