#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h> 
#include <vector>

#ifdef __APPLE__	
#include <CoreFoundation/CoreFoundation.h>
#endif

void uprintf(const char *format, const char *str){
#ifdef __APPLE__	
	CFStringEncoding encoding = CFStringGetSystemEncoding();
	CFStringRef ustr = CFStringCreateWithCString(kCFAllocatorDefault, str, encoding);
	if(ustr){
		CFIndex ustrlen = CFStringGetMaximumSizeForEncoding(CFStringGetLength(ustr), kCFStringEncodingUTF8);	
		std::vector<char> buf(++ustrlen);
		CFStringGetCString(ustr, (char *)&buf[0], ustrlen, kCFStringEncodingUTF8);
		printf(format, &buf[0]);
		CFRelease(ustr);
	}else{
		printf(format, "");
	}
#endif	
}

int main (int argc, char * const argv[]) {

	static struct option longopts[] = {
		{ "wait", required_argument, NULL, 'w'},
		{ "port", required_argument, NULL, 'p'},		
		{ "help", required_argument, NULL, 'h'},		
		{ NULL, 0, NULL, 0}
	};
	
	int wait = 2;
	int port = 19813;	
	
	int f;
	
	while ((f = getopt_long(argc, argv, "p:w:h", longopts, NULL)) != -1)
		switch (f) {
			case 'p':
				port = atoi(optarg);
				break;				
			case 'w':
				wait = atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, "Usage: ls4d [options...]\n\
-p, --port\tport number of the server (default=19813)\n\
-w, --wait\tnumber of seconds to wait for each udp line(default=2)\n\
-h, --help\tdisplay this information\n");
				return 0;
				break;
			default:
				abort();
		}
	
    int sock;
	
    if ((sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP)) != -1){
		int broadcast = 1;
		if (setsockopt (sock, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) != 0){
			close (sock);
		}else{
			struct timeval tv;
			tv.tv_sec = wait;
			tv.tv_usec = 0;
			setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof tv);
			char *ip = (char *)"255.255.255.255";
			char msg[96];
			memset(msg, 0, 96);
			strcpy(&msg[32], "4D Server II");
			struct sockaddr_in si;
			si.sin_family = AF_INET;
			si.sin_port = htons (port);
			inet_aton (ip, (in_addr *)&si.sin_addr.s_addr);
			sendto (sock, msg, 96, 0, (struct sockaddr*) &si, sizeof(si));
			char buf[96];
			struct sockaddr_in remaddr;
			socklen_t addrlen = sizeof (remaddr); 
			
			char host[32];
			char name[32];
			
			int recvlen; 
			do{
				
				memset(host, 0, 32);
				memset(name, 0, 32);	
				
				recvlen	= recvfrom (sock, buf, 96, 0, (struct sockaddr *)&remaddr, &addrlen);
				
				if (recvlen > 0){

					strcpy (host, &buf[0]);
					strcpy (name, &buf[64]);				
					
					uprintf ("%s\t", host);
					uprintf ("%s\n", name);
					
				}
			}while(recvlen > 0);	
			close (sock);
		}
	}
    return 0;
}


