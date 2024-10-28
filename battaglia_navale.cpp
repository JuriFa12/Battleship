//Berno Sara

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <limits>
#include <ios>
#include "griglia.h"
#include "griglia_difesa.h"
#include "griglia_attacco.h"
#include "game.h"
#include "Sottomarino.h"
#include "Nave_supporto.h"
#include "Nave.h"
#include "Corazzata.h"

struct Parametri_invalidi : std::runtime_error	//Eccezione
{
	Parametri_invalidi():runtime_error("Parametri_invalidi si e' verificata") {}
};

int main(int argc, char *argv[])
{
  	int scelta=0;
  	std::ofstream fout ("replay.txt"); //istruzione per scrittura su file

	//scelta tipologia partita (da riga di comando)
  	if (*argv[1] =='p' && *argv[2] =='c')
  	{
  		scelta = 2;
  	}
  	else 
  	{
  		if (*argv[1]=='c' && *argv[2]=='c')
  			scelta=1;
  		else
  		{
  			throw Parametri_invalidi();
  		}
  	}

	//crazione giocatori
	game p1 = game();
	game p2 = game();

	if(scelta==1)
		p1.set_tipo_giocatore('c');
	else
		p1.set_tipo_giocatore('p');
	p2.set_tipo_giocatore('c');	

	//inizializzazione variabili
	const int numero_navi = 3;
	bool nave_creata = false;
	std::string coordinata_prua, coordinata_poppa;

	std::string tipo_nave[] = {"Corazzata","Nave di supporto","Sottomarino di esplorazione"};
	char codice_nave[] = {'C','S','E'};
	int quantita_navi[] = {3,3,2};
	int dimensione_navi[] = {5,3,1};
	std::string coord_lettere[] = {"A","B","C","D","E","F","G","H","I","L","M","N"};

	srand(time(NULL)); //cambio seed per rand() in base alla data di esecuzione, per generare numeri casuali
	int inizio = rand() % 2 + 1;
	fout << inizio <<"\n";

	//POSIZIONAMENTO NAVI NELLE GRIGLIE
	for (int num_giocatori=0; num_giocatori<2; num_giocatori++)
	{
		for(int i=0; i<numero_navi; i++) // itero su "tipo_nave"
		{
			for(int j=0; j<quantita_navi[i]; j++) // itero su "quantita_navi"
			{
				nave_creata = false;
				while (!nave_creata)
				{
					try
					{	
						//richiesta inserimento coordinate al giocatore umano, se presente
						if(p1.get_tipo_giocatore()=='p' && num_giocatori==0)
						{
							std::cout<<"Quali sono le coordinate per "<<tipo_nave[i]<<" "<<j+1<<":\n";
							std::cin>>coordinata_prua>>coordinata_poppa;
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						else //se partita computer vs computer
						{
							//generazioni navi casuali
							int x_prua = rand() % 12, y_prua = rand() % 12, x_poppa = 0, y_poppa = 0;
							coordinata_prua = coord_lettere[x_prua] + std::to_string(y_prua+1); //estrazione casella che conterrà la prua
							int direzione = rand() % 2; //scelta casuale direzione nave: 0=orizzontale, 1=verticale
							if (direzione == 0) //nave orizzontale
							{
								x_poppa = x_prua;
								y_poppa = y_prua + dimensione_navi[i]-1;
							}
							else //nave verticale 
							{
								y_poppa = y_prua;
								x_poppa = x_prua + dimensione_navi[i]-1;
							}
							if(x_poppa>11) //se fuori range manda un'eccezione
							{
								try{
									throw Parametri_invalidi();
								}
								catch(Parametri_invalidi())
								{
									//non mostrare l'eccezione
								}
							}
							coordinata_poppa = coord_lettere[x_poppa] + std::to_string(y_poppa+1); //calcolo casella che conterrà la poppa
						}
						if (num_giocatori==0) //se prima esecuzione del ciclo for, le navi vengono assegnate al giocatore p1
						{
							p1.set_ship(coordinata_prua,coordinata_poppa,codice_nave[i],j,dimensione_navi[i]);
							fout << coordinata_prua <<" "<< coordinata_poppa << "\n"; //inserimento coordinate sul file
						}
						else //se seconda esecuzione del ciclo for, le navi vengono assegnate al giocatore p2
						{
							p2.set_ship(coordinata_prua,coordinata_poppa,codice_nave[i],j,dimensione_navi[i]);
							fout << coordinata_prua <<" "<< coordinata_poppa << "\n"; //inserimento coordinate sul file
						}
						nave_creata = true;
					}
					catch(const std::exception& e)
					{
						if(p1.get_tipo_giocatore()=='p' && num_giocatori == 0) //mostra eccezioni solo per il giocatore umano
						{
							std::cerr << e.what() << '\n';
						}
						else 
						{
							// Non mostrare alcuna eccezione per il giocatore computer
						}
					}
				}
			}
		}
		//visualizzazione griglie con navi
		if (num_giocatori==0)
		{
			std::cout<<"Griglia giocatore 1 \n";
			p1.user_griglia();
		}
		else
		{
			std::cout<<"Griglia giocatore 2 \n";
			p2.user_griglia();
		}		
	}

	//scelta casuale giocatore iniziale	
	bool turno_di_p1;
	if (inizio == 1)
		turno_di_p1 = true; //inizia giocatore 1
	else
		turno_di_p1 = false; //inzia giocatore 2

	int num_turni_max = 100, num_turni = 0, num_azioni=0, k=0;
	std::string sorgente, bersaglio, vincitore = " ";

	//IMPLEMENTAZIONE PARTITA
	while (num_turni < num_turni_max && vincitore == " ")
	{
		bool azione_ok = false; //variabile per verificare se l'azione era valida e quindi cambiare turno
		
		if(num_azioni%2 == 0 && p1.get_tipo_giocatore()=='c')
		 	std::cout<<"Turno n. "<<num_turni+1<<"\n";

		//AZIONE GIOCATORE 1 (umano o pc)
		if (turno_di_p1)
		{
			azione_ok = false;
			while(!azione_ok && vincitore == " ") //finché non viene inserita un'azione corretta e nessun giocatore ha vinto
			{
				try
				{
					if(p1.get_tipo_giocatore() == 'p') //se il giocatore 1 è umano, chiedere inserimento azione
					{
						//calcolo numero navi totali del giocatore
						std::vector<int> x_centri_corazzate, y_centri_corazzate, x_centri_supporti, y_centri_supporti, x_centri_sottomarini, y_centri_sottomarini;
						int num_tot_navi = p1.get_centri_corazzate(x_centri_corazzate, y_centri_corazzate) + p1.get_centri_supporti(x_centri_supporti, y_centri_supporti) + p1.get_centri_sottomarini(x_centri_sottomarini, y_centri_sottomarini);
						
						if (num_tot_navi == 0) //se nessuna nave presente, vittoria di p2
							vincitore = "p2";
						else
						{
							std::cout<<"Inserire azione\n";	
							std::cin>>sorgente>>bersaglio;
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
							p1.make_azione(p2, sorgente, bersaglio); //esecuzione azione giocatore umano
							azione_ok = true; //azione andata a buon fine
							fout << sorgente << " " <<bersaglio << "\n"; //inserimento azione nel file
							if (sorgente == "AA" && bersaglio == "AA")
							{
								//il comando AA AA non usa la mossa del turno
							}
							else
								turno_di_p1 = !turno_di_p1; //cambio turno					
							//std::cout<<"giocatore 1: \n";
							//p1.user_griglia();
						}
					}
					else //se p1 è computer
					{
						//estrazione casuale nave da vettore contenente i centri di tutte le navi
						std::vector<int> x_centri_corazzate, y_centri_corazzate, x_centri_supporti, y_centri_supporti, x_centri_sottomarini, y_centri_sottomarini;
						int num_corazzate = p1.get_centri_corazzate(x_centri_corazzate, y_centri_corazzate);
						int num_supporti = p1.get_centri_supporti(x_centri_supporti, y_centri_supporti);
						int num_sottomarini = p1.get_centri_sottomarini(x_centri_sottomarini, y_centri_sottomarini);
						int num_tot_navi = num_corazzate + num_supporti + num_sottomarini;
						int x_centri[num_tot_navi], y_centri[num_tot_navi];

						if (num_tot_navi == 0) //se nessuna nave presente, vittoria di p2
							vincitore = "p2";
						else 
						{
							for (int i=0; i<num_tot_navi; i++)
							{
								if (i<num_corazzate)
								{
									//inserimento dei centri delle corazzate
									x_centri[i] = x_centri_corazzate[i];
									y_centri[i] = y_centri_corazzate[i];
								}
								else if (i<(num_corazzate+num_supporti))
								{
									//inserimento dei centri dei supporti
									x_centri[i] = x_centri_supporti[i-num_corazzate];
									y_centri[i] = y_centri_supporti[i-num_corazzate];
								}
								else
								{
									//inserimento dei centri dei sottomarini
									x_centri[i] = x_centri_sottomarini[i-num_corazzate-num_supporti];
									y_centri[i] = y_centri_sottomarini[i-num_corazzate-num_supporti];
								}				
							}
							k++; //incremento k per generare un numero casuale sempre diverso
							srand(k);
							int indice_centro_sorgente = rand() % num_tot_navi;

							//generazione stringhe per mossa casuale
							sorgente = coord_lettere[x_centri[indice_centro_sorgente]] + std::to_string(y_centri[indice_centro_sorgente]+1);
							bersaglio = coord_lettere[rand()% 12] + std::to_string(rand()%12 + 1);		
							p1.make_azione(p2, sorgente, bersaglio); //esecuzione azione giocatore 1
							fout << sorgente << " " << bersaglio << "\n"; //inserimento azione nel file
							std::cout<<"Azione: "<<sorgente<<" "<<bersaglio<<"\n";
							azione_ok = true;
							turno_di_p1 = !turno_di_p1; //cambio turno
						}
					}
				}
				catch(const std::exception& e)
				{
					if(p1.get_tipo_giocatore()=='c')
					{
						// se partita computer vs computer non vengono mostrate eccezioni
					}
					else
						std::cerr << e.what() << '\n';
				}
			}
		}
		else //azione GIOCATORE 2 (computer)
		{ 
			azione_ok = false;
			while(!azione_ok && vincitore == " ") //finché non viene inserita un'azione corretta o non c'è un vincitore
			{
				try
				{
					//estrazione casuale nave da vettore contenente i centri di tutte le navi
					std::vector<int> x_centri_corazzate, y_centri_corazzate, x_centri_supporti, y_centri_supporti, x_centri_sottomarini, y_centri_sottomarini;
					int num_corazzate = p2.get_centri_corazzate(x_centri_corazzate, y_centri_corazzate);
					int num_supporti = p2.get_centri_supporti(x_centri_supporti, y_centri_supporti);
					int num_sottomarini = p2.get_centri_sottomarini(x_centri_sottomarini, y_centri_sottomarini);
					int num_tot_navi = num_corazzate + num_supporti + num_sottomarini;
					int x_centri[num_tot_navi], y_centri[num_tot_navi];

					if (num_tot_navi == 0) //se nessuna nave presente, vittoria di p1
							vincitore = "p1";
					else //sono ancora presenti navi del giocatore 2 (computer)
					{
						for (int i=0; i<num_tot_navi; i++)
						{
							if (i<num_corazzate)
							{
								//inserimento dei centri delle corazzate
								x_centri[i] = x_centri_corazzate[i];
								y_centri[i] = y_centri_corazzate[i];
							}
							else if (i<(num_corazzate+num_supporti))
							{
								//inserimento dei centri deli supporti
								x_centri[i] = x_centri_supporti[i-num_corazzate];
								y_centri[i] = y_centri_supporti[i-num_corazzate];
							}
							else
							{
								//inserimento dei centri dei sottomarini
								x_centri[i] = x_centri_sottomarini[i-num_corazzate-num_supporti];
								y_centri[i] = y_centri_sottomarini[i-num_corazzate-num_supporti];
							}				
						}

						k++; //incremento k per generare un numero casuale sempre diverso
						srand(k);
						int indice_centro_sorgente = rand() % num_tot_navi;

						sorgente = coord_lettere[x_centri[indice_centro_sorgente]] + std::to_string(y_centri[indice_centro_sorgente]+1);
						bersaglio = coord_lettere[rand()% 12] + std::to_string(rand()%12 + 1);
						p2.make_azione(p1, sorgente, bersaglio); //esecuzione azione del giocatore 2
						fout << sorgente <<" " <<bersaglio << "\n"; //inserimento azione nel file
						std::cout<<"Azione: "<<sorgente<<" "<<bersaglio<<"\n";
						azione_ok = true;
						turno_di_p1 = !turno_di_p1; //cambio turno
						// std::cout<<"Giocatore p2\n";
						// p2.user_griglia();
						// std::cout<<"\n";
					}
				}
				catch(const std::exception& e)
				{
					//non mostrare eccezioni per il giocatore p2, in quanto computer
				}
			}
		}
		if (sorgente == "AA" && bersaglio == "AA")
		{
			//il comando "AA AA" non viene contato come azione
		}
		else
			num_azioni++; //incremento numero turni
		
		if (p1.get_tipo_giocatore()=='c' && num_azioni % 2==0) //incremento di un turno ogni due azioni, se partita computer vs computer
			num_turni++;
	}

	if (vincitore == "p1" && p1.get_tipo_giocatore() == 'p') //output per giocatore umano se partita terminata per sua vittoria
		std::cout<<"Partita terminata, hai vinto! \n";
	else
	{
		if (vincitore != " ")
			std::cout<<"Partita terminata per vittoria\n";
	}
	if (num_turni == num_turni_max) //se numero turni massimo raggiunto
		std::cout<<"Partita terminata perche' numero turni massimo raggiunto \n";
	
	fout.close(); //chiusura file
	
	return 0;
}