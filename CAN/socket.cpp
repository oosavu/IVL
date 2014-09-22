#include "socket.h"

Socket::Socket()
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    if((sock=socket(PF_CAN,SOCK_RAW,CAN_RAW))<0)
    {
        qDebug()<<"not may connect to socket";
    }

    addr.can_family=AF_CAN;
    memcpy(ifr.ifr_ifrn.ifrn_name ,"can0\0\0\0\0\0\0\0\0\0\0\0",16);
    if(ioctl(sock,SIOCGIFINDEX, &ifr)<0)
    {
        qDebug()<<"not may ioctl";
    }
    //setsockopt(sock,SOL_CAN_RAW,CAN_RAW_FILTER,&rfilter,sizeof(rfilter));

    addr.can_ifindex=ifr.ifr_ifindex;
    if(bind(sock,(struct sockaddr *)&addr,sizeof(addr))<0)
    {
        qDebug()<<"not may connect to socket";
    }
    qDebug()<<"init socket";
}

void Socket::writeMsg(const CanMessage &msg)
{
    int nbytes;
    frame.can_id = msg.id;
    frame.can_dlc = msg.lenght;
    memcpy(frame.data,msg.data,8);
 //   qDebug()<<"attempt send CANPKG: " +  tmpMsg.toString();
    nbytes = write(sock,&frame,sizeof(struct can_frame));
    if(nbytes!=sizeof(struct can_frame))
    {
       qDebug()<<"socket writing error! nbytes = " + QString::number(nbytes);
    }
    else
    {
       // qDebug()<<"msg sending!" << tmpMsg.toString();
    }
}

void /*CanMessage*/ Socket::readMsg()
{
    int nbytes;
   // CanMessage msg;
    nbytes=read(sock,&frame,sizeof(struct can_frame));
    if(nbytes != sizeof(struct can_frame))
    {
        qDebug()<<"socket reading error! nbytes = " + QString::number(nbytes);
    }
    lastMsg.id = frame.can_id;
    lastMsg.lenght = frame.can_dlc;
    memcpy(lastMsg.data,frame.data,8);
    //return msg;
}
