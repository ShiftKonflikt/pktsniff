#ifndef nethders_h
#define nethders_h

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

struct __attribute__((packed)) ether_hdr
{
    /* ethernet frame */
    unsigned char dest_mac[6];
    unsigned char src_mac[6];
    unsigned char ether_type[2];  
};


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


struct __attribute__((packed)) eip4_hdr 
{
unsigned int version ;
unsigned int IHL ;
unsigned char qos;
unsigned int tot_len ;
unsigned int Identification ;
unsigned int unused_flag ;
unsigned int DF ;
unsigned int MF ;
unsigned int Frag_off;
unsigned char TTL;
unsigned char Protocol;
unsigned char checksum[2];
unsigned char source[4];
unsigned char destination[4];
};



#endif