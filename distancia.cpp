#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;


#define MAX 10005 
#define Node pair< int , int > 
#define INF 1<<30 


struct cmp {
    bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
};
vector< Node > ady[ MAX ];
int distancia[ MAX ];  
bool visitado[ MAX ];
priority_queue< Node , vector<Node> , cmp > Q; 
int V;                     
int previo[ MAX ];         

void init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF; 
        visitado[ i ] = false; 
        previo[ i ] = -1;    
    }
}


void relajacion( int actual , int adyacente , int peso ){
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  
        previo[ adyacente ] = actual;                         
        Q.push( Node( adyacente , distancia[ adyacente ] ) );
    }
}


void print( int destino ){
    if( previo[ destino ] != -1 )    
        print( previo[ destino ] );  
    printf("%d " , destino );      
}

void dijkstra( int inicial ){
    init(); 
    Q.push( Node( inicial , 0 ) ); 
    distancia[ inicial ] = 0;      
    int actual , adyacente , peso;
    while( !Q.empty() ){                   
        actual = Q.top().first;            
        Q.pop();                          
        if( visitado[ actual ] ) continue;
        visitado[ actual ] = true;         

        for( int i = 0 ; i < ady[ actual ].size() ; ++i ){ //adyacentes
            adyacente = ady[ actual ][ i ].first;  
            peso = ady[ actual ][ i ].second;       
            if( !visitado[ adyacente ] ){       
                relajacion( actual , adyacente , peso ); 
            }
        }
    }


    printf( "Distancias mas cortas a los vertices\n" );
    for( int i = 1 ; i <= V ; ++i ){
        printf("Del vertice %d al Vertice %d la distancia mas corta = %d\n", inicial, i , distancia[ i ] );
        int destino = i;
        puts("\nY el El camino mas corto es ");
   		print( destino );
    	printf("\n\n");
    }

}

int main(){
    int E , origen, destino , peso , inicial;
    printf("Cuantos vectores: ");
    scanf("%d", &V);
    printf("\nCuantas aristas: ");
    scanf("%d" , &E );
    system("CLS");
    while( E-- ){
    	printf("Agrega los vectores adyacentes y la distancia(de la forma V1 V2 D): \n");
        scanf("%d %d %d" , &origen , &destino , &peso );
        ady[ origen ].push_back( Node( destino , peso ) ); 
        system("CLS");
    }
    printf("Ingrese el vertice inicial: ");
    scanf("%d" , &inicial );
    system("CLS");
    dijkstra( inicial );
    return 0;
    
}


