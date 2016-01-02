#pragma once
#include <iostream>

class Soba {
	// Podaci o svim sobama ce se cuvati u polju u programu
	protected:
		short id; // id sobe jest istovremeno indeks elementa polja u kojem se cuvaju u RAM-u, -1 znaci da ne postoji
		wchar_t kopis[50];
		wchar_t opis[1000]; // upitno koliko ce se koristiti s obzirom da nemamo vremena izmisljati opise za sve sobe
		short s, i, j, z, d, g; // zapadno, juzno, istocno, sjeverno, dolje, gore - poveznice sa spojenim sobama, oznacava indeks sobe, u slucaju da nema sobe na toj strani, vrijednost je -1
	public:
		void init()
		{
			this->id = -1;
			this->kopis[0] = '\0';
			this->opis[0] = '\0';
			this->s = -1;
			this->i = -1;
			this->j = -1;
			this->z = -1;
			this->g = -1;
			this->d = -1;
		}
		void Opisi()
		{
			// PARSER CE, KADA DOBIJE ZAPOVIJED 'GLEDAJ', POTEGNUTI PROCEDURU 'OPISI' SOBE U KOJOJ SE IGRAC KOJI JE IZDAO NAREDBU NALAZI
			std::wcout << this->opis << std::endl;
		}
		bool ucitaj(short id, wchar_t opis, Soba *izlazi[4])
		{
			/*
			SQL UPITOM SE PUNE PODACI O SOBI IZ BAZE
			this->id = id;
			memcpy(this->opis, opis, sizeof(opis));
			this->z = izlazi[0];
			this->j = izlazi[1];
			this->i = izlazi[2];
			this->s = izlazi[3];
			*/
		}
};

class Igrac {
	// Podaci o spojenim igracima bi se isto mogli drzati u polju u programu
	protected:
		short id;
		/*
		struct postavke{
			bool kopis;
		};
		*/
		short pozicija; // ID sobe u kojoj se nalazi igrac
		wchar_t nick[50];
	public:
		void init()
		{
			this->id = -1;
			this->pozicija = -1;
			this->nick[0] = '\0';
		}
		bool ucitaj() 
		{
			/*
			VADI SE SA SQL UPITOM, VRAÆA NULU U SLUÈAJU GREŠKE
			this->id = bazaIgraca.id;
			this->nick = bazaIgraca.nick;
			this->pozicija = bazaPoz.pozicija;
			*/
		}
		bool potez(char s) 
		{
		// Poziva text parser i proslijeðuje zapovijed
			switch (s)
			{
				case 'z':
					break;
				case 'j':
					break;
				case 'i':
					break;
				case 's':
					break;
				case 'd':
					break;
				case 'g':
					break;
				default: break;
			}
		}
};

class Predmet{
	protected:
		short id;
		wchar_t naziv[50];
	public:
		void init()
		{
			this->id = 0;
			this->naziv[0] = '\0';
		}
};