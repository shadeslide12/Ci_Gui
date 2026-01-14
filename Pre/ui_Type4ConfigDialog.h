/********************************************************************************
** Form generated from reading UI file 'Type4ConfigDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TYPE4CONFIGDIALOG_H
#define UI_TYPE4CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Type4ConfigDialog
{
public:
    QVBoxLayout *mainLayout;
    QGroupBox *infoGroupBox;
    QGridLayout *infoGridLayout;
    QLabel *fileNameLabel;
    QLabel *fileNameValue;
    QLabel *stageInletLabel;
    QLabel *stageInletValue;
    QLabel *stageExitLabel;
    QLabel *stageExitValue;
    QGroupBox *selectionGroupBox;
    QGridLayout *selectionGridLayout;
    QLabel *secondaryInletsLabel;
    QLabel *secondaryExitsLabel;
    QLabel *filmcoolingLabel;
    QLabel *torqueWallsLabel;
    QLabel *mixingPlanesLabel;
    QListWidget *secondaryInletsList;
    QListWidget *secondaryExitsList;
    QListWidget *filmcoolingList;
    QListWidget *torqueWallsList;
    QListWidget *mixingPlanesList;
    QLabel *secondaryInletsCount;
    QLabel *secondaryExitsCount;
    QLabel *filmcoolingCount;
    QLabel *torqueWallsCount;
    QLabel *mixingPlanesCount;
    QPushButton *clearSecondaryInletsBtn;
    QPushButton *clearSecondaryExitsBtn;
    QPushButton *clearFilmcoolingBtn;
    QPushButton *clearTorqueWallsBtn;
    QPushButton *clearMixingPlanesBtn;
    QHBoxLayout *buttonLayout;
    QSpacerItem *buttonSpacer;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *Type4ConfigDialog)
    {
        if (Type4ConfigDialog->objectName().isEmpty())
            Type4ConfigDialog->setObjectName(QString::fromUtf8("Type4ConfigDialog"));
        Type4ConfigDialog->resize(700, 550);
        Type4ConfigDialog->setModal(true);
        mainLayout = new QVBoxLayout(Type4ConfigDialog);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        infoGroupBox = new QGroupBox(Type4ConfigDialog);
        infoGroupBox->setObjectName(QString::fromUtf8("infoGroupBox"));
        infoGridLayout = new QGridLayout(infoGroupBox);
        infoGridLayout->setObjectName(QString::fromUtf8("infoGridLayout"));
        fileNameLabel = new QLabel(infoGroupBox);
        fileNameLabel->setObjectName(QString::fromUtf8("fileNameLabel"));

        infoGridLayout->addWidget(fileNameLabel, 0, 0, 1, 1);

        fileNameValue = new QLabel(infoGroupBox);
        fileNameValue->setObjectName(QString::fromUtf8("fileNameValue"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        fileNameValue->setFont(font);

        infoGridLayout->addWidget(fileNameValue, 0, 1, 1, 1);

        stageInletLabel = new QLabel(infoGroupBox);
        stageInletLabel->setObjectName(QString::fromUtf8("stageInletLabel"));

        infoGridLayout->addWidget(stageInletLabel, 0, 2, 1, 1);

        stageInletValue = new QLabel(infoGroupBox);
        stageInletValue->setObjectName(QString::fromUtf8("stageInletValue"));
        stageInletValue->setFont(font);

        infoGridLayout->addWidget(stageInletValue, 0, 3, 1, 1);

        stageExitLabel = new QLabel(infoGroupBox);
        stageExitLabel->setObjectName(QString::fromUtf8("stageExitLabel"));

        infoGridLayout->addWidget(stageExitLabel, 0, 4, 1, 1);

        stageExitValue = new QLabel(infoGroupBox);
        stageExitValue->setObjectName(QString::fromUtf8("stageExitValue"));
        stageExitValue->setFont(font);

        infoGridLayout->addWidget(stageExitValue, 0, 5, 1, 1);


        mainLayout->addWidget(infoGroupBox);

        selectionGroupBox = new QGroupBox(Type4ConfigDialog);
        selectionGroupBox->setObjectName(QString::fromUtf8("selectionGroupBox"));
        selectionGridLayout = new QGridLayout(selectionGroupBox);
        selectionGridLayout->setObjectName(QString::fromUtf8("selectionGridLayout"));
        secondaryInletsLabel = new QLabel(selectionGroupBox);
        secondaryInletsLabel->setObjectName(QString::fromUtf8("secondaryInletsLabel"));
        secondaryInletsLabel->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(secondaryInletsLabel, 0, 0, 1, 1);

        secondaryExitsLabel = new QLabel(selectionGroupBox);
        secondaryExitsLabel->setObjectName(QString::fromUtf8("secondaryExitsLabel"));
        secondaryExitsLabel->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(secondaryExitsLabel, 0, 1, 1, 1);

        filmcoolingLabel = new QLabel(selectionGroupBox);
        filmcoolingLabel->setObjectName(QString::fromUtf8("filmcoolingLabel"));
        filmcoolingLabel->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(filmcoolingLabel, 0, 2, 1, 1);

        torqueWallsLabel = new QLabel(selectionGroupBox);
        torqueWallsLabel->setObjectName(QString::fromUtf8("torqueWallsLabel"));
        torqueWallsLabel->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(torqueWallsLabel, 0, 3, 1, 1);

        mixingPlanesLabel = new QLabel(selectionGroupBox);
        mixingPlanesLabel->setObjectName(QString::fromUtf8("mixingPlanesLabel"));
        mixingPlanesLabel->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(mixingPlanesLabel, 0, 4, 1, 1);

        secondaryInletsList = new QListWidget(selectionGroupBox);
        secondaryInletsList->setObjectName(QString::fromUtf8("secondaryInletsList"));
        secondaryInletsList->setSelectionMode(QAbstractItemView::MultiSelection);

        selectionGridLayout->addWidget(secondaryInletsList, 1, 0, 1, 1);

        secondaryExitsList = new QListWidget(selectionGroupBox);
        secondaryExitsList->setObjectName(QString::fromUtf8("secondaryExitsList"));
        secondaryExitsList->setSelectionMode(QAbstractItemView::MultiSelection);

        selectionGridLayout->addWidget(secondaryExitsList, 1, 1, 1, 1);

        filmcoolingList = new QListWidget(selectionGroupBox);
        filmcoolingList->setObjectName(QString::fromUtf8("filmcoolingList"));
        filmcoolingList->setSelectionMode(QAbstractItemView::MultiSelection);

        selectionGridLayout->addWidget(filmcoolingList, 1, 2, 1, 1);

        torqueWallsList = new QListWidget(selectionGroupBox);
        torqueWallsList->setObjectName(QString::fromUtf8("torqueWallsList"));
        torqueWallsList->setSelectionMode(QAbstractItemView::MultiSelection);

        selectionGridLayout->addWidget(torqueWallsList, 1, 3, 1, 1);

        mixingPlanesList = new QListWidget(selectionGroupBox);
        mixingPlanesList->setObjectName(QString::fromUtf8("mixingPlanesList"));
        mixingPlanesList->setSelectionMode(QAbstractItemView::MultiSelection);

        selectionGridLayout->addWidget(mixingPlanesList, 1, 4, 1, 1);

        secondaryInletsCount = new QLabel(selectionGroupBox);
        secondaryInletsCount->setObjectName(QString::fromUtf8("secondaryInletsCount"));
        secondaryInletsCount->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(secondaryInletsCount, 2, 0, 1, 1);

        secondaryExitsCount = new QLabel(selectionGroupBox);
        secondaryExitsCount->setObjectName(QString::fromUtf8("secondaryExitsCount"));
        secondaryExitsCount->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(secondaryExitsCount, 2, 1, 1, 1);

        filmcoolingCount = new QLabel(selectionGroupBox);
        filmcoolingCount->setObjectName(QString::fromUtf8("filmcoolingCount"));
        filmcoolingCount->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(filmcoolingCount, 2, 2, 1, 1);

        torqueWallsCount = new QLabel(selectionGroupBox);
        torqueWallsCount->setObjectName(QString::fromUtf8("torqueWallsCount"));
        torqueWallsCount->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(torqueWallsCount, 2, 3, 1, 1);

        mixingPlanesCount = new QLabel(selectionGroupBox);
        mixingPlanesCount->setObjectName(QString::fromUtf8("mixingPlanesCount"));
        mixingPlanesCount->setAlignment(Qt::AlignCenter);

        selectionGridLayout->addWidget(mixingPlanesCount, 2, 4, 1, 1);

        clearSecondaryInletsBtn = new QPushButton(selectionGroupBox);
        clearSecondaryInletsBtn->setObjectName(QString::fromUtf8("clearSecondaryInletsBtn"));

        selectionGridLayout->addWidget(clearSecondaryInletsBtn, 3, 0, 1, 1);

        clearSecondaryExitsBtn = new QPushButton(selectionGroupBox);
        clearSecondaryExitsBtn->setObjectName(QString::fromUtf8("clearSecondaryExitsBtn"));

        selectionGridLayout->addWidget(clearSecondaryExitsBtn, 3, 1, 1, 1);

        clearFilmcoolingBtn = new QPushButton(selectionGroupBox);
        clearFilmcoolingBtn->setObjectName(QString::fromUtf8("clearFilmcoolingBtn"));

        selectionGridLayout->addWidget(clearFilmcoolingBtn, 3, 2, 1, 1);

        clearTorqueWallsBtn = new QPushButton(selectionGroupBox);
        clearTorqueWallsBtn->setObjectName(QString::fromUtf8("clearTorqueWallsBtn"));

        selectionGridLayout->addWidget(clearTorqueWallsBtn, 3, 3, 1, 1);

        clearMixingPlanesBtn = new QPushButton(selectionGroupBox);
        clearMixingPlanesBtn->setObjectName(QString::fromUtf8("clearMixingPlanesBtn"));

        selectionGridLayout->addWidget(clearMixingPlanesBtn, 3, 4, 1, 1);


        mainLayout->addWidget(selectionGroupBox);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        buttonLayout->addItem(buttonSpacer);

        cancelButton = new QPushButton(Type4ConfigDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        buttonLayout->addWidget(cancelButton);

        okButton = new QPushButton(Type4ConfigDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        buttonLayout->addWidget(okButton);


        mainLayout->addLayout(buttonLayout);


        retranslateUi(Type4ConfigDialog);
        QObject::connect(okButton, SIGNAL(clicked()), Type4ConfigDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Type4ConfigDialog, SLOT(reject()));

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(Type4ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *Type4ConfigDialog)
    {
        Type4ConfigDialog->setWindowTitle(QCoreApplication::translate("Type4ConfigDialog", " Configuration", nullptr));
        infoGroupBox->setTitle(QCoreApplication::translate("Type4ConfigDialog", "Monitor Info", nullptr));
        fileNameLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "File Name:", nullptr));
        fileNameValue->setText(QCoreApplication::translate("Type4ConfigDialog", "-", nullptr));
        stageInletLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Stage Inlet:", nullptr));
        stageInletValue->setText(QCoreApplication::translate("Type4ConfigDialog", "-", nullptr));
        stageExitLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Stage Exit:", nullptr));
        stageExitValue->setText(QCoreApplication::translate("Type4ConfigDialog", "-", nullptr));
        selectionGroupBox->setTitle(QCoreApplication::translate("Type4ConfigDialog", "Boundary Face Selection", nullptr));
        secondaryInletsLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Secondary Inlets", nullptr));
        secondaryExitsLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Secondary Exits", nullptr));
        filmcoolingLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Film Cooling Zones", nullptr));
        torqueWallsLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Torque Walls", nullptr));
        mixingPlanesLabel->setText(QCoreApplication::translate("Type4ConfigDialog", "Mixing Planes", nullptr));
        secondaryInletsCount->setText(QCoreApplication::translate("Type4ConfigDialog", "Selected: 0", nullptr));
        secondaryExitsCount->setText(QCoreApplication::translate("Type4ConfigDialog", "Selected: 0", nullptr));
        filmcoolingCount->setText(QCoreApplication::translate("Type4ConfigDialog", "Selected: 0", nullptr));
        torqueWallsCount->setText(QCoreApplication::translate("Type4ConfigDialog", "Selected: 0", nullptr));
        mixingPlanesCount->setText(QCoreApplication::translate("Type4ConfigDialog", "Selected: 0", nullptr));
        clearSecondaryInletsBtn->setText(QCoreApplication::translate("Type4ConfigDialog", "Clear", nullptr));
        clearSecondaryExitsBtn->setText(QCoreApplication::translate("Type4ConfigDialog", "Clear", nullptr));
        clearFilmcoolingBtn->setText(QCoreApplication::translate("Type4ConfigDialog", "Clear", nullptr));
        clearTorqueWallsBtn->setText(QCoreApplication::translate("Type4ConfigDialog", "Clear", nullptr));
        clearMixingPlanesBtn->setText(QCoreApplication::translate("Type4ConfigDialog", "Clear", nullptr));
        cancelButton->setText(QCoreApplication::translate("Type4ConfigDialog", "Cancel", nullptr));
        okButton->setText(QCoreApplication::translate("Type4ConfigDialog", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Type4ConfigDialog: public Ui_Type4ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TYPE4CONFIGDIALOG_H
