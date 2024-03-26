#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

//kalsa pojazd zawiera model, marke oraz metody to wyswietlania pojazdow

class pojazd {
public:
	pojazd() {

	};

	pojazd(string ma, string mo) {
		marka = ma;
		model = mo;
	}
	virtual string getmarka() {
		return marka;
	}
	virtual string getmodel() {
		return model;
	}

	virtual string wyswietl() {
		string dowys;
		dowys.append(marka + " " + model + "\n");
		return dowys;
	}
protected:
	string marka;
	string model;
};

class osobowy : public pojazd {
public:
	osobowy(string ma,string mo,int poje) {
		marka = ma;
		model = mo;
		pojemnoscsilnika = poje;
	}
	string wyswietl() override {
		string dowys;
		dowys.append(marka + " " + model + " " + to_string(pojemnoscsilnika) + "\n");
		return dowys;
	}
private:
	double pojemnoscsilnika;
};


class motor : public pojazd {
public:
	motor(string ma, string mo, int prze) {
		marka = ma;
		model = mo;
		przebieg = prze;
	}
	string wyswietl() override {
		string dowys;
		dowys.append(marka+" "+ model + " "+ to_string(przebieg) + "\n");
		return dowys;
	}
private:
	int przebieg;
};

unique_ptr<pojazd> tworzenie(string co) {

	istringstream iss(co);
	vector<string> slowa;
	string slowo;
	while (getline(iss, slowo, ' ')) {
		slowa.push_back(slowo);
	}
	unique_ptr<pojazd> pojazd = make_unique<osobowy>(slowa[0], slowa[1], stod(slowa[2]));
	return pojazd;
}
unique_ptr<pojazd> tworzenieoso(string co) {

	istringstream iss(co);
	vector<string> slowa;
	string slowo;
	while (getline(iss, slowo, ' ')) {
		slowa.push_back(slowo);
	}
	unique_ptr<pojazd> pojazd = make_unique<osobowy>(slowa[0], slowa[1], stod(slowa[2]));
	return pojazd;
}
unique_ptr<pojazd> tworzeniemoto(string co) {

	istringstream iss(co);
	vector<string> slowa;
	string slowo;
	while (getline(iss, slowo, ' ')) {
		slowa.push_back(slowo);
	}
	unique_ptr<pojazd> pojazd = make_unique<motor>(slowa[0], slowa[1], stod(slowa[2]));
	return pojazd;
}


class bazadanych {
public:
	bazadanych() {
	}
	void dodaj(unique_ptr<pojazd> po) {
		pojazdy.push_back(move(po));
	}
	void usun(string marka,string model) {
		//wyszukujemy pojazdy ktore chcemy usunac przy pomocy remove_if a potem usuwamy za pomoca erase
		pojazdy.erase(remove_if(pojazdy.begin(), pojazdy.end(), [marka, model](const auto& pojazd)
			{return pojazd->getmarka() == marka && pojazd->getmodel() == model; }));

	}
	void zapis_do_pliku(string nazwa="C:\\Users\\User\\Documents\\Studia\\semestr7\\c++\\bazadanych\\plik.txt") {
		ofstream plik(nazwa);
		//plik.open(nazwa, ios::out | ios::binary);
		if (plik.is_open()) {
			string napis;
			for (const auto& pojazd : pojazdy) {
				//plik.write(const char * ( & pojazd), sizeof pojazd);
				//napis.append(pojazd->wyswietl());
				plik << pojazd->wyswietl();
			}
			//plik.write(reinterpret_cast<char*>( & napis), sizeof napis);
		}
		else {
			cout << "plik sie nie otworzyl \n";
		}
		plik.close();
	}
	void wczytaj_z_pliku(string nazwa = "C:\\Users\\User\\Documents\\Studia\\semestr7\\c++\\bazadanych\\dane.txt") {
		ifstream plik(nazwa);
		string co;

		if (plik.is_open()) {
			cout << "czytanie z pliku" << endl;
			while (getline(plik, co)) {
				pojazdy.push_back(move(tworzenie(co)));
			}

		}
		else {
			cout << "nie mozna otworzyc pliku" << endl;
		}
		
	}
	void wyszukaj(string marka, string model) { 
		for (const auto& pojazd : pojazdy) {
			if(pojazd->getmarka()==marka && pojazd->getmodel()==model)
			cout<<pojazd->wyswietl();
		}
	}
	void wyswietl() {
		for (const auto& pojazd : pojazdy) {
			cout<<pojazd->wyswietl();
			
		}
	}

private:
	vector<unique_ptr<pojazd>> pojazdy;
};




int main() {
	bazadanych baza;
	baza.dodaj(make_unique<osobowy>("Toyota", "Corolla", 4));
	baza.dodaj(make_unique<motor>("Honda", "CBR1000RR", 1000));

	baza.wyswietl();
	baza.wyszukaj("Toyota", "Corolla");
	baza.zapis_do_pliku();
	baza.wczytaj_z_pliku();
	baza.wyswietl();
	
	while (true) {
		string akcja;
		cout << "baza danych wpisz co chcesz zrobic" << endl;
		cout << "wp-wpisz do bazy" <<endl;
		cout << "us-usun z bazy" << endl;
		cout << "zp-zapisz baze do pliku" << endl;
		cout << "wc-wczytaj baze z pliku" << endl;
		cout << "wy-wyspisz baze daych" << endl;
		cin >> akcja;
		if (akcja == "wp") {
			cout << "jaki rodzaj pojazdu chcesz wykonac osobowy/motor" << endl;
			cin >> akcja;
			if (akcja == "osobowy") {
				cout << "wpisz marke model oraz pojemnosc silnika oddziel spacja" << endl;
				cin >> akcja;
				baza.dodaj(tworzenieoso(akcja));
			}
			else if(akcja == "motor") {
				cout << "wpisz marke model oraz pojemnosc silnika oddziel spacja" << endl;
				cin >> akcja;
				baza.dodaj(tworzenieoso(akcja));
			}
			else {
				cout << "zle wpisane dane"<<endl;
			}
		}
		if (akcja == "us") {
			cout << "wpisz jaka marke chcesz usunac potem kliknij enter nastepnie wpisz model" << endl;
			string model;
			cin >> akcja;
			cin >> model;
			baza.usun(akcja, model);
		}
		if (akcja == "zp") {
			cout << "wpisz do jakiego pliku chcesz zapisac plik" << endl;
			cin >> akcja;
			baza.zapis_do_pliku(akcja);
		}
		if (akcja=="wc") {
			cout << "wpisz z jakiego pliku chcesz wczytac dane" << endl;
			cin >> akcja;
			baza.wczytaj_z_pliku(akcja);
		}
		if (akcja == "wy") {
			cout << "*********************" << endl;
			baza.wyswietl();
			cout << "*********************" << endl;
		}
	}

	return 0;
}
