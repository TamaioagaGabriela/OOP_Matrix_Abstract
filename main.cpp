#include <iostream>
#include <string>
#include <fstream>
#include "OOP_Matrix_Abstract.h"

using namespace std;

istream & operator >> (istream &in,  VectorIntregi &vect)           // supraincarcarea op. de citire pt VECTORI
{
    for(int j = 0; j < vect.dim; j++)
    {
        in >> vect.v[j];
    }
    return in;
}

ostream & operator << (ostream &out, const VectorIntregi &vect)     // supraincarcarea op. de afisare pt VECTORI
{
    for(int j = 0; j < vect.dim; j++)
        out << vect.v[j] << " ";
    out << endl;
    return out;
}

void VectorIntregi::set_Nr(int i)                                   // setare nr elemente vector
{
    dim = i;
}

void VectorIntregi::set_Dim_Vector(int dim)                         // alocare dinamica vector de tip int
{
    v = new int[dim];
}

int VectorIntregi::get_Nr()                                         // returnez dimensiunea vectorului
{
    return dim;
}

int * VectorIntregi:: get_Vect()                       // obtin vectorul cu elemente de tip int
{
    return v;
}

int VectorIntregi:: suma()
{
    int suma = 0;
    for(int i = 0; i < dim; i++)
        suma = suma + v[i];
    return suma;
}

int VectorIntregi:: maxim()
{
    int max_vector = v[0];
    int i = 1;
    while(i < dim)
    {
        if (max_vector < v[i])
            max_vector = v[i];
        i++;
    }
    return max_vector;
}

int VectorIntregi:: poz_maxim()
{
    int poz_max_vector = 0;
    int max_vector = v[0];
    int i = 1;
    while(i < dim)
    {
        if (max_vector < v[i])
        {
            max_vector = v[i];
            poz_max_vector = i;
        }
        i++;
    }
    return poz_max_vector;
}

void VectorIntregi::sortare()
{
    int i,j;
    for(i = 0; i < dim-1; i++)
        for(j = 0; j < dim-i-1; j++)
        {
            if (v[j] > v[j+1])
                swap(v[j], v[j+1]);
        }
}

int VectorIntregi:: operator*(VectorIntregi w)                                // produsul scalar dintre 2 vectori
{
    int i, prod_sc = 0;
    for(i = 0; i < dim; i++)
        prod_sc = v[i] * w.v[i] + prod_sc;
    return prod_sc;
}


istream & operator >> (istream &in,  MatriceIntregi_Oarecare &matrice)        // supraincarcarea op. de citire pt MATRICE OARECARE
{
    for(int j = 0; j < matrice.nr_linii; j++)
    {
        in >> matrice.a[j];
    }
    return in;
}

ostream & operator << (ostream &out, const MatriceIntregi_Oarecare &matrice)  //supraincarcarea op. de afisare pt MATRICE OARECARE
{
    for(int j = 0; j < matrice.nr_linii; j++)
    {
        out << matrice.a[j];
    }
    return out;
}

VectorIntregi * MatriceIntregi_Oarecare:: get_A()                             // obtin vectorul a de tip vectorintreg => matricea
{
    return a;
}

int MatriceIntregi_Oarecare:: get_Nr_linii()                                  // obtin nr de linii ale matricei oarecare
{
    return nr_linii;
}

void MatriceIntregi_Oarecare::set_Dimensiuni(int i, int j)                    // setez dimensiunile matricei oarecare
{
    nr_linii = i;
    nr_coloane = j;
}

MatriceIntregi_Oarecare MatriceIntregi_Oarecare :: operator+ (MatriceIntregi_Oarecare & B)    // suma a doua matrice oarecare
{
    MatriceIntregi_Oarecare rezultat(this -> nr_linii, this -> nr_coloane);
    rezultat.set_Dimensiuni(this -> nr_linii, this -> nr_coloane);
    for(int j = 0; j < this -> nr_linii; j++)
    {
        rezultat.a[j].set_Nr(this -> nr_coloane);                             // pt fiecare vector linie setez dimensiunea
        for (int k = 0; k < this -> nr_coloane; k++)
        {
            rezultat.a[j].v[k] = B.a[j].v[k] + this -> a[j].v[k];
        }
    }
    return rezultat;
};

int verificare(MatriceIntregi_Oarecare A, VectorIntregi x, VectorIntregi y)   // calculez produsul dintre o matrice oarecare si vector cu ajutorul prod. scalar
{
    int ok = 1;
    int nr_linii = A.get_Nr_linii();
    for(int j = 0; j < nr_linii; j++)
    {
        if (x * A.get_A()[j] != y.get_Vect()[j])
            ok=0;
    }
    return ok;
}


