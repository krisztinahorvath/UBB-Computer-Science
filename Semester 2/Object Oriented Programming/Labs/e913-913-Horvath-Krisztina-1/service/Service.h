#pragma once
#include "Repository.h"
#include "Observer.h"

class Service: public Subject{
private:
    Repository& repo;

public:
    Service(Repository& r): repo(r) { repo.read_file_questions(); repo.read_file_participants(); }
    ~Service(){ repo.write_file_participants(); repo.write_file_questions();}
    std::vector<Question> get_questions(){ return repo.get_questions(); }
    std::vector<Participant> get_participants() {return repo.get_participants();}
    std::vector<Question> get_questions_sorted_id();
    std::vector<Question> get_questions_sorted_score();

    int find_q_id(int id);
    void add_question(int id, std::string text, std::string answer, int score);
    int answer_question(int id, std::string ans, std::string name);

    void add_selected_questions(Question& q);
    std::vector<Question> selected_questions(){ return repo.get_selected_questions();}
    int in_selected_questions(int id);

};


