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
ofstream create_txt(string file_name);
void transitions();
void validate(string chain, char state, ofstream &file);

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

        // Convertimos option de string a entero
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
                        chain += (random < 9) ? "0" : "1";
                    }
                    else{
                        // Se generan mas 1's que 0's en la segunda mitad de la cadena
                        chain += (random < 9) ? "1" : "0";
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

void transitions(){
    ofstream file = create_txt("IDs.txt");
    ofstream anim = create_txt("animationTM.txt");
    string chain = request_string();
    anim << chain << endl;
    // estados: q0 -> A, q1 -> B, q2 -> C, q3 -> D, q4 -> E
    char state = 'A';
    int not_valid = 0, direction = 1; // 1 = Derecha, -1 = Izquierda
    // Creamos un vector para facilitar las descripciones instantaneas
    vector<char> IDs(chain.begin(), chain.end());
    IDs.insert(IDs.begin(), state);
    for (char c : IDs){
        file << c;
    }

    for (int i = 0; i <= chain.length(); i += direction){
        switch (chain[i]){
            case '0':
                if (state == 'A'){
                    state = 'B';
                    chain[i] = 'X';
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs[i + 1] = 'X';
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else if (state == 'B'){
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);  
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }                  
                }
                else if (state == 'C'){
                    direction = -1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else {
                    not_valid = 1;
                }
                break;
            case '1':
                if (state == 'B'){
                    state = 'C';
                    chain[i] = 'Y';
                    direction = -1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs[i + 1] = 'Y';
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else {
                    not_valid = 1;
                }
                break;
            case 'X':
                if (state == 'C'){
                    state = 'A';
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else {
                    not_valid = 1;
                }
                break;
            case 'Y':
                if (state == 'A'){
                    state = 'D';
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }                    
                }
                else if (state == 'B'){
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }                    
                }
                else if (state == 'C'){
                    direction = -1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else if (state == 'D'){
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.insert(IDs.begin() + (i + direction), state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else {
                    not_valid = 1;
                }
                break;
            case '\0':
                if (state == 'D'){
                    state = 'E';
                    direction = 1;
                    // Modificamos el vector de IDs para la descripcion instantanea
                    IDs.erase(IDs.begin() + i);
                    IDs.push_back(state);
                    // Escritura en el archivo
                    file << u8" ⊦ ";
                    for (char c : IDs){
                        file << c;
                    }
                }
                else {
                    not_valid = 1;
                }
                break;
            default:
                not_valid = 1;
                break;
        }
        if (not_valid) break;
    }

    file.close();
    validate(chain, state, anim);
    anim.close();

    if (chain.length() <= 16) system("python TM_animation.py");
}

void validate(string chain, char state, ofstream &file){
    if (state == 'E'){
        cout << "\n\nLa cadena es valida\n";
        file << "La cadena es valida";
    }
    else{
        cout << "\n\nLa cadena no es valida\n";
        file << "La cadena no es valida";
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