istream & operator >> (istream &in,  MatriceIntregi_Patratica &matrice)       // supraincarcarea op. de citire pt MATRICE PATRATICA
{
    for(int j = 0; j < matrice.dim; j++)
    {
      in >> matrice.a[j];
    }
    return in;
}

ostream & operator << (ostream &out, const MatriceIntregi_Patratica &matrice) //supraincarcarea op. de afisare pt MATRICE PATRATICA
{
    for(int j = 0; j < matrice.dim; j++)
    {
        out << matrice.a[j];
    }
    return out;
}

VectorIntregi * MatriceIntregi_Patratica:: get_A()                            // obtin vectorul a de tip vectorintreg => matricea patratica
{
    return a;
}

int MatriceIntregi_Patratica:: get_Nr_linii()                                 // obtin dimensiunea matricei patratice
{
    return dim;
}

void MatriceIntregi_Patratica::set_Dimensiuni(int i)                          // setez dimensiunea pt matricea patratica
{
    dim = i;
}

MatriceIntregi_Patratica MatriceIntregi_Patratica :: operator+ (MatriceIntregi_Patratica & B)  // suma a doua matrice patratice
{
    MatriceIntregi_Patratica rezultat(this -> dim);
    rezultat.set_Dimensiuni(this -> dim);
    for(int j = 0; j < this -> dim; j++)
    {
        rezultat.a[j].set_Nr(this -> dim);                                    // pt fiecare vector linie setez dimensiunea

        for (int k = 0; k < this -> dim; k++)
        {
            rezultat.a[j].v[k] = B.a[j].v[k] + this -> a[j].v[k];
        }
    }
    return rezultat;
};

int MatriceIntregi_Patratica :: get_determinant()                             // obtin determinantul matricei patratice
{
    return Det(*this);
}

MatriceIntregi_Patratica MatriceIntregi_Patratica :: get_cofactor(int rand, int coloana)
{
    MatriceIntregi_Patratica temp(dim - 1);                                   // aloc memorie pt matrice prin constructorul cu parametrii
    temp.set_Dimensiuni(dim-1);                                               // setez dimensiunea matricei

    for (int i = 0, k = 0; i < dim; i++)
    {
        if(i == rand)
            continue;
        for (int j = 0, l = 0; j < dim; j++)                                  // obtin matricea fara linia i si coloana j
        {
            if(j == coloana)
                continue;
            temp.a[k].v[l++] = a[i].v[j];
        }
        k++;
    }
    return temp;
}

int MatriceIntregi_Patratica :: Det(MatriceIntregi_Patratica& matrice)        // functie recursiva
{
    if (matrice.dim == 1)
        return matrice.a[0].v[0];
    int D=0;
    for (int i = 0; i < matrice.dim; i++)
    {
        MatriceIntregi_Patratica tempp = matrice.get_cofactor(i, matrice.dim - 1);
        D = D + ((i + matrice.dim - 1) % 2 ? -1 : 1) * matrice.a[i].v[matrice.dim-1] * Det(tempp);  // dezvoltare pe linii si coloane, adun determinantii minorilor
        if (tempp.a != nullptr)
            delete &tempp;
    }
    return D;
}


