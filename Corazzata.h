//Berno Sara

#ifndef CORAZZATA_H
#define CORAZZATA_H

#include "Nave.h"

//Classe Corazzata, derivata di Nave

class Corazzata : public Nave
{
    public:
        //costruttore: costruzione nave di dimensione 5
        Corazzata(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa);
        Corazzata();

        //funzione per riparare la nave (resettare la corazza) se nelle vicinanze di un supporto
        void restore() { corazza=5; }

        //costruttore di copia
        Corazzata(const Corazzata& n);
};


#endif //CORAZZATA_H
