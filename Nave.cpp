//Berno Sara

#include"Nave.h"

//costruttore
Nave::Nave( int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa, int dim ) 
{
    x_prua = coordinata_x_prua;
    y_prua = coordinata_y_prua;
    x_poppa = coordinata_x_poppa;
    y_poppa = coordinata_y_poppa;
    x_centro = (coordinata_x_prua + coordinata_x_poppa)/2;
    y_centro = (coordinata_y_prua+coordinata_y_poppa)/2;
    dimensione = dim;
    corazza = dim;
}

//funzione che diminuisce la corazza quando la nave viene colpita
void Nave::danno()
{
    if (corazza > 0)
    {
        corazza = corazza - 1;
    }
} 

//se nave affondata, cambia le sue coordinate mettendola fuori dalla griglia
void Nave::affonda_nave()
{
    x_prua = -1;
    y_prua = -1;
    x_poppa = -1;
    y_poppa = -1;
    x_centro = -1;
    y_centro = -1;
}
