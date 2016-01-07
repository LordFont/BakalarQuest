import socket
from threading import Thread, Lock
import os

lista_veza = list() #lista veza; koristi se za slanje poruka svim klijentima
lista_adresa = list() #lista adresa veze, sadrzi samo id adrese/veze
lock = Lock() #koristi se za rad s globalnim varijablima

def odvajanje(poruka, adrs): #funkcija koja mice komandu i stavlja ip adresu umjesto toga
  poruka = poruka.split()
  poruka[0] = adrs[0] + ':'
  poruka = ' '.join(poruka)
  poruka = poruka + '\n'
  return poruka

def komunikacija(veza,adresa):
  BUFFER_SIZE = 1024 #buffer za primljene podataka
  while 1:
    data = veza.recv(BUFFER_SIZE)#primi paket
    data = data.split()#Rastavi na rijeci. Ovo treba jer mice new line
    if len(data) < 1:
      veza.send("Spamate enter -.-'\n")#ako klijent spama enter
      continue
    else:
      data = ' '.join(data)#sastavi rijeci natrag u "recenicu"
    if data == "/izlaz":
      veza.send("Prekidam vezu...\n")
      print "Prekidam vezu s", adresa[0]
      lock.acquire()
      for j in range(len(lista_veza)):
	if lista_adresa[j] == adresa[1]:
	  lista_adresa.pop(j)
	  lista_veza.pop(j)#micanje veze iz lista veza
	  break
      lock.release()
      veza.close()#prekidanje veze
      break
    if data == "/server shutdown":
      print "Gasim server."
      os._exit(1)#gasi sve dretve i izlazi iz programa
    elif data.split()[0] == "/reci":
      data = odvajanje(data, adresa)
      print "Saljem poruku svim klijentima osim source:",data
      lock.acquire()
      for j in range(len(lista_veza)):
	if lista_adresa[j] != adresa[1]:
	  lista_veza[j].send(data)
      lock.release()#ova petlja salje svima poruku osim izvoru koji je poslao poruku
    elif data.split()[0] == "/ponovi":
      data = odvajanje(data, adresa)
      print "Vracam poruku:",data
      veza.send(data)#vraca istu poruku koji je klijent poslao
    elif data == "/pomoc":
      data = "/pomoc ->  prikazuje ovaj tekst\n"+"/izlaz ->  prekida vezu s serverom\n"+"/reci [poruka] ->  Saljes poruku ostalim igracima\n"+"/ponovi [poruka] ->  ponovi poslanu poruku\n"
      veza.send(data)
    else:
      veza.send("Ovo sto se napisali nema smisla...\n")
	

TCP_IP = "127.0.0.1"
#TCP_IP = "161.53.120.19"
TCP_PORT = 8880

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(50) #otvaranje veze

print "Server je startan."

while 1:
  conn, addr = s.accept() #prihvacanje veze
  print "Klijent spojen: ", addr #prikazuje tko se spojio
  lock.acquire()
  lista_veza.append(conn) #dodaju se inf o vezi
  lista_adresa.append(addr[1])
  lock.release()
  kom_veza = Thread(target=komunikacija, args=(conn,addr,))#definiranje dretve
  kom_veza.setDaemon(True)
  kom_veza.start()#zapocinje dretvu
