/*
S -> iCtSA
A -> ;eS | epsilon
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int if_number();
ofstream create_txt(string file_name);
void pseudocode(vector<char> production);
void num_tabs(int tabs, string &spaces);
void grammar();
void derivations(vector<char> production, int &derivation, ofstream &file);

int main() {
    grammar();
    return 0;
}

int if_number(){
    int op, n;  

    srand(time(NULL));

    do{        
        cout << "1. Modo manual\n";
        cout << "2. Modo automatico\n";
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op){
            case 1:
                do{
                    cout << "\n\nIntroduce el numero de if's que quieres generar: ";
                    cin >> n;
                    if (n < 1 || n > 1000){
                        cout << "El numero debe estar entre 1 y 1000\n";
                        cout << "Intente de nuevo\n";
                        system("pause");
                        system("cls");
                    }
                } while (n < 1 || n > 1000);
                break;
            case 2:
                // Generamos el numero de if's entre 1 y 1000
                n = 1 + rand() % 1000;
                cout << "\nSe generaran " << n << " if's\n";                
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

    return n;
}

void grammar(){
    ofstream file = create_txt("derivations.txt");
    int if_num = if_number();
    int random, derivation = 1;
    string S = "iCtSA";
    string A = ";eS";
    vector<char> production = {'S'};

    file << "Derivaciones:\n\n";
    file << "0. S";

    do{
        for (int i = 0; i < production.size(); i++){
            switch(production[i]){
                case 'S':
                    if (if_num){
                        random = 1 + rand() % 10;
                        // Probabilidad de que se genere un if
                        if (random <= 5){
                            production.erase(production.begin() + i);
                            production.insert(production.begin() + i, S.begin(), S.end());
                            if_num--;
                            derivations(production, derivation, file);
                        }                        
                    }
                    break;
                case 'A':                
                    random = 1 + rand() % 10;
                    // Probabilidad de que se genere un else
                    if (random <= 7){
                        production.erase(production.begin() + i);
                        production.insert(production.begin() + i, A.begin(), A.end());
                    }
                    else production.erase(production.begin() + i);
                    derivations(production, derivation, file);
                    break;
            }            
        }
    } while (if_num); // Mientras no se hayan generado todos los if's se sigue generando la cadena

    // Escribimos el programa
    pseudocode(production);

    file.close();    
}

void derivations(vector<char> production, int &derivation, ofstream &file){
    // Escribimos las derivaciones
    file << endl << derivation << ". ";
    for (char c : production){
        file << c;
    }
    
    derivation++;
}

void pseudocode(vector<char> production){
    ofstream file = create_txt("pseudocode.txt");
    int tabs = 0;
    // Pila para manejar las identaciones
    stack<char> stack;
    bool anterior_else = false;
    string spaces;

    cout << "Cadena generada: ";
    file << "Cadena generada: ";
    for (char c : production){
        cout << c;
        file << c;
    }

    file << "\n\n";

    for (char c : production) {
        switch (c) {
            case 'i':
                tabs = stack.size();
                num_tabs(tabs, spaces);
                file << spaces << "if (condition) then\n";
                stack.push('I');
                break;
            case 'S':
                tabs = stack.size();
                num_tabs(tabs, spaces);
                file << spaces << "statement\n";
                if (!stack.empty() && stack.top() == 'E'){
                    stack.pop();
                }
                break;
            case ';':
                if (!stack.empty() && stack.top() == 'E'){
                    stack.pop();
                }
                stack.pop();
                tabs = stack.size();
                num_tabs(tabs, spaces);
                file << spaces << "else\n";
                stack.push('E');
                break;
        }
    }

    file.close();
}

void num_tabs(int tabs, string &spaces){
    spaces = "";
    for (int i = 0; i < tabs; i++){
        spaces += "\t";
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
    
    // system("cls");
    
    return file;
}