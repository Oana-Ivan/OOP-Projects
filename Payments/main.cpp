#include <iostream>
#include <string.h>
using namespace std;
class Plata {
public:
   Plata() {
       tip_plata = 0;
       zi = luna = an = -1;
       suma = 0.0;
   }
   Plata( int z, int l, int a, double s, int tip) {
       nr_plati++;
       zi = z; luna = l; an = a;
       suma = s;
       tip_plata = tip;
   }
   Plata (Plata & P) {
    nr_plati++;
    //tip_plata = P.tip_plata;
    zi = P.zi; luna = P.luna; an = P.an;
    suma = P.suma;
    tip_plata = P.tip_plata;
   }
   Plata& operator= (Plata& P) {
        //tip_plata = P.tip_plata;
        zi = P.zi; luna = P.luna; an = P.an;
        suma = P.suma;
        tip_plata = P.tip_plata;
        return *this;
   }
   friend ostream & operator << (ostream &output, const Plata &P) {
       output << "Plata nr. " << nr_plati << endl;
       output << "Suma: " << P.suma << endl;
       output << "Data: " << P.zi << "/" << P.luna << "/" << P.an << endl;
       return output;
   }
   friend istream& operator >> (istream &intput, Plata &P) {
       nr_plati++;
       //intput >> P.tip_plata >> P.zi >> P.luna >> P.an >> P.suma;
       intput >> P.zi >> P.luna >> P.an >> P.suma;
       return intput;
   }
   friend int getNr_plati() {return nr_plati;}
   void incrementarePlati() {nr_plati++;}
   int getZi() const {return zi;}
   void setZi(int i) {zi = i;}
   int getLuna() const{return luna;}
   void setLuna(int i) {luna = i;}
   int getAn() const {return an;}
   void setAn(int i) {an = i;}
   double getSuma() const {return suma;}
   void setSuma(int i) {suma = i;}
   int getTip()const {return tip_plata;}
   void setTip(int t) { tip_plata = t;}
   virtual ~Plata(){}
   //friend class plataNumerar;
   virtual char * getNume() const{return NULL;}
   virtual void setNume(char *s, int l){}
   virtual void setCard (int c){}
   virtual int getCard ()const{ return -1;};
private:
    static int nr_plati;
   // unsigned int tip_plata; // 1 pt numerar, 2 pt cec, 3 pt card de credit
    int zi, luna, an, tip_plata;
    double suma;
};
int Plata::nr_plati;
class plataNumerar: public Plata {
public:
   plataNumerar(): Plata() { setTip(1); };
   plataNumerar( int z, int l, int a, double s, int t):Plata( z, l, a, s, t) {};
   plataNumerar(plataNumerar &P):Plata (P) {}; // sau plata(&p)
   plataNumerar& operator= (plataNumerar& P) {
        //tip_plata = P.tip_plata;
        setZi(P.getZi()); setLuna(P.getLuna()); setAn(P.getAn());
        setSuma(P.getSuma());
        setTip(P.getTip());
        return *this;
   }
   friend ostream & operator << (ostream &output,  plataNumerar &P) {
       output << "Tip plata: numerar" << endl; // << getNr_plati() << endl;
       output << "Suma: " << P.getSuma() << endl;
       output << "Data: " << P.getZi() << "/" << P.getLuna() << "/" << P.getAn() << endl;
       output << endl;
       return output;
   }
   friend istream& operator >> (istream &intput, plataNumerar &P) {
       P.incrementarePlati();
       int z, l, a, s;
       intput >> z >> l >> a >> s;
       P.setZi(z);
       P.setLuna(l);
       P.setAn(a);
       P.setSuma(s);
       return intput;
   }
   char * getNume(){return NULL;}
   void setCard (int c){}
   void setNume(){}
   int getCard (){ return -1;};
   ~plataNumerar(){}
};
class plataCec: public Plata {
public:
   plataCec():Plata() {
       nume = NULL;
       setTip(2);
   }
   plataCec(int z, int l, int a, double s, int t,  char * n, int nn): Plata(z, l, a, s, t) {
           nume = new char [nn + 1];
           strcpy(nume, n);
   }
   plataCec(plataCec& P): Plata (P) {
    nume = new char [strlen(P.nume) + 1];
    strcpy(nume, P.nume);
   }
   plataCec& operator= (plataCec& P) {
        setZi(P.getZi()); setLuna(P.getLuna()); setAn(P.getAn());
        setSuma(P.getSuma());
        setTip(P.getTip());
        nume = new char [strlen(P.nume) + 1];
        strcpy(nume, P.nume);
        return *this;
   }
   friend ostream & operator << (ostream &output, const plataCec &P) {
       output << "Tip plata: cec" << endl;
       output << "Suma: " << P.getSuma() << endl;
       output << "Data: " << P.getZi() << "/" << P.getLuna() << "/" << P.getAn() << endl;
       output << "Nume platitor: " << P.nume;
       output << endl;
       return output;
   }
   char * getNume(){return nume;}
   void setNume( char *n, int lung) {
       nume = new char [lung + 1];
       strcpy(nume, n);
   }
   void setCard (int c){}
   int getCard (){return -1;};
   ~plataCec() {
       delete nume;
   }
private:
    char * nume;
};

