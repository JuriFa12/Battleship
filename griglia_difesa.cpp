//Francesco Carretta

#include "griglia_difesa.h"
#include "griglia.h"
#include <iostream>
#include <fstream>

griglia_difesa::griglia_difesa() : griglia() //costruttore
{
}

griglia_difesa::griglia_difesa(const griglia_difesa& g) :griglia() //costruttore di copia
{
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
			campo[i][j] = g.campo[i][j];
	}

}


griglia_difesa&  griglia_difesa :: operator=(const griglia_difesa& g)  //assegnamento di copia
{
	griglia_difesa();
	for (int i=0; i<12; i++)
	{
		for (int j=0; j<12; j++)
			campo[i][j] = g.campo[i][j];
	}

	return *this;


}

void griglia_difesa::show_griglia()  //stampa la griglia
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


void griglia_difesa::show_griglia(std::ofstream& fout) //stampa la griglia su file di testo
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


void griglia_difesa :: place_ship (int x_iniziale, int y_iniziale,int x_finale,int y_finale ,char type_ship)	//posizionamento navi
{
	if (x_iniziale==-1 || y_iniziale==-1 || x_finale==-1 || y_finale==-1) throw Posizione_illegale();	//lancia eccezioni in caso di condizioni non verificate
	if (fuori_dominio(x_iniziale, y_iniziale)) throw Posizione_fuori_dominio();
	if (fuori_dominio(x_finale, y_finale)) throw Posizione_fuori_dominio();	
	
	if ((x_iniziale == x_finale) && (y_finale > y_iniziale))	//se la nave è in orizzontale e la poppa passata è > della prua
	{
		if ((y_finale-y_iniziale == 4 && type_ship== 'C') || (y_finale-y_iniziale == 2 && type_ship== 'S') || (y_finale-y_iniziale == 0 && type_ship== 'E'))	//controlla che la lunghezza della nave corrisponda al tipo di nave passato, altrimenti lancia eccezione
		{
			for (int i=y_iniziale; i <= y_finale; i++)	//scrivi la lettera corrispondente alla nave nelle caselle corrispondenti se queste sono libere partendo dalla prua
			{
				if (campo[x_iniziale][i]==' ')
					campo[x_iniziale][i]=type_ship;
				else 
				{
					// rimuovo le celle su cui ho scritto e poi lancio l'eccezione
					for (int j=y_iniziale; j < i; j++)
					{
						campo[x_iniziale][j]=' ';
					}
					throw Posizione_occupata();
				}

			}
		}
		else 
			throw Dimensione_errata(); 
	}
	else
	{
		if ((x_iniziale == x_finale) && (y_finale < y_iniziale))	//se la nave è in orizzontale e la poppa passata è < della prua
		{
			if ((y_iniziale-y_finale == 4 && type_ship== 'C') || (y_iniziale-y_finale == 2 && type_ship== 'S') || (y_iniziale-y_finale == 0 && type_ship== 'E'))	//controlla che la lunghezza della nave corrisponda al tipo di nave passato, altrimenti lancia eccezione
			{

				for (int i=y_finale; i <= y_iniziale; i++)	//scrivi la lettera corrispondente alla nave nelle caselle corrispondenti se queste sono libere partendo dalla poppa
				{
					if (campo[x_iniziale][i] == ' ')
						campo[x_iniziale][i]=type_ship;
					else 
					{
						// rimuovo le celle su cui ho scritto e poi lancio l'eccezione
						for (int j=y_finale; j < i; j++)
						{
							campo[x_iniziale][j]=' ';
						}
						throw Posizione_occupata();
					}
				}

			}
			else 
				throw Dimensione_errata(); 

		}
		else
		{
			if ((y_iniziale == y_finale) && (x_finale > x_iniziale))	//se la nave è in verticale e la poppa passata è > della prua
			{
				if ((x_finale-x_iniziale == 4 && type_ship== 'C') || (x_finale-x_iniziale == 2 && type_ship== 'S') || (x_finale-x_iniziale == 0 && type_ship== 'E'))	//controlla che la lunghezza della nave corrisponda al tipo di nave passato, altrimenti lancia eccezione
				{	
					for (int i= x_iniziale; i <= x_finale; i++)	//scrivi la lettera corrispondente alla nave nelle caselle corrispondenti se queste sono libere partendo dalla prua
					{
						if (campo[i][y_finale]==' ')
							campo[i][y_finale]=type_ship;
						else
						{
							// rimuovo le celle su cui ho scritto e poi lancio l'eccezione
							for (int j=x_iniziale; j < i; j++)
							{
								campo[j][y_finale]=' ';
							}
							throw Posizione_occupata();
						}
					}
				}
				else throw Dimensione_errata(); //ok
			}
			else
			{
				if ((y_iniziale == y_finale) && (x_finale < x_iniziale))	//se la nave è in verticale e la poppa passata è < della prua
				{
						if ((x_iniziale-x_finale == 4 && type_ship== 'C') || (x_iniziale-x_finale == 2 && type_ship== 'S') || (x_iniziale-x_finale == 0 && type_ship== 'E'))	//controlla che la lunghezza della nave corrisponda al tipo di nave passato, altrimenti lancia eccezione
						{
							for (int i= x_finale; i <= x_iniziale; i++)
							{
								if(campo[i][y_finale]==' ')	//scrivi la lettera corrispondente alla nave nelle caselle corrispondenti se queste sono libere partendo dalla poppa
									campo[i][y_finale]=type_ship;
								else 
								{
									// rimuovo le celle su cui ho scritto e poi lancio l'eccezione
									for (int j=x_finale; j < i; j++)
									{
										campo[j][y_finale]=' ';
									}
									throw Posizione_occupata();
								}

							}
						}
						else 
							throw Dimensione_errata();

				}
				else
				{
					if ((y_iniziale==y_finale && x_iniziale==x_finale))	//caso particolare nel caso si tratti di sottomarino (prua=poppa)
					{
						if (type_ship != 'E') throw Dimensione_errata();

						if(campo[x_finale][y_finale]==' ') 
							campo[x_finale][y_finale]=type_ship;
						else
							throw Posizione_occupata();	
					}
					else
						throw Posizione_illegale();

				}
			}
		}
	}
}


