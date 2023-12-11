#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <exception>
#include <stdlib.h> 

using namespace std;

bool checkIntException(int a, int begin_range, int end_range)
{
	bool passed = false;

	try
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			throw invalid_argument("Greshen vhod. Trqbva da e chislo");
		}
		else if (a > begin_range && a < end_range)
		{
			passed = true;
		}
		else
		{
			throw out_of_range("Greshen vhod. Chisloto trqbva da ot " + to_string(begin_range + 1) + " do " + to_string(end_range - 1));
		}
	}

	catch (const exception& e)
	{
		cerr << "Error: " << e.what() << endl;
		cout << "Natisni Enter za da prodiljish." << endl;
		cin.get();
		system("cls");
	}

	return passed;
}



class Tehnika
{
public:
	virtual void viewTehnika() = 0;
	virtual string accessData() = 0;
	virtual double getPrice() = 0;
	virtual vector<string> getDetails() = 0;

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

	virtual vector<string> getDetails()
	{
		vector<string> temp = { part, to_string(speed), to_string(cores) };

		return temp;
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

	virtual vector<string> getDetails()
	{
		vector<string> temp = { part, to_string(speed), to_string(memory) };

		return temp;
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

	virtual vector<string> getDetails()
	{
		vector<string> temp = { part, socket, chipset, memory_type, form_factor };

		return temp;
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


		while (true)
		{
			try
			{
				if (tech_list.empty())
				{
					throw invalid_argument("Nqma produkti za mahane.\n");
				}

				cout << "Kakvo iskash da mahnesh ot bazata za danni?" << endl;

				//Тука нареждаме всичките компоненти, които сме добавили чрез програмата.//

				for (int i = 0; i < tech_list.size(); i++)
				{
					cout << i + 1 << ". ";
					tech_list[i]->viewTehnika();
				}

				cout << "0. Nazad\n";


				cin >> choice;
				cin.ignore(10, '\n');

				if (choice == 0) break;

				else if (choice < -1 && choice > tech_list.size() + 1)
				{
					throw out_of_range("Chisloto trqbva da e ot " + to_string(0) + " do " + to_string(tech_list.size() + 1));
				}

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

				if (lines.size() > 1) lines.erase(lines.begin() + id);

				else lines.erase(lines.begin());

				for (int i = 0; i < lines.size(); i++)
				{
					write_file << lines[i] << endl;
				}


				lines.clear();
				write_file.close();
			}

			catch (const exception& e)
			{
				cerr << "Error: " << e.what() << endl;
				cout << "Natisni Enter za da prodiljish." << endl;
				cin.get();
				system("cls");
				break;
			}
		}
	}

	//Нарежда всики добавени компоненти//

	void List()
	{
		try
		{
			if (tech_list.empty())
			{
				throw invalid_argument("Nqma dobavena tehnika\n");
			}

			for (int i = 0; i < tech_list.size(); i++)
			{
				cout << i + 1 << ". ";
				tech_list[i]->viewTehnika();
			}
		}

		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
			cout << "Natisni Enter za da prodiljish." << endl;
			cin.get();
			system("cls");
		}
	}
private:
};

editTehnika fetch_data(editTehnika object)
{
	//Това вмъква информацията записана на файл в програмата//

	string processor_data = "d:\\data\\processor_info.txt"; string graphics_data = "d:\\data\\graphics_info.txt"; string mobo_data = "d:\\data\\mobo_info.txt";
	vector<string> data{ processor_data, graphics_data, mobo_data };

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

	Klienti(string name, string p, string e, string c)
	{
		id = nextId++;
		part = name;
		phone = p;
		email = e;
		city = c;

		int add = 0;
		string line;
		vector<string> lines;


		klienti_read.open(file_path);

		if (klienti_read.is_open())
		{
			while (getline(klienti_read, line))
			{
				lines.push_back(line);
			}

			add = lines.size();

			klienti_read.close();
		}

		klienti_write.open(file_path, fstream::app);

		klienti_write << id + add << ". " << part << '\t' << phone << '\t' << email << '\t' << city << endl;

		klienti_write.close();

	}

	~Klienti() { };

	void view()
	{
		cout << "Ime: " << part << '\t' << "Grad: " << city << '\t' << "Email: " << email << '\t' << "Telefon: " << phone << endl;
	}

	void viewKoshnitsa()
	{
		cout << "V koshnitsata ti ima: " << endl;

		for (int i = 0; i < koshnitsa.size(); i++)
		{
			cout << koshnitsa[i] << endl;
		}
	}

	int getId() const
	{
		return id;
	}

	vector<string> giveDetails()
	{
		vector <string> temp = { part, email, city, phone };

		return temp;
	}

private:
	int id;
	static int nextId;
	string part, phone, email, city;
	string file_path = "d:\\data\\klienti.txt";
	fstream klienti_read;
	fstream klienti_write;
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
		int size;
		bool passed = false;
		vector <Tehnika*> temp = object.tech_list;;

		while (true)
		{
			try
			{

				if (temp.empty())
				{
					throw invalid_argument("Nqma dobavena tehnika.\n");
				}

				while (!passed)
				{
					cout << "Predlagana tehnika: " << endl;

					object.List();

					cout << "0. Nazad\n";

					cin >> choice;
					size = temp.size();
					passed = checkIntException(choice, -1, size + 1);
				}

				passed = false;

				if (choice == 0)
				{
					system("cls");
					break;
				}

				system("cls");
				cout << "Tehnikata beshe dobavena v koshnitsta." << endl;
				cin.get();
				cin.ignore(5, '\n');
				system("cls");

				choice--;

				klient[0]->koshnitsa.push_back(temp[choice]);
			}

			catch (const exception& e)
			{
				cerr << "Error: " << e.what() << endl;
				cout << "Natisni Enter za da prodiljish." << endl;
				cin.get();
				system("cls");
				break;
			}
		}
	}

