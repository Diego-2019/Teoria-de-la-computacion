#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <thread> // Para usar sleep_for()
#include <chrono> // Para usar seconds()
#define MAX 28

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

bool mode();
void alphabet_power(bool automatic, int &power);
void permutations(int power);
ofstream create_txt(string file_name);
void write_txt(ofstream &file, char letter);
void desicion(bool automatic, bool &repeat, int power);

int main(){
    int power;
    bool repeat = true, automatic;

    srand(time(NULL));

    automatic = mode();
    
    // Bucle para repetir el proceso
    do{
        alphabet_power(automatic, power);
        permutations(power);
        desicion(automatic, repeat, power);
    } while (repeat);
    
    return 0;
}

// Se establece el modo de ejecucion del programa
bool mode(){
    bool automatic;
    
    do{
        cout << "Desea que el programa se ejecute automaticamente? (1 = si, 0 = no): ";
        cin >> automatic;
        if (automatic > 1 || automatic < 0){
            cout << "Opcion invalida\n";
            system("pause");
            system("cls");
        }
    } while(automatic > 1 || automatic < 0);

    return automatic;
}

void alphabet_power(bool automatic, int &power){
    // Se establece el valor de la potencia en modo automatico
    if (automatic){
        power = 1 + rand() % (4); 
        cout << "\nEl valor de la potencia es: " << power << " ";
        for (int i = 0; i < 4; i++){
            sleep_for(seconds(1));
            cout << ".";
        }
    }
    // Se establece el valor de la potencia en modo manual
    else{
        do{
            system("cls");
            cout << "Ingrese el maximo valor de la potencia: ";
            cin >> power;

            if (power < 0 || power > MAX){
                cout << "No hay suficiente almacenamiento para ese valor\n";
                cout << "Debe ingresar una valor entre 0 y " << MAX << endl;
                system("pause");
            }
        } while (power < 0 || power > MAX);
    }
}

void permutations(int power){
    int string_count = 1;
    // Crear archivos de texto
    ofstream file = create_txt("permutaciones.txt");
    ofstream ocurrences = create_txt("ocurrencias.csv");

    // file << "{\u03B5"; // Unicode para el simbolo de vacio(epsilon)
    file << "{E"; // Reemplazo del simbolo de vacio(epsilon)

    ocurrences << "Cadena, OcurrenciaA\n";
    ocurrences << "0, 0\n";

    // Bucle para recorrer cada potencia
    for (int i = 1; i <= power; i++){
        // Bucle para recorrer cada permutacion
        for (int j = 0; j < pow(2, i); j++, string_count++){
            int a_count = 0;
            file << ", ";
            // Bucle para recorrer cada bit de la permutacion
            for (int num = j, bit = 0; num > 0 || bit < i; num = num >> 1, bit++){
                // Si el bit menos significativo es 1, se escribe 'b', de lo contrario 'a'
                if (num & 1){
                    write_txt(file, 'b');
                }
                else{
                    write_txt(file, 'a');
                    a_count++;
                }
            }
            ocurrences << string_count  << ", " << a_count << endl;
        }
        cout << "Potencia " << i << " completada\n";
    }
    file << "}\n";

    // Cerrar archivos
    file.close(); 
    ocurrences.close(); 
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

void write_txt(ofstream &file, char letter){
    // Escribe un caracter en el archivo
    file << letter;
}

void desicion(bool automatic, bool &repeat, int power){
    // Decicion automatica de repetir el proceso
    if (automatic){
        repeat = rand() % 2;
        if (!repeat){
            cout << "\nYa me canse de hacer calculos, no quiero hacer mas\n";
            sleep_for(seconds(2));
            cout << "Adios\n";
            sleep_for(seconds(1));
        }
        else{
            cout << "\nQuiero hacer otro calculo\n";
            sleep_for(seconds(2));
            cout << "Puedes abrir el archivo permutaciones.txt para ver los resultados\n";
            sleep_for(seconds(2));
            system("pause");
        }
    }
    // Decicion manual de repetir el proceso
    else{
        do{
            cout << "\nDesea hacer otro calculo? (1 = si, 0 = no): ";
            cin >> repeat;
            if (repeat > 1 || repeat < 0){
                cout << "Opcion invalida\n";
                system("pause");
                system("cls");
            }
        } while (repeat > 1 || repeat < 0);
    }
}