class plataCard: public plataCec {
public:
   plataCard():plataCec() {
       nr_card = 0;
       setTip(3);
   }
   plataCard(int z, int l, int a, double s, int t, char * n, int nn, int nr_c): plataCec(z, l, a, s, t, n, nn) {
           nr_card = nr_c;
   }
   plataCard(plataCard& P): plataCec (P) {
       nr_card = P.nr_card;
   }
   plataCard& operator= (plataCard& P) {
        setZi(P.getZi()); setLuna(P.getLuna()); setAn(P.getAn());
        setSuma(P.getSuma());
        setTip(P.getTip());
        setNume(P.getNume(),strlen(P.getNume()));
        nr_card = P.nr_card;
        return *this;
   }
    void setCard (int c){nr_card = c;}
   int getCard (){ return nr_card;};
   ~plataCard() {}
private:
    int nr_card;
};

template <class T>
class Gestiune {
public:
    Gestiune() {
        v_plati = NULL;
    }
    Gestiune operator+= (const T& nPlata) {
         Plata aux[nr_plati];
        int i;
        for (i = 0; i < nr_plati - 1; i++) { 
            int z, l, a, s;
            z = v_plati[i].getZi();
            l = v_plati[i].getLuna();
            a = v_plati[i].getAn();
            s = v_plati[i].getSuma();
            aux[i].setZi(z);
            aux[i].setLuna(l);
            aux[i].setAn(a);
            aux[i].setSuma(s);
           try {
               if(aux[i].getTip() == 1) throw 1;
               int nn = strlen(aux[i].getNume());
               char * nm;
               nm = new char[20];
               strcpy(nm, v_plati[i].getNume());
               aux[i].setNume(nm, (nn+1));
               if(aux[i].getTip() == 3) throw 2.0;
                //p[i].setCard(0);
           }

           catch(double x) {
              aux[i].setCard(v_plati[i].getCard());
           }
           catch(int x){}
        }
        v_plati = new Plata [nr_plati - 1];
        for (i = 0; i < nr_plati - 1; i++) {
            //v_plati[i] = aux[i];
            int z, l, a, s;
            z = aux[i].getZi();
            l = aux[i].getLuna();
            a = aux[i].getAn();
            s = aux[i].getSuma();
            v_plati[i].setZi(z);
            v_plati[i].setLuna(l);
            v_plati[i].setAn(a);
            v_plati[i].setSuma(s);
           try {
               if (v_plati[i].getTip() == 1) throw 1;
               int nn = strlen(v_plati[i].getNume());
               char * nm;
               nm = new char[20];
               strcpy(nm, aux[i].getNume());
               v_plati[i].setNume(nm, (nn+1));
               if (v_plati[i].getTip() == 3) throw 2.0;
                //p[i].setCard(0);
           }

           catch(double x) {
              v_plati[i].setCard(aux[i].getCard());
           }
           catch(int x){}
        }
        //v_plati[nr_plati-1] = nPlata;
        int z, l, a, s;
            z = nPlata.getZi();
            l = nPlata.getLuna();
            a = nPlata.getAn();
            s = nPlata.getSuma();
            v_plati[nr_plati-1].setZi(z);
            v_plati[nr_plati-1].setLuna(l);
            v_plati[nr_plati-1].setAn(a);
            v_plati[nr_plati-1].setSuma(s);
           try {
               if(v_plati[nr_plati-1].getTip() == 1) throw 1;
               int nn = strlen(v_plati[nr_plati-1].getNume());
               char * nm;
               nm = new char[20];
               strcpy(nm, nPlata.getNume());
               v_plati[nr_plati-1].setNume(nm, (nn+1));
               if(v_plati[nr_plati-1].getTip() == 3) throw 2.0;
                //p[i].setCard(0);
           }

           catch(double x) {
              v_plati[nr_plati-1].setCard(nPlata.getCard());
           }
           catch(int x){}
    }
    ~Gestiune() {
        delete v_plati;
    }
private:
    static int nr_plati;
    Plata * v_plati;
};
template <class T>
int Gestiune<T>::nr_plati;

template <>
class Gestiune <char *> {
public:
    Gestiune() {
        v_clienti = NULL;
    }
    void adaugareClient (const char* nClient) {
        nr_clienti++;
        char * aux[nr_clienti];
        int i;
        for (i = 0; i < nr_clienti; i++) {
            strcpy(aux[i], v_clienti[i]);
        }
        v_clienti = new char* [nr_clienti];
        for (i = 0; i < nr_clienti - 1; i++) {
            strcpy(v_clienti[i], aux[i]);
        }
        strcpy(v_clienti[nr_clienti-1], nClient);
    }
    ~Gestiune() {
        delete v_clienti;
    }
private:
    static int nr_clienti;
    char ** v_clienti;
};
int Gestiune<char *>::nr_clienti; 

int main() {
    Gestiune <Plata> gestiunePlati;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t, z, l, a, s, card;
        char * nume;
        nume = NULL;
        cout << "Introduceti tipul platii (1 pt numerar, 2 pt cec, 3 pt card): ";
        cin >> t;
        cout << "Data(zi, luna, an): "; cin >> z >> l >> a;
        cout << "Suma:"; cin >> s;
        if(t == 1)
        {
            plataNumerar N(z, l, a, s, t);
            gestiunePlati += N;
        }

        if (t == 2) {
            cout << "Nume: ";
            nume = new char [20];
            cin >> nume;
            if (t == 3) {
                cout << "Nr card ";
                cin >> card;
                plataCard C(z, l,a, s, t, nume, strlen(nume), card);
                gestiunePlati += C;
            }
            plataCec Ce(z, l,a, s, t, nume, strlen(nume));
            gestiunePlati += Ce;
        }
        delete nume;
        nume = NULL;
    }
    return 0;
}
