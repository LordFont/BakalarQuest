class Igrac:

    def __init__(self):
        self.id = -1;
        self.nick = ""
        self.pozicija = -1;

    def ucitaj(self):
        """
        Ovdje ide SQL skripta koja ce ucitati podatke iz baze
        """

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
        self.id = -1
        self.kopis = ""
        self.opis = ""
        self.s = -1
        self.i = -1
        self.j = -1
        self.z = -1
        self.d = -1
        self.g = -1

    def getAdjecent(pozicija, smjer):
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
    
