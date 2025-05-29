//Diego Alejandro Hidalgo Machaca
//Luigi Yamil Valenzuela Calderon

#include <iostream>
#include <vector>

class cMonedas
{
public:

	cMonedas(std::vector<int> in_vector) : monedas(in_vector) {}

	void get_monedas_diff()
	{
		int counter{ 0 }, suma{ 0 };

		for (int i = 0; i <= monedas.size() - 2; i++)
		{
			if (suma + monedas[i] >= monedas[i + 1]) //NO CUMPLE
				break;

			suma += monedas[i];
			counter++;
		}

		if (monedas.size() > 0)
			counter++;
		std::cout << "RESULTADO: " << counter << "\n";
	}

private:
	std::vector<int> monedas;
};

int main()
{
	cMonedas test(std::vector<int>({1, 3, 6, 8, 16, 32}));

	test.get_monedas_diff();
}