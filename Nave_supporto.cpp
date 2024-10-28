//Francesco Carretta

#include "Nave.h"
#include "Nave_supporto.h"

Nave_supporto::Nave_supporto(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa) : Nave(coordinata_x_prua,  coordinata_y_prua, coordinata_x_poppa, coordinata_y_poppa, 3) 
{

}

Nave_supporto :: Nave_supporto(const Nave_supporto& n) : Nave(n.posizione_x_prua(), n.posizione_y_prua(), n.posizione_x_poppa(), n.posizione_y_poppa(), n.get_corazza())
{

}

Nave_supporto :: Nave_supporto(): Nave(3)
{
  
}

void Nave_supporto :: change_coordinate(int x_destinazione,int y_destinazione)
{
  int delta_x = x_destinazione - x_centro;
  int delta_y = y_destinazione - y_centro;

  x_prua += delta_x;
  y_prua += delta_y;

  x_centro += delta_x;
  y_centro += delta_y;

  x_poppa += delta_x;
  y_poppa += delta_y;
}
