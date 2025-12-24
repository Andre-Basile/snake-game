#include <iostream>
#include<vector>
#include<iomanip>

using namespace std;

vector<int> dimensionsTableau(int dimension){
    vector<int> tailles;
    if(dimension == 1){
        int t(0);
            do{
                       cout << "\n  Taille du tableau > ";
                       if( cin >> t  && (t >= 0)){
                            break;
                        }
                        cin.clear();
                        cin.ignore(255,'\n');
                 }while(t <= 0);
                tailles.push_back(t);
        }

    if(dimension == 2){
        int lines(0),cols(0);

        do{
           cout << "\nNombres de lignes > ";
            if( cin >> lines  && (lines > 0)){
                break;
            }
            cin.clear();
            cin.ignore(255,'\n');
        }while(lines <= 0);

        do{
           cout << "\nNombres de cols > ";
            if( cin >> cols  && (cols > 0)){
                break;
            }
            cin.clear();
            cin.ignore(255,'\n');
        }while(cols <= 0);

        tailles.push_back(lines);  //LINES EST en indice 0 et ensuite on a col en 1
        tailles.push_back(cols);
    }
            return tailles;
 }

vector<vector<char>> MatriceAireDeJeu(int lines,int cols,vector<vector<int>>& PointsConstitutifsDuSerpent,char tete,char itemMangeable,int & nbreItemMangeables){
    char caractereSpecialDeMur{'#'};
    vector<vector<char>> tab;
    
    vector<char>  BorderLine;
    for(int i=0;i<cols;i++){
        BorderLine.push_back(caractereSpecialDeMur);
    }

    tab.push_back(BorderLine);

    cout << endl <<  " Creons l'aire de jeu ligne par ligne ! ";
    for(int i=1;i<lines-1;i++){
        vector<char> currentLine;

        cout << endl << "> ";
        currentLine.push_back(caractereSpecialDeMur);
        for(int j=1;j<cols-1;j++){
                char myChar;
                //cout << " caractere de l'aire de jeu : ";
                cin >> myChar;
                currentLine.push_back(myChar);

                if(myChar == itemMangeable) nbreItemMangeables++;

                char caseVide = '.';
                if(myChar != caseVide && myChar != itemMangeable){
                    vector<int> coordonneesTete = {i,j};
                    PointsConstitutifsDuSerpent.push_back(coordonneesTete);
                }
        }
        currentLine.push_back(caractereSpecialDeMur);
        tab.push_back(currentLine);

        //Quand l'utilisateur entre de surplus,tant qu'on a déjà ce que nous voulons,on nettoie le buffer
        cin.clear();
        cin.ignore(255,'\n');
    }

    /*
     for(int i=0;i<PointsConstitutifsDuSerpent.size();i++){
        cout << endl << "Point " << i+1 << " aux coord " << PointsConstitutifsDuSerpent[i][0] << " , " << PointsConstitutifsDuSerpent[i][1];       
    }
    */
    tab.push_back(BorderLine);

    //Nettoyer la mémoire
    cin.clear();
    cin.ignore(255,'\n');
    return tab;
}

char commande(){
    char choice;
    do{
        cout << endl << "\t ======================================== ";
        cout << endl <<  "\t |  U : deplacement vers le haut\t|";
            cout << endl <<  "\t |  D : deplacement vers le  bas\t|";
                cout << endl <<  "\t |  L : deplacement vers le gauche\t|";
                    cout << endl <<  "\t |  R : deplacement vers le droite\t|";
          cout << endl << "\t ======================================== ";
          cout << endl << "\t  Choix >> ";
          cin >> choice;
    }while(choice != 'U' && choice != 'D'  && choice != 'L' && choice != 'R');

      return choice;
}


vector<int> positionDeLaTeteOuUnElement(vector<vector<char>> GameArea,char teteOuElement){
    //on pourrait bien obtenir le meme resultat avec le tableau <pointConstitutifsDuSerpent>
    vector<int> coord;
    for(int i=0;i<GameArea.size();i++){
        for(int j=0;j<GameArea[0].size();j++){
            if(GameArea[i][j] == teteOuElement){
                coord.push_back(i);
                coord.push_back(j);
                return coord;;
            }
        }
    }
    return coord;
}


