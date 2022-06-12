#include "movietracker.h"
#include "ui_movietracker.h"
#include "infowindow.h"
#include "addwindow.h"
#include "editwindow.h"
#include <fstream>
#include <sstream>
#include <QFileDialog>
#include <QMessageBox>
#include "mainwindow.h"
#include <QPainter>

MovieTracker::MovieTracker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieTracker)
{
    ui->setupUi(this);

    createList();
    //proxyModel = new ProxyModel();
    //proxyModel -> setSourceModel(itemModel);
    //ui -> tableView -> setModel(proxyModel);

    //ui -> tableView -> setSortingEnabled(true);
    //ui -> tableView -> sortByColumn(0, Qt::SortOrder::AscendingOrder);

}

MovieTracker::~MovieTracker()
{
    delete ui;
}

//Creating listView with data
void MovieTracker::createList()
{
    std::string fName = "netflix_titles.csv";
    std::ifstream inputFile(fName);
    std::string line, token;
    std::getline(inputFile, line);

    //Parsing through CSV file
    while (std::getline(inputFile, line))
    {
        bool quote = false;
        std::vector<std::string> linesVector;
        std::string temp;
        for (int i = 0; i < line.size() + 1; i++)
        {
            if (line[i] == '"')
                quote = !quote;
            if (line[i] != '"' and line[i] != ',')
                temp += line[i];
            if (line[i] == ',' and !quote)
            {
                linesVector.push_back(temp);
                temp.clear();
            }
        }
        //Adding features to std::vector<Data>

        Data data;
        data.title = linesVector[2];
        data.type = linesVector[1];
        data.director = linesVector[3];
        data.country = linesVector[5];
        data.year = linesVector[7];
        data.tv_rating = linesVector[8];
        this -> dataVector.push_back(data);
    }
    inputFile.close();

    //Creating itemModel and adding 2 columns there (title and status)
    this -> itemModel = new QStandardItemModel(this);
    for (int i = 0; i < dataVector.size(); i++)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::fromStdString(dataVector[i].title)));
        items.append(new QStandardItem(QString::fromStdString(dataVector[i].status)));
        itemModel -> appendRow(items);
    }

    //setting columns labels
    itemModel -> setHeaderData(0, Qt::Horizontal, tr("Movies"));
    itemModel -> setHeaderData(1, Qt::Horizontal, tr("Status"));

    //Proxy model
    proxyModel = new ProxyModel();
    proxyModel -> setSourceModel(itemModel);
    proxyModel -> setStatus("Unwatched");
    ui -> tableView -> setModel(proxyModel);

    //setting itemModel to tableView
    //********this -> ui -> tableView -> setModel(itemModel);
    this -> ui -> tableView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    //********this -> ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);

    //setting number of movies
    this -> ui -> numberOfMoviesText -> setAutoFillBackground(false);
    this -> ui -> numberOfMoviesText -> setReadOnly(true);
    this -> ui -> numberOfMoviesText -> setText(QString::fromStdString(std::to_string(dataVector.size())) + " movies");
}

//Search button
void MovieTracker::on_search_button_clicked()
{

}

//Edit button
void MovieTracker::on_edit_button_clicked()
{
    int row = this -> ui -> tableView -> currentIndex().row();

    editWindow editWin;
    editWin.setPointers(&dataVector[row], this->itemModel, row);
    editWin.setModal(true);

    this -> ui -> tableView -> setModel(itemModel);

    editWin.exec();
}

//Delete button
void MovieTracker::on_delete_button_clicked()
{
    //Deleting from tableView
    int dataRow = this -> ui -> tableView -> currentIndex().row();
    this -> itemModel -> removeRows(dataRow, 1);
    //Deleting from the dataVector
    std::vector<Data>::iterator it = this -> dataVector.begin() + dataRow;
    this -> dataVector.erase(it);

    //Updating number of movies
    this -> ui -> numberOfMoviesText -> setText(QString::fromStdString(std::to_string(dataVector.size())) + " movies");
}

//Add button
void MovieTracker::on_add_button_clicked()
{
    addWindow addWin;
    Data addData;
    this -> dataVector.push_back(addData);

    addWin.setPointers(this -> itemModel, &dataVector[dataVector.size() - 1]);

    addWin.setModal(true);
    addWin.exec();
    //Updating number of movies
    int rows = itemModel->rowCount();

    ui -> tableView -> setModel(itemModel);
    this -> ui -> numberOfMoviesText -> setText(QString::fromStdString(std::to_string(dataVector.size())) + " movies");
}

