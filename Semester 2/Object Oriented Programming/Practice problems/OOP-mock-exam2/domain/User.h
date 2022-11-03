#pragma once
#include <string>
#include <sstream>
#include <iostream>

class User {
private:
    std::string name;

public:
    User();
    User(std::string u): name(u){}
    ~User();
    friend std::ostream&operator<<(std::ostream& os, User& u);
    friend std::istream&operator>>(std::istream& is, User& u);
    std::string get_name() { return name;}
};

class Question{
private:
    int id;
    std::string text;
    std::string name;

public:
    Question();
    Question(int i, std::string t, std::string n): id(i), text(t), name(n){}
    friend std::ostream&operator<<(std::ostream& os, Question& q);
    friend std::istream&operator>>(std::istream& is, Question& q);

    std::string to_string(){
        std::stringstream buffer;
        buffer  << id << ";" << text << ";" << name;
        return buffer.str();
    }

    int get_id(){ return id;}
    std::string get_text() {return text;}
};

class Answer{
private:
    int id;
    int question_id;
    std::string name;
    std::string text;
    int number_of_votes;

public:
    Answer();
    Answer(int i, int q, std::string n, std::string t, int nr): id(i), question_id{q}, name(n), text(t), number_of_votes(nr){}
    friend std::ostream&operator<<(std::ostream& os, Answer& a);
    friend std::istream&operator>>(std::istream& is, Answer& a);
    int get_question_id() {return question_id;}
    std::string to_string(){
        std::stringstream buffer;
        buffer << id << ";" << question_id << ";" << name << ";" << text << ";" << number_of_votes;
        return buffer.str();
    }
    std::string get_name() { return name;}
};


