#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtCharts/QtCharts>
#include <QLayout>
#include <math.h>
#include <convert.h>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_vt_clicked();
    void on_ht_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
