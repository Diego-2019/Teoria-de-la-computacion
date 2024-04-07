#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <map>
#include <thread> // Para usar sleep_for()
#include <chrono> // Para usar seconds()

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

struct coordinates{
    int paragraph, wordNumber;
};

// mapa de palabras y sus posiciones
using Map = map<string, vector<coordinates>>;

void preparation();
ofstream create_txt(string file_name);
void searcher(int &paragraph, string line, Map &positions, ofstream &process, char &state);
void check_word(char state, int paragraph, int wordNumber, Map &positions);
void results(Map positions);
void graph_dfa();

int main(){
    char repeat;
    do{
        preparation();
        graph_dfa();
        do{
            cout << "Desea repetir el programa? (s/n): ";
            cin >> repeat;
            repeat = tolower(repeat);
            if (repeat != 's' && repeat != 'n'){
                cout << "Opcion no valida\n";
                cout << "Intente de nuevo\n";
            }
        } while (repeat != 's' && repeat != 'n');
        sleep_for(seconds(1));
        system("cls");
    } while (repeat == 's');
    return 0;
}

void preparation(){
    system("python html_txt.py");
    ifstream file("texto.txt");
    string line;
    char state = 'A';
    int paragraph = 0;
    ofstream process = create_txt("proceso.txt");
    Map positions = {
        {"feminal", {}},
        {"feminazi", {}},
        {"feminista", {}},
        {"tonta", {}},
        {"torta", {}},
        {"vieja", {}}
    };
    
    if(file.is_open()){
        while(getline(file, line)){
            if(!line.empty()){
                paragraph++;
                // Llamar a la funcion searcher(...)
                searcher(paragraph, line, positions, process, state);
            }
        }
        file.close();
        process.close();
        // Llamar a la funcion results(...)
        results(positions);
    }
    else{
        cout << "No se pudo abrir el archivo" << endl;
    }
}

void searcher(int &paragraph, string line, Map &positions, ofstream &process, char &state){
    char enie = 165;
    int pos = 0, wordNumber = 1;
    // Bucle para recorrer el parrafo
    while (line[pos]){
        process << "d(" << state << ", " << line[pos] << ") --> ";
        // switch case del automata
        switch (tolower(line[pos])){
            //! Transiciones al leer una 'f'
            case 'f':
                state = 'B';
                break;
            //! Transiciones al leer una 'e'
            case 'e':
                if (state == 'B') state = 'E';
                else if (state == 'G') state = 'K';
                else state = 'A';
                break;
            //! Transiciones al leer una 'm'
            case 'm':
                if (state == 'E') state = 'H';
                else state = 'A';
                break;
            //! Transiciones al leer una 'i'
            case 'i':
                if (state == 'D') state = 'G';
                else if (state == 'H') state = 'L';
                else if (state == 'M') state = enie;
                else if (state == 'Q') state = 'S';
                else state = 'A';
                break;
            //! Transiciones al leer una 'n'
            case 'n':
                if (state == 'F') state = 'I';
                else if (state == 'L') state = 'M';
                else state = 'A';
                break;
            //! Transiciones al leer una 'a'
            case 'a':
                if (state == 'M') state = 'O';
                else if (state == 'N') state = 'T';
                else if (state == 'U') state = 'X';
                else if (state == 'V') state = 'Y';
                else if (state == 'W') state = 'Z';
                else state = 'A';
                break;
            //! Transiciones al leer una 'l'
            case 'l':
                if (state == 'O') state = 'R';
                else state = 'A';
                break;
            //! Transiciones al leer una 'z'
            case 'z':
                if (state == 'O') state = 'Q';
                else state = 'A';
                break;
            //! Transiciones al leer una 's'
            case 's':
                if (state == enie) state = 'P';
                else state = 'A';
                break;
            //! Transiciones al leer una 't'
            case 't':
                if (state == 'I') state = 'V';
                else if (state == 'J') state = 'W';
                else if (state == 'P') state = 'U';
                else state = 'C';
                break;
            //! Transiciones al leer una 'o'
            case 'o':
                if (state == 'C' || state == 'U' || state == 'V' || state == 'W') state = 'F';
                else state = 'A';                
                break;
            //! Transiciones al leer una 'r'
            case 'r':
                if (state == 'F') state = 'J';
                else state = 'A';
                break;
            //! Transiciones al leer una 'v'
            case 'v':
                state = 'D';
                break;
            //! Transiciones al leer una 'j'
            case 'j':
                if (state == 'K') state = 'N';
                else state = 'A';
                break;
            default:
                if (isspace(line[pos])) wordNumber++;
                state = 'A';
                break;
        }
        process << "{" << state << "}\n";
        // Llamar a la funcion check_word(...)
        check_word(state, paragraph, wordNumber, positions);
        pos++;
    }
}

void check_word(char state, int paragraph, int wordNumber, Map &positions){
    switch (state){
        // Estado final de la palabra 'feminal'
        case 'R':
            positions["feminal"].push_back({paragraph, wordNumber});
            break;
        // Estado final de la palabra 'feminazi'
        case 'S':
            positions["feminazi"].push_back({paragraph, wordNumber});
            break;
        // Estado final de la palabra 'vieja'
        case 'T':
            positions["vieja"].push_back({paragraph, wordNumber});
            break;
        // Estado final de la palabra 'feminista'
        case 'X':
            positions["feminista"].push_back({paragraph, wordNumber});
            break;
        // Estado final de la palabra 'tonta'
        case 'Y':
            positions["tonta"].push_back({paragraph, wordNumber});
            break;
        // Estado final de la palabra 'torta'
        case 'Z':
            positions["torta"].push_back({paragraph, wordNumber});
            break;
    }
}

void results(Map positions){
    // element tomará el valor de cada elemento del mapa (clave, valor)
    for (auto element : positions){
        cout << "Se encontraron " << element.second.size() << " ocurrencias de la palabra '" << element.first << "'\n";
        // positions tomará el valor de cada elemento del vector
        for (auto positions : element.second){
            cout << "En el parrafo " << positions.paragraph << " es la palabra numero " << positions.wordNumber << endl;
        }
        cout << endl;
    }
}

ofstream create_txt(string file_name){
    ofstream file;
    bool retry = false;
    int intentos = 3;

    //Bucle para intentar abrir el archivo
    do{
        // Si ya existe el archivo, se sobreescribe
        file.open(file_name, ios::out);
        if (file.fail()){
            cout << "No se pudo abrir el archivo\n";
            cout << "Reintentando...\n";
            system("pause");
            retry = true;
            intentos--;
        }
        if (!intentos){
            system("cls");
            cout << "No se pudo abrir el archivo\n";
            cout << "Adios\n";
            exit(1);
        }
    } while (retry);

    system("cls");

    return file;
}

void graph_dfa(){
    char op;
    do{
        cout << "\n\nDesea ver el diagrama del automata? (s/n): ";
        cin >> op;
        op = tolower(op);
        if (op != 's' && op != 'n'){
            cout << "Opcion no valida\n";
            cout << "Intente de nuevo\n";
        }
    } while (op != 's' && op != 'n');

    if (op == 's'){
        system("python automata.py");
    }
}