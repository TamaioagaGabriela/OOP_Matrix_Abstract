#ifndef OOP_MATRIX_ABSTRACT_H_INCLUDED
#define OOP_MATRIX_ABSTRACT_H_INCLUDED

using namespace std;

class VectorIntregi
{
    int *v;

protected:
    int dim;

public:
    int suma();
    int maxim();
    int poz_maxim();
    void sortare();
    void set_Nr(int i);
    void set_Dim_Vector(int dim);
    int get_Nr();
    int * get_Vect();
    int operator* (VectorIntregi w);

    friend ostream & operator << (ostream &out, const VectorIntregi &vect);
    friend istream & operator >> (istream &in, VectorIntregi &vect);
    friend class MatriceIntregi;
    friend class MatriceIntregi_Oarecare;
    friend class MatriceIntregi_Patratica;

    VectorIntregi()
    {
        v = NULL;                            //constructorul de initializare
    }

    VectorIntregi(int dim)
    {
        v = new int[dim];                    //constructorul cu parametru (pt alocare dinamica)
    }

    VectorIntregi(VectorIntregi &vect)       //constructorul de copiere
    {
        v = new int[vect.dim];
        dim = vect.dim;
        for (int i = 0; i <= vect.dim; i++)
            v[i] = vect.v[i];
    }

    VectorIntregi operator = (VectorIntregi vect)
    {
        delete []this->v;
        v = new int[vect.dim];
        dim = vect.dim;
        for (int i = 0; i <= vect.dim; i++)
        {
            v[i]= vect.v[i];
        }
        return *this;
    }

    ~VectorIntregi()                        // destructorul - sterg memoria alocata pt vector
    {
        if (v != NULL)
            delete []v;
    }
};

class MatriceIntregi
{
protected:
    VectorIntregi *a;

public:
    void set_Dimensiuni(int, int );
    VectorIntregi * get_A();
    int get_Nr_linii();
    virtual bool diagonala()=0;             // functia virtuala pe care o implementez ulterior, la matrice oarecare, respectiv patratica

    MatriceIntregi()                        // constructorul de initializare
    {
        a = nullptr;
    };

    virtual ~MatriceIntregi() = 0;          // destructorul - de tip virtual
};

MatriceIntregi::  ~MatriceIntregi() {}

class MatriceIntregi_Oarecare: public MatriceIntregi
{
    int nr_linii;
    int nr_coloane;

public:

    VectorIntregi * get_A();
    void set_Dimensiuni(int i, int j);
    int get_Nr_linii();
    MatriceIntregi_Oarecare operator+ (MatriceIntregi_Oarecare & B);     // suma a doua matrici oarecare
    bool diagonala()                                                     // implementare functie virtuala; verific daca e diagonala
    {
        for (int i = 0; i < nr_linii; i ++)
            for (int j = 0; j < nr_coloane; j ++)
                if (i != j && a[i].v[j]!=0)
                    return false;
        return true;
    };

    friend ostream & operator << (ostream &out, const MatriceIntregi_Oarecare &matrice);
    friend istream & operator >> (istream &in,  MatriceIntregi_Oarecare &matrice);

    MatriceIntregi_Oarecare(): MatriceIntregi()                           // constructor de initializare
    {
        nr_linii = 0;
        nr_coloane = 0;
    }

    MatriceIntregi_Oarecare(int nr_linii, int nr_coloane): MatriceIntregi()  // constructor cu parametrii (pt alocare dinamica)
    {
        a = new VectorIntregi(nr_linii);
        for(int i = 0; i < nr_linii; i++)
        {
            a[i].set_Nr(nr_coloane);
            a[i].set_Dim_Vector(nr_coloane);     // aloc memorie pentru fiecare vector
        }
    }

    virtual ~MatriceIntregi_Oarecare()          // destructorul de tip virtual implementat
    {
        if(a != nullptr)
        {
            for (int i = 0; i < nr_linii; i++)
                delete &(a[i]);                 // sterg memoria alocata pt fiecare vector linie
            delete a;                           // sterg memoria alocata pt matrice
        }
    }
};

class MatriceIntregi_Patratica: public MatriceIntregi
{
    int dim;
public:

    VectorIntregi * get_A();
    void set_Dimensiuni(int i);
    int get_Nr_linii();
    bool diagonala()                                     // implementare functie virtuala - verific daca matricea e diagonala
    {
        for (int i = 0; i < dim; i ++)
            for (int j = 0; j < dim; j ++)
                if (i != j && a[i].v[j]!=0)
                    return false;
        return true;
    }

    int Det(MatriceIntregi_Patratica& matrice);                           // functie recursiva: dezvoltare dupa linii si coloane
    MatriceIntregi_Patratica get_cofactor(int rand, int coloana);         // returneaza matricea fara linia si coloana date ca parametrii
    int get_determinant();                                                // returneaza valoarea determinantului
    MatriceIntregi_Patratica operator+ (MatriceIntregi_Patratica & B);    // suma a doua matrici patratice

    friend ostream & operator << (ostream &out, const MatriceIntregi_Patratica &matrice);
    friend istream & operator >> (istream &in,  MatriceIntregi_Patratica &matrice);

    MatriceIntregi_Patratica(): MatriceIntregi()         // constructorul de initializare
    {
        dim = 0;
    }

    MatriceIntregi_Patratica(int dim): MatriceIntregi()  // constructorul cu parametru (pt alocare dinamica)
    {
        a = new VectorIntregi(dim);
        for (int i = 0; i < dim; i++)
        {
            a[i].set_Nr(dim);
            a[i].set_Dim_Vector(dim);                    // aloc memorie pt fiecare vector de pe linie=dim
        }
    }

    virtual ~MatriceIntregi_Patratica()                  // destructorul de tip virtual
    {
        if (a != nullptr)
        {
            for (int i = 0; i < dim; i++)
                delete &(a[i]);                          // sterg memoria alocata pt fiecare vector
            delete a;                                    // sterg memoria alocata pt matrice
        }
    }
};

#endif // OOP_MATRIX_ABSTRACT_H_INCLUDED
