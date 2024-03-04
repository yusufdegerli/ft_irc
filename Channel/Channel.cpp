#include "Channel.hpp"

Channel::Channel()
{
    this->topic = "";
    this->name = "";
    this->key = "";
    this->key_required = false;
    this->invite_only = false;
}

Channel::Channel(std::string name)
{
    this->topic = "";
    this->name = name;
    this->key = "";
    this->key_required = false;
    this->invite_only = false;
}
Channel::Channel(std::string name, std::string key)
{
    this->topic = "";
    this->name = name;
    this->key = key;
    this->key_required = true;
    this->invite_only = false;
}


Channel::Channel(Channel const &cpy)
{
     this->topic = cpy.topic;
    this->name = cpy.name;
    this->Operators = cpy.Operators;
    this->members = cpy.members;
    this->key = cpy.key;
    this->key_required = cpy.key_required;
    this->invite_only = cpy.invite_only;
}

void    Channel::operator=(Channel const &cpy)
{
    this->topic = cpy.topic;
    this->name = cpy.name;
    this->Operators = cpy.Operators;
    this->members = cpy.members;
    this->key = cpy.key;
    this->key_required = cpy.key_required;
    this->invite_only = cpy.invite_only;
}

Channel::~Channel(){}

std::string Channel::getName(){return this->name;}

std::vector<Client> &Channel::getMembers(){return this->members;}
std::vector<Client> &Channel::getOperators(){return this->Operators;}

bool Channel::getKeyRequired(){return this->key_required;}
bool Channel::getInviteOnly(){return this->invite_only;}

std::string &Channel::getKey(void){return this->key;}
std::string &Channel::getTopic(void){return this->topic;}

void Channel::addToMembers(Client const &New){this->members.push_back(New);}
void Channel::addToOperators(Client const &New){ this->Operators.push_back(New);}

bool Channel :: checkMembers(Client const &New)
{
    for (size_t i = 0; i < this->members.size(); i++)
    {
        if (this->members[i].getNick() == New.getNick())
            return true;
    }
    return false;
}

bool Channel :: checkOperators(Client const &New)
{
    for (size_t i = 0; i < this->Operators.size(); i++)
    {
        if (this->Operators[i].getNick() == New.getNick())
            return true;
    }
    return false;
}


void Channel :: printMembers()
{
    for (size_t i = 0; i < this->members.size(); i++)
    {
        std::cout << this->members[i].getNick() << std::endl;
    }
}

void Channel :: setTopic(std::string topic){this->topic = topic;}


