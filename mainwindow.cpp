#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    renderer_ = new glrenderer();
    mainLayout->addWidget(renderer_);
    centralWidget()->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_File_triggered() {
    QString filename =
        QFileDialog::getOpenFileName(this, tr("Load File"), ".");
    if (filename.isEmpty()) return;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    renderer_->loadSoundFile(filename.toStdString());
    QApplication::restoreOverrideCursor();
}
