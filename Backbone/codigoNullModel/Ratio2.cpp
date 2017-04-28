#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;
using std::string;


// string **GetData(ifstream entrada, int N ) {
// 
//     
//     string Datos[N][3];
//     
//         int i=0;        
//         string line;
//         while(getline(entrada, line)) {            
//             string data;
//             stringstream linestream(line);
//             
//             int j=0;
//             while(getline(linestream, data, '\t')){           
//                 Datos[i][j]=data;
//                 j++;
//                 
//             }
//             
//             i++;
//         }          
//             
//     return Datos;
//  
//     
// }


vector < vector< string > > GetData(ifstream &entrada, int N ) {

    
    vector < vector< string > > Datos;
    
        Datos.resize(N);
        int i=0;        
        string line;
        
        while(getline(entrada, line)) {
            
            string data;
            stringstream linestream(line);
            
            while(getline(linestream, data, '\t')){           
                Datos[i].push_back(data);
            }
            
            i++;
        }          
            
    return Datos;
 
    
}



int main(int argc, char** argv) {

    ifstream entrada1;
    entrada1.open(argv[1]);    
    ifstream entrada2;
    entrada2.open(argv[2]);   
    
    ofstream salida;
    salida.open("YsSanos.dat");    

    int N = atoi(argv[3]);
    double Ynull = atof(argv[4]);
    
    vector < vector< string > > Sanos = GetData(entrada1, N);
    vector < vector< string > > Enfermos = GetData(entrada2, N);
    
    vector <double> YsSanos;
    vector <double> YsEnfermos;
 
//     YsSanos.resize(Sanos.size());
//     YsEnfermos.resize(Enfermos.size());
    
    
 
 
//     for (int i=0;i<Sanos.size();i++){
    for (int i=0;i<N;i++){
        YsSanos.push_back(atof(Sanos[i][2].c_str()));
        YsEnfermos.push_back(atof(Enfermos[i][2].c_str()));
        
//          cout << Sanos[i][2].c_str() << "   " << Enfermos[i][2].c_str() << endl;
    }
    
    
    
//     for (int i=0;i<N;i++){
//         cout << YsSanos[i] << endl;
//         }       
//     
        
    double R=0;
    for (int i=0;i<N;i++){
            if (YsEnfermos[i] >= Ynull) {
                cout << Enfermos[i][0] << endl;
//                 cout << "-----------" << endl;  
            }  
//         cout << YsSanos[i] << "  " << YsEnfermos[i] << endl;
            R =(YsEnfermos[i]/YsSanos[i]);
//             if (R > 1){
//                 cout << Sanos[i][0] << " " << R << endl;
//                 cout << "#########" << endl;                 
//             }
        }       

    
    
    
}

