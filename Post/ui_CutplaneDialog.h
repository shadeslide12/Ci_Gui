/********************************************************************************
** Form generated from reading UI file 'CutplaneDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUTPLANEDIALOG_H
#define UI_CUTPLANEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CutplaneDialog
{
public:
    QVBoxLayout *mainLayout;
    QGroupBox *sliceControlGroup;
    QGridLayout *sliceControlLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *Btn_AddNew;
    QCheckBox *checkBox;
    QLabel *label_SLoaction;
    QComboBox *Combo_SLiceLocation;
    QHBoxLayout *sliderLayout;
    QSlider *horizontalSlider;
    QLabel *label_ValueLocation;
    QPushButton *Btn_SetPosition;
    QGroupBox *mappingGroup;
    QHBoxLayout *mappingLayout;
    QLabel *lab_MapVariable;
    QComboBox *Combo_SekectMapVariable;
    QSpacerItem *mappingSpacer;
    QGroupBox *colorMapGroup;
    QVBoxLayout *colorMapLayout;
    QHBoxLayout *colorSchemeLayout;
    QLabel *lab_ContourType;
    QComboBox *Combo_ContourType;
    QHBoxLayout *distributionLayout;
    QLabel *label_3;
    QCheckBox *Check_Banded;
    QCheckBox *Check_Continuous;
    QSpacerItem *distributionSpacer;
    QGroupBox *contoursGroup;
    QGridLayout *contoursLayout;
    QLabel *label_5;
    QLineEdit *LnEdit_Min;
    QLabel *label_6;
    QLineEdit *LnEdit_Max;
    QLabel *label_7;
    QLineEdit *LnEdit_Numbers;
    QSpacerItem *contoursSpacer;
    QSpacerItem *verticalSpacer;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *CutplaneDialog)
    {
        if (CutplaneDialog->objectName().isEmpty())
            CutplaneDialog->setObjectName(QString::fromUtf8("CutplaneDialog"));
        CutplaneDialog->resize(650, 620);
        CutplaneDialog->setMinimumSize(QSize(650, 620));
        CutplaneDialog->setMaximumSize(QSize(800, 700));
        mainLayout = new QVBoxLayout(CutplaneDialog);
        mainLayout->setSpacing(15);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(20, 20, 20, 20);
        sliceControlGroup = new QGroupBox(CutplaneDialog);
        sliceControlGroup->setObjectName(QString::fromUtf8("sliceControlGroup"));
        sliceControlLayout = new QGridLayout(sliceControlGroup);
        sliceControlLayout->setSpacing(10);
        sliceControlLayout->setObjectName(QString::fromUtf8("sliceControlLayout"));
        sliceControlLayout->setContentsMargins(20, -1, 20, -1);
        label = new QLabel(sliceControlGroup);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        sliceControlLayout->addWidget(label, 0, 0, 1, 1);

        comboBox = new QComboBox(sliceControlGroup);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        sliceControlLayout->addWidget(comboBox, 0, 1, 1, 1);

        Btn_AddNew = new QPushButton(sliceControlGroup);
        Btn_AddNew->setObjectName(QString::fromUtf8("Btn_AddNew"));
        Btn_AddNew->setMinimumSize(QSize(120, 0));
        Btn_AddNew->setMaximumSize(QSize(60, 30));

        sliceControlLayout->addWidget(Btn_AddNew, 0, 2, 1, 1);

        checkBox = new QCheckBox(sliceControlGroup);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        sliceControlLayout->addWidget(checkBox, 0, 3, 1, 1);

        label_SLoaction = new QLabel(sliceControlGroup);
        label_SLoaction->setObjectName(QString::fromUtf8("label_SLoaction"));
        label_SLoaction->setFont(font);

        sliceControlLayout->addWidget(label_SLoaction, 1, 0, 1, 1);

        Combo_SLiceLocation = new QComboBox(sliceControlGroup);
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->setObjectName(QString::fromUtf8("Combo_SLiceLocation"));

        sliceControlLayout->addWidget(Combo_SLiceLocation, 1, 1, 1, 2);

        sliderLayout = new QHBoxLayout();
        sliderLayout->setObjectName(QString::fromUtf8("sliderLayout"));
        horizontalSlider = new QSlider(sliceControlGroup);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        sliderLayout->addWidget(horizontalSlider);

        label_ValueLocation = new QLabel(sliceControlGroup);
        label_ValueLocation->setObjectName(QString::fromUtf8("label_ValueLocation"));
        label_ValueLocation->setMinimumSize(QSize(100, 0));

        sliderLayout->addWidget(label_ValueLocation);

        Btn_SetPosition = new QPushButton(sliceControlGroup);
        Btn_SetPosition->setObjectName(QString::fromUtf8("Btn_SetPosition"));

        sliderLayout->addWidget(Btn_SetPosition);


        sliceControlLayout->addLayout(sliderLayout, 2, 0, 1, 4);


        mainLayout->addWidget(sliceControlGroup);

        mappingGroup = new QGroupBox(CutplaneDialog);
        mappingGroup->setObjectName(QString::fromUtf8("mappingGroup"));
        mappingLayout = new QHBoxLayout(mappingGroup);
        mappingLayout->setObjectName(QString::fromUtf8("mappingLayout"));
        mappingLayout->setContentsMargins(20, -1, 20, -1);
        lab_MapVariable = new QLabel(mappingGroup);
        lab_MapVariable->setObjectName(QString::fromUtf8("lab_MapVariable"));
        lab_MapVariable->setFont(font);

        mappingLayout->addWidget(lab_MapVariable);

        Combo_SekectMapVariable = new QComboBox(mappingGroup);
        Combo_SekectMapVariable->setObjectName(QString::fromUtf8("Combo_SekectMapVariable"));
        Combo_SekectMapVariable->setMinimumSize(QSize(200, 0));

        mappingLayout->addWidget(Combo_SekectMapVariable);

        mappingSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mappingLayout->addItem(mappingSpacer);


        mainLayout->addWidget(mappingGroup);

        colorMapGroup = new QGroupBox(CutplaneDialog);
        colorMapGroup->setObjectName(QString::fromUtf8("colorMapGroup"));
        colorMapLayout = new QVBoxLayout(colorMapGroup);
        colorMapLayout->setObjectName(QString::fromUtf8("colorMapLayout"));
        colorMapLayout->setContentsMargins(20, -1, 20, -1);
        colorSchemeLayout = new QHBoxLayout();
        colorSchemeLayout->setObjectName(QString::fromUtf8("colorSchemeLayout"));
        lab_ContourType = new QLabel(colorMapGroup);
        lab_ContourType->setObjectName(QString::fromUtf8("lab_ContourType"));
        lab_ContourType->setFont(font);

        colorSchemeLayout->addWidget(lab_ContourType);

        Combo_ContourType = new QComboBox(colorMapGroup);
        Combo_ContourType->setObjectName(QString::fromUtf8("Combo_ContourType"));
        Combo_ContourType->setMinimumSize(QSize(300, 0));

        colorSchemeLayout->addWidget(Combo_ContourType);


        colorMapLayout->addLayout(colorSchemeLayout);

        distributionLayout = new QHBoxLayout();
        distributionLayout->setObjectName(QString::fromUtf8("distributionLayout"));
        label_3 = new QLabel(colorMapGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        distributionLayout->addWidget(label_3);

        Check_Banded = new QCheckBox(colorMapGroup);
        Check_Banded->setObjectName(QString::fromUtf8("Check_Banded"));
        Check_Banded->setChecked(true);

        distributionLayout->addWidget(Check_Banded);

        Check_Continuous = new QCheckBox(colorMapGroup);
        Check_Continuous->setObjectName(QString::fromUtf8("Check_Continuous"));
        Check_Continuous->setChecked(false);

        distributionLayout->addWidget(Check_Continuous);

        distributionSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        distributionLayout->addItem(distributionSpacer);


        colorMapLayout->addLayout(distributionLayout);


        mainLayout->addWidget(colorMapGroup);

        contoursGroup = new QGroupBox(CutplaneDialog);
        contoursGroup->setObjectName(QString::fromUtf8("contoursGroup"));
        contoursLayout = new QGridLayout(contoursGroup);
        contoursLayout->setSpacing(10);
        contoursLayout->setObjectName(QString::fromUtf8("contoursLayout"));
        contoursLayout->setContentsMargins(20, -1, 20, -1);
        label_5 = new QLabel(contoursGroup);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        contoursLayout->addWidget(label_5, 0, 0, 1, 1);

        LnEdit_Min = new QLineEdit(contoursGroup);
        LnEdit_Min->setObjectName(QString::fromUtf8("LnEdit_Min"));
        LnEdit_Min->setMaximumSize(QSize(120, 16777215));

        contoursLayout->addWidget(LnEdit_Min, 0, 1, 1, 1);

        label_6 = new QLabel(contoursGroup);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        contoursLayout->addWidget(label_6, 0, 2, 1, 1);

        LnEdit_Max = new QLineEdit(contoursGroup);
        LnEdit_Max->setObjectName(QString::fromUtf8("LnEdit_Max"));
        LnEdit_Max->setMaximumSize(QSize(120, 16777215));

        contoursLayout->addWidget(LnEdit_Max, 0, 3, 1, 1);

        label_7 = new QLabel(contoursGroup);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        contoursLayout->addWidget(label_7, 1, 0, 1, 1);

        LnEdit_Numbers = new QLineEdit(contoursGroup);
        LnEdit_Numbers->setObjectName(QString::fromUtf8("LnEdit_Numbers"));
        LnEdit_Numbers->setMaximumSize(QSize(120, 16777215));

        contoursLayout->addWidget(LnEdit_Numbers, 1, 1, 1, 1);

        contoursSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        contoursLayout->addItem(contoursSpacer, 1, 2, 1, 2);


        mainLayout->addWidget(contoursGroup);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mainLayout->addItem(verticalSpacer);

        buttonBox = new QDialogButtonBox(CutplaneDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        mainLayout->addWidget(buttonBox);


        retranslateUi(CutplaneDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CutplaneDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CutplaneDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CutplaneDialog);
    } // setupUi

    void retranslateUi(QDialog *CutplaneDialog)
    {
        CutplaneDialog->setWindowTitle(QCoreApplication::translate("CutplaneDialog", "Slice Details", nullptr));
        CutplaneDialog->setStyleSheet(QCoreApplication::translate("CutplaneDialog", "QDialog {\n"
"    background-color: #f5f5f5;\n"
"}\n"
"QGroupBox {\n"
"    font-weight: bold;\n"
"    border: 2px solid #cccccc;\n"
"    border-radius: 8px;\n"
"    margin-top: 1ex;\n"
"    padding-top: 10px;\n"
"}\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px 0 5px;\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}\n"
"QPushButton {\n"
"    background-color: #5DADE2;\n"
"    border: none;\n"
"    color: white;\n"
"    padding: 8px 16px;\n"
"    border-radius: 4px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498db;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2980b9;\n"
"}\n"
"QComboBox, QLineEdit {\n"
"    border: 1px solid #ddd;\n"
"    border-radius: 4px;\n"
"    padding: 4px;\n"
"    background-color: white;\n"
"}\n"
"QComboBox:focus, QLineEdit:focus {\n"
"    border-color: #2980b9;\n"
"}\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px;\n"
"    background: qli"
                        "neargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"    margin: 2px 0;\n"
"    border-radius: 4px;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -2px 0;\n"
"    border-radius: 9px;\n"
"}", nullptr));
        sliceControlGroup->setTitle(QCoreApplication::translate("CutplaneDialog", "Slice Control", nullptr));
        label->setText(QCoreApplication::translate("CutplaneDialog", "Slice No:", nullptr));
        Btn_AddNew->setText(QCoreApplication::translate("CutplaneDialog", "Extract Slices", nullptr));
        checkBox->setText(QCoreApplication::translate("CutplaneDialog", "Show Primary Slice", nullptr));
        label_SLoaction->setText(QCoreApplication::translate("CutplaneDialog", "Slice Locations:", nullptr));
        Combo_SLiceLocation->setItemText(0, QCoreApplication::translate("CutplaneDialog", "X-Planes", nullptr));
        Combo_SLiceLocation->setItemText(1, QCoreApplication::translate("CutplaneDialog", "Y-Planes", nullptr));
        Combo_SLiceLocation->setItemText(2, QCoreApplication::translate("CutplaneDialog", "Z-Planes", nullptr));

        label_ValueLocation->setText(QCoreApplication::translate("CutplaneDialog", "X: 0.0801", nullptr));
        Btn_SetPosition->setText(QCoreApplication::translate("CutplaneDialog", "Set Position", nullptr));
        mappingGroup->setTitle(QCoreApplication::translate("CutplaneDialog", "Mapping Variable", nullptr));
        lab_MapVariable->setText(QCoreApplication::translate("CutplaneDialog", "Variable:", nullptr));
        colorMapGroup->setTitle(QCoreApplication::translate("CutplaneDialog", "Color Map Options", nullptr));
        lab_ContourType->setText(QCoreApplication::translate("CutplaneDialog", "Color Scheme:", nullptr));
        label_3->setText(QCoreApplication::translate("CutplaneDialog", "Distribution Method:", nullptr));
        Check_Banded->setText(QCoreApplication::translate("CutplaneDialog", "Banded", nullptr));
        Check_Continuous->setText(QCoreApplication::translate("CutplaneDialog", "Continuous", nullptr));
        contoursGroup->setTitle(QCoreApplication::translate("CutplaneDialog", "Contours Level", nullptr));
        label_5->setText(QCoreApplication::translate("CutplaneDialog", "Minimum:", nullptr));
        LnEdit_Min->setInputMask(QString());
        LnEdit_Min->setText(QCoreApplication::translate("CutplaneDialog", "0.0", nullptr));
        label_6->setText(QCoreApplication::translate("CutplaneDialog", "Maximum:", nullptr));
        LnEdit_Max->setText(QCoreApplication::translate("CutplaneDialog", "2.0", nullptr));
        label_7->setText(QCoreApplication::translate("CutplaneDialog", "Numbers:", nullptr));
        LnEdit_Numbers->setText(QCoreApplication::translate("CutplaneDialog", "10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CutplaneDialog: public Ui_CutplaneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTPLANEDIALOG_H