bool OnMange(int x,int y,vector<vector<char>> GameArea,char itemMangeable){
        vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,itemMangeable);
        cout << endl << " taille corrd = " << coordTete.size();
        
        if(coordTete.size() == 0)  return false;
       
        cout << endl << " sortie de posTete et coordtte_x = " << coordTete[0] << " et coordtete_y = " <<coordTete[1];

        if(coordTete[0] == x && coordTete[1] == y){ cout << " youpi je mange "; return true;} 
        cout << "Oh non j mange pas";
        return false;
}

bool OnBouffe(int x,int y,vector<vector<char>> GameArea,char itemMangeable){
        if(GameArea[x][y] == itemMangeable) return true;
        return false;
}



void glisserSerpent(vector<vector<char>>& GameArea,int& tailleSerpent,char tete,vector<int> destinationDeLaTete,char caseVide,char itemCorpsDuSerpent,char itemMangeable,vector<vector<int>>& PointsConstitutifsDuSerpent) {
    
    vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,tete);  //Unique donc on peut autoriser une recherche dans toute la matrice MAIS les items changeables pouvant etre nombreux,utiliser cette fonction sur elles peut aboutir à des résultats non escomptés ,c'est d'ailleurs pour cette raison que c'est a fonction <OnBouffe> qui sera utilisée ici au lieu de <OnMange>

    if(coordTete.size() <2){ //On s'assure qu'il y a bien une  tete de serpent
        cout << " Tete de serpent non initialisée ! ";
        return;
    }

   
    
  //  destinationDeLaTete[0] = coordTete[0]+1;
  // destinationDeLaTete[1] = coordTete[1];

    bool aMange = OnBouffe(destinationDeLaTete[0],destinationDeLaTete[1],GameArea,itemMangeable); 

   // cout << endl << "  la tete est " << GameArea[coordTete[0]][coordTete[1]] << " en pos " << coordTete[0] <<  "," << coordTete[1];
    GameArea[destinationDeLaTete[0]][destinationDeLaTete[1]] = tete;  //On deplace la tete vers la destination
    GameArea[coordTete[0]][coordTete[1]] = caseVide;      //On rend libre l'endroit d'où la tete a quitté

   
    //On réinitialise le gardeur de traces <<PointsConstitutifsDuSerpent>> sachant que la tete est le derner element du vecteur
  //  cout << endl << "la taile de PointsConstitutifsDuSerpent des le depart est " << PointsConstitutifsDuSerpent.size();
    PointsConstitutifsDuSerpent[PointsConstitutifsDuSerpent.size()-1] = {destinationDeLaTete[0],destinationDeLaTete[1]};

    vector<int> OuLeDernierPointAQuitte = coordTete;

    for(int i=PointsConstitutifsDuSerpent.size()-2;i>=0;i--){  //On commence par le deuxieme point jusqu'au dernier,le premier est la tete (déjà traitée)
       
        vector<int> Actuel = PointsConstitutifsDuSerpent[i];
        char c = GameArea[Actuel[0]][Actuel[1]];
  //      cout << endl << " point consécutif " << c << " aux coord " << Actuel[0] << " , " << Actuel[1] << " et va vers " << OuLeDernierPointAQuitte[0] << " , " << OuLeDernierPointAQuitte[1];
        GameArea[OuLeDernierPointAQuitte[0]][OuLeDernierPointAQuitte[1]] = c;
        PointsConstitutifsDuSerpent[i] = {OuLeDernierPointAQuitte[0],OuLeDernierPointAQuitte[1]};
       GameArea[Actuel[0]][Actuel[1]] = caseVide;

     if(i-1>=0){
            vector<int> next = PointsConstitutifsDuSerpent[i-1];
     }   

        OuLeDernierPointAQuitte[0] = Actuel[0];
        OuLeDernierPointAQuitte[1] = Actuel[1];

      //  cout << " Le prochain point ira en " << OuLeDernierPointAQuitte[0] << "," << OuLeDernierPointAQuitte[1];
    }

    //Maintenant,on passe au deuxième gros travail qui est de voir si le serpent a mangé quelque chose
    //Si c'est le cas,il faut agrandir le serpent en ajoutant un point à la fin de la liste des points constitutifs du serpent
    vector<int> coordTeteApresDeplacement = positionDeLaTeteOuUnElement(GameArea,tete);
     if(aMange){
        //Heureusement, on sait où a quitté la queue du serpent car ces coordonnées sont les deux valeurs actuellement présentes dans le vecteur <<OuLeDernierPointAQuitte>>
        // Le nouvel élément à ajouter sera donc à la position OuLeDernierPointAQuitte[0],OuLeDernierPointAQuitte[1],
            tailleSerpent++;
            
         GameArea[OuLeDernierPointAQuitte[0]][OuLeDernierPointAQuitte[1]] = itemCorpsDuSerpent;
         vector<int> nouvelleCoordQueue = {OuLeDernierPointAQuitte[0],OuLeDernierPointAQuitte[1]};
        // PointsConstitutifsDuSerpent.push_back(nouvelleCoordQueue); Non ! car c'est la tete qui est en fin de iste ici
        PointsConstitutifsDuSerpent.insert(PointsConstitutifsDuSerpent.begin(),nouvelleCoordQueue);
 //        cout << endl << " La taille du serpent est " << tailleSerpent << " et cele de pointcons est " <<PointsConstitutifsDuSerpent.size();
    } 
}



