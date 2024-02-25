#include "Server.hpp"

Server::Server(int port, std::string password)
{
    this->port = port;
    this->password = password;
    this->optv = 1;

    this->server_address.sin_family = AF_INET;
    this->server_address.sin_port = htons(this->port);
    this->server_address.sin_addr.s_addr = INADDR_ANY;
    this->adr_len = sizeof(this->server_address);
}

void pieceByPiece(char *buff, std::vector<std::string> &bufferRaw)
{
    static int information = 1;
    std::string line;
    std::string lastName;
    std::string name;
    std::string ip;
    size_t len;
    std::string user;
    std::string lastStr = "";
    std::istringstream buffer(buff);

    while(std::getline(buffer, line, '\n'))
    {
        bufferRaw.push_back(line);
    }   
    std::string passwd = bufferRaw[0].substr(6, bufferRaw[0].size() -1);
    if (information == 2)
    {
        std::string nick = bufferRaw[1].substr(5, bufferRaw[1].size() -1);
        lastStr = bufferRaw[2];
        lastName = strrchr(lastStr.c_str(), ' ');
        len = lastStr.size() - lastName.size();
        int i = len;
        while(!isdigit(lastStr.c_str()[i]))
            i--;
        name = lastStr.substr(i + 1, len - i - 1);
        int index = lastStr.find(':');
        index -= 2;
        len -= index;
        while(lastStr.c_str()[index] != ' ')
            index--;
        ip = lastStr.substr(index + 1, len - index - 1);
        index--;
        while(lastStr.c_str()[index] != ' ')
            index--;
        user = lastStr.substr(5, index - 5);
        Client kullanici(passwd, nick, user, ip, name, lastName.erase(0, 1));
    }
    information++;
}

void Server :: setServerfd(int server_fd)
{
    this->serverfd = server_fd;

    if (this->serverfd == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
}

void Server :: check_bind_status(int bind_val)
{
    if (bind_val == -1)
    {
        std::cerr << "bind error" << std::endl;
        exit(1);
    }
}

void Server :: check_listen_status(int list_val)
{
    if (list_val == -1)
    {
        std::cerr << "listen error" << std::endl;
        exit(1);
    }
}

void Server :: check_accept_status(int accept_val)
{
    if (accept_val == -1)
    {
        std::cerr << "accept error" << std::endl;
        exit(1);
    }

    this->acc_val = accept_val;
}

void Server :: serverFunc()
{
    int recv_val;
    std::vector<std::string> bufferRaw;
    char buff[1024];

    this->setServerfd(socket(AF_INET, SOCK_STREAM, 0));
    setsockopt(this->serverfd, SOL_SOCKET, SO_REUSEADDR, &this->optv, sizeof(this->optv));

    check_bind_status(bind(this->serverfd, (const sockaddr *)&this->server_address, this->adr_len)); // istenilen soketi, verilen adrese bağlıyor. BU kadar!
    check_listen_status(listen(this->serverfd, 5));//Gelen bağlantıları, bekletir. İkinci parametre kaç tane bağlantının beklemesi gerektiğini söyler.

    std::cout << "Server is listening..." << std::endl;
    check_accept_status(accept(this->serverfd, (sockaddr *)&this->server_address, &this->adr_len));

    while(1)
    {
        char buff[1024] = {0}; // her recv fonksiyonu çalıştığında saçma sapan, ascii dışında karakterler geliyor. Böyle yaparak bunu önlüyorum.
        recv_val = recv(this->acc_val,buff,sizeof(buff), 0);
        if (recv_val == -1)
        {
            std::cerr << "recv error" << std::endl;
            exit(1);
        }
        else
        {
            pieceByPiece(buff, bufferRaw);
            std::cout << "client message: " << buff << std::endl;
        }
    }
    close(this->acc_val);
    close(this->serverfd);
}

Server::~Server(){}
