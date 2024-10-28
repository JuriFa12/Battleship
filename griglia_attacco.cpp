//Farruku Juri

#include "griglia_attacco.h"
#include <iostream>
#include <fstream>


griglia_attacco::griglia_attacco() //costruttore
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j<12; j++)
		{
			campo[i][j]=' ';
		}
	}
}


griglia_attacco::griglia_attacco(const griglia_attacco& g) :griglia() //costruttore di copia
{
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
			campo[i][j] = g.campo[i][j];
	}

}

griglia_attacco&  griglia_attacco :: operator=(const griglia_attacco& g)  //assegnamento di copia
{
	griglia_attacco();
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
			campo[i][j] = g.campo[i][j];
	}

	return *this;


}


void griglia_attacco::show_griglia() //stampa la griglia a video
{
	char riga = 'A';

	for (int i= 0; i < 12; i++)
	{
		std::cout << riga <<" ";
		if (riga == 'I')
			riga=riga+3;
		else
			riga=riga+1;

		for (int j=0; j<12; j++)
		{
			std::cout << '|' << campo[i][j] << '|';
		}
		std::cout <<"\n";
	}
	for (int i = 0; i < 13; i++)
	{
		if (i==0)
			std::cout << " " << " " << " ";
		else 
		{
			if (i>= 1 && i<= 9)
				std::cout << i << " " << " ";
			else
				std::cout << i << " ";
		}

			

	}

	std::cout << "\n";
}




void griglia_attacco::show_griglia(std::ofstream& fout) //stampa la griglia su file di testo 
{

	char riga = 'A';

	for (int i= 0; i < 12; i++)
	{
		fout << riga <<" ";
		if (riga == 'I')
			riga=riga+3;
		else
			riga=riga+1;

		for (int j=0; j<12; j++)
		{
			fout << '|' << campo[i][j] << '|';
		}
		fout <<"\n";
	}


	for (int i = 0; i < 13; i++)
	{
		if (i==0)
			fout << " " << " " << " ";
		else 
		{
			if (i>= 1 && i<= 9)
				fout << i << " " << " ";
			else
				fout << i << " ";
		}
	}

	fout << "\n";
}


char griglia_attacco::danno(griglia_difesa enemy, int coordinata_x,int coordinata_y)
{

	if (fuori_dominio(coordinata_x, coordinata_y)) throw Posizione_fuori_dominio(); //lancia eccezione nel caso il controllo non vada a buon fine
	
	char verifica= enemy.cell(coordinata_x,coordinata_y);  //preleva il valore contenuto da una cella della griglia di difesa del nemico, assegna il colpo di conseguenza

	if (verifica!=' '){
		campo[coordinata_x][coordinata_y]='X';
		return 'X';
	} else {
		campo[coordinata_x][coordinata_y]='O';
		return 'O';
	}

}

void griglia_attacco::search_ship(griglia_difesa enemy, int coordinata_x,int coordinata_y)
{
	int x_min, x_max, y_min, y_max;
	x_min = coordinata_x-2;
	y_min = coordinata_y-2;
	x_max = coordinata_x+2;
	y_max = coordinata_y+2;

	if (x_min<0)
		x_min = 0;
	if (x_max>11)
		x_max = 11;
	if (y_min<0)
		y_min = 0;
	if (y_max>11)
		y_max = 11;


	for (int i=x_min; i<=x_max; i++)  //controllo quadrato 5x5 intorno alla coordinata x,y passata, restituisco Y se navi o parti di esse occupano tali caselle 
	{
		for (int j=y_min; j<=y_max; j++)
		{
			if (enemy.cell(i,j)!=' ')
				campo[i][j]='Y';
		}
	}
}


void griglia_attacco :: remove_sonar() //rimuobo il valore 'Y' dalla griglia
{

	for (int i=0; i < 12; i++)
	{
		for (int j=0; j<12; j++)
		{
			if (campo[i][j] == 'Y')
				campo[i][j] =' ';
		}
	}
}
