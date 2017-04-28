#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;
using std::string;

// RUN
// ./a.out RED.adj N A/B TIMESigma

int main(int argc, char** argv) {

    ifstream entrada;
    ofstream salida;
    ofstream parametros;
    ofstream pesos;
    ofstream NodsBB;

    entrada.open(argv[1]);
    
    float N = atof(argv[2]);
    char type = *argv[3];
    int A = atof(argv[4]);
    
    vector<string> fileName;
    vector < vector< string > > matrix;
    
    stringstream ss(argv[1]);
    string token;
    while( getline( ss, token, '.' ) ) {
        fileName.push_back(token);
    }
    
    
    string output;
    string params;
    string outputPesos;
    string outputNBB;
    
    output = fileName[0] + "_NullModel_Backbone" + ".dat";
//     cout << output << endl;
    params = "parametros_" + fileName[0];
    outputPesos = fileName[0] + "_PESOS" + ".dat";
    outputNBB = fileName[0] + "_NodosBackbone";
    
    salida.open(output.c_str());
    
        
    
// Extraccion de DATOS ############################

    if (fileName[1] == "adj" || fileName[1] == "txt") {
        
        cout << "archivo " + fileName[1] << endl;

        matrix.resize(N);
//         cout << "N = " << N << endl;        
        string   line;    
        int i =0;
        
        while(getline(entrada, line)) {
            
            string data;
            stringstream linestream(line);
            
            while(getline(linestream, data, '\t')){           
            matrix[i].push_back(data);
                
            }
            
            i++;
        }          
        
        
    } else {
        
        cout << "archivo sif" << endl;
        
        string arr[3];    
        string line;
        string tmp;            
        arr[0]=" ";
        
        vector<string> temporal;

        while(getline(entrada, line)) {
            
            string data;
            stringstream linestream(line); // tomamos cada linea como un flujo
                            
            string tmp = arr[0]; // asignamos  tmp el ultimo valor de arr[0] i.e. el gen source

            int i=0;
            char sep;
            if (type == 'A') {sep = '\t';} else {sep = ' ';}
            
            while(getline(linestream, data, sep)){ //obtenemos toda la nueva linea separa por tabs en o espacio en arreglo de tres
                arr[i] = data;
                i++;        
            }  
            
//             for (int i=0;i<3;i++){cout << arr[i]  << ", "; }cout << endl; 
            
            if (!arr[0].compare(tmp) || !tmp.compare(" ")) { 
                temporal.push_back(arr[1]); // si el primer target es igual al amterior o bien es vacio (la primera vez), entonces agregamos el peso actual al vector temporal
            } else {
                matrix.push_back(temporal); // en caso contrario, agregamos todos los pesos del vector temporal a la matriz
                temporal.clear();           // limpiamos el vector temporla
            } 
            
        }     
    
       
        
    } 


// Calculo de Fuerzas y pesos normalizados ############################    

    pesos.open(outputPesos.c_str());
    NodsBB.open(outputNBB.c_str());

//     double Ynull = (2 - (1/(N))) + 2*((N-1)*sqrt( ((20 + 4*(N-1))/(N*(N+1)*(N+2))) - (4/(pow(N,2)))));
    double Ynull = (2 - (1/(N))) + A*((N-1)*sqrt( ((20 + 4*(N-1))/(N*(N+1)*(N+2))) - (4/(pow(N,2)))));

    if (fileName[1] == "adj") {

        for (int k=0; k<N; k++) {
            
            double s = 0;
            double w = 0;
            double p = 0;
            double Sp = 0;
            vector <double> P;
        
        

            for (int i=1; i<matrix[k].size();i=i+2) {
                w = atof(matrix[k][i+1].c_str());
                pesos << w << '\n';
                s = s + w;
                
            } 


            for (int i=1; i<matrix[k].size();i=i+2) {
                w = atof(matrix[k][i+1].c_str());        
                p = w/s;
                P.push_back(p);
                Sp = Sp + pow(p,2);
            
            }   salida << matrix[k][0] << "\t";

            double Y = (N - 1)*Sp; 
            
            salida << log10(N - 1) << "\t" << Y << endl;            
            if (Y > Ynull) {NodsBB << matrix[k][0] << "\t" << Y << endl;}  
            
            
//             salida << gardo << "\t" << Y << endl;
            
/*            cout << matrix[k][0] << "   " << P.size() << endl;
            for (int i=0; i<P.size();i++) {                
                cout << P[i] << endl;
                cout << "##############" << endl;
            }     */       
                             
            
        }        
        
    } else {
        
        N = matrix.size();
//         cout << "N = " << N << endl;

        for (int k=0; k<N; k++) {
            
//             cout << k << endl;
            
            double s = 0;
            double w = 0;
            double p = 0;
            double Sp = 0;
            vector <double> P;            
            

            int start;
            if(fileName[1] == "sif"){start=0;}else{start=1;}
            for (int i = start; i<matrix[k].size();i++) {
                w = atof(matrix[k][i].c_str());     
                s = s + w;
                
            } 


            if(fileName[1] == "sif"){start=0;}else{start=1;}
            for (int i = start; i<matrix[k].size();i++) {
                w = atof(matrix[k][i].c_str());
                pesos << w << '\n';
                p = w/s;
                P.push_back(p);
                Sp = Sp + pow(p,2);
            
            }    salida << matrix[k][0] << "\t";

            double Y = (N - 1)*Sp; 
            
            salida << log10(N - 1) << "\t" << Y << endl;
            if (Y > Ynull) {NodsBB << matrix[k][0] << "\t" << Y << endl;}
            
/*            cout << matrix[k][0] << "   " << P.size() << endl;
            for (int i=0; i<P.size();i++) {                
                cout << P[i] << endl;
                
            } cout << "##############" << endl;     */      
                    
            
//             cout << "lo hice 1!" << endl;
//             cout << "N = " << N << endl;
            
        }  
        
//         cout << "lo hice 2  ############################!" << endl;
        
    }
    
//     cout << "aqui**************************!" << endl;
    
    
    
//     double Ynull = (2 - (1/(N))) + 2*((N-1)*sqrt( ((20 + 4*(N-1))/(N*(N+1)*(N+2))) - (4/(pow(N,2)))));
    
    parametros.open(params.c_str());
    

    
    cout << "N = " << N << endl;
    
    cout << "Ynull = " << Ynull << endl;
    cout << "log10(N - 1) = " << log10(N - 1) << endl;


    
    parametros << output.c_str() << ' ' << Ynull << ' ' << log10(N - 1) << endl;
    
    
    
    
}



