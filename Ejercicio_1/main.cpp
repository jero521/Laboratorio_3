#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>


using namespace std;

//////////////////--definicion de funciones--//////////////////////

int lecturarapida(char *apunt_archi);
int* lectura2(int g,char *apunt_archi);
void codificar2(int *puntero,int esp,int g);
void codificar1(int *puntero,int esp,int g);

int *binario( char jamon[], int bin[], int g);
char *text(char n[]);
void decodificar2(char* apunt_archi, int seed, int g);



////////////////////////////////////////////////////////



//admin: 1203568749, adminpro23, 99999999 COP


////////////////////////////////////////////////////////


/////////////--Inico del programa--//////////////////////////
/// \brief main
/// \return
///

int main(){

    int g=0, numero=0, metodo=0;
    int* val=NULL;
    char abrir_archi[250];
    char* apunt_archi=NULL;
   // char* apunt_sali=NULL;



    cout<<"Elija una opcion ."<<endl<<" 1: metodo 1"<<endl<<" 2: metodo 2 "<<endl<<" 3: decodificar metodo 1"<<endl<<" 4: decodificar metodo 2"<<endl;cin>>metodo;

    if(metodo==1){

        cout<<"Ingrese un numero entero para la semilla: ";cin>>numero;

        apunt_archi = text(abrir_archi);  //le pide al usuario el nombre del archivo de inicio

        g=lecturarapida(apunt_archi);  //lee el archivo para saber cuantos elementos hay dentro

        if(g<1){
            cout<<"archivo de lectura vacio"<<endl;
            exit(1);
        }


        val = lectura2(g, apunt_archi);  //realiza un procedimiento para deolver un arreglo de bits del archivo

        codificar1(val, numero, g);

    }

    if(metodo==2){

        cout<<"Ingrese un numero entero para la semilla: ";cin>>numero;

        apunt_archi = text(abrir_archi);  //le pide al usuario el nombre del archivo de inicio

        g=lecturarapida(apunt_archi);  //lee el archivo para saber cuantos elementos hay dentro

        if(g<1){
            cout<<"archivo de lectura vacio"<<endl;
            exit(1);
        }

        val = lectura2(g, apunt_archi);  //realiza un procedimiento para devolver un puntero de un arreglo de bits

        codificar2(val, numero, g);   //codifica el archivo


    }

    if (metodo==3){

    apunt_archi = text(abrir_archi);
    }

    if (metodo==4){

    apunt_archi = text(abrir_archi);

    g=lecturarapida(apunt_archi);  //lee el archivo para saber cuantos elementos hay dentro

    int seed;

    cout<<"Ingrese la semilla: ";cin>>seed;

    if(g<1){
        cout<<"archivo de lectura vacio"<<endl;
        exit(1);
    }

    decodificar2(apunt_archi, seed, g);


    }


    if(metodo==0){




    }






    return 0;

}

////////////////////////////////////////////////////////////////////////////////////




//Funcion que le pide el nombre del archivo de inico con su extension y lo retorna//

char *text(char abrir_archi[250]){

    cout<<"Ingrese el nombre del archivo de entrada con la extension: ";cin>>abrir_archi;



    return abrir_archi;
}


/////////////////////////////////////////////////////////////////////////////////
/// \brief lecturarapida
/// \param apunt_archi
/// \return
///

//Funcion que se encarga de ver cuantos caracteres hay en el archivo//


int lecturarapida(char *apunt_archi){


    int n=0;
    char temp='a';



    ifstream p;
    p.open(apunt_archi,ios::in);    //abrir el archivo en modo lectura

    if(p.fail()){
        cout<< "No se pudo abrir el archivo"<<endl;
        exit(1);
    }


    while(p.good()){     //mientras no se llegue al final del archivo
       temp=p.get();
        n+=1;

}



    p.close();
    n--;

    return n;
}
////////////////////////////////////////////////////////////////////////////////////
/// \brief binario
/// \param jamon
/// \param bin
/// \param g
/// \return
///

/* Funcion que resive un arreglo con el que dentro se encuentra lo que hay en archivo, tambien otro arreglo y un entero vacio para cambiar el primer arreglo a binario y ponerlo en el segundo arreglo.
   devolviendo este segundo arreglo*/


int *binario( char jamon[], int bin[], int g){

    int cont=0;

    for(int i=0; i<g; i++){
      char  temp = jamon[i];

    for(int j=0; j<8; j++){
        bin[cont] = (((temp<<j))&128)/128;
        cont++;

    }




    }

     return bin;

}
/////////////////////////////////////////////////////////////////////////////////////
/// \brief lectura2
/// \param g
/// \param apunt_archi
/// \return
///

