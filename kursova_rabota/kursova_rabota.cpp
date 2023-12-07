#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;


class Tehnika
{
public:
	virtual void viewTehnika() = 0;
	virtual string accessData() = 0;
	virtual double getPrice() = 0;

	int getId() const
	{
		return id;
	}

protected:
	int id;
	string part;
	double price;
};

class Processor :public Tehnika
{
public:

	Processor(string name, double s, int c, double p, bool already_added = false)
	{
		id = nextId++;
		part = name;
		speed = s;
		cores = c;
		price = p;

		if (!already_added)
		{
			processor_info.open(file_path, fstream::app);

			processor_info << part << '\t' << speed << '\t' << cores << '\t' << price << endl;

			processor_info.close();
		}
	}

	~Processor() { };

	//Виртуалните методи//

	virtual void viewTehnika()
	{
		cout << right << setw(6) << part << setw(6) << speed << " GHz" << setw(6) << cores << " Cores" << setw(6) << price << " lv." << endl;
	}

	virtual string accessData()
	{
		return file_path;
	}

	virtual double getPrice()
	{
		return price;
	}

private:
	static int nextId;
	string part; double speed, price; int cores;
	string file_path = "d:\\data\\processor_info.txt";
	fstream processor_info;
};

int Processor::nextId = 1;

class GraphicsCard :public Tehnika
{
public:

	GraphicsCard(string name, double s, int m, double p, bool already_added = false)
	{
		id = nextId++;
		part = name;
		speed = s;
		memory = m;
		price = p;

		if (!already_added)
		{
			graphics_info.open(file_path, fstream::app);

			graphics_info << part << '\t' << speed << '\t' << memory << '\t' << price << endl;

			graphics_info.close();
		}
	}

	~GraphicsCard() { };

	virtual void viewTehnika()
	{
		cout << right << part << setw(10) << speed << " GHz" << setw(8) << memory << " GB" << setw(8) << price << " lv." << endl;
	}

	virtual string accessData()
	{
		return file_path;
	}

	virtual double getPrice()
	{
		return price;
	}


private:
	static int nextId;
	string part; double speed, price; int memory;
	string file_path = "d:\\data\\graphics_info.txt";
	fstream graphics_info;
};

int GraphicsCard::nextId = 1;

class Motherboard :public Tehnika
{
public:

	Motherboard(string name, string s, string c, string m, string f, double p, bool already_added = false)
	{
		id = nextId++;
		part = name;
		socket = s;
		chipset = c;
		memory_type = m;
		form_factor = f;
		price = p;

		if (!already_added)
		{
			mobo_info.open(file_path, fstream::app);

			mobo_info << part << '\t' << socket << '\t' << chipset << '\t' << memory_type << '\t' << form_factor << '\t' << price << endl;

			mobo_info.close();
		}
	}

	~Motherboard() { };

	virtual void viewTehnika()
	{
		cout << right << part << setw(12) << socket << " Socket" << setw(12) << chipset << " Chipset" << setw(12) << memory_type << " Memory" << setw(12) << "Size: " << form_factor << setw(12) << price << " lv." << endl;
	}

	virtual string accessData()
	{
		return file_path;
	}

	virtual double getPrice()
	{
		return price;
	}


private:
	static int nextId;
	string part, socket, chipset, memory_type, form_factor;
	double price;
	string file_path = "d:\\data\\mobo_info.txt";
	fstream mobo_info;
};

int Motherboard::nextId = 1;

class editTehnika
{
public:
	vector<Tehnika*> tech_list;

	editTehnika() {};
	~editTehnika() {};

	void Add(Tehnika* object)
	{
		tech_list.push_back(object);
	}

	//Този метод позволява да се махне избрана от потребителя техника.//
	void Remove()
	{

		int choice, id;
		string line, file_path;
		vector <string> lines;
		fstream read_file;
		ofstream write_file;

		if (tech_list.empty())
		{
			cout << "Nqma produkti za mahane." << endl;
		}

		else
		{
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
			id = tech_list[choice]->getId();
			id--;

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
				if (i != id)
				{
					write_file << lines[i] << endl;
				}
			}

			write_file.close();
		}

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
};

