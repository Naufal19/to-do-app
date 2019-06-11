#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>

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
        for (int i = 5 ; i > 0; i--) {
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
    char x[20] ;
    status = 0;
    while (1)
    {
        cin.clear() ;
        cin.ignore() ;
        cout << ">> Bulan : "; cin.get(x,20);
        key = atof(x) ;
        if (key > 12 || key < 1)
        {
            cout << "Bulan tidak valid!\n Masukkan 1-12\n";
            system("PAUSE");
            system("CLS");
        } 
        else {
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
    char x[20] ;
    while (1)
    {
        cin.clear() ;
        cin.ignore() ;
        cout << ">> Minggu : "; cin.get(x,20);
        key = atof(x) ;
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
    char x[20] ;
    cout << "Todo : ";
    cin.clear() ;
    cin.ignore();
    getline(cin, pBaru->info);
    // cin >> pBaru->info;
    char key ;
    cout << "Masukkan Prioritas (Y/N) : " ; cin >> key ;
    if (key == 'y' || key == 'Y' ){
        cin.ignore() ;
        cout << "Prioritas : ";
        cin.get(x,20) ;
        int temp = atof(x) ;
        if (atof(x) <= 10 && atof(x) > 0 )
        {
            pBaru->prior = atof(x);
            pBaru->next = NULL;    
        }
        else
        {    
            cout << "Prioritas salah, input data kembali !\n" ;
            system("PAUSE") ;
            createTodoList(pBaru) ;
        }
        
    }
    else if (key == 'n' || key == 'N')
    {
        pBaru->prior = 7 ;
        pBaru->next = NULL ;
    }
    else
    {
        cout << "Input salah, ulangi !\n" ;
        createTodoList(pBaru) ;
    }
}

void insertPriorTodoList(pQueue& pBaru, pointerbulan& Bantu, int& status, pointerminggu& pMinggu) 
{
    pQueue pBantu = pMinggu->firstQ ;    
    pQueue pBantuPrev = pMinggu->firstQ ;
    
    if (status == 1) {
        if (pMinggu->firstQ == NULL && pMinggu->lastQ == NULL)
        {
            pMinggu->firstQ = pBaru ;
            pMinggu->lastQ = pBaru ;
        }
        else   
        {
            while (pBaru->prior >= pBantu->prior && pBantu->next != NULL){ //!pentinggg!!!
                pBantuPrev = pBantu;
                pBantu = pBantu->next ;
            }

            if (pBantu == pMinggu->firstQ && pBaru->prior <= pBantu->prior){
                //insert first
                pBaru->next = pBantu;
                pMinggu->firstQ = pBaru ;
            }
            else if (pBantu == pMinggu->lastQ && pBaru->prior > pBantu->prior){ 
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
void LinearSearchToDo (pointerminggu& pBantu0, pointerbulan& p, int& status,int& cekto ) {
    int info1 ;
    char x[20] ;
    cin.clear() ;
    cin.ignore() ;
    cout << "No Todo List : " ;
    cin.get(x,20) ;
    info1 = atof(x) ;
    
    pQueue pBantu, pQ ;
    pBantu = pBantu0->firstQ  ;

    status = 0 ;

    cout << p->months << " " << pBantu0->weeks << "\n" ;
        
        if (info1 != 0) {
            while (pBantu != NULL && status == 0)
            {
                if (info1 == pBantu->no ) {
                    status = 1 ;
                }
                else {
                    pBantu = pBantu->next ;
                }   
            }
        }
        else {
            cout << "Input Nomor !!\n" ;
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
                } 
        else {
                cout << "Data tidak ditemukan!" << endl ;
                cekto = 1 ;
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

void cetakAll(listbulan First, string fileName){
    pointerbulan pBantu;
    pointerminggu pCari;
    pQueue pq;
    pBantu = First;
    
    // ofstream saveFile;
    // saveFile.open(fileName);

    for (int i = 1; i <= 12; i++)
    {
        cout << "\nBulan : " << pBantu->months << endl << left;
        // saveFile << pBantu->months << endl;
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

        pCari = pBantu->firstminggu;
        while (pCari != NULL){
            if (pCari->firstQ != NULL)
            {
                pq = pCari->firstQ ;
                cout << setfill(' ') << "| Week-" << setw(41) << pCari->weeks << "|" << endl ;
                int j = 1;
                while (pq != NULL) {
                    pq->no = j;
                    cout    << setfill('-') << setw(6) 
                            << "+" << setw(30) 
                            << "+" << setw(12) 
                            << "+" << "+" << "\n";
                    cout    << "| " << setfill(' ') << pq->no << setw(3) << "."
                            << "| " << setw(28) << pq->info 
                            << "|     " << setw(6) << pq->prior 
                            << "|\n";
                    // saveFile    << pq->no << "\n" 
                    //             << pq->info << "\n"
                    //             << pq->prior << "\n";
                    pq = pq->next ;
                    j++;
                }
                cout    << setfill('-') << setw(6) 
                        << "+" << setw(30) 
                        << "+" << setw(12) 
                        << "+" << "+" << "\n";
            }
            pCari = pCari->nextminggu ;
            // saveFile << "." << endl;
        }
        // saveFile << ";" << endl;
        pBantu = pBantu->nextbulan;
    }
    // saveFile.close();
}

void save(listbulan First, string fileName){
    pointerbulan pBantu;
    pointerminggu pCari;
    pQueue pq;
    pBantu = First;
    
    ofstream saveFile;
    saveFile.open(fileName);

    for (int i = 1; i <= 12; i++)
    {
        saveFile << pBantu->months << endl;
        pCari = pBantu->firstminggu;
        while (pCari != NULL){
            if (pCari->firstQ != NULL)
            {
                pq = pCari->firstQ ;
                int j = 1;
                while (pq != NULL) {
                    pq->no = j;
                    saveFile    << pq->no << "\n" 
                                << pq->info << "\n"
                                << pq->prior << "\n";
                    pq = pq->next ;
                    j++;
                }
            }
            pCari = pCari->nextminggu ;
            saveFile << "." << endl;
        }
        // saveFile << ";" << endl;
        pBantu = pBantu->nextbulan;
    }
    saveFile.close();
}

int checkText(string fileName){
    ifstream fileku;
    fileku.open(fileName);
    if(fileku.fail()){
        cout << "Your file doesn't exist!" << endl;
        return 0;
    } else {
        cout << "Please wait, we're preparing your file!" << endl;
    }
    fileku.close();
}

void inputFromData(listbulan& First, string fileName){
    string  input,
            info;
    // listQ firstQ;
    string no;
    int prioritas;

    ifstream myFile;
    myFile.open(fileName);

    pointerbulan pBantu = First;
    for (int j = 1; j <= 12; j++){      //loop bulan
        myFile >> input; //read nama bulan
        // cout << input << endl; //read nama bulan
        
        pointerminggu pBantu2 = pBantu->firstminggu;
        for (int i = 1; i <= 5; i++) //loop minggu
        {

            // cout << "minggu-" << i << endl;
            // pQueue pBantu3 = pBantu2->firstQ;
            // cout << pBantu3 << endl;
            
            while (1) //loop todo =>> insert first
            {

                myFile >> no; 
                if (no == ".") break;
                int nomor = stoi(no);
                myFile.ignore();
                // myFile >> info;
                getline(myFile, info);
                // cout << info << endl;
                myFile >> prioritas; //ngambil todo di minggu pertama

                //!create element
                pQueue pBaru = new elementQ;
                pBaru->no = nomor;
                pBaru->info = info;
                pBaru->prior = prioritas;
                pBaru->next = NULL;
                //!-------------

                //!insert last
                if (pBantu2->firstQ == NULL)
                {
                    pBantu2->firstQ = pBaru;
                } else {
                    pQueue pBantu3 = pBantu2->firstQ;
                    while (pBantu3->next != NULL)
                    {
                        pBantu3 = pBantu3->next;
                    }
                    pBantu3->next = pBaru;
                }
                //!----------

                //!insertlastd
                // cout << pBantu3 << endl;
                // pQueue pBantuQ = pBantu3;

                //--------

                // cout << no << " " << info << " " << prioritas << endl;
                // cout << pBaru->no << " " << pBaru->info << " " <<
                //  pBaru->prior << endl;
                // cout << pBantu->firstminggu->firstQ->info << endl;
            }

            pBantu2 = pBantu2->nextminggu;
        }

        pBantu = pBantu->nextbulan;
    }
    myFile.close();
}

int main(int argc, char const *argv[])
{   
    listbulan first ;
    pointerbulan b ;
    
    firstminggu m ;
    pointerminggu pm ;
    
    pQueue pQ ;

    char x, 
        lagi,
        test[20]; 
    int key,
        status, 
        found,
        cekto,
        menu;

    string user  ;
    string password ;
    int p ; 
    
    do {
    cout << "\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" ;
    cout << "!! WELCOME TO ToDoApp.exe !!\n" ;
    cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" ;
    cout << "\n\t>> UserName : " ; cin >> user ;
    cout << "\t>> Password : " ; cin >> password ;
    cout << "\n" ;
    
    if (user == "eclipse2018" && password == "2018") {
        p =1 ;
        CreateList(first) ;
        Bulan(first,b) ;
        CreateWeek(m,first) ;

        string myFileName = "todoApp.txt";
        checkText(myFileName);
        inputFromData(first,myFileName) ;
        system("PAUSE");

        while (1)
        {    
            cin.clear() ;
            cin.ignore();       
            system("CLS");
            cout << "=================================\n" ;
            cout << "||  WELCOME TO THE TODO APP ! ||\n";
            cout << "=================================\n" ;
            cout << "---------MENU----------\n";
            cout << "1. Create To Do List\n" ;    
            cout << "2. Update To Do List\n" ;
            cout << "3. Delete To Do List\n" ;
            cout << "4. Show To Do List per Month\n" ;
            cout << "5. Show To Do List All\n" ;
            cout << "99. Save and Exit\n" ;
            cout << "------------------------\n";
            cout << "SELECT MENU : ";        

            cin.get(test,20);
            menu = atof(test) ;

            switch (menu)
            {
            case 1:
                system("CLS");
                cout << "=================================\n" ;
                cout << "=====|| CREATE TODO LIST ||=====\n";
                cout << "=================================\n" ;
                
                LinearSearchMonth(first,x,status,b);
                do
                {   
                    LinearSearchWeek(b,key,pm);
                    createTodoList(pQ);
                    insertPriorTodoList(pQ,b,status,pm);
                    system("CLS");
                    cout << "*********************************\n" ;
                    cout << "-----|| CREATE TODO LIST ||-----\n";
                    cout << "*********************************\n" ;
                    cetak(status,b,pm);
                    cout << "INPUT LAGI? (y/n) \n"; cin >> lagi;
                } while (lagi == 'y' || lagi == 'Y');
                save(first, myFileName);
                system("PAUSE");
                break;
            case 2:
                system("CLS");
                cout << "=================================\n" ;
                cout << "=====|| UPDATE TODO LIST ||=====\n";
                cout << "=================================\n" ;
                LinearSearchMonth(first,x,status,b);
                do
                {
                    system("CLS");
                    cout << "*********************************\n" ;
                    cout << "----|| UPDATE TODO LIST ||----\n";
                    cout << "*********************************\n" ;
                    cetak(status,b,pm) ;
                    LinearSearchWeek(b,key,pm);
                    LinearSearchToDo(pm,b,status,cekto);
                    system("CLS");
                    if(cekto == 1) {
                        cout << "Data Tidak Ada !\n" ;
                    }
                    else{
                        cetak(status,b,pm);
                        cout << "UPDATE LAGI? (y/n) \n"; cin >> lagi;
                    }
                } while (lagi == 'y' || lagi == 'Y');
                save(first, myFileName);
                system("PAUSE");
                break;
            case 3:
                system("CLS");
                cout << "=================================\n" ;
                cout << "=====|| DELETE TODO LIST ||=====\n";
                cout << "=================================\n" ;
                    LinearSearchMonth(first,x,status,b);
                    cetak(status,b,pm) ;
                    LinearSearchWeek(b,key,pm);
                    deleteQueue(status,b,pm);
                    system("PAUSE");
                    system("CLS");
                    cout << "*********************************\n" ;
                    cout << "------||DELETE TODO LIST||------\n";
                    cout << "*********************************\n" ;
                    cetak(status,b,pm);
                    save(first, myFileName);
                    system("PAUSE");
                break;
            case 4:
                system("CLS");
                cout << "=================================\n" ;
                cout << "==|| SHOW TODO LIST A MONTH ||==\n";
                cout << "=================================\n" ;
                LinearSearchMonth(first,x,status,b) ;
                cetak(status,b,pm) ;
                save(first, myFileName);
                system("PAUSE");
                break;
            case 5:
                system("CLS");
                cout << "=================================\n" ;
                cout << "===|| SHOW TODO LIST A YEAR||===\n";
                cout << "=================================\n" ;
                cetakAll(first, myFileName);
                save(first, myFileName);                
                system("PAUSE");
                break;
            case 99:
                system("CLS");
                save(first, myFileName);
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
    else 
        {
            system("CLS") ;
            cout << "####################\n" ;
            cout << "ACCESS DENIED !!\n" ; 
            cout << "####################\n" ;
            system("pause") ;
            system("CLS") ;
            p = 0 ;
        }
    } while (p == 0 ) ;
}