//Farruku Juri

#ifndef GAME_H
#define GAME_H

#include "griglia_difesa.h"
#include "griglia_attacco.h"
#include "Nave.h"
#include "Sottomarino.h"
#include "Nave_supporto.h"
#include "Corazzata.h"
#include <vector>

#include <iostream>

// classe game

class game
{

	private:
		griglia_difesa griglia_difensiva;
		griglia_attacco griglia_offensiva;
		bool done=false;
		Corazzata corazzate[3];	//array contenente il numero di corazzate
		Nave_supporto supporti[3];	// array contenente il numero di supporti 
		Sottomarino sottomarini[2];	// array contenente il numero di sottomarini
		char tipo_giocatore;


	public:
		
		struct Nessuna_nave_presente : std::runtime_error	//Eccezione: non sono state trovate navi nella posizione indicata
		{
			Nessuna_nave_presente():runtime_error("Nessuna_nave_presente si e' verificata") {}
		};
		
		struct Parametri_invalidi : std::runtime_error	//Eccezione
		{
			Parametri_invalidi():runtime_error("Parametri_invalidi si e' verificata") {}
		};
		
		void set_tipo_giocatore(char tipo) {tipo_giocatore = tipo;};	//imposta se computer o giocatore
		char get_tipo_giocatore(void) {return tipo_giocatore;}	//funzione restituzione

		//costruttori
		game(void);
		game(const game& g);	//costruttore di copia
		void set_ship (std::string prua, std::string poppa,char type_ship,int number_ship,int dimensione);	//invoca il metodo per posizionare le navi sulla griglia di difesa
		void ripara_barche(std::string coordinata_centro);
		void user_griglia();	//stampa le griglie d'attacco e di difesa del giocatore
		int find_ship(int x_pos, int y_pos, char tipo_nave);	//funzione per trovare barche
		bool check_azione (int x_centro,int y_centro, char& type_ship, int& index);	//controllo possibilità di compiere un'azione
		void make_azione (game& enemy,std::string sorgente, std::string bersaglio);	//compie l'azione specifica per ogni nave
		griglia_difesa&   return_griglia_difesa(){return griglia_difensiva ;}
		griglia_attacco&  return_griglia_attacco(){return griglia_offensiva ;}
		Corazzata& get_corazzata(int index){ return corazzate[index];}	//restituisce una corazzata appartenente all'array di corazzate
		Sottomarino& get_sottomarino(int index){ return sottomarini[index];}	//restituisce un sottomarino appartenente all'array di sottomarini 
		Nave_supporto& get_supporto(int index){ return supporti[index];}	//restituisce un supporto appartenente all'array di supporti
		int get_centri_corazzate(std::vector<int>& x_centri, std::vector<int>& y_centri); 
		int get_centri_sottomarini(std::vector<int>& x_centri, std::vector<int>& y_centri);
		int get_centri_supporti(std::vector<int>& x_centri, std::vector<int>& y_centri);

};


#endif //GAME_H
