#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> //INT_MAX
#define BUFFER_LEN 4000
#define LEFT(i) 2*i + 1
#define RIGHT(i) 2*i + 2

//GLOBALI:
//var stringa d lunghezza variabile per memorizzare un comado (ricorda carattere terminatore \0 )
char buffer[BUFFER_LEN];
//var per memorizzare d = numero di nodi del grafo, k = quanti migliori grafi da stampare
int d = 0, k = 0;
int firstTopK = 0;
//intero per area matrice
int area = 0;
//buffer per matrici
//intero per lunghezza array dinamico
int sizeDijkstraResults = 0;
//vettore dinamico di interi risultato di compute Dijkstra-> l'intero etichetta corrisponde all'indice del vettore
/*array dei risultati di compute_Dijkstra :
      0 1 2  3  -> indici indicano quanti grafi sono stati letti prima
     [7,5,7,150] -> size 4
*/
typedef struct {
    int index;//memorizza numero di grafi letti prima
    int pathSum;//memorizza somma cammini minimi
} box;
box *allDijkstraResults;
int NGraphs = 0;//conta grafi letti
char* r=0;

//conversioni:

long toInt(char str[],int i)
{
    long n = 0;

    while (str[i] && (str[i] >= '0' && str[i] <= '9')){
        n = n * 10 + (str[i] - '0');
        i++;
    }

    return n;
}


//>>PARTE A :funzioni per aggiungiGrafo:

//invoco su tutti i grafi e salvo risultato in un array
/* quella che sarebbe un matrice in teoria è un vettore nella pratica
 * d=3
  [1,2,3] nodo 0 : 1 autoanello, peso 2 verso nodo 1, peso 3 verso nodo 2
  [4,5,6] nodo 1   etc.
  [7,8,9] nodo 2   etc.
*/
int compute_Dijkstra(int vector[area], int size) { //matrice passata come parametro in vettore

    //size == area = true;

    int source = 0; //nodo sorgente
    int cost[area]; //vettore dei costi dal vettore dei pesi( costo INF se peso 0)
    int distance[d]; //vettore che memorizza le distanze tra i vari nodi
    int visited[d];//tiene traccia dei nodi già  visitati nei vari path (source a 1 dall'inizio)
    //int prec[d];
    int counter = 0;
    int minDistance = 0;
    int nextNode = 0;
    int result = 0;//sennò quando ho nodi irraggiungibili nel fare la somma sfora e cicla a MIN_INT
    int rootiszero = 0;

    //source non connessa
    for (int i = 1; i < d; i++) {
        if (vector[i] == 0) {//cella 1 e 2 sono zero
            rootiszero++;
        }
    }

    if (rootiszero == d - 1) {
        //printf("result = %d\n", 0);
        return 0;//sommo infiniti?
    }


    //inizializzo i costi prendendoli dal vettore dei pesi
    for (int x = 0; x < area; x++) {

        if (vector[x] == 0) {
            cost[x] = INT_MAX;//no edge
        } else {
            cost[x] = vector[x];//edge
        }
    }


    //inizializzo la distanza tra il primo nodo e i nodi adiacenti
    for (int x = 0; x < d; x++) {

        distance[x] = cost[x];//init costo nodi adiacenti a source(se no edge INF)
        //prec[x] = source; //set nodo precedente a source
        visited[x] = 0; //segno tutti i nodi come non visitati (anche source che cambio dopo)

    }


    //inizializzo parametri primo nodo
    distance[source] = 0;//distanza da source
    visited[source] = 1;//ÃƒÂ¨ visitato perchè parto da qui
    counter = 1; // 1 nodo visitato



    //per ogni nodo da 1 a d-1
    while (counter < d - 1) {

        minDistance = INT_MAX;//init

        for (int x = 0; x < d; x++) {
            //se la distanza del nodo x da 0 è minore della minima computata e non l'ho visitato
            if (distance[x] < minDistance && !visited[x]) {
                minDistance = distance[x];//setta nuova distanza minima del nodo
                nextNode = x; //setto x come prossimo nodo da cui fare i controlli
            }

        }


        visited[nextNode] = 1;//nextNode lo sto visitando

        //aggiorno i costi dato il nuovo nodo (x + nextNode*3 scorre array a blocchi di 3 in base al nextNode come se fosse una matrice)
        /* d=3
          0<=x<3
          0  1  2
        0 [1,2,3] nodo 0  nextNode = 0; 0*3 + x
        1 [4,5,6] nodo 1  nextNode = 1; 1*3 + x
        2 [7,8,9] nodo 2  nextNode = 2; 2*3 + x
        */
        for (int x = 0; x < d; x++) {

            if (!visited[x] && cost[x + nextNode * d] != INT_MAX) {//se non ÃƒÂ¨ stato visitato


                if ((minDistance + cost[x + nextNode * d]) <
                    distance[x]) { //se la distanza minima più il costo corrispondente
                    // è minore di quello computato precedentemente
                    distance[x] = minDistance + cost[x + nextNode * d]; // aggiorno costo per arrivare al nodo x
                    //prec[x] = nextNode; //aggiorno nodo precedente per arrivarci
                }

            }

        }

        counter++;
    }



    //sommo cammini minimi da 0 ad un qualsiasi altro nodo memorizzati in distance[]
    for (int x = 0; x < d; x++) {
        if (distance[x] == INT_MAX) {
            result = result + 0;//salta nodo non raggiungibile
        } else {
            result = result + distance[x];
        }
    }


    /*printf("result = %u\n", result);

    for (int j = 0; j < d; j++) {
        printf("%d, \n", distance[j]);
    }*/

    return result;
}


