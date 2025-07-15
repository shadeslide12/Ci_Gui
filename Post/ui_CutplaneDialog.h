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

QT_BEGIN_NAMESPACE

class Ui_CutplaneDialog
{
public:
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_Noraml_z;
    QLabel *label_Origin_z;
    QLabel *label;
    QLineEdit *lineEdit_Origin_x;
    QLabel *label_Noraml_x;
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLineEdit *lineEdit_Noraml_x;
    QPushButton *pushButton;
    QLabel *label_Noraml_y;
    QLabel *label_Noraml_z;
    QLineEdit *lineEdit_Origin_y;
    QLabel *label_Origin_x;
    QLineEdit *lineEdit_Noraml_y;
    QLineEdit *lineEdit_Origin_z;
    QLabel *label_Origin_y;
    QLabel *label_SLoaction;
    QComboBox *Combo_SLiceLocation;
    QSlider *horizontalSlider;
    QPushButton *Btn_ExtractSlice;
    QLabel *label_ValueLocation;
    QCheckBox *checkBox;

    void setupUi(QDialog *CutplaneDialog)
    {
        if (CutplaneDialog->objectName().isEmpty())
            CutplaneDialog->setObjectName(QString::fromUtf8("CutplaneDialog"));
        CutplaneDialog->resize(623, 367);
        CutplaneDialog->setMinimumSize(QSize(0, 0));
        CutplaneDialog->setMaximumSize(QSize(16777215, 16777215));
        gridLayout = new QGridLayout(CutplaneDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_Noraml_z = new QLineEdit(CutplaneDialog);
        lineEdit_Noraml_z->setObjectName(QString::fromUtf8("lineEdit_Noraml_z"));
        lineEdit_Noraml_z->setMinimumSize(QSize(150, 25));
        lineEdit_Noraml_z->setMaximumSize(QSize(150, 25));
        QFont font;
        font.setPointSize(11);
        lineEdit_Noraml_z->setFont(font);

        gridLayout->addWidget(lineEdit_Noraml_z, 5, 3, 1, 1);

        label_Origin_z = new QLabel(CutplaneDialog);
        label_Origin_z->setObjectName(QString::fromUtf8("label_Origin_z"));
        label_Origin_z->setMinimumSize(QSize(70, 25));
        label_Origin_z->setMaximumSize(QSize(70, 25));
        label_Origin_z->setFont(font);

        gridLayout->addWidget(label_Origin_z, 5, 0, 1, 1);

        label = new QLabel(CutplaneDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(70, 25));
        label->setMaximumSize(QSize(70, 25));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_Origin_x = new QLineEdit(CutplaneDialog);
        lineEdit_Origin_x->setObjectName(QString::fromUtf8("lineEdit_Origin_x"));
        lineEdit_Origin_x->setMinimumSize(QSize(150, 25));
        lineEdit_Origin_x->setMaximumSize(QSize(150, 25));
        lineEdit_Origin_x->setFont(font);

        gridLayout->addWidget(lineEdit_Origin_x, 3, 1, 1, 1);

        label_Noraml_x = new QLabel(CutplaneDialog);
        label_Noraml_x->setObjectName(QString::fromUtf8("label_Noraml_x"));
        label_Noraml_x->setMinimumSize(QSize(70, 25));
        label_Noraml_x->setMaximumSize(QSize(70, 25));
        label_Noraml_x->setFont(font);

        gridLayout->addWidget(label_Noraml_x, 3, 2, 1, 1);

        buttonBox = new QDialogButtonBox(CutplaneDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 6, 0, 1, 4);

        comboBox = new QComboBox(CutplaneDialog);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setFont(font);

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        lineEdit_Noraml_x = new QLineEdit(CutplaneDialog);
        lineEdit_Noraml_x->setObjectName(QString::fromUtf8("lineEdit_Noraml_x"));
        lineEdit_Noraml_x->setMinimumSize(QSize(150, 25));
        lineEdit_Noraml_x->setMaximumSize(QSize(150, 25));
        lineEdit_Noraml_x->setFont(font);

        gridLayout->addWidget(lineEdit_Noraml_x, 3, 3, 1, 1);

        pushButton = new QPushButton(CutplaneDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(40, 25));
        pushButton->setMaximumSize(QSize(40, 25));
        pushButton->setFont(font);

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);

        label_Noraml_y = new QLabel(CutplaneDialog);
        label_Noraml_y->setObjectName(QString::fromUtf8("label_Noraml_y"));
        label_Noraml_y->setMinimumSize(QSize(70, 25));
        label_Noraml_y->setMaximumSize(QSize(70, 25));
        label_Noraml_y->setFont(font);

        gridLayout->addWidget(label_Noraml_y, 4, 2, 1, 1);

        label_Noraml_z = new QLabel(CutplaneDialog);
        label_Noraml_z->setObjectName(QString::fromUtf8("label_Noraml_z"));
        label_Noraml_z->setMinimumSize(QSize(70, 25));
        label_Noraml_z->setMaximumSize(QSize(70, 25));
        label_Noraml_z->setFont(font);

        gridLayout->addWidget(label_Noraml_z, 5, 2, 1, 1);

        lineEdit_Origin_y = new QLineEdit(CutplaneDialog);
        lineEdit_Origin_y->setObjectName(QString::fromUtf8("lineEdit_Origin_y"));
        lineEdit_Origin_y->setMinimumSize(QSize(150, 25));
        lineEdit_Origin_y->setMaximumSize(QSize(150, 25));
        lineEdit_Origin_y->setFont(font);

        gridLayout->addWidget(lineEdit_Origin_y, 4, 1, 1, 1);

        label_Origin_x = new QLabel(CutplaneDialog);
        label_Origin_x->setObjectName(QString::fromUtf8("label_Origin_x"));
        label_Origin_x->setMinimumSize(QSize(70, 25));
        label_Origin_x->setMaximumSize(QSize(70, 25));
        label_Origin_x->setFont(font);

        gridLayout->addWidget(label_Origin_x, 3, 0, 1, 1);

        lineEdit_Noraml_y = new QLineEdit(CutplaneDialog);
        lineEdit_Noraml_y->setObjectName(QString::fromUtf8("lineEdit_Noraml_y"));
        lineEdit_Noraml_y->setMinimumSize(QSize(150, 25));
        lineEdit_Noraml_y->setMaximumSize(QSize(150, 25));
        lineEdit_Noraml_y->setFont(font);

        gridLayout->addWidget(lineEdit_Noraml_y, 4, 3, 1, 1);

        lineEdit_Origin_z = new QLineEdit(CutplaneDialog);
        lineEdit_Origin_z->setObjectName(QString::fromUtf8("lineEdit_Origin_z"));
        lineEdit_Origin_z->setMinimumSize(QSize(150, 25));
        lineEdit_Origin_z->setMaximumSize(QSize(150, 25));
        lineEdit_Origin_z->setFont(font);

        gridLayout->addWidget(lineEdit_Origin_z, 5, 1, 1, 1);

        label_Origin_y = new QLabel(CutplaneDialog);
        label_Origin_y->setObjectName(QString::fromUtf8("label_Origin_y"));
        label_Origin_y->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_Origin_y->sizePolicy().hasHeightForWidth());
        label_Origin_y->setSizePolicy(sizePolicy);
        label_Origin_y->setMinimumSize(QSize(70, 25));
        label_Origin_y->setMaximumSize(QSize(70, 25));
        label_Origin_y->setFont(font);

