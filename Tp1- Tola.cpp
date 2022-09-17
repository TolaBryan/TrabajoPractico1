#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    const int clien {8};
    const int prod {5};
    string VCodCliente[clien];//Vector para nombre de los clientes
    string VCodProd[prod];//Vector para nombre de los productos

    float VPeso[clien][prod] {}; //matriz para el peso en el "punto 1"
    float VRecorrido [clien][prod] {}; //Matriz para el recorrido punto 2 y punto 3
    int cantproduc[clien][prod] {};//matriz para el punto 3
    
    //Abro archivo para almacenarlo en los vectores e separlos por cliente y producto
    ifstream ArchiNombres;
    
    ArchiNombres.open("Nombres.txt");
    
    if(!ArchiNombres){
        cout<<"Error al abrir el archivo"<<endl;
        return 1;
    }
    for(int i=0;i<clien;++i){
        ArchiNombres>>VCodCliente[i];
    }
    for(int i=0;i<prod;++i){
        ArchiNombres>>VCodProd[i];
    }
    
    ArchiNombres.close();
    
    //abro archivo de datos
    ifstream ArchiDatos;
    ArchiDatos.open("Datos.txt");
    
    if(!ArchiDatos){
        cout<<"Error al abrir el archivo"<<endl;
        return 1;
    }
    
    int Clientes,productos;
    float Peso, Recorrido;
    
    while(ArchiDatos>>Clientes>>productos>>Peso>>Recorrido){
        VPeso[Clientes][productos]+=Peso;
        VRecorrido[Clientes][productos]+=Recorrido;
        cantproduc[Clientes][productos]++;
    }
   
    //punto 1
    cout<<"PUNTO 1"<<endl;
    cout<<"Generando productos de clientes mayores a 13000kg: "<<endl;
    
    int ipeso,jpeso;
    int cant[prod]{};
    for(int i=0;i<clien;++i){
        cout<<endl;
        for(int j=0;j<prod;++j){
            
            if(VPeso[i][j]>13000){
                cout<<"Cliente: "<<VCodCliente[i]<<"  Peoducto: "<<VCodProd[j]<<"  Peso: "<<VPeso[i][j]<<"kg"<<endl;
                cant[i]=cant[i]+1;//Contador para el punto 2, para saber que cliente tiene mas porductos superiores a 13000kg
            }
        }
    }
    
    cout<<endl;
    cout<<" ----- ----- "<<endl;
    cout<<endl;
    
    
    //punto 2
    cout<<"PUNTO 2"<<endl;
    
    bool primera=true;
    int mayor,imayor;
    for(int i=0;i<prod;++i){
        if(cant[i]>mayor || primera){
            mayor=cant[i];
            imayor=i;
            primera=false;
        }
    }
    
    cout<<"La cliente con mas productos es " <<VCodCliente[imayor]<<endl;
    cout<<endl;
    
    for(int i=0;i<clien;++i){
        for(int j=0;j<prod;++j){
            if(imayor==i){
                cout<<"Producto: "<<VCodProd[j]<<"  Recorrido: "<<VRecorrido[i][j]<<"Km"<<endl;            
            }
        }
    }
    
    cout<<endl;
    cout<<" ----- ----- "<<endl;
    cout<<endl;
    
    
    //PUNTO 3
    cout<<"PUNTO 3"<<endl;
    
    primera=true;
    int jreco;
    float Recorrridomayor;
    
    for(int j=0;j<prod;++j){
        if(VRecorrido[imayor][j]>Recorrridomayor || primera){
            Recorrridomayor= VRecorrido[imayor][j];
            jreco= j;
            primera=false;
        }
    }
    
    int Cantotal{0};
    
    for(int i=0;i<clien;++i){
        for(int j=0;j<prod;++j){
            if(jreco==j){
                Cantotal+=cantproduc[i][j];
            }
        }
    }
    
    
    cout<<"El producto con mayor recorrido es "<<VCodProd[jreco]<<" con "<<VRecorrido[imayor][jreco]<<"Km"<<endl;
    cout<<"La cantidad total sin importar los clientes de "<<VCodProd[jreco]<<" es "<<Cantotal<<" productos"<<endl;
    ArchiDatos.close();
    return 0;

    
}
