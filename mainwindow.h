#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlmodel.h"
#include "sqldelegate.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void onExit();
    
    private:
        Ui::MainWindow *ui;
        SQLModel *model;
};

#endif // MAINWINDOW_H
