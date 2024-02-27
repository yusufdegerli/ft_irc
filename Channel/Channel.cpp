#include "Channel.hpp"

Channel::Channel()
{
    this->key_required = false;
    this->name = "";
    this->topic = "";
}

Channel::Channel(std::string const &name)
{
    this->key_required = false;
    this->name = name;
    this->topic = "";
}

Channel::Channel(Channel const &cpy)
{
    this->key_required = cpy.key_required;
    this->members = cpy.members;
    this->name = cpy.name;
    this->topic = cpy.topic;
}

Channel::~Channel(){}

std::string Channel::getName(){return this->name;}

void    Channel::addToMembers(Client const &New){ this->members.push_back(New);}