editTehnika fetch_data(editTehnika object)
{
	//Това вмъква информацията записана на файл в програмата//

	string processor_data = "d:\\data\\processor_info.txt"; string graphics_data = "d:\\data\\graphics_info.txt"; string mobo_data = "d:\\data\\mobo_info.txt";
	string psu_data = "d:\\data\\psu_info.txt"; string storage_data = "d:\\data\\storage_info.txt"; string memory_data = "d:\\data\\memory_info.txt";
	vector<string> data{ processor_data, graphics_data, mobo_data, psu_data, storage_data, memory_data };

	fstream read_file;

	for (int i = 0; i < data.size(); i++)
	{
		string name; double price;

		read_file.open(data[i]);

		if ((read_file.is_open()) && (i == 0))
		{
			while (!read_file.eof())
			{

				double speed;
				int cores;

				//Поради начина, по който съм правил трябва да се провери дали следващия ред е празен и ако е да се пропусне//

				getline(read_file, name, '\t');

				if (name == "") break;

				read_file >> speed >> cores >> price;
				read_file.ignore(10, '\n');

				object.Add(new Processor(name, speed, cores, price, true));
			}
		}

		else if ((read_file.is_open()) && (i == 1))
		{
			while (!read_file.eof())
			{
				double speed;
				int memory;

				getline(read_file, name, '\t');

				if (name == "") break;

				read_file >> speed >> memory >> price;
				read_file.ignore(10, '\n');

				object.Add(new GraphicsCard(name, speed, memory, price, true));
			}
		}
		else if ((read_file.is_open()) && (i == 2))
		{
			while (!read_file.eof())
			{
				string socket, chipset, memory_type, form_factor;

				getline(read_file, name, '\t');

				if (name == "") break;
				getline(read_file, socket, '\t');
				getline(read_file, chipset, '\t');
				getline(read_file, memory_type, '\t');
				getline(read_file, form_factor, '\t');
				read_file >> price;
				read_file.ignore(10, '\n');

				object.Add(new Motherboard(name, socket, chipset, memory_type, form_factor, price, true));
			}
		}

		read_file.close();
	}

	return object;
}

class Klienti
{
public:

	vector <Tehnika*> koshnitsa;

	Klienti(string name, int p, string e, string c, bool already_added = false)
	{
		id = nextId++;
		part = name;
		phone = p;
		email = e;
		city = c;

		if (!already_added)
		{
			Klienti_Info.open(file_path, fstream::app);

			Klienti_Info << part << '\t' << phone << '\t' << email << '\t' << city << endl;

			Klienti_Info.close();
		}
	}

	~Klienti() { };

	void view()
	{
		cout << "Name: " << part << '\t' << "Phone number: " << phone << '\t' << "Email: " << email << '\t' << "City: " << city << endl;
	}

	void viewKoshnitsa()
	{
		cout << "V koshnitsata ti ima: " << endl;

		for (int i = 0; i < koshnitsa.size(); i++)
		{
			cout << koshnitsa[i] << endl;
		}
	}

	string accessData()
	{
		return file_path;
	}

	int getId() const
	{
		return id;
	}

private:
	int id;
	static int nextId;
	string part; int phone; string email; string city;
	string file_path = "d:\\data\\klienti.txt";
	fstream Klienti_Info;
};

int Klienti::nextId = 1;

class editKlienti
{
public:
	editKlienti() {};
	~editKlienti() {};

	void addClient(Klienti* object)
	{
		klient.push_back(object);
	}

	void addKoshnitsa(editTehnika object)
	{
		int choice;
		vector <Tehnika*> temp;
		cout << "Predlagana tehnika: " << endl;

		object.List();

		cin >> choice;
		choice--;

		temp = object.tech_list;

		klient[0]->koshnitsa.push_back(temp[choice]);
	}

	void removeKlient()
	{
		klient.erase(klient.begin());
	}

	void removeTehnika()
	{
		int choice;

		cout << "Kakvo iskate da mahnete ot koshnitsata vi?" << endl;

		vector <Tehnika*> temp = klient[0]->koshnitsa;

		for (int i = 0; i < temp.size(); i++)
		{
			cout << i + 1 << ". ";
			temp[i]->viewTehnika();
		}

		cin >> choice;
		choice--;
		temp.erase(temp.begin() + choice);

		klient[0]->koshnitsa = temp;
	}

