
#include "tictactoe.h"

void showBoard (string);
void mark(int, int, int);
int moveIsValid(int,int);
int switchPlayer(int);
int checkWin();

using namespace std;

string Board[3][3];
int main ( int argc, char*argv[]){
	int  count=0;
	int orig_sock;                            // original socket in client
	int	len, portno;
	struct sockaddr_in serv_adr;              // server address
	struct hostent *host;
	string PlayerName;
	int result = 1;
	int move[2];
	int bytes_recvd, bytes_sent;
	char cbuffer[512];
	char *ptr = &cbuffer[0];
	char winner[10];
	char result_buffer;
	char cmove;
	char choice_buffer[2], comp_choice[2];
	int x_move,y_move, chance = 1;
	
	
	if (argc != 3){
		cout<<"usage:"<<argv[0]<<"server"<<endl;
		return 1;
	}
	
	host = gethostbyname(argv[1]);				// obtain host server info
	if (host ==(struct hostent*) NULL) {
		perror("gethostbyname");
		return 2;
	}
	
	// Create a reliable, stream socket using TCP
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sock == -1)
	{	
		perror("Sorry. Socket could not be created!");
		return 1;
	}
	
	memset(&serv_adr, 0, sizeof( serv_adr));
	serv_adr.sin_family = AF_INET;				// IPv4 address family
	memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);
	portno = atoi(argv[2]);
	serv_adr.sin_port = htons(portno);
	
	// SOCKET
	if ((orig_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("generate error");
		return 3;
	}
	
	// CONNECT
	if (connect( orig_sock,(struct sockaddr *)&serv_adr,sizeof(serv_adr)) < 0) { 
		perror("connect error");
		return 4;
	}
	
	cout << "Enter Your Name:"<<endl;
	cin >> PlayerName;
	
	// PROCESS
	do 
	{
		showBoard(PlayerName);
		
			
				
				cout <<"----- "<<PlayerName << "'s turn-----" << endl;
				cout << "Enter the two digit number with spaces between to  move to the box as shown:" << endl;
				cin >> x_move>>y_move;
				int flag=moveIsValid(x_move,y_move);
				 while(flag != 1){
					   cout <<"invalid input,enter again"<< endl;
					   cin >> x_move>>y_move;
					   flag=moveIsValid(x_move,y_move);
					  }
			        	
						mark(chance,x_move,y_move);
						sprintf(&choice_buffer[0], "%d",x_move );
						sprintf(&choice_buffer[1], "%d", y_move);
 						bytes_sent = send(orig_sock, &choice_buffer, sizeof(choice_buffer), 0);
 						if(bytes_sent == -1)
 						{
 							perror("player data send error.");
 							return 5;
 						}
								
		int value = switchPlayer(chance);
		chance = value;
	
	
	bytes_recvd = recv(orig_sock, &comp_choice, sizeof(comp_choice), 0);
		
					
					if(bytes_recvd == -1)
					{
						perror("computer data received error");
						return 6;
					}
          	int xmove = comp_choice[0]-'0';
			int ymove =comp_choice[1]-'0';
			    	mark(chance,xmove,ymove);
			 
			
			//}
		value = switchPlayer(chance);// USER OR PC
		chance= value;
		
		result = checkWin();
		count=count+result;
		
		if(count==5 && result==1)
		{
			cout<<"Game End in a Draw";
			break;
		}
		
		// game moves in loop until it is 1.
		signal(SIGPIPE, SIG_IGN);
	
	}while(result == 1);
	 
		
	
	return 0;
	}
int moveIsValid (int a, int b )
{
    while(a>=0 && a<3 && b>=0 && b<3)
    {
        if (Board[a][b] != "X" && Board[a][b] != "O" )
        {
		return true;
        }
        else
        {   cout<<"INVALID MOVE:"<< endl;
        return false;
        }
    }
}

void showBoard (string playername1)
{
   cout <<"-------------Welcome to tic-tac-toe-------------"<<endl;
   cout << playername1 << " is X and Computer is O."<< endl;
	 
			if((Board[0][0])=="\0")
			{
				 Board[0][0]="00";
			}
			if((Board[0][1])=="\0")
			{
				 Board[0][1]="01";
			}
		if((Board[0][2])=="\0")
			{
				 Board[0][2]="02";
			}
		if((Board[1][0])=="\0")
			{
				 Board[1][0]="10";
			}
			if((Board[1][1])=="\0")
			{
				 Board[1][1]="11";
			}
		if((Board[1][2])=="\0")
			{
				 Board[1][2]="12";
			}
		if((Board[2][0])=="\0")
			{
				 Board[2][0]="20";
			}
					if((Board[2][1])=="\0")
			{
				 Board[2][1]="21";
			}
				if((Board[2][2])=="\0")
			{
				 Board[2][2]="22";
			}
				
	
   cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;

}
void mark(int chance, int m,int n)
{
	if (chance == 1 )
	{

		Board[m][n] = 'X';
	}
	else
		Board[m][n] = 'O';
}


int switchPlayer(int temp)
{
   if ( temp == 1)
		  temp++;
   
    else if ( temp == 2)
   		temp--;
    
    return (temp);
}

int checkWin()
{
	int end = 0;
	if (Board[0][0] == "X" && Board[0][1] == "X" && Board[0][2] == "X")
		
	{
		
   cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[1][0] == "X" && Board[1][1] == "X" && Board[1][2] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[2][0] == "X" && Board[2][1] == "X" && Board[2][2] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[0][0] == "X" && Board[1][1] == "X" && Board[2][2] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " YOU WON "<< endl;
	}
	else if (Board[0][2] == "X" && Board[1][1] == "X" && Board[2][0] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[0][0] == "X" && Board[1][0] == "X" && Board[2][0] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[0][1] == "X" && Board[1][1] == "X" && Board[2][1] == "X")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}
	else if (Board[0][2] == "X" && Board[1][2] == "X" && Board[2][2] == "X")
	{
		
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << "  YOU WON "<< endl;
	}

	//  computer case 
	else if (Board[0][0] == "O" && Board[0][1] == "O" && Board[0][2] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[1][0] == "O" && Board[1][1] == "O" && Board[1][2] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[2][0] == "O" && Board[2][1] == "O" && Board[2][2] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[0][0] == "O" && Board[1][1] == "O" && Board[2][2] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[0][2] == "O" && Board[1][1] == "O" && Board[2][0] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[0][0] == "O" && Board[1][0] == "O" && Board[2][0] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[0][1] == "O" && Board[1][1] == "O" && Board[2][1] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else if (Board[0][2] == "O" && Board[1][2] == "O" && Board[2][2] == "O")
	{
		 cout << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[0][0] << " | " << Board[0][1] << " | " << Board[0][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[1][0] << " | " << Board[1][1] << " | " << Board[1][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << "| " << Board[2][0] << " | " << Board[2][1] << " | " << Board[2][2] << " | " << endl;
   cout << " ---+---+---" << endl;
   cout << endl;
		cout << " COMPUTER WON "<< endl;
	}
	else
	{
		end = 1;
		return end;
	}  
	
}






