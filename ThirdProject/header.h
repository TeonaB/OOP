#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <map>


///clasa locuinta sau clasa de baza
class Locuinta
{
protected:
    std::string numeClient;
    int suprafataUtila;
    float discount;
    friend class Builder_agentie;
public:
    Locuinta(std::string numeClient, int suprafataUtila, float discount) : numeClient(numeClient), suprafataUtila(suprafataUtila), discount(discount) {};
    ~Locuinta() {};
    Locuinta()=default;
    Locuinta& operator=(const Locuinta& other)
    {
        numeClient = other.numeClient;
        suprafataUtila = other.suprafataUtila;
        discount = other.discount;
        return *this;
    }
    ///operatori citire si afisare
    friend std::istream& operator>>(std::istream& in, Locuinta& locuinta)
    {
        std::cout<<"Numele clientului:";
        in>>locuinta.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>locuinta.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>locuinta.discount;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, const Locuinta& locuinta)
    {
        out << "Numele clientului: " << locuinta.numeClient << std::endl<<"Suprafata utila: " << locuinta.suprafataUtila << std::endl<< "Discount: " << locuinta.discount << std::endl;
        return out;
    }
    ///calculul chiriei cu fct virtual pura ca sa o putem personaliza pentru fiecare locuinta in parte, in functie de felul acesteia
    virtual float CalculChirie(int X, bool Y) = 0;
    virtual void Afisare()
    {
        std::cout<<"Numele clientului: " << numeClient << std::endl<<"Suprafata utila: " << suprafataUtila << std::endl<< "Discount: " << discount << std::endl;
    }

};


