#pragma once
#include <iostream>

class Igrac {
	protected:
		short id;
		short pozicija;
		wchar_t nick[50];
	public:
		void init()
		{
			this->id = -1;
			this->pozicija = -1;
			this->nick[0] = '\0';
		}
		bool ucitajIgraca() 
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

class Soba {
	protected:
		short id;
		wchar_t opis[1000];
	public:
		void init()
		{
			this->id = 0;
			this->opis[0] = '\0';
		}
		void Opisi()
		{
			// PARSER CE, KADA DOBIJE ZAPOVIJED 'GLEDAJ', POTEGNUTI PROCEDURU 'OPISI' SOBE U KOJOJ SE IGRAC KOJI JE IZDAO NAREDBU NALAZI
			std::wcout << this->opis << std::endl;
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
