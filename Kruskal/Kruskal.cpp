#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Arete {
public:
    int src, dest, poids;

    Arete(int src, int dest, int poids) {
        this->src = src;
        this->dest = dest;
        this->poids = poids;
    }
};

class Graphe {
public:
    int V, E;
    vector<string> MST;
    vector<Arete> aretes;

    Graphe(int V, int E) {
        this->V = V;
        this->E = E;
    }

    void ajouterArete(int src, int dest, int poids) {
        Arete arete(src, dest, poids);
        aretes.push_back(arete);
    }
    
    int trouver(vector<int>& parent, int i) {
        if (parent[i] == -1)
            return i;
        return trouver(parent, parent[i]);
    }
    
    void kruskalMST() {
        vector<int> parent(V, -1);        
        sort(aretes.begin(), aretes.end(), [](Arete a, Arete b) {
            return a.poids < b.poids;
            });

        for (Arete arete : aretes) {
            int x = trouver(parent, arete.src);
            int y = trouver(parent, arete.dest);            
            
            if (x != y) {
                cout << arete.src << " - " << arete.dest << " : " << arete.poids << endl;
                MST.push_back( "(" + to_string(arete.src) + ", " + to_string(arete.dest) + ", " + to_string(arete.poids) + "),\n");
                parent[x] = y;
            }
        }
    }

    void exporter_Kruskal() {

        ofstream outputFile("Kruskal_data.txt");

        if (outputFile.is_open()) {

            outputFile << "[" << endl;
            for (Arete arete : aretes) {
                outputFile << "(" << arete.src << ", " << arete.dest << ", " << arete.poids << ")," << endl;
            }
            outputFile << "]" << endl;

            outputFile.close();
            cout << "Exportation de Kruskal reussie" << endl;
        }
        else {
            cout << "Echec d'acces au fichier" << endl;
        }
    }

    void exporter_Kruskal_MST() {

        ofstream outputFile("Kruskal_MST.txt");

        if (outputFile.is_open()) {

            outputFile << "[" << endl;
            for (string var : MST)
            {
                outputFile << var;
            }            
            outputFile << "]" << endl;

            outputFile.close();
            cout << "Exportation de Kruskal MST reussie" << endl;
        }
        else {
            cout << "Echec d'acces au fichier" << endl;
        }
    }
};


void Dessiner() {
    string pythonScriptPath = "Kruskal_Draw.py";

    string command = "python " + pythonScriptPath;

    int result = system(command.c_str());

    if (result == 0) {
        cout << "Les graphes ont ete dessines avec succes.";
    }
    else {
        cout << "Erreur d'execution";
    }
}

int main() {
    Graphe graphe(5, 5);
    
    graphe.ajouterArete(0, 1, 6);
    graphe.ajouterArete(1, 2, 5);
    graphe.ajouterArete(0, 2, 8);
    graphe.ajouterArete(2, 3, 1);
    graphe.ajouterArete(3, 4, 2);

    graphe.exporter_Kruskal();

    cout << "Arbre couvrant minimal de Kruskal :" << endl;
    graphe.kruskalMST();
    graphe.exporter_Kruskal_MST();
    Dessiner();


    /*
    int nbrSommet, nbrArret;
    cout << "Entrez le nombre de sommets : " << endl;
    cin >> nbrSommet;
    cout << "Entrez le nombre d'arrets : " << endl;
    cin >> nbrArret;

    Graphe graphe1(nbrSommet, nbrArret);
    int dep, dest, poids;
    for (int i = 0;i < nbrArret;i++) {
        cout << "Entrez le sommet de depart / destination / poids : " << endl;
        cin >> dep >> dest >> poids;
        graphe1.ajouterArete(dep, dest, poids);
    }
    */

    return 0;
}