import mysql.connector as db

class Igrac:

    def __init__(self):
        self.idd = -1
        self.nick = ""
        self.pozicija = -1

    def ucitaj(self, nick):
        """
        Ovdje ide SQL skripta koja ce ucitati podatke iz baze
        """
        db_name = 'BakalarQuest'
        con = db.connect(user='root', password='pass')
        cur = con.cursor()

        con.database = db_name

        cur.execute('SELECT * FROM IGRAC WHERE nickname=' + nick + ';')

        for idd, nickname, username, password, pozicija in cur:
            res = [idd, nickname, pozicija]
            self.idd = res[0]
            self.nick = res[1]
            self.pozicija = res[2]

        cur.close()
        con.close()

    def potez(self, smjer):
        """
        Text parser poziva ovu funkciju
        """
        if smjer == 's':
            self.pozicija = getAdjecent(self.pozicija, 's')
        elif smjer == 'i':
            self.pozicija = getAdjecent(self.pozicija, 'i')
        elif smjer == 'j':
            self.pozicija = getAdjecent(self.pozicija, 'j')
        elif smjer == 'z':
            self.pozicija = getAdjecent(self.pozicija, 'z')
        elif smjer == 'd':
            self.pozicija = getAdjecent(self.pozicija, 'd')
        elif smjer == 'g':
            self.pozicija = getAdjecent(self.pozicija, 'g')


class Soba:

    def __init__(self):
        self.idd = -1
        self.kopis = ""
        self.opis = ""
        self.s = -1
        self.i = -1
        self.j = -1
        self.z = -1
        self.d = -1
        self.g = -1

    def getAdjecent(self, smjer):
        if smjer == 's':
            return self.s
        elif smjer == 'i':
            return self.i
        elif smjer == 'j':
            return self.j
        elif smjer == 'z':
            return self.z
        elif smjer == 'd':
            return self.d
        elif smjer == 'g':
            return self.g

    def ucitaj(self, idd):
        db_name = 'BakalarQuest'
        con = db.connect(user='root', password='pass')
        cur = con.cursor()

        con.database = db_name

        cur.execute('SELECT * FROM SOBA WHERE id=' + str(idd) + ';')

        for idd, opis, s, i, j, z, d, g in cur:
            res = [idd, opis, s, i, j, z, d, g]
            self.idd = res[0]
            self.opis = res[1]
            self.s = res[2]
            self.i = res[3]
            self.j = res[4]
            self.z = res[5]
            self.d = res[6]
            self.g = res[7]

        cur.close()
        con.close()
    
