#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
using namespace std;

//polje u kojem se spremaju veze
int niz_klijenata[100];
char const* ip_adresa[100];
//var za pracenje broja veza
int k = 0;
mutex mtx;


//preuzeto iz Beej's Guide to Network Programming, sluzi kao dio koji uzima IP adresa u pretvori ga u string
void *get_in_addr(struct sockaddr *sa){
    if (sa->sa_family == AF_INET) {
    return &(((struct sockaddr_in*)sa)->sin_addr);
    }
}

//funkcija koja mice vezu od polja
void odspajanje(int veza){
      //integer za oznaku gdje se u polju nalazi veza
      int br_red;
      mtx.lock();
      //petlja koja trazi vezu, uzima redni broj i brise vezu
      for(int i = 0; i<k;i++){
	if(veza == niz_klijenata[i]){
	  br_red = i;
	  niz_klijenata[i] = 0;
	  break;
	}
      }
      //petlja koja premjestava sve veze za jedan iza u polju, jer je sad razmak
      for(int i = br_red;i<k;i++){
	niz_klijenata[i] = niz_klijenata[i+1];
	ip_adresa[i] = ip_adresa[i+1];
      }
      //smanjuje varijablu za pracenje borja veza za jedan
      k--;
      mtx.unlock();
}

void komunikacija(int veza, char buffer[], int buff_velicina, int socket, char const* u_adresa){
      //stavljanje ip adrese u nesto koristljivo
      char ip_adress[20];
      strcpy(ip_adress, u_adresa);
      cout<<ip_adress<<": "<<strlen(ip_adress)<<endl;
      for(int i = 0; i<=strlen(ip_adress);i++){
	if(i == strlen(ip_adress)){
	  cout<<i<<endl;
	  ip_adress[i] = ':';
	  ip_adress[i+1] = ' ';
	  ip_adress[i+2] = '\0';
	  break;
	}
      }
      cout<<ip_adress<<": "<<strlen(ip_adress)<<endl;
      //var j sluzi za prepoznavanje same poruke i komande
      int j = 0;
      //polje u kojem se sprema komanda
      char commanda[10000];
      //polje u kojem se sprema tekst npr. za /say
      char meso_poruke[10000];
      //poruka koji dolazi od klijenta se sprema iz bufera ovdje. Buffer must be free!
      char poruka[10000];
      
      //varijabla za recv
      int prihvaceno;
      while(1){
	//resetiranje svih spremnika
	memset(commanda,0,10000);
	memset(poruka,0,10000);
	memset(meso_poruke,0,10000);
	//cekanje i prihvacanje paketa od klijenta
	prihvaceno = recv(veza,buffer,buff_velicina, 0);
	//prebacivanje od buffera u poruku
	strcpy(poruka, buffer);
	//pronalazenje razmaka izmesju komande i poruke
	while((poruka[j]!=32)&&(j<strlen(poruka)-2))j++;
	//prebacivanje komande
	for(int i = 0;i<j;i++)commanda[i]=poruka[i];
	//prebacivanje same poruke
	for(int i = j+1;i<strlen(poruka);i++)meso_poruke[i-(j+1)]=poruka[i];
	//stavljanje oznake za kraj stringa
	commanda[j]='\0';
	//resetiranje oznake
	j = 0;
	//resetiranje buffera
	memset(buffer,0,buff_velicina);
	//if za prekidanje veze
	if(!strcmp(commanda, "/exit")){
	  socket = send(veza, "Veza se prekida \n",strlen("Veza se prekida \n"), 0);
	  close(veza);
	  odspajanje(veza);
	  cout<<"Veza je prekinuta"<<endl;
	  break;
	};
	//if za gasenje servera
	if(!strcmp(commanda, "/server_shutdown")){
	  cout<<"Gasim server"<<endl;
	  exit(0);
	};
	//if za gasenje servera
	if(!strcmp(commanda, "/spojen")){
	  cout<<"Klijent pita ako je spojen."<<endl;
	  socket = send(veza, "Spojen! \n",strlen("Spojen! \n"), 0);
	}
	//if za vracanje mesa_poruke samo klijentu
	if(!strcmp(commanda, "/echo")){
	  cout<<"Server vraca meso poruke."<<endl;
	  socket = send(veza, meso_poruke,strlen(meso_poruke), 0);
	}
	//if za slanje poruke svima koji su spojeni
	if(!strcmp(commanda, "/say")){
	    mtx.lock();
	    for(int i = 0; i<k; i++){
	      socket = send(niz_klijenata[i], ip_adress,strlen(ip_adress), 0);
	      socket = send(niz_klijenata[i], meso_poruke,strlen(meso_poruke), 0);
	    }
	    mtx.unlock();
	}
      }
}


int main(){
  //integeri za razlicite funkcije vezane uz spajanje
  int povratna;
  int opisnik, opisnik_klijent;
  int priv_red = 0;
  
  //buffer i i mjesto gdje se stavlja poruka dobivena od strane klijenta
  char buff[10000];
  char ip_adr_inet[20];
  //char const* ip_adresa;
  
  //deklaracija varijabli vezanih uz adrese
  struct addrinfo upute;
  struct addrinfo *rezultat;
  struct sockaddr_storage adresa_klijent;
  
  //deklaracija varijabli za velicinu adrese klijenta
  socklen_t adresa_klijent_velicina;
  
  //postavljanje memorijskog bloka upute na vrijednost nula, velicina strukture addrinfo
  memset(&upute, 0, sizeof(struct addrinfo));
  
  //postavljanje servera za TCP
  upute.ai_family = AF_INET; // IPv4
  upute.ai_socktype = SOCK_STREAM;//TCP
  povratna = getaddrinfo("127.0.0.1", "8880", &upute, &rezultat);//Postavlja se vrijednosti vezane uz server
  
  opisnik = socket(rezultat->ai_family, rezultat->ai_socktype, rezultat->ai_protocol);//postavlja se socket
  povratna = ::bind(opisnik, rezultat->ai_addr, rezultat->ai_addrlen);//povezuje se socket s ovim programom
  
  //oslobadja informacije o adresama
  freeaddrinfo(rezultat);
  //slusa na portu definiranom u opisnik, maksimalno 5 veza
  povratna = listen(opisnik, 5);
  while(1){
    //postavljanje velicine adrese klijenta
    adresa_klijent_velicina = sizeof adresa_klijent;
    //prihvacanje veze
    opisnik_klijent = accept(opisnik, (struct sockaddr *)&adresa_klijent, &adresa_klijent_velicina);
    //upisujemo vezu u polje veza
    mtx.lock();
    ip_adresa[k] = inet_ntop(adresa_klijent.ss_family, get_in_addr((struct sockaddr *)&adresa_klijent), ip_adr_inet, sizeof(ip_adr_inet));
    cout<<ip_adresa[k]<<": Veza s klijentom uspostavljena"<<endl;
    niz_klijenata[k] = opisnik_klijent;
    priv_red = k;
    k++;
    mtx.unlock();
    //odgovor da smo prihvatili vezu
    povratna = send(opisnik_klijent, "Spojeni ste s serverom \n", strlen("Spojeni ste s serverom \n"), 0);
    //fukcija koja radi na samoj komunikaciji izmedju server i klijenta
    thread proces(komunikacija,opisnik_klijent,buff,sizeof(buff),povratna,ip_adresa[priv_red]);
    proces.detach();
  }
  
  return 0;
}
