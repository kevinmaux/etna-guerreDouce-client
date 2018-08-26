//other headers
#include "clientZmq.h"

//c++ headers
#include <thread>
#include <chrono>

class game
{
    enum status{
        client_dead,
        client_win,
        cycle_info,
        game_end,
        game_start
    };

public:
    game(std::string ipGame, int portGame, std::string ipNotif, int portNotif);
    ~game();

    void mainLoop();

private:
    void aliveThread();
    void notificationThread();
    bool login();
    void statusManager(int status);

    bool m_gameIsRunning;
    bool m_alive;
    bool m_clientAlive;
    bool m_logged;
    status m_currentStatus;
    clientZmq* mainZmq;
    std::string m_ipNotif;
    int m_portNotif;
};
