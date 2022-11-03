#pragma once
#include "Repository.h"
#include "Observer.h"

class Service: public Subject {
private:
    Repository& repo;

public:
    Service(Repository& r): repo(r){repo.read_file_users(); repo.read_file_answers(); repo.read_file_questions();}

    std::vector<User> get_users(){ return repo.get_users(); }
    std::vector<Question> get_questions(){ return repo.get_questions(); }
    std::vector<Question> get_sorted_questions();
    std::vector<Answer> get_answers(){ return repo.get_answers(); }

    /**
     * This function looks in repo for the answers that have question
     * id equal to the given param id and returns a vector of answers
     * with that id*/
    std::vector<Answer> get_answers_for_question(int id);
    Question get_matching_question(std::string q);

    /** Creates a question with the given data and call the add_question() function from the repo
     * which adds a question to the repo*/
    void add_question_serv(std::string name, std::string text, int id);
    void write_to_file(){ repo.write_file_answers(); repo.write_file_questions(); }

    ~Service();
};


