/*Progamma esame Lab.Programmazione Cesarano-Arcopinto*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>		//Libreria che include le funzioni per le stringhe
#include <stdbool.h>	//Libreria che include le variabili booleane
#include <time.h>		//Libreria che ci permettere di leggere la data e l'ora del sistema

struct account {		//Struct che contiene tutti i dati relativi l'account
    char nome[50];
    char cognome[50];
    int eta;
    char username[50];
    char password[50];
};
struct account a;	//Assegno ad a (Puntatore) la struttura account (RECORD)

long int size = sizeof(a);	//Assegno a size la dimenzione in byte della struttura a

struct post {				//Struct che contiene tutti i dati relativi ai post
	char pusername[50];
    char post[500];
    int numlike;
    char ora[50];
    char like[500];
};
struct post p;	//Assegno a p (puntatore) la struttura account(RECORD)

long int psize = sizeof(p);	//Assegno a psize la dimenzione in byte della struttura p
FILE *fp, *fpp, *ft, *ftp;	//Dichiaro i file che uso nel programma

//Dichiaro le funzioni che uso nel programma
void addaccount();
bool esiste(char tempusername[50]);
void addpost(char tempusername[50]);
void cercaaccount(char tempusername[50]);
void cercapost(char tempusername[50]);
void deleteaccount(char tempusername[50]);
void deletepost(char tempusername[50]);
void displayaccount();
void displaypost(char tempusername[50]);
void like(char tempusername[50]);
void removelike(char tempusername[50]);
bool loginaccount(char tempusername[50]);
void opzioniaccount(char tempusername[50]);

int main() //Inizio funzione principale
{
	int choice; //Variabile che contiene la scelta dello switch
    char username[50]; //Variabile che contiene l'username dell'account a cui vuoi loggare
    bool loggato; //Variabile booleana che contiene True se l'utente si è loggato correttamente
  
    fp = fopen("data.txt", "rb+"); //Apro il file (in lettura binaria) che contiene i dati degli account
    fpp = fopen("post.txt", "rb+"); //Apro il file (in lettura binaria) che contiene i post
  
    
    if (fp == NULL) {	//Se il file è vuoto prova ad aprire il file in scrittura
        fp = fopen("data.txt", "wb+");	
        
        if (fp == NULL) {	//Se il file è inaccessibile mostro un errore poichè il file non è apribile
            printf("\nNon riesco a connettermi al database degli account...");	
            exit(1); //Quindi esci dal programma è restituisci stato 1
            
        }
    }
    
      if (fpp == NULL) {
        fpp = fopen("post.txt", "wb+");
        
        if (fpp == NULL) {
            printf("\nNon riesco a connettermi al database dei post...");
            exit(1); //Quindi esci dal programma è restituisci stato 1
            
        }
    }
  
    printf("\n\n\n\n\t\t\t\t=====================================================");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t\t=====================================================");
    printf("\n\t\t\t\t[|:::>:::>:::>::>   SOCIALIZZIAMO   <::<:::<:::<:::|]\t");
    printf("\n\t\t\t\t=====================================================");
    printf("\n\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t\t\t=====================================================\n");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\tSviluppatori Agostino Cesarano\n");
    printf("t\t\t\t\t\t\t\t\t\t\t\te Alessandro Arcopinto\n\n\t\t\t\t");
  
    system("pause");
  
    while (1) { //Ripeti il ciclo fin quando non c'è una scelta
        system("cls");
        printf("\n1. LOGIN\n");
        printf("\n2. REGISTRATI\n");      
        printf("\n3. ESCI\n");
        printf("\nSCEGLI UN OPZIONE...\n");
        scanf("%d", &choice); //Input per la scelta dello switch
  
        switch (choice) {
        case 1:
      		system("cls");
      		
            printf("\nNome Utente : ");	
            scanf("%s", username); //Input dell'username dell'account a cui vuoi loggare
            
            loggato=loginaccount(username); //Assegna a loggato il valore di return di login account
            
			if(loggato){ //Se loggato = TRUE apri il menu account
            	opzioniaccount(username);
			}
			
            break; //Fine scelta 1

        case 2:
  
            addaccount(); //Apre la funzione che aggiunge un account
            
            break;	//Fine scelta 2
			  	    			
        case 3:
        	
            fclose(fp); //Chiude i file ed esce
            fclose(fpp);
            
            exit(0); //Fine scelta 3
            
            break;
  
        default: //Per default in caso di input di scelta non valido stampa un errore
        	
            printf("\nSCELTA NON VALIDA...\n");
        }
    }

} //Fine main

void addaccount() //Inizio funzione che aggiunge gli account
{
    system("cls"); //Pulisci la console
    fseek(fp, 0, SEEK_END); //Apri il file fp (quello che contiene i dati degli account) è posizionati alla fine
    
    	printf("ATTENZIONE! SI RACCOMANDA DI NON USARE SPAZI\n"); //Avviso per un corretto funzionamento del programma
    	
        printf("\nNome : ");
        scanf("%s", a.nome); //Input dei vari dati relativi all'account
        
        printf("\nCognome : ");
        scanf("%s", a.cognome);
        
        printf("\nEta' : ");
        scanf("%d", &a.eta);
        while(a.eta<16)
        {
        	printf("\nL'eta' minima per iscriversi e' di 16 anni"); //Nel caso in cui l'età è minore di 16 anni non è possibile l'iscrizione
        	printf("\nEta' : ");   
        	scanf("%d", &a.eta);
		}
        printf("\nUsername : ");
        scanf("%s", a.username);
		
        printf("\nPassword : ");
        scanf("%s", a.password);
        
        printf("\n\tAccount iscritto correttamente BENVENUTO SU SOCIALIZZIAMO!");
        
        printf("\n\n\n\t");
        system("pause"); //Premere un tasto per continuare
    	fwrite(&a, size, 1, fp); //Salva su file fp il record a
    	
} //Fine funzione addaccount

void addpost(char tempusername[50]) //Inizio funzione che aggiunge i post
{
    system("cls");
    
    int num=1; //Variabile che contiene il numero di post del nome utente che deve aggiungere un nuovo post
    rewind(fpp); //Apro di nuovo dall'inizio il file fpp (quello che contiene i post)
    
        while (fread(&p, psize,1, fpp)== 1) { //Leggo il record p dal file fpp fino a quando non ho più niente da leggere
        		if (strcmp(p.pusername, tempusername) == 0) { //Se l'username letto è uguale all'username dell account che vuole aggiungere il post
        			num++; //incrementa si uno la variabile num
				}
        	}
        	
        	if(num<11){ //Se num è minore di 11,quindi non vengono letti 10 post con lo stesso nome utente procedi con l'aggiunta del post
        	
        	fseek(fpp, 0, SEEK_END);  //Apri il file fpp (quello che contiene i post) è posizionati alla fine
        	
        	time_t currentTime; //Dichiaro una vaiabile time che conterrà la data e l'ora corrente
    		time(&currentTime);	//Immetti nella variabile time currentTime il tempo e l'ora
    		struct tm *localTime = localtime(&currentTime); //Dichiaro la struttura time
    		strftime(p.ora, 50, "Pubblicato alle %H:%M, del giorno %d/%m/%Y.", localTime); //Funzione che assegna a p.ora le informazioni dell'ora e della data in formato stringa 
    		
    		strcpy(p.pusername,tempusername); //Copia in p.username il valore di tempusername
    		
        	printf("\nNuovo post[%d]: ",num);
        	scanf(" %[^\n]s", p.post); //Leggi l'input fino all' immissione di \n quindi legge tutto ciò che è immesso fino al click di invio
        	p.numlike=0; //Setta il numero di like pari a 0
			        	
        	strcpy(p.like,"Nessun like"); //Setta p.like uguale a "Nessun LIke"
        	
    		fwrite(&p, psize, 1, fpp); //Salva sul file fpp il record p
    		
    		printf("\n\nHai creato un nuovo POST!\n\n");
			system("pause");
        	}
			else //Se il numero dei post è maggiore di 10 elimina prima un post
			{
					printf("Hai raggiunto il massimo numero di post,elimina prima un post");
					printf("\n\n\n\t");
					system("pause");
						
			}
			
} //Fine funzione addpost

void deleteaccount(char tempusername[50]) //Inizio funzione che elimina gli account
{
    system("cls");
    
    char scelta[3]; //Variabile che contiene la scelta (si/no)
    
		printf("\nSei sicuro di voler eliminare il tuo account e' tutti i post associati?(si/no) : ");
        scanf("%s", scelta); //Input di scelta
        
  		if (strcmp(scelta,"si") == 0) { //Se la scelta è uguale a si
  		
        ft = fopen("temp.txt", "wb+"); //Apri i file temporanei
        ftp = fopen("ptemp.txt", "wb+");
        
        rewind(fp); //Inizializza i file data e post
        rewind(fpp);
  
        while (fread(&a, size,1, fp)== 1) { //Leggo il record a dal file fp fino a quando non ho più niente da leggere
        		if (strcmp(a.username, tempusername) != 0) { //Se l'username letto è diverso dall'username dell account che vuole elimare il proprio account
            	fwrite(&a, size, 1, ft); //Scrivi sul file temporanio il record a escluso l'account da eliminare
            	}
		}
		        while (fread(&p, psize,1, fpp)== 1) { //Leggo il record p dal file fpp fino a quando non ho più niente da leggere
        		if (strcmp(p.pusername, tempusername) != 0) { //Se l'username dei post è diverso dall'username dell account che vuole elimare il proprio account
            	fwrite(&p, psize, 1, ftp); //Scrivi sul file temporanio il record p escluso i post da eliminare
            }
		}
  
        fclose(fp); //Chiudi tutti i file 
        fclose(ft);
        fclose(fpp);
        fclose(ftp);
        
        remove("data.txt"); //Elimina il file principale che contiene i post 
        rename("temp.txt", "data.txt"); //Rinomina il file temporanio che non contiene l'account eliminato con il nome del file principale
        fp = fopen("data.txt", "rb+"); //Apri nuovamente il file principale
        
        remove("post.txt");
        rename("ptemp.txt", "post.txt");
        fpp = fopen("post.txt", "rb+");
        printf("\n\nHai eliminato con successo il tuo account e i dati associati\n\n");
		system("pause");
        system("cls");
        main(); //Ritorna alla funzione principale
	}

} //Fine funzione deleteaccount

void deletepost(char tempusername[50]) //Inzio funzione che elimina i post
{
	char scelta[3];
	char premove[500]; //Variabile che contiene il post da eliminare
		
	system("cls");
	ftp = fopen("ptemp.txt", "wb+"); //Apro il file temporaneo che conterrà il file senza post eliminato
	rewind(fpp); //Inizzializza il file principale che contiene i post
		
    while (fread(&p, psize, 1, fpp) == 1 && strcmp(scelta,"si") != 0){ //Leggo il record p dal file fpp fino a quando non ho più niente da leggere
		if (strcmp(p.pusername, tempusername) == 0){ //Se l'username dei post è uguale all'username dell account loggato mostra tutti i suoi post 
			
		printf("\n@%s Post's \tPOST--> %s \n", p.pusername, p.post);	
        printf("\n\t\t\tNUMERO LIKE: %d \t %s\n\n\tUTENTI CHE HANNO MESSO LIKE--> %s", p.numlike, p.ora, p.like);
    	printf("\n====================================================================================================================\n");
    	printf("\nVuoi eliminare questo POST?(si/no) : ");
    	scanf("%s", scelta); //Input di scelta
    		if (strcmp(scelta,"si") == 0) { //Se scelta è uguale a si 
    		strcpy(premove,p.post); //premove sarà uguale a p.post
    		}
    	}
    }

    		rewind(fpp); //Inizzializza il file principale che contiene i post
        		while (fread(&p, psize, 1, fpp) == 1){ //Leggo il record p dal file fpp fino a quando non ho più niente da leggere
        			if(strcmp(p.post,premove)!=0){ //Se il post è diverso dal post da eliminare 
        			fwrite(&p, psize, 1, ftp); //Scrivi sul file temporanio il record p escluso il post da eliminare
					}
				}
							
			printf("\nHai elimato il POST scelto\n");
			printf("\n\n\n\t");
            system("pause");
            		
            fclose(fpp); //Chiudi i file aperti
			fclose(ftp);
	
    		remove("post.txt"); //Rimuovi il file principale
    		rename("ptemp.txt", "post.txt"); //Rinomina il file temporaneo che non contiene il post eliminato col nome del file principale
    		fpp = fopen("post.txt", "rb+"); //Apri nuovamente il file principale
          	


} //Fine funzione deletepost

void displayaccount() //Inizio funzione che ci fa visualizzare gli account iscritti
{
    system("cls");
    rewind(fp); //Inizzializzo il file
    
    printf("\n====================================================================================================================");
    printf("\nNOME\t\t\tCOGNOME\t\t\tETA\t\t\tUSERNAME\n");
    
    while (fread(&a, size, 1, fp) == 1){ //Leggo il record a dal file è lo stampo
    
        printf("\n%s \t \t %s \t \t %d \t \t %s\n",a.nome, a.cognome, a.eta, a.username); 
  	}
  	printf("\n====================================================================================================================\n");
    printf("\n\n\n\t");
    system("pause");
} //Fine funzione displayaccount

void displaypost(char tempusername[50]) //Inizio funzione che ci fa visualizzare i post degli iscritti
{
    system("cls");
    rewind(fpp);  //Inizzializzo il file
    
    char scelta[3]; //Variabile che contiene la scelta (si/no)
    
    printf("\n====================================================================================================================\n");
    while (fread(&p, psize, 1, fpp) == 1){ //Leggo il record p dal file è lo stampo
    
		printf("\n@%s Post's \tPOST--> %s \n", p.pusername, p.post);	
        printf("\n\t\t\tNUMERO LIKE: %d \t %s\n\n\tUTENTI CHE HANNO MESSO LIKE--> %s", p.numlike, p.ora, p.like);
    	printf("\n====================================================================================================================\n");
	}
	
   	printf("\nVuoi mettere like ad uno di questi POST?(si/no): ");
    scanf("%s", scelta); //Input di scelta
    
  	if (strcmp(scelta,"si") == 0) { //Se scelta è uguale a si chiama la funzione like
		like(tempusername);
  	}
} //Fine funzione displaypost

void cercaaccount(char tempusername[50]) //Inizio funzione che ci fa visualizzare un account a nostra scelta
{
	
    system("cls");
    rewind(fp); //Inizzializzo il file
    
    printf("\n====================================================================================================================");
    printf("\nNOME\t\t\tCOGNOME\t\t\tETA\t\t\tUSERNAME\n");
    while (fread(&a, size, 1, fp) == 1){ //Leggo il record a dal file
    
    	if (strcmp(a.username, tempusername) == 0) { //Se l'username degli account è uguale all'username dell account da cercare stampalo
    	
        printf("\n%s\t\t%s\t\t%d\t\t\t%s",a.nome, a.cognome, a.eta, a.username); 
    	printf("\n====================================================================================================================\n");
       }
   }
    cercapost(tempusername); //Stampa anche i post dell'account cercato
} //Fine funzione cercaaccount

void cercapost(char tempusername[50]) //Inizio funzione che ci fa visualizzare i post dell'account cercato
{
    rewind(fpp); //Inizzializzo il file
    
    while (fread(&p, psize, 1, fpp) == 1){ //Leggo il record p dal file è lo stampo
		if (strcmp(p.pusername, tempusername) == 0) { //Se l'username dell'account che ha pubblicato il post è uguale all'username dell account da cercare stampalo
			
		printf("\n@%s Post's \tPOST--> %s \n", p.pusername,p.post);	
        printf("\n\t\t\tNUMERO LIKE: %d \t %s\n\n\tUTENTI CHE HANNO MESSO LIKE--> %s", p.numlike, p.ora, p.like);
    	printf("\n====================================================================================================================\n");
        }
}	
    
    printf("\n\n\n\t");
    system("pause");
} //Fine funzione cercapost

void like(char tempusername[50]) //Inizio funzione che ci permette di mettere like ad un post
{
	char username[50]; //Variabile che contiene l'username a cui vuoi mettere like
	char scelta[3]; //Variabile che contiene la scelta (si/no)
		
	ftp = fopen("ptemp.txt", "wb+"); //Apro il file temporaneo
	rewind(fpp); //Inizzializzo il file principale
		
	printf("\nInserisci l'username a cui vuoi mettere like: ");
	scanf("%s", username); //Input username
	system("cls");

    while (fread(&p, psize, 1, fpp) == 1){ //Leggo il record p dal file è lo stampo
    
		if (strcmp(p.pusername, username) == 0){ //Se l'username dell'account che ha pubblicato il post è uguale all'username dell account da cercare stampalo
			
		printf("\n@%s Post's \tPOST--> %s \n", p.pusername, p.post);	
        printf("\n\t\t\tNUMERO LIKE: %d \t %s\n\n\tUTENTI CHE HANNO MESSO LIKE--> %s", p.numlike, p.ora, p.like);
    	printf("\n====================================================================================================================\n");
    	printf("\nVuoi mettere like a questo POST?(si/no): ");
    	scanf("%s", scelta); //Input scelta

    		if (strcmp(scelta,"si") == 0) { //Se scelta è uguale a si	
				if(strcmp(p.like,"Nessun like")==0){ //se p.like è uguale a "Nessun LIke"
					
					p.numlike++; //Incrementa il numero di like
					strcpy(p.like,"\n\t"); //Copia \n\t in p.like
					strcat(p.like,tempusername); //Aggiungi a p.like tempusername cioè il nome utente di chi mette like
					printf("\nHai messo like al POST\n");
					printf("\n\n\n\t");
            		system("pause");
				}
				else
				{
					if(strstr(p.like,tempusername)==NULL){ //Se il nome utente di chi mette like non è contenuto in p.like
					
							p.numlike++; //Incrementa il numero di like
							strcat(p.like,"\n\t"); //Aggiungi \n\t in p.like
							strcat(p.like,tempusername); //Aggiungi a p.like tempusername cioè il nome utente di chi mette like
							printf("\nHai messo like al POST\n");
							printf("\n\n\n\t");
            		        system("pause");
					}
					else //Se il nome utente di chi mette like è già contenuto in p.like
					{
						printf("\nHai gia' messo like a questo POST! \n"); //Quindi non c'è bisogno di rimetterlo
						printf("\n\n\n\t");
						system("pause");
					}

				}
			}		
    	}
    fwrite(&p, psize, 1, ftp); //Scrivi nel file temporanio i post + il post a cui hai messo like
    }
    
    fclose(fpp); //Chiudi i file aperti
	fclose(ftp);
	
    remove("post.txt"); //Rimuovi il file principale
    rename("ptemp.txt", "post.txt"); //Rinomina il file temporaneo che non contiene il post eliminato col nome del file principale
    fpp = fopen("post.txt", "rb+"); //Apri nuovamente il file principale
} //Fine funzione like

void removelike(char tempusername[50]) //Inizio funzione che ci permette di rimuovere like ad un post
{
	system("cls");
	char scelta[3]; //Variabile che contiene la scelta (si/no)
	char uremove[50]; //Variabile che contiene la stringa da sottrarre
		
	ftp = fopen("ptemp.txt", "wb+"); //Apro il file temporaneo
	rewind(fpp); //Inizzializzo il file principale
	
    while (fread(&p, psize, 1, fpp) == 1){ //Leggo il record p dal file è lo stampo
		if(strstr(p.like,tempusername)!=NULL){ //Se il nome utente di chi è loggato è contenuto in p.like (quindi è nei like) stampa il post

		printf("\n@%s Post's \tPOST--> %s \n", p.pusername, p.post);	
        printf("\n\t\t\tNUMERO LIKE: %d \t %s\n\n\tUTENTI CHE HANNO MESSO LIKE--> %s", p.numlike, p.ora, p.like);
    	printf("\n====================================================================================================================\n");
    	printf("\nVuoi togliere like a questo POST?(si/no): ");
    	scanf("%s", scelta); //Input scelta
    			
    		if (strcmp(scelta,"si") == 0) {
    		
    		strcpy(uremove, "\n\t");
    		strcat(uremove, tempusername);
			p.numlike--;
			
				size_t substrlen;
    			char *pos = NULL;
    			if(p.like && uremove && *p.like && *uremove){
        			if(pos = strstr(p.like, uremove)){
            		substrlen = strlen(uremove);
            		memmove(pos, pos + substrlen, strlen(p.like) - substrlen + 1);
        			}
				}
				
				if(strlen(p.like)==0){
				strcpy(p.like,"Nessun like");
				}
			printf("\nHai tolto like al POST\n");
			printf("\n\n\n\t");
            system("pause");
			}
		}
    fwrite(&p, psize, 1, ftp); //Scrivi nel file temporanio i post + il post a cui hai tolto like
    }
    
    fclose(fpp); //Chiudi i file aperti
	fclose(ftp);
	
    remove("post.txt"); //Rimuovi il file principale
    rename("ptemp.txt", "post.txt"); //Rinomina il file temporaneo che non contiene il post eliminato col nome del file principale
    fpp = fopen("post.txt", "rb+"); //Apri nuovamente il file principale
} //Fine funzione removelike

bool loginaccount(char tempusername[50]) //Inizio funzione che permette di fare il login
{
    char temppassword[50];
    
    printf("\nPassword : ");
    scanf("%s", temppassword); //Rinserisci la password
    rewind(fp); //Inizializzo il file
    
    while (fread(&a, size, 1, fp) == 1){ //Leggo il record a dal file
        if (strcmp(a.username, tempusername) == 0) { //Se l'username letto è uguale all'username dell account che vuole loggare
            if(strcmp(a.password, temppassword) == 0) //Se la password è uguale alla password letta
            {
            printf("\nLoggato Correttamente\n\n");
            system("pause");
            return true; //La funzione restituisce true
			}
			else
			{
            printf("\nPassword errata\n\n");
            system("pause");
            return false; //La funzione restituisce false
			}			
		}	
	}
} //Fine funzione loginaccount

void opzioniaccount(char tempusername[50]) //Inizio funzione che ci stampa il menu utente
{
	int choice; //Variabile che contiene la scelta dello switch
	char usertofind[50]; //Variabile che contiene il nome utente da cercare

	   	while (1) { //Ripeti il ciclo fin quando non c'è una scelta
		system("cls");
		printf("Sei correttamente loggato ad @%s\n",tempusername);
	    printf("\n1. VISUALIZZA GLI ACCOUNT ISCRITTI\n");
	    printf("\n2. VISUALIZZA I POST DEGLI ISCRITTI\n");
	    printf("\n3. CERCA UN ACCOUNT E I SUOI POST\n");
	    printf("\n4. IL TUO ACCOUNT E I TUOI POST\n");
	    printf("\n5. ELIMINA UNO DEI TUOI POST\n");
	    printf("\n6. METTI LIKE AD UN POST\n");
	    printf("\n7. POST A CUI HAI MESSO LIKE\n");
	    printf("\n8. CREA UN NUOVO POST\n");
        printf("\n9. ELIMINA IL TUO ACCOUNT E' I POST ASSOCIATI\n");  
        printf("\n10. LOGOUT\n");        
		printf("\nSCEGLI UN OPZIONE...\n");
        scanf("%d", &choice); //Input per la scelta dello switch
  
        switch (choice) {
        case 1:
  
            displayaccount();
            break;
        
        case 2:
        	
        	displaypost(tempusername);
        	break;
        	
        case 3:
        	
        	printf("\nNome Utente da cercare : ");
    		scanf("%s", usertofind);
        	cercaaccount(usertofind);
        	break;
        	
        case 4:
  			
			cercaaccount(tempusername);
        	break;
        
        case 5:
  			
			deletepost(tempusername);
        	break;
        	
        case 6:
  			
			like(tempusername);
        	break;
        
    	case 7:
  
        	removelike(tempusername);
        	break;
        	
        case 8:
  
        	addpost(tempusername);
        	break;
            
        case 9:
  
            deleteaccount(tempusername);
            break;
            
        case 10:
        	
        	system("cls");
        	main();
        	break;
        	
        default:
        printf("\nSCELTA NON VALIDA...\n");
        }
	}
} //Fine funzione opzioniaccount

