#include <iostream>

using namespace std;
//Acciones basicas para las matrices de manera recursiva usando punteros, creacion de las listas dentro de una matriz
void crearM(int**m,int fil,int col,int i=0){
    if(i<fil){
        *(m+i)=new int[col];
        crearM(m,fil,col,i+1);
    }
}
void rellenar(int**m,int f,int c,int i,int j=0){
    if(j<c){
        cout<<"Ingresar valor para el elemento "<<i<<" "<<j<<":";
        cin>>*(*(m+i)+j);
        rellenar(m,f,c,i,j+1);
    }
}
void mostrar(int**m,int f,int c,int i,int j=0){
    if(j<c){
        cout<<*(*(m+i)+j)<<" ";
        mostrar(m,f,c,i,j+1);
    }
}
//Las funciones de mostrar y rellenar comparten estructura por lo cual se utilizara una funcion que recorra las filas
//y se usara un booleano flag para decidir que accion se realizara si el ingreso o la muestra de datos
void multiF(int**m,int f,int c,bool flag,int i=0){
    if(i<f){
        if (flag){
            rellenar(m,f,c,i);
        }else{
            mostrar(m,f,c,i);
            cout<<"\n";
        }
        multiF(m,f,c,flag,i+1);
    }
}
/*Debido a la estructura comun de las operaciones basicas de matrices se usara una estructura en comun para recorrer
tanto filas como columnas y con ayuda de una variable operacion se decidira que operacion se realizara, usando para
esto un puntero a funcion el cual cambiara dependiendo del valor de "op", ademas las funciones "mayor","menor",etc
Usaran el valor en la posicion i j tanto de la matriz A como de la matriz B y tomaran como referencia el elemento en
la matriz C debido a que este sera modificado*/
void mayor(int a,int b,int *c){*c=(a>b)?a:b;}//se utiliza operador ternario para optimizar espacio
void menor(int a,int b,int *c){*c=(a<b)?a:b;}
void suma(int a,int b,int *c){*c=a+b;}
void resta(int a,int b,int *c){*c=a-b;}
void promedio(int a,int b,int *c){*c=(a+b)/2;}
//OoeracionesF y operacionesM son la estrustura comun que comparten las operaciones basicas
void operacionesF(int**mA,int**mB,int**mC,int f,int c,int op,int i,int j=0){
    if (j<c){
        void(*fptr)(int,int,int*)=promedio;
        if(op==0)
            fptr=mayor;
        else if(op==1)
            fptr=menor;
        else if(op==2)
            fptr=suma;
        else if(op==3)
            fptr=resta;
        (*fptr)(*(*(mA+i)+j),*(*(mB+i)+j),*(mC+i)+j);
        operacionesF(mA,mB,mC,f,c,op,i,j+1);
    }
}
void operacionesM(int**mA,int**mB,int**mC,int f,int c,int op,int i=0){
    if(i<f){
        operacionesF(mA,mB,mC,f,c,op,i);
        operacionesM(mA,mB,mC,f,c,op,i+1);
    }
}
//Multiplicacion de matrices de forma recursiva tomando como base la estructura de un for(,,)
void multE(int**mA,int**mB,int**mC,int fA,int cB,int n,int i,int j,int k=0){
    if(k<n){
        *(*(mC+i)+j)+=(*(*(mA+i)+k)**(*(mB+k)+j));
        multE(mA,mB,mC,fA,cB,n,i,j,k+1);
    }
}
void multF(int**mA,int**mB,int**mC,int fA,int cB,int n,int i,int j=0){
    if(j<cB){
        *(*(mC+i)+j)=0;
        multE(mA,mB,mC,fA,cB,n,i,j);
        multF(mA,mB,mC,fA,cB,n,i,j+1);
    }
}
void multM(int**mA,int**mB,int**mC,int fA,int cB,int n,int i=0){
    if(i<fA){
        multF(mA,mB,mC,fA,cB,n,i);
        multM(mA,mB,mC,fA,cB,n,i+1);
    }
}
//Funciones de interaccion con el usuario en las cuales se podra elegir que operacion realizar dependiendo de las
//dimensiones de las matrices definidas previamente
void opNoMult(int**mA,int**mB,int**mC,int filas,int columnas){
    cout<<"Elige que operacion deseas realizar:\n1)Mayor\n2)Menor\n3)Suma\n4)Resta\n5)Promedio\n6)Mostrar matrices A y B\n0)Salir\n";
    int op;
    cin>>op;
    if(op==0){
        return;
    }
    if(op==6){
        cout<<"Matriz A:\n";
        multiF(mA,filas,columnas,false);
        cout<<"Matriz B:\n";
        multiF(mB,filas,columnas,false);
    }else{
        operacionesM(mA,mB,mC,filas,columnas,op-1);
        cout<<"\nMatriz resultante:\n";
        multiF(mC,filas,columnas,false);
    }
    opNoMult(mA,mB,mC,filas,columnas);
}
void todasOp(int**mA,int**mB,int**mC,int n){
    cout<<"Elige que operacion deseas realizar:\n1)Mayor\n2)Menor\n3)Suma\n4)Resta\n5)Promedio\n6)Multiplicacion AxB\n7)Multiplicacion BxA\n8)Mostrar matrices A y B\n0)Salir\n";
    int op;
    cin>>op;
    if(op==0){
        return;
    }
    if(op==8){
        cout<<"Matriz A:\n";
        multiF(mA,n,n,false);
        cout<<"Matriz B:\n";
        multiF(mB,n,n,false);
    }else {
        if(op==7){
            multM(mB,mA,mC,n,n,n);
        }else if(op==6){
            multM(mA,mB,mC,n,n,n);
        }else{
            operacionesM(mA,mB,mC,n,n,op-1);
        }
        cout<<"\nMatriz resultante:\n";
        multiF(mC,n,n,false);
    }
    todasOp(mA,mB,mC,n);
}
//Funcion de borrado de las listas de una matriz de forma recursiva
void borrarM(int **m,int fil,int i=0){
    if(i<fil){
        delete[]*(m+i);
    }
}
int main(){
    //Se pide el ingreso de dimensiones de las matrices al Usuario
    int filasA,filasB,columnasA,columnasB;
    cout <<"Ingresar filas para matriz A:";
    cin >> filasA;
    cout <<"Ingresar columnas para matriz A:";
    cin >> columnasA;
    cout <<"Ingresar filas para matriz B:";
    cin >> filasB;
    cout <<"Ingresar columnas para matriz B:";
    cin >> columnasB;
    //dependiendo del tamaño de las matrices el usuario podra realizar diferentes operaciones
    //por lo cual se considerara estos casos, de no ser compatibles se terminara la ejecucion con un mensaje de error
    if((filasA==filasB && columnasA==columnasB)||filasB==columnasA||filasA==columnasB){
        int **matrizA=new int*[filasA];
        int **matrizB=new int*[filasB];
        crearM(matrizA,filasA,columnasA);
        crearM(matrizB,filasB,columnasB);
        cout<<"\nDatos para la matrizA:\n";
        multiF(matrizA,filasA,columnasA,true);
        cout<<"\nDatos para la matrizB:\n";
        multiF(matrizB,filasB,columnasB,true);
        cout<<"Matriz A:\n";
        multiF(matrizA,filasA,columnasA,false);
        cout<<"Matriz B:\n";
        multiF(matrizB,filasB,columnasB,false);
        if(filasA==filasB && columnasA==columnasB && filasB!=columnasA){
            int **matrizC=new int*[filasA];
            crearM(matrizC,filasA,columnasA);
            opNoMult(matrizA,matrizB,matrizC,filasA,columnasA);
            borrarM(matrizC,filasA);
            delete[]matrizC;
        }else if(filasA==filasB && columnasA==columnasB && filasB==columnasA){
            int **matrizC=new int*[filasA];
            crearM(matrizC,filasA,columnasB);
            todasOp(matrizA,matrizB,matrizC,filasA);
            borrarM(matrizC,filasA);
            delete[]matrizC;
        }else if (filasB==columnasA){
            int **matrizC=new int*[filasA];
            crearM(matrizC,filasA,columnasB);
            cout<<"La unica operacion realizable es AxB, cuyo resultado es:\n";
            multM(matrizA,matrizB,matrizC,filasA,columnasB,filasB);
            multiF(matrizC,filasA,columnasB,false);
            borrarM(matrizC,filasA);
            delete[]matrizC;
        }else{
            int **matrizC=new int*[filasB];
            crearM(matrizC,filasB,columnasA);
            cout<<"La unica operacion realizable es BxA, cuyo resultado es:\n";
            multM(matrizB,matrizA,matrizC,filasB,columnasA,filasA);
            multiF(matrizC,filasB,columnasA,false);
            borrarM(matrizC,filasB);
            delete[]matrizC;
        }
        //Al haber concluido con la ejecucion se borrara las matrices creadas para liberar la memoria
        borrarM(matrizA,filasA);
        borrarM(matrizB,filasB);
        delete[]matrizA;
        delete[]matrizB;
    }else{
        cout<<"\n\nNo se puede realizar ninguna de las operaciones porque el tamanho de las matrices no lo permite\n";
    }
    return 0;
}
