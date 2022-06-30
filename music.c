#include<stdio.h>
#include<windows.h>
#include<MMSystem.h>
#include<string.h>
#include<stdbool.h>

typedef struct Play{ //Structure which stores the playlist
	struct Play *next;
	struct Play *prev;
	char song[256];
}play;

void insert(play **head,char *data) {//cicular double link list insertion
	play *y=(play *)malloc(sizeof(play)),*z;
	strcpy(y->song,data);
	if(!(*head)) {
		*head=y;
		y->next=y;
		y->prev=y;
		return;
	}
	play *rear=(*head)->prev;//insertion happens at the end of the list
	rear->next=y;
	y->next=*head;
	y->prev=rear;
	(*head)->prev=y;
}

void print(play *head) {//To print the playlist
	printf("The songs on the playlist are :-\n\n");
	play *y=head;
	int i=1;
	printf("%d. %s\n",i++,y->song);
	y=y->next;
	while(y!=head) {
		printf("%d. %s\n",i++,y->song);
		y=y->next;
	}
}

int main() {
	int i,choice=2,n,choiceprev;
	char c;
	play *head=NULL,*x;
	char data[256];
	printf("Enter the no of songs: ");
	scanf("%d",&n);
	printf("\nEnter the names of the song as stored in SSD (only .wav file supported): \n(To avoid unforseen error please rename any file that has any characters other than alphaum and underscore.)\n");
	for(i=0;i<n;i++) {
		fflush(stdin);
		scanf("%[^\n]",data);
		fflush(stdin);
		insert(&head,data);
	}
	printf("\n\nInput complete. Press any key to continue.....");
	getch();//Just a flair for visuals
	x=head;
	while(choice) {
		system("cls");//clear screen so that the playlist is always visible
		print(head);
		if(choice!=2)//going to the next or previous song in the playlist will alwyas play the song by default
		printf("\n\nTrack %s is selected and playing.....", x->song);
		else//Just show what song is selected or which node I am in when it's not playing
		printf("\n\nTrack %s is selected." , x->song);
		printf("\n");
		printf("\n\nEnter 1 to play, 2 to stop, 3 to go to the previous song, 4 to go to the next song and any other key to permanenetly stop: ");
		scanf("%d",&choice);
		switch (choice) {
			case 1:PlaySound(x->song,NULL,SND_ASYNC);
					break;
			case 2:PlaySound(NULL,0,0);
					break;
			case 3:x=x->prev;
					PlaySound(x->song,NULL,SND_ASYNC);
					break;
			case 4:x=x->next;
					PlaySound(x->song,NULL,SND_ASYNC);
					break;
			default:choice=0;
					break;
		}
		choiceprev=choice;
	}
	return 0;
}
