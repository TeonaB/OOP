#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>


///clasa locuinta sau clasa de baza
class Locuinta {
protected:
    std::string numeClient;
    int suprafataUtila;
    float discount;
public:
    Locuinta(std::string numeClient, int suprafataUtila, float discount) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount){};

    ///operatori citire si afisare
    friend std::istream& operator>>(std::istream& in, Locuinta& locuinta)
    {
        std::cout<<"Numele clientului:";
        in>>locuinta.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>locuinta.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>locuinta.discount;
        if(locuinta.discount<=0)
            {
                throw std::runtime_error("Discount imposibil!");
            }
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Locuinta& locuinta)
    {
        out << "Numele clientului: " << locuinta.numeClient << std::endl<<"Suprafata utila: " << locuinta.suprafataUtila << std::endl<< "Discount: " << locuinta.discount << std::endl;
        return out;
    }
    ///calculul chiriei
    virtual float CalculChirie(int X, bool Y) = 0;
    float getDiscount()
    {
        return discount;
    }

    virtual void Afisare()
    {
        std::cout<<"Numele clientului: " << numeClient << std::endl<<"Suprafata utila: " << suprafataUtila << std::endl<< "Discount: " << discount << std::endl;
    }

};


///clasa apartament, derivata 2
class Apartament : public Locuinta {
private:
    int etaj;
public:
    Apartament(std::string numeClient, int suprafataUtila, float discount, int etaj) : Locuinta(numeClient, suprafataUtila, discount), etaj(etaj) {}

    ///operatori de citire si afisare
    friend std::istream& operator>>(std::istream& in, Apartament& apartament)
    {
        std::cout<<"Numele clientului:";
        in>>apartament.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>apartament.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>apartament.discount;
        if(apartament.discount<=0)
            {
                throw std::runtime_error("Discount imposibil!");
            }
        std::cout<<std::endl<<"Etaj:";
        in>>apartament.etaj;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Apartament& apartament) {
        out << "Tip locuinta: Apartament" << std::endl<< "Etaj: " << apartament.etaj << std::endl<< static_cast<Locuinta&>(apartament);
        return out;
    }
    ///calculul chiriei
    float CalculChirie(int X, bool Y) override
    {
        return X * suprafataUtila * (1 - Y * discount / 100.0);
    }

    void Afisare()
    {
        Locuinta::Afisare();
        std::cout<<"Numarul etajului: "<<etaj<<std::endl;
    }
};


///clasa casa, derivata 2
class Casa : public Locuinta {
private:
    int suprafataCurte;
public:
    Casa(std::string numeClient, int suprafataUtila, float discount, int suprafataCurte) : Locuinta(numeClient, suprafataUtila, discount), suprafataCurte(suprafataCurte) {}

    ///operatori de citire si afisare
    friend std::istream& operator>>(std::istream& in, Casa& casa)
    {
        std::cout<<"Numele clientului:";
        in>>casa.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>casa.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>casa.discount;
        if(casa.discount<=0)
            {
                throw std::runtime_error("Discount imposibil!");
            }
        std::cout<<std::endl<<"Suprafata curtii:";
        in>>casa.suprafataCurte;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Casa& casa)
    {
        out << "Tip locuinta: Casa" << std::endl<< "Suprafata curte: " << casa.suprafataCurte << std::endl<< static_cast<Locuinta&>(casa);
        return out;
    }
    ///calculul chiriei
    float CalculChirie(int X, bool Y) override
    {
        return X * (suprafataUtila + 0.2 * suprafataCurte) * (1 - Y * discount / 100.0);
    }

    void Afisare()
    {
        Locuinta::Afisare();
        std::cout<<"Suprafata Curtii: "<<suprafataCurte<<std::endl;
    }
};


///Agentia imobiliara care va avea un vector de pointeri de tip Locuinta
class AgentieImobiliara{
private:
    ///il facem unique pointer ca sa nu putem copia 2 agentii imobiliare, maxim sa le mutam
    std::vector<std::unique_ptr<Locuinta>> listaLocuinte;
public:
    ///initial va fi gol
    AgentieImobiliara(){}
    ~AgentieImobiliara()
    {
        listaLocuinte.clear();
    }

