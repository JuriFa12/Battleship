//Berno Sara

#ifndef GRIGLIA_ATTACCO_H
#define GRIGLIA_ATTACCO_H

#include "griglia.h"
#include "griglia_difesa.h"
#include "Nave.h"
#include "Sottomarino.h"
#include "Nave_supporto.h"
#include "Corazzata.h"

//classe griglia_attacco, derivata di griglia

class griglia_attacco : public griglia
{
	private:
		char campo [12][12];

	public:
		//costruttori
		griglia_attacco(void);
		griglia_attacco(const griglia_attacco& g); //costruttore di copia
		griglia_attacco& operator=(const griglia_attacco& g); //assegnamento di copia
	
		void show_griglia() override; //stampa la griglia di attacco
		char danno(griglia_difesa enemy,int coordinata_x,int coordinata_y); //esegue un danno nelle coordinate indicate sulla griglia di difesa del nemico
		void search_ship(griglia_difesa enemy,int coordinata_x,int coordinata_y); //cerca una nave nella griglia di difesa nemica
		void remove_sonar (); //rimuove dalla grigla le Y (ricerca sonar sottomarino)
		void show_griglia(std::ofstream& file_scrittura);  //stampa griglia su un file
};

#endif //GRIGLIA_ATTACCO_H