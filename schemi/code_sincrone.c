

void SendSincron(queue,Messaggio*m){

	Messaggio m1,m2;
	m1.type=REQUEST_TO_SEND;
	msgsnd(queue1,&m1,sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue2,&m2,sizeof(Messaggio)-sizeof(long),OK_TO_SEND,0);
	msgsnd(queue,m,sizeof(Messaggio)-sizeof(long),0);


}

void ReceiveBloccante(Messaggio*m,queue,tipomess){

	Messaggio m1,m2;
	msgrcv(queue1,&m1,sizeof(Messaggio)-sizeof(long),REQUEST_TO_SEND,0);
	m2.type=OK_TO_SEND;
	msgsnd(queue2,&m2,sizeof(Messaggio)-sizeof(long),0);
	msgrcv(queue,m,sizeof(Messaggio)-sizeof(long),tipomess,0);
}
