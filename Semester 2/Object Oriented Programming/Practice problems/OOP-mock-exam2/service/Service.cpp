//
// Created by krisz on 6/5/2022.
//

#include "Service.h"

std::vector<Answer> Service::get_answers_for_question(int id) {
    std::vector<Answer> res;
    std::vector<Answer> ans = repo.get_answers();
    for(auto i: ans)
        if(i.get_question_id() == id)
            res.push_back(i);
    return res;
}

std::vector<Question> Service::get_sorted_questions() {
    std::vector<Question> sorted = repo.get_questions();
    std::vector<int> nr_ans;

    int ind = 0;
    for(auto q: repo.get_questions()){
        nr_ans.push_back(get_answers_for_question(q.get_id()).size());
        ind++;
    }

    for(int i = 0 ; i < sorted.size() - 1; i++)
        for(int j = i + 1; j < sorted.size(); j++)
            if(nr_ans[i] < nr_ans[j]){
                Question aux = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = aux;
            }

    return sorted;
}

Question Service::get_matching_question(std::string q) {
    Question res{};
    int match = 0;
    for(auto s: repo.get_questions())
        if(s.get_text().find(q) != std::string::npos){
            int count = 0;
            for(int i = 0; i < s.get_text().size(); i++)
                if(q[i] == s.get_text()[i])
                    count++;
            if(count > match){
                match = count;
                res = s;
            }
        }

    return res;
}

void Service::add_question_serv(std::string name, std::string text, int id ) {
    Question q(id, text, name);
    repo.add_question(q);
    notify();
}

Service::~Service() {
    write_to_file();
}


