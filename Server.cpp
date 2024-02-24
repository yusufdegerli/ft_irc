#include "Server.hpp"

Server::Server(int port, std::string password)
{
    this->port = port;
    this->password = password;
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


void serverFunc(){
    int serverfd;
    sockaddr_in server_address;
    int bind_val;
    int list_val;
    int accept_val;
    int recv_val;
    std::vector<std::string> bufferRaw;
    char buff[1024];

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int optval = 1;         /* BU İKİ SATIRI YORUMA ALMAYI UNUTMAYIN AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA */
    setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6667);
    server_address.sin_addr.s_addr = INADDR_ANY;
    bind_val = bind(serverfd, (const sockaddr *)&server_address, sizeof(server_address)); // istenilen soketi, verilen adrese bağlıyor. BU kadar!
    if (bind_val == -1)
    {
        std::cerr << "bind error" << std::endl;
        exit(1);
    }
    list_val = listen(serverfd, 5);//Gelen bağlantıları, bekletir. İkinci parametre kaç tane bağlantının beklemesi gerektiğini söyler.
    if (list_val == -1)
    {
        std::cerr << "listen error" << std::endl;
        exit(1);
    }
    std::cout << "server is listening" << std::endl;
    socklen_t len = sizeof(server_address); 
    accept_val = accept(serverfd, (sockaddr *)&server_address, &len);
    if (accept_val == -1)
    {
        std::cerr << "accept error" << std::endl;
        exit(1);
    }
    while(1)
    {
        char buff[1024] = {0}; // her recv fonksiyonu çalıştığında saçma sapan, ascii dışında karakterler geliyor. Böyle yaparak bunu önlüyorum.
        recv_val = recv(accept_val,buff,sizeof(buff), 0);
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
    close(accept_val);
    close(serverfd);
}

Server::~Server(){}