	void removeTehnika()
	{
		int choice;
		bool passed = false;
		vector <Tehnika*> temp = klient[0]->koshnitsa;

		while (true)
		{
			try
			{
				if (temp.empty())
				{
					throw invalid_argument("Nqma nishto v koshnitsata.");
				}

				int choice;

				while (!passed)
				{
					cout << "Kakvo iskate da mahnete ot koshnitsata vi?" << endl;

					for (int i = 0; i < temp.size(); i++)
					{
						cout << i + 1 << ". ";
						temp[i]->viewTehnika();
					}

					cout << "0. Nazad\n";

					cin >> choice;
					passed = checkIntException(choice, -1, temp.size() + 1);
				}

				passed = false;

				if (choice == 0)
				{
					system("cls");
					break;
				}

				system("cls");
				cout << "Tehnikata beshe premahnata ot koshnitsta." << endl;
				cin.get();
				system("cls");

				choice--;
				temp.erase(temp.begin() + choice);

				klient[0]->koshnitsa = temp;
			}

			catch (const exception& e)
			{
				cerr << "Error: " << e.what() << endl;
				cout << "Natisni Enter za da prodiljish." << endl;
				cin.get();
				system("cls");
				break;
			}
		}
	}

	void endOrder()
	{
		fstream saveOrder;
		saveOrder.open("d:\\data\\orders.txt", fstream::app);
		vector <Tehnika*> temp;
		vector <string> tehnika_details;
		vector <string> klient_details;
		double sum = 0;
		double add = 0;

		temp = klient[0]->koshnitsa;

		try
		{
			if (temp.empty())
			{
				throw invalid_argument("Nqma dobavena tehnika v koshnitsta.");
			}

			cout << "Porychkata vi beshe prikluchena.";

			klient_details = klient[0]->giveDetails();

			saveOrder << "<===============PORYCHKA===============>" << endl;;
			saveOrder << "Ime: " << klient_details[0] << "\tEmail: " << klient_details[1] << "\tGrad: " << klient_details[2] << "\tTelefon: " << klient_details[3] << endl;

			for (int i = 0; i < temp.size(); i++)
			{
				add = temp[i]->getPrice();
				sum += add;

				tehnika_details = temp[i]->getDetails();
				tehnika_details.push_back(to_string(add));

				saveOrder << i + 1 << ". ";

				for (int k = 0; k < tehnika_details.size(); k++)
				{
					if (k + 1 == tehnika_details.size()) saveOrder << tehnika_details[k] << endl;

					else saveOrder << tehnika_details[k] << '\t';
				}

			}

			saveOrder << "\nObshto: " << "\t" << sum << " lv.\n";
			saveOrder << "<======================================>" << "\n\n";

			cout << "Obshtata suma na porichkata vi e: " << sum << " lv." << endl;
			cin.get();
			system("cls");

			saveOrder.close();

			klient[0]->koshnitsa.clear();
		}
		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
			cout << "Natisni Enter za da prodiljish." << endl;
			cin.get();
			system("cls");
		}

	}

	void List()
	{
		vector <Tehnika*> temp = klient[0]->koshnitsa;

		try
		{
			if (temp.empty())
			{
				throw invalid_argument("Koshnitsata e prazna.");
			}

			cout << "Danni na klienta:\n";
			klient[0]->view();

			for (int i = 0; i < temp.size(); i++)
			{
				cout << i + 1 << ". ";
				temp[i]->viewTehnika();
			}

			cout << "\nNatisni Enter za da se virnesh obratno.\n";

			cin.get();
			system("cls");
		}

		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
			cout << "Natisni Enter za da prodiljish." << endl;
			cin.get();
			system("cls");
		}
	}

