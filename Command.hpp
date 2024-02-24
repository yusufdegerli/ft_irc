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


class Command
{
    private:
        std::string buffer;
    public:
        int commandCntl(std::string buffer);
        void commandPass();         //Kullanıcı, sunucunun şifresini girilmesini ister
        void commandUser();         //Kullanıcı adı değiştirme
        void commandNick();         //Takma ad değiştirme
        void commandJoin();         //Kanala katılma
        void commandPrivmsg();      //Kişiye/Kanala özel mesaj atma
        
        void commandMode();         //Kişi ve kanallar için, ünvan değiştirme
        void commandPart();         //Bir kanaldan çıkmaya yarıyor
        void commandTopic();        //Kanalın ismini/konusunu değiştirme
        void commandKick();         //Kişiyi, kanaldan/server'dan atma
        void commandBan();          //Kişiyi, kanaldan/server'dan yasaklama
        void commandList();         //kanalları konularıyla birlikte liseteleme
        void commandWho();          //Kanaldaki kişileri listeleme
        void commandOper();         //Bir kullanıcıya operatör olarak izin veriyorsun
        void commandQuit();         //Kullanıcının sunucudan bağlantısının kopması

};