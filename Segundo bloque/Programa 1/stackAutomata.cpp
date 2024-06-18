#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <thread> // Para usar sleep_for()
#include <chrono> // Para usar seconds()

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

string request_string();
void transitions();
void validate(string chain, char state, int not_valid);
ofstream create_txt(string file_name);

int main(){
    transitions();
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

        stringstream ss(option);
        ss >> op;

        switch (op){
            case 1:
                cout << "Introduce una cadena a validar: ";
                getline(cin, chain);
                break;
            case 2:
                // Generamos la longitud de la cadena entre 1 y 100000
                n = 1 + rand() % 100000;
                cout << "\nLa cadena sera de " << n << " caracteres\n";
                for (int i = 0; i < n; i++){
                    random = rand() % 10;
                    if (i < (n / 2)){
                        // Se generan mas 0's que 1's en la primera mitad de la cadena
                        chain += (random < 9) ? "0" : "1";
                    }
                    else{
                        // Se generan mas 1's que 0's en la segunda mitad de la cadena
                        chain += (random < 9) ? "1" : "0";
                    }
                }
                
                cout << "La cadena generada es: " << chain << "\n\n";
                sleep_for(seconds(10));
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

void transitions(){
    ofstream file = create_txt("transitions.txt");
    stack<char> stack;
    string chain = request_string();
    char state = 'q';
    stack.push('Z');
    int not_valid = 0;

    // Bucle para recorrer la cadena
    for (int pos = 0; pos <= chain.length(); pos++){
        switch (chain[pos]){
            case '0':
                if (state == 'q' && stack.top() == 'Z'){
                    stack.push('X');
                    // Se escribe la transicion en el archivo
                    file << "d(q, 0, Z) = {(q, XZ)}\n";
                }
                else if (state == 'q' && stack.top() == 'X'){
                    stack.push('X');
                    //Se escribe la transicion en el archivo
                    file << "d(q, 0, X) = {(q, XX)}\n";
                }
                else {
                    not_valid = 1;
                }
                break;
            case '1':
                if (state == 'q' && stack.top() == 'X'){
                    state = 'p';
                    stack.pop();
                    // Se escribe la transicion en el archivo
                    file << "d(q, 1, X) = {(p, e)}\n";
                }
                else if (state == 'p' && stack.top() == 'X'){
                    stack.pop();
                    // Se escribe la transicion en el archivo
                    file << "d(p, 1, X) = {(p, e)}\n";
                    
                }
                else {
                    not_valid = 1;
                }
                break;
            case '\0':
                // Verificar el si la pila esta vacia al llegar al final de la cadena
                if (state == 'p' && stack.empty()){
                    not_valid = 1;
                }
                else if (state == 'p' && stack.top() == 'Z'){
                    state = 'f';
                    // Se escribe la transicion en el archivo
                    file << "d(p, e, Z)  {(f, Z)}\n";
                }
                break;
            default:
                not_valid = 1;
                break;
        }
        if (not_valid) break;
    }
    file.close();
    validate(chain, state, not_valid);

    if (chain.length() <= 10) system("python graficoSA.py");
}

void validate(string chain, char state, int not_valid){
    ofstream file = create_txt("animation.txt");
    file << chain << "\n";

    if (not_valid){
        cout << "La cadena \"" << chain << "\" no es valida\n";
        file << "La cadena \"" << chain << "\" no es valida\n";
    }
    else if (state == 'f'){
        cout << "La cadena \"" << chain << "\" es aceptada\n";
        file << "La cadena \"" << chain << "\" es aceptada\n";
    }
    else{
        cout << "La cadena \"" << chain << "\" no es aceptada\n";
        file << "La cadena \"" << chain << "\" no es aceptada\n";
    }
    file.close();
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