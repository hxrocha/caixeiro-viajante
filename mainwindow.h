#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <QPicture>
#include <QLabel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnCalcular_clicked();




    void on_edCruzamentos_editingFinished();

    void on_edMutacao_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QwtPlot plot;

    QLabel l;
};

#endif // MAINWINDOW_H
