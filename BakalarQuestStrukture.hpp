#pragma once
#include <iostream>

class Soba {
	protected:
		short id;
		wchar_t opis[1000]; // upitno koliko ce se koristiti s obzirom da nemamo vremena izmisljati opise za sve sobe
		Soba *z, *j, *i, *s; // zapadno, juzno, istocno, sjeverno - poveznice sa spojenim sobama, u slucaju da nema sobe na toj strani, pokazivac je vrijednosti NULL
	public:
		void init()
		{
			this->id = 0;
			this->opis[0] = '\0';
			this->z = NULL;
			this->j = NULL;
			this->i = NULL;
			this->s = NULL;
		}
		void Opisi()
		{
			// PARSER CE, KADA DOBIJE ZAPOVIJED 'GLEDAJ', POTEGNUTI PROCEDURU 'OPISI' SOBE U KOJOJ SE IGRAC KOJI JE IZDAO NAREDBU NALAZI
			std::wcout << this->opis << std::endl;
		}
		short getID(Soba *x)
		{
			return x->id;
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
	protected:
		short id;
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
		bool potez(short s) 
		{
			switch (s)
			{
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
