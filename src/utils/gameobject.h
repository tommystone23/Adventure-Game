#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "logger.h"

class GameObject
{
public:
    GameObject() {}
    ~GameObject() {}

protected:
    void set_identifier(std::string identifier) { _identifier = identifier; }

    virtual Logger info() const;
    virtual Logger warn() const;
    virtual Logger error() const;

private:
    std::string _identifier;
};

#endif //GAMEOBJECT_H