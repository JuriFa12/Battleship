//Farruku Juri

#ifndef GRIGLIA_H
#define GRIGLIA_H

#include <array>
#include <string>
#include <stdexcept>

//classe griglia (astratta)

class griglia
{
	public:
	
		struct Posizione_fuori_dominio : std::runtime_error //eccezione, utilizzata da tutte le sottoclassi
		{
			Posizione_fuori_dominio(): runtime_error("Posizione_fuori_dominio si è verificata"){}
		};
		
		//costruttori
		griglia();
		griglia(const griglia&); // costruttore di copia
		griglia& operator=(const griglia&); //assegnamento di copia
		virtual void show_griglia()=0;
		
		
		virtual ~griglia(){};

	protected:
		char campo[12][12];
		bool fuori_dominio (int coordinata_x,int coordinata_y);  //verifica se un valore è fuori dominio

};

#endif //GRIGLIA_H