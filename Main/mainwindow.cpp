#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "PreMainWindow.h"


#include <QDir>
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
    // connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton_2_clicked()));
    // connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(on_pushButton_3_clicked()));

    ui->lE_ShowDir->setText(QDir::homePath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    PreMainWindow *premainwindow = new PreMainWindow();
    premainwindow->show();
    this->close();
    return;
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow *postmainwindow = new MainWindow();
    postmainwindow->show();
    this->close();
    return;
}

void MainWindow::on_Btn_ChooseDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Choose Directory", QDir::homePath());
    QDir::setCurrent(dir);
    ui->lE_ShowDir->setText(dir);
}
