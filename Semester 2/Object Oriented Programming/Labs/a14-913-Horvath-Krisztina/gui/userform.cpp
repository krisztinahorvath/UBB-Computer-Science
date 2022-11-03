#include <QMessageBox>
#include <utility>
#include "userform.h"
#include "ui_userform.h"

UserForm::UserForm(Service* s, WatchList* watch, std::string type, QWidget *parent) :
    QWidget(parent), serv(s), watchList(watch), type(std::move(type)), ui(new Ui::UserForm)
{
    ui->setupUi(this);
    this->connect_signals_slots();
}

UserForm::~UserForm()
{
    delete ui;
}

void UserForm::populate_list(const std::vector<Movie>& v) {
    this->ui->movie_listWidget->clear();
    for(auto&m: v)
        this->ui->movie_listWidget->addItem(QString::fromStdString(m.get_title() + " - " + m.get_genre() + " - " +
                                                                   std::to_string(m.get_year()) + " - " + std::to_string(m.get_likes()) + " - " + m.get_trailer()));
}

void UserForm::display_by_genre() {
    try{
        std::string genre;
        genre = this->ui->genre_lineEdit->text().toStdString();
        WatchList* w = this->serv->display_by_genre_serv(genre);
        if(this->type == "html")
            this->watchList = new HTMLWatchList(w->get_watchlist(), 0);
        else
            this->watchList = w;
        if(w->is_empty())
            QMessageBox::critical(this, "Error", "There are no movies that can be watched!");

        Movie m = this->watchList->get_current();

        this->ui->movie_listWidget->clear();
        this->ui->movie_listWidget->addItem(QString::fromStdString(m.get_title() + " \n " + m.get_genre() + " \n " +
                                                                   std::to_string(m.get_year()) + " \n " + std::to_string(m.get_likes()) + " \n " + m.get_trailer()));
        w->play_trailer_serv();
    }
    catch(...){
        QMessageBox::critical(this, "Error", "Invalid genre");
    }
}

void UserForm::delete_from_watchlist() {
    std::string title, genre, year, like;
    title = this->ui->title_lineEdit->text().toStdString();
    genre = this->ui->genre_lineEdit->text().toStdString();
    year = this->ui->year_lineEdit->text().toStdString();

    if(this->ui->like_radioButton->isChecked())
        like = "y";
    else like = "n";

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
        if(like == "y"){
            try{
                this->serv->like_movie_serv(title, genre, stoi(year));
                QMessageBox* liked = new QMessageBox();
                liked->setWindowTitle("Movie liked!");
                liked->setText("\t\tMovie was liked!\n");
                liked->setStandardButtons(QMessageBox::Ok);
                liked->show();
            }
            catch (RepositoryException& e){
                QMessageBox::critical(this, "Error", e.what());
            }
        }
        else if(like == "n")
            QMessageBox::critical(this, "Error", "\t\tMovie wasn't liked!\n");

        try{
            this->serv->remove_watchlist_serv(title, genre, stoi(year));
            QMessageBox* deleted = new QMessageBox();
            deleted->setWindowTitle("Movie deleted!");
            deleted->setText("\t\tMovie deleted successfully from the watch list!\n");
            deleted->setStandardButtons(QMessageBox::Ok);
            deleted->show();
        }
        catch (WatchListRepoException& e){
            QMessageBox::critical(this, "Error", e.what());
        }
    }
    this->ui->title_lineEdit->clear();
    this->ui->genre_lineEdit->clear();
    this->ui->year_lineEdit->clear();
    this->display_watchlist();
}

void UserForm::open_in_app() {
    this->watchList->open_in_app();
}

void UserForm::add_to_watchlist() {
    try{
        this->serv->add_watchlist_serv(this->watchList->get_current());
        QMessageBox* added = new QMessageBox();
        added->setWindowTitle("Movie added!");
        added->setText("Movie added successfully to the watchlist!");
        added->setStandardButtons(QMessageBox::Ok);
        added->show();
    }
    catch(WatchListRepoException& e){
        QMessageBox::critical(this, "Error", e.what());
    }
    catch(...){

    }
}

void UserForm::next_in_list() {
    try{
        this->watchList->next();
        this->ui->movie_listWidget->clear();

        Movie m = this->watchList->get_current();
        this->ui->movie_listWidget->addItem(QString::fromStdString(m.get_title() + " \n " + m.get_genre() + " \n " +
                                                                   std::to_string(m.get_year()) + " \n " + std::to_string(m.get_likes()) + " \n " + m.get_trailer()));
        this->watchList->play_trailer_serv();
    }
    catch(...)
    {
        QMessageBox::critical(this, "Error", "No movies that can be watched");
    }
}

void UserForm::exit_from_list() {
    this->ui->movie_listWidget->clear();
    this->ui->genre_lineEdit->clear();
}

void UserForm::connect_signals_slots() {
    QObject::connect(this->ui->list_pushButton, &QPushButton::clicked, this, &UserForm::display_by_genre);
    QObject::connect(this->ui->delete_pushButton, &QPushButton::clicked, this, &UserForm::delete_from_watchlist);
    QObject::connect(this->ui->open_pushButton, &QPushButton::clicked, this, &UserForm::open_in_app);
    QObject::connect(this->ui->add_pushButton, &QPushButton::clicked, this, &UserForm::add_to_watchlist);
    QObject::connect(this->ui->next_pushButton, &QPushButton::clicked, this, &UserForm::next_in_list);
    QObject::connect(this->ui->exit_pushButton, &QPushButton::clicked, this, &UserForm::exit_from_list);
    QObject::connect(this->ui->watchlist_pushButton, &QPushButton::clicked, this, &UserForm::display_watchlist);
}

void UserForm::display_watchlist() {
    this->ui->movie_listWidget->clear();
    this->populate_list(this->serv->get_all_watchlist());
}
