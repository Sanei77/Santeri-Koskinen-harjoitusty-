#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX_1HH = 100;
const int MAX_2HH = 100;
const int HINTA_1HH = 100;
const int HINTA_2HH = 150;

struct Varaus {
    int varausnumero;
    string nimi;
    int huonetyyppi; // 1: 1hh, 2: 2hh
    int yot;
    double loppusumma;
};

vector<bool> yhdenHengenHuoneet(MAX_1HH, false);
vector<bool> kahdenHengenHuoneet(MAX_2HH, false);
vector<Varaus> varaukset;

int generoiVarausnumero() {
    return rand() % 90000 + 10000;
}

bool tarkistaSaatavuus(int tyyppi) {
    if (tyyppi == 1) {
        return count(yhdenHengenHuoneet.begin(), yhdenHengenHuoneet.end(), false) > 0;
    }
    else if (tyyppi == 2) {
        return count(kahdenHengenHuoneet.begin(), kahdenHengenHuoneet.end(), false) > 0;
    }
    return false;
}

int varaaHuone(int tyyppi) {
    if (tyyppi == 1) {
        for (int i = 0; i < MAX_1HH; ++i) {
            if (!yhdenHengenHuoneet[i]) {
                yhdenHengenHuoneet[i] = true;
                return i + 1;
            }
        }
    }
    else if (tyyppi == 2) {
        for (int i = 0; i < MAX_2HH; ++i) {
            if (!kahdenHengenHuoneet[i]) {
                kahdenHengenHuoneet[i] = true;
                return MAX_1HH + i + 1;
            }
        }
    }
    return -1;
}

double laskeLoppusumma(int huonetyyppi, int yot) {
    double hinta = (huonetyyppi == 1 ? HINTA_1HH : HINTA_2HH) * yot;
    int alennusProsentti = (rand() % 3) * 10; // 0%, 10%, 20%
    return hinta * (1 - alennusProsentti / 100.0);
}

void teeVaraus() {
    string nimi;
    int tyyppi, yot;

    cout << "Anna varaajan nimi: ";
    cin.ignore();
    getline(cin, nimi);

    cout << "Valitse huonetyyppi (1: 1hh, 2: 2hh): ";
    cin >> tyyppi;
    if (tyyppi != 1 && tyyppi != 2) {
        cout << "Virheellinen valinta" << endl;
        return;
    }

    if (!tarkistaSaatavuus(tyyppi)) {
        cout << "Valitun tyypin huoneet ovat loppuun varattu" << endl;
        return;
    }

    cout << "Anna öiden määrä: ";
    cin >> yot;
    if (yot <= 0) {
        cout << "Virheellinen määrä öitä" << endl;
        return;
    }

    int huoneNro = varaaHuone(tyyppi);
    if (huoneNro == -1) {
        cout << "Huoneen varaaminen epäonnistui" << endl;
        return;
    }

    int varausnumero = generoiVarausnumero();
    double loppusumma = laskeLoppusumma(tyyppi, yot);

    varaukset.push_back({ varausnumero, nimi, tyyppi, yot, loppusumma });
    cout << "Varaus onnistui Varausnumero: " << varausnumero << ", Huone: " << huoneNro
        << ", Loppusumma: " << fixed << setprecision(2) << loppusumma << " euroa" << endl;
}

void haeVaraus() {
    int valinta;
    cout << "Hae varaus (1: Varausnumerolla, 2: Nimen perusteella): ";
    cin >> valinta;

    if (valinta == 1) {
        int numero;
        cout << "Anna varausnumero: ";
        cin >> numero;

        for (const auto& varaus : varaukset) {
            if (varaus.varausnumero == numero) {
                cout << "Varaus löytyi Nimi: " << varaus.nimi
                    << ", Huonetyyppi: " << (varaus.huonetyyppi == 1 ? "1hh" : "2hh")
                    << ", Yöt: " << varaus.yot
                    << ", Loppusumma majoittumiselle: " << fixed << setprecision(2) << varaus.loppusumma << " euroa" << endl;
                return;
            }
        }
        cout << "Varausta ei löytynyt." << endl;

    }
    else if (valinta == 2) {
        string nimi;
        cout << "Anna nimi: ";
        cin.ignore();
        getline(cin, nimi);

        for (const auto& varaus : varaukset) {
            if (varaus.nimi == nimi) {
                cout << "Varaus löytyi Varausnumero: " << varaus.varausnumero
                    << ", Huonetyyppi: " << (varaus.huonetyyppi == 1 ? "1hh" : "2hh")
                    << ", Yöt: " << varaus.yot
                    << ", Loppusumma majoittumiselle: " << fixed << setprecision(2) << varaus.loppusumma << " euroa" << endl;
                return;
            }
        }
        cout << "Varausta ei löytynyt." << endl;
    }
    else {
        cout << "Virheellinen valinta" << endl;
    }
}

int main() {
    srand(time(0));
    int valinta;

    do {
        cout << "\nHotellin varausjärjestelmä\n";
        cout << "1. Tee varaus\n";
        cout << "2. Hae varaus\n";
        cout << "3. Lopeta\n";
        cout << "Valitse toiminto: ";
        cin >> valinta;

        switch (valinta) {
        case 1:
            teeVaraus();
            break;
        case 2:
            haeVaraus();
            break;
        case 3:
            cout << "Ohjelma suljetaan" << endl;
            break;
        default:
            cout << "Virheellinen valinta" << endl;
        }
    } while (valinta != 3);

    return 0;
}
