#include "ipAddressUtils.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Array to hold the multiplier for each octet for converting to and from decimal
//form.
int octMultiplier[] = {16777216, 65536, 256, 1};

/*
Converts the number of mask bits to the decimal value of the IP address of the
 mask.  This is done without first calculating the mask as an IP address.
*/
static unsigned int maskBitToDec(char *maskChar){
    int             numFullOctets, len, remainingBits, maskBitsInt=0,bitVal=128, decPlaceMult=1, temp=0;
    unsigned int    result=0;

    len = strlen(maskChar);
    for (size_t i = len-1; i < -1; i--)
    {
            maskBitsInt += (maskChar[i]-'0')*decPlaceMult;
            decPlaceMult = decPlaceMult*10;
    }
    
    numFullOctets = maskBitsInt/8;
    remainingBits = maskBitsInt%8;

    for (size_t i = 0; i < numFullOctets; i++){

    result += 255*octMultiplier[i];
    }
    for (size_t i = 0; i < remainingBits; i++)
    {
        temp +=bitVal;
        bitVal=bitVal >> 1;
    }
    //in this case numFullOctets is the correct position in the
    //octMultiplier array due to 0 based indexing.
    result += temp*octMultiplier[numFullOctets];

    return result;

}

void get_broadcast_address(char *ipAddress, char *mask , char *outputBuffer){
    unsigned int broadCastAddress;

    broadCastAddress = (~(maskBitToDec(mask)))|get_ip_integeral_equivalent(ipAddress);

    get_abcd_ip_format(broadCastAddress, outputBuffer);

}

unsigned int get_ip_integeral_equivalent(char *ip){
    unsigned int    temp=0, result=0, digMult=1, octet=3;
    int             len;

    len = strlen(ip)-1;
    while (len>-1)
    {
        if(ip[len]=='.'){
            len--;
            result = result + temp*octMultiplier[octet];
            digMult = 1;
            temp = 0;
            octet--;
        }
        else{
            temp = temp + (ip[len]-'0')*digMult;
            digMult = digMult*10;
            len--;
        }
        
    }
    result = result + temp*octMultiplier[octet];
    return result;
}

void get_abcd_ip_format(unsigned int ipInDec, char *outputBuffer){
    //Hold the the character string being built
    char currentDig, tempString[4];
    int  digitCounter=0, totalDigCount=0, strLength=0;
    unsigned int remainder = ipInDec, ip[4], tempInt;
    /*
    The integral part of remainder/octMultiplier gives the octet for that
    Part of the IP address. Also counting the number of digits in each octet
    as it is being calculated, for generating the tempString
    */
    for(int i = 0; i < 4; i++){
        ip[i] = remainder/octMultiplier[i];
        remainder = remainder%octMultiplier[i];
        //log10 will return an error if you pass it a 0.
        if(ip[i] == 0) totalDigCount += 1;
        else if(ip[i] == 1) totalDigCount += 1;
        
        else totalDigCount += (int) ceil(log10((double) ip[i]));
    }
    
    /*
    Need add 3 to the strLength for the . and one for the NULL terminator.
    However, due to 0 based indexing, adding 3 to strLength will give the 
    position of the NULL terminator
    */
    
    strLength = totalDigCount+3;
    outputBuffer[strLength]='\0';
    strLength--;

    for(int i = 3; i > -1; i--){
        int counter = 0;
        do
        {   
            tempInt = ip[i]%10;
            ip[i] = ip[i]/10;
            outputBuffer[strLength] = tempInt+'0';
            digitCounter++; 
            strLength--;
        } while (ip[i]>0);
        if(i!=0) outputBuffer[strLength]='.';
        strLength--;
    }
}

void get_network_id(char *ipAddress, char *mask, char *outputBuffer){
    unsigned int networkId;

    networkId = maskBitToDec(mask)&get_ip_integeral_equivalent(ipAddress);

    get_abcd_ip_format(networkId, outputBuffer);
}

unsigned int get_subnet_cardinality(char *maskChar){
    int len, maskBitsInt=0, decPlaceMult=1;
    unsigned int numValidHosts=1;
      
    len = strlen(maskChar);
    for (size_t i = len-1; i < -1; i--)
    {
            maskBitsInt += (maskChar[i]-'0')*decPlaceMult;
            decPlaceMult = decPlaceMult*10;
    }
    for (size_t i = 0; i < 32-maskBitsInt; i++) {

        numValidHosts = numValidHosts*2;
    }

    return numValidHosts - 2;
    
}

int check_ip_subnet_membership(char *networkId, char *mask, char *ipAdressToCheck){
    unsigned int networkIdOfIPaddresstoCheck, networkIdInt;

    networkIdOfIPaddresstoCheck = maskBitToDec(mask)&get_ip_integeral_equivalent(ipAdressToCheck);

    networkIdInt = get_ip_integeral_equivalent(networkId);

    if(networkIdInt==networkIdOfIPaddresstoCheck) return 0;
    else return -1;


}