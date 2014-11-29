#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>

using namespace std;

const string HOST = "github.com";
const string PAGE= "/";
const int PORT = 80;
const string USERAGENT = "Meanie 1.1" ;
 
void usage() {
  fprintf(stderr, "USAGE: htmlget host [page]\n\
    \thost: the website hostname. ex: coding.debuntu.org\n\
   \tpage: the page to retrieve. ex: index.html, default: /\n");
}
 
 
int create_tcp_socket() {
  int sock;
  if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
    perror("Can't create TCP socket");
    exit(1);
  }
  return sock;
}
 
 
string get_ip(const string& host) {
  struct hostent *hent;
  int iplen = 15; //XXX.XXX.XXX.XXX
  char *ip = new char[iplen + 1];
  memset(ip, 0, iplen+1);
  if((hent = gethostbyname(host.c_str())) == NULL) {
    herror("Can't get IP");
    exit(1);
  }

  if(inet_ntop(AF_INET, (void *)hent->h_addr_list[0], ip, iplen) == NULL) {
    perror("Can't resolve host");
    exit(1);
  }
  return string(ip);
}
 
string build_get_query(string host,string page) {
  string getpage = page;
  const string tpl  ="GET /%s HTTP/1.1\r\nHost: %s\r\nUser-Agent: %s\r\nConnection: close\r\n\r\n";
  if(getpage[0] == '/'){
    getpage.erase(getpage.begin());
    fprintf(stderr,"Removing leading \"/\", converting %s to %s\n", page.c_str(), getpage.c_str());
  }
  // -5 is to consider the %s %s %s in tpl and the ending \0
  char *query = new char[host.size()+getpage.size()+USERAGENT.size()+tpl.size()-5];
  sprintf(query, tpl.c_str(), getpage.c_str(), host.c_str(), USERAGENT.c_str());
  string ret = string(query);
  delete[] query;
  return ret;
}


void sendQuery(int sock, const string& get) {
  fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get.c_str());
  //Send the query to the server
  for (int sent = 0; sent < (int)get.size();) {
    string aux = string(get.begin() + sent, get.end());
    int tmpres = send(sock, aux.c_str(), get.size() - sent, 0);
    if(tmpres == -1){
      perror("Can't send query");
      exit(1);
    }
    sent += tmpres;
  }
 
}

int main(int argc, char **argv) {
  struct sockaddr_in *remote;
  int sock;
  int tmpres;
  string ip;
  string get;
  char buf[BUFSIZ+1];
 
  if(argc == 1){
    usage();
    exit(2);
  }  
  string host = string(argv[1]);
  string page = string(argc > 2 ? argv[2] : PAGE);
  sock = create_tcp_socket();
  ip = get_ip(host);
  fprintf(stderr, "IP is %s\n", ip.c_str());
  remote = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in *));
  remote->sin_family = AF_INET;
  tmpres = inet_pton(AF_INET, ip.c_str(), (void *)(&(remote->sin_addr.s_addr)));
  if (tmpres < 0) {
    perror("Can't set remote->sin_addr.s_addr");
    exit(1);
  } else 
  if (tmpres == 0) {
    fprintf(stderr, "%s is not a valid IP address\n", ip.c_str());
    exit(1);
  }

  remote->sin_port = htons(PORT);
 
  if(connect(sock, (struct sockaddr *)remote, sizeof(struct sockaddr)) < 0){
    perror("Could not connect");
    exit(1);
  }
  get = build_get_query(host, page);
  fprintf(stderr, "Query is:\n<<START>>\n%s<<END>>\n", get.c_str());
  sendQuery(sock, get);
  //now it is time to receive the page
  memset(buf, 0, sizeof(buf));
  int htmlstart = 0;
  char * htmlcontent;
  while((tmpres = recv(sock, buf, BUFSIZ, 0)) > 0) {
    if(htmlstart == 0) {
      /* Under certain conditions this will not work.
      * If the \r\n\r\n part is splitted into two messages
      * it will fail to detect the beginning of HTML content
      */
      htmlcontent = strstr(buf, "\r\n\r\n");
      if(htmlcontent != NULL){
        htmlstart = 1;
        htmlcontent += 4;
      }
    }else{
      htmlcontent = buf;
    }
    if(htmlstart){
      fprintf(stdout,"%s", htmlcontent);
    }
 
    memset(buf, 0, tmpres);
  }

  if(tmpres < 0) {
    perror("Error receiving data");
  }
  free(remote);
  close(sock);
  return 0;
}