	void endOrder()
	{
		vector <Tehnika*> temp;
		double sum = 0;

		temp = klient[0]->koshnitsa;

		cout << "Porychkata vi beshe prikluchena.";

		for (int i = 0; i < temp.size(); i++)
		{
			sum += temp[i]->getPrice();
		}

		cout << "Obshtata suma na porichkata vi e: " << sum << " lv." << endl;

		klient[0]->koshnitsa.clear();
	}

	void List()
	{
		vector <Tehnika*> temp = klient[0]->koshnitsa;

		cout << "Danni na klienta: ";
		klient[0]->view();

		for (int i = 0; i < temp.size(); i++)
		{
			cout << i + 1 << ". ";
			temp[i]->viewTehnika();
		}
	}

private:
	vector<Klienti*> klient;
};

int main()
{
	int izb;
	editTehnika os;
	editKlienti editKl;
	os = fetch_data(os);
	while (true) {
		cout << "<===============MAIN MENU===============>" << endl;
		cout << "1. Menu za klient\n2. Menu za razrabotchik\n3. Izhod\n";
		cin >> izb;
		cin.ignore(10, '\n');
		if (izb == 1)
		{

			string name, email, city;
			int phone;

			cout << "Name: "; getline(cin, name);
			cout << "Email: "; getline(cin, email);
			cout << "City: "; getline(cin, city);
			cout << "Phone number: "; cin >> phone;
			cin.ignore(10, '\n');

			editKl.addClient(new Klienti(name, phone, email, city));

			int choiceKl;
			while (true)
			{
				cout << "<===============CLIENT MENU===============>" << endl;
				cout << "1. Izberi produkt.\n2. Viz spisaka za produkti.\n3. Poruchai product.\n0. Izlez ot programata\n";
				cin >> choiceKl;
				if (choiceKl == 0)
				{
					break;
				}
				else if (choiceKl == 3)
				{
					editKl.endOrder();
				}
				else if (choiceKl == 2)
				{
					editKl.List();
				}
				else if (choiceKl == 1)
				{
					editKl.addKoshnitsa(os);
				}

			}
			break;
		}
		if (izb == 2) {
			int choiceDev;
			while (true) {
				cout << "<===============DEVELOPER MENU===============>" << endl;
				cout << "1. Dobavi produkt.\n2. Mahni produkt\n3. Viz spisaka za produkti.\n0. Izlez ot programata\n";
				cin >> choiceDev;
				if (choiceDev == 1) {
					int choice;
					cout << "Kakiv produkt iskash da dobavish?" << endl;
					cout << "1. Processor\n2.Video karta\n3.Dunna platka\n";
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
						cin.ignore();
						os.Add(new Processor(name, speed, cores, price));
					}
					else if (choice == 2)
					{
						string name;
						double speed, price;
						int memory;

						cout << "Ime: "; getline(cin, name);
						cout << "Skorost: "; cin >> speed;
						cout << "Pamet: "; cin >> memory;
						cout << "Cena: "; cin >> price;
						cin.ignore();
						os.Add(new GraphicsCard(name, speed, memory, price));
					}
					else if (choice == 3)
					{
						string name, socket, chipset, memory_type, form_factor;
						double price;

						cout << "Ime: "; getline(cin, name);
						cout << "Soket: "; getline(cin, socket);
						cout << "Chipset: "; getline(cin, chipset);
						cout << "Vid pamet: "; getline(cin, memory_type);
						cout << "Razmer: "; getline(cin, form_factor);
						cout << "Cena: "; cin >> price;
						cin.ignore();
						os.Add(new Motherboard(name, socket, chipset, memory_type, form_factor, price));
					}
				}
				if (choiceDev == 2) {
					os.Remove();
				}
				if (choiceDev == 3) {
					os.List();
				}
				if (choiceDev == 0) {
					break;
				}
				else {
					cout << "Nevaliden izbor. Molq opitaite otnovo.\n";
				}
			}
		}
		if (izb == 3) {
			break;
		}
	}
}