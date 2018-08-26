#include "clientZmq.h"

clientZmq::clientZmq(std::string ip, int port, int type)
{
    m_ip = std::string("tcp://"+ip+":"+std::to_string(port));

    context = new zmq::context_t(1);
    socket = new zmq::socket_t(*context, type);
    socket->connect(ip);
}
clientZmq::~clientZmq()
{
    socket->disconnect(m_ip);
    socket->close();
    context->close();
}

bool clientZmq::sender(std::string message)
{
    zmq::message_t data(message.size());
    memcpy(data.data(), message.data(), message.size());
    if (socket->send(data))
        return true;
    std::cout<<"ERROR - can't send message : \n"<<message<<std::endl;
    return false;
}
std::string clientZmq::receiver()
{
    zmq::message_t data;
    socket->recv(&data);
    return std::string(static_cast<char*>(data.data()));
}
