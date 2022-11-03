#include <fstream>
#include <utility>
#include "CSVWatchList.h"

CSVWatchlist::CSVWatchlist() {

}


CSVWatchlist::~CSVWatchlist() = default;

void CSVWatchlist::write_to_file() {
    std::string file_name = R"(C:\Facultate\OOP\a8-9-913-Horvath-Krisztina\repo\CSVWatchList)";
    std::ofstream f(file_name, std::ios::trunc);
    if(!f.is_open()){
        std::string error = "\n\tError! Couldn't open watchlist CSV file!\n";
        throw WatchListRepoException(error);
    }
    for(auto m: this->get_watchlist())
        f << m << "\n";
    f.close();

}

void CSVWatchlist::open_in_app() {
    std::string file_name = R"(C:\Facultate\OOP\a8-9-913-Horvath-Krisztina\repo\CSVWatchList)";
    std::string cmd = "notepad.exe " + file_name;
    system(cmd.c_str());
}

CSVWatchlist::CSVWatchlist(std::vector<Movie> vector1, int i) : WatchList(std::move(vector1), i) {

}