private:
	vector<Klienti*> klient;
};

int main()
{
	int izb;
	bool passed = false;
	editTehnika os;
	editKlienti editKl;
	os = fetch_data(os);
	while (true) {

		while (!passed)
		{
			cout << "<===============MAIN MENU===============>" << endl;
			cout << "1. Menu za klient\n2. Menu za razrabotchik\n3. Izlez ot programata\n";

			cin >> izb;
			cin.ignore(10, '\n');
			passed = checkIntException(izb, 0, 4);
		}

		passed = false;

		system("cls");

		if (izb == 1)
		{

			string name, email, city, string_phone;
			int phone;
			char zero = '0';

			cout << "Ime: "; getline(cin, name);
			cout << "Email: "; getline(cin, email);
			cout << "Grad: "; getline(cin, city);

			while (true)
			{
				try
				{
					cout << "Telefon: "; cin >> phone;
					string_phone = zero + to_string(phone);
					cin.ignore(10, '\n');

					system("cls");

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
						throw invalid_argument("Greshen vhod. Trqbva da e chislo");
					}
					else if (string_phone.size() != 10)
					{
						throw length_error("Greshen vhod. Nevaliden nomer");
					}
					else
					{
						break;
					}
				}

				catch (const exception& e)
				{
					cerr << "Error: " << e.what() << endl;
					cout << "Natisni Enter za da prodiljish." << endl;
					cin.get();
					system("cls");
				}
			}


			editKl.addClient(new Klienti(name, string_phone, email, city));

			int choiceKl;

			while (true)
			{
				while (!passed)
				{

					cout << "<===============CLIENT MENU===============>" << endl;
					cout << "1. Izberi produkt.\n2. Mahni produkt\n3. Viz spisaka za produkti.\n4. Poruchai product.\n0. Nazad\n";

					cin >> choiceKl;
					cin.ignore(10, '\n');
					passed = checkIntException(choiceKl, -1, 5);
				}

				passed = false;

				system("cls");

				if (choiceKl == 0)
				{
					break;
				}
				else if (choiceKl == 4)
				{
					editKl.endOrder();
				}
				else if (choiceKl == 3)
				{
					editKl.List();
				}
				else if (choiceKl == 2)
				{
					editKl.removeTehnika();
				}
				else if (choiceKl == 1)
				{
					editKl.addKoshnitsa(os);
				}

			}
		}
		if (izb == 2) {
			int choiceDev;
			while (true) {
				cout << "<===============DEVELOPER MENU===============>" << endl;
				cout << "1. Dobavi produkt.\n2. Mahni produkt\n3. Viz spisaka za produkti.\n0. Nazad\n";


				while (!passed)
				{
					cin >> choiceDev;
					cin.ignore(10, '\n');
					passed = checkIntException(choiceDev, -1, 4);
				}

				passed = false;

				if (choiceDev == 1) {
					while (true)
					{
						int choice;
						cout << "Kakiv produkt iskash da dobavish?" << endl;
						cout << "1. Processor\n2. Video karta\n3. Dunna platka\n0. Nazad\n";

						while (!passed)
						{
							cin >> choice;
							cin.ignore(10, '\n');
							passed = checkIntException(choice, -1, 4);
						}

						passed = false;

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
						else if (choice == 0) break;
					}

				}
				else if (choiceDev == 2) {
					os.Remove();
				}
				else if (choiceDev == 3) {
					os.List();
				}
				else if (choiceDev == 0) {
					break;
				}
			}
		}
		if (izb == 3) {
			break;
		}
	}
}