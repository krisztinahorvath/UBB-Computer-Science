#pragma once
#include <vector>
#include <sstream>
#include <string>

class Question {
private:
    int id;
    std::string text;
    std::string correct_answer;
    int score;

public:
    Question();
    Question(int i, std::string t, std::string c, int s): id(i), text(t), correct_answer(c), score(s){}
    int get_id(){return id;}

    friend std::istream&operator>>(std::istream& is, Question& q);
    friend std::ostream&operator<<(std::ostream& os, Question& q);

    std::string to_string();
    int get_score(){return score;}
    std::string get_text() {return text;}
    std::string get_correct_answer() {return correct_answer;}
    std::string to_string_part();

};

class Participant{
private:
    std::string name;
    int score;

public:
    Participant();
    Participant(std::string n, int s): name(n), score(s){}

    friend std::istream&operator>>(std::istream& is, Participant& p);
    friend std::ostream&operator<<(std::ostream& os, Participant& p);

    std::string to_string();

    std::string get_name(){return name;}
    int get_score() { return score;}
    int set_score(int s) { score = score + s; return  score;}
};

