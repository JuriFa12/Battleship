//Francesco Carretta

#include "Nave.h"
#include "Sottomarino.h"

Sottomarino::Sottomarino(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa) : Nave( coordinata_x_prua,  coordinata_y_prua, coordinata_x_poppa, coordinata_y_poppa,1)
{

}

Sottomarino :: Sottomarino(const Sottomarino& n) : Nave(n.posizione_x_prua(), n.posizione_y_prua(), n.posizione_x_poppa(), n.posizione_y_poppa(), n.get_corazza())
{

}

Sottomarino :: Sottomarino(): Nave(1)
{
  
}

void Sottomarino :: change_coordinate(int x_destinazione,int y_destinazione)
{
  x_prua=x_destinazione;
  y_prua=y_destinazione;

  x_poppa=x_destinazione;
  y_poppa=y_destinazione;

  x_centro=x_destinazione;
  y_centro=y_destinazione;

}

