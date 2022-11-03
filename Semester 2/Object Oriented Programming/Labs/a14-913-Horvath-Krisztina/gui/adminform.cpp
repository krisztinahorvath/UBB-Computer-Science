#include <fstream>
#include "adminform.h"
#include "ui_adminform.h"
#include <string>
#include <QMessageBox>

AdminForm::AdminForm(Service* s,Repository* r,  QWidget *parent) :
        QWidget(parent), serv(s), repo(r),
        ui(new Ui::AdminForm)
{
    ui->setupUi(this);

    /// lab work 12
    QLinearGradient list_grad(0,0,0, this->ui->movie_list->height());
    list_grad.setColorAt(0,QColorConstants::Svg::purple);
    list_grad.setColorAt(1, Qt::white);

    QPalette pal = this->ui->movie_list->palette();
    pal.setBrush(QPalette::ColorRole::Base, QBrush(list_grad));
    this->ui->movie_list->setPalette(pal);


    repo->write_to_file();
    this->connect_signals_slots();
    this->populate_list();
}

AdminForm::~AdminForm()
{
    delete ui;
}

void AdminForm::populate_list() {
    this->ui->movie_list->clear();
    std::vector<Movie> all_movies = this->serv->get_all_movies();
    for(auto& m: all_movies)
        this->ui->movie_list->addItem(QString::fromStdString(m.get_title() + " - " + m.get_genre() + " - " +
        std::to_string(m.get_year()) + " - " + std::to_string(m.get_likes()) + " - " + m.get_trailer()));
}

void AdminForm::add_movie() {
    std::string title, genre, year, likes, trailer;
    title = this->ui->title_lineEdit->text().toStdString();
    genre = this->ui->genre_lineEdit->text().toStdString();
    year = this->ui->year_lineEdit->text().toStdString();
    likes = this->ui->likes_lineEdit->text().toStdString();
    trailer = this->ui->trailer_lineEdit->text().toStdString();

    try
    {
        valid.validate_movie(title, genre, year, likes, trailer);
        this->serv->add_movie_serv(title, genre, stoi(year), stoi(likes), trailer);
        QMessageBox* added = new QMessageBox();
        added->setWindowTitle("Movie added!");
        added->setText("Movie added successfully to the repo!");
        added->setStandardButtons(QMessageBox::Ok);
        added->show();
        this->populate_list();
        this->clear_list_edits();
    }
    catch (RepositoryException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (MovieException& e){
        QMessageBox::critical(this, "Error", e.what());
    }
    catch(std::invalid_argument& e){
        QMessageBox::critical(this, "Error", "Please make sure to only introduce integers in the year and likes fields!");
    }
    catch(...){

    }
}

void AdminForm::delete_movie() {
    std::string title, genre, year, likes, trailer;
    title = this->ui->title_lineEdit->text().toStdString();
    genre = this->ui->genre_lineEdit->text().toStdString();
    year = this->ui->year_lineEdit->text().toStdString();

    int ok = 0;

    try{
        valid.validate_title(title);
    }
    catch (MovieException& e){
        QMessageBox::critical(this, "Error", e.what());
        ok++;
    }

    try{
        valid.validate_genre(genre);
    }
    catch (MovieException& e){
        QMessageBox::critical(this, "Error", e.what());
        ok++;
    }

    try{
        valid.validate_year(year);
    }
    catch (MovieException& e){
        QMessageBox::critical(this, "Error", e.what());
        ok++;
    }

    if(ok == 0){
        try{
            this->serv->remove_movie_serv(title, genre, stoi(year));
            QMessageBox* added = new QMessageBox();
            added->setWindowTitle("Movie deleted!");
            added->setText("Movie deleted successfully from the repo!");
            added->setStandardButtons(QMessageBox::Ok);
            added->show();
            this->populate_list();
            this->clear_list_edits();
        }
        catch(RepositoryException& e){
            QMessageBox::critical(this, "Error", e.what());
        }
        catch(std::invalid_argument& e){
            QMessageBox::critical(this, "Error", "Please make sure to only introduce integers in the year field!");
        }
        catch(MovieException& e){
            QMessageBox::critical(this, "Error", e.what());
        }
        catch(...){

        }
    }

}

void AdminForm::update_movie() {
    std::string title, genre, year, likes, trailer;
    title = this->ui->title_lineEdit->text().toStdString();
    genre = this->ui->genre_lineEdit->text().toStdString();
    year = this->ui->year_lineEdit->text().toStdString();
    likes = this->ui->likes_lineEdit->text().toStdString();
    trailer = this->ui->trailer_lineEdit->text().toStdString();

    try
    {
        valid.validate_movie(title, genre, year, likes, trailer);
        this->serv->update_movie_serv(title, genre, stoi(year), stoi(likes), trailer);
        QMessageBox* added = new QMessageBox();
        added->setWindowTitle("Movie updated!");
        added->setText("Movie updated successfully in the repo!");
        added->setStandardButtons(QMessageBox::Ok);
        added->show();
        this->populate_list();
        this->clear_list_edits();
    }
    catch (RepositoryException& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }
    catch (MovieException& e){
        QMessageBox::critical(this, "Error", e.what());
    }
    catch(std::invalid_argument& e){
        QMessageBox::critical(this, "Error", "Please make sure to only introduce integers in the year and likes fields!");
    }
    catch(...){

    }
}

void AdminForm::connect_signals_slots() {
    QObject::connect(this->ui->addButton, &QPushButton::clicked, this, &AdminForm::add_movie);
    QObject::connect(this->ui->deleteButton, &QPushButton::clicked, this, &AdminForm::delete_movie);
    QObject::connect(this->ui->updateButton, &QPushButton::clicked, this, &AdminForm::update_movie);

}

void AdminForm::clear_list_edits() {
    this->ui->title_lineEdit->clear();
    this->ui->genre_lineEdit->clear();
    this->ui->year_lineEdit->clear();
    this->ui->likes_lineEdit->clear();
    this->ui->trailer_lineEdit->clear();
}