    ///pentru a accesa v si a afla cate locuinte avem folosim metodele
    std::vector<std::unique_ptr<Locuinta>>& GetLista() {
        return listaLocuinte;
    }
    int getNumar() {
        return listaLocuinte.size();
    }
    ///adaugam o locuinta
     void adauga(std::unique_ptr<Locuinta> locuinta) {
       listaLocuinte.push_back(std::move(locuinta));
    }
    ///citirea datelor
    friend std::istream& operator>>(std::istream& is, AgentieImobiliara& other)
    {   int numar;
        std::cout << "Introduceti numarul de locuinte: ";
        is >> numar;
        for (int i = 0; i < numar; i++)
        {
            std::cout << "Introduceti tipul locuintei (A pentru Apartament /C pentru Casa): ";
            char tip;
            is >> tip;
            if (tip == 'A')
            {
                int etaj;
                std::string numeClient;
                int suprafataUtila;
                float discount;
                std::cout << "Introduceti etajul apartamentului: ";
                is >> etaj;
                std::cout << "Introduceti numele clientului: ";
                is >> numeClient;
                std::cout << "Introduceti suprafata utila: ";
                is >> suprafataUtila;
                std::cout << "Introduceti discount-ul (%): ";
                is >> discount;
                try
                {
                    std::cout << "Introduceti discount-ul (%): ";
                    is >> discount;
                    if(discount<=0 || discount>100)
                    {
                        throw std::runtime_error("Discount imposibil!");
                        std::cout<<std::endl<<"Discount:";
                        is>>discount;
                    }
                }
                catch (std::exception const &ex)
                {
                    std::cerr << "Eroare: " << ex.what() << std::endl;
                    std::cout<<std::endl<<"Discount:";
                        is>>discount;
                }
                std::unique_ptr <Locuinta> apartament = std::make_unique<Apartament>(numeClient, suprafataUtila, discount, etaj);
                other.adauga(std::move(apartament));
            }
            else if (tip == 'C')
            {
                int suprafataCurte;
                std::string numeClient;
                int suprafataUtila;
                float discount;
                std::cout << "Introduceti suprafata curtii casei: ";
                is >> suprafataCurte;
                std::cout << "Introduceti numele clientului: ";
                is >> numeClient;
                std::cout << "Introduceti suprafata utila: ";
                is >> suprafataUtila;
                try
                {
                    std::cout << "Introduceti discount-ul (%): ";
                    is >> discount;
                    if(discount<=0 || discount>100)
                    {
                        throw std::runtime_error("Discount imposibil!");
                        std::cout<<std::endl<<"Discount:";
                        is>>discount;
                    }
                }
                catch (std::exception const &ex)
                {
                    std::cerr << "Eroare: " << ex.what() << std::endl;
                    std::cout<<std::endl<<"Discount:";
                        is>>discount;
                }
                std::unique_ptr<Locuinta> casa = std::make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
                other.adauga(std::move(casa));
            }
        }
        return is;
    }

    friend std::ostream& operator<<(std::ostream& out, AgentieImobiliara& other)
    {
        for (int i = 0; i < other.getNumar(); i++)
        {
            out<<"Locuinta " << i+1 << " este:"<<std::endl;
            if(typeid(*other.listaLocuinte[i])==typeid(Casa))
            {
                Casa* temp;
                temp = reinterpret_cast<Casa*>(other.listaLocuinte[i].get());
                temp->Afisare();
            }
            else
                if(typeid(*other.listaLocuinte[i])==typeid(Apartament))
            {
                Apartament* temp;
                temp = reinterpret_cast<Apartament*>(other.listaLocuinte[i].get());
                temp->Afisare();
            }
            out<<"Chiria este de "<<other.listaLocuinte[i]->CalculChirie(25,1)<<std::endl;
            out<<std::endl;
        }
        return out;
    }
};
