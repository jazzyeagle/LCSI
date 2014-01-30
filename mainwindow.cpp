#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	JSONModel *model = new JSONModel(this);
	ui->table->setModel(model);
	ui->table->hideColumn(6);
	ui->table->hideColumn(7);
	ui->table->hideColumn(8);
	ui->table->hideColumn(9);
	ui->table->hideColumn(10);
	ui->table->hideColumn(11);
	ui->table->hideColumn(12);
	//ui->table->hideColumn(13);
}

MainWindow::~MainWindow() {
	delete ui;
}
