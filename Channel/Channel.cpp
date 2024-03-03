#include "Channel.hpp"

Channel::Channel()
{
    this->key_required = false;
    this->name = "";
    this->key = "";
    this->topic = "";
}

// Channel::Channel(std::string const &name)
// {
//     this->key_required = false;
//     this->name = name;
//     this->topic = "";
// }

Channel::Channel(std::string name)
{
    this->key_required = false;
    this->name = name;
    this->key = "";
    this->topic = "";
}
Channel::Channel(std::string name, std::string key)
{
    this->key_required = true;
    this->name = name;
    this->key = key;
    this->topic = "";
    std::cout << "key: " << this->key << " name: " << this->name << std::endl;
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
bool Channel::getSecretChan(){return this->secret_chan;}

std::string &Channel::getKey(void){return this->key;}
std::string &Channel::getTopic(void){return this->topic;}

void Channel::addToMembers(Client const &New)
{
    Client client = New;
    this->members.push_back(client);
}
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

/* void Channel::writeMembersByName(std::vector<Client> members)
{
    std::cout << "üst\n";
    std::cout << "size: " << members.size() << std::endl;
    for (size_t m = 0; m < members.size(); m++)
        std::cout << members[m].getName() << std::endl;
    std::cout << "alt\n";
} */

