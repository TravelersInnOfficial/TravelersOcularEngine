#ifndef IODRIVER_H
#define IODRIVER_H
#include <SFML/Graphics.hpp>

class IODriver{
public:
    IODriver();
    ~IODriver();
    bool Update(sf::Event* event);

private:
    bool m_close;
};

#endif