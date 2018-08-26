//zmq headers
#include <zmq.hpp>

//c++ headers
#include <iostream>
#include <string>

class clientZmq
{
public:
    clientZmq(std::string ip, int port, int type);
    ~clientZmq();

    bool sender(std::string message);
    std::string receiver();

private:
    zmq::context_t* context;
    zmq::socket_t* socket;

    //socket info
    std::string m_ip;

};
