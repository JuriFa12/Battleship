//Farruku Juri

#include "game.h"
#include "griglia_difesa.h"
#include "Corazzata.h"
#include "Sottomarino.h"
#include "griglia_attacco.h"
#include <string>


game :: game ()	//inizializza gli array (vuoti)
{
	Corazzata corazzate[3] ={};
	Nave_supporto supporti[3]={};
	Sottomarino sottomarini[2]={};
}


void game:: set_ship (std::string prua, std::string poppa,char type_ship,int number_ship,int dimensione)	
{
	
	char coordinata_x_prua=prua.at(0);	//divido la stringa "prua" in due sottostringhe
	std::string coordinata_y_prua="";
	if (prua.length()==2)
		coordinata_y_prua=prua.substr(1,1);
	else
		coordinata_y_prua=prua.substr(1,2);


	int y_prua=0;
	try // catturo eventuale eccezione se inserisco qualcosa che non è un numero
	{
        y_prua=std::stoi(coordinata_y_prua)-1;
    }
    catch (std::invalid_argument const &e) 
	{
		y_prua=-1;
	}
	int x_prua=0;
	
	if ((coordinata_x_prua == 'J') || (coordinata_x_prua == 'K')) throw Parametri_invalidi(); 
	if ((coordinata_x_prua == 'M') || (coordinata_x_prua == 'N')||(coordinata_x_prua=='L'))	//eseguo la conversione lettera-numero utilizzanto tabella ascii (mancano j,k nella griglia, prevedo caso eccezionale)
		x_prua=(int)coordinata_x_prua-67;
	else
		x_prua=(int)coordinata_x_prua-65;


	char coordinata_x_poppa=poppa.at(0);	//divido la stringa "poppa" in due sottostringhe
	std::string coordinata_y_poppa="";
	if (poppa.length()==2)
		coordinata_y_poppa=poppa.substr(1,1);
	else
		coordinata_y_poppa=poppa.substr(1,2);

	int y_poppa=0;
	try // catturo eventuale eccezione se inserisco qualcosa che non è un numero
	{
        y_poppa=std::stoi(coordinata_y_poppa)-1;
    }
    catch (std::invalid_argument const &e) 
	{
		y_poppa=-1;
	}
	int x_poppa=0;
	
	if ((coordinata_x_poppa == 'J') || (coordinata_x_poppa == 'K')) throw Parametri_invalidi(); 
	if ((coordinata_x_poppa == 'M') || (coordinata_x_poppa == 'N')||(coordinata_x_poppa=='L'))	//eseguo la conversione lettera-numero utilizzanto tabella ascii (mancano j,k nella griglia, prevedo caso eccezionale)
	 	x_poppa=(int)coordinata_x_poppa-67;
	else
		x_poppa=(int)coordinata_x_poppa-65;

	griglia_difensiva.place_ship(x_prua,y_prua,x_poppa,y_poppa,type_ship);

	if(dimensione==5)
		corazzate[number_ship]=Corazzata(x_prua,y_prua,x_poppa,y_poppa);
	else
	{
		if(dimensione==3)
			supporti[number_ship]=Nave_supporto(x_prua,y_prua,x_poppa,y_poppa);
		else
			sottomarini[number_ship]=Sottomarino(x_prua,y_prua,x_poppa,y_poppa);
	}
}

void game :: user_griglia()	//stampa le griglie
{
	griglia_difensiva.show_griglia();
	griglia_offensiva.show_griglia();
}

