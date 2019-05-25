#include <iostream>
using namespace std ;

struct elementQ
{
    string info;
    int prior;
    elementQ *next;
 
};

struct minggu {
    int weeks ;
    char jumlah[10] ;
    minggu* nextminggu ;
    elementQ* firstQ ;
    elementQ *lastQ ;  
};

struct bulan {
    string months ;
    bulan* nextbulan ;
    minggu* firstminggu ;    
};

typedef elementQ *pQueue;
typedef bulan* listbulan ;
typedef bulan* pointerbulan ;
typedef minggu* firstminggu ;
typedef minggu* pointerminggu ;

// Create List
void CreateList(listbulan &First){
    First = NULL;
}

// Insert Main List
void CreateMonth(listbulan& First,pointerbulan& pBaru, string x){ 
    pBaru = new bulan;
    pBaru->months = x ;

    pBaru->nextbulan = NULL;
    pBaru->firstminggu = NULL;
    

    if (First == NULL) {
        First = pBaru;
    } 
    else {
        pBaru->nextbulan = First ; 
        First = pBaru ;
    }
}

void Bulan(listbulan& First, pointerbulan& pBaru) {
    CreateMonth(First, pBaru,"Desember");
    CreateMonth(First, pBaru,"November");
    CreateMonth(First, pBaru,"Oktober");
    CreateMonth(First, pBaru,"September");
    CreateMonth(First, pBaru,"Agustus");
    CreateMonth(First, pBaru,"Juli");
    CreateMonth(First, pBaru,"Juni");
    CreateMonth(First, pBaru,"Mei");
    CreateMonth(First, pBaru,"April");
    CreateMonth(First, pBaru,"Maret");
    CreateMonth(First, pBaru,"Februari");
    CreateMonth(First, pBaru,"Januari");
}

// Show Month
void ShowMainList (listbulan First) {
    pointerbulan pBantu ;
    pBantu = First ;
    while (pBantu != NULL) {
        cout << pBantu->months << " ";
        pBantu = pBantu->nextbulan ;
    }   
}

// Create and Insert Week
void CreateWeek (firstminggu& pBaru, listbulan& First) {
    pointerbulan p ;
    p = First ;
    while (p != NULL) {
        for (int i = 0 ; i < 5; i++) {
            //create
            pBaru = new minggu ;
            pBaru->weeks = i+1 ;
            pBaru->nextminggu = NULL ;
            pBaru->firstQ = NULL ;   
            pBaru->lastQ = NULL ;  
                // insert
            	if (p->firstminggu == NULL){
                    p->firstminggu = pBaru ;
		        }
		        else {
                    pBaru->nextminggu = p->firstminggu ;
                    p->firstminggu = pBaru ;
                }
        }
        // next month
        p = p->nextbulan ;
    }
}

void LinearSearchMonth(listbulan& First, string key, int &status, pointerbulan& pBantu){
    pBantu = First;
    status = 0;
    cout << "Bulan ? "; 
    cin >> key ;
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->months == key) {
            cout << "Ditemukan " ;
            status = 1;
        }
        else{
            pBantu = pBantu->nextbulan;
        }
    }
}

void LinearSearchWeek(pointerbulan& First, int& key, pointerminggu &pBantu){
    cout << "Minggu ke ? " ;cin >> key ;
    pBantu = First->firstminggu ;
    int status = 0;
    cout << First->months ;
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->weeks == key){
            cout << "Ditemukan " ;
            status = 1;
        }
        else
            pBantu = pBantu->nextminggu ;
    }
    cout << "\n==============\n" ;
    cout << First->months << ", Minggu ke " << pBantu->weeks ;
}


void createTodoList(pQueue &pBaru)
{
    pBaru = new elementQ;

    cout << "Info : ";
    cin >> pBaru->info;
    cout << "Prioritas : ";
    cin >> pBaru->prior;
    pBaru->next = NULL;
}

