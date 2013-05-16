#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->actionE_xit->setShortcut(QKeySequence::Quit);
    connect(ui->actionE_xit, SIGNAL(triggered()), this, SLOT(onExit()));
    model = new SQLModel(this);
    ui->SQLView->setModel(model->getModel());
    ui->SQLView->setItemDelegateForColumn(9, new SQLDelegate(this));
    ui->SQLView->setItemDelegateForColumn(10, new SQLDelegate(this));
    for(int i=0; i<model->getModel()->rowCount(); i++) {
        ui->SQLView->openPersistentEditor(model->getModel()->index(i, 9));
        ui->SQLView->openPersistentEditor(model->getModel()->index(i, 10));
        ui->SQLView->setRowHeight(i, 100);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onExit() {
    close();
}
