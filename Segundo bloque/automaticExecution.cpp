#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <windows.h>

using namespace std;
using namespace this_thread; // Para usar sleep_for()
using namespace chrono; // Para usar seconds()

int main() {
    srand(time(nullptr)); // Inicializar el generador de numeros aleatorios
    int repeat = 1;
    
    while (repeat) {
        // Generar un numero aleatorio entre 0 y 3
        int programa = rand() % 4;

        cout << "\tMenu\n";
        cout << "1. Ejecutar Automata de pila\n";
        cout << "2. Ejecutar Backus-Naur condicional IF\n";
        cout << "3. Ejecutar Gramatica no ambigua\n";
        cout << "4. Ejecutar Maquina de Turing\n";
        cout << "Quiero ejecutar el programa: " << programa + 1 << "\n\n";
        sleep_for(seconds(2));
        
        if (programa == 0){
            cout << "Ejecutando stackAutomata.exe" << endl;
            SetCurrentDirectoryW(L"C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Segundo bloque/Programa 4");
            system("stackAutomata.exe");
        }
        else if (programa == 1){
            cout << "Ejecutando backusNaur.exe" << endl;
            SetCurrentDirectoryW(L"C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Segundo bloque/Programa 5");
            system("backusNaur.exe");
        }
        else if (programa == 2){
            cout << "Ejecutando unambiguousGram.exe" << endl;
            SetCurrentDirectoryW(L"C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Segundo bloque/Programa 6");
            system("unambiguousGram.exe");
        }
        else{
            cout << "Ejecutando turingMachine.exe" << endl;
            SetCurrentDirectoryW(L"C:/Users/diego/Documentos/ESCOM/Programas/Teoria de la computacion/Segundo bloque/Programa 7");
            system("turingMachine.exe");
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
