//Berno Sara

#ifndef NAVE_H
#define NAVE_H

//classe Nave (astratta)

class Nave{
    
    protected:
        //dichiarazione variabili
        int corazza, dimensione,x_prua, y_prua,x_poppa, y_poppa, x_centro, y_centro;

    public:
        //costruttori:
        Nave();
        Nave(int size){dimensione=size;} //costruttore di default
        Nave(int coordinata_x_prua, int coordinata_y_prua,int coordinata_x_poppa,int coordinata_y_poppa, int dim); //costruttore con posizione prua e poppa
        
        //definizione funzioni pubbliche
        int posizione_x_prua() const {return x_prua;} //restituzione posizione x prua
        int posizione_y_prua() const {return y_prua;} //restituzione posizione y prua
        int posizione_x_poppa() const {return x_poppa;} //restituzione posizione x poppa
        int posizione_y_poppa() const {return y_poppa;} //restituzione posizione y poppa
        int posizione_x_centro() const {return x_centro;} //restituzione posizione x centro
        int posizione_y_centro() const {return y_centro;} //restituzione posizione y centro
        int get_corazza() const {return corazza;}
        void danno();
        void affonda_nave();
};

#endif //NAVE_H
