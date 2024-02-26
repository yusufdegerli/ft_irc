#pragma once
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <vector>
#include <poll.h>

class Server;

class Command
{
    private:
        std::string buffer;
    public:
        int commandCntl(std::string commandline, int acc_val);
        void commandPass(std::string commandline, int acc_val);         //Kullanıcı, sunucunun şifresini girilmesini ister
        void commandUser(std::string commandline, int acc_val);         //Kullanıcı adı değiştirme
        void commandNick(std::string commandline, int acc_val);         //Takma ad değiştirme
        void commandJoin(std::string commandline, int acc_val);        //Kanala katılma
        void commandPrivmsg(std::string commandline, int acc_val);      //Kişiye/Kanala özel mesaj atma
        
        void commandMode(std::string commandline, int acc_val);         //Kişi ve kanallar için, ünvan değiştirme
        void commandPart(std::string commandline, int acc_val);         //Bir kanaldan çıkmaya yarıyor
        void commandTopic(std::string commandline, int acc_val);        //Kanalın ismini/konusunu değiştirme
        void commandKick(std::string commandline, int acc_val);         //Kişiyi, kanaldan/server'dan atma
        void commandBan(std::string commandline, int acc_val);          //Kişiyi, kanaldan/server'dan yasaklama
        void commandList(std::string commandline, int acc_val);         //kanalları konularıyla birlikte liseteleme
        void commandWho(std::string commandline, int acc_val);          //Kanaldaki kişileri listeleme
        void commandOper(std::string commandline, int acc_val);         //Bir kullanıcıya operatör olarak izin veriyorsun
        void commandQuit(std::string commandline, int acc_val);         //Kullanıcının sunucudan bağlantısının kopması

        void runCommands(std::string buffer, void func());

};