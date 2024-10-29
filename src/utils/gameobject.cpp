#include "gameobject.h"

Logger GameObject::info() const
{
    return Logger() << "INFO: ";
}

Logger GameObject::warn() const
{
    return Logger() << "WARN: ";
}

Logger GameObject::error() const
{
    return Logger() << "ERROR: ";
}