        gridLayout->addWidget(label_Origin_y, 4, 0, 1, 1);

        label_SLoaction = new QLabel(CutplaneDialog);
        label_SLoaction->setObjectName(QString::fromUtf8("label_SLoaction"));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        label_SLoaction->setFont(font1);

        gridLayout->addWidget(label_SLoaction, 1, 0, 1, 1);

        Combo_SLiceLocation = new QComboBox(CutplaneDialog);
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->addItem(QString());
        Combo_SLiceLocation->setObjectName(QString::fromUtf8("Combo_SLiceLocation"));

        gridLayout->addWidget(Combo_SLiceLocation, 1, 1, 1, 1);

        horizontalSlider = new QSlider(CutplaneDialog);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 2, 1, 1, 1);

        Btn_ExtractSlice = new QPushButton(CutplaneDialog);
        Btn_ExtractSlice->setObjectName(QString::fromUtf8("Btn_ExtractSlice"));

        gridLayout->addWidget(Btn_ExtractSlice, 2, 3, 1, 1);

        label_ValueLocation = new QLabel(CutplaneDialog);
        label_ValueLocation->setObjectName(QString::fromUtf8("label_ValueLocation"));

        gridLayout->addWidget(label_ValueLocation, 2, 2, 1, 1);

        checkBox = new QCheckBox(CutplaneDialog);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        gridLayout->addWidget(checkBox, 1, 3, 1, 1);


        retranslateUi(CutplaneDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CutplaneDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CutplaneDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CutplaneDialog);
    } // setupUi

    void retranslateUi(QDialog *CutplaneDialog)
    {
        CutplaneDialog->setWindowTitle(QCoreApplication::translate("CutplaneDialog", "CutplaneDialog", nullptr));
        lineEdit_Noraml_z->setText(QCoreApplication::translate("CutplaneDialog", "0", nullptr));
        label_Origin_z->setText(QCoreApplication::translate("CutplaneDialog", "Origin_z", nullptr));
        label->setText(QCoreApplication::translate("CutplaneDialog", "Cutplane", nullptr));
        lineEdit_Origin_x->setText(QCoreApplication::translate("CutplaneDialog", "0", nullptr));
        label_Noraml_x->setText(QCoreApplication::translate("CutplaneDialog", "Noraml_x", nullptr));
        lineEdit_Noraml_x->setText(QCoreApplication::translate("CutplaneDialog", "1", nullptr));
        pushButton->setText(QCoreApplication::translate("CutplaneDialog", "new", nullptr));
        label_Noraml_y->setText(QCoreApplication::translate("CutplaneDialog", "Noraml_y", nullptr));
        label_Noraml_z->setText(QCoreApplication::translate("CutplaneDialog", "Noraml_z", nullptr));
        lineEdit_Origin_y->setText(QCoreApplication::translate("CutplaneDialog", "0", nullptr));
        label_Origin_x->setText(QCoreApplication::translate("CutplaneDialog", "Origin_x", nullptr));
        lineEdit_Noraml_y->setText(QCoreApplication::translate("CutplaneDialog", "0", nullptr));
        lineEdit_Origin_z->setText(QCoreApplication::translate("CutplaneDialog", "0", nullptr));
        label_Origin_y->setText(QCoreApplication::translate("CutplaneDialog", "Origin_y", nullptr));
        label_SLoaction->setText(QCoreApplication::translate("CutplaneDialog", "Slice Locations", nullptr));
        Combo_SLiceLocation->setItemText(0, QCoreApplication::translate("CutplaneDialog", "X-Planes", nullptr));
        Combo_SLiceLocation->setItemText(1, QCoreApplication::translate("CutplaneDialog", "Y-Planes", nullptr));
        Combo_SLiceLocation->setItemText(2, QCoreApplication::translate("CutplaneDialog", "Z-Planes", nullptr));

        Btn_ExtractSlice->setText(QCoreApplication::translate("CutplaneDialog", "Extract Slices", nullptr));
        label_ValueLocation->setText(QCoreApplication::translate("CutplaneDialog", "Value : 0.0000", nullptr));
        checkBox->setText(QCoreApplication::translate("CutplaneDialog", "Show Primary Slice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CutplaneDialog: public Ui_CutplaneDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUTPLANEDIALOG_H
