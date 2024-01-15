/*
Takes three arguments, as character string ip address, char with the number of bits in the mask mask, a char string output buffer.  
The output buffer contains the value of the boradcast address for the subnet
*/
void get_broadcast_address(char *, char *, char *);

/*
Takes a character string, and returns the unsigned int equiv.
*/
unsigned int get_ip_integeral_equivalent(char *);

/*
Takes an unsigned int and a character buffer, convert the unsigned int into its IPv4 address and stores that in the character buffer.
*/
void get_abcd_ip_format(unsigned int, char *);

/*
Takes three char strings, IPv4 address, a network mask expressed as the number of bits in the mask, and the output buffer.
The network ID is calculated and placed in the output buffer.
*/
void get_network_id(char *, char *, char *);

/*
Takes a char that is the number of bits in the mask for the network and returns the number of valid host addresses
(2^(32-bits in mask))-2
*/
unsigned int get_subnet_cardinality(char *);

/*
Takes a char string that is the network ID,a char string that is the number of bits in the mask, and a char string that is an IP address to check.
Returns 0 if the IP address is in the subnet and -1 if it is not.
*/
int check_ip_subnet_membership(char *, char *, char *);

