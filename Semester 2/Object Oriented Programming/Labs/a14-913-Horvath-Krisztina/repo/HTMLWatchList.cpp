#include "HTMLWatchList.h"
#include <fstream>

HTMLWatchList::HTMLWatchList() = default;

HTMLWatchList::~HTMLWatchList() = default;

void HTMLWatchList::write_to_file() {
    std::string file_name = R"(C:\Facultate\OOP\a14-913-Horvath-Krisztina\repo\HTMLWatchList.html)";
    std::ofstream f(file_name, std::ios::trunc);

    if(!f.is_open()){
        std::string error = "\n\tError! Couldn't open watchlist HTML file!\n";
        throw WatchListRepoException(error);
    }

    f << "<!DOCTYPE html>" << "\n";
    f << "<html>" << "\n";

    f << "<head>" << "\n";
    f << "<title>Movie Playlist</title>" << "\n";
    f << "</head>" << "\n";

    f << "<body>" << "\n";

    f << "<table border=\"1\">" << "\n";

    f << "<tr>" << "\n";
    f << "<td>Title</td>" << "\n";
    f << "<td>Genre</td>" << "\n";
    f << "<td>Year</td>" << "\n";
    f << "<td>Likes</td>" << "\n";
    f << "<td>Trailer</td>" << "\n";
    f << "</tr>" << "\n";

    for(const auto& m: this->get_watchlist()){
        f << "<tr>" << "\n";

        f << "<td>" << m.get_title() << "</td>" << "\n";
        f << "<td>" << m.get_genre() << "</td>" << "\n";
        f << "<td>" << m.get_year() << "</td>" << "\n";
        f << "<td>" << m.get_likes() << "</td>" << "\n";
        f << "<td><a href =" << m.get_trailer() << ">Link</a></td>";

        f << "</tr>" << "\n";
    }

    f << "</table>" << "\n";

    f << "</body>" << "\n";

    f << "</html>" << "\n";
    f.close();


}

void HTMLWatchList::open_in_app() {
    std::string link = R"(C:\Facultate\OOP\a14-913-Horvath-Krisztina\repo\HTMLWatchList.html)";
    std::string s = "start " + link;
    system(s.c_str());
}

HTMLWatchList::HTMLWatchList(std::vector<Movie> vector1, int i) : WatchList(vector1, i) {

}
