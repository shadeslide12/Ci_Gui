/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKOpenGLNativeWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpenFile;
    QAction *actionLoadMesh;
    QAction *actionUpdateFlow;
    QAction *actionAddScalarBarActor;
    QAction *actionAddAxisActor;
    QAction *actionAddOutlineActor;
    QAction *actionAddPointInformation;
    QAction *actionCalculatorFunction;
    QAction *actionNewWindow;
    QAction *actionExport_Picture;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *mainSplitter;
    QTabWidget *tabWidget_Control;
    QWidget *tab_normal;
    QVBoxLayout *verticalLayout_tab1;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_2;
    QWidget *buttonWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *xoyView;
    QPushButton *xozView;
    QPushButton *yozView;
    QPushButton *xyzView;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *contourCheckBox;
    QPushButton *contourSettingButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *meshCheckBox;
    QSpacerItem *horizontalSpacer_7;
    QCheckBox *shadeCheckBox;
    QCheckBox *edgeCheckBox;
    QPushButton *selectBoundaryButton;
    QLabel *label_4;
    QWidget *widget_3;
    QPushButton *IsoSurfaceSettingButton;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *slicesCheckBox;
    QCheckBox *isoSurfaceCheckBox;
    QPushButton *addSliceButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QWidget *widget_5;
    QGridLayout *gridLayout_4;
    QCheckBox *lightingCheckBox;
    QSpacerItem *horizontalSpacer_16;
    QCheckBox *transparancyCheckBox;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QComboBox *CBtn_BackGround;
    QWidget *Wi_expan;
    QWidget *tab_turbo;
    QVBoxLayout *turboTabLayout;
    QLabel *label_3;
    QPushButton *Btn_TurboInitial;
    QWidget *Wi_TurboSet;
    QVBoxLayout *turboSetLayout;
    QWidget *Wi_BasicInfo;
    QVBoxLayout *basicInfoLayout;
    QCheckBox *Check_3Dview;
    QCheckBox *Check_Meri;
    QCheckBox *Check_BladeToBlade;
    QCheckBox *Check_ThreeView;
    QWidget *Wi_Copy;
    QGridLayout *gridLayout_3;
    QLabel *label_8;
    QLabel *label_9;
    QComboBox *com_copy;
    QLabel *label_10;
    QLineEdit *Led_Copy;
    QScrollArea *periodicCopyScrollArea;
    QWidget *periodicCopyContainer;
    QGridLayout *periodicCopyGridLayout;
    QPushButton *Btn_ApplyCopy;
    QPushButton *Btn_ClearCopyCurrentZone;
    QPushButton *Btn_ClearAllZoneCopy;
    QWidget *Wi_B2B_2;
    QGridLayout *Wi_B2B;
    QSlider *Sli_Span;
    QLabel *label_19;
    QPushButton *Btn_Apply;
    QLabel *label_BladeToBlade;
    QWidget *wi_expan;
    QWidget *vtkContainer;
    QVBoxLayout *VTKLayout;
    QVTKOpenGLNativeWidget *vtkBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1666, 1031);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        MainWindow->setFont(font);
        actionOpenFile = new QAction(MainWindow);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionLoadMesh = new QAction(MainWindow);
        actionLoadMesh->setObjectName(QString::fromUtf8("actionLoadMesh"));
        actionUpdateFlow = new QAction(MainWindow);
        actionUpdateFlow->setObjectName(QString::fromUtf8("actionUpdateFlow"));
        actionAddScalarBarActor = new QAction(MainWindow);
        actionAddScalarBarActor->setObjectName(QString::fromUtf8("actionAddScalarBarActor"));
        actionAddAxisActor = new QAction(MainWindow);
        actionAddAxisActor->setObjectName(QString::fromUtf8("actionAddAxisActor"));
        actionAddOutlineActor = new QAction(MainWindow);
        actionAddOutlineActor->setObjectName(QString::fromUtf8("actionAddOutlineActor"));
        actionAddPointInformation = new QAction(MainWindow);
        actionAddPointInformation->setObjectName(QString::fromUtf8("actionAddPointInformation"));
        actionCalculatorFunction = new QAction(MainWindow);
        actionCalculatorFunction->setObjectName(QString::fromUtf8("actionCalculatorFunction"));
        actionCalculatorFunction->setEnabled(true);
        actionNewWindow = new QAction(MainWindow);
        actionNewWindow->setObjectName(QString::fromUtf8("actionNewWindow"));
        actionExport_Picture = new QAction(MainWindow);
        actionExport_Picture->setObjectName(QString::fromUtf8("actionExport_Picture"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        mainSplitter = new QSplitter(widget_2);
        mainSplitter->setObjectName(QString::fromUtf8("mainSplitter"));
        mainSplitter->setOrientation(Qt::Orientation::Horizontal);
        mainSplitter->setHandleWidth(4);
        mainSplitter->setChildrenCollapsible(false);
        tabWidget_Control = new QTabWidget(mainSplitter);
        tabWidget_Control->setObjectName(QString::fromUtf8("tabWidget_Control"));
        tabWidget_Control->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_Control->sizePolicy().hasHeightForWidth());
        tabWidget_Control->setSizePolicy(sizePolicy1);
        tabWidget_Control->setMinimumSize(QSize(280, 0));
        tabWidget_Control->setMaximumSize(QSize(350, 16777215));
        tab_normal = new QWidget();
        tab_normal->setObjectName(QString::fromUtf8("tab_normal"));
        verticalLayout_tab1 = new QVBoxLayout(tab_normal);
        verticalLayout_tab1->setObjectName(QString::fromUtf8("verticalLayout_tab1"));
        scrollArea = new QScrollArea(tab_normal);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(false);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 324, 902));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        widget_4 = new QWidget(scrollAreaWidgetContents_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        sizePolicy2.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy2);
        verticalLayout_2 = new QVBoxLayout(widget_4);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        buttonWidget = new QWidget(widget_4);
        buttonWidget->setObjectName(QString::fromUtf8("buttonWidget"));
        sizePolicy2.setHeightForWidth(buttonWidget->sizePolicy().hasHeightForWidth());
        buttonWidget->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(buttonWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        xoyView = new QPushButton(buttonWidget);
        xoyView->setObjectName(QString::fromUtf8("xoyView"));
        sizePolicy2.setHeightForWidth(xoyView->sizePolicy().hasHeightForWidth());
        xoyView->setSizePolicy(sizePolicy2);
        xoyView->setMinimumSize(QSize(35, 35));
        xoyView->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(xoyView);

        xozView = new QPushButton(buttonWidget);
        xozView->setObjectName(QString::fromUtf8("xozView"));
        sizePolicy2.setHeightForWidth(xozView->sizePolicy().hasHeightForWidth());
        xozView->setSizePolicy(sizePolicy2);
        xozView->setMinimumSize(QSize(35, 35));
        xozView->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(xozView);

        yozView = new QPushButton(buttonWidget);
        yozView->setObjectName(QString::fromUtf8("yozView"));
        sizePolicy2.setHeightForWidth(yozView->sizePolicy().hasHeightForWidth());
        yozView->setSizePolicy(sizePolicy2);
        yozView->setMinimumSize(QSize(35, 35));
        yozView->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(yozView);

        xyzView = new QPushButton(buttonWidget);
        xyzView->setObjectName(QString::fromUtf8("xyzView"));
        sizePolicy2.setHeightForWidth(xyzView->sizePolicy().hasHeightForWidth());
        xyzView->setSizePolicy(sizePolicy2);
        xyzView->setMinimumSize(QSize(35, 35));
        xyzView->setMaximumSize(QSize(35, 35));

        horizontalLayout->addWidget(xyzView);


        verticalLayout_2->addWidget(buttonWidget);


        verticalLayout->addWidget(widget_4);

        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font);
        label->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

        verticalLayout->addWidget(label);

        widget = new QWidget(scrollAreaWidgetContents_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        contourCheckBox = new QCheckBox(widget);
        contourCheckBox->setObjectName(QString::fromUtf8("contourCheckBox"));
        contourCheckBox->setMinimumSize(QSize(150, 0));
        contourCheckBox->setFont(font);
        contourCheckBox->setChecked(true);

        gridLayout_2->addWidget(contourCheckBox, 3, 1, 1, 1);

        contourSettingButton = new QPushButton(widget);
        contourSettingButton->setObjectName(QString::fromUtf8("contourSettingButton"));
        contourSettingButton->setMinimumSize(QSize(20, 20));
        contourSettingButton->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(contourSettingButton, 3, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 4, 0, 1, 1);

        meshCheckBox = new QCheckBox(widget);
        meshCheckBox->setObjectName(QString::fromUtf8("meshCheckBox"));
        meshCheckBox->setFont(font);

        gridLayout_2->addWidget(meshCheckBox, 2, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 5, 0, 1, 1);

        shadeCheckBox = new QCheckBox(widget);
        shadeCheckBox->setObjectName(QString::fromUtf8("shadeCheckBox"));
        shadeCheckBox->setFont(font);
        shadeCheckBox->setChecked(true);

        gridLayout_2->addWidget(shadeCheckBox, 4, 1, 1, 1);

        edgeCheckBox = new QCheckBox(widget);
        edgeCheckBox->setObjectName(QString::fromUtf8("edgeCheckBox"));
        edgeCheckBox->setFont(font);

        gridLayout_2->addWidget(edgeCheckBox, 5, 1, 1, 1);


        verticalLayout->addWidget(widget);

        selectBoundaryButton = new QPushButton(scrollAreaWidgetContents_2);
        selectBoundaryButton->setObjectName(QString::fromUtf8("selectBoundaryButton"));
        selectBoundaryButton->setFont(font);

        verticalLayout->addWidget(selectBoundaryButton);

        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        widget_3 = new QWidget(scrollAreaWidgetContents_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        widget_3->setMinimumSize(QSize(220, 0));
        widget_3->setMaximumSize(QSize(220, 16777215));
        IsoSurfaceSettingButton = new QPushButton(widget_3);
        IsoSurfaceSettingButton->setObjectName(QString::fromUtf8("IsoSurfaceSettingButton"));
        IsoSurfaceSettingButton->setGeometry(QRect(191, 11, 20, 20));
        IsoSurfaceSettingButton->setMinimumSize(QSize(20, 20));
        IsoSurfaceSettingButton->setMaximumSize(QSize(20, 20));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        slicesCheckBox = new QCheckBox(widget_3);
        slicesCheckBox->setObjectName(QString::fromUtf8("slicesCheckBox"));
        slicesCheckBox->setMinimumSize(QSize(186, 0));
        slicesCheckBox->setFont(font);

        gridLayout->addWidget(slicesCheckBox, 2, 1, 1, 1);

        isoSurfaceCheckBox = new QCheckBox(widget_3);
        isoSurfaceCheckBox->setObjectName(QString::fromUtf8("isoSurfaceCheckBox"));
        sizePolicy.setHeightForWidth(isoSurfaceCheckBox->sizePolicy().hasHeightForWidth());
        isoSurfaceCheckBox->setSizePolicy(sizePolicy);
        isoSurfaceCheckBox->setMinimumSize(QSize(100, 1));
        isoSurfaceCheckBox->setMaximumSize(QSize(150, 16777215));
        isoSurfaceCheckBox->setFont(font);
        isoSurfaceCheckBox->setIconSize(QSize(16, 16));
        isoSurfaceCheckBox->setChecked(false);
        isoSurfaceCheckBox->setAutoExclusive(false);

        gridLayout->addWidget(isoSurfaceCheckBox, 1, 1, 1, 1);

        addSliceButton = new QPushButton(widget_3);
        addSliceButton->setObjectName(QString::fromUtf8("addSliceButton"));
        addSliceButton->setMinimumSize(QSize(20, 20));
        addSliceButton->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(addSliceButton, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_3);

        label_6 = new QLabel(scrollAreaWidgetContents_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        widget_5 = new QWidget(scrollAreaWidgetContents_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        sizePolicy3.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy3);
        widget_5->setMinimumSize(QSize(220, 0));
        widget_5->setMaximumSize(QSize(220, 80));
        gridLayout_4 = new QGridLayout(widget_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lightingCheckBox = new QCheckBox(widget_5);
        lightingCheckBox->setObjectName(QString::fromUtf8("lightingCheckBox"));
        lightingCheckBox->setMinimumSize(QSize(186, 0));
        lightingCheckBox->setFont(font);

        gridLayout_4->addWidget(lightingCheckBox, 2, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_16, 1, 0, 1, 1);

        transparancyCheckBox = new QCheckBox(widget_5);
        transparancyCheckBox->setObjectName(QString::fromUtf8("transparancyCheckBox"));
        sizePolicy.setHeightForWidth(transparancyCheckBox->sizePolicy().hasHeightForWidth());
        transparancyCheckBox->setSizePolicy(sizePolicy);
        transparancyCheckBox->setMinimumSize(QSize(186, 1));
        transparancyCheckBox->setMaximumSize(QSize(16777215, 16777215));
        transparancyCheckBox->setFont(font);
        transparancyCheckBox->setIconSize(QSize(16, 16));
        transparancyCheckBox->setChecked(false);
        transparancyCheckBox->setAutoExclusive(false);

        gridLayout_4->addWidget(transparancyCheckBox, 1, 1, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 2, 0, 1, 1);


        verticalLayout->addWidget(widget_5);

        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_7 = new QLabel(scrollAreaWidgetContents_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        label_7->setFont(font1);

        horizontalLayout_6->addWidget(label_7);

        CBtn_BackGround = new QComboBox(scrollAreaWidgetContents_2);
        CBtn_BackGround->addItem(QString());
        CBtn_BackGround->addItem(QString());
        CBtn_BackGround->setObjectName(QString::fromUtf8("CBtn_BackGround"));
        QFont font2;
        font2.setPointSize(9);
        font2.setBold(true);
        CBtn_BackGround->setFont(font2);

        horizontalLayout_6->addWidget(CBtn_BackGround);


        verticalLayout->addLayout(horizontalLayout_6);

        Wi_expan = new QWidget(scrollAreaWidgetContents_2);
        Wi_expan->setObjectName(QString::fromUtf8("Wi_expan"));

        verticalLayout->addWidget(Wi_expan);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_tab1->addWidget(scrollArea);

        tabWidget_Control->addTab(tab_normal, QString());
        tab_turbo = new QWidget();
        tab_turbo->setObjectName(QString::fromUtf8("tab_turbo"));
        turboTabLayout = new QVBoxLayout(tab_turbo);
        turboTabLayout->setObjectName(QString::fromUtf8("turboTabLayout"));
        turboTabLayout->setContentsMargins(4, 4, 4, 4);
        label_3 = new QLabel(tab_turbo);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        turboTabLayout->addWidget(label_3);

        Btn_TurboInitial = new QPushButton(tab_turbo);
        Btn_TurboInitial->setObjectName(QString::fromUtf8("Btn_TurboInitial"));
        Btn_TurboInitial->setFont(font);

        turboTabLayout->addWidget(Btn_TurboInitial);

        Wi_TurboSet = new QWidget(tab_turbo);
        Wi_TurboSet->setObjectName(QString::fromUtf8("Wi_TurboSet"));
        Wi_TurboSet->setEnabled(false);
        turboSetLayout = new QVBoxLayout(Wi_TurboSet);
        turboSetLayout->setSpacing(6);
        turboSetLayout->setObjectName(QString::fromUtf8("turboSetLayout"));
        turboSetLayout->setContentsMargins(0, 0, 0, 0);
        Wi_BasicInfo = new QWidget(Wi_TurboSet);
        Wi_BasicInfo->setObjectName(QString::fromUtf8("Wi_BasicInfo"));
        sizePolicy.setHeightForWidth(Wi_BasicInfo->sizePolicy().hasHeightForWidth());
        Wi_BasicInfo->setSizePolicy(sizePolicy);
        basicInfoLayout = new QVBoxLayout(Wi_BasicInfo);
        basicInfoLayout->setSpacing(2);
        basicInfoLayout->setObjectName(QString::fromUtf8("basicInfoLayout"));
        basicInfoLayout->setContentsMargins(0, 0, 0, 0);
        Check_3Dview = new QCheckBox(Wi_BasicInfo);
        Check_3Dview->setObjectName(QString::fromUtf8("Check_3Dview"));
        Check_3Dview->setFont(font1);
        Check_3Dview->setChecked(true);

        basicInfoLayout->addWidget(Check_3Dview);

        Check_Meri = new QCheckBox(Wi_BasicInfo);
        Check_Meri->setObjectName(QString::fromUtf8("Check_Meri"));
        Check_Meri->setFont(font1);

        basicInfoLayout->addWidget(Check_Meri);

        Check_BladeToBlade = new QCheckBox(Wi_BasicInfo);
        Check_BladeToBlade->setObjectName(QString::fromUtf8("Check_BladeToBlade"));
        Check_BladeToBlade->setFont(font1);

        basicInfoLayout->addWidget(Check_BladeToBlade);

        Check_ThreeView = new QCheckBox(Wi_BasicInfo);
        Check_ThreeView->setObjectName(QString::fromUtf8("Check_ThreeView"));
        Check_ThreeView->setFont(font1);

        basicInfoLayout->addWidget(Check_ThreeView);


        turboSetLayout->addWidget(Wi_BasicInfo);

        Wi_Copy = new QWidget(Wi_TurboSet);
        Wi_Copy->setObjectName(QString::fromUtf8("Wi_Copy"));
        sizePolicy.setHeightForWidth(Wi_Copy->sizePolicy().hasHeightForWidth());
        Wi_Copy->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(Wi_Copy);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_8 = new QLabel(Wi_Copy);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setFont(font);

        gridLayout_3->addWidget(label_8, 0, 0, 1, 3);

        label_9 = new QLabel(Wi_Copy);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        label_9->setFont(font3);

        gridLayout_3->addWidget(label_9, 1, 0, 1, 1);

        com_copy = new QComboBox(Wi_Copy);
        com_copy->setObjectName(QString::fromUtf8("com_copy"));

        gridLayout_3->addWidget(com_copy, 1, 1, 1, 2);

        label_10 = new QLabel(Wi_Copy);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font3);

        gridLayout_3->addWidget(label_10, 2, 0, 1, 1);

        Led_Copy = new QLineEdit(Wi_Copy);
        Led_Copy->setObjectName(QString::fromUtf8("Led_Copy"));

        gridLayout_3->addWidget(Led_Copy, 2, 1, 1, 2);

        periodicCopyScrollArea = new QScrollArea(Wi_Copy);
        periodicCopyScrollArea->setObjectName(QString::fromUtf8("periodicCopyScrollArea"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(periodicCopyScrollArea->sizePolicy().hasHeightForWidth());
        periodicCopyScrollArea->setSizePolicy(sizePolicy4);
        periodicCopyScrollArea->setMinimumSize(QSize(0, 270));
        periodicCopyScrollArea->setFrameShape(QFrame::Shape::NoFrame);
        periodicCopyScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        periodicCopyScrollArea->setWidgetResizable(true);
        periodicCopyContainer = new QWidget();
        periodicCopyContainer->setObjectName(QString::fromUtf8("periodicCopyContainer"));
        periodicCopyContainer->setGeometry(QRect(0, 0, 318, 270));
        periodicCopyGridLayout = new QGridLayout(periodicCopyContainer);
        periodicCopyGridLayout->setObjectName(QString::fromUtf8("periodicCopyGridLayout"));
        periodicCopyScrollArea->setWidget(periodicCopyContainer);

        gridLayout_3->addWidget(periodicCopyScrollArea, 3, 0, 1, 3);

        Btn_ApplyCopy = new QPushButton(Wi_Copy);
        Btn_ApplyCopy->setObjectName(QString::fromUtf8("Btn_ApplyCopy"));

        gridLayout_3->addWidget(Btn_ApplyCopy, 4, 0, 1, 1);

        Btn_ClearCopyCurrentZone = new QPushButton(Wi_Copy);
        Btn_ClearCopyCurrentZone->setObjectName(QString::fromUtf8("Btn_ClearCopyCurrentZone"));

        gridLayout_3->addWidget(Btn_ClearCopyCurrentZone, 4, 1, 1, 1);

        Btn_ClearAllZoneCopy = new QPushButton(Wi_Copy);
        Btn_ClearAllZoneCopy->setObjectName(QString::fromUtf8("Btn_ClearAllZoneCopy"));

        gridLayout_3->addWidget(Btn_ClearAllZoneCopy, 4, 2, 1, 1);


        turboSetLayout->addWidget(Wi_Copy);

        Wi_B2B_2 = new QWidget(Wi_TurboSet);
        Wi_B2B_2->setObjectName(QString::fromUtf8("Wi_B2B_2"));
        sizePolicy.setHeightForWidth(Wi_B2B_2->sizePolicy().hasHeightForWidth());
        Wi_B2B_2->setSizePolicy(sizePolicy);
        Wi_B2B = new QGridLayout(Wi_B2B_2);
        Wi_B2B->setObjectName(QString::fromUtf8("Wi_B2B"));
        Sli_Span = new QSlider(Wi_B2B_2);
        Sli_Span->setObjectName(QString::fromUtf8("Sli_Span"));
        Sli_Span->setOrientation(Qt::Orientation::Horizontal);

        Wi_B2B->addWidget(Sli_Span, 1, 1, 1, 1);

        label_19 = new QLabel(Wi_B2B_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font3);

        Wi_B2B->addWidget(label_19, 1, 0, 1, 1);

        Btn_Apply = new QPushButton(Wi_B2B_2);
        Btn_Apply->setObjectName(QString::fromUtf8("Btn_Apply"));

        Wi_B2B->addWidget(Btn_Apply, 2, 0, 1, 2);

        label_BladeToBlade = new QLabel(Wi_B2B_2);
        label_BladeToBlade->setObjectName(QString::fromUtf8("label_BladeToBlade"));
        label_BladeToBlade->setFont(font);

        Wi_B2B->addWidget(label_BladeToBlade, 0, 0, 1, 2);


        turboSetLayout->addWidget(Wi_B2B_2);


        turboTabLayout->addWidget(Wi_TurboSet);

        wi_expan = new QWidget(tab_turbo);
        wi_expan->setObjectName(QString::fromUtf8("wi_expan"));

        turboTabLayout->addWidget(wi_expan);

        tabWidget_Control->addTab(tab_turbo, QString());
        mainSplitter->addWidget(tabWidget_Control);
        vtkContainer = new QWidget(mainSplitter);
        vtkContainer->setObjectName(QString::fromUtf8("vtkContainer"));
        VTKLayout = new QVBoxLayout(vtkContainer);
        VTKLayout->setSpacing(0);
        VTKLayout->setObjectName(QString::fromUtf8("VTKLayout"));
        VTKLayout->setContentsMargins(0, 0, 0, 0);
        vtkBox = new QVTKOpenGLNativeWidget(vtkContainer);
        vtkBox->setObjectName(QString::fromUtf8("vtkBox"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(vtkBox->sizePolicy().hasHeightForWidth());
        vtkBox->setSizePolicy(sizePolicy5);

        VTKLayout->addWidget(vtkBox);

        mainSplitter->addWidget(vtkContainer);

        horizontalLayout_3->addWidget(mainSplitter);


        horizontalLayout_2->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1666, 27));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        menubar->setFont(font4);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font4);
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuAbout->setFont(font4);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionLoadMesh);
        menuFile->addAction(actionUpdateFlow);
        menuFile->addAction(actionExport_Picture);
        toolBar->addAction(actionNewWindow);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionAddScalarBarActor);
        toolBar->addAction(actionAddAxisActor);
        toolBar->addAction(actionAddOutlineActor);
        toolBar->addAction(actionAddPointInformation);

        retranslateUi(MainWindow);

        tabWidget_Control->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Cipher_Post", nullptr));
        actionOpenFile->setText(QCoreApplication::translate("MainWindow", "OpenFile", nullptr));
#if QT_CONFIG(tooltip)
        actionOpenFile->setToolTip(QCoreApplication::translate("MainWindow", "open aes mesh file", nullptr));
#endif // QT_CONFIG(tooltip)
        actionLoadMesh->setText(QCoreApplication::translate("MainWindow", "&Load Mesh", nullptr));
        actionUpdateFlow->setText(QCoreApplication::translate("MainWindow", "&Update Flow", nullptr));
        actionAddScalarBarActor->setText(QCoreApplication::translate("MainWindow", "AddScalarBarActor", nullptr));
#if QT_CONFIG(tooltip)
        actionAddScalarBarActor->setToolTip(QCoreApplication::translate("MainWindow", "add scalarBar", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddAxisActor->setText(QCoreApplication::translate("MainWindow", "AddAxisActor", nullptr));
#if QT_CONFIG(tooltip)
        actionAddAxisActor->setToolTip(QCoreApplication::translate("MainWindow", "add coordinate axis", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddOutlineActor->setText(QCoreApplication::translate("MainWindow", "AddOutlineActor", nullptr));
#if QT_CONFIG(tooltip)
        actionAddOutlineActor->setToolTip(QCoreApplication::translate("MainWindow", "add outline", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAddPointInformation->setText(QCoreApplication::translate("MainWindow", "Probe Data", nullptr));
#if QT_CONFIG(tooltip)
        actionAddPointInformation->setToolTip(QCoreApplication::translate("MainWindow", "add point attribute information", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCalculatorFunction->setText(QCoreApplication::translate("MainWindow", "CalculatorFunction", nullptr));
#if QT_CONFIG(tooltip)
        actionCalculatorFunction->setToolTip(QCoreApplication::translate("MainWindow", "add new parameter", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNewWindow->setText(QCoreApplication::translate("MainWindow", "NewWindow", nullptr));
#if QT_CONFIG(tooltip)
        actionNewWindow->setToolTip(QCoreApplication::translate("MainWindow", "create a new window", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExport_Picture->setText(QCoreApplication::translate("MainWindow", "Export Picture", nullptr));
        mainSplitter->setStyleSheet(QCoreApplication::translate("MainWindow", "QSplitter::handle {\n"
"    background-color: #d0d0d0;\n"
"    border: 1px solid #a0a0a0;\n"
"}\n"
"QSplitter::handle:hover {\n"
"    background-color: #4a8fc4;\n"
"}\n"
"QSplitter::handle:pressed {\n"
"    background-color: #3d87c2;\n"
"}", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Orientation view", nullptr));
        xoyView->setText(QString());
        xozView->setText(QString());
        yozView->setText(QString());
        xyzView->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Show basic object", nullptr));
        contourCheckBox->setText(QCoreApplication::translate("MainWindow", "Contour", nullptr));
        contourSettingButton->setText(QString());
        meshCheckBox->setText(QCoreApplication::translate("MainWindow", "Mesh", nullptr));
        shadeCheckBox->setText(QCoreApplication::translate("MainWindow", "Shade", nullptr));
        edgeCheckBox->setText(QCoreApplication::translate("MainWindow", "Edge", nullptr));
        selectBoundaryButton->setText(QCoreApplication::translate("MainWindow", "Control Panel", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Show derived object", nullptr));
        IsoSurfaceSettingButton->setText(QString());
        slicesCheckBox->setText(QCoreApplication::translate("MainWindow", "Slices", nullptr));
        isoSurfaceCheckBox->setText(QCoreApplication::translate("MainWindow", "Iso-Surfaces", nullptr));
        addSliceButton->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Adjust Show Effects", nullptr));
        lightingCheckBox->setText(QCoreApplication::translate("MainWindow", "Lighting", nullptr));
        transparancyCheckBox->setText(QCoreApplication::translate("MainWindow", "Transparancy", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Options", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "BackGround", nullptr));
        CBtn_BackGround->setItemText(0, QCoreApplication::translate("MainWindow", "Sky Blue", nullptr));
        CBtn_BackGround->setItemText(1, QCoreApplication::translate("MainWindow", "White", nullptr));

        tabWidget_Control->setTabText(tabWidget_Control->indexOf(tab_normal), QCoreApplication::translate("MainWindow", "General", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "View Control", nullptr));
        Btn_TurboInitial->setText(QCoreApplication::translate("MainWindow", "Initialize", nullptr));
        Check_3Dview->setText(QCoreApplication::translate("MainWindow", "3D View", nullptr));
        Check_Meri->setText(QCoreApplication::translate("MainWindow", "Meridional", nullptr));
        Check_BladeToBlade->setText(QCoreApplication::translate("MainWindow", "Blade-Blade", nullptr));
        Check_ThreeView->setText(QCoreApplication::translate("MainWindow", "Three View", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Graphical Instancing", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Domain", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Num of copies", nullptr));
        Btn_ApplyCopy->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        Btn_ClearCopyCurrentZone->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        Btn_ClearAllZoneCopy->setText(QCoreApplication::translate("MainWindow", "Clear All", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "span", nullptr));
        Btn_Apply->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        label_BladeToBlade->setText(QCoreApplication::translate("MainWindow", "Blade to Blade", nullptr));
        tabWidget_Control->setTabText(tabWidget_Control->indexOf(tab_turbo), QCoreApplication::translate("MainWindow", "Turbo", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "&About", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
