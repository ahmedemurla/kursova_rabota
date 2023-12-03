#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//Това е абстрактният клас за всички видове комп. техника//

class Tehnika
{
public:
	virtual void viewTehnika() = 0;
	virtual string accessData() = 0;

protected:
	string part;
	double price;
};

class Processor :public Tehnika
{
public:

	Processor(string name, double s, int c, double p, bool already_added = false)
	{
		part = name;
		speed = s;
		cores = c;
		price = p;

		if (!already_added)
		{
			processor_info.open(file_path, fstream::app);

			processor_info << part << '\t' << speed << '\t' << cores << '\t' << price;

			processor_info.close();
		}
	}

	~Processor() { };

	//Виртуалните методи//

	virtual void viewTehnika()
	{
		cout << right << part << setw(10) << speed << " GHz" << setw(10) << cores << " Cores" << setw(10) << price << " lv." << endl;
	}

	virtual string accessData()
	{
		return file_path;
	}

private:
	string part; double speed, price; int cores;
	string file_path = "d:\\data\\processor_info.txt";
	fstream processor_info;
};

class editTehnika
{
public:
	editTehnika() {};
	~editTehnika() {};

	void Add(Tehnika* object)
	{
		tech_list.push_back(object);
	}

	//Този метод позволява да се махне избрана от потребителя техника.//
	void Remove()
	{

		int choice;
		string line, file_path;
		vector <string> lines;
		fstream read_file;
		ofstream write_file;

		cout << "Kakvo iskash da mahnesh ot bazata za danni?" << endl;

		//Тука нареждаме всичките компоненти, които сме добавили чрез програмата.//

		for (int i = 0; i < tech_list.size(); i++)
		{
			cout << i + 1 << ". ";
			tech_list[i]->viewTehnika();
		}

		cin >> choice;
		choice--;

		//Тука махаме го от вектора, който ги съхранява.//

		file_path = tech_list[choice]->accessData();

		tech_list.erase(tech_list.begin() + (choice));

		/*А тази част е за да ги махмет от файла, на които са записани.
		Първо четем всеки ред и ги записваме в нов вектор.*/

		read_file.open(file_path);

		while (getline(read_file, line))
		{
			lines.push_back(line);
		}

		read_file.close();

		//После четем този нов вектор и записваме всичко, който не е този елемент, които току що махнаме, в файла пак.//

		write_file.open(file_path);

		for (int i = 0; i < lines.size(); i++)
		{
			if (i != choice)
			{
				write_file << lines[i] << endl;
			}
		}

		write_file.close();
	}

	//Нарежда всики добавени компоненти//

	void List()
	{
		for (int i = 0; i < tech_list.size(); i++)
		{
			cout << i + 1 << ". ";
			tech_list[i]->viewTehnika();
		}
	}
private:
	vector<Tehnika*> tech_list;
};

int main()
{
	//Това вмъква информацията записана на файл в програмата//

	string processor_data = "d:\\data\\processor_info.txt"; fstream read_file;
	editTehnika os;
	string line;
	read_file.open(processor_data);

	if (read_file.is_open())
	{
		while (!read_file.eof())
		{
			string name;
			double speed, price;
			int cores;

			getline(read_file, name, '\t');
			read_file >> speed >> cores >> price;

			os.Add(new Processor(name, speed, cores, price, true));
		}

		read_file.close();
	}

	while (true)
	{
		int choice;

		cout << "Kakvo iskash da napravish?" << endl;;
		cout << "1. Dobavi produkt.\n2. Mahni produkt\n3. Viz spisaka za produkti.\n";

		cin >> choice;

		if (choice == 1)
		{
			cout << "Kakiv produkt iskash da dobavish?" << endl;
			cout << "1. Processor\n";
			cin >> choice;
			cin.ignore();

			if (choice == 1)
			{
				string name;
				double speed, price;
				int cores;

				cout << "Ime: "; getline(cin, name);
				cout << "Skorost: "; cin >> speed;
				cout << "Yadra: "; cin >> cores;
				cout << "Cena: "; cin >> price;

				os.Add(new Processor(name, speed, cores, price));
			}
		}
		else if (choice == 2)
		{
			os.Remove();
		}

		else if (choice == 3)
		{
			os.List();
		}

		else if (choice == 0) break;
	}
}