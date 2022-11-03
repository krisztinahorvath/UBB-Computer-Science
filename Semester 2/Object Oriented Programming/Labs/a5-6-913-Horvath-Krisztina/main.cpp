#include <iostream>
#include "ui/ui.h"
#include "tests/tests.h"

void add_movies_to_repo(Service& serv) {
    serv.add_movie_serv("Hercules", "Animation", 1997, 1796764, "https://www.youtube.com/watch?v=g_Fq2kkqb6c");
    serv.add_movie_serv("Schindler's List", "Biography", 1993, 921634, "https://www.youtube.com/watch?v=M5FpB6qDGAE");
    serv.add_movie_serv("Batman", "Crime", 2022, 1558997, "https://www.youtube.com/watch?v=ewDSeyWve8M");
    serv.add_movie_serv("American Sniper", "Action", 2014, 350230, "https://www.youtube.com/watch?v=99k3u9ay1gs");
    serv.add_movie_serv("Beauty and the Beast", "Romance", 2017, 79791, "https://www.youtube.com/watch?v=e3Nl_TCQXuw");
    serv.add_movie_serv("Frozen", "Animation", 2013, 448325, "https://www.youtube.com/watch?v=TbQm5doF_Uc");
    serv.add_movie_serv("Ghostbusters", "Fantasy", 1984, 22294745,"https://www.youtube.com/watch?v=ahZFCF--uRY");
    serv.add_movie_serv("IT", "Horror", 2017, 951770, "https://www.youtube.com/watch?v=hAUTdjf9rko&t=2s");
    serv.add_movie_serv("Minions", "Animation", 2015, 157889, "https://www.youtube.com/watch?v=SvKmSNxFHyQ");
    serv.add_movie_serv("Corpse Bride", "Animation", 2005, 199731, "https://www.youtube.com/watch?v=AGACeWVdFqo");
}

int main()
{
    {
//        Tests::test_all(); /// todo change update
        Repository repo{};
        Service serv{repo};

        add_movies_to_repo(serv);

        UI ui{serv};
        ui.start();
    }
    return 0;
}
