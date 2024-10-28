//Farruku Juri

#include "griglia.h"


griglia::griglia() //crea una griglia ed inizializza a ' ' i suoi valori
{
	for (int i =0; i<12; i++)
	{
		for (int j=0; j<12; j++)
		{
			campo[i][j]=' ';
		}
	}
}

griglia& griglia::operator=(const griglia& g) //assegnazione di copia
{
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
			campo[i][j]=g.campo[i][j];
	}

	return *this;
}


bool griglia::fuori_dominio(int coordinata_x, int coordinata_y)	// verifica appartenenza a dominio della griglia
{
	return (coordinata_x<0 || coordinata_x > 11) || (coordinata_y < 0 || coordinata_y > 11);
}