bool Bas(vector<vector<char>>& GameArea,int& tailleSerpent,char tete,char itemCorpsDuSerpent,char barriere,char caseVide,char itemMangeable,vector<vector<int>>& PointsConstitutifsDuSerpent) {

    
    char corpsSerpent = 'O';

    vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,tete);
    if(GameArea[coordTete[0]+1][coordTete[1]]   ==  barriere){
        return false;
    }

    vector<int> destinationDeLaTete = {coordTete[0]+1,coordTete[1]};

    if(GameArea[coordTete[0]+1][coordTete[1]]   ==  corpsSerpent){
        return false;
    }

    glisserSerpent(GameArea,tailleSerpent,tete,destinationDeLaTete,caseVide,itemCorpsDuSerpent,itemMangeable,PointsConstitutifsDuSerpent);

     return true;
}


bool Haut(vector<vector<char>>& GameArea,int& tailleSerpent,char tete,char itemCorpsDuSerpent,char barriere,char caseVide,char itemMangeable,vector<vector<int>>& PointsConstitutifsDuSerpent) {

    
    char corpsSerpent = 'O';

    vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,tete);
    if(GameArea[coordTete[0]-1][coordTete[1]]   ==  barriere){
        return false;
    }

    vector<int> destinationDeLaTete = {coordTete[0]-1,coordTete[1]};

    if(GameArea[coordTete[0]-1][coordTete[1]]   ==  corpsSerpent){
        return false;
    }

    glisserSerpent(GameArea,tailleSerpent,tete,destinationDeLaTete,caseVide,itemCorpsDuSerpent,itemMangeable,PointsConstitutifsDuSerpent);

     return true;
}

bool Gauche(vector<vector<char>>& GameArea,int& tailleSerpent,char tete,char itemCorpsDuSerpent,char barriere,char caseVide,char itemMangeable,vector<vector<int>>& PointsConstitutifsDuSerpent) {
   
    char corpsSerpent = 'O';

    vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,tete);
    if(GameArea[coordTete[0]][coordTete[1]-1]   ==  barriere){
        return false;
    }
    vector<int> destinationDeLaTete = {coordTete[0],coordTete[1]-1};

    if(GameArea[coordTete[0]][coordTete[1]-1]   ==  corpsSerpent){
        return false;
    }

    glisserSerpent(GameArea,tailleSerpent,tete,destinationDeLaTete,caseVide,itemCorpsDuSerpent,itemMangeable,PointsConstitutifsDuSerpent);
      return true;
}

