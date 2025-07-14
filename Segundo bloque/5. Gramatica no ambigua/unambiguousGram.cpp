/* Gramatica no ambigua:
B -> (RB | e
R -> ) | (RR
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread> // Para usar sleep_for()
#include <chrono> // Para usar seconds()
#include <sstream>

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

string request_string();
void grammar();
ofstream create_txt(string file_name);
void validate(string chain, vector<char> steps, ofstream &file);

int main(){
    grammar();
    return 0;
}

string request_string(){
    string chain, option;
    int op, n, random;  

    srand(time(NULL));

    do{
        cout << "1. Modo manual\n";
        cout << "2. Modo automatico\n";
        cout << "Seleccione una opcion: ";
        getline(cin, option);

        // Convertimos la opcion de string a entero
        stringstream ss(option);
        ss >> op;

        switch (op){
            case 1:
                cout << "Introduce una cadena a validar: ";
                getline(cin, chain);
                break;
            case 2:
                // Generamos la longitud de la cadena entre 1 y 1000
                n = 1 + rand() % 1000;
                cout << "\nLa cadena sera de " << n << " caracteres\n";
                for (int i = 0; i < n; i++){
                    random = rand() % 10;
                    if (i < (n / 2)){
                        // Se generan mas 0's que 1's en la primera mitad de la cadena
                        chain += (random < 8) ? "(" : ")";
                    }
                    else{
                        // Se generan mas 1's que 0's en la segunda mitad de la cadena
                        chain += (random < 8) ? ")" : "(";
                    }
                }
                
                cout << "La cadena generada es: " << chain << "\n\n";
                sleep_for(seconds(5));
                break;
            default:
                system("cls");
                cout << "Opcion no valida\n";
                cout << "Intente de nuevo\n";
                system("pause");
                system("cls");
                break;
        }
    }while (op != 1 && op != 2);

    return chain;
}

void grammar(){
    int not_valid = 0;
    string temp, chain = request_string();
    // Vector de pasos
    vector<char> steps = {'B'};
    ofstream file = create_txt("steps.txt");

    file << "Cadena a validar: " << chain << "\n\n";
    cout << "Cadena a validar: " << chain << "\n\n";
    file << "Paso 0:  B\n";
    cout << "Paso 0:  B\n";

    for (int i = 0; i <= chain.length(); i++){
        switch (chain[i]){
            case '(':
                // Si se lee un '(' y el ultimo paso fue 'B', reemplazamos 'B' por '(RB'
                if (steps[i] == 'B'){
                    temp = "(RB";
                    steps.erase(steps.begin() + i);
                    steps.insert(steps.begin() + i, temp.begin(), temp.end());
                }
                // Si se lee un '(' y el ultimo paso fue 'R', reemplazamos 'R' por '(RR'                
                else if (steps[i] == 'R'){
                    temp = "(RR";
                    steps.erase(steps.begin() + i);
                    steps.insert(steps.begin() + i, temp.begin(), temp.end());
                }
                else{
                    not_valid = 1;
                }
                break;
            case ')':
                // Si se lee un ')' y el ultimo paso fue 'R', reemplazamos 'R' por ')'
                if (steps[i] == 'R'){
                    temp = ")";
                    steps.erase(steps.begin() + i);
                    steps.insert(steps.begin() + i, temp.begin(), temp.end());
                }
                else{
                    not_valid = 1;
                }
                break;
            case '\0':
                // Si se llega al final de la cadena y el ultimo paso fue 'B', eliminamos 'B'
                if (steps[i] == 'B'){
                    steps.erase(steps.begin() + i);
                }
                else{
                    not_valid = 1;
                }
                break;
            default:
                cout << "Cadena no valida\n";
                exit(1);
        }
        file << "Paso " << i + 1 << ":  ";
        cout << "Paso " << i + 1 << ":  ";
        // Se imprime el vector en el paso actual
        for (char c : steps){
            file << c;
            cout << c;
        }
        file << "\n";
        cout << "\n";

        if (not_valid) break;
    }

    // Validamos si es una cadena valida
    validate(chain, steps, file);
    file.close();
}

void validate(string chain, vector<char> steps, ofstream &file){
    bool valid = true;
    // Debemos sacar el mayor para poder comparar en el bucle
    int mayor;
    if (chain.length() > steps.size()){
        mayor = chain.length();
    }
    else{
        mayor = steps.size();
    }

    // Comparamos el vector de pasos con la cadena
    for (int i = 0; i < mayor; i++){
        if (chain[i] != steps[i]){
            valid = false;
            break;
        }
    }

    if (valid){
        cout << "\nLa cadena \"" << chain << "\" es valida\n";
        file << "\nLa cadena \"" << chain << "\" es valida\n";
    }
    else{
        cout << "\nLa cadena \"" << chain << "\" no es valida\n";
        file << "\nLa cadena \"" << chain << "\" no es valida\n";
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