//Funcion que recibe un numero entero y crea un arreglo con lo que hay en el archivo. junto a la funcion binario  deulve un puntero.


int* lectura2(int g,char *apunt_archi){

    if(g<1){
        exit(1);
    }




    ifstream archi;
    char temp;
    char jamon[g];
    int cont=0;
    static int vale[1000];
    static int devulve[10000];






    archi.open(apunt_archi,ios::in);    //abrir el archivo en modo lectura

    if(archi.fail()){
        cout<< "No se pudo abrir el archivo";
        exit(1);
    }


    while(archi.good()){     //mientras no se llegue al final del archivo
        temp=archi.get();



    jamon[cont]=temp;     //agregra a un arreglo lo que encuentra en en el archivo
    cont++;

    }
   int *ptr = binario( jamon, vale, g);  //funcion que resive 2 arreglos y devuvlve otro arreglo



  for(int i=0;i<g*8;i++){  //se crea un areglo con lo que devolvio el puntero ptr
      devulve[i]= ptr[i];
  }




    archi.close();

    return devulve;


}
//////////////////////////////////////////////////////////////////////
/// \brief codificar2
/// \param puntero
/// \param esp
/// \param g
///
//codifica el arreglo que resive con el numero de la semilla y la cantidad de datos que tiene el archivo//

void codificar2(int *puntero, int esp, int g){

    int cont=0;
    int list[esp];

    ofstream fout;

    char foll[256];

    cout<<"Ingrese el archivo de salida con la extencion ";cin>>foll;


    fout.open(foll,fstream::app); //lo abre y escribe al final del fichero





    for(int i=0;i<g*8+1;i++){       //recorre el arreglo

        if(cont!=esp){

        list[cont]=puntero[i];
        cont++;
        }

        else{                                      //aplica la codificacion
            int aux = list[cont-1];
            for(int j=cont -1;j>=0;j--){
                list[j]=list[j-1];
            }
            list[0]=aux;


            for(int k=0;k<esp;k++){    //escribe en el archivo que le paso el usuario
                cout<<list[k];

                fout<<list[k];

            }

            cont=1;


            list[0]=puntero[i];
            }
        }
    fout<<"\n";




    fout.close();

}
/////////////////////////////////////////////////////////////////////////////////


void codificar1(int *puntero, int esp, int g){
    int cont=0;
    int list[esp];

    ofstream fout;

    char foll[256];

    cout<<"Ingrese el archivo de salida con la extencion ";cin>>foll;


    fout.open(foll,fstream::app); //lo abre y escribe al final del fichero

    for(int i=0;i<g*8+1;i++){       //recorre el arreglo

        if(cont!=esp){

        list[cont]=puntero[i];
        cont++;
        }

        else{

        }

}


}

void decodificar2(char* apunt_archi, int seed, int g){

    ofstream fout;
    ifstream archi;
    char list[seed],list2[g];
    char jamon[g];
    char temp, f[250],aux='a';
    int cont1=0,cont=0,z=0;




    archi.open(apunt_archi,ios::in);    //abrir el archivo en modo lectura

    if(archi.fail()){
        cout<< "No se pudo abrir el archivo";
        exit(1);
    }


    while(archi.good()){     //mientras no se llegue al final del archivo
        temp=archi.get();



    jamon[cont]=temp;     //agregra a un arreglo lo que encuentra en en el archivo
   // cout<<jamon[cont];  //***************************************
    cont++;

    }
    cout<<"Ingrese el archivo de salida con su extension: ";cin>>f;

    fout.open(f);






    for(int i=0;i<g+1;i++){       //recorre el arreglo


        if(cont1<seed){

        list[cont1]=jamon[i];
        cont1++;
        continue;

        }


        else{
                        //aplica la decodificacion
            aux = list[0];
            for(int j=0;j<seed;j++){
                list[j]=list[j+1];
            }
            list[cont1-1]=aux;




            for(int k=0;k<seed;k++){    //escribe en el archivo que le paso el usuario

                //cout<<list[k];
                list2[z]=list[k];
                //fout<<list[k];
                z++;

            }
            list[0]=jamon[i];

            cont1=1;


          //  list[0]=jamon[cont1];

            }


        }
    z=0;
    char list3[8];
    char sum=0;
    int con=0;
    int pepe=128;

    for(int h=0;h<g/8;h++){

        for(int i=0;i<8;i++){


            list3[i]=list2[z];
            z++;

        }



        while(pepe!=0){



            if(list3[con]=='1'){
                sum+=pepe;
            }
            con++;
            pepe/=2;

        }


        con=0;
        pepe=128;


        fout<<sum;


    sum=0;

    }


    fout.close();






}


























