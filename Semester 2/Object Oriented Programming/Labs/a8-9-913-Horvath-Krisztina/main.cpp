#include <iostream>
#include <fstream>
#include "ui/ui.h"
#include "CSVWatchList.h"
#include "HTMLWatchList.h"
#include "Comparator.h"
//#include <memory>


int main()
{
    {
        std::cout << "Test comparator: \n";
        test_compare();
        std::cout << "test finished\n";
        std::string type;


        std::cout << "\n\tChoose file type(csv or html): ";
        std::getline(std::cin, type);
        if (type == "exit")
            return 0;
        if (type == "csv" || type == "html")  ///todo use <memory>
        {
            Repository* admin_repo = new Repository();
            admin_repo->read_from_file();

            WatchList* user_repo;
            if (type == "csv")
                user_repo = new CSVWatchlist(); /// todo watchlist is empty
            else
                user_repo = new HTMLWatchList();

            Service* admin_ctrl = new Service{ *admin_repo, user_repo};
            UI* console = new UI(*admin_ctrl, user_repo);

            console->start();

            delete console;
            delete admin_ctrl;
            delete user_repo;
            delete admin_repo;
        }
    }
    return 0;
}