int game :: find_ship(int x_pos, int y_pos, char tipo_nave)	//funzione per individuare l'indice di una nave appartenente ad uno degli array
{
	bool right=false;

	if (tipo_nave=='C' || tipo_nave=='c')	//se è una corazzata (con o senza danno) 
	{
		for (int i=0; i<3; i++)	//scorri l'array di corazzate
		{
			int prua_x = corazzate[i].posizione_x_prua();	//memorizza posizione prua e poppa della corazzata i
			int prua_y = corazzate[i].posizione_y_prua();
			int poppa_x = corazzate[i].posizione_x_poppa();
			int poppa_y = corazzate[i].posizione_y_poppa();
			if (prua_x==poppa_x)	//se nave orizzontale
			{
				if (prua_y <= poppa_y)
				{
					for (int y=prua_y; y <=poppa_y; y++)	//scorri le caselle della nave (da prua a poppa)
					{
						if (x_pos==prua_x && y_pos==y) 
							return i;	//ritorna l'indice se il controllo va a buon fine
					}
				} 
				else 
				{
					for (int y=poppa_y; y<=prua_y; y++)	//scorri le caselle della nave (da poppa a prua)
					{
						if (x_pos==prua_x && y_pos==y)
							return i;	//ritorna l'indice se il controllo va a buon fine
					}
				}
			} 
			else if (prua_y==poppa_y) //se nave verticale
			{
				if (prua_x<=poppa_x) 
				{
					for (int x=prua_x; x<=poppa_x; x++)	//scorri le caselle della nave (da prua a poppa)
					{
						if (y_pos==prua_y && x_pos==x)
							return i;	//ritorna l'indice se il controllo va a buon fine
					}
				} 
				else 
				{
					for (int x=poppa_x; x<=prua_x; x++)	//scorri le caselle della nave (da poppa a prua)
					{
						if (y_pos==prua_y && x_pos==x)
							return i;	//ritorna l'indice se il controllo va a buon fine
					}
				}
			}
		}
	} 
	else if (tipo_nave=='S' ||tipo_nave=='s') // se è un supporto (con o senza danno) (ripeti quanto appena fatto per corazzata)
	{
		for (int i=0; i<3; i++) 
		{
			int prua_x = supporti[i].posizione_x_prua();
			int prua_y = supporti[i].posizione_y_prua();
			int poppa_x = supporti[i].posizione_x_poppa();
			int poppa_y = supporti[i].posizione_y_poppa();
			if (prua_x==poppa_x)
			{
				if (prua_y<=poppa_y) 
				{
					for (int y=prua_y; y<=poppa_y; y++)
					{
						if (x_pos==prua_x && y_pos==y) 
							return i;
					}
				} 
				else 
				{
					for (int y=poppa_y; y<=prua_y; y++)
					{
						if (x_pos==prua_x && y_pos==y)
							return i;
					}
				}
			} 
			else if (prua_y==poppa_y) 
			{
				if (prua_x<=poppa_x) 
				{
					for (int x=prua_x; x<=poppa_x; x++)
					{
						if (y_pos==prua_y && x_pos==x)
							return i;
					}
				} 
				else 
				{
					for (int x=poppa_x; x<=prua_x; x++)
					{
						if (y_pos==prua_y && x_pos==x)
							return i;
					}
				}
			}
		}
	} 
	else if (tipo_nave=='E' || tipo_nave =='e')	// se è un sottomarino (con o senza danno)
	{
		for (int i=0; i<2; i++) //memorizza posizione prua e poppa sottomarino i
		{
			int prua_x = sottomarini[i].posizione_x_prua();	
			int prua_y = sottomarini[i].posizione_y_prua();
			int poppa_x = sottomarini[i].posizione_x_poppa();
			int poppa_y = sottomarini[i].posizione_y_poppa();
			if ((prua_x==x_pos) && (prua_y==y_pos))	//se coincide con la posizione passata
				return i;	//ritorna l'indice
			
		}
	}

	return 0;	//uscita dalla funzione

}


