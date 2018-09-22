#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <vector>

using namespace std ;

static int OneN = 0 ;
static int TwoN = 0 ;
static int ThreeN = 0 ;
static int Count = 0 ;
static int Number = 1 ;
static bool jump = false ;

void Print( vector<int> dataBase, int functionN ) {
    cout << "[" << Number << "] : " ;
    Number ++ ;
    for ( int i = 0 ; i < functionN ; i ++ ) cout << dataBase[i]<< " " ;
    cout << endl ;
    Count ++ ;
} // Print()

vector<int> Rotate( vector<int> tempData, int times, int digit, int functionN ) {
    int tempInt = tempData[times] ;
    for( int move = times ; move > digit ; move -- ) tempData[move] = tempData[move-1] ;
    tempData[digit] = tempInt ;
    return tempData ;
} // Rotate()

void Perm( vector<int> dataBase, int digit, int functionN ) {
    if (  digit < functionN ) {
        for ( int times = digit ; times < functionN ; times ++ ) {
            vector<int> tempData ;
            tempData.assign( dataBase.begin(), dataBase.end() ) ;
            Perm( Rotate( tempData, times, digit, functionN ) , digit + 1, functionN ) ;
        } // for()
    } // if()

    else {
        Print( dataBase, functionN ) ;
    } // else()
} // Perm()

void LesserThan() {
    vector<int> dataBase ;
    dataBase.clear() ;
    for ( int i = 1 ; i <= OneN ; i ++ ) dataBase.push_back(i) ;
    Perm( dataBase, 0, OneN ) ;
    cout << "Layers = " << OneN << endl ;
    cout << "Result count = " << Count << endl ;
} // LesserThan()

void GivenN() {
    vector<int> dataBase ;
    int elements = 0 ;

    for ( int i = 0 ; i < TwoN ; i ++ ) {
        cin >> elements ;
        dataBase.push_back( elements ) ;
    } // for()

    Perm( dataBase, 0, TwoN) ;
} // GivenN()

void GivenLength( vector<int> & dataBase, int layer ) {
    if ( layer != ThreeN - 1 ) {
        while ( dataBase[0] <= 10 - ThreeN ) {
              while ( dataBase[layer] > layer + 10 - ThreeN && layer > 0 ) { // 位數往上
                layer -- ;
                dataBase[layer] ++ ;
                for ( int time = layer ; time < ThreeN ; time ++ ) dataBase[time+1] = dataBase[time] + 1 ;
              } // while

              GivenLength( dataBase, layer + 1 ) ;
              dataBase[layer] ++ ;
              for ( int time = layer ; time < ThreeN ; time ++ ) dataBase[time+1] = dataBase[time] + 1 ;
        } // while()
    } // if()

    else if( layer == ThreeN - 1 ) {
        Perm( dataBase, 0, ThreeN ) ;

        while ( dataBase[layer] < 9 ) {
            dataBase[layer] ++ ;
            Perm( dataBase, 0, ThreeN ) ;
        } // while()
    } // if()
} //GivenLength()

int main( int argc, const char * argv[] ) {
    int command = 0 ;
    char continueOrNot = '\0' ;

    cout << "*******************************************" << endl ;
    cout << "*******     Permutation Practice      *****" << endl ;
    cout << "******* 0 : Quit                      *****" << endl ;
    cout << "******* 1 : N numbers from 1 ... 9    *****" << endl ;
    cout << "******* 2 : N numbers from user input *****" << endl ;
    cout << "******* 3 : N numbers from 1 ... 9    *****" << endl ;
    cout << "*******************************************" << endl ;

    do {

        cout << endl << "Please enter your choice :" << endl ;
        cin >> command ;

        while ( command > 3 || command < 0 ) {
            cout << "Error command! please enter an acceptable command :" << endl ;
            cin >> command ;
        } // while()

        if ( command == 0 ) {
            cout << "Bye :((((" << endl ;
            return 0 ;
        } // if()

        if ( command == 1 ) {
            cout << "Please enter your N ( 1~9 ) :" << endl ;
            cin >> OneN ;

            while ( OneN <= 0 || OneN > 9 ) {
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> OneN ;
            } // while()

            clock_t time ;
            time = clock() ;
            LesserThan() ;
            time = clock() - time ;
            cout << "Time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ;
        } // if()
        else if ( command == 2 ) {
            cout << "Please enter your N ( 1~9 ) :" << endl ;
            cin >> TwoN ;

            while ( TwoN <= 0 || TwoN > 9 ) {
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> TwoN ;
            } // while()

            clock_t time ;
            time = clock() ;
            GivenN() ;
            time = clock() - time ;
            cout << "Time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ;
        } // if()
        else if ( command == 3 ) {
            cout << "Please enter your N ( 1~9 ) :" << endl ;
            cin >> ThreeN ;

            while ( ThreeN <= 0 || ThreeN > 9 ) {
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> ThreeN ;
            } // while()

            vector<int> dataBase;
            for ( int i = 1 ; i <= ThreeN ; i ++ ) dataBase.push_back(i) ;
            GivenLength( dataBase, 0 ) ;
        } // if()

        cout << "Do you want to practice again? (Y/N)" << endl ;
        cin >> continueOrNot ;

        while( continueOrNot != 'Y' && continueOrNot != 'y' && continueOrNot != 'N' && continueOrNot != 'n' ) {
            cout << "Error command! please enter an acceptable command :" << endl ;
            cin >> continueOrNot ;
        } // while()

        Count = 0 ;
        Number = 1 ;

    } while( continueOrNot == 'Y' || continueOrNot == 'y' ) ;

    cout << "Bye :(((" ;
}
