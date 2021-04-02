#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isFileLoaded = false;
    ResetStats();
}

MainWindow::~MainWindow()
{
    delete ui;
}


///Select file button
void MainWindow::on_btn_openFile_clicked()
{
    this->fileName = QFileDialog::getOpenFileName(this, tr("Открыть текстовый файл"), "../IdentifierTable", tr("Текстовый файл (*.txt)"));
    this->ui->text_fileName->setText(this->fileName);
}
///Load file button
void MainWindow::on_btn_loadFile_clicked()
{
    if (this->fileName == "")
    {
        QMessageBox mb;
        mb.setText("Файл не выбран.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }

    QFile inputFile(this->fileName);
    if(inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        in.setEncoding(QStringConverter::Utf8);
        this->ui->text_input->clear();
        while(!in.atEnd()) {
            QString line = in.readLine();
            identifierList.push_back(line);
            this->ui->text_input->appendPlainText(line);
        }
    } else {
        QMessageBox msg;
        msg.warning(this, "Ошибка", "Невозможно открыть файл");
    }

    isFileLoaded = true;
    AddIdentifiers();
}
///Search button
void MainWindow::on_pushButton_3_clicked()
{
    if (!isFileLoaded)
    {
        QMessageBox mb;
        mb.setText("Файл не загружен.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }

    QString identifier = this->ui->le_identifier->text().toLower();

    //empty string check
    if (identifier == "")
    {
        QMessageBox mb;
        mb.setText("Введите идентификатор.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }

    bool isFound = QueryIdentifier(identifier);
    //if not found
    if (!isFound)
    {
        QMessageBox mb;
        mb.setText("Идентификатор не найден.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }

    searchCount++;
    GetStats();
    DisplayStats();
}
///Reset button
void MainWindow::on_pushButton_4_clicked()
{
    if (!isFileLoaded)
    {
        QMessageBox mb;
        mb.setText("Файл не загружен.");
        mb.setStandardButtons(QMessageBox::Ok);
        mb.exec();
        return;
    }
    ResetStats();
}
///Quit button
void MainWindow::on_pushButton_5_clicked()
{
    this->window()->close();
}



///Add all identifiers from the list
void MainWindow::AddIdentifiers()
{
    for (unsigned int i = 0; i < identifierList.length(); i++)
    {
        std::string identifier = identifierList[i].toLower().toStdString();

        ht.add(&identifier);
        sl.add(identifier);
    }
}
///Search for identifier
bool MainWindow::QueryIdentifier(QString identifier)
{
    ResetContainers();

    std::string indentifierStd = identifier.toStdString();
    //query containers, store results
    bool ht_res = ht.contains(&indentifierStd);
    bool sl_res = sl.contains(indentifierStd);

    //if results are different, smth is wrong, throw
    if (ht_res != sl_res)
    {
        throw;
    }

    //return result
    return ht_res;
}
///Get stats from containers
void MainWindow::GetStats()
{
    //get last search counts
    ht_last = ht.getCompares();
    sl_last = sl.getCompares();

    //add to sum
    ht_sum += ht_last;
    sl_sum += sl_last;
}
///Display stats
void MainWindow::DisplayStats()
{
    //display search count
    this->ui->l_searchCount->setText("Всего поиск: " + QString::number(searchCount) + " раз");

    //calculate average
    float ht_avg = ht_sum/searchCount;
    float sl_avg = sl_sum/searchCount;

    //update ht
    this->ui->l_ht_curCompares->setText("Сравнений: " + QString::number(ht_last));
    this->ui->l_ht_totalCompares->setText("Всего сравнений: " + QString::number(ht_sum));
    this->ui->l_ht_avgCompares->setText("В среднем: " + QString::number(ht_avg));

    //update slz
    this->ui->l_sl_curCompares->setText("Сравнений: " + QString::number(sl_last));
    this->ui->l_sl_totalCompares->setText("Всего сравнений: " + QString::number(sl_sum));
    this->ui->l_sl_avgCompares->setText("В среднем: " + QString::number(sl_avg));
}
///Reset container stats
void MainWindow::ResetContainers()
{
    ht.resetStats();
    sl.resetStats();
}
///Reset display stats
void MainWindow::ResetStats()
{
    ResetContainers();
    ht_sum = 0.0f;
    sl_sum = 0.0f;

    //reset search count
    searchCount = 0;
    this->ui->l_searchCount->setText("Всего поиск: 0 раз");

    //reset ht
    this->ui->l_ht_curCompares->setText("Сравнений: 0");
    this->ui->l_ht_totalCompares->setText("Всего сравнений: 0");
    this->ui->l_ht_avgCompares->setText("В среднем: 0");

    //reset sl
    this->ui->l_sl_curCompares->setText("Сравнений: 0");
    this->ui->l_sl_totalCompares->setText("Всего сравнений: 0");
    this->ui->l_sl_avgCompares->setText("В среднем: 0");
}
