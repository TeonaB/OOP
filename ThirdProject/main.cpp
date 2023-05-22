#include <vector>
#include "header.h"
///Tema 7
using namespace std;
int main()
{
    AgentieImobiliara agentie;
    char nr;
    while (true)
    {
        cout << "Alegeti ce doriti sa faceti:" << endl;
        cout << "1. Adauga o locuinta" << endl;
        cout << "2. Afiseaza toti clientii cu chiriile acestora " << endl;
        cout << "3. Afiseaza castigul lunar pentru agentie" <<endl;
        cout << "4. Final" << endl;
        try
        {
            cin >> nr;
            if(nr!='3'&&nr!='1'&&nr!='2'&&nr!='4')
                throw std::runtime_error("Nu exista aceasta optiune!");
            switch (nr)
            {
            case '1':
            {
                bool ok=agentie.adaugaAlegere(agentie);
                if(ok==false)
                    cin>>agentie;
                break;
            }
            case '2':
            {
                int nr2 = agentie.getNumar();
                if (nr2 == 0)
                {
                    cout << "Nu este nimic de afisat" << endl;
                }
                else
                {
                    cout <<"Agentia are urmatoarele locuinte:" << endl;
                    cout << agentie;
                    cout<<endl<<endl<<endl;
                }
                break;
            }
            case '3':
            {
                gestiuneCastiguri.afiseazaCastiguri();
                break;
            }
            case '4':
            {
                cout<<"Programul se va inchide";
                return 0;
            }

            }
        }
        catch (std::exception const &ex)
        {
            std::cerr << "Eroare: " << ex.what() << std::endl;
        }

    }

    return 0;
}
