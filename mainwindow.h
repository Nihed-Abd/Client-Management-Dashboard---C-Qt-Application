#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_on_pb_add_clicked_clicked();

    void on_actualiser_clicked();

    void on_modify_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_2_activated(const QModelIndex &index);

    void on_recherche_cin_textChanged(const QString &arg1);

    void on_pushButton_2_clicked(const QModelIndex &index);

    void on_valider_abo_clicked();

    void on_valider_commision_clicked();

    void on_pdf1_clicked();

    void on_pdf2_clicked();

private:
    Ui::MainWindow *ui;
    client c;
};

#endif // MAINWINDOW_H
