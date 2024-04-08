#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <windows.h>

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

int main() {
    srand(time(nullptr)); // Inicializar el generador de números aleatorios
    int repeat = 1;
    
    while (repeat) {
        int programa = rand() % 2; // Generar un número aleatorio: 0 o 1

        cout << "\tMenu\n";
        cout << "1. Ejecutar universo\n";
        cout << "2. Ejecutar buscador\n";
        cout << "Quiero ejecutar el programa: " << programa + 1 << "\n\n";
        sleep_for(seconds(2));
        
        if (programa == 0){
            cout << "Ejecutando universo.exe" << endl;
            SetCurrentDirectoryW(L"C:\\Users\\diego\\Documentos\\ESCOM\\Programas\\Teoria de la computacion\\Programa 1");
            system("universo.exe");
            // system("\"C:\\Users\\diego\\Documentos\\ESCOM\\Programas\\Teoria de la computacion\\Programa 1\\universo.exe\"");
        } 
        else{
            cout << "Ejecutando buscador.exe" << endl;
            SetCurrentDirectoryW(L"C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Programa 3");
            system("buscador.exe");
            // system("\"C:\\Users\\diego\\Documentos\\ESCOM\\Programas\\Teoria de la computacion\\Programa 3\\buscador.exe\"");
        }
        
        repeat = rand() % 2;

        if (repeat){
            cout << "volviendo al menu ";
            for (int i = 4; i > 0; i--){
                cout << ".";
                sleep_for(seconds(1));
            }
            system("cls"); 
        }
    }

    cout << "Fin del programa\n";
    sleep_for(seconds(5));
    system("cls");

    return 0;
}