void griglia_difesa :: ship_hit (int coordinata_x, int coordinata_y) //rende minuscolo una lettera di una nave colpita
{

	if (campo[coordinata_x][coordinata_y] == 'C' || campo[coordinata_x][coordinata_y] == 'S' || campo[coordinata_x][coordinata_y] == 'E')
		campo[coordinata_x][coordinata_y]+=32;		

}

void griglia_difesa :: ship_repair (int x_iniziale, int y_iniziale, int x_finale,int y_finale)
{

	int x_start = 0;	//utilizza delle variabili per memorizzare da dove a dove riparare
	int x_stop = 0;
	int y_start = 0;
	int y_stop = 0;

	if (x_iniziale<=x_finale) //se la x prua è minore della x poppa
	{
		x_start = x_iniziale;
		x_stop = x_finale;
	} 
	else	//x prua maggiore x poppa
	{
		x_start = x_finale;	
		x_stop = x_iniziale;
	}

	if (y_iniziale<=y_finale)	//y prua è minore della y poppa
	{
		y_start = y_iniziale;
		y_stop = y_finale;
	} 
	else	//y prua è minore y poppa
	{
		y_start = y_finale;
		y_stop = y_iniziale;
	}

	for (int i=x_start; i<=x_stop; i++)
	{
		for (int j=y_start; j<=y_stop; j++)	//aggiorna i valori della nave da minuscolo a maiuscolo se sono i minuscolo partendo da prua
		{
			if (campo[i][j]>=97 && campo[i][j]<= 115)
			{
				campo[i][j]-=32;
			}
		}
	}
}

void griglia_difesa :: move_sottomarino(int x_iniziale,int y_iniziale, int x_finale, int y_finale)
{

	if (fuori_dominio(x_iniziale, y_iniziale)) throw Posizione_fuori_dominio();		//lancia eccezioni nel caso di parametri non validi
	if (fuori_dominio(x_finale, y_finale)) throw Posizione_fuori_dominio();


	if(campo[x_finale][y_finale]==' ')	//se la posizione finale è libera sposta il sottomarino e cancellalo dalla posizione iniziale, altrimenti lancia eccezione
	{
		campo[x_finale][y_finale]='E';
		campo[x_iniziale][y_iniziale]=' ';
	}
	else
		throw Posizione_occupata();
	
}

void griglia_difesa :: move_supporto(int x_iniziale,int y_iniziale, int x_finale, int y_finale, int x_prua_iniziale, int y_prua_iniziale, int x_poppa_iniziale, int y_poppa_iniziale)
{
	int x_prua_finale;	
	int y_prua_finale;
	int x_poppa_finale;
	int y_poppa_finale;
	
	if (x_prua_iniziale == x_poppa_iniziale)	//se nave in orizzontale
	{
		x_prua_finale = x_finale;	//salva i valori della prua e della poppa finale a partire da il centro finale
		x_poppa_finale = x_finale;
		y_prua_finale = y_finale-1;
		y_poppa_finale = y_finale+1;
		
		
		if (fuori_dominio(x_prua_finale, y_prua_finale)) throw Posizione_fuori_dominio();	//lancia eccezioni nel caso di parametri non validi
		if (fuori_dominio(x_poppa_finale, y_poppa_finale)) throw Posizione_fuori_dominio();
		
		char copia [3] ={};	//utilizza array di char per salvare le lettere presenti nelle posizioni iniziali (maiuscolo o minuscolo) e li stampa nelle posizioni finale se queste sono libere, altrimenti lancia eccezione	
		int j=0;
		
			for (int i=y_prua_iniziale; i <= y_poppa_iniziale; i++)
		{
			copia[j]=campo[x_iniziale][i];
			campo[x_iniziale][i]=' ';	//svuota le caselle iniziali
			j++;
		}
		
		j=0;
		
		for (int i=y_prua_finale; i <= y_poppa_finale; i++)
		{
			if(campo[x_finale][i]!=' ') //se almeno una delle caselle finali non è vuota riscrivi la nave sulle caselle iniziali e lancia eccezione
			{	
				for (int i=y_prua_iniziale; i <= y_poppa_iniziale; i++)
				{
					campo[x_iniziale][i] = copia[j];
					j++;
				}
				throw Posizione_occupata();
			}
		}
		
		j=0;

		for (int i=y_prua_finale; i <= y_poppa_finale; i++)	//scrivi su caselle finali
		{
			campo[x_finale][i]=copia[j];
			j++;
		}
		
	}
	else if (y_prua_iniziale == y_poppa_iniziale)	//se nave in orizzontale
	{
		y_prua_finale = y_finale;	//salva i valori della prua e della poppa finale a partire da il centro finale
		y_poppa_finale = y_finale;
		x_prua_finale = x_finale-1;
		x_poppa_finale = x_finale+1;
		
		if (fuori_dominio(x_prua_finale, y_prua_finale)) throw Posizione_fuori_dominio();	//lancia eccezioni nel caso di parametri non validi
		if (fuori_dominio(x_poppa_finale, y_poppa_finale)) throw Posizione_fuori_dominio();

		char copia [3]={};	//utilizza array di char per salvare le lettere presenti nelle posizioni iniziali (maiuscolo o minuscolo) e li stampa nelle posizioni finale se queste sono libere, altrimenti lancia eccezione
		int j=0;
		
	for (int i=x_prua_iniziale; i<=x_poppa_iniziale; i++)
		{
			copia[j]=campo[i][y_iniziale];
			campo[i][y_iniziale]=' ';	//svuota le caselle iniziali
			j++;
		}
		
		j=0;
		
		for (int i=x_prua_finale; i<=x_poppa_finale; i++)
		{
			if (campo[i][y_finale]!=' ')	//se almeno una delle caselle finali non è vuota riscrivi la nave sulle caselle iniziali e lancia eccezione
			{
				for (int i=x_prua_iniziale; i<=x_poppa_iniziale; i++)
				{
					campo[i][y_iniziale] = copia[j];
					j++;
				}
				throw Posizione_occupata();
			}
		}
		
		j=0;

		for (int i=x_prua_finale; i<=x_poppa_finale; i++)	//scrivi su caselle finali
		{
			campo[i][y_finale]=copia[j];
			j++;
		}
	}
}

void griglia_difesa::remove_ship(int x_iniziale,int y_iniziale,int x_finale,int y_finale)
{

	if ((x_iniziale == x_finale) && (y_finale > y_iniziale))	//nave orizziontale, poppa > prua
	{
		for (int i=y_iniziale; i <= y_finale; i++)
		{
				campo[x_iniziale][i]=' ';	//svuota le caselle
		}
	}
	else
	{
		if ((x_iniziale == x_finale) && (y_finale < y_iniziale))	//nave orizziontale, poppa < prua
		{
			for (int i=y_finale; i <= y_iniziale; i++)	//svuota le caselle
			{
					campo[x_iniziale][i]=' ';
			}

		}
		else
		{
			if ((y_iniziale == y_finale) && (x_finale > x_iniziale))	//nave verticale, poppa > prua
			{

				for (int i= x_iniziale; i <= x_finale; i++)
				{
						campo[i][y_finale]= ' ';	//svuota le caselle

				}
			}
			else
			{
				if ((y_iniziale == y_finale) && (x_finale < x_iniziale))	//nave verticale, poppa < prua
				{
					for (int i= x_finale; i <= x_iniziale; i++)
				{
						campo[i][y_finale]=' ';
				}

				}
				else
				{
					if ((x_iniziale==x_finale) && (y_finale==y_iniziale))
						campo[x_iniziale][y_finale]=' ';
				}

			}
		}
	}
}