void insertPriorTodoList(pQueue& pBaru, pointerbulan& Bantu, int& status, pointerminggu& pMinggu) 
{
    pQueue pBantu = pMinggu->firstQ ;    
    pQueue pBantuPrev = pMinggu->firstQ ;
    
    if (status == 1) {
        if (pMinggu->firstQ == NULL)
        {
            cout << "x" ;
            pMinggu->firstQ = pBaru ;
            pMinggu->lastQ = pBaru ;
        }
        else   
        {
            while (pBaru->prior > pBantu->prior && pBantu->next != NULL){ //!pentinggg!!!
                pBantuPrev = pBantu;
                pBantu = pBantu->next ;
            }
                if (pBantu == pMinggu->firstQ && pBaru->prior < pBantu->prior){
                    //insert first
                    pBaru->next = pBantu;
                    pMinggu->firstQ = pBaru ;
                }
                else if (pBantu == pMinggu->lastQ && pBaru->prior > pBantu->prior){ 
                    //insert last
                    pBantu->next = pBaru;
                    pMinggu->lastQ = pBaru;
                }
                else{
                    //insert before pBantu
                    pBantuPrev->next = pBaru ;
                    pBaru->next = pBantu ;
                }
            cout << "Berhasil di input!" << endl;
        }
    }
}

// MASIH BUG !!
void LinearSearchToDo (pointerminggu& pBantu0, pointerbulan& p, int& status) {
    string info1 ;
    cout << "Cari To Do List : " ;
    cin >> info1 ;
    
    firstminggu pBantu ;
    pBantu = pBantu0  ;

    status = 0 ;

    cout << p->months << " " << pBantu->weeks << "\n" ;
    while (pBantu->firstQ != NULL && status == 0)
    {
        if (info1 == pBantu->firstQ->info ) {
            cout << "Ada\n" ;
            status = 1 ;
        }
        else {
            pBantu->firstQ = pBantu->firstQ->next ;
        }   
    }
}

void cetak (int& status, listbulan& pBulan, pointerminggu& pCari0) {
    pQueue pq ;
    firstminggu pCari ;
    pCari = pBulan->firstminggu ;

    cout << pBulan->months ;
    if (status == 1)
    {
        cout << endl ;
        for(int i = 0 ; i < 5 ; i++) {
            /* code */  
            pq = pCari->firstQ ;
            cout << "Minggu : " << pCari->weeks << endl ;
            while (pq != NULL) {
                /* code */
                cout << "\t"<< pq->info << " " << pq->prior << endl ;
                pq = pq->next ;
            }
            pCari = pCari->nextminggu ;
        }
    }
    
}

void deleteQueue(int& status, pointerbulan& pBulan, pointerminggu& pMinggu)
{
    pQueue pHapus ;
    if (status == 1)
    {
        if (pMinggu->firstQ == NULL && pMinggu->lastQ == NULL)
        {
            cout << "\n\t***List Kosong!***" << endl;
        }
        else
        {
            pHapus = pMinggu->firstQ ;
            pMinggu->firstQ = pMinggu->firstQ->next;
            pHapus->next = NULL ;
            cout << "\n\t***List yang dihapus adalah " << pHapus->info << "***" << endl;
        }
    }
    else
    {
        cout << "Coba lagi" ;
    }
}


int main(int argc, char const *argv[])
{   
    listbulan first ;
    pointerbulan b ;
    
    firstminggu m ;
    pointerminggu pm ;
    
    pQueue pQ ;

    string x ; 
    int key ;
    int status ;
    int found ;
    //Month Lists
    CreateList(first) ;
    Bulan(first,b) ;
    CreateWeek(m,first) ;

    cout << "1. Create To Do List\n" ;    
    cout << "2. Delete To Do List\n" ;
    cout << "3. Show To Do List\n" ;

    cout << "\nMENU DIATAS GA GUNA\n" ;
    
    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    createTodoList(pQ) ;
    insertPriorTodoList(pQ,b,status,pm) ;


    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    createTodoList(pQ) ;
    insertPriorTodoList(pQ,b,status,pm) ;

    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    createTodoList(pQ) ;
    insertPriorTodoList(pQ,b,status,pm) ;

    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    createTodoList(pQ) ;
    insertPriorTodoList(pQ,b,status,pm) ;

    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    createTodoList(pQ) ;
    insertPriorTodoList(pQ,b,status,pm) ;

    cout << "\n==punten mau nampilin data==\n" ;
    LinearSearchMonth(first,x,status,b) ;
    cetak(status,b,pm) ;

    cout << "\n==punten mau ngapus data==\n" ;
    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    deleteQueue(status,b,pm) ;
    cetak(status,b,pm) ;

    
    cout << "\n==punten mau ngapus data lagi==\n" ;
    LinearSearchMonth(first,x,status,b) ;
    LinearSearchWeek(b,key,pm) ;
    deleteQueue(status,b,pm) ;
    cetak(status,b,pm) ;
        
}