bool Droite3(vector<vector<char>>& GameArea,int& tailleSerpent,char tete,char itemCorpsDuSerpent,char barriere,char caseVide,char itemMangeable,vector<vector<int>>& PointsConstitutifsDuSerpent) {
   
    char corpsSerpent = 'O';

    vector<int> coordTete = positionDeLaTeteOuUnElement(GameArea,tete);
    if(GameArea[coordTete[0]][coordTete[1]+1]   ==  barriere){
        return false;
    }
    vector<int> destinationDeLaTete = {coordTete[0],coordTete[1]+1};

    if(GameArea[coordTete[0]][coordTete[1]+1]   ==  corpsSerpent){
        return false;
    }

    glisserSerpent(GameArea,tailleSerpent,tete,destinationDeLaTete,caseVide,itemCorpsDuSerpent,itemMangeable,PointsConstitutifsDuSerpent);
      return true;
}

void afficheAireDeJeu(vector<vector<char>> GameArea) {
    for(int i=0;i<GameArea.size();i++){
        cout << endl << " ";
        for(int j=0;j<GameArea[0].size();j++){
            cout << GameArea[i][j] << " ";
        }
    }

}


void afficheAireDeJeuModeFurtif(vector<vector<char>> GameArea) {
    for(int i=0;i<GameArea.size();i++){
        cout << endl << " ";
        for(int j=0;j<GameArea[0].size();j++){
            if(GameArea[i][j] == '.'){
                cout << " " << " ";
                continue;
            }
            cout << GameArea[i][j] << " ";
        }
    }

}

void afficheScoreDeJeu(int score){
    cout << endl << " \t  =============================";
    cout << endl << " \t  |" << setw(20) << "SCORE DU JEU" << setw(8) << right << "|";
    cout << endl << " \t  |" << setw(14) << right << score << setw(14) << right << "|";
    cout << endl << " \t  =============================";
}

int main()
{
    int tailleSerpent = 0,score = 0,nbreItemMangeables = 0;
    vector<vector<int>> PointsConstitutifsDuSerpent;
    cout << "Bienvenue !" << endl;
    vector<int> dim = dimensionsTableau(2);
    vector<vector<char>> GameArea = MatriceAireDeJeu(dim[0],dim[1],PointsConstitutifsDuSerpent,'S','*',nbreItemMangeables);
   
   // afficheAireDeJeu(GameArea);
    afficheAireDeJeuModeFurtif(GameArea);
     char directionChoisie;
    do{
     directionChoisie = commande();
    /*vector<int> c = positionDeLaTeteOuUnElement(GameArea,'S');
    cout << " bonjour";   */
     if(directionChoisie == 'R') {
    
            bool decision = Droite3(GameArea, tailleSerpent,'S','O','#','.','*',PointsConstitutifsDuSerpent);

         if(decision == false){
             cout << " GAME OVER !!! ";
             break;
         }            
      }

     if(directionChoisie == 'U') {
         bool decision = Haut(GameArea, tailleSerpent,'S','O','#','.','*',PointsConstitutifsDuSerpent);
         if(decision == false){
             cout << " GAME OVER !!! ";
             break;
         }
      }

     if(directionChoisie == 'D') {
         bool decision = Bas(GameArea, tailleSerpent,'S','O','#','.','*',PointsConstitutifsDuSerpent);

         if(decision == false){
             cout << " GAME OVER !!! ";
             break;
         }
      }

     if(directionChoisie == 'L') {
         bool decision = Gauche(GameArea, tailleSerpent,'S','O','#','.','*',PointsConstitutifsDuSerpent);
         if(decision == false){
             cout << " GAME OVER !!! ";
             break;
         }
      }

    // afficheAireDeJeu(GameArea);
     afficheAireDeJeuModeFurtif(GameArea);
     
      if(tailleSerpent == nbreItemMangeables) {
             cout << endl << " GAME WON...CONGRATULATIONS  !!! ";
             break;
         }
     }while(true);

    afficheScoreDeJeu(tailleSerpent); //Eh oui ! La taille du serpent augmente à chaque fois qu'on mange un item donc le score est égal à la taille du serpent

    cout << endl;
    return 0;
}

