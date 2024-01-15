#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ipAddressUtils.h"

int main(int argc, char const *argv[])
{   
    unsigned int ipInDec = 3232235521;
    int inSubNet;
    char *ipStr = "192.168.0.1", *mask = "20";
    char *ip = (char *)malloc(sizeof(char)*16);
    get_abcd_ip_format(ipInDec, ip);

    ipInDec = get_ip_integeral_equivalent(ipStr);

    printf("IP address %s, in decimal form %u\n", ipStr, ipInDec);
    printf("Decimal form %u to IP address: %s\n", ipInDec ,ip);
    get_network_id(ipStr, mask, ip);
    printf("Network ID: %s\n", ip);
    inSubNet = check_ip_subnet_membership(ip, mask, ipStr);
    printf("Is IP address %s in subnet %s, %d\n", ipStr, ip, inSubNet);
    get_broadcast_address(ipStr, mask, ip);
    printf("Broadcast addrress: %s\n", ip);
    printf("Number of Valid Hosts: %u\n", get_subnet_cardinality(mask));




    return 0;
}