///clasa apartament, derivata 2
class Apartament : public Locuinta
{
private:
    int etaj;
public:
    Apartament(std::string numeClient, int suprafataUtila, float discount, int etaj) : Locuinta(numeClient, suprafataUtila, discount), etaj(etaj) {};
    ~Apartament() {};
    Apartament() = default;
    Apartament& operator=(const Apartament& other)
    {
        Locuinta::operator=(other);
        etaj=other.etaj;
        return *this;
    }
    Apartament(const Apartament* other)
    {
        numeClient=other->numeClient;
        suprafataUtila=other->suprafataUtila;
        discount=other->discount;
        etaj=other->etaj;
    }
    ///operatori de citire si afisare
    friend std::istream& operator>>(std::istream& in, Apartament& apartament)
    {
        std::cout<<"Numele clientului:";
        in>>apartament.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>apartament.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>apartament.discount;
        std::cout<<std::endl<<"Etaj:";
        in>>apartament.etaj;
        return in;
    }
    friend std::ostream& operator<<(std::ostream& out, Apartament& apartament)
    {
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
class Casa : public Locuinta
{
private:
    int suprafataCurte;
public:
    Casa(std::string numeClient, int suprafataUtila, float discount, int suprafataCurte) : Locuinta(numeClient, suprafataUtila, discount), suprafataCurte(suprafataCurte) {}
    ~Casa() {};
    Casa();
    Casa& operator=(const Casa& other)
    {
        Locuinta::operator=(other);
        suprafataCurte=other.suprafataCurte;
        return *this;
    }
    Casa(const Casa* other)
    {
        numeClient=other->numeClient;
        suprafataUtila=other->suprafataUtila;
        discount=other->discount;
        suprafataCurte=other->suprafataCurte;
    }
    ///operatori de citire si afisare
    friend std::istream& operator>>(std::istream& in, Casa& casa)
    {
        std::cout<<"Numele clientului:";
        in>>casa.numeClient;
        std::cout<<std::endl<<"Suprafata utila:";
        in>>casa.suprafataUtila;
        std::cout<<std::endl<<"Discount:";
        in>>casa.discount;
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
///design pattern factory
class Factory_agentie
{
public:
    static Apartament* Apartamentvechi ()
    {
        return new Apartament("Default", 5, 20, 7);
    }
    static Apartament* Apartamentnou ()
    {
        return new Apartament("Default", 10, 0, 3);
    }
    static Casa* Casanoua ()
    {
        return new Casa("Default", 20, 20,350);
    }
    static Casa* Casaveche ()
    {
        return new Casa("Default", 10, 0,150);
    }
};
///design pattern builder
class Builder_agentie
{
private:
    Apartament loc;
public:
    Builder_agentie() = default;
    Builder_agentie& numeClient(const std::string& tip) {
        loc.numeClient = tip;
        return *this;
    }
    Builder_agentie& suprafataUtila(int nr) {
        loc.suprafataUtila = nr;
        return *this;
    }
    Builder_agentie& discount(int nr) {
        loc.discount = nr;
        return *this;
    }
    Apartament build() {
        return new Apartament(loc.numeClient, loc.suprafataUtila, loc.discount,0);
    }
};
///functie template
template<typename U>
U CalculTotal(std::vector<U> a)
{
    U total=0;
    for(int i=0; i<a.size(); i++)
        total+=a[i];
    return total;
}
///clasa template
template<typename T>
class Gestiune
{
private:
    std::vector <int> vector_id;
    std::vector <T> vector_castiguri;
public:
    void adaugaCastig(int id, const T& castiguri)
    {
        int ok=0;
        for(int i=0; i<vector_id.size(); i++)
            if(vector_id[i]==id)
            {
                ok=1;
                vector_castiguri[i] += castiguri;
            }
        if(ok==0)
        {
            vector_id.push_back(id);
            vector_castiguri.push_back(castiguri);
        }
    }
    void afiseazaCastiguri()
    {
        if(vector_id.size()==0)
            std::cout<<"Nu este nimic de afisat"<<std::endl;
        else
        {
            for(int i=0; i<vector_id.size(); i++)
            {
                std::cout<<"Id-ul client "<<vector_id[i]<<std::endl;
                std::cout<<"Incasari lunare "<<vector_castiguri[i]<<std::endl;
            }
            std::cout<<"Suma totala de incasari lunare "<<CalculTotal(vector_castiguri)<<std::endl;
        }
    }
};

static Gestiune<float> gestiuneCastiguri;
static std::string nume="Prima mea agentie";
///Agentia imobiliara care va avea un vector de pointeri de tip Locuinta
class AgentieImobiliara
{
protected:
    ///il facem unique pointer ca sa nu putem copia 2 agentii imobiliare, maxim sa le mutam
    std::vector<std::unique_ptr<Locuinta>> listaLocuinte;
    static std::string nume;
public:
    ///initial va fi gol
    AgentieImobiliara() {};
    ~AgentieImobiliara()
    {
        listaLocuinte.clear();
    }
    ///pentru a accesa v si a afla cate locuinte avem folosim metodele
    std::vector<std::unique_ptr<Locuinta>>& GetLista()
    {
        return listaLocuinte;
    }
    int getNumar()
    {
        return listaLocuinte.size();
    }
    static std::string GetNume()
    {
        return nume;
    }
    ///adaugam o locuinta
    void adauga(std::unique_ptr<Locuinta> locuinta)
    {
        listaLocuinte.push_back(std::move(locuinta));
    }
    ///citirea datelor
    bool adaugaAlegere(AgentieImobiliara& other)
    {
        std::cout<<"Doriti o locuinta existenta sau personalizata?"<<std::endl;
        std::cout<<"1. Locuinta existenta"<<std::endl;
        std::cout<<"2. Locuinta personalizata"<<std::endl;
        int nr;
        std::cin>>nr;
        while(nr!=1 && nr!=2)
        {
            std::cout<<"Incearca alta optiune";
            std::cin>>nr;
        }
        if(nr==1)
        {
            int id, x;
            std::cout << "Introduceti id-ul clientului:";
            std::cin >>id;
            std::cout<<"Alegeti :"<<std::endl;
            std::cout<<"1. Apartament nou"<<std::endl;
            std::cout<<"2. Apartament vechi"<<std::endl;
            std::cout<<"3. Casa noua"<<std::endl;
            std::cout<<"4. Casa veche"<<std::endl;
            std::cout<<"5. Locuinta cu lipsuri"<<std::endl;
            std::cin >>x;
            while(x!=1 && x!=2 && x!=3 && x!=4 && x!=5)
            {
                std::cout<<"Incearca alta optiune";
                std::cin>>x;
            }
            if(x == 1)
            {
                Apartament* locuinta = Factory_agentie::Apartamentnou();
                std::unique_ptr <Locuinta> apartament = std::make_unique<Apartament>(locuinta);
                other.adauga(std::move(apartament));
                gestiuneCastiguri.adaugaCastig(id,2500);
            }
            else if(x == 2)
            {
                Apartament* locuinta = Factory_agentie::Apartamentvechi();
                std::unique_ptr <Locuinta> apartament = std::make_unique<Apartament>(locuinta);
                other.adauga(std::move(apartament));
                gestiuneCastiguri.adaugaCastig(id,1500);
            }
            else if(x == 3)
            {
                Casa* locuinta = Factory_agentie::Casanoua();
                std::unique_ptr <Locuinta> apartament = std::make_unique<Casa>(locuinta);
                other.adauga(std::move(apartament));
                gestiuneCastiguri.adaugaCastig(id,4500);
            }
            else if(x == 4)
            {
                Casa* locuinta = Factory_agentie::Casaveche();
                std::unique_ptr <Locuinta> apartament = std::make_unique<Casa>(locuinta);
                other.adauga(std::move(apartament));
                gestiuneCastiguri.adaugaCastig(id,3500);
            }
            else if(x == 5)
            {
                Builder_agentie loc;
                std::string nume;
                int sup, disc;
                std::cout<< "Nume client: "<<std::endl;
                std::cin>>nume;
                std::cout<< "Suprafata utila: "<<std::endl;
                std::cin>>sup;
                std::cout<< "Discount: "<<std::endl;
                std::cin>>disc;
                Apartament loc2 = loc.numeClient(nume).suprafataUtila(sup).discount(disc).build();
                std::unique_ptr <Locuinta> loc3 = std::make_unique<Apartament>(loc2);
                other.adauga(std::move(loc3));
                gestiuneCastiguri.adaugaCastig(id,loc2.CalculChirie(1500,1));
            }
            return true;
        }
        return false;
    }

    friend std::istream& operator>>(std::istream& is, AgentieImobiliara& other)
    {
        int id;
        try
        {
            int numar;
            std::cout << "Introduceti id-ul clientului:";
            is>>id;
            std::cout << "Introduceti numarul de locuinte: ";
            is >> numar;
            if(typeid(numar)!=typeid(int))
                throw std::runtime_error("Incearca din nou!");
            else
                for (int i = 0; i < numar; i++)
                {
                    try
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
                            std::cout << "Introduceti discount-ul (%): ";
                            is >> discount;
                            std::unique_ptr<Locuinta> casa = std::make_unique<Casa>(numeClient, suprafataUtila, discount, suprafataCurte);
                            other.adauga(std::move(casa));
                        }
                        else
                            throw std::runtime_error("Alegere imposibila!");

                    }
                    catch (std::exception const &ex)
                    {
                        std::cerr << "Eroare: " << ex.what() << std::endl;
                    }
                }

        }
        catch (std::exception const &ex)
        {
            std::cerr << "Eroare: " << ex.what() << std::endl;
        }

        for (int i = 0; i < other.getNumar(); i++)
        {
            auto x=other.listaLocuinte[i]->CalculChirie(1500,1);
            gestiuneCastiguri.adaugaCastig(id,x);
        }
        return is;
    }
    ///afisarea datelor
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
            else if(typeid(*other.listaLocuinte[i])==typeid(Apartament))
            {
                Apartament* temp;
                temp = reinterpret_cast<Apartament*>(other.listaLocuinte[i].get());
                temp->Afisare();
            }
            out<<"Chiria este de "<<other.listaLocuinte[i]->CalculChirie(1500,1)<<std::endl;
            out<<std::endl;
        }
        return out;
    }
};

