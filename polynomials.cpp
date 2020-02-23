#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
using namespace std;
class Polinom
{
    int grad_polinom;
    double *coeficenti;

public:

    Polinom() {
        grad_polinom = -1;
        coeficenti = NULL;
    }
    //supraincarcarea lui <<
    friend ostream& operator<<(ostream &output, const Polinom &P ) {
         output << "Grad = " << P.grad_polinom << "\n";
         output << "Coeficentii: ";
         int i;
         for (i = 0; i <= P.grad_polinom; i++) output << P.coeficenti[i] << " ";
         output << "\n";
         return output;
    }
    //supraincarcarea lui >>
    friend istream& operator>>(istream  &input, Polinom &P) {
         input >> P.grad_polinom;
         P.coeficenti = new double[P.grad_polinom + 1];
         int i;
         for (i = 0; i <= P.grad_polinom; i++) input >> P.coeficenti[i];
         return input;
    }
    //calcul valoare
    double Calcul (double x);

    //supraincarcarea operatorului =
    Polinom& operator=(Polinom p2) {
        this->grad_polinom = p2.grad_polinom;
        this->coeficenti = new double[p2.grad_polinom+1];
        int i;
        for (i = 0; i <= grad_polinom; i++) this->coeficenti[i] = p2.coeficenti[i];
        return *this;
    }

    //suma a doua polinoame prin supraincarcarea lui +
    Polinom operator+(const Polinom& p2) {
        Polinom rezultat;
        int grad_maxim = (this->grad_polinom > p2.grad_polinom)? this->grad_polinom : p2.grad_polinom;
        int grad_minim = (this->grad_polinom < p2.grad_polinom)? this->grad_polinom : p2.grad_polinom;

        rezultat.grad_polinom = grad_maxim;
        rezultat.coeficenti = new double[grad_maxim+1];

        int i;
        for (i = 0; i <= grad_minim; i++) rezultat.coeficenti[i] = this->coeficenti[i] + p2.coeficenti[i];
        if (this->grad_polinom > p2.grad_polinom)
            for (i = grad_minim + 1; i <= grad_maxim; i++) rezultat.coeficenti[i] = this->coeficenti[i];
        else for (i = grad_minim + 1; i <= grad_maxim; i++) rezultat.coeficenti[i] = p2.coeficenti[i];

        return rezultat;
    }

    //diferenta a doua polinoame prin supraincarcarea lui -
    Polinom operator-(const Polinom& p2) {
        Polinom rezultat;
        int grad_maxim = (this->grad_polinom > p2.grad_polinom)? this->grad_polinom : p2.grad_polinom;
        int grad_minim = (this->grad_polinom < p2.grad_polinom)? this->grad_polinom : p2.grad_polinom;

        rezultat.grad_polinom = grad_maxim;
        rezultat.coeficenti = new double[grad_maxim + 1];

        int i;
        for (i = 0; i <= grad_minim; i++) rezultat.coeficenti[i] = this->coeficenti[i] - p2.coeficenti[i];
        if (this->grad_polinom > p2.grad_polinom)
            for (i = grad_minim + 1; i <= grad_maxim; i++) rezultat.coeficenti[i] = this->coeficenti[i];
        else for (i = grad_minim + 1; i <= grad_maxim; i++) rezultat.coeficenti[i] = p2.coeficenti[i];

        return rezultat;
    }
    //produsul a doua polinoame prin supraincarcarea lui *
    Polinom operator*(const Polinom& p2) {
        Polinom rezultat;
        rezultat.grad_polinom = this->grad_polinom + p2.grad_polinom;

        int dim_coef = rezultat.grad_polinom + 1;
        rezultat.coeficenti = new double[dim_coef];

        int i, j;
        for (i = 0; i < dim_coef; i++) rezultat.coeficenti[i] = 0;

        for (i = 0; i <= this->grad_polinom; i++)
            for (j = 0; j <= p2.grad_polinom; j++) {
            rezultat.coeficenti[i+j] += this->coeficenti[i] * p2.coeficenti[j];
            }
        return rezultat;
    }

