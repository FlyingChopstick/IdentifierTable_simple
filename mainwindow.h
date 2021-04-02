#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QString>
#include <QVector>

#include "hashTableSimple.h"
#include "sortedDynArray.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_openFile_clicked();

    void on_btn_loadFile_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QVector<QString> identifierList;

    HashTable ht;
    SortedList<std::string> sl;

    void AddIdentifiers();
    bool QueryIdentifier(QString identifier);
    void GetStats();
    void DisplayStats();
    void ResetContainers();
    void ResetStats();

    int searchCount;
    int ht_last;
    int sl_last;
    float ht_sum;
    float sl_sum;

    bool isFileLoaded;
};
#endif // MAINWINDOW_H
