#include <iostream>
// #include <string.h>
#include <iomanip>
using namespace std;

struct elementQ
{
    string info;
    int prior;
    int no;
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
    int monthKode ;
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
void CreateMonth(listbulan& First,pointerbulan& pBaru, string x, int num){ 
    pBaru = new bulan;
    pBaru->months = x ;
    pBaru->monthKode = num ;

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
    CreateMonth(First, pBaru,"Desember", 12);
    CreateMonth(First, pBaru,"November",11);
    CreateMonth(First, pBaru,"Oktober",10);
    CreateMonth(First, pBaru,"September",9);
    CreateMonth(First, pBaru,"Agustus",8);
    CreateMonth(First, pBaru,"Juli",7);
    CreateMonth(First, pBaru,"Juni",6);
    CreateMonth(First, pBaru,"Mei",5);
    CreateMonth(First, pBaru,"April",4);
    CreateMonth(First, pBaru,"Maret",3);
    CreateMonth(First, pBaru,"Februari",2);
    CreateMonth(First, pBaru,"Januari",1);
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
        for (int i = 6 ; i > 0; i--) {
            //create
            pBaru = new minggu ;
            pBaru->weeks = i;
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

void LinearSearchMonth(listbulan& First, int key, int &status, pointerbulan& pBantu){
    pBantu = First;
    status = 0;
    while (1)
    {
        cout << "Bulan : "; cin >> key;
        if (key > 12 || key < 1)
        {
            cout << "Bulan tidak valid!\n Masukkan 1-12\n";
        } else {
            break;
        }
    }
    
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->monthKode == key) {
            // cout << pBantu->months << " ditemukan!\n" ;
            status = 1;
        }
        else{
            pBantu = pBantu->nextbulan;
        }
    }
}

void LinearSearchWeek(pointerbulan& First, int& key, pointerminggu &pBantu){
    while (1)
    {
        cout << "\nMinggu : "; cin >> key;
        if (key > 5 || key < 1)
        {
            cout << "Minggu tidak valid!\n Masukkan 1-5\n";
        } else {
            break;
        }
    }
    pBantu = First->firstminggu;
    int status = 0;
    while (pBantu != NULL && status == 0)
    { //!ketemu
        if (pBantu->weeks == key){
            // cout << "ditemukan!" ;
            status = 1;
        }
        else
            pBantu = pBantu->nextminggu ;
    }
    
    cout << "==============\n" ;
    cout << First->months << ", Minggu ke-" << pBantu->weeks << "\n";
}


void createTodoList(pQueue &pBaru)
{
    pBaru = new elementQ;

    cout << "Todo : ";
    cin.ignore();
    getline(cin, pBaru->info);
    // cin >> pBaru->info;
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
            pMinggu->firstQ = pBaru ;
            pMinggu->lastQ = pBaru ;
        }
        else   
        {
            while (pBaru->prior < pBantu->prior && pBantu->next != NULL){ //!pentinggg!!!
                pBantuPrev = pBantu;
                pBantu = pBantu->next ;
            }
            if (pBantu == pMinggu->firstQ && pBaru->prior > pBantu->prior){
                //insert first
                pBaru->next = pBantu;
                pMinggu->firstQ = pBaru ;
            }
            else if (pBantu == pMinggu->lastQ && pBaru->prior < pBantu->prior){ 
                //insert last
                pBantu->next = pBaru;
                pMinggu->lastQ = pBaru;
            }
            else {
                //insert before pBantu
                pBantuPrev->next = pBaru ;
                pBaru->next = pBantu ;
            }
        }
        cout << "Berhasil di input!\n" << endl;
    }
}

// MASIH BUG !!
void LinearSearchToDo (pointerminggu& pBantu0, pointerbulan& p, int& status) {
    int info1 ;
    cout << "No Todo List : " ;
    cin >> info1 ;
    
    pQueue pBantu, pQ ;
    pBantu = pBantu0->firstQ  ;

    status = 0 ;

    cout << p->months << " " << pBantu0->weeks << "\n" ;
    while (pBantu != NULL && status == 0)
    {
        if (info1 == pBantu->no ) {
            status = 1 ;
        }
        else {
            pBantu = pBantu->next ;
        }   
    }

    if (status == 1) {
        cout << "Data ditemukan!" << endl;
        pQ = new elementQ;
        cout << "Info : ";
        cin.ignore();
        getline(cin, pQ->info);
        pQ->next = NULL;
        swap (pQ->info, pBantu->info);
        cout << "Data berhasil diupdate!" << endl;
    } else {
        cout << "Data tidak ditemukan!" << endl;
    }
}

