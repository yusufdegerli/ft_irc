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

void pieceByPiece(char *buff, std::vector<std::string> &bufferRaw, Client *New)
{
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
    if (New->getInformation() == 2 && bufferRaw.empty())
    {
        New->setUsrPass(bufferRaw[0].substr(6, bufferRaw[0].size() -1));
        New->setUsrNick(bufferRaw[1].substr(5, bufferRaw[1].size() -1));
        lastStr = bufferRaw[2];
        lastName = strrchr(lastStr.c_str(), ' ');
        New->setUsrSurname(lastName.erase(0,1));
        len = lastStr.size() - lastName.size();
        int i = len;
        while(!isdigit(lastStr.c_str()[i]))
            i--;
        New->setUsrName(lastStr.substr(i + 1, len - i - 1));
        int index = lastStr.find(':');
        index -= 2;
        len -= index;
        while(lastStr.c_str()[index] != ' ')
            index--;
        New->setHostname(lastStr.substr(index + 1, len - index));
        index--;
        while(lastStr.c_str()[index] != ' ')
            index--;
        New->setUsrUser(lastStr.substr(5, index - 5));
        //Client kullanici(passwd, nick, user, ip, name, lastName.erase(0, 1));
    }
    New->setInformation(New->getInformation() + 1);
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
    sockaddr_in client_address;

    this->setServerfd(socket(AF_INET, SOCK_STREAM, 0));
    setsockopt(this->serverfd, SOL_SOCKET, SO_REUSEADDR, &this->optv, sizeof(this->optv));

    check_bind_status(bind(this->serverfd, (const sockaddr *)&this->server_address, this->adr_len)); // istenilen soketi, verilen adrese bağlıyor. BU kadar!
    check_listen_status(listen(this->serverfd, 5));//Gelen bağlantıları, bekletir. İkinci parametre kaç tane bağlantının beklemesi gerektiğini söyler.

    std::cout << "Server is listening..." << std::endl;
    // struct pollfd *fds = new pollfd();
    struct pollfd tmp;
	this->fds.push_back(tmp);
    this->fds[0].fd = this->serverfd;
    this->fds[0].events = POLLIN;
    while(1)
    {
        int poll_status = poll(&(this->fds[0]), this->fds.size(), -1);// Süresiz bekleyin
        if (poll_status == -1) {
            perror("Poll error");
            exit(EXIT_FAILURE);
        }
        if (this->fds[0].revents & POLLIN) {
            socklen_t len = sizeof(client_address);
            check_accept_status(accept(serverfd, (sockaddr *)&client_address, &len));
            Client tmp;
            tmp.setInformation(1);
            tmp.setSocket(this->acc_val);
            unsigned long clientAddr = ntohl(client_address.sin_addr.s_addr);
            std::string clientIP = std::to_string((clientAddr >> 24) & 0xFF) + "." + std::to_string((clientAddr >> 16) & 0xFF) + "." + std::to_string((clientAddr >> 8) & 0xFF) + "." + std::to_string(clientAddr & 0xFF);
            tmp.setRealIp(clientIP);
            this->clients.push_back(tmp);
            struct pollfd tmp2;
			this->fds.push_back(tmp2);
			this->fds.at(this->fds.size() - 1).fd = this->acc_val;
			this->fds.at(this->fds.size() - 1).events = POLLIN;

        }
        for (size_t i = 1; i < this->fds.size(); i++)
        {
            if (this->fds[i].fd != -1 && this->fds[i].revents & POLLIN) {
                char buff[1024] = {0}; // her recv fonksiyonu çalıştığında saçma sapan, ascii dışında karakterler geliyor. Böyle yaparak bunu önlüyorum.
                recv_val = recv(this->fds[i].fd, buff, sizeof(buff), 0);
                if (recv_val <= 0)
                {
                    //recv okuma yapamazsa veya client bağlantıyı kopardıysa buraya giriyor.
                    std::cerr << "recv error" << std::endl;
                    exit(1);
                }
                else
                {
                    //int j = 0;
                    std::cout << this->clients[i - 1].getInformation() << std::endl;
                    pieceByPiece(buff, bufferRaw, &this->clients[i - 1]);
                    std::cout << "client message: " << buff << std::endl;
                }
            
            }
        }

    }
    close(this->acc_val);
    close(this->serverfd);
}

Server::~Server(){}
