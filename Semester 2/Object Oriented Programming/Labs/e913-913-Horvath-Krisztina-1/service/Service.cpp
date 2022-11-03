//
// Created by krisz on 6/6/2022.
//

#include "Service.h"

std::vector<Question> Service::get_questions_sorted_id() {
    std::vector<Question> sorted = repo.get_questions();

    for(int i = 0; i < sorted.size() -1 ; i++)
        for(int j = i+1; j < sorted.size(); j++)
            if(sorted[i].get_id() > sorted[j].get_id()){
                Question q = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = q;
            }
    return sorted;
}

std::vector<Question> Service::get_questions_sorted_score() {
    std::vector<Question> sorted = repo.get_questions();

    for(int i = 0; i < sorted.size() -1 ; i++)
        for(int j = i+1; j < sorted.size(); j++)
            if(sorted[i].get_score() < sorted[j].get_score()){
                Question q = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = q;
            }
    return sorted;
}

int Service::find_q_id(int id) {
    for(auto i: repo.get_questions())
        if(i.get_id() == id)
            return 0;
    return 1;
}

void Service::add_question(int id, std::string text, std::string answer, int score) {
    Question q{id, text, answer, score};
    repo.add_question(q);
    notify();
}

int Service::answer_question(int id, std::string ans, std::string name) {
   return repo.answer_question(id, ans, name);
}

void Service::add_selected_questions(Question& q) {
    repo.add_selected_questions(q);
//    notify();
}

int Service::in_selected_questions(int id) {
    for(auto i: repo.get_selected_questions())
        if(i.get_id() == id)
            return 1;
    return 0;
}


