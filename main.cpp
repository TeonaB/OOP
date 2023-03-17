#include <iostream>
#include <string>
using namespace std;
///Cerinta cu nr.6
class Materie
{
private:
    string denumire;
    bool optional;

public:
    //constructorul de initializare
    Materie()
    {
        denumire=" ";
        optional=true;
    }
    //constructorul pentru atribuire cu 2 parametri
    Materie(const string denumire2, const bool& optional2)
    {
        denumire=denumire2;
        optional=optional2;
    }
    //supraincarcare == pentru if-ul din main
    bool operator==(const Materie& m1)
    {
        if (m1.denumire==denumire && m1.optional==optional)
            return true;
        else
            return false;
    }
    //destructor
    ~Materie() {}
    //functii prieten pentru afisare
    friend ostream& operator<<(ostream& os, const Materie& materie);

};
ostream& operator<<(ostream& out, const Materie& materie)
{
    out << "Materia selectata: " << materie.denumire <<" si optional: "<<materie.optional<<endl;
    return out;
}
class Student
{
private:
    int nrMatricol;
    string nume;
    int grupa;

public:
    //constructor de initializare
    Student()
    {
        nrMatricol=0;
        grupa=0;
        nume=" ";
    }
    //constructor pentru atribuire cu 3 parametri
    Student(const int& nrMatricol2, const string& nume2, const int& grupa2)
    {
        nrMatricol=nrMatricol2;
        nume=nume2;
        grupa=grupa2;
    }
    //supraincarcare = pentru clasa curs
    Student& operator=(const Student& altStudent)
    {
        nrMatricol = altStudent.nrMatricol;
        nume = altStudent.nume;
        grupa = altStudent.grupa;
        return *this;
    }
    //supraincarcare == pentru clasa curs
    bool operator==(const Student& altStudent)
    {
        if(nrMatricol==0)
            return true;
        else
            return false;
    }
    //destructor
    ~Student() {}
    //functii prieten pentru afisare si citire
    friend ostream& operator<<(ostream& os, const Student& student);
    friend istream& operator>>(istream& in, Student& student);

};
ostream& operator<<(ostream& out, const Student& student)
{
    out << "Studentul selectat: " << student.nume <<" din grupa "<<student.grupa<<" si nr matricol "<<student.nrMatricol<<endl;
    return out;
}
istream& operator>>(istream& in, Student& student)
{
    in>>student.nume>>student.nrMatricol>>student.grupa;
    return in;
}
class Curs
{
private:
    Materie mat;
    int NrStudenti;
    Student St[100];

public:
    //constructor de initializare
    Curs()
    {
        mat=Materie();
        NrStudenti=0;
        for(int i=0; i<100; i++)
            St[i]=Student();
    }
    //constructor de atribuire cu 3 parametri
    Curs(const Materie& mat2, const int& nrStudenti2, const Student* St2)
    {
        mat=mat2;
        NrStudenti=nrStudenti2;
        for(int i=0; i<100; i++)
            St[i]=St2[i];
    }
    //constructor de atribuire cu parametru curs
    Curs(const Curs& altCurs)
    {
        mat=altCurs.mat;
        NrStudenti=altCurs.NrStudenti;
        for(int i=0; i<100; i++)
            St[i]=altCurs.St[i];
    }
    //supraincarcare = pentru main
    Curs& operator=(const Curs& altCurs)
    {
        mat=altCurs.mat;
        NrStudenti=altCurs.NrStudenti;
        for(int i=0; i<100; i++)
            St[i]=altCurs.St[i];
        return *this;
    }
    //constructor de atribuire cu parametru materie
    Curs(const Materie& mat2)
    {
        mat=mat2;
        NrStudenti=0;
        for(int i=0; i<100; i++)
            St[i]=Student();
    }
    //supraincarcare += pentru main
    Curs& operator +=(const Student& s)
    {
        for(int i=0; i<100; i++)
            if(St[i]==Student())
            {
                St[i]=s;
                i=100;
            }
        NrStudenti+=1;
        return *this;
    }
    //destructor
    ~Curs(){}
    //supraincarcare + pentru main
    Curs& operator+(const Student &s)
    {
        for(int i=0; i<100; i++)
            if(St[i]==Student())
            {
                St[i]=s;
                i=100;
            }
        NrStudenti+=1;
        return *this;
    }
    //functie prieten pentru afisare
    friend ostream& operator<<(ostream& os, Curs& curs);
    //getter pentru materie sa fie folosita in main
    Materie materie() const
    {
        return mat;
    }

};
ostream& operator<<(ostream& os, Curs& curs)
{
    os << "Cursul selectat: " << curs.materie()<<" cu "<<curs.NrStudenti<<" studenti: "<<endl;
    for(int i=0; i<100; i++)
        if(curs.St[i]==Student())
            i=100;
        else
            os<<curs.St[i];
    return os;
}
int main()
{
    Materie m1("POO",0), m2("Pedagogie",1),m3;
    if (m1==m2)
        cout<<"Cursuri identice"<<endl;
    else
        cout<<"Denumiri diferite"<<endl;
    cout<<"Se da studentul ";
    Student s1(12,"Ionescu",133), s2;
    cin>>s2;
    cout<<s1<<s2;

    Curs c1(m1);
    c1+=s1;
    c1 = c1 + s2;
    Curs c2 = c1;
    cout<<c2;
    m3 = c2.materie();
    cout<<m3;


    return 0;
}
