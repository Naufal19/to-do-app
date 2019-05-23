#include <iostream>
using namespace std ;

// struct isi {
//     string todo ;
//     isi* nexttodo ;
// };

struct minggu {
    int weeks ;
    char jumlah[10] ;
    minggu* nextminggu ;
    // isi* firsttodo ;
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

// Search Month
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

// Search Week
void LinearSearchWeek(pointerbulan& First, int key, int &status, pointerminggu &pBantu){
    pBantu = First->firstminggu ;
    status = 0;
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->weeks == key){
            cout << "Ditemukan " ;
            status = 1;
        }
        else
            pBantu = pBantu->nextminggu ;
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

// void CreateToDoList (pointerisi ToDo, pointerminggu& p) {
//     // int x,y, status ;
//     // pointerbulan pBantu ;
//     // cout << "Minggu ke ? " ; cin >> y ;
//     //     LinearSearchWeek(pBantu,y,status,p) ;

//     // if (status) {
//     //     cout << "Jumlah To Do List : " ; cin >> x ;    
//     //     cin.ignore() ;
//     //     for (int i = 0; i < x ; i++) {
//     //         // Create ToDo
//     //         ToDo = new isi ;
//     //         cout << i << ". " ; getline(cin,ToDo->todo) ;
//     //         ToDo->nexttodo = NULL ;

//     //         // Insert Todo 

//     //     }
        
// }




int main(int argc, char const *argv[])
{   
    listbulan first ;
    pointerbulan b ;
    string x ;
    pointerminggu m ;
    
    //Month Lists
    CreateList(first) ;
    Bulan(first,b) ;

    cout << "1. Create To Do List\n" ;    
    cout << "2. Delete To Do List\n" ;
    cout << "3. Show To Do List\n" ;
    
    ShowMainList(first) ;

}