
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 255 //lunghezzza
#define F 1024//numero massimo di figli in un nodo
#define OK printf("ok\n");
#define NO printf("no\n");
int sen_find=0;
struct nodo{
	char name[N+1];
	struct nodo* son;
	struct nodo* next;
	struct nodo* prev;
	char *contenuto;
	int file;
};
struct nodo root;
struct elem_lista{
	char *name;
	struct elem_lista * next_elem;
	struct elem_lista *prev_elem;
};
long unsigned int nbytes=1000;
//qua tutti i prototipi
void create( char* percorso);
int  create_ric(char*percorso, struct nodo* padre);
void create_dir( char* percorso);
int create_dir_ric(char*percorso, struct nodo* padre);
void read(char* percorso);
int read_ric(char*percorso, struct nodo* padre);
void delete(char*percorso);
int delete_ric(char*percorso, struct nodo* padre);
void delete_r(char*percorso);
void delete_r_ric(char*percorso, struct nodo* padre, int se_prima_volta);
void write(char*percorso,char*contenuto);
void write_ric(char*percorso, char*contenuto, struct nodo* padre);
void find(char*nome);
struct elem_lista* find_ric(char*da_trovare,  char* da_stampare, struct nodo* padre,int se_prima_volta, struct elem_lista* primo_della_lista);
struct nodo* pos_effettiva( char* a, int*sentinella,char *percorso, struct nodo* padre);
struct elem_lista* insert (char *da_stampare, struct elem_lista* primo_della_lista);
void print_(struct elem_lista* primo_della_lista);
//fine prototipi, adesso il main
int main(){
	int sen_main=0;
	int i=0;
	strcpy(root.name, "");
	root.son=NULL;
	while(sen_main==0){
		int per=-1;
		int bytes_read=-1;
		char comando[11];
		char *percorso;
		char *contenuto;
		percorso=(char*)malloc(nbytes+1);
		contenuto=(char*)malloc(nbytes+1);
		int com= scanf("%s", comando);
		if(com>11 || com <1){
			return 0;
		}
		if (comando[0] == 'e'){
			sen_main=1;
		}
		else{
			per= scanf("%s", percorso);
			if(per==-1){
				return -1;
			}
			if (comando[0] == 'w'){
				bytes_read = getline (&contenuto, &nbytes, stdin);
				if (bytes_read==-1){
					return -1;
				}
				write(percorso, contenuto);
			}
			int len =strlen(percorso);
			if(len > bytes_read){
				nbytes = len+50;
			}
			else{
				nbytes=bytes_read+50;
			}
		}
//ho finito l'input
		char h[11]= "create_dir";
		char g[11]="create";
		if (strcmp(comando, h)==0){
			create_dir(percorso);
		}
		else{
			if(strcmp(comando,g)==0){
				create(percorso);
			}
		}
		if(comando[0]=='r'){
			read(percorso);
		}
		char j[11]="delete_r";
		if(comando[0]=='d'){
			if(strcmp(comando,j)==0){
				delete_r(percorso);
			}
			else{
				delete(percorso);
			}
		}
		if(comando[0]=='f'){
			find(percorso);
		}
	}
	return 0;
}
//fine main, adesso tutte le funzioni(con le ausiliare ricorsive ecc...)
void create(char* percorso){
	struct nodo* padre = &root;
	if (create_ric(percorso, padre)==1){
		OK
	}
	else NO;
}
int create_ric(char*percorso, struct nodo* padre){
	char *a; int sentinella=0;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella ==1){
		struct nodo *punt=padre->son;
		int h=1;
		if(punt!=NULL){
			while(punt->next!=NULL){
				if(strcmp(a, punt->name)==0){
					return -1;
				}
				punt=punt->next;
				h++;
				if (h>F){
					return -1;
				}
			}
			struct nodo* new_nodo;
			new_nodo= malloc(sizeof(struct nodo));
			strcpy(new_nodo->name, a);
			new_nodo->contenuto=NULL;
			new_nodo->file=1;
			punt->next=new_nodo;
			new_nodo->next=NULL;
			new_nodo->prev=punt;
			new_nodo->son=NULL;
			return 1;
		}
		else{
			struct nodo *new_nodo;
			new_nodo = malloc (sizeof(struct nodo));
			strcpy(new_nodo->name, a);
			new_nodo->contenuto=NULL;
			new_nodo->file=1;
			new_nodo->prev=NULL;
			new_nodo->next=NULL;
			new_nodo->son=NULL;
			padre->son=new_nodo;
			return 1;
		}
	}
	return -1;
}
void create_dir(char* percorso){
	struct nodo* padre = &root;
	if (create_dir_ric(percorso, padre)==1){
		OK
	}
	else NO;
}
int create_dir_ric(char*percorso, struct nodo* padre){
	int sentinella=0;char *a;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella ==1){
		struct nodo *punt=padre->son;
		int h=1;
		if(punt!=NULL){
			while(punt->next!=NULL){
				if(strcmp(a, punt->name)==0){
					return -1;
				}
				punt=punt->next;
				h++;
				if (h>F){
					return -1;
				}
			}
			struct nodo* new_nodo;
			new_nodo= malloc(sizeof(struct nodo));
			strcpy(new_nodo->name, a);
			new_nodo->contenuto=NULL;
			new_nodo->file=0;
			punt->next=new_nodo;
			new_nodo->next=NULL;
			new_nodo->prev=punt;
			new_nodo->son=NULL;
			return 1;
		}
		else{
			struct nodo *new_nodo;
			new_nodo = malloc (sizeof(struct nodo));
			strcpy(new_nodo->name, a);
			new_nodo->contenuto=NULL;
			new_nodo->file=0;
			new_nodo->prev=NULL;
			new_nodo->next=NULL;
			new_nodo->son=NULL;
			padre->son=new_nodo;
			return 1;
		}
	}
	return -1;
}
void read(char*percorso){
	struct nodo* padre = &root;
	if (read_ric(percorso, padre)!=1){
		NO
	}
}
int read_ric(char*percorso, struct nodo* padre){
	int sentinella=0;char *a;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella ==1){
		struct nodo*punt= padre->son;
		if(punt !=NULL){

			while((strcmp(a, punt->name)!=0 || punt->file==0) && sentinella ==1){
				if(punt->next!= NULL){
					punt=punt->next;
				}
				else{
					sentinella=-1;
				}
			}
			if(sentinella==1){
				if(punt->contenuto !=NULL){
					printf("contenuto ");
					int y=0;
					while(punt->contenuto[y+2]!= '"'){
						printf("%c", punt->contenuto[y+2]);
						y++;
					}
					printf("\n");
					return 1;
				}
				else{
					printf("contenuto \n");
					return 1;
				}
			}
		}
	}
	return -1;
}
void delete(char*percorso){
	struct nodo* padre = &root;
	if(delete_ric(percorso, padre)==1){

		OK
	}
	else{
		NO
	}
}
int delete_ric(char* percorso, struct nodo* padre){
	int sentinella=0;char *a;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella==1){
		struct nodo*punt= padre->son;
		if(punt !=NULL){
			while(strcmp(a, punt->name)!=0 && sentinella ==1){
				if(punt->next!= NULL){
					punt=punt->next;
				}
				else{
					return -1;
				}
			}
			if(sentinella==1){
				if(punt->son ==NULL){
					if(punt->prev!=NULL){
						punt->prev->next= punt->next;
					}
					else{
						padre->son=punt->next;
					}
					if(punt->next != NULL){
						punt->next->prev=punt->prev;
					}
					free(punt);
					return 1;
				}
				else return -1;
			}
		}
	}
	return -1;
}
void delete_r(char* percorso){
	struct nodo* padre = &root;
	delete_r_ric(percorso, padre,1);
}
void delete_r_ric(char*percorso, struct nodo* padre, int se_prima_volta){
	int sentinella=0;char *a;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella==1){
		struct nodo*punt= padre->son;
		if(punt !=NULL){
			while(strcmp(a, punt->name)!=0 && sentinella ==1){
				if(punt->next!= NULL){
					punt=punt->next;
				}
				else{
					sentinella=-1;
				}
			}
			if(sentinella==1){
				while(punt->son!=NULL){
					char *d;
					d=(char*)malloc(nbytes+1);
					strcpy(d, "/");
					strcat(d,punt->son->name);
					delete_r_ric(d,punt,0);
				}
				char *h;
				h=(char*)malloc(nbytes+1);
				strcpy(h, "/");
				strcat(h, punt->name);
				int i= delete_ric(h,padre);
				if(se_prima_volta==1){
					if(i==1){
						OK;
					}
					else NO;
				}
			}
		}
		else{
			sentinella=-1;
		}
	}
	if(sentinella==-1){
		NO;
	}

}
void write(char*percorso,char*contenuto){
	struct nodo* padre = &root;
	write_ric(percorso, contenuto, padre);
}
void write_ric(char*percorso, char*contenuto, struct nodo* padre){
	int sentinella=0;char *a;
	a=(char*)malloc(nbytes+1);
	padre= pos_effettiva(a, &sentinella, percorso, padre);
	if(sentinella==1){
		struct nodo*punt= padre->son;
		if(punt !=NULL){
			while((strcmp(a, punt->name)!=0 || punt->file==0) && sentinella ==1){
				if(punt->next!= NULL){
					punt=punt->next;
				}
				else{
					sentinella=-1;
				}
			}
			if(sentinella==1){
				int y=0;
				punt->contenuto = contenuto;
				while (contenuto[y+2]!= '"'){
					y=y+1;
				}
				printf("ok %d\n", y);
			}
		}
		else{
			sentinella =-1;
		}
	}
	if(sentinella==-1){
		NO;
	}
}
struct nodo* pos_effettiva( char* a, int *punt_sentinella, char *percorso, struct nodo *padre){
	int k=0; int z=1;
	while(*punt_sentinella==0){
		k=k+1;
		if(k>255){
			*punt_sentinella =-1;
		}
		else{
			int i=0;
			while (percorso[i+z]!= '/' && *punt_sentinella==0){
				a[i]=percorso[i+z];
				i++;
				if(i==N+1){
					*punt_sentinella=-1;
				}
				else if(percorso[i+z]== '\0'){
					*punt_sentinella=1;
					a[i]=percorso[i+z];
				}
			}
			a[i]='\0';
			z=z+i+1;
			if(*punt_sentinella==0){
				padre= padre->son;
				if(padre==NULL){
					*punt_sentinella=-1;

				}
				else{
					while((strcmp(padre->name,a)!=0||padre->file==1) && *punt_sentinella==0 ){
						padre=padre->next;
						if(padre==NULL){
							*punt_sentinella=-1;
							break;
						}
					}
				}
			}
		}
	}
	return padre;
}
void find(char*name){
	char *da_stampare;
	da_stampare= (char*)malloc(nbytes+1);
	strcpy(da_stampare, "");
	struct nodo* padre= &root;
	struct elem_lista *primo_della_lista = NULL;
	 primo_della_lista= find_ric(name, da_stampare, padre,1, primo_della_lista);
	 print_(primo_della_lista);
}
struct elem_lista* find_ric(char*name,char*da_stampare, struct nodo* padre, int se_prima_volta, struct elem_lista* primo_della_lista){
	struct nodo*punt = padre->son;
	while(punt != NULL){
		char *da_stampare_locale;
		da_stampare_locale = (char*)malloc(nbytes+1);
		strcpy(da_stampare_locale, da_stampare);
		strcat(da_stampare_locale, "/");
		strcat(da_stampare_locale, punt->name);
		if(strcmp(name, punt->name)==0){
			primo_della_lista = insert(da_stampare_locale, primo_della_lista);
		}
		if(punt->file==0){
			primo_della_lista= find_ric(name, da_stampare_locale, punt,0, primo_della_lista );
		}
		punt=punt->next;
	}
	return primo_della_lista;
}
struct elem_lista* insert (char *da_stampare_locale, struct elem_lista* primo_della_lista){
	struct elem_lista *new_elem;
	new_elem = malloc(sizeof(struct elem_lista));
	new_elem->name= (char*)malloc(nbytes+1);
	strcpy(new_elem->name, da_stampare_locale);
	new_elem->next_elem=NULL;
	new_elem->prev_elem=NULL;
	if(primo_della_lista==NULL){
		primo_della_lista=new_elem;
	}
	else if(strcmp(da_stampare_locale, primo_della_lista->name)<=0){
		new_elem->next_elem=primo_della_lista;
		primo_della_lista->prev_elem=new_elem;
		primo_della_lista=new_elem;
	}
	else {
		int sen=0;
		struct elem_lista* punt;
		punt=primo_della_lista;
		while(strcmp(punt->name, da_stampare_locale)<0 &&sen==0){
			if(punt->next_elem==NULL){ //siamo arrivati in fondo, deve essere posizionato in fondo
				new_elem->prev_elem=punt;
				punt->next_elem=new_elem;
				new_elem->next_elem=NULL;
				sen=1;
			}
			else{
				punt=punt->next_elem;

			}
		}
		if(sen==0){ //vuol dire che non l'ho ancora posizionato
			new_elem->prev_elem= punt->prev_elem;
			new_elem->next_elem=punt;
			punt->prev_elem->next_elem = new_elem;
			punt->prev_elem=new_elem;
		}
	}
	return primo_della_lista;
}
void print_(struct elem_lista* punt){
	if(punt==NULL){
		NO;
	}
	while(punt !=NULL){
		printf("ok %s\n", punt->name);
		punt=punt->next_elem;
	}
}

