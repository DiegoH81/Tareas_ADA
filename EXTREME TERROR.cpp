//Diego Alejandro Hidalgo Machaca
//Luigi Yamil Valenzuela Calderon

#include <iostream>
#include <vector>


class cVuri_Shamsu
{
private:
    using pair_f_i = std::pair<float, int>;

    struct data
    {
        int vuri, shamsu, diff;

        data(double in_vuri, double in_shamsu) :
            vuri(in_vuri), shamsu(in_shamsu), diff(shamsu - vuri) {}
    };

    std::vector<data> vector;
    int n_business, n_avoid;

public:
    cVuri_Shamsu() :
        vector(), n_business(0), n_avoid(0) {}

    void ask_data()
    {

        std::cout << "\nquantity of business(N): ";
        std::cin >> n_business;

        std::cout << "quantity of business to avoid(K): ";
        std::cin >> n_avoid;

        for (int i = 0; i < n_business; i++)
        {
            int vuri{ 0 }, shamsu{ 0 };

            std::cout << "Negocio " << i << " VURI (X): ";
            std::cin >> vuri;

            std::cout << "Negocio " << i << " SHAMSU (Y): ";
            std::cin >> shamsu;

            vector.push_back(data(vuri, shamsu));
        }

    }

    void operate()
    {
        for (int i = 0; i < vector.size() - 1; i++)
            for (int j = 0; j < i; j++)
                if (vector[j].diff < vector[j + 1].diff)
                    std::swap(vector[j], vector[j + 1]);


        int suma{ 0 };

        for (int i = vector.size() - 1; i >= 0; i--)
        {
            if (vector[i].diff < 0 && n_avoid > 0)
            {
                n_avoid--;
                continue;
            }
                

            suma += vector[i].diff;
        }

        if (suma < 0)
            std::cout << "NO PROFIT!\n";
        else
            std::cout << "PROFIT: " << suma << "\n";

        vector.clear();
        n_business = n_avoid = 0;
    }
};


int main()
{
    cVuri_Shamsu test;
    int nTest;
    printf("test cases: ");
    std::cin >> nTest;
    for (int i = 0; i < nTest; i++) {
        test.ask_data();
        printf("\nCase %d: ", i + 1);
        test.operate();
    }
}