//Back button
void MovieTracker::on_back_button_clicked()
{
    this -> close();
}

//Detailed info button
void MovieTracker::on_info_button_clicked()
{
    int dataRow = this -> ui -> tableView -> currentIndex().row();

    infoWindow infoWin;
    infoWin.getData(dataVector[dataRow]);
    infoWin.setModal(true);
    infoWin.exec();
}

//Save button
void MovieTracker::on_save_button_clicked()
{
    //Creating a file and first line with column titles
    QString fileName = QFileDialog::getSaveFileName(this, "Backup file", "", tr("CSV file (*.csv);;All Files (*)"));
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write("Tile, Type, Director, Country, Year, Rating, Status\n");
    //Filling file with data
    for (int i = 0; i < dataVector.size(); i++)
    {
        std::stringstream ss;
        ss << dataVector[i].title << "," << dataVector[i].type << "," << dataVector[i].director << ","
           << dataVector[i].country << "," << dataVector[i].year << "," << dataVector[i].tv_rating << "," << dataVector[i].status << '\n';
        file.write(ss.str().c_str());
    }
    file.close();
}


//Load button
void MovieTracker::on_load_button_clicked()
{
    //Getting file name and loading it
    QString fileName = QFileDialog::getOpenFileName(this, "Load", "");
    QFile loadFile(fileName);
    loadFile.open(QIODevice::ReadOnly);
    loadFile.readLine();
    //Clearing the model and dataVector in case users loads some file
    if (fileName != "")
    {
        dataVector.clear();
        itemModel -> removeRows(0, itemModel -> rowCount());
    }
    //Inserting data from file to dataVector
    while(!loadFile.atEnd())
    {
        std::string token;
        std::string line = loadFile.readLine().toStdString();
        std::istringstream ss(line);
        std::vector<std::string> linesVector;
        while (std::getline(ss, token, ','))
        {
            linesVector.push_back(token);
        }

        Data  data;
        data.title = linesVector[0];
        data.type = linesVector[1];
        data.director = linesVector[2];
        data.country = linesVector[3];
        data.year = linesVector[4];
        data.tv_rating = linesVector[5];
        this -> dataVector.push_back(data);

    }
    loadFile.close();
    //Creating itemModel and adding 2 columns there (title and status)
    this -> itemModel = new QStandardItemModel(this);
    for (int i = 0; i < dataVector.size(); i++)
    {
        QList<QStandardItem *> items;
        items.append(new QStandardItem(QString::fromStdString(dataVector[i].title)));
        items.append(new QStandardItem(QString::fromStdString(dataVector[i].status)));
        itemModel -> appendRow(items);
    }

    //setting columns labels
    itemModel -> setHeaderData(0, Qt::Horizontal, tr("Movies"));
    itemModel -> setHeaderData(1, Qt::Horizontal, tr("Status"));

    //Proxy model
    proxyModel = new ProxyModel();
    proxyModel -> setSourceModel(itemModel);
    proxyModel -> setStatus("Unwatched");
    ui -> tableView -> setModel(proxyModel);

    //setting number of movies
    this -> ui -> numberOfMoviesText -> setAutoFillBackground(false);
    this -> ui -> numberOfMoviesText -> setReadOnly(true);
    this -> ui -> numberOfMoviesText -> setText(QString::fromStdString(std::to_string(dataVector.size())) + " movies");
}


void MovieTracker::on_lineEdit_textChanged(const QString &arg1)
{
    proxyModel -> setTitle(ui -> lineEdit -> text());
    proxyModel -> setStatus(ui -> lineEdit -> text());
    if (ui -> lineEdit -> text().isEmpty())
    {
        proxyModel -> setStatus("Unwatched");
    }
}
//Setting up a logo
 void MovieTracker::paintEvent(QPaintEvent *event)
 {
    QPainter painter(this);
     painter.setPen(QPen(Qt::black, 8));
    painter.drawRect(0, 0, 138, 61);
    painter.setPen(QPen(Qt::black, 8));
    painter.background();
    QPolygon pol;
    pol << QPoint(30, 61) << QPoint(45, 0) << QPoint(70, 40) << QPoint(95, 0) << QPoint(110, 61);
    painter.drawPolygon(pol);
 }


