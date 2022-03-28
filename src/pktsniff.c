#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "ether.h" 
#include "ip.h"

/* All hail our overlord IEEE */

/*
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |Version|  IHL  |Type of Service|          Total Length         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |         Identification        |Flags|      Fragment Offset    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |  Time to Live |    Protocol   |         Header Checksum       |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                       Source Address                          |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Destination Address                        |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                    Options                    |    Padding    |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/


struct  __attribute__((packed)) ip4fullpkt {
struct ether_hdr eth;
struct ip4_hdr   ip;
};




int main(){
    int packnum=-1;
    setvbuf(stdout, NULL, _IONBF, 0);
    struct  ip4fullpkt *xyz;
    unsigned char* buf = (unsigned char*)malloc(1514);
    int fd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
    if(fd<0){exit(EXIT_FAILURE);}
    struct ifreq ifopts;
    char *intrf = "wlp0s20f3";
    int len = strlen(intrf);
    strncpy(ifopts.ifr_name, intrf, IFNAMSIZ-1);
    ioctl(fd, SIOCGIFFLAGS, &ifopts);
    ifopts.ifr_flags |= IFF_PROMISC;
    ioctl(fd, SIOCSIFFLAGS, &ifopts);

if ((setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, intrf, len))== -1){
		perror("SO_BINDTODEVICE");
		pclose(fd);
		exit(EXIT_FAILURE);
}printf("stat :");
while(1){
   ++packnum;
   int siz= recvfrom(fd, buf, ETH_FRAME_LEN, 0, NULL, NULL);
   if(siz<0){
        printf("fatal error pktnum %d",packnum);
        continue;}
   if(siz>1514){
        printf("packet size exceeded hence dropped");
        continue;}
   if(buf[12]==0x08 && buf[13]==0x00){
   xyz = (struct ip4fullpkt *)buf;
   unsigned short DSCP=(xyz->ip.qos)>>2,ECN=(xyz->ip.qos & 252 );
   printf("\nnumber=%d|size=%d|dmac=%.2X%.2X:%.2X%.2X:%.2X%.2X|smac=%.2X%.2X:%.2X%.2X:%.2X%.2X\n",packnum,siz,xyz->eth.dest_mac[0],xyz->eth.dest_mac[1],xyz->eth.dest_mac[2],xyz->eth.dest_mac[3],xyz->eth.dest_mac[4],xyz->eth.dest_mac[5],xyz->eth.src_mac[0],xyz->eth.src_mac[1],xyz->eth.src_mac[2],xyz->eth.src_mac[3],xyz->eth.src_mac[4],xyz->eth.src_mac[5]);
   printf(" \nVERSION -> %hu",xyz->ip.version);
   printf(" \nIHL -> %hu",xyz->ip.IHL);
   printf(" \nDSCP -> %hu",DSCP); //
   printf(" \nECN -> %hu",ECN); //
   printf(" \nRBIT -> %hu",0);
   printf(" \nDF -> %hu",(xyz->ip.fragmentdat[0] & 0x40 )>>6);
   printf(" \nMF -> %hu",(xyz->ip.fragmentdat[0] & 0x20 )>>5);
   printf(" \nFragment offset -> %hu",(xyz->ip.fragmentdat[0] & 31 )+xyz->ip.fragmentdat[1]);
   printf(" \nTOTAL LENGTH -> %hu",xyz->ip.tot_len[0]+xyz->ip.tot_len[1]);
   printf(" \nIDENTIFICATION -> %.2X%.2X",xyz->ip.Identification[0],xyz->ip.Identification[1]);
   printf(" \nTTL -> %hu",xyz->ip.TTL);
   printf(" \nPROTOCOL -> %hu",xyz->ip.Protocol);
   printf(" \nCHECKSUM -> %hu",xyz->ip.checksum);
   printf(" \nSOURCE -> %hu.%hu.%hu.%hu",xyz->ip.source[0],xyz->ip.source[1],xyz->ip.source[2],xyz->ip.source[3]);
   printf(" \nDESTINATION -> %hu.%hu.%hu.%hu",xyz->ip.destination[0],xyz->ip.destination[1],xyz->ip.destination[2],xyz->ip.destination[3]);
   if(xyz->ip.Protocol == 1){
     printf("\n\nICMP PACKET");
     
   }



   }








}
return 0;
}


/*
int sock_fd;
sock_fd=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
if(sock_fd<0)
{
printf("err");
return -1;
*/



/*
if (getifaddrs(&addresses) == -1)
{
printf("bleh");
return -1;
}
struct ifaddrs *address = addresses;
while(address)
{
int family = address->ifa_addr->sa_family;
if (family == AF_INET )
{
printf("%s\t", address->ifa_name);
printf("%s\t", family == AF_INET ? "IPv4" : "IPv6");
printf("\n");
}
address = address->ifa_next;
printf("number=%d|size=%d|dmac=%x|smac=%x\n",packnum,siz,);
}
freeifaddrs(addresses);*/