void cetak (int& status, listbulan& pBulan, pointerminggu& pCari0) {
    pQueue pq ;
    firstminggu pCari;
    cout << "Bulan : ";
    pCari = pBulan->firstminggu;

    cout << pBulan->months ;
    if (status == 1)
    {
        cout << endl << left;
        cout    << setfill('-') << setw(6) 
                << "+" << setw(30) 
                << "+" << setw(12) 
                << "+" << "+" << "\n";
        cout << "|" << setw(5) << " No. " << setfill(' ')
                    << setw(30) << "| Deskripsi" 
                    << setw(12) << "| Prioritas" 
                    << "|\n";
        cout    << setfill('-') << setw(6) 
                << "+" << setw(30) 
                << "+" << setw(12) 
                << "+" << "+" << "\n";
        while (pCari != NULL){
            if (pCari->firstQ != NULL)
            {
                pq = pCari->firstQ ;
                cout << setfill(' ') << "| Week-" << setw(41) << pCari->weeks << "|" << endl ;
                int i = 1;
                while (pq != NULL) {
                    pq->no = i;
                    cout    << setfill('-') << setw(6) 
                            << "+" << setw(30) 
                            << "+" << setw(12) 
                            << "+" << "+" << "\n";
                    cout    << "| " << setfill(' ') << pq->no << setw(3) << "."
                            << "| " << setw(28) << pq->info 
                            << "|     " << setw(6) << pq->prior 
                            << "|\n";
                    pq = pq->next ;
                    i++;
                }
                cout    << setfill('-') << setw(6) 
                        << "+" << setw(30) 
                        << "+" << setw(12) 
                        << "+" << "+" << "\n";
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
            cout << "Tidak ada yang dapat dihapus!" << endl;
        }
        else
        {
            pHapus = pMinggu->firstQ ;
            pMinggu->firstQ = pMinggu->firstQ->next;
            pHapus->next = NULL ;
            cout << "List berhasil dihapus" << endl;
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

    char x, 
        lagi; 
    int key,
        status, 
        found,
        menu;
    //Month Lists
    CreateList(first) ;
    Bulan(first,b) ;
    CreateWeek(m,first) ;

    while (1)
    {   
        system("CLS");
        cout << "WELCOME TO THE TODO LIST APP!\n";
        cout << "---------MENU----------\n";
        cout << "1. Create To Do List\n" ;    
        cout << "2. Update To Do List\n" ;
        cout << "3. Delete To Do List\n" ;
        cout << "4. Show To Do List\n" ;
        cout << "0. Exit\n" ;
        cout << "------------------------\n";
        cout << "SELECT MENU : "; cin >> menu;

        switch (menu)
        {
        case 1:
            system("CLS");
            cout << "----|| CREATE TODO LIST ||----\n";
            LinearSearchMonth(first,x,status,b);
            do
            {   
                LinearSearchWeek(b,key,pm);
                createTodoList(pQ);
                insertPriorTodoList(pQ,b,status,pm);
                system("CLS");
                cout << "----|| CREATE TODO LIST ||----\n";
                cetak(status,b,pm);
                cout << "INPUT LAGI? (y/n) \n"; cin >> lagi;
            } while (lagi == 'y' || lagi == 'Y');
            system("PAUSE");
            break;
        case 2:
            system("CLS");
            cout << "----|| UPDATE TODO LIST ||----\n";
            LinearSearchMonth(first,x,status,b);
            
            do
            {
                system("CLS");
                cout << "----|| UPDATE TODO LIST ||----\n";
                cetak(status,b,pm) ;
                LinearSearchWeek(b,key,pm);
                LinearSearchToDo(pm,b,status);
                system("CLS");
                cetak(status,b,pm);
                cout << "UPDATE LAGI? (y/n) \n"; cin >> lagi;
            } while (lagi == 'y' || lagi == 'Y');
            system("PAUSE");
            break;
        case 3:
            system("CLS");
            cout << "DELETE TODO LIST\n";
                LinearSearchMonth(first,x,status,b);
                cetak(status,b,pm) ;
                LinearSearchWeek(b,key,pm);
                deleteQueue(status,b,pm);
                system("PAUSE");
                system("CLS");
                cout << "DELETE TODO LIST\n";
                cetak(status,b,pm);
                system("PAUSE");
            break;
        case 4:
            system("CLS");
            cout << "SHOW TODO LIST\n";
            LinearSearchMonth(first,x,status,b) ;
            cetak(status,b,pm) ;
            system("PAUSE");
            break;
        case 0:
            system("CLS");
            cout << "HAVE A GREAT DAY!\n";
            system("PAUSE");
            return 0;
            break;
        default:
            cout << "MENU TIDAK TERSEDIA!\n";
            system("PAUSE");
            break;
        }
    }
}