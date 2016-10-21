/*
* File:   kcpsession.h
* Author: axiezhou
*
* Created on 2016/10/20
*/

#ifndef __KCPSESSION_H__
#define __KCPSESSION_H__

#include <arpa/inet.h>

#include "ikcp.h"

struct KCPAddr
{
    KCPAddr(const sockaddr_in& sockaddr, socklen_t sock_len) :
        sockaddr(sockaddr), sock_len(sock_len){}
    sockaddr_in sockaddr;
    socklen_t sock_len;
};

class KCPServer;
class KCPSession;

KCPSession* NewKCPSessison(KCPServer* server, const KCPAddr& addr, int conv, IUINT64 current);

class KCPSession
{
public:
    KCPSession(KCPServer* server, const KCPAddr& addr, IUINT64 current);
    ~KCPSession();

    void Update(IUINT32 current);
    int Send(const char* data, int len);
    IUINT64 LastActiveTime() const;
    void SetKCP(ikcpcb* kcp);
public:
    void KCPInput(const sockaddr_in& sockaddr, const socklen_t socklen, const char* data, long sz, 
        IUINT64 current);
    void Output(const char* buf, int len);

private:
    ikcpcb* kcp_;
    KCPServer* server_;
    KCPAddr addr_;
    IUINT64 last_active_time_;
};


#endif