bool game :: check_azione (int x_centro,int y_centro, char& type_ship, int& index)	//controllo validità azione
{
	bool right=false;	//variabile flag

	for (int i=0; i<3; i++)	//controlla che il centro passato coincida effettivamente con il centro di una delle navi contenute nei rispettivi array
	{
		if ((x_centro == corazzate[i].posizione_x_centro()) && (y_centro == corazzate[i].posizione_y_centro()))
		{	
			right=true;
			index = i;
			type_ship = 'C';
		}
		if ((x_centro == supporti[i].posizione_x_centro()) && (y_centro == supporti[i].posizione_y_centro()))
		{	
			right=true;
			index = i;
			type_ship = 'S';
		}

	}

	if(!right)
	{
		for (int i=0; i<2; i++)
		{
			if ((x_centro == sottomarini[i].posizione_x_centro()) && (y_centro == sottomarini[i].posizione_y_centro()))
			{	
				right=true;
				index = i;
				type_ship = 'E';
			}
		}
	}


	return right;	//right = false se il nella coordinata passata non c'è alcun centro di nave; true altrimenti

}

void game :: make_azione (game& enemy,std::string sorgente,std::string bersaglio)
{
	if ((sorgente.compare("XX")==0) && (bersaglio.compare("XX")==0))	//stampa griglia con comando speciale
	{
		user_griglia();
		return;
	}

	if ((sorgente.compare("AA")==0) && (bersaglio.compare("AA")==0))	//rimuovo sonar con comando speciale
	{
		griglia_offensiva.remove_sonar();
		return;
	}

	char coordinata_x_sorgente=sorgente.at(0);	//divido la stringa "sorgente" in due sottostringhe
	std::string coordinata_y_sorgente="";
	if (sorgente.length()==2)
		coordinata_y_sorgente=sorgente.substr(1,1);
	else
		coordinata_y_sorgente=sorgente.substr(1,2);

	int y_sorgente=0;
	try // catturo eventuale eccezione se inserisco qualcosa che non è un numero
	{
        y_sorgente=std::stoi(coordinata_y_sorgente)-1;
    }
    catch (std::invalid_argument const &e) 
	{
		throw Parametri_invalidi();
	}

	int x_sorgente=0;
	if ((coordinata_x_sorgente == 'J') || (coordinata_x_sorgente == 'K')) throw Parametri_invalidi(); //J e K non appartengono alla griglia
	if ((coordinata_x_sorgente == 'M') || (coordinata_x_sorgente == 'N')||(coordinata_x_sorgente=='L'))	//eseguo la conversione lettera-numero utilizzanto tabella ascii (mancano j,k nella griglia, prevedo caso eccezionale)
		x_sorgente=(int)coordinata_x_sorgente-67;
	else
		x_sorgente=(int)coordinata_x_sorgente-65;

	char coordinata_x_bersaglio=bersaglio.at(0);	//divido la stringa "bersaglio" in due sottostringhe
	std::string coordinata_y_bersaglio="";
	if (bersaglio.length()==2)
		coordinata_y_bersaglio=bersaglio.substr(1,1);
	else
		coordinata_y_bersaglio=bersaglio.substr(1,2);

	int y_bersaglio=0;
	try // catturo eventuale eccezione se inserisco qualcosa che non è un numero
	{
        y_bersaglio=std::stoi(coordinata_y_bersaglio)-1;
    }
    catch (std::invalid_argument const &e) 
	{
		throw Parametri_invalidi();
	}


	int x_bersaglio=0;
	if ((coordinata_x_bersaglio == 'J') || (coordinata_x_bersaglio == 'K')) throw Parametri_invalidi(); 
	if ((coordinata_x_bersaglio == 'M') || (coordinata_x_bersaglio == 'N') ||(coordinata_x_bersaglio=='L'))	//eseguo la conversione lettera-numero utilizzanto tabella ascii (mancano j,k nella griglia, prevedo caso eccezionale)
	 	x_bersaglio=(int)coordinata_x_bersaglio-67;
	else
		x_bersaglio=(int)coordinata_x_bersaglio-65;



	char tipo_nave = ' ';
	int index = -1;
	bool check= check_azione(x_sorgente,y_sorgente,tipo_nave,index);	//controlla se l'azione ha senso (c'è effettivamente un centro di nave nella coordinate passate?), modifica check, index e tipo nave

	if (check == true)	//se il controllo è andato a buon fine
	{
		if (tipo_nave=='C' && index!=-1)	//esegui azione specifica per la corazzata
		{
			if(enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio) >=97 && enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio) <= 122) //se nave nemica già colpita, esci
				return;

			char colpo= griglia_offensiva.danno(enemy.return_griglia_difesa(),x_bersaglio,y_bersaglio);
			if (colpo =='X')
			{	
				enemy.return_griglia_difesa().ship_hit(x_bersaglio,y_bersaglio);	//se il colpo è andato a segno esegui ship_hit sulla nave nemica
				int enemy_index=enemy.find_ship(x_bersaglio,y_bersaglio,enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio));	//identifica l'indice della nave colpita

				if (enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio) == 'c')	//se si tratta di una corazzata colpita
				{
					enemy.get_corazzata(enemy_index).danno();	//esegui danno (togli corazza)
					if (enemy.get_corazzata(enemy_index).get_corazza()==0)	//se la corazza è 0
					{
						enemy.return_griglia_difesa().remove_ship(enemy.get_corazzata(enemy_index).posizione_x_prua(),enemy.get_corazzata(enemy_index).posizione_y_prua(),enemy.get_corazzata(enemy_index).posizione_x_poppa(),enemy.get_corazzata(enemy_index).posizione_y_poppa());	//rimuove la corazzata affondata dalla griglia
						// affondo la nave
						enemy.get_corazzata(enemy_index).affonda_nave();
					}
				}
				else
				{
					if (enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio) == 's')	//se si tratta di un supporto colpito
					{		
						enemy.get_supporto(enemy_index).danno();	//esegui danno (togli corazza)
						if (enemy.get_supporto(enemy_index).get_corazza()==0)
						{
							enemy.return_griglia_difesa().remove_ship(enemy.get_supporto(enemy_index).posizione_x_prua(),enemy.get_supporto(enemy_index).posizione_y_prua(),enemy.get_supporto(enemy_index).posizione_x_poppa(),enemy.get_supporto(enemy_index).posizione_y_poppa());	//rimuove il supporto affondato dalla griglia
							// affondo la nave
							enemy.get_supporto(enemy_index).affonda_nave();
						}
					}
					else
					{
						if (enemy.return_griglia_difesa().cell(x_bersaglio,y_bersaglio) == 'e')	//se si tratta di un sottomarino colpito
						{
							enemy.get_sottomarino(enemy_index).danno();	//esegui danno (togli corazza)
							if (enemy.get_sottomarino(enemy_index).get_corazza()==0) 
							{
								enemy.return_griglia_difesa().remove_ship(enemy.get_sottomarino(enemy_index).posizione_x_prua(),enemy.get_sottomarino(enemy_index).posizione_y_prua(),enemy.get_sottomarino(enemy_index).posizione_x_poppa(),enemy.get_sottomarino(enemy_index).posizione_y_poppa());	//rimuove il supporto affondato dalla griglia
								// affondo la nave
								enemy.get_sottomarino(enemy_index).affonda_nave();
							}
						}
					}
				}
			}
			else return;
		} 
		else if (tipo_nave=='S' && index!=-1) //esegui azione specifica per il supporto
		{
			griglia_difensiva.move_supporto(supporti[index].posizione_x_centro(),supporti[index].posizione_y_centro(),x_bersaglio,y_bersaglio,supporti[index].posizione_x_prua(),supporti[index].posizione_y_prua(),supporti[index].posizione_x_poppa(),supporti[index].posizione_y_poppa());
			supporti[index].change_coordinate(x_bersaglio,y_bersaglio);


			int max_x_value, min_x_value, max_y_value, min_y_value;
			max_x_value = x_bersaglio+1;
			min_x_value = x_bersaglio-1;
			max_y_value = y_bersaglio+1;
			min_y_value = y_bersaglio-1;
			
			if (min_x_value < 0) 
				min_x_value = 0;
			if (min_y_value < 0) 
				min_y_value = 0;
			if (max_x_value > 11) 
				max_x_value = 11;
			if (max_y_value > 11) 
				max_y_value = 11;

			for (int i=min_x_value; i<=max_x_value; i++)
			{
				for (int j=min_y_value; j<=max_y_value; j++)
				{
					if (griglia_difensiva.cell(i,j) != ' ')
					{
						int my_ship=find_ship(i,j,griglia_difensiva.cell(i,j));

						if((my_ship == index) && (griglia_difensiva.cell(i,j) =='S' || griglia_difensiva.cell(i,j) =='s'))
						{

						}
						else
						{
							if (griglia_difensiva.cell(i,j) == 'c' || griglia_difensiva.cell(i,j) =='C')
							{
								corazzate[my_ship].restore();
								griglia_difensiva.ship_repair(corazzate[my_ship].posizione_x_prua(),corazzate[my_ship].posizione_y_prua(),corazzate[my_ship].posizione_x_poppa(),corazzate[my_ship].posizione_y_poppa());
							}
							else
							{
								if(griglia_difensiva.cell(i,j) == 's' || griglia_difensiva.cell(i,j) =='S')
								{
									supporti[my_ship].restore();
									griglia_difensiva.ship_repair(supporti[my_ship].posizione_x_prua(),supporti[my_ship].posizione_y_prua(),supporti[my_ship].posizione_x_poppa(),supporti[my_ship].posizione_y_poppa());


								}
							}
						}
					}

				}
			} 
		}
		else if (tipo_nave=='E' && index!=-1)	//esegui azione specifica per  il sottomarino
		{
			griglia_difensiva.move_sottomarino(sottomarini[index].posizione_x_centro(),sottomarini[index].posizione_y_centro(),x_bersaglio,y_bersaglio);	//muovi il sottomarino sulla griglia
			sottomarini[index].change_coordinate(x_bersaglio,y_bersaglio);	//aggiorna posizione sottomarino nell'array di sottomarini
			griglia_offensiva.search_ship(enemy.return_griglia_difesa(),x_bersaglio,y_bersaglio);	//esegui ricerca navi
		}

	}
	else 
		throw Nessuna_nave_presente();	//lancia eccezione

}


