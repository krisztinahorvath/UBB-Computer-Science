//
// Created by krisz on 5/5/2022.
//

#include <algorithm>
#include "Comparator.h"
#include <assert.h>
#include "repository.h"

bool CompareAscendingByYear::compare(Movie t1, Movie t2) {
    if(t1.get_year() < t2.get_year())
        return true;
    return false;
}

bool CompareDescendingByTitle::compare(Movie t1, Movie t2)  {
    return t1.get_title().compare(t2.get_title()) > 0;
}

template <typename TELem>
void comparing(std::vector<TELem>& m, Comparator<TELem> *c) {
    TELem aux;
    for(int i = 0; i < m.size() - 1; i++){
        for(int j = i+1; j < m.size(); j++){
            if(!c->compare(m[i], m[j])){
                aux = m[i];
                m[i] = m[j];
                m[j] = aux;
            }
        }
    }
}

void test_compare(){
    Movie m1("Hercules", "Animation", 1997, 1333, "adssfdgfhgj");
    Movie m2("Corpse Bride", "Animation", 2005, 14134, "asedrty");
    Movie m3("Batman", "Crime", 2022, 325235, "qe23rw4t5r");
    std::vector<Movie> repo;
    repo.push_back(m1);
    repo.push_back(m3);
    repo.push_back(m2);
    Comparator<Movie>* c = new CompareAscendingByYear;
    comparing(repo, c);
    assert(repo[0].get_title() == m1.get_title());
    assert(repo[1].get_title() == m2.get_title());
    assert(repo[2].get_title() == m3.get_title());

    Comparator<Movie>* comp = new CompareDescendingByTitle;

    comparing(repo, comp);
    assert(repo[0].get_title() == m1.get_title());
    assert(repo[1].get_title() == m2.get_title());
    assert(repo[2].get_title() == m3.get_title());

    delete c;
    delete comp;
}