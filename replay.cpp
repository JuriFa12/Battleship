//Farruku Juri

#include <iostream>
#include <fstream>
#include <string>
#include "game.h"
#include "griglia_difesa.h"
#include "Corazzata.h"
#include "Sottomarino.h"
#include "griglia_attacco.h"
#include <time.h>
#include <thread>
#include <chrono>



int main(int argc,char* argv[])
{
	
	//controllo siano stati passati 2 parametri o 3 da riga di comando
	if (argc==3)
	{
		if(*argv[1] =='v')
		{	
			std::string file_lettura=argv[2];
			std:: ifstream fin(file_lettura);  //apro file in lettura

			//creazione delle barche per il player 1 o player 2 in base all'ordine di inizio
			char num_player=' ';
			fin >> num_player;
			game p1=game();
			game p2=game();

			if(num_player =='1')
			{
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'C',i,5);

					}
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'E',i,1);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'C',i,5);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'E',i,1);
					}	
			}
			else
			{
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'C',i,5);

					}
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'E',i,1);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'C',i,5);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'E',i,1);
					}
			} 
			//mostra le griglie dei giocatori

			p1.user_griglia();
			p2.user_griglia();

			int turno=1;

			while (!fin.eof())
			{
	
				std::string sorgente="";
				std::string bersaglio="";
				//lettura da file delle azioni e stampa a video con pausa di 1 secondo se parte il giocatore 1
				if (num_player=='1')
				{	
					fin >> sorgente;
					fin >> bersaglio;
					try
					{
						p1.make_azione(p2,sorgente,bersaglio);
						fin >> sorgente;
						fin >> bersaglio;
						p2.make_azione(p1,sorgente,bersaglio);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					}
					catch (const std::exception& e)
					{

					}

					std::cout <<"Turno n:" <<turno <<"\n";
					p1.user_griglia();
					p2.user_griglia();
					turno++;

				}
				else
				{
					//lettura da file delle azioni e stampa a video con pausa di 1 secondo se parte il giocatore 2
					fin >> sorgente;
					fin >> bersaglio;
					try
					{
						p2.make_azione(p1,sorgente,bersaglio);
						fin >> sorgente;
						fin >> bersaglio;
						p1.make_azione(p2,sorgente,bersaglio);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					}
					catch (const std::exception& e)
					{

					}

					std::cout <<"Turno n:" <<turno <<"\n";
					p2.user_griglia();
					p1.user_griglia();
					turno++;

				}

				
			

			
			}
			fin.close();
		}
	} 
	//fine caso in cui stampo a video





	else
	{
		//verifica che gli argomenti passati da riga di comando siano 3, in tal caso si scrive su file di testo il replay
		if (argc == 4 )
		{
			if(*argv[1] == 'f')
			{
				std::string file_lettura=argv[2];
				std::string file_scrittura=argv[3];

				std::ifstream fin(file_lettura); //apre file in lettura
				std::ofstream fout(file_scrittura); //apre file in scrittura
				

				char num_player=' ';
				fin >> num_player;
				game p1=game();
				game p2=game();

				if(num_player =='1')
			{	
				//posizionamento delle barche per i 2 player
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'C',i,5);

					}
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'E',i,1);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'C',i,5);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'E',i,1);
					}				
			}
			else
			{
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'C',i,5);

					}
					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p2.set_ship(prua,poppa,'E',i,1);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'C',i,5);
					}

					for (int i=0; i<3;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'S',i,3);
					}
					for (int i=0; i<2;i++)
					{
						std::string prua="";
						std::string poppa="";
						fin >> prua;
						fin >> poppa;
						p1.set_ship(prua,poppa,'E',i,1);
					}

			} //fine setting barche
			//scrittura delle griglie iniziali su file di output

			p1.return_griglia_difesa().show_griglia(fout);
			p1.return_griglia_attacco().show_griglia(fout);

			p2.return_griglia_difesa().show_griglia(fout);
			p2.return_griglia_attacco().show_griglia(fout);


			int turno=1;

			while (!fin.eof())
			{
				//stampa su file di testo di output le griglie ad ogni azione eseguita se parte il giocatore 1
				std::string sorgente="";
				std::string bersaglio="";
				if (num_player=='1')
				{	
					fin >> sorgente;
					fin >> bersaglio;
					try
					{
						p1.make_azione(p2,sorgente,bersaglio);
						fin >> sorgente;
						fin >> bersaglio;
						p2.make_azione(p1,sorgente,bersaglio);
					}
					catch (const std::exception& e)
					{

					}

					fout <<"Turno n:" <<turno <<"\n";
					p1.return_griglia_difesa().show_griglia(fout);
					p1.return_griglia_attacco().show_griglia(fout);

					p2.return_griglia_difesa().show_griglia(fout);
					p2.return_griglia_attacco().show_griglia(fout);
					
					turno++;

				}
				else
				{
					fin >> sorgente;
					fin >> bersaglio;
					try
					{
						//stampa su file di testo di output le griglie ad ogni azione eseguita se parte il giocatore 2
						p2.make_azione(p1,sorgente,bersaglio);
						fin >> sorgente;
						fin >> bersaglio;
						p1.make_azione(p2,sorgente,bersaglio);
					}
					catch (const std::exception& e)
					{

					}

					fout <<"Turno n:" <<turno <<"\n";
					p2.return_griglia_difesa().show_griglia(fout);
					p2.return_griglia_attacco().show_griglia(fout);

					p1.return_griglia_difesa().show_griglia(fout);
					p1.return_griglia_attacco().show_griglia(fout);
					
					turno++;
				}
			}
			fout.close();
			fin.close();

			}
		}
	}

	
}
