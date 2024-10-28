//Francesco Carretta

#ifndef NAVE_SUPPORTO_H
#define NAVE_SUPPORTO_H

#include "Nave.h"

//Classe Nave_supporto, derivata di Nave

class Nave_supporto : public Nave
{

public:
  
	//costruttori
    Nave_supporto();
	Nave_supporto(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa);
    Nave_supporto(const Nave_supporto& n); // costruttore di copia
	
    void restore() { corazza=3; }
    
    
    void change_coordinate(int x_destinazione,int y_destinazione); //cambia le coordinate della nave



  
};

#endif //NAVE_SUPPORTO_H