#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<poll.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<vector>
#include<string>
#include "message.h"
#include "logging.h"
#include "logging.c"
/* This C code illustrates multiplexing multiple
   pipe connection by a single thread.
  
   Server thread will block on a any of two fd's
   by using poll(). 
	message size is fixed to 40 for proper operation with
    stream data .
*/
using namespace std;
#define PIPE(fd) socketpair(AF_UNIX, SOCK_STREAM, PF_UNIX, fd)
struct Int2{
	int pipe[2];
};
class Client{
    public:
        string fileName;
        int numberOfArguments;
        vector<int> arguments;
    Client(){
        
    }
    Client(string path,int number, vector<int> argumentList) {
        fileName=path;
        numberOfArguments=number;
        arguments= argumentList; 
    }
};

vector<Client> parser(int n){
    vector<Client> ClientList;
    string path;
    int number;
    Client c ;
    for(int i=0;i<n;i++){
        vector<int> argumentList;
        int arg;
        cin>>path>>number;
        for(int j=0;j<number;j++){
            cin>>arg;
            argumentList.push_back(arg);
        }
        c = Client(path,number, argumentList);
        ClientList.push_back(c);
    }  
    return ClientList; 
}
vector<int> getFirstLine(){
    int starting_bid,minimum_increment,number_of_bidders;
    vector<int> firstLine;
    cin>>starting_bid>>minimum_increment>>number_of_bidders;
    firstLine.push_back(starting_bid);
    firstLine.push_back(minimum_increment);
    firstLine.push_back(number_of_bidders);
    return firstLine;
}
void printClient(Client c){
    cout<<c.fileName<<" "<<c.numberOfArguments<<"\n";
    for(int arg : c.arguments){
        cout<<arg<<" ";
    }
    cout<<"\n";
    return;
}
void server(vector<Int2>pipeList ,int n,vector<pid_t>pidList,int starting_bid,int minimmum_increment)
{	
	int current_bid=starting_bid;
	struct pollfd pfd[n] ;
	oi output_data;
	ii  input_data ;
	sm server_mess;
	cm  c_mess;
	vector<int> finishedClients=vector<int>(n);
	int waitingClients=0;
	int winner_id=-1;
	for(int i=0;i<n;i++){
		pfd[i] = { pipeList[i].pipe[0], POLLIN, 0};
		close(pipeList[i].pipe[1]);  /* unused ends */
	}
	int messageSize=100;
	
	char mess[messageSize];
	int  r;
	int timeout=0;
	int min_delay=INT32_MAX;
	/* pollfd strcture keeps: file descriptor, requested event, returned event */
	bool flag=true;
	while (flag) {
		flag=false;
		for(int i=0;i<n;i++){
			if(pfd[i].fd>=0){
				flag=true;
				break;
			}
		}
		if(!flag){
			continue;
		}
		 /* one still open */
		/* clear returned event */
		for  (int i = 0; i < n; i++) 
				pfd[i].revents = 0;
		if(min_delay!=INT32_MAX){
			timeout=min_delay;
		}
		int res=poll(pfd, n, timeout);  /* no timeout*/
		for (int i = 0; i < n; i++){ 
			if (pfd[i].revents && POLLIN) {
				
				r = read(pfd[i].fd, &c_mess , sizeof(cm));
				
				if (r == 0)/* EOF */
				{	
					pfd[i].fd = -1;   /* poll() ignores pollfd item if fd is negative */
				} 			
				else{
					
					int client_id=i;
					int pid= pidList[i];
					int message_type = c_mess.message_id;
					
					input_data.pid=pid;
					input_data.info=c_mess.params;
					input_data.type=c_mess.message_id;

					output_data.pid=pid;
					output_data.type=message_type;
					if(message_type==CLIENT_CONNECT){
						int delay = c_mess.params.delay;
						if(delay<min_delay){
							min_delay=delay;
						}
						server_mess.message_id=SERVER_CONNECTION_ESTABLISHED;
						cei connection_info;
						connection_info.client_id=client_id;
						connection_info.current_bid=current_bid;
						connection_info.minimum_increment=minimmum_increment;
						connection_info.starting_bid=starting_bid;
						server_mess.params.start_info=connection_info;
						output_data.info=server_mess.params;
						print_input(&input_data,client_id);
						print_output(&output_data,client_id);
						write(pipeList[i].pipe[0],&server_mess,sizeof(sm));
					}
					else if(message_type==CLIENT_BID){
						
						int bid=c_mess.params.bid;
						int result=BID_ACCEPTED;
						int increment = bid-current_bid;
						if(bid<starting_bid){
							result=BID_LOWER_THAN_STARTING_BID;
						}
						else if(increment<0){
							result=BID_LOWER_THAN_CURRENT;
						}
						else if(increment<minimmum_increment){
							result=BID_INCREMENT_LOWER_THAN_MINIMUM;
						}
						else if(current_bid<bid ){
							current_bid=bid;
							result = BID_ACCEPTED;
							winner_id=client_id;
						}
						server_mess.message_id=SERVER_BID_RESULT;
						server_mess.params.result_info.current_bid=current_bid;
						server_mess.params.result_info.result=result;
						output_data.info=server_mess.params;
						print_input(&input_data,client_id);
						print_output(&output_data,client_id);
						write(pipeList[i].pipe[0],&server_mess,sizeof(sm));
					}
					else if(message_type==CLIENT_FINISHED){
						
						int status = c_mess.params.status;
						ii  input_data ;
						input_data.pid=pid;
						input_data.info=c_mess.params;
						input_data.type=c_mess.message_id;
						print_input(&input_data,client_id);
						int clientStatus=status;
						waitingClients++;
						finishedClients[client_id]=clientStatus;
					}
					
					
				}
				
			}
		}
		if(waitingClients==n){
			break;
		}
	}
	
	int winning_bid=current_bid;
	print_server_finished(winner_id,winning_bid);// before sending winner info
	server_mess.message_id=SERVER_AUCTION_FINISHED;
	server_mess.params.winner_info.winner_id=winner_id;
	server_mess.params.winner_info.winning_bid=current_bid;
	output_data.info.winner_info.winner_id=winner_id;
	output_data.info.winner_info.winning_bid=winning_bid;
	output_data.type=SERVER_AUCTION_FINISHED;
	for(int i=0;i<n;i++){
		write(pipeList[i].pipe[0],&server_mess,sizeof(sm));
		output_data.pid=pidList[i];
		print_output(&output_data,i);
	}
	/*reaping*/
	int status;
	int status_match;
	for(int i=0;i<n;i++){
		waitpid(pidList[i],&status,0);
		status_match=0;
		if(status==finishedClients[i]){
			status_match=1;
		}
		print_client_finished(i,status,status_match);//after reaping
		close(pfd[i].fd);
	}
	
	return ;
}
int child(int p[], string path,int numberOfArguments, vector<int> arguments)
{
	const char * filename =path.c_str();
	dup2(p[1],STDOUT_FILENO);  //child's stdout >> p[1]
    dup2(p[1],STDIN_FILENO); //child's stdin >> p[1]
	close(p[0]);	/* unused end */
	char * argv[numberOfArguments+2];
	argv[0]=new char[path.size()];
	strcpy(argv[0],path.c_str());
	for(int i=0;i<numberOfArguments;i++){
		argv[i+1]=new char(to_string(arguments[i]).size());
		strcpy(argv[i+1],to_string(arguments[i]).c_str());
	}
	argv[numberOfArguments+1]=new char(1);
	argv[numberOfArguments+1]=NULL;
	
	execv(filename,argv);
	return 0;
}

int main() {
	vector<int> firstLine = getFirstLine();
    int starting_bid,minimum_increment,number_of_bidders;
    starting_bid=firstLine[0];
	minimum_increment=firstLine[1];
	number_of_bidders= firstLine[2];
    vector<Client> ClientList = parser(number_of_bidders);
    int n=number_of_bidders;
    vector<Int2> pipeList;
    pipeList=vector<Int2>(n);
	int w;
	for (int i=0;i<n;i++){
		PIPE(pipeList[i].pipe);
	}
	vector<pid_t> pidList=vector<pid_t>(n);
	for(int i=0;i<n;i++){
		pid_t pid=fork();
		if(!pid){
			
			Client c=ClientList[i];
			string path = c.fileName;
			vector<int> arguments = c.arguments; 
			int numberOfArguments=c.numberOfArguments;
			child(pipeList[i].pipe, path, numberOfArguments, arguments);
			return 0;
		}
		else{
			
			pidList[i]=pid;
		}
	}
	
	server(pipeList,n,pidList,starting_bid,minimum_increment);
	return 0;
}