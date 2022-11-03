//#include "tests.h"
//#include <assert.h>
//#include "repo/repository.h"
//#include "domain/DynamicVector.h"
//#include "service/services.h"
//
//void Tests::test_all()
//{
//    test_movie();
//    test_dynamic_vector();
//    test_repo();
//    test_service();
//    test_watchlist();
//}
//
//void Tests::test_movie() {
//    Movie m = Movie("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(m.get_title() == "Batman");
//    assert(m.get_genre() == "Crime");
//    assert(m.get_year() == 2022);
//    assert(m.get_likes() == 1558997);
//    assert(m.get_trailer() == "https://www.youtube.com/watch?v=ewDSeyWve8M");
//
//    Movie m1 = Movie("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(m.operator==(m1) == true);
//    m1 = Movie("Batman", "Crime", 2021, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(m.operator==(m1) == false);
//
//    m.play_trailer();
//}
//
//void Tests::test_dynamic_vector() {
//    DynamicVector<int> v1{2};
//    v1.add(10);
//    v1.add(20);
//    assert(v1.get_size() == 2);
//    assert(v1.get_elem(0) == 10);
//    v1.add(30);
//    assert(v1.get_size() == 3);
//    DynamicVector<int> v2 = v1;
//    assert(v2.get_size() == 3);
//
//    DynamicVector<int> v3 = v1;
//    assert(v3.get_elem(0) == 10);
//
//    v3.remove(1);
//    assert(v3.get_elem(1) == 30);
//
//    v2.update(2, 40);
//    assert(v2.get_elem(2) == 40);
//}
//
//void Tests::test_repo() {
//    Repository repo = Repository();
//    Movie m1 = Movie("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    repo.add_movie(m1);
//    int pos = repo.find_movie("Batman", "Crime", 2022);
//    assert(pos != -1);
//
//    m1 = Movie("Batman", "Crime", 2022, 15997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    repo.update_movie(m1);
//
//    DynamicVector<Movie> movies = repo.get_movies();
//    assert(movies.get_size() == 1);
//    assert(movies.get_elem(0).get_likes() == 15997);
//    repo.remove_movie(m1);
//
//    DynamicVector<Movie> empty_movies = repo.get_movies();
//    assert(empty_movies.get_size() == 0);
//
//    repo.add_movie(m1);
//    assert(repo.add_movie(m1) == 0);
//    pos = repo.find_movie("Catwoman", "Crime", 2011);
//    assert(pos == -1);
//
//    m1 = Movie("Catwoman", "Crime", 2011, 15997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(repo.update_movie(m1) == 0);
//    Movie m2 = Movie("Hercules", "Animation", 1997, 1796764, "https://www.youtube.com/watch?v=g_Fq2kkqb6c");
//    assert(repo.remove_movie(m2) == 0);
//}
//
//void Tests::test_service() {
//    Repository repo = Repository();
//    Service serv = Service(repo);
//
//    serv.add_movie_serv("Hercules", "Animation", 1997, 1796764, "https://www.youtube.com/watch?v=g_Fq2kkqb6c");
//    serv.add_movie_serv("Schindler's List", "Biography", 1993, 921634, "https://www.youtube.com/watch?v=M5FpB6qDGAE");
//    serv.add_movie_serv("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//
//    serv.remove_movie_serv("Schindler's List", "Biography", 1993);
//    serv.update_movie_serv("Batman", "Crime", 2022, 58997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//
//    std::string nr = "1579";
//    assert(serv.convert_to_int(nr) == 1579);
//    nr = "1579-";
//    assert(serv.convert_to_int(nr) == -1);
//
//
//    DynamicVector<Movie> movies = serv.get_all_movies();
//    assert(movies.get_size() == serv.get_repo().get_movies().get_size());
//
//    DynamicVector<Movie> watchlist = serv.get_all_watchlist();
//    assert(watchlist.get_size() == serv.get_all_watchlist().get_size());
//
//    Repository rw = Repository();
//    Service s = Service(rw);
//    Movie m1 = Movie("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(s.add_watchlist_serv(m1) == 1);
//    assert(s.remove_watchlist_serv("Batman", "Crime", 2022) == 1);
//    assert(s.add_watchlist_serv(m1) == 1);
//
//    Movie m2 = Movie("Hercules", "Animation", 1997, 1796764, "https://www.youtube.com/watch?v=g_Fq2kkqb6c");
//
//    s.add_watchlist_serv(m2);
//    Movie m3 = Movie("Minions", "Animation", 2015, 157889, "https://www.youtube.com/watch?v=SvKmSNxFHyQ");
//    s.add_watchlist_serv(m3);
//    DynamicVector<Movie> w = s.get_all_movies();
//    WatchList w1 = s.display_by_genre_serv("");
//    for(int i = 0; i < s.get_all_watchlist().get_size(); i++){
//        assert(w1.get_current() == w.get_elem(i));
//        w1.next();
//    }
//
//    WatchList w2 = s.display_by_genre_serv("Animation");
//
//    Repository rr = Repository();
//    Service srr = Service(rr);
//
//    Movie mm1 = Movie("American Sniper", "Action", 2014, 350230, "https://www.youtube.com/watch?v=99k3u9ay1gs");
//    assert(srr.add_watchlist_serv(mm1) == 1) ;
//    assert(srr.add_movie_serv("American Sniper", "Action", 2014, 350230, "https://www.youtube.com/watch?v=99k3u9ay1gs") == 1);
//
//    Movie mm2 = Movie("Beauty and the Beast", "Romance", 2017, 79791, "https://www.youtube.com/watch?v=e3Nl_TCQXuw");
//    assert(srr.add_watchlist_serv(mm2) == 1) ;
//    assert(srr.add_movie_serv("Beauty and the Beast", "Romance", 2017, 79791, "https://www.youtube.com/watch?v=e3Nl_TCQXuw") == 1);
//
//    WatchList ww1 = srr.display_by_genre_serv("Romance");
//    assert(ww1.get_size() == 1);
//
//    assert(srr.like_movie_serv("Beauty and the Beast", "Romance", 2017) == 1);
//    Movie like_mm2 = Movie("Beauty and the Beast", "Romance", 2017, 79792, "https://www.youtube.com/watch?v=e3Nl_TCQXuw");
//    assert(srr.get_all_movies().get_elem(1) == like_mm2);
//
//    WatchList ww2 = srr.display_by_genre_serv("");
//    assert(ww2.get_size() == 2);
//    assert(ww2.find_movie_by_info("Beauty and the Beast", "Romance", 2017) == like_mm2);
//    assert(ww2.find_movie_by_info("American Sniper", "Action", 2014) == mm1);
//}
//
//void Tests::test_watchlist() {
//    WatchList w = WatchList();
//
//    assert(w.get_size() == 0);
//
//    assert(w.is_empty() == true);
//    w.play_trailer_serv();
//    Movie m1 = Movie("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(w.add_watchlist(m1) == 1);
//    assert(w.add_watchlist(m1) == 0);
//    assert(w.is_empty() == false);
//
//    assert(w.remove_watchlist(m1) == 1);
//    assert(w.remove_watchlist(m1) == 0);
//
//    assert(w.add_watchlist(m1) == 1);
//    Movie m2 = Movie("Catwoman", "Crime", 2011, 15997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
//    assert(w.add_watchlist(m2) == 1);
//    w.next();
//    assert(w.get_current() == m2);
//    assert(w.find_movie_by_info("Catwoman", "Crime", 2011) == m2);
//
//    WatchList w1 = WatchList();
//    assert(w1.add_watchlist(m1) == 1);
//    w1.next();
//
//
//    Movie m = Movie("", "", 0, 0, "");
//    assert(w.find_movie_by_info("CC", "aaa", 1000) == m);
//
//    w.play_trailer_serv();
//}
//
//
