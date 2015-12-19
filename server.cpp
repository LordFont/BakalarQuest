#include <sys/types.h>
#include <sys/socket.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void komunikacija(int veza, char buffer[], int buff_velicina){
      //sadrzaj iz paketa koji ce se nalaziti u bufferu se sprema ovdje
      char poruka[10000];
      //varijabla za recv
      int prihvaceno;
      while(1){
	//cekanje i prihvacanje paketa od klijenta
	int prihvaceno = recv(veza,buffer,buff_velicina, 0);
	//prebacivanje od buffera u poruku
	strcpy(poruka, buffer);
	//ova petlja mice 'enter' tj. new line znak
	for(int i=0;i<strlen(poruka);i++){
	  if(i==(strlen(poruka)-2)){
	    poruka[i] = '\0';
	    break;
	    }
	}
	//resetiranje buffera
	memset(buffer,0,buff_velicina);
	//if za prekidanje veze
	if(!strcmp(poruka, "/exit")) break;
	//if za gasenje servera
	if(!strcmp(poruka, "/server_shutdown"))exit(0);
      }
}


int main(){
  //integeri za razlicite funkcije vezane uz spajanje
  int povratna;
  int opisnik, opisnik_klijent;
  
  //buffer i i mjesto gdje se stavlja poruka dobivena od strane klijenta
  char buff[10000];
  
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
  povratna = bind(opisnik, rezultat->ai_addr, rezultat->ai_addrlen);//povezuje se socket s ovim programom
  
  //oslobadja informacije o adresama
  freeaddrinfo(rezultat);
  //slusa na portu definiranom u opisnik, maksimalno 5 veza
  povratna = listen(opisnik, 5);
  while(1){
    //postavljanje velicine adrese klijenta
    adresa_klijent_velicina = sizeof adresa_klijent;
    //prihvacanje veze
    opisnik_klijent = accept(opisnik, (struct sockaddr *)&adresa_klijent, &adresa_klijent_velicina);
    cout<<"Veza s klijentom uspostavljena"<<endl;
    //odgovor da smo prihvatili vezu
    povratna = send(opisnik_klijent, "Spojeni ste s serverom \n", strlen("Spojeni ste s serverom \n"), 0);
    //fukcija koja radi na samoj komunikaciji izmedju server i klijenta
    komunikacija(opisnik_klijent,buff,sizeof(buff),poruka);
    //prekidanje veze
    povratna = send(povratna, "Veza se prekida \n",strlen("Veza se prekida \n"), 0);
    close(opisnik_klijent);
    cout<<"Veza je prekinuta"<<endl;
  }
  return 0;
}
