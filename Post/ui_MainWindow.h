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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
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
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
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
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *edgeCheckBox;
    QCheckBox *meshCheckBox;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *shadeCheckBox;
    QSpacerItem *horizontalSpacer_6;
    QCheckBox *vectorCheckBox;
    QPushButton *contourSettingButton;
    QPushButton *vectorSettingButton;
    QPushButton *selectBoundaryButton;
    QLabel *label_4;
    QWidget *widget_3;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QCheckBox *slicesCheckBox;
    QCheckBox *isoSurfaceCheckBox;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QCheckBox *streamlineCheckBox;
    QPushButton *IsoSurfaceSettingButton;
    QPushButton *addSliceButton;
    QPushButton *addStreamLineButton;
    QLabel *label_6;
    QWidget *widget_5;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_16;
    QCheckBox *lightingCheckBox;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *lightingButton;
    QPushButton *transparantButton;
    QCheckBox *transparancyCheckBox;
    QLabel *label_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_9;
    QCheckBox *MeridionalcheckBox;
    QPushButton *MeridionalButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_10;
    QCheckBox *ConstHeightCheckBox;
    QPushButton *ConstHeightpushButton;
    QLabel *label_3;
    QCheckBox *Check_3Dview;
    QCheckBox *Check_Meri;
    QCheckBox *Check_DoubleView;
    QVBoxLayout *VTKLayout;
    QVTKOpenGLNativeWidget *vtkBox;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTools;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1666, 1000);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
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
        actionNewWindow = new QAction(MainWindow);
        actionNewWindow->setObjectName(QString::fromUtf8("actionNewWindow"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        scrollArea = new QScrollArea(widget_2);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(240, 0));
        scrollArea->setMaximumSize(QSize(240, 16777215));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 238, 882));
        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(9, 9, 141, 18));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setFont(font);
        widget_4 = new QWidget(scrollAreaWidgetContents_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(9, 33, 194, 71));
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

        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(9, 110, 153, 18));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font);
        label->setContextMenuPolicy(Qt::PreventContextMenu);
        widget = new QWidget(scrollAreaWidgetContents_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 134, 210, 162));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 3, 0, 1, 1);

        contourCheckBox = new QCheckBox(widget);
        contourCheckBox->setObjectName(QString::fromUtf8("contourCheckBox"));
        contourCheckBox->setMinimumSize(QSize(150, 0));
        contourCheckBox->setFont(font);
        contourCheckBox->setChecked(true);

        gridLayout_2->addWidget(contourCheckBox, 3, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        edgeCheckBox = new QCheckBox(widget);
        edgeCheckBox->setObjectName(QString::fromUtf8("edgeCheckBox"));
        edgeCheckBox->setFont(font);

        gridLayout_2->addWidget(edgeCheckBox, 5, 1, 1, 1);

        meshCheckBox = new QCheckBox(widget);
        meshCheckBox->setObjectName(QString::fromUtf8("meshCheckBox"));
        meshCheckBox->setFont(font);

        gridLayout_2->addWidget(meshCheckBox, 2, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 5, 0, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 6, 0, 1, 1);

        shadeCheckBox = new QCheckBox(widget);
        shadeCheckBox->setObjectName(QString::fromUtf8("shadeCheckBox"));
        shadeCheckBox->setFont(font);
        shadeCheckBox->setChecked(true);

        gridLayout_2->addWidget(shadeCheckBox, 4, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 4, 0, 1, 1);

        vectorCheckBox = new QCheckBox(widget);
        vectorCheckBox->setObjectName(QString::fromUtf8("vectorCheckBox"));
        vectorCheckBox->setFont(font);

        gridLayout_2->addWidget(vectorCheckBox, 6, 1, 1, 1);

        contourSettingButton = new QPushButton(widget);
        contourSettingButton->setObjectName(QString::fromUtf8("contourSettingButton"));
        contourSettingButton->setMinimumSize(QSize(20, 20));
        contourSettingButton->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(contourSettingButton, 3, 2, 1, 1);

        vectorSettingButton = new QPushButton(widget);
        vectorSettingButton->setObjectName(QString::fromUtf8("vectorSettingButton"));
        vectorSettingButton->setMinimumSize(QSize(20, 20));
        vectorSettingButton->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(vectorSettingButton, 6, 2, 1, 1);

        selectBoundaryButton = new QPushButton(scrollAreaWidgetContents_2);
        selectBoundaryButton->setObjectName(QString::fromUtf8("selectBoundaryButton"));
        selectBoundaryButton->setGeometry(QRect(9, 302, 121, 26));
        selectBoundaryButton->setFont(font);
        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(9, 350, 173, 18));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setFont(font);
        widget_3 = new QWidget(scrollAreaWidgetContents_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(9, 374, 220, 102));
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        widget_3->setMinimumSize(QSize(220, 0));
        widget_3->setMaximumSize(QSize(220, 16777215));
        gridLayout = new QGridLayout(widget_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

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
        isoSurfaceCheckBox->setMinimumSize(QSize(186, 1));
        isoSurfaceCheckBox->setMaximumSize(QSize(16777215, 16777215));
        isoSurfaceCheckBox->setFont(font);
        isoSurfaceCheckBox->setIconSize(QSize(16, 16));
        isoSurfaceCheckBox->setChecked(false);
        isoSurfaceCheckBox->setAutoExclusive(false);

        gridLayout->addWidget(isoSurfaceCheckBox, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        streamlineCheckBox = new QCheckBox(widget_3);
        streamlineCheckBox->setObjectName(QString::fromUtf8("streamlineCheckBox"));
        streamlineCheckBox->setMinimumSize(QSize(186, 0));
        streamlineCheckBox->setFont(font);

        gridLayout->addWidget(streamlineCheckBox, 3, 1, 1, 1);

        IsoSurfaceSettingButton = new QPushButton(widget_3);
        IsoSurfaceSettingButton->setObjectName(QString::fromUtf8("IsoSurfaceSettingButton"));
        IsoSurfaceSettingButton->setMinimumSize(QSize(20, 20));
        IsoSurfaceSettingButton->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(IsoSurfaceSettingButton, 1, 2, 1, 1);

        addSliceButton = new QPushButton(widget_3);
        addSliceButton->setObjectName(QString::fromUtf8("addSliceButton"));
        addSliceButton->setMinimumSize(QSize(20, 20));
        addSliceButton->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(addSliceButton, 2, 2, 1, 1);

        addStreamLineButton = new QPushButton(widget_3);
        addStreamLineButton->setObjectName(QString::fromUtf8("addStreamLineButton"));
        addStreamLineButton->setMinimumSize(QSize(20, 20));
        addStreamLineButton->setMaximumSize(QSize(20, 20));

        gridLayout->addWidget(addStreamLineButton, 3, 2, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(9, 482, 168, 18));
        sizePolicy2.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy2);
        label_6->setFont(font);
        widget_5 = new QWidget(scrollAreaWidgetContents_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(9, 506, 220, 72));
        sizePolicy3.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy3);
        widget_5->setMinimumSize(QSize(220, 0));
        widget_5->setMaximumSize(QSize(220, 16777215));
        gridLayout_4 = new QGridLayout(widget_5);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_16 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_16, 1, 0, 1, 1);

        lightingCheckBox = new QCheckBox(widget_5);
        lightingCheckBox->setObjectName(QString::fromUtf8("lightingCheckBox"));
        lightingCheckBox->setMinimumSize(QSize(186, 0));
        lightingCheckBox->setFont(font);

        gridLayout_4->addWidget(lightingCheckBox, 2, 1, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 2, 0, 1, 1);

        lightingButton = new QPushButton(widget_5);
        lightingButton->setObjectName(QString::fromUtf8("lightingButton"));
        lightingButton->setMinimumSize(QSize(20, 20));
        lightingButton->setMaximumSize(QSize(20, 20));

        gridLayout_4->addWidget(lightingButton, 2, 2, 1, 1);

        transparantButton = new QPushButton(widget_5);
        transparantButton->setObjectName(QString::fromUtf8("transparantButton"));
        transparantButton->setMinimumSize(QSize(20, 20));
        transparantButton->setMaximumSize(QSize(20, 20));

        gridLayout_4->addWidget(transparantButton, 1, 2, 1, 1);

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

        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(9, 584, 96, 18));
        layoutWidget = new QWidget(scrollAreaWidgetContents_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 610, 212, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        MeridionalcheckBox = new QCheckBox(layoutWidget);
        MeridionalcheckBox->setObjectName(QString::fromUtf8("MeridionalcheckBox"));

        horizontalLayout_4->addWidget(MeridionalcheckBox);

        MeridionalButton = new QPushButton(layoutWidget);
        MeridionalButton->setObjectName(QString::fromUtf8("MeridionalButton"));
        MeridionalButton->setMinimumSize(QSize(20, 20));
        MeridionalButton->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(MeridionalButton);

        layoutWidget1 = new QWidget(scrollAreaWidgetContents_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 640, 211, 26));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        ConstHeightCheckBox = new QCheckBox(layoutWidget1);
        ConstHeightCheckBox->setObjectName(QString::fromUtf8("ConstHeightCheckBox"));

        horizontalLayout_5->addWidget(ConstHeightCheckBox);

        ConstHeightpushButton = new QPushButton(layoutWidget1);
        ConstHeightpushButton->setObjectName(QString::fromUtf8("ConstHeightpushButton"));
        ConstHeightpushButton->setMinimumSize(QSize(20, 20));
        ConstHeightpushButton->setMaximumSize(QSize(20, 20));

        horizontalLayout_5->addWidget(ConstHeightpushButton);

        label_3 = new QLabel(scrollAreaWidgetContents_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 680, 121, 16));
        Check_3Dview = new QCheckBox(scrollAreaWidgetContents_2);
        Check_3Dview->setObjectName(QString::fromUtf8("Check_3Dview"));
        Check_3Dview->setGeometry(QRect(10, 710, 85, 21));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        Check_3Dview->setFont(font1);
        Check_3Dview->setChecked(true);
        Check_Meri = new QCheckBox(scrollAreaWidgetContents_2);
        Check_Meri->setObjectName(QString::fromUtf8("Check_Meri"));
        Check_Meri->setGeometry(QRect(130, 710, 101, 21));
        Check_Meri->setFont(font1);
        Check_DoubleView = new QCheckBox(scrollAreaWidgetContents_2);
        Check_DoubleView->setObjectName(QString::fromUtf8("Check_DoubleView"));
        Check_DoubleView->setGeometry(QRect(10, 740, 121, 21));
        Check_DoubleView->setFont(font1);
        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_3->addWidget(scrollArea);

        VTKLayout = new QVBoxLayout();
        VTKLayout->setObjectName(QString::fromUtf8("VTKLayout"));
        vtkBox = new QVTKOpenGLNativeWidget(widget_2);
        vtkBox->setObjectName(QString::fromUtf8("vtkBox"));

        VTKLayout->addWidget(vtkBox);


        horizontalLayout_3->addLayout(VTKLayout);


        horizontalLayout_2->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1666, 24));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        menubar->setFont(font2);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFile->setFont(font2);
        menuTools = new QMenu(menubar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuTools->setFont(font2);
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTools->menuAction());
        menuFile->addAction(actionLoadMesh);
        menuFile->addAction(actionUpdateFlow);
        toolBar->addAction(actionNewWindow);
        toolBar->addAction(actionOpenFile);
        toolBar->addAction(actionAddScalarBarActor);
        toolBar->addAction(actionAddAxisActor);
        toolBar->addAction(actionAddOutlineActor);
        toolBar->addAction(actionAddPointInformation);
        toolBar->addAction(actionCalculatorFunction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "CFD Post-processing Tool", nullptr));
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
        actionAddPointInformation->setText(QCoreApplication::translate("MainWindow", "AddPointInformation", nullptr));
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
        label_5->setText(QCoreApplication::translate("MainWindow", "Orientation view", nullptr));
        xoyView->setText(QString());
        xozView->setText(QString());
        yozView->setText(QString());
        xyzView->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Show basic object", nullptr));
        contourCheckBox->setText(QCoreApplication::translate("MainWindow", "Contour", nullptr));
        edgeCheckBox->setText(QCoreApplication::translate("MainWindow", "Edge", nullptr));
        meshCheckBox->setText(QCoreApplication::translate("MainWindow", "Mesh", nullptr));
        shadeCheckBox->setText(QCoreApplication::translate("MainWindow", "Shade", nullptr));
        vectorCheckBox->setText(QCoreApplication::translate("MainWindow", "Vector", nullptr));
        contourSettingButton->setText(QString());
        vectorSettingButton->setText(QString());
        selectBoundaryButton->setText(QCoreApplication::translate("MainWindow", "Select Actor..", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Show derived object", nullptr));
        slicesCheckBox->setText(QCoreApplication::translate("MainWindow", "Slices", nullptr));
        isoSurfaceCheckBox->setText(QCoreApplication::translate("MainWindow", "Iso-Surfaces", nullptr));
        streamlineCheckBox->setText(QCoreApplication::translate("MainWindow", "Streamtraces", nullptr));
        IsoSurfaceSettingButton->setText(QString());
        addSliceButton->setText(QString());
        addStreamLineButton->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Adjust Show Effects", nullptr));
        lightingCheckBox->setText(QCoreApplication::translate("MainWindow", "Lighting", nullptr));
        lightingButton->setText(QString());
        transparantButton->setText(QString());
        transparancyCheckBox->setText(QCoreApplication::translate("MainWindow", "Transparancy", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Specialized", nullptr));
        MeridionalcheckBox->setText(QCoreApplication::translate("MainWindow", "Meridional Plane", nullptr));
        MeridionalButton->setText(QString());
        ConstHeightCheckBox->setText(QCoreApplication::translate("MainWindow", "Const Height", nullptr));
        ConstHeightpushButton->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWindow", "View Control", nullptr));
        Check_3Dview->setText(QCoreApplication::translate("MainWindow", "3D View", nullptr));
        Check_Meri->setText(QCoreApplication::translate("MainWindow", "Meridional", nullptr));
        Check_DoubleView->setText(QCoreApplication::translate("MainWindow", "Double View", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "&File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "&Tools", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