void max_heapify(box a[], int heapsize, int pos) {
    int l = LEFT(pos);//left
    int r = RIGHT(pos);//right
    int posmax = pos;//min

    if (l < heapsize && a[l].pathSum > a[pos].pathSum) {
        posmax = l;
    }

    if (r < heapsize && a[r].pathSum > a[posmax].pathSum) {
        posmax = r;
    }

    if (posmax != pos) {
        box temp = a[pos];
        a[pos] = a[posmax];
        a[posmax] = temp;
        max_heapify(a, heapsize, posmax);
    }
}

void build_max_heap(box a[], int heapsize) {
    heapsize = k;
    for (int i = heapsize / 2 - 1; i >= 0; i--) {
        max_heapify(a, heapsize, i);//fa si che il sotto albertp con root in i sia un max-heap
    }

}



//salva grafo in array di lunghezza fissa dato dall'area della matrice di adiacenza d*d
void read_and_save_Graph() {

    area = d * d;
    int graph[area];
    int dijkstraResult;
    int j = 0, w=1,z=0;
    int loop=0;

    while (j < area) {

        z=0;//init

        //leggi d alla volta
        r=fgets(buffer,4000,stdin); //stp a \n, memo newline \n-->virgole!

        graph[j]=toInt(buffer,z);
        //printf("elem : %d\n",graph[j]);

        while (loop==0){

            //scorre parte del buffer
            while ((buffer[z] != ',')){
                if (buffer[z] != '\n') {
                    z++;
                    //printf("z : %d\n", z);
                }else{
                    //printf("loop : %d\n", loop);
                    loop=1;
                    break;
                }
            }

            if (loop==0) {
                //converte
                graph[w] = toInt(buffer, z + 1);//i indica l'inizio del nuovo numero
                //printf("elem : %d\n", graph[w]);

                z++;//salta virgola
                w++;
            }

        }

        loop=0;
        w++;
        j = j + d;
        //printf("j: %d, loop = %d\n", j,loop);

    }


    /*
    for (int i = 0; i < area; i++) {
        printf("%d,", graph[i]);
    }*/

    dijkstraResult = compute_Dijkstra(graph,area);//chiamata a funzione per calcolare la somma dei cammini minimi e salvre il risultato

    if (NGraphs<k){//da 0 a k-1
        //riempio l'array--> stesse inserzioni di prima
        allDijkstraResults[NGraphs].pathSum=dijkstraResult;
        allDijkstraResults[NGraphs].index=NGraphs;
    }else if (NGraphs==k){
        //una vola che ho riempito l'array costruisco lo heap una sola volta O(n*logn)--> al posto di merge sort
        build_max_heap(allDijkstraResults,k);
    }

    //dato il fatto che ho tutti i k elementi e costruito lo heap, per tutti i futuri valori
    if (NGraphs>=k){
        //se il valore è minore del primo (la root del max heap= valore massimo)
        if (dijkstraResult<allDijkstraResults[0].pathSum){
            //sovrascrivo il valore
            allDijkstraResults[0].pathSum=dijkstraResult;
            allDijkstraResults[0].index=NGraphs;
            //dato il fatto che è uno heap so che i sotto-alberi dx e sx della root sono max heap quindi posso chiamare max_heapify per ripristinare la proprietÃ  O(logn)--> al posto di merge sort
            max_heapify(allDijkstraResults,k,0);
        }
    }

    NGraphs++;//incremento il contatore (serve per gli sapere quanti grafi ho letto prima)

    //--non ho più bisogno di mergesort per sapere il più grande per il confronto e neanche per TopK
    //--no realloc :)

}


void aggiungiGrafo() {
    read_and_save_Graph();
}



//>>PARTE B: funzioni per TopK:


//stampa risultati tramite bestKGraphs come intero etichetta
void print_results_by_index() {
    int printable=0;


    //se ho meno grafi di k printo nquelli che ho
    if (NGraphs < k) {
        printable = NGraphs;
    } else {//NGraphs >= k
        //se ne ho >= k gli printo la classifica
        printable = k;
    }



    for (int i = 0; i < printable; i++) {
        if (i == printable - 1) {
            printf("%d\n", allDijkstraResults[i].index);
        } else {
            printf("%d ", allDijkstraResults[i].index);
        }
    }


}


void TopK() {
    print_results_by_index();
}


int main() { //testato fino a selezione dei comandi

    //legge interi d,k un'unica volta
    r=fgets(buffer, 4000, stdin);


    int i=0;

    while (buffer[i]!=' '){
        i++;
    }

    //printf("%d\n", i);

    d=toInt(buffer,0);
    k=toInt(buffer,i+1);

    //printf("d: %d, k =%d\n", d, k);


    //instantiate graphsChart : dimensione = k
    sizeDijkstraResults = k;
    allDijkstraResults = calloc(sizeDijkstraResults, sizeof(box));

    //legge comandi
    while (fgets(buffer, 4000, stdin)!=NULL) {

        char cmd = buffer[0];//leggo il primo carattere

        //identifica quale comando è stato inserito da stdin
        switch (cmd) {

            case 'A'://comando AggiungiGrafo

                //chiama aggiungiGrafo
                aggiungiGrafo();

                firstTopK = 1;

                break;

            case 'T': //cmando TopK

                if (firstTopK == 1) {//se non è la prima TopK
                    //chiama TopK
                    TopK();
                } else {
                    printf("\n");
                }

                break;

            default:
                break;

        }

    }

    free(allDijkstraResults);
    //printf("\n");

    return 0;
}


