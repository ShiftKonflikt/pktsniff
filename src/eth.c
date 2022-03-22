#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include "ether.h" 
#include "nethders.h"

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



void print_ipv4(unsigned char *buf){

unsigned char version,IHL,TOS,flags,ttl,protocol,source[6],destination[6],ph1,ph2;
unsigned short tot_len,Identification,frag_off,checksum;
version = buf[14] >> 4;
IHL = buf[15] << 4;
tot_len = buf[16] + buf[17];
Identification = buf[18] + buf[19];
ph1 = (buf[20]<<3)>>3;
frag_off = buf[21] + ph1;
ttl = buf[22] ;
protocol = buf[23];
checksum = buf[24]+buf[25];
printf("   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |%u  |  %u      |Type of Service|         %hu                   |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |        %hu                    |0%u%u|     %hu                 |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |  %u           |    %u         |         Header Checksum       |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |                   %hu.%hu.%hu.%hu                             |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |                    %hu.%hu.%hu.%hu                            |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  "
  "        |                Options/Data                   |    Padding    |\n  "
  "        +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n  ",
  version,IHL,tot_len,Identification,9,9,frag_off,ttl,protocol,buf[26],buf[27],buf[28],buf[29],
 buf[30],buf[31],buf[32],buf[33]
);

return ;

}






int main(){
int packnum=-1;
struct  ppkt *xyz;
setvbuf(stdout, NULL, _IONBF, 0);
unsigned char* buf = (unsigned char*)malloc(1514);
int fd = socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
if(fd<0){
  exit(EXIT_FAILURE);
}
struct ifreq ifopts;
char *intrf = ""; // no support for iffaddrs strct for now just a test will be added in future
int len = strlen(intrf);
strncpy(ifopts.ifr_name, intrf, IFNAMSIZ-1);
ioctl(fd, SIOCGIFFLAGS, &ifopts);
ifopts.ifr_flags |= IFF_PROMISC;
ioctl(fd, SIOCSIFFLAGS, &ifopts);

if ((setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, intrf, len))== -1){
		perror("SO_BINDTODEVICE");
		pclose(fd);
		exit(EXIT_FAILURE);
}
printf("tes");
while(1){
++packnum;
int siz= recvfrom(fd, buf, ETH_FRAME_LEN, 0, NULL, NULL);
if(siz<0){
  printf("fatal error pktnum %d",packnum);
  continue;
}
if(siz>1514){
  printf("packet size exceeded hence dropped");
  continue;
}
printf("number=%d|size=%d|dmac=%.2X%.2X:%.2X%.2X:%.2X%.2X|smac=%.2X%.2X:%.2X%.2X:%.2X%.2X\n",packnum,siz,buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7],buf[8],buf[9],buf[10],buf[11]);
if(buf[12]==0x08 && buf[13]==0x00 ){
printf("type=Ipv4 \n");
print_ipv4(buf);


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
