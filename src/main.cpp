#include <iostream>
#include "game.h"
#include "../ext/iniReader/SimpleIni.h"

int main()
{
    CSimpleIniA ini;
    ini.SetUnicode();
    ini.LoadFile("config.ini");
    std::string ipGame = ini.GetValue("GAME", "IP", "");
    int portGame = ini.GetDoubleValue("GAME", "PORT", 0);
    std::string ipNotif = ini.GetValue("NOTIFICATION", "IP", "");
    int portNotif = ini.GetDoubleValue("NOTIFICATION", "PORT", 0);
    if (!portNotif || !portGame || ipNotif.empty() || ipGame.empty())
    {
        std::cout<<"ERROR - ini file had bad parameters"<<std::endl;
        return 0;
    }
    std::cout<<ipGame<<":"<<portGame<<" - "<<ipNotif<<":"<<portNotif<<std::endl;
    game m_game(ipGame, portGame, ipNotif, portNotif);
    m_game.mainLoop();
    return 0;
}