int main()
{
    int i, cerinta;
    cout << "Alegeti modul de citire a vectorilor si a matricilor(1-consola, 2-fisier): ";
    cin >> i;
    if (i == 1)
    {
        cout << "Alegeti numarul cerintei (1-operatii vector, 2-operatii matrice, 3-functia verificare): ";
        cin >> cerinta;
        if (cerinta == 1)
        {
            //SUBPUNCT 1
            int nr;
            cout << "Dati numarul de elemente ale vectorului: ";
            cin >> nr;
            VectorIntregi v1(nr);                                   // apelez constructorul cu parametru prin care aloc memorie
            VectorIntregi v2(nr);
            v1.set_Nr(nr);                                          // setez dimensiunea vectorilor
            v2.set_Nr(nr);
            cout << "Scrieti elementele vectorului nr. 1: ";
            cin >> v1;

            cout << "Suma: " << v1.suma() << endl;
            cout << "Maxim: " << v1.maxim() << endl;
            cout << "Pozitie maxim: " << v1.poz_maxim() << endl;
            cout << "Scrieti elementele vectorului nr. 2: ";
            cin >> v2;

            cout << "Produs scalar dintre cei doi vectori este: " << v1 * v2 << endl;
            v1.sortare();
            cout << "Vectorul nr. 1 este sortat: " << v1 << endl;
           // delete []v1.get_Vect();                                 // eliberez memoria alocata pt vectori
            //delete []v2.get_Vect();
        }

        else if (cerinta == 2)
        {
            //SUBPUNCT 2
            int nr_linii, nr_coloane;
            cout << "Dati numarul de linii si de coloane ale matricii: ";
            cin >> nr_linii >> nr_coloane;
            if (nr_linii != nr_coloane)
            {
                MatriceIntregi_Oarecare m1(nr_linii, nr_coloane);
                MatriceIntregi_Oarecare m2(nr_linii, nr_coloane);   // apelez constructorul cu parametrii prin care aloc memorie

                m1.set_Dimensiuni(nr_linii,nr_coloane);             // setez dimensiunea matricilor
                m2.set_Dimensiuni(nr_linii,nr_coloane);

                cout << "Scrieti matricea nr. 1:" << endl;
                cin >> m1;
                if (m1.diagonala())                                 // verificare diagonala; apelare functie virtuala
                    cout << "Matricea oarecare este diagonala" << endl << endl;
                else cout << "Matricea oarecare nu e diagonala" << endl << endl;

                cout << "Scrieti matricea nr. 2:" << endl;
                cin >> m2;
                if (m2.diagonala())
                    cout << "Matricea oarecare este diagonala" << endl << endl;
                else cout << "Matricea oarecare nu este diagonala" << endl << endl;
                cout << "Suma celor doua matrici este: " << endl;
                cout << m1+m2;                                       // suma a doua matrici oarecare
                //delete []m1.get_A();                                          // eliberez memoria alocata pt matrice
                //delete []m2.get_A();
            }

            else
            {
                int dim;
                dim = nr_coloane;
                MatriceIntregi_Patratica m3(dim);                    // apelez constructorul cu parametrii prin care aloc memorie
                MatriceIntregi_Patratica m4(dim);
                m3.set_Dimensiuni(dim);                              // setez dimensiunea matricilor
                m4.set_Dimensiuni(dim);

                cout<< "Scrieti matricea patratica nr.1:" << endl;
                cin >> m3;
                if (m3.diagonala())                                  // verificare diagonala; apelare functie virtuala
                    cout << "Matricea patratica este diagonala" << endl;
                else cout << "Matricea patratica NU este diagonala" << endl;
                cout << "Determinantul matricii este: ";
                cout << m3.get_determinant() << endl << endl;

                cout<< "Scrieti matricea patratica nr.2:" << endl;
                cin >> m4;
                if (m4.diagonala())
                    cout << "Matricea patratica este diagonala" << endl;
                else cout << "Matricea patratica NU este diagonala" << endl;
                cout << "Determinantul matricii este: ";
                cout << m4.get_determinant() << endl << endl;

                cout << "Suma celor doua matrici patrate este: " << endl;
                cout << m3+m4;                                       // suma a doua matrici patratice
                //delete &m3;                                          // eliberez memoria alocata pt matrice
                //delete &m4;

            }
        }

        else if(cerinta == 3)
        {
            //  SUBPUNCT 3
            int nr_linii_a, nr_coloane_a, ok;
            cout << "Dati numarul de linii si de coloane ale matricii A: ";
            cin >> nr_linii_a >> nr_coloane_a;
            MatriceIntregi_Oarecare a(nr_linii_a, nr_coloane_a);               // apelez constructorul cu parametrii; aloc memorie pt matrice
            VectorIntregi x(nr_coloane_a);                                     // apelez constructorul cu parametru; aloc memorie pt vectori
            VectorIntregi y(nr_linii_a);
            a.set_Dimensiuni(nr_linii_a,nr_coloane_a);                         // setez dimensiunea matricii
            cout << "Scrieti matricea A:" << endl;
            cin >> a;
            x.set_Nr(nr_coloane_a);                                            // setez dimensiunea vectorilor
            y.set_Nr(nr_linii_a);
            cout << "Scrieti elementele vectorului X (" << nr_coloane_a << " elemente):";
            cin >> x;
            cout << "Scrieti elementele vectorului Y (" << nr_linii_a << " elemente):";
            cin >> y;
            ok = verificare( a, x, y);                                         // verificare Ax=y
            if (ok == 0)
                cout << "Nu, nu se verifica ecuatia Ax=y!" << endl;
            else cout << "Da,se verifica ecuatia Ax=y!" << endl;
         //   delete []y.get_Vect();
           // delete []x.get_Vect();      // eliberez memoria alocata pt vectori, respectiv pt matrice
            //delete []a.get_A();
           // delete &a;
        }
    }
    else if (i == 2)
    {
        std::ifstream f("abs.in");      // fisierul din care citesc
        std::ofstream g("abs.out");     // fisierul in care afisez
        //SUBPUNCT A
        int nr_elem;
        f >> nr_elem;
        VectorIntregi v1(nr_elem);      // apelez constructorul cu parametru; aloc memorie pt vectori
        v1.set_Nr(nr_elem);
        VectorIntregi v2(nr_elem);
        v2.set_Nr(nr_elem);             // setez dimensiunea vectorului
        f >> v1;
        g << "Vectorul nr. 1 este: ";
        g << v1;
        g << "Suma: " << v1.suma() << endl;
        g << "Maxim: " << v1.maxim() << endl;
        g << "Pozitie maxim: " << v1.poz_maxim() << endl;
        f >> v2;
        g << "Vectorul nr. 2 este: ";
        g << v2;
        g << "Produs scalar: " << v1*v2 << endl;
        v1.sortare();
        g << "Vectorul este sortat: " << v1;
        g << endl;
       // delete []v1.get_Vect();
        //delete []v2.get_Vect();          // eliberez memoria alocata pt vectori

        //SUBPUNCT 2
        int nr_linii, nr_coloane;
        f >> nr_linii >> nr_coloane;
        if (nr_linii != nr_coloane)
        {
            MatriceIntregi_Oarecare m1(nr_linii, nr_coloane);           // apelez constructorul cu parametrii; aloc memorie pt matrice
            m1.set_Dimensiuni(nr_linii, nr_coloane);
            MatriceIntregi_Oarecare m2(nr_linii, nr_coloane);
            m2.set_Dimensiuni(nr_linii, nr_coloane);                    // setez dimensiunile matricei

            f >> m1;
            g << "Matricea oarecare nr. 1 este: " << endl << m1;        // verificare diagonala: apelare functie virtuala
            if (m1.diagonala())
                g << "Matricea oarecare este diagonala." << endl;
            else g << "Matricea oarecare nu este diagonala." << endl;

            f >> m2;
            g << "Matricea oarecare nr. 2 este: " << endl << m2;
            if (m2.diagonala())
                g << "Matricea oarecare este diagonala." << endl << endl;
            else g << "Matricea oarecare nu este diagonala." << endl << endl;
            g << "Suma matricilor oarecare este: " << endl;
            g << m2 + m1 << endl;
          //  delete &m1;                                                  // eliberez memoria alocata pt matrice
            //delete &m2;
        }

        else
        {
            int dim;
            dim = nr_linii;
            MatriceIntregi_Patratica m3(dim);                           // apelez constructorul cu parametrii; aloc memorie pt matrice
            MatriceIntregi_Patratica m4(dim);
            m3.set_Dimensiuni(dim);                                     // setez dimensiunile matricei
            m4.set_Dimensiuni(dim);

            f >> m3;
            g << "Matricea patratica nr. 1 este: " << endl;
            g << m3;
            if (m3.diagonala())                                        // verificare diagonala: apelare functie virtuala
                g << "Matricea patratica este diagonala." << endl;
            else g << "Matricea patratica nu este diagonala." << endl;
            g << "Determinantul matricii este: ";
            g << m3.get_determinant() << endl << endl;                 // apelare functie determinant
            f >> m4;
            g << "Matricea patratica nr. 2 este: " << endl;
            g << m4;
            if (m4.diagonala())
                g << "Matricea patratica este diagonala." << endl;
            else g << "Matricea patratica nu este diagonala." << endl;
            g << "Determinantul matricii este: ";
            g << m4.get_determinant() << endl << endl;

            g << "Suma celor doua matrici patrate este: " << endl;     // adunarea a doua matrici
            g << m4 + m3;
            g << endl;
          //  delete &m3;                                                // eliberez memoria alocata pt matrice
            //delete &m4;
        }
        //SUBPUNCT 3
        int nr_linii_a, nr_coloane_a, ok;
        f >> nr_linii_a >> nr_coloane_a;
        MatriceIntregi_Oarecare a(nr_linii_a, nr_coloane_a); // apelez constructorul cu parametrii; aloc memorie pt matrice
        a.set_Dimensiuni(nr_linii_a, nr_coloane_a);          // setez dimensiunile matricei
        f >> a;
        g << "Matricea A este:" << endl <<a;
        VectorIntregi x(nr_coloane_a);                      // apelez constructorul cu parametru; aloc memorie pt vector
        x.set_Nr(nr_coloane_a);
        VectorIntregi y(nr_linii_a);
        y.set_Nr(nr_linii_a);                               // setez lungimea vectorilor
        f >> x;
        g << "Vectorul x este:" << endl << x;
        f >> y;
        g << "Vectorul y este:" << endl << y;
        ok = verificare( a, x, y);                          // functia de verificare: Ax=y
        if (ok == 0)
            g << "Nu, nu se verifica ecuatia Ax=y!";
        else g << "Da,se verifica ecuatia Ax=y!";

       // delete []y.get_Vect();                              // eliberez memoria alocata vectorilor
        //delete []x.get_Vect();
        //delete &a;                                          // eliberez memoria alocata matricii

        g.close();                                          // inchid fisierele
        f.close();
    }
    return 0;
}
