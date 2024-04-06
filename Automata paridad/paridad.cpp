#include <iostream>
#include <string>

using namespace std;

void initial_state();
void q0(string input, int &pos);
void q1(string input, int &pos);
void q2(string input, int &pos);
void q3(string input, int &pos);

int main(){

    initial_state();

    return 0;
}

void initial_state(){
    string input;
    int pos = 0;

    cout << "Ingrese la cadena a evaluar: ";
    cin >> input;

    cout << "switch case\n";
    string state = "q0";
    for (int i = 0; i < input.length() && state != "x"; i++){
    cout << "d(" << state << ", " << input[i] << ") --> ";
        switch (input[i]){
            case '0':
                if (state == "q0") state = "q2";
                else if (state == "q1") state = "q3";                
                else if (state == "q2") state = "q0";
                else if (state == "q3") state = "q1";
                break;
            case '1':
                if (state == "q0") state = "q1";
                else if (state == "q1") state = "q0";
                else if (state == "q2") state = "q3";
                else if (state == "q3") state = "q2";
                break;
            default:
                cout << "La cadena contiene caracteres invalidos" << endl;
                state = "x";
                break;
        }
        cout << "{" << state << "}\n";
    }
    if (state == "q0"){
        cout << "\nLa cadena es par";
    }
    else{
        cout << "\nLa cadena es impar";
    }
        
    cout << "\nFunciones\n";
    q0(input, pos);
}

void q0(string input, int &pos){
    cout << "Estado q0" << endl;
    if (input[pos] == '1'){
        q1(input, ++pos);
    }
    else if (input[pos] == '0'){
        q2(input, ++pos);
    }
    else if (!input[pos]){
        cout << "\nLa cadena es par";
    }
}

void q1(string input, int &pos){
    cout << "Estado q1" << endl;
    if (input[pos] == '1'){
        q0(input, ++pos);
    }
    else if (input[pos] == '0'){
        q3(input, ++pos);
    }
    else if (!input[pos]){
        cout << "\nLa cadena es impar";
    }
}

void q2(string input, int &pos){
    cout << "Estado q2" << endl;
    if (input[pos] == '1'){
        q3(input, ++pos);
    }
    else if (input[pos] == '0'){
        q0(input, ++pos);
    }
    else if (!input[pos]){
        cout << "\nLa cadena es impar";
    }
}

void q3(string input, int &pos){
    cout << "Estado q3" << endl;
    if (input[pos] == '1'){
        q2(input, ++pos);
    }
    else if (input[pos] == '0'){
        q1(input, ++pos);
    }
    else if (!input[pos]){
        cout << "\nLa cadena es impar";
    }
}