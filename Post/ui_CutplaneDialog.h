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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CutplaneDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label_2;
    QComboBox *Combo_ContourType;
    QLabel *label_3;
    QCheckBox *Check_Banded;
    QCheckBox *Check_Continuous;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *LnEdit_Min;
    QLineEdit *LnEdit_Max;
    QLineEdit *LnEdit_Numbers;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_SLoaction;
    QComboBox *comboBox;
    QLabel *label;
    QLabel *label_ValueLocation;
    QComboBox *Combo_SLiceLocation;
    QCheckBox *checkBox;
    QSlider *horizontalSlider;
    QPushButton *Btn_ExtractSlice;
    QPushButton *Btn_AddNew;

    void setupUi(QDialog *CutplaneDialog)
    {
        if (CutplaneDialog->objectName().isEmpty())
            CutplaneDialog->setObjectName(QString::fromUtf8("CutplaneDialog"));
        CutplaneDialog->resize(617, 582);
        CutplaneDialog->setMinimumSize(QSize(0, 0));
        CutplaneDialog->setMaximumSize(QSize(16777215, 16777215));
        buttonBox = new QDialogButtonBox(CutplaneDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(440, 530, 166, 24));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label_2 = new QLabel(CutplaneDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 260, 151, 16));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        Combo_ContourType = new QComboBox(CutplaneDialog);
        Combo_ContourType->setObjectName(QString::fromUtf8("Combo_ContourType"));
        Combo_ContourType->setGeometry(QRect(20, 300, 541, 23));
        label_3 = new QLabel(CutplaneDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 340, 251, 16));
        QFont font1;
        font1.setPointSize(9);
        label_3->setFont(font1);
        Check_Banded = new QCheckBox(CutplaneDialog);
        Check_Banded->setObjectName(QString::fromUtf8("Check_Banded"));
        Check_Banded->setGeometry(QRect(280, 340, 85, 21));
        Check_Continuous = new QCheckBox(CutplaneDialog);
        Check_Continuous->setObjectName(QString::fromUtf8("Check_Continuous"));
        Check_Continuous->setGeometry(QRect(420, 340, 111, 21));
        label_4 = new QLabel(CutplaneDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 390, 151, 16));
        label_4->setFont(font);
        label_5 = new QLabel(CutplaneDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 430, 57, 15));
        label_6 = new QLabel(CutplaneDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(260, 430, 57, 15));
        label_7 = new QLabel(CutplaneDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 480, 71, 16));
        LnEdit_Min = new QLineEdit(CutplaneDialog);
        LnEdit_Min->setObjectName(QString::fromUtf8("LnEdit_Min"));
        LnEdit_Min->setGeometry(QRect(100, 430, 113, 23));
        LnEdit_Max = new QLineEdit(CutplaneDialog);
        LnEdit_Max->setObjectName(QString::fromUtf8("LnEdit_Max"));
        LnEdit_Max->setGeometry(QRect(330, 430, 113, 23));
        LnEdit_Numbers = new QLineEdit(CutplaneDialog);
        LnEdit_Numbers->setObjectName(QString::fromUtf8("LnEdit_Numbers"));
        LnEdit_Numbers->setGeometry(QRect(100, 470, 113, 23));
        widget = new QWidget(CutplaneDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 58, 601, 161));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_SLoaction = new QLabel(widget);
        label_SLoaction->setObjectName(QString::fromUtf8("label_SLoaction"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setWeight(50);
        label_SLoaction->setFont(font2);

        gridLayout->addWidget(label_SLoaction, 1, 0, 1, 1);

        comboBox = new QComboBox(widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(70, 25));
        label->setMaximumSize(QSize(70, 25));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_ValueLocation = new QLabel(widget);
        label_ValueLocation->setObjectName(QString::fromUtf8("label_ValueLocation"));

        gridLayout->addWidget(label_ValueLocation, 2, 2, 1, 1);

        Combo_SLiceLocation = new QComboBox(widget);
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->setObjectName(QString::fromUtf8("Combo_SLiceLocation"));

        gridLayout->addWidget(Combo_SLiceLocation, 1, 1, 1, 1);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 1, 3, 1, 1);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 2, 1, 1, 1);

        Btn_ExtractSlice = new QPushButton(widget);
        Btn_ExtractSlice->setObjectName(QString::fromUtf8("Btn_ExtractSlice"));

        gridLayout->addWidget(Btn_ExtractSlice, 2, 3, 1, 1);

        Btn_AddNew = new QPushButton(widget);
        Btn_AddNew->setObjectName(QString::fromUtf8("Btn_AddNew"));
        Btn_AddNew->setMinimumSize(QSize(40, 25));
        Btn_AddNew->setMaximumSize(QSize(40, 25));
        Btn_AddNew->setFont(font);

        gridLayout->addWidget(Btn_AddNew, 0, 2, 1, 1);


        retranslateUi(CutplaneDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CutplaneDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CutplaneDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CutplaneDialog);
    } // setupUi

    void retranslateUi(QDialog *CutplaneDialog)
    {
        CutplaneDialog->setWindowTitle(QCoreApplication::translate("CutplaneDialog", "Slice Details", nullptr));
        label_2->setText(QCoreApplication::translate("CutplaneDialog", "Color Map Option :", nullptr));
        label_3->setText(QCoreApplication::translate("CutplaneDialog", "Color Map Distribution Method :", nullptr));
        Check_Banded->setText(QCoreApplication::translate("CutplaneDialog", "Banded", nullptr));
        Check_Continuous->setText(QCoreApplication::translate("CutplaneDialog", "Continuous", nullptr));
        label_4->setText(QCoreApplication::translate("CutplaneDialog", "Contours Level :", nullptr));
        label_5->setText(QCoreApplication::translate("CutplaneDialog", "Minium :", nullptr));
        label_6->setText(QCoreApplication::translate("CutplaneDialog", "Maxium :", nullptr));
        label_7->setText(QCoreApplication::translate("CutplaneDialog", "Numbers :", nullptr));
        label_SLoaction->setText(QCoreApplication::translate("CutplaneDialog", "Slice Locations", nullptr));
        label->setText(QCoreApplication::translate("CutplaneDialog", "Slice No:", nullptr));
        label_ValueLocation->setText(QCoreApplication::translate("CutplaneDialog", "Value : 0.0000", nullptr));
        Combo_SLiceLocation->setItemText(0, QCoreApplication::translate("CutplaneDialog", "X-Planes", nullptr));
        Combo_SLiceLocation->setItemText(1, QCoreApplication::translate("CutplaneDialog", "Y-Planes", nullptr));
        Combo_SLiceLocation->setItemText(2, QCoreApplication::translate("CutplaneDialog", "Z-Planes", nullptr));

        checkBox->setText(QCoreApplication::translate("CutplaneDialog", "Show Primary Slice", nullptr));
        Btn_ExtractSlice->setText(QCoreApplication::translate("CutplaneDialog", "Extract Slices", nullptr));
        Btn_AddNew->setText(QCoreApplication::translate("CutplaneDialog", "new", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CutplaneDialog: public Ui_CutplaneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTPLANEDIALOG_H
