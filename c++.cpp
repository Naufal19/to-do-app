#include <iostream>
using namespace std ;

struct minggu {
    int weeks ;
    char isi[1000] ;
    minggu* nextminggu ;
};

struct bulan {
    string months ;
    bulan* nextbulan ;
    minggu* firstminggu ;    
};

typedef bulan* listbulan ;
typedef bulan* pointerbulan ;
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

// Create and Insert Week
void CreateWeek (pointerminggu& pBaru, listbulan& First) {
    pointerbulan p;
    p = First ;

    while (p != NULL) {
 
        for (int i = 0 ; i < 5; i++) {
            //create
            pBaru = new minggu ;
            pBaru->weeks = i+1 ;
            pBaru->nextminggu = NULL ;
                
                // insert
            	if (p->firstminggu == NULL){
			        cout << i+1 ;
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

// Searching
void LinearSearch(listbulan& First, string key, int &status, pointerbulan &pBantu){
    pBantu = First;
    status = 0;
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->months == key){
            cout << "Ditemukan " ;
            status = 1;
        }
        else
            pBantu = pBantu->nextbulan;
    }
}

// Show Weeks Whit Key
void ShowWeeks (listbulan First) {
    pointerbulan pBantu ;
    string key ; int status ;

    cout << ":: " ; cin >> key ;

    LinearSearch(First,key,status,pBantu) ;
    

    if (status == 1) {
        while (pBantu->firstminggu != NULL) {
            cout << pBantu->firstminggu->weeks  ;
            pBantu->firstminggu = pBantu->firstminggu->nextminggu ;
        }  
    }
    else
    {
        cout << "Bulan tidak tersedia, Ulangi ! " ;
        LinearSearch(First,key,status,pBantu) ;
    }
    
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



int main(int argc, char const *argv[])
{   
    listbulan first ;
    pointerbulan b ;
    string x ;
    pointerminggu m ;
    
    //Month Lists
    CreateList(first) ;
    Bulan(first,b) ;

    cout << "1. Create Week\n" ;
    cout << "2. Create To Do List\n" ;    
    cout << "3. Delete To Do List\n" ;
    cout << "4. Show To Do List\n" ;

}
