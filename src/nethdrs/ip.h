#ifndef nethders_h
#define nethders_h
#include <sys/cdefs.h>
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





struct __attribute__((packed)) ip4_hdr 
{
#if BYTE_ORDER == LITTLE_ENDIAN
	unsigned char	IHL:4,version:4;		
#endif
#if BYTE_ORDER == BIG_ENDIAN
	unsigned char	version:4,ihl:4;	
#endif
unsigned char qos;
unsigned char tot_len[2] ;
unsigned char Identification[2] ;
unsigned char fragmentdat[2] ;
unsigned char TTL;
unsigned char Protocol;
unsigned short checksum;
unsigned char source[4],destination[4];
};



/*ipv6 tobe added later*/


/*
struct __attribute__((packed)) ip4_hdr 
{

unsigned char version_IHL ;
unsigned char qos;
unsigned short tot_len ;
unsigned short Identification ;
unsigned short flag;
unsigned int Frag_off;
unsigned char TTL;
unsigned char Protocol;
unsigned short checksum;
unsigned char source[4];
unsigned char destination[4];
};

struct  ppkt{
struct ether_hdr eth;
struct ip4_hdr  iphdr;
unsigned char payload[];
};
*/

#endif
