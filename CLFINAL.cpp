#include <stdexcept>
#include <array>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//g++ -std=c++11 -Wall CLFINAL.cpp -o CLFINAL


// NOMBRES DE TIRAGES A EFFECTUER 

int N = 10000; //Envrion 12 min (pour 40000)

enum class Pays{Autriche,France, Italie, Angleterre, Allemagne, Espagne, Portugal, PaysBas};

    // STRUCTS
struct Config{
    vector<vector<string>>tir; // tirage
    int apparition; // nbre apparition config
};

struct Proba{
    string name;  // équipe affontée
    float appear; // nbre apparition
};

struct Equipe{
    string nom;
    Pays pays;
    int place;
    char groupe;
    vector<Proba>prob; // tab du nombre d'apparition pour chaque équipe affrontée par cette Equipe 
    
};

struct Tableau{
    vector<vector<Equipe>>tab; // tab final avec probas d'affronter chaque équipe pour chaque Equipe
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   
    // EQUIPES PHASES DE GROUPES SAISON 2018/2019

Equipe City{"City",Pays::Angleterre,1,'A',{}};
Equipe PSG{"Paris",Pays::France,2,'A',{}};

Equipe Liv{"Liverpool",Pays::Angleterre,1,'B',{}};
Equipe Atl{"Atletico",Pays::Espagne,2,'B',{}};

Equipe Ajax{"Ajax",Pays::PaysBas,1,'C',{}};
Equipe Sporting{"Sporting",Pays::Portugal,2,'C',{}};

Equipe Real{"Real",Pays::Espagne,1,'D',{}};
Equipe Inter{"Inter",Pays::Italie,2,'D',{}};

Equipe Bayern{"Bayern",Pays::Allemagne,1,'E',{}};
Equipe Benfica{"Benfica",Pays::Portugal,2,'E',{}};

Equipe ManU{"United",Pays::Angleterre,1,'F',{}};
Equipe Vil{"Villareal",Pays::Espagne,2,'F',{}};

Equipe LOSC{"Lille",Pays::France,1,'G',{}};
Equipe Salz{"Salzoubrg",Pays::Autriche,2,'G',{}};

Equipe Juve{"Juventus",Pays::Italie,1,'H',{}};
Equipe Chel{"Chelsea",Pays::Angleterre,2,'H',{}};


vector<vector<Equipe>>all = {{City,Liv,Ajax,Real,Bayern, ManU,LOSC,Juve},{PSG,Atl,Sporting,Inter,Benfica,Vil,Salz,Chel}};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
    // EQUIPES PHASES DE GROUPES SAISON 2020/2021

Equipe Mun{"Bayern",Pays::Allemagne,1,'A',{}};
Equipe Atleti{"Atlético",Pays::Espagne,2,'A',{}};

Equipe RM{"Real",Pays::Espagne,1,'B',{}};
Equipe Glad{"M'Gladbach",Pays::Allemagne,2,'B',{}};

Equipe City{"City",Pays::Angleterre,1,'C',{}};
Equipe Port{"Porto",Pays::Portugal,2,'C',{}};

Equipe Live{"Liverpool",Pays::Angleterre,1,'D',{}};
Equipe Atal{"Atalanta",Pays::Italie,2,'D',{}};

Equipe Chel{"Chelsea",Pays::France,1,'E',{}};
Equipe Sev{"Seville",Pays::Espagne,2,'E',{}};

Equipe Dor{"Dortmund",Pays::Allemagne,1,'F',{}};
Equipe Laz{"Lazio",Pays::Italie,2,'F',{}};

Equipe Juv{"Juventus",Pays::Italie,1,'G',{}};
Equipe FCB{"Barcelona",Pays::Espagne,2,'G',{}};

Equipe Paris{"Paris",Pays::France,1,'H',{}};
Equipe Lep{"Leipzig",Pays::Allemagne,2,'H',{}};


vector<vector<Equipe>>all2 = {{Mun,RM,City,Live,Chel, Dor,Juv,Paris},{Atleti,Glad,Port,Atal,Sev,Laz,FCB,Lep}};
*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // SURCHARGES OPERATEURS

// Struct Equipe
ostream& operator<<(ostream& out, Equipe e){
    out << e.nom << " :  Place: "  << e.place << " / Groupe: " << e.groupe << endl<<endl;
    for( size_t i = 0; i < e.prob.size(); i++){
        out << e.prob[i].name << " : " << (float(e.prob[i].appear)/N)*100 <<'%'<<endl;
    }
    out << "////////////////////" << endl;
    return out;
}

//vector de Proba
ostream& operator<<(ostream& out, vector<Proba>prob){
    for( size_t i = 0; i < prob.size(); i++){
        if (float(prob[i].appear) == 0){
            out << setw(14)<<(float(prob[i].appear))<<"%" ;
        }else{
            out << setw(14)<<(float(prob[i].appear))<<"%" ;
        }
    }
    return out;
}
    
//vector 2d string   
ostream& operator<<(ostream& out, vector<vector<string>> t){
    out << '{';
    for(size_t i = 0; i < t.size(); i++){
        if ( i == t.size()-1){
            out << '{' << t[i][0] << ", " << t[i][1] << "}";
        }else{
            out << '{' << t[i][0] << ", " << t[i][1] << "},";
        }
    }
    out << '}';
    return out;
}

//Struct Tableau
ostream& operator<<(ostream& out, Tableau T){
    out << "        ";
    for(size_t i = 0; i < 8; i++){
        out << "     "<<T.tab[0][i].nom <<"   |" ;
    }
    out << endl<< endl;
    for(size_t i = 0; i < 8; i++){
        out << setw(3)<< T.tab[1][i].nom << setw(3)<< T.tab[1][i].prob << endl << endl ;
    }
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // FONCTIONS: PRESCENCE ELEM DANS UN TAB, OU NON


// Renvoie l'indice de s si il est dans le tab, -1 sinon
int estTire(string s, vector<string>t){
    for (size_t i = 0 ; i < t.size(); i++){
        if( s == t[i] ) {
            return i;
        }
    }
    return -1;
}
// Renvoie l'indice de s si il est dans le tab de Proba, -1 sinon
int estTirePro(string s, vector<Proba>t){
    for (size_t i = 0 ; i < t.size(); i++){
        if( s == t[i].name ) {
            return i;
        }
    }
    return -1;
}

// Renvoie true si 2 tab 2d de string sont égaux, false sinon
bool memeConfig( vector<vector<string>> t, vector<vector<string>> tt){
    size_t ok = 0;
    for(size_t i = 0; i < t.size(); i++){
        for( size_t j = 0; j < tt.size(); j++){
            if (t[i][0] == tt[j][0] and t[i][1] == tt[j][1]){
                ok++;
            }
        }
    }
    
    if ( ok == t.size()){
        return true;
    }
    else{return false;}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // FONCTION TIRAGE ALÉATOIRE


// Tableau d'une configuration d'un tirage de huitièmes de final
vector<vector<string>> tirage(vector<vector<Equipe>>G){
     
    vector<vector<string>>tir = {}; //Tableau de la configuration finale ( 8 confrontations de 2 équipes)
    vector<string>E1 = {};          //Tableau équipes 1ères tirées 
    vector<string>E2 = {};          //Tableau équipes 2èmes tirées 
    Equipe deux;
    Equipe prem; 
    
    
    while(tir.size() != G.size()){  //tant qu'il n'y a pas 8 matchs
        
        vector<Equipe>E = {};     // Tableau équipes que peut affronter 'deux' dans équipes non tirées 
        vector<Equipe>G1 = {};    // Tableau équipes 1ères NON tirées
        vector<string>match = {}; // Tableau du match (comporte 2 équipes à chaque fin de boucle)
        
        do{
            deux = G[rand()% G.size()][1];  // on tire 'deux', une équipe 2ème qui n'a pas encore été tirée
        }while(estTire(deux.nom, E2) != -1);
        
        E2.push_back(deux.nom); // on place 'deux' dans les équipes 1ères déja tirées
        
        // Création de G1
        for(size_t i = 0; i < G.size(); i++){
            G1.push_back(G[i][0]);
            if(estTire(G[i][0].nom,E1) != -1){
                G1.pop_back();
            }
        }
        
        // Création de E
        for(size_t i = 0; i < G1.size(); i++){
            if ( G1[i].groupe != deux.groupe and G1[i].pays != deux.pays){
                E.push_back(G1[i]);
            }
        }
       
        // Si 'deux' ne peut affronter personne, on recommence le tirage 
        if ( E.size() == 0 ){
            E1.clear();
            E2.clear();
            tir.clear();
       
        }else{ 
            prem = E[rand()% E.size()]; // sinon on tire 'prem', une équipe dans les équipes que peut affronter 'deux'

            
            E1.push_back(prem.nom);  // on place 'prem' dans les équipes 1ères déja tirées
            
            // les 2 équipes tirées forment le match
            match.push_back(deux.nom);
            match.push_back(prem.nom);
            
            tir.push_back(match);  // on place ce match dans le tirage
        }
       
    }
    return tir;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // FONCTIONS CONFIGURATIONS

// Liste de toutes les configurations possibles (sans doublon)
vector<Config> listeConfig(vector<vector<Equipe>>Groupe, int nbtirages){
    
    Config TIR{tirage(Groupe),1};  
    vector<Config>configs = {};
    configs.push_back(TIR);
  
    for (int i = 0; i < nbtirages ; i++){
        size_t k = 0;
        vector<vector<string>>tir_sub = tirage(Groupe);
        
        for (size_t j = 0; j < configs.size(); j++){
            if( memeConfig(configs[j].tir, tir_sub) == false){
                k++;
            }
            else{
                configs[j].apparition++;
            }
        }
        
        if (k == configs.size()){
            Config T{tir_sub,1};
            configs.push_back(T);
        }
        //cout << i <<' '; // Décompte
        
    }
    return configs;
}

// Nombre d'apparition d'une config donnée dans la liste des configs (à diviser par le nombre de configs et x100 pour le %)
float probaConfig(vector<vector<string>>huitiemes, vector<Config>configs){
    for (size_t i = 0; i < configs.size(); i++){
        if (memeConfig(huitiemes, configs[i].tir)){
            return configs[i].apparition;
        }
    }
    return -1;
}

//Nombre d'appartion d'une confrontation sur un nombre nb de configs
Proba probaEquipe(Equipe e, Equipe f, vector<Config>configs, int nb){

    Proba p{f.nom,0};
    if(e.place == 1){
        for( size_t i = 0; i < configs.size(); i++){
            for(size_t j = 0; j < configs[i].tir.size(); j++){
                if(configs[i].tir[j][1] == e.nom and configs[i].tir[j][0]==f.nom){
                    p.appear++;
                }
            }
        }
    }else{
        for( size_t i = 0; i < configs.size(); i++){
            for(size_t j = 0; j < configs[i].tir.size(); j++){
                if(configs[i].tir[j][0] == e.nom and configs[i].tir[j][1]==f.nom){
                    p.appear++;
                }
            }
        }
    }
    p.appear = (p.appear/nb)*100;
    return p;
}

//Pour une équipe donnée, Tableau du nombre d'apparition pour chaque confrontation

vector<Proba> tabProbaEquipe(Equipe e, vector<vector<Equipe>>all,vector<Config>configs,int nb){
    vector<Proba>equipes = {};
    if(e.place == 1){
        for( size_t i = 0; i < all[1].size(); i++){
            equipes.push_back(probaEquipe(e,all[1][i],configs,nb));
        }
    }else{
        for( size_t i = 0; i < all[0].size(); i++){
            equipes.push_back(probaEquipe(e,all[0][i],configs,nb));
        }
    }
    return equipes;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   
    // MAIN

int main(){
    srand(time(NULL));
    
    
    
    //Equipes après les phases de poules 18/19 (position de chaque équipe dans le sous tableau = son classement dans son groupe )
    vector<vector<Equipe>>Groupe19 = {{City,PSG},{Liv,Atl},{Ajax,Sporting},{Real,Inter},{Bayern,Benfica},{ManU,Vil},{LOSC,Salz},{Juve,Chel}};
    
   /* cout <<endl << "EXEMPLE DE TIRAGE ALEATOIRE :" <<endl <<endl;    
    
    vector<vector<string>> t = tirage(Groupe19);
    

    cout << "Tirage 1 : " << t[0][1]<< " vs " << t[0][0]<< endl<< endl;
    cout << "Tirage 2 : " << t[1][1]<< " vs " << t[1][0]<< endl<< endl;
    cout << "Tirage 3 : " << t[2][1]<< " vs " << t[2][0]<< endl<< endl;
    cout << "Tirage 4 : " << t[3][1]<< " vs " << t[3][0]<< endl<< endl;
    cout << "Tirage 5 : " << t[4][1]<< " vs " << t[4][0]<< endl<< endl;
    cout << "Tirage 6 : " << t[5][1]<< " vs " << t[5][0]<< endl<< endl;
    cout << "Tirage 7 : " << t[6][1]<< " vs " << t[6][0]<< endl<< endl;
    cout << "Tirage 8 : " << t[7][1]<< " vs " << t[7][0]<< endl<< endl;

    
    cout << endl<< endl<< "EDITION 2018/2019 : "<<endl<<endl;*/
    
    // Tirage 8emes officiel 18/19
    //vector<vector<string>>huitiemesoff19 = {{"Tottenham", "Dortmund"},{"Shalke", "City"},{"Ajax", "Real"},{"Atlético", "Juventus"},{"Lyonnais", "Barcelona"},{"United", "Paris"},{"Liverpool", "Bayern"},{"Roma", "Porto"}};
    
    
    cout << endl;
   
    
    vector<Config>nbreconfig19 = listeConfig(Groupe19,N);
    int nb19 = nbreconfig19.size();
    
    
    cout << "Nombres essais avant stabilisations: environ "<< N << endl<< endl;  
    cout << "Nombres totales de combinaisons : "<< nb19 << endl<< endl;
    
    //cout << "Probabilité d'obtenir la configuration officielle de la saison 2018/2019 : " << (probaConfig(huitiemesoff19, nbreconfig19)/N)*100 << '%' << endl<< endl;
    
    
    for( size_t i = 0; i < all.size(); i++){
        for( size_t j = 0; j < all[i].size(); j++){
            all[i][j].prob = tabProbaEquipe(all[i][j],all,nbreconfig19,nb19);
        }
    }
        
    Tableau Final{all};
    cout << Final << endl;

    
    
    cout << endl << endl << endl;
    
    
    
    /*
    cout << "EDITION 2020/2021 : "<<endl<<endl;
    
    
    //Equipes après les phases de poules 20/21 (position de chaque équipe dans le sous tableau = son classement dans son groupe )
    vector<vector<Equipe>>Groupe21 = {{Mun,Atleti},{RM,Glad},{City,Port},{Live,Atal},{Chel,Sev},{Dor,Laz},{Juv,FCB},{Paris,Lep}};
    
    // Tirage 8emes officiel 18/19
    vector<vector<string>>huitiemesoff21 = {{"M'Gladbach", "City"},{"Lazio", "Bayern"},{"Atlético", "Chelsea"},{"Leipzig", "Liverpool"},{"Porto", "Juventus"},{"Barcelona", "Paris"},{"Seville", "Dortmund"},{"Atalanta", "Real"}};
    
    vector<Config>nbreconfig21 = listeConfig(Groupe21,N);
    int nb21 = nbreconfig21.size();
    
    
    cout << "Nombres essais avant stabilisations: environ 30 000" << endl<< endl;  
    cout << "Nombres totales de combinaisons : "<< nb21 << endl<< endl;
    
    cout << "Probabilité d'obtenir la configuration officielle de la saison 2020/2021 : " << (probaConfig(huitiemesoff21, nbreconfig21)/N)*100 << '%' << endl<< endl;
    
    
    for( size_t i = 0; i < all2.size(); i++){
        for( size_t j = 0; j < all2[i].size(); j++){
            all2[i][j].prob = tabProbaEquipe(all2[i][j],all2,nbreconfig21,nb21);
        }
    }
        
    Tableau Final2{all2};
    cout << Final2 << endl<<endl;
    */
    return 0;
}    

















