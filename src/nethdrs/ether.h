#ifndef _LINUX_IF_ETHER_H
#define _LINUX_IF_ETHER_H
/* copied from https://www.iana.org/assignments/ieee-802-numbers/ieee-802-numbers.xhtml, https://en.wikipedia.org/wiki/EtherType and linux if_ether.h */
#define ETH_P_LOOP      0x0060  //Loop back device
#define ETH_P_ALL       0x0003  //linux all packet 
#define ETH_P_IP        0x0800  //IPv4
#define ARP             0x0806  //Adress resolution protocol
#define WON             0x0842  //wake-on-lan
#define AVTP            0x22F0  //Audio Video Transport Protocol 
#define TRILL           0x22F3  //IETF TRILL Protocol
#define SRP             0x22EA  //Stream Reservation Protocol 
    /*Digital equipment corporation protocols */
#define DMOP            0x6002  //DEC MOP
#define DECnet          0x6003  //DECnet Phase IV, DNA Routing 
#define DEClan          0x6004  //DEC LAN
        
#define RARP            0x8035  //Reverse ARP
#define ATALK           0x809B  //AppleTalk (Ethertalk) 
#define AARP            0x80F3  //Apple ARP (ffs apple why?)
#define VTAG            0x8100  //VLAN-tagged frame (IEEE 802.1Q) and Shortest Path Bridging IEEE 802.1aq with NNI compatibility
#define SLPP            0x8102  //Simple Loop Prevention Protocol
#define VLACP           0x8103  //Virtual Link Aggregation Control Protocol 
#define IPX             0x8137  //internet packet exchange
#define QNX             0x8204  //QNXOS 
#define EFC             0x8808  //Ethernet flow control 
#define ESP             0x8809  //Ethernet Slow Protocols[11] such as the Link Aggregation Control Protocol (LACP) 
#define CBNET           0x8819  //Cobranet
#define MPLSU           0x8847  //MPLS unicast
#define MPLSM           0x8848  //MPLS multicast
#define PPoED           0x8863  //Point to point over ethernet Discovery Stage 
#define PPoES           0x8864  //Point to point over ethernet Session Stage 
#define HPLUG           0x887B  //HomePlug 1.0 MME
#define EAPL            0x888E  //EAP over LAN (IEEE 802.1X) 
#define PROFINET        0x8892  //PROFINET Protocol 
#define HSCSI           0x889A  //SCSI over Ethernet
#define ATA             0x88A2  //ATA over Ethernet
#define Ecat            0x88A4  //EtherCAT Protocol 
#define SVLANI          0x88A8  //Service VLAN tag identifier (S-Tag) on Q-in-Q tunnel.
        /* ELECTRIC SUBSTATION COMMUNICATION RAD*/
#define EPOE            0x88AB  //Ethernet Powerlink
#define GOOSE           0x88B8  //GOOSE (Generic Object Oriented Substation event) 
#define GSE             0x88B9  //GSE (Generic Substation Events) Management Services 
#define SV              0x88BA  //SV (Sampled Value Transmission) 

#define MTRMON          0x88BF  //MikroTik RoMON (unofficial) 
#define LLDP            0x88CC  //Link Layer Discovery Protocol (LLDP) 
#define SERCOS          0x88CD  //SERCOS III 
#define HPGP            0x88E1  //HomePlug Green PHY 
#define MRP             0x88E3  //Media Redundancy Protocol (IEC62439-2) 
#define MACsec          0x88E5  //IEEE 802.1AE MAC security (MACsec) 
#define PBB             0x88E7  //Provider Backbone Bridges (PBB) (IEEE 802.1ah) 
#define PTP             0x88F7  //Precision Time Protocol (PTP) over IEEE 802.3 Ethernet 
#define NCSI            0x88F8  //Network controller side band
#define AGCFU           0x8902  //IEEE 802.1ag Connectivity Fault Management (CFM) Protocol / ITU-T Recommendation Y.1731 (OAM) 
#define FCoE            0x8906  //Fibre Channel over Ethernet (FCoE) 
#define FCoEI           0x8914  //Fibre Channel over Ethernet Initialization
#define RoCE            0x8915  //RDMA over Converged Ethernet (RoCE) 
#define TTE             0x891D  //TTEthernet Protocol Control Frame (TTE) 
#define MoCA            0x893A  //1905.1 IEEE Protocol 
#define HSR             0x892F  //High-availability Seamless Redundancy (HSR) 
#define ECTP            0x9000  //Ethernet Configuration Testing Protocol[12] 
#define RTAG            0xF1C1  //Redundancy Tag (IEEE 802.1CB Frame Replication and Elimination for Reliability) 





struct __attribute__((packed)) ether_hdr
{
    /* ethernet frame */
    unsigned char dest_mac[6];
    unsigned char src_mac[6];
    unsigned char ether_type[2];  
};








#endif 