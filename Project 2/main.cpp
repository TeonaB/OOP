#include <vector>
#include "header.h"
///Tema 7
using namespace std;
int main()
{
    AgentieImobiliara agentie;
    int nr;
    while (true)
    {
        cout << "Alegeti ce doriti sa faceti:" << endl;
        cout << "1. Adauga o locuinta" << endl;
        cout << "2. Afiseaza toate locuintele cu chiriile acestora " << endl;
        cout << "3. Final" << endl;
        try
        {
            cin >> nr;
            if(nr!=3&&nr!=1&&nr!=2)
                throw std::runtime_error("Nu exista aceasta optiune!");
            switch (nr)
            {
            case 1:
            {
                cin>>agentie;
                break;
            }
            case 2:
            {
                int nr2 = agentie.getNumar();
                if (nr2 == 0)
                {
                    cout << "Nu este nimic de afisat" << endl;
                }
                else
                {
                    cout << "Agentia are urmatoarele locuinte:" << endl;
                    cout << agentie;
                    cout<<endl<<endl<<endl;
                }
                break;
            }
            case 3:
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
