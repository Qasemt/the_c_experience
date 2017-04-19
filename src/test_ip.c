#include "test_ip.h"
#include <stdint.h>
#include <winsock2.h>
#include <stdio.h>

// need link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

void run_test_ip(void)
{
	uint64_t ip,netip,netmask,netstart,netend;
	//unsigned long ulAddr = INADDR_NONE;

 

	 ip = inet_addr("50.22.100.250"); // value to check
	 netip = inet_addr("50.22.1.1");; // network ip to compare with
	 netmask = inet_addr("255.255.0.0"); // network ip subnet mask
	 netstart = (netip & netmask); // first ip in subnet
	 netend = (netstart | ~netmask); // last ip in subnet
	if ((ip >= netstart) && (ip <= netend))
	{
		// is in subnet range...
		printf("subnet range");
	}
	else
	{
		// not in subnet range...
	}
}
