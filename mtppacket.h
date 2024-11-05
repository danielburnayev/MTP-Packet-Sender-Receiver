#ifndef MTP_PACKET_

#define MTP_PACKET_
#define TIMEOUT 500
#define MAX_DATA_LENGTH 1456

struct mtp_header { //16 bytes max
    unsigned int type; // 0 for ack, 1 for data
    unsigned int seqNum;
    unsigned int length;
    unsigned int checksum;
} typedef MTPHeader;

struct mtp_packet { // must be 1472 bytes, max
    MTPHeader header;
    
    //can be data from a file or ACK-related stuff if acking
    //1456 bytes, length of 1456
    char* contents; 
} typedef MTPPacket;

MTPPacket* constructNewMTPPacket();

#endif