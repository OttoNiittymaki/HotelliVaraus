//kusinen hotellivaraus softa

#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <random>
#include <vector>
#include <ctime>
#include <map>
#include <string>
#include <sstream>

using namespace std;




// P��ohjelma - Koitin kikkailla aliohjelmilla mutta ei toiminut, fuck it.

int main() {
	setlocale(LC_ALL, "FI_fi");


	

	// Arvotaan huoneiden lukum��r� sek� y�iden hinta. Se tehd��n t�ss� jottei tule uusia arvoja joka kerta jossain aliohjelman loopissa.

	// T�ss� satunnaislukugeneraattorin alustaminen
	srand(time(0));

	// Satunnaisluvun generointi ja m��ritys muuttujaan

	int huonemaara = rand() % 41 + 30; //V�lilt� 30-70
	int huonehinta = rand() % 21 + 80; //V�litl� 80-100


	//M��ritet��n huoneet vektori, jota k�yt�mme huoneiden arpomiseen ja varaamiseen
	vector<bool> huoneet(huonemaara, false);

	//Varaukset map on itse database jossa varaukset el�v�t, key INT on varausnumero ja value STRING on iso litania tavaraa joka m��ritell��n my�hemmin
	map<int, string> varaukset;


	bool poistu = true;

	while (poistu) {

		
		//Menun perusn�kym�
		cout << "\n" << "\n" << "Tervetuloa Hotelli Jaloviinaan! Valitse alta mit� haluat tehd�. " << "\n";
		cout << "\n" << "(1): Varaa huone";
		cout << "\n" << "(2): Tarkista varaus" << "\n";
		cout << "(Kirjoita 0 jos haluat poistua)" << "\n";

		//Muuttujien m��rittely
		int menuvalinta;
		cin >> menuvalinta;

		string nimi;


		
		switch (menuvalinta) {



		//Case 1 eli huonevaraus - Yritin tehd� ensin aliohjelmana mutta muuttujien kanssa leikkiminen ei toiminut. Joten suoraan perkele switchiss� vaan.

		case 1:

			//Alussa perus coutit ja otetaan talteen tiedot

			cout << "\nHuonehinta on: " << huonehinta << " euroa";

			cout << "\n" << "Mill� nimell� varaamme huoneen?" << "\n";

			cin >> nimi;
			cout << "\n" << "Mink� kokoisen huoneen haluat?" << "\n";
			cout << "(1): 1 hengen huone" << "\n";
			cout << "(2): 2 hengen huone" << "\n";


			int huonekoko;

			//Checkataan input huonekokoon

			while (true) {
				cin >> huonekoko;

				if (cin.fail()) {
					cout << "Yrit� uudestaan, sy�t� joko 1 tai 2\n";
					cin.clear();
					cin.ignore(80);
					continue;
				}

				if (huonekoko == 1 || huonekoko == 2) {
					break;
				}

				cout << "V��r� huonekoko, sy�t� joko 1 tai 2: \n";
			}

			//Sama �iden m��r��n

			cout << "\nKuinka monta y�t�? \n";

			int y�t;

			while (true) {
				cin >> y�t;

				if (cin.fail()) {
					cout << "Yrit� uudestaan, sy�t� �iden m��r� numeroina\n";
					cin.clear();
					cin.ignore(80);
					continue;
				}

				if (y�t > 0) {
					break;
				}

				cout << "Sy�t� �iden m��r� uudestaan:  \n";
			}



			// Huoneen numeron arpominen ja varaus

			while (true) {

				// Arvotaan huone

				int huonevalinta = rand() % huoneet.size(); //Huoneet vektorin koon perusteella arvotaan huonenumero
				int kokokustannus = y�t * huonehinta; //Lasketaan jo t�ss� kokokustannus yksinkertaisesti

				

				//Tarkistetaan onko huone vapaana, jos ei niin arvotaan uudestaan. 

				if (huoneet[huonevalinta] = 0 || huonevalinta == 0) {
					
					continue;
				}
				else {

					//Kun todetaan ett� huone vapaana, arvotaan ensin varausnumero (en jaksanut tehd� tarkistusta t�h�n ett� onko varausnumero jo varattu koska niin iso numero range, ep�todenn�k�ist� osua samaan, kello on liikaa siihen lol)

					int varausnumero = rand() % 89999 + 10000;
					
					//Perus coutit jossa kerrotaan varauksen tiedot

					cout << "\nHuoneesi on nyt varattu! Huoneesi numero on: " << huonevalinta << "\n";
					cout << "Varausnumerosi on: " << varausnumero << " ja varaus on tehty nimell�: " << nimi << "\n";
					cout << "Kokonaiskustannus: " << kokokustannus << " euroa \n";

					//Muutetaan vektorin arvo 0 jotta se tiet�� ett� huone on varattu

					huoneet[huonevalinta] = 0;

					//T�ss� muutetaan kaikki varaustiedot yhteen stringiin joka laitetaan MAP tyyppiseen databaseen. N�in saadaan varausnumero KEY:ll� kaikki tiedot suoraan.

					ostringstream oss;
					oss << "Nimi: " << nimi << "  Huone: " << huonevalinta << "  Hinta: " << kokokustannus << " euroa  Y�t: " << y�t;

					string varaustiedot = oss.str();

					//Laitetaan varaukset MAP:iin varausnumero KEYksi ja varaustiedot stringi arvoksi, my�hemp�� hakua varten. 

					varaukset.insert({ varausnumero, varaustiedot });
					

					break;
				}

			}


			
			break;
		

		//HAKU KOODIT

		case 2:

			//En keksinyt nyt miten saisi helposti nimell� haettua joten jos asiakas ei muista varausnumeroa onnea matkaan
			cout << "\nSy�t� varausnumerosi: ";
			int varausnumerohaku;
			cin >> varausnumerohaku;

			//T�ss� haetaan MAP:ista varausnumero avaimella pitk� string litania "varaustiedot" jonka m��rittelimme aiemmin.
			cout << "Varauksesi tiedot: \n";
			cout << varaukset.at(varausnumerohaku);


			break;



		default:
			cout << "Hyv�sti..";
		}


		if (menuvalinta == 0)
			poistu = false;
	}


	//K�yt� while lausekeetta booleanilla eli niin kauan kun TRUE niin py�rit� ohjelmaa, mutta kun k�ytt�j� 
	// painaa jotain n�pp�int� break loop

	return 0;
}




