//Francesco Carretta

#ifndef SOTTOMARINO_H
#define SOTTOMARINO_H

#include "Nave.h"

//Classe Sottomarino, derivata di Nave

class Sottomarino : public Nave

{

  public:

	//costruttori
    Sottomarino();
	Sottomarino(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa);
    Sottomarino(const Sottomarino& n); //costruttore di copia
    
    void change_coordinate(int x_destinazione,int y_destinazione);  //cambia le coordinate della nave

};

#endif //SOTTOMARINO_H