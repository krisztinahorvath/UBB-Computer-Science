//
// Created by krisz on 6/6/2022.
//

#include "Repository.h"
#include <fstream>

Repository::Repository() {

}

void Repository::read_file_questions() {
    std::string file = R"(C:\Facultate\OOP\exam\e913-913-Horvath-Krisztina-1\repo\questions.txt)";
    std::ifstream f(file);

    Question q{};
    while(f >> q)
        questions.push_back(q);
    f.close();
}

void Repository::read_file_participants() {
    std::string file = R"(C:\Facultate\OOP\exam\e913-913-Horvath-Krisztina-1\repo\participants.txt)";
    std::ifstream f(file);

    Participant q{};
    while(f >> q)
        participants.push_back(q);
    f.close();
}

void Repository::write_file_questions() {
    std::string file = R"(C:\Facultate\OOP\exam\e913-913-Horvath-Krisztina-1\repo\questions.txt)";
    std::ofstream f(file, std::ios::trunc);

    for(auto q: questions)
        f << q << "\n";
    f.close();
}

void Repository::write_file_participants() {
    std::string file = R"(C:\Facultate\OOP\exam\e913-913-Horvath-Krisztina-1\repo\participants.txt)";
    std::ofstream f(file, std::ios::trunc);

    for(auto p: participants)
        f << p << "\n";

    f.close();
}

int Repository::answer_question(int id, std::string ans, std::string name) {
    for(auto q: get_questions())
        if(q.get_id() == id) {
            add_selected_questions(q);
            if(q.get_correct_answer() == ans){
                int count = 0;
                for(auto part: get_participants()){
                    if(part.get_name() == name){
                        Participant p = Participant(part.get_name(), part.get_score() + q.get_score());
                        participants[count] = p;
                        int i = part.set_score(q.get_score());
//                        return p.get_score() ;
                        return part.get_score();
                    }
                    count++;
                }
            }

        }
    return -1;
}
