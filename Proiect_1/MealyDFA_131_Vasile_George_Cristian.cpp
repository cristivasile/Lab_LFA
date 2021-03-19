//Vasile George-Cristian
//Grupa 131

#include <iostream>

using namespace std;

struct tranzitie {
    string start, end, message;
    char lit='z';
};

bool exists(string v[], int n, string state) {  //functie care verifica daca o stare exista deja
    for (int i = 0; i < n; i++)
        if (v[i] == state)
            return 1;
    return 0;
}

int main()
{

    unsigned int n, aux;
    string def_state, x;
    string* final_state;
    tranzitie* transitions;
    string stack_afis[1001],stack_traseu[1001];
    unsigned int transitions_nr = 0, afis_top = 0, traseu_top = 0, final_states_nr = 0;

    cout << "Introduceti numarul de stari: ";
    cin >> n;

    string* states;
    states = new string[n];
    int state_nr = 0;


    cout << "Introduceti numarul de tranzitii: ";
    cin >> aux;

    transitions = new tranzitie[aux];


    string init, fin, mesaj;
    char lit;
    bool OK, OK1, OK2;

    cout << "Introduceti tranzitiile. Format: <string>stare_inceput <string>stare_destinatie <char>litera <string>mesaj: \n";
    for (int i = 0; i < aux; i++) {
        OK = 1;                 //se verifica daca exista deja o tranzitie de la nodul curent 
        OK1 = 0;                //se verifica daca starea de inceput nu exista inca
        OK2 = 0;                //se verifica daca starea in care mergem nu exista inca
        cout << "Se citeste tranzitia #" << i + 1 << ": ";
        cin >> init >> fin >> lit >> mesaj;
        if (exists(states, state_nr, init) == 0) {
            if (state_nr == n) {
                cout << "Prea multe stari! Reincercati! ";
                i--;
                continue;
            }
            else {
                OK1 = 1;                      //am adaugat starea de inceput in vectorul de stari
                states[state_nr++] = init;
            }
        }

        if (exists(states, state_nr, fin) == 0) {
            if (state_nr == n) {
                cout << "Prea multe stari! Reincercati! ";
                i--;
                if (OK1 == 1)                // daca am adaugat starea de inceput la acest pas si trebuie sa o stergem
                    state_nr--;
                continue;
            }
            else {
                OK2 = 1;                      //am adaugat starea in care mergem in vectorul de stari
                states[state_nr++] = fin;
            }
        }


        for (int j = 0; j < transitions_nr; j++)
            if (transitions[j].start == init && transitions[j].lit == lit)
                OK = 0;

        if (OK == 0) {
            if (OK1 == 1)     // daca am adaugat starea de inceput la acest pas si trebuie sa o stergem
                state_nr--;
            if (OK2 == 1)     // daca am adaugat starea in care mergem la acest pas si trebuie sa o stergem
                state_nr--;
            cout << "Exista deja o tranzitie cu aceasta litera din aceasta stare. Automatul Mealy trebuie sa fie DFA!\n";
            i--;
        }
        else {
            transitions[transitions_nr].start = init;
            transitions[transitions_nr].end = fin;
            transitions[transitions_nr].lit = lit;
            transitions[transitions_nr].message = mesaj;
            transitions_nr++;
        }
    }


    cout << "Introduceti starea initiala: ";
    cin >> def_state;
    if (exists(states, state_nr, def_state) == 0) {
        while (state_nr == n) {
            cout << "Prea multe stari! Reincercati! ";
            cin >> def_state;
        }
            states[state_nr++] = def_state;
    }


    cout << "Introduceti numarul de stari finale: ";
    cin >> final_states_nr;
    while (final_states_nr > n) {
        cout << "Numar prea mare. Reincercati: ";
        cin >> final_states_nr;
    }

    final_state = new string[final_states_nr];

    cout << "Se citesc starile finale: \n";
    for (int i = 0; i < final_states_nr; i++) {

        cout << "Se citeste starea finala #" << i + 1 << ": ";
        cin >> x;
        if (exists(states, state_nr, x) == 0) {
            if (state_nr == n) {
                cout << "Prea multe stari! Reincercati! ";
                i--;
            }
            else {
                states[state_nr++] = x;
                final_state[i] = x;
            }
        }
        else {
            final_state[i] = x;
        }
    }

    cout << "Introduceti numarul de cuvinte care trebuie testate: ";
    cin >> aux;
    unsigned int k,j;
    string cuv;
    string curr_state;
    char curr_char;
    for (int i = 0; i < aux; i++) {
        OK = 1;             //variabila care verifica daca am parcurs tot cuvantul
        afis_top = 0;       //se reseteaza stiva de afis
        traseu_top = 0;
        cout << "Se citeste cuvantul #" << i + 1 << ": ";
        cin >> cuv;
        curr_state = def_state;
        for (j = 0; j < cuv.size(); j++) {
            curr_char = cuv[j];
            for (k = 0; k < transitions_nr; k++)
                if (transitions[k].start == curr_state && transitions[k].lit == curr_char)
                    break;
            if (k == transitions_nr) { //nu exista o tranzitie din starea curenta cu litera cuvantului
                cout << "Cuvantul nu este acceptat. (cuvantul nu poate fi parcurs in intregime de catre automat).\n";
                OK = 0;
                break;
            }
            else {
                stack_traseu[traseu_top++] = curr_state;
                curr_state = transitions[k].end;
                stack_afis[afis_top++] = transitions[k].message;
            }
        }
        if (j == cuv.size()) {
            for (k = 0; k < final_states_nr; k++) 
                if (final_state[k] == curr_state)
                    break;
            if (k == final_states_nr) {
                cout << "Cuvantul nu este acceptat. (starea in care se termina nu este finala)\n";
            }
            else {
                cout << "Cuvantul este acceptat.\nOutput: ";
                for (k = 0; k < afis_top; k++)
                    cout << stack_afis[k];
                cout << "\n";
                cout << "Traseu: ";
                stack_traseu[traseu_top++] = curr_state;
                for (k = 0; k < traseu_top; k++)
                    cout << stack_traseu[k] << " ";
                cout << "\n";
            }
        }
    }

    delete[] final_state;
    delete[] transitions;
    delete[] states;
    return 0;

}