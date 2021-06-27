#include "../inc/stozek.hh"
#define WZORZEC_STOZEK "../BrylyWzorcowe/szescianUP.dat"
#define FOLDER_ROBOCZY "../datasets/"

void stozek::InfoObiektu()
{
    std::cout << "Pozycja Gory z ostrym szczytem:" << daj_trans() << std::endl;
}

bool stozek::Zbudujstozek()
{
    std::string NazwaPlikuWyjsciowego;
    NazwaPlikuWyjsciowego = "../BrylyWzorcowe/Gora_" + std::to_string(NumerBryly) + ".dat";
    pobierz_nazwe_final(NazwaPlikuWyjsciowego);
    pobierz_nazwe_wzorca(WZORZEC_STOZEK);

    std::ifstream IN(daj_wzorcowego());
    std::ofstream OUT(daj_wyjsciowego());
    vector3d PomVek;

    if (!IN.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: " << daj_wzorcowego() << std::endl
                  << std::endl;
        return false;
    }

    if (!OUT.is_open())
    {
        std::cerr << std::endl
                  << " Blad otwarcia do odczytu pliku: " << daj_wyjsciowego() << std::endl
                  << std::endl;
        return false;
    }

    for (int index_up = 0; index_up < 5; ++index_up)
    {
        for (int index = 0; index < 4; ++index)
        {
            if (PomVek[2] > 0.5)
            {
                PomVek[0] = PomVek[1] = 0;
            }
            else if (PomVek[2] == 0.5)
            {
                PomVek[0] /= 2;
                PomVek[1] /= 2;
            }
            skaluj(PomVek);
            TransformujWspolrzednePunktu(PomVek);
            OUT << PomVek;
            IN >> PomVek;
            OUT << std::endl;
        }
        OUT << std::endl;
    }

    return !OUT.fail();
}
