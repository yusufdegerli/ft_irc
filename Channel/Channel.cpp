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

std::vector<Client> Channel::getMembers(){return this->members;}
std::vector<Client> Channel::getOperators(){return this->Operators;}

bool Channel::getKeyRequired(){return this->key_required;}
bool Channel::getInviteOnly(){return this->invite_only;}

std::string Channel::getKey(void){return this->key;}

void Channel::addToMembers(Client const &New){ this->members.push_back(New);}
void Channel::addToOperators(Client const &New){ this->Operators.push_back(New);}
