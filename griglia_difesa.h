//Francesco Carretta

#ifndef GRIGLIA_DIFESA_H
#define GRIGLIA_DIFESA_H


#include "griglia.h"
#include "Nave.h"
#include "Sottomarino.h"
#include "Nave_supporto.h"
#include "Corazzata.h"

//classe griglia_difesa, derivata di griglia

class griglia_difesa : public griglia
{
	public:
		struct Posizione_occupata : std::runtime_error	//Eccezione: viene lanciata quando si cerca di inserire un valore in una casella già occupata
		{
			Posizione_occupata():runtime_error("Posizione_occupata si e' verificata") {}
		};

		struct Posizione_illegale : std::runtime_error	//Eccezione: viene lanciata quando si inseriscono navi in posizioni non valide (es. in obliquo)
		{
			Posizione_illegale():runtime_error("Posizione_illegale si e' verificata") {}
		};

		struct Dimensione_errata : std::runtime_error	//Eccezione: viene lanciata quando le coordinate passate non rispecchiano alcuna dimensione di nave
		{
			Dimensione_errata():runtime_error("Dimensione_errata si e' verificata") {}
		};
	
		// costruttori
		griglia_difesa(void);
		griglia_difesa(const griglia_difesa& g);	//costruttore di copia
		griglia_difesa& operator=(const griglia_difesa& g);	//assegnamento di copia
		void show_griglia() override;	//stampa la griglia a schermo
		void show_griglia(std::ofstream& file_scrittura);	//stampa la griglia su un file
		void place_ship(int x_iniziale, int y_iniziale,int x_finale,int y_finale ,char type_ship); //prendi coordinate iniziali e finali e inserisci la nave identificata da type_ship sulla griglia
		void ship_hit (int coordinata_x,int coordinata_y);	//cambia le lettere da maiuscolo a minuscolo nel caso la nave sia stata colpita
		void ship_repair (int coordinata_iniziale_x,int coordinata_iniziale_y,int coordinata_finale_x,int coordinata_finale_y); //cambia le lettere da minuscolo a maiuscolo se curata
		void move_sottomarino(int x_iniziale,int y_iniziale, int x_finale, int y_finale); //muovi il sottomarino
		void move_supporto(int x_iniziale,int y_iniziale, int x_finale, int y_finale, int x_prua_iniziale, int y_prua_iniziale, int x_poppa_iniziale, int y_poppa_iniziale); //muovi il supporto
		void remove_ship (int coordinata_iniziale_x,int coordinata_iniziale_y,int coordinata_finale_x,int coordinata_finale_y);	//cancella le lettere che indicano una nave dalla griglia
		char cell (int coordinata_x,int coordinata_y){return campo[coordinata_x][coordinata_y];}	//restituisce il valore contenuto da una cella
		


};

#endif //GRIGLIA_DIFESA_H
