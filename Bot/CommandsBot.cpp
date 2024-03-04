#include "CommandsBot.hpp"

static std::vector<std::string> split(std::string str, char delimeter)
{
	std::vector<std::string> 	r;
	std::stringstream			ss(str);
	std::string					word;

	while (std::getline(ss, word, delimeter))
		r.push_back(word);
	return (r);
}

static std::string trim(const std::string &str, char delimeter) {
    size_t first = str.find_first_not_of(delimeter);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(delimeter);
    return str.substr(first, (last - first + 1));
}

static std::vector<std::string> parser(std::string& buffer)
{
	std::vector<std::string> r;
	std::string	line;
	std::stringstream ss;

	ss << buffer;
	while (std::getline(ss, line))
	{
		line = trim(line, '\r');
		r.push_back(line);
	}
	ss.clear();
	return (r);
}

CommandsBot::CommandsBot(std::string userName, std::string nickName)
:nickName(nickName), userName(userName){
	funcMap["!help"] = &CommandsBot::cmdHelp;
	funcMap["!cmd"] = &CommandsBot::cmdCmd;

	comMap["PASS"] = " :PASS <password>";
	comMap["NICK"] = " :NICK <nickname>";
	comMap["USER"] = " :USER <username> 0 * <realname>";
	comMap["JOIN"] = " :JOIN <channel>{,<channel>} [<key>{,<key>}]";
	comMap["PART"] = " :PART <channel>{,<channel>}";
	comMap["QUIT"] = " :QUIT [<reason>]";
	comMap["TOPIC"] = " :TOPIC <channel> [<topic>]";
	comMap["PRIVMSG"] = " :PRIVMSG <target>{,<target>} <text to be sent>";
	comMap["MODE"] = " :MODE <target> [<modestring> [<mode arguments>...]]";
	comMap["LIST"] = " :LIST [<channel>{,<channel>}]";
	comMap["NAMES"] = " :NAMES <channel>{,<channel>}";
	comMap["INVITE"] = " :INVITE <nickname> <channel>";
	comMap["WHO"] = " :WHO <nickname>";
	comMap["KICK"] = " :KICK <channel> <user> *( \",\" <user> ) [<comment>]";
}

CommandsBot::~CommandsBot(){

}

void	CommandsBot::runComs(std::string coms){
	parsed = parser(coms);
	for (size_t i = 0; i < parsed.size(); i++)
	{
		splitted = split(parsed[i], ' ');
		if (splitted.size() < 4)
			continue ;
		if (splitted[1] == "PRIVMSG"){
			std::map<std::string, void (CommandsBot::*)()>::iterator it = this->funcMap.find(splitted[3].erase(0, 1));
			if (it != this->funcMap.end()) {
					(this->*(it->second))();
			}else{
				std::cout << "Command not found!" << std::endl;
			}
		}
	}
}

void	CommandsBot::cmdCmd(){
	std::string msg = "";
	if (splitted.size() < 5){
		msg = "PRIVMSG " + parseSenderName() + " :Missing argument!\r\n";
		send(_socket, msg.c_str(), msg.length(), 0);
		return;
	}
	transform(splitted[4].begin(), splitted[4].end(), splitted[4].begin(), ::toupper);
	std::map<std::string,std::string>::iterator it = this->comMap.find(splitted[4]);
	if (it != this->comMap.end())
		msg = "PRIVMSG " + parseSenderName() + it->second;
	else
		msg = "PRIVMSG " + parseSenderName() + " :Wrong command (" + splitted[4] + ")\r\n";
	send(_socket, msg.c_str(), msg.length(), 0);
}

std::string CommandsBot::parseSenderName(){
	size_t idx = splitted[0].find('!');
	if (idx != std::string::npos)
		return std::string(splitted[0].substr(1, idx - 1));
	return (NULL);
}

void	CommandsBot::cmdHelp(){
	std::string msg = "PRIVMSG " + parseSenderName() + " :Usage: !cmd <COMMAND NAME>\r\n";
	send(_socket, msg.c_str(), msg.length(), 0);
	msg = "PRIVMSG " + parseSenderName() + " :<COMMAND NAME>: PRIVMSG, MODE, PASS, NICK, USER, JOIN, PART,\
 QUIT, TOPIC, LIST, NAMES, INVITE, WHO, KICK\r\n";
	send(_socket, msg.c_str(), msg.length(), 0);
}


//SET FUNCS
void	CommandsBot::setSocket(int socket){ this->_socket = socket; }

//GET FUNCS
int	CommandsBot::getSocket() const { return (_socket); }
