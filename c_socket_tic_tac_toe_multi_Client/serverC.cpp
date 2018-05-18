

#include "tictactoe.h"

int main(int argc, char **argv) {
	pid_t err;
	//error, server socket id, client socket id, port number.
	//length of client address
	int socketserver, scoketclient, portno,n,Turn=1,Move;
	socklen_t clientaddr;  
	// buffer for storing
	char buffer[512],child[30],user[15];
	struct sockaddr_in serv_addr, cli_addr; //server address, client address
	if(argc < 2) // to check the login process
	{
		cout <<"error, no port provided." <<endl;
		exit(1);
	}
			
		//Creates a socket
		socketserver = socket(AF_INET, SOCK_STREAM, 0);
		if(socketserver<0)
		{
			cout <<"Error opening socket" <<endl;
			exit(2);
		}
		
		//local address structure
		memset(&serv_addr, 0, sizeof(serv_addr));
		portno = atoi(argv[1]);
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(portno);
		
		//bind socket to the local address
		if(bind(socketserver, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		{	
			cout <<"Bind Error" <<endl;
			exit(3);
		}
		
		//listen for socket
		if(listen(socketserver,5) < 0) 
		{
			cout <<"listen Error" <<endl;
			exit(4);
		}
		
		
	while(1)
		{
			clientaddr = sizeof(cli_addr);
			
			//connect to the client. 
			scoketclient = accept(socketserver, (struct sockaddr *) &cli_addr, &clientaddr);
			if(scoketclient < 0) 
			{
				cout <<"Error Creation";
				exit(4);
			}
		
			cout <<"New Connection with  port " <<inet_ntoa(cli_addr.sin_addr) <<ntohs(cli_addr.sin_port) <<endl;
			err = fork();
			if(err == -1){
				cout <<"parent: fork failed, errno = " <<errno <<endl;
				exit(5);	
			}
			else if(err == 0){
				sprintf(child, "%d", scoketclient);
				err = execl("./serverG", "serverG", child);
				if ( err == -1 ) 
					{
					cout <<" parent:  execl failed, errno = " <<errno <<endl;
					exit (6);
					}
				cout <<err <<endl;
				close(scoketclient);
				return 0;
				}
			else
				close(scoketclient);
				close(scoketclient);
		
	}
		return 0;
}
	