int game :: get_centri_corazzate(std::vector<int>& x_centri, std::vector<int>& y_centri)
{
	int num_corazzate = 0;
	for (int i=0; i<3; i++)
	{
		if(corazzate[i].get_corazza() > 0)	//se la corazzata i non è affondata, aggiungi in coda al vettore di centri il suo centro
		{
			num_corazzate++;
			x_centri.push_back(corazzate[i].posizione_x_centro());
			y_centri.push_back(corazzate[i].posizione_y_centro());
		}
	}
	return num_corazzate;	//restituisce il numero di corazzate con corazza >0
}

	int game :: get_centri_sottomarini(std::vector<int>& x_centri, std::vector<int>& y_centri)	
{
	int num_sottomarini = 0;
	for (int i=0; i<2; i++)
	{
		if(sottomarini[i].get_corazza() > 0)	//se il sottomarino i non è affondato, aggiungi in coda al vettore di centri il suo centro
		{
			num_sottomarini++;
			x_centri.push_back(sottomarini[i].posizione_x_centro());
			y_centri.push_back(sottomarini[i].posizione_y_centro());
		}
	}
	return num_sottomarini;	//restituisce il numero di sottomarini con corazza >0
}

int game :: get_centri_supporti(std::vector<int>& x_centri, std::vector<int>& y_centri)
{
	int num_supporti = 0;
	for (int i=0; i<3; i++)
	{
		if(supporti[i].get_corazza() > 0)	//se il supporto i non è affondato, aggiungi in coda al vettore di centri il suo centro
		{
			num_supporti++;
			x_centri.push_back(supporti[i].posizione_x_centro());
			y_centri.push_back(supporti[i].posizione_y_centro());
		}
	}
	return num_supporti; //restituisce il numero di supporti con corazza >0
}