    ~Polinom() { delete coeficenti; }
    friend class Pereche;
};
double Polinom::Calcul(double x)
{
    int grad = grad_polinom;
    double rezultat = 0;
    while (grad >= 0) {
        rezultat += coeficenti[grad] * pow(x,grad);
        grad--;
    }
    return rezultat;
}
class Pereche {
    double x;
    Polinom P;
public:
    Pereche() { x = 0; }
    Pereche(double a, Polinom p2) {
        x = a;
        P.grad_polinom = p2.grad_polinom;
        P.coeficenti = new double[p2.grad_polinom + 1];
        int i;
        for (i = 0; i <= p2.grad_polinom; i++) P.coeficenti[i] = p2.coeficenti[i];
    }
    ~Pereche(){}

    int getx() { return x; }

    friend ostream& operator<<(ostream &output, const Pereche &Y ) {
         output << "Perechea formata din: \n";
         output << "x=" << Y.x << "\n";
         output << "Polinomul: \n" << Y.P;
         output << "\n";
         return output;
    }
    friend istream& operator>>(istream  &input, Pereche &Y) {
         input >> Y.x;
         input >> Y.P;
         return input;
    }
    unsigned int Radacina() {
        if (P.Calcul(x)) return 0;
        return 1;
    }
};
int main() {
    Polinom p1, p2;
    cout << "Introduceti gradul si coeficenti primului polinom. \n";
    cin >> p1;
    cout << p1 << "\n\n";

    ifstream f("date.txt");
    ofstream g("date2.txt");
    f >> p2;
    g << p2;
    cout << "Al doilea polinom a fost citit din fisier si are gradul si coeficentii urmatori: \n";
    cout << p2;
    f.close();
    g.close();

    double x;
    cout << "\nCalcul valoarea polinoamelor in punctul x.\n";
    cout << "x = "; cin >> x; cout << "\n";
    cout << "Valoarea primului polinom in punctul x = " << x << " este " << p1.Calcul(x) << ".\n";
    cout << "Valoarea celui de-al doilea polinom in punctul x = " << x << " este " << p2.Calcul(x) << ".\n";

    Polinom p3;

    p3 = p1 + p2;
    cout << "\nPolinomul suma: \n" << p3 << "\n";

    p3 = p1 - p2;
    cout << "\nPolinomul diferenta: \n" << p3 << "\n";

    p3 = p1 * p2;
    cout << "\nPolinomul produs: \n" << p3 << "\n";

    cout << "Verificare pereche.\n";

    double r;
    cout << "\n1) Verificare daca r este radacina pentru primul polinom introdus.(folosirea constructorului cu parametri)\n" << "r=";
    cin >> r;

    Pereche p(r,p1);
    if (p.Radacina()) cout << "r=" << r << " este radacina pentru polinom.\n\n";
     else cout << "r=" << r << " nu este radacina pentru polinom.\n\n";

    cout << "2) Verificare pereche. (constructorul fara parametri)\n\n";
    Pereche z;
    cout << "Introduceti pereche(radacina, grad polinom, coeficenti polinom):\n";
    cin >> z;
    cout << "\n" << z;

    if (z.Radacina()) cout << "x=" << z.getx() << " este radacina pentru polinom.\n";
     else cout << "x=" << z.getx() << " nu este radacina pentru polinom.\n";

    //citirea informațiilor complete a n obiecte, memorarea și afisarea acestora
    cout << "\nCitirea, memorarea si afisarea a n obiecte.\n\n";
    unsigned int n, i;
    cout << "n="; cin >> n;
    Polinom *v = (Polinom *) malloc(n*sizeof(Polinom));
    for (i = 0; i < n; i++) {
        cout << "Intoduceti polinomul " << i + 1 <<"\n";
        cin >> v[i];
    }
    cout << "\n";
    for (i = 0; i < n; i++) {
        cout << "Polinomul " << i + 1 << "\n" << v[i] << "\n";
    }
    free(v);

    return 0;
}
