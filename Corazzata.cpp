//Berno Sara

#include "Corazzata.h"
#include "Nave.h"


//definizione costruttori

Corazzata :: Corazzata(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa) : Nave(coordinata_x_prua,  coordinata_y_prua, coordinata_x_poppa, coordinata_y_poppa, 5) 
{
	
}

Corazzata :: Corazzata(const Corazzata& n) : Nave(n.posizione_x_prua(), n.posizione_y_prua(), n.posizione_x_poppa(), n.posizione_y_poppa(), n.get_corazza())
{

}

Corazzata :: Corazzata(): Nave(5)
{
	
}