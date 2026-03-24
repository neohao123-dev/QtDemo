#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "roundprogressbar.h"
#include <QPropertyAnimation>

#include <QTime>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RoundProgressBar *progressBar = new RoundProgressBar(this);
    progressBar->resize(240, 300);
    progressBar->setValue(90);

    progressBar->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
