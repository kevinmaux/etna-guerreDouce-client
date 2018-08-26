#include "game.h"

game::game(std::string ipGame, int portGame, std::string ipNotif, int portNotif)
{
       mainZmq = new clientZmq(ipGame, portGame, ZMQ_REQ);
       m_ipNotif = ipNotif;
       m_portNotif = portNotif;
}
game::~game()
{
}

void game::statusManager(int status)
{
    switch (status)
    {
    case game_start:
        m_gameIsRunning = true;
        m_clientAlive = true;
        std::cout<<"INFO - Game Start"<<std::endl;
        break;
    case game_end:
        m_gameIsRunning = false;
        std::cout<<"INFO - Game Finish"<<std::endl;
    case client_dead:
        m_clientAlive = false;
        std::cout<<"INFO - Client dead"<<std::endl;
        break;
    case client_win:
        std::cout<<"INFO - Client won"<<std::endl;
    default:
        std::cout<<"INFO - New loop"<<std::endl;
        if (m_clientAlive)
        {
            //action
        }
        break;
    }
}
bool game::login()
{
    std::string data = "";
    do
    {
        if (!mainZmq->sender("identify"))
            return false;
        data = mainZmq->receiver();
        if (data.find("ok") != std::string::npos)
            m_logged = true;
    }
    while(!m_logged);

    return m_logged;
}
void game::aliveThread()
{
    while(m_alive)
    {
        if (mainZmq->sender("heartbeats"))
        {
            if (mainZmq->receiver().find("ok") == std::string::npos)
                m_alive = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}
void game::notificationThread()
{
    clientZmq notificationZmq(m_ipNotif, m_portNotif, ZMQ_SUB);
    std::string data = "";
    while (m_alive)
    {
        data = notificationZmq.receiver();
    }
}
void game:: mainLoop()
{
    m_alive = true;
    std::thread alive(&game::aliveThread, this);
    while (m_alive)
    {
        if (!m_logged)
        {
            if(!login())
                return;
           std::thread notification(&game::notificationThread, this);
        }
        statusManager(m_currentStatus);
        if (m_currentStatus == game_end)
            return;
    }
}
