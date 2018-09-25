// 10627130 資工二甲 林冠良 & 10627131 資工二甲 李峻瑋
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

void Print( vector<int> dataBase, int functionN ) { // print out the dataBase
    cout << "[" << Number << "] : " ;
    Number ++ ;
    for ( int i = 0 ; i < functionN ; i ++ ) cout << dataBase[i]<< " " ; // print it out one by one and increase the index
    cout << endl ;
    Count ++ ;
} // Print()

vector<int> Rotate( vector<int> tempData, int times, int digit, int functionN ) { // rotate the the position of the given range
    int tempInt = tempData[times] ; // store the data we want
    for( int move = times ; move > digit ; move -- ) tempData[move] = tempData[move-1] ; // swap the places
    tempData[digit] = tempInt ; // restore the data back
    return tempData ; // return the rotated dataBase
} // Rotate()

void Perm( vector<int> dataBase, int digit, int functionN ) { // find out the rank of the given dataBase
    if (  digit < functionN ) {
        for ( int times = digit ; times < functionN ; times ++ ) {
            vector<int> tempData ; // create a temporary dataBase
            tempData.assign( dataBase.begin(), dataBase.end() ) ; // copy the current dataBase to the temporary one
            Perm( Rotate( tempData, times, digit, functionN ) , digit + 1, functionN ) ; // throw into Rotate() to find out the rank
        } // for()
    } // if()

    else {
        Count ++ ;
        // Print( dataBase, functionN ) ; // after the rank has find out, print it out
    } // else()
} // Perm()

void LesserThan() {
    vector<int> dataBase ; // create the dataBase
    dataBase.clear() ; // clear the dataBase
    for ( int i = 1 ; i <= OneN ; i ++ ) dataBase.push_back(i) ; // store the data in
    Perm( dataBase, 0, OneN ) ; // perm it
    cout << "Layers = " << OneN << endl ; // print out recursion counts
    cout << "Result count = " << Count << endl ; // print out result counts
} // LesserThan()

void GivenN() {
    vector<int> dataBase ;
    int elements = 0 ;
    cout << "Please enter " << TwoN << " element(s)" << endl ;

    for ( int i = 0 ; i < TwoN ; i ++ ) {
        cin >> elements ; // read what user input
        dataBase.push_back( elements ) ; // push it back one by one
    } // for()
    // print out the time
    Perm( dataBase, 0, TwoN ) ; // perm it
} // GivenN()

void GivenLength( vector<int> & dataBase, int layer ) {
    if ( layer != ThreeN - 1 ) {
        while ( dataBase[0] <= 10 - ThreeN ) { // this god damn while took us two days !!!
              while ( dataBase[layer] > layer + 10 - ThreeN && layer > 0 ) {
                layer -- ; // jump back a layer
                dataBase[layer] ++ ; // increase the current layer
                for ( int time = layer ; time < ThreeN ; time ++ ) dataBase[time+1] = dataBase[time] + 1 ; // set up the data after the current layer
              } // while

              GivenLength( dataBase, layer + 1 ) ; // recursion
              dataBase[layer] ++ ; // increase the current layer
              for ( int time = layer ; time < ThreeN ; time ++ ) dataBase[time+1] = dataBase[time] + 1 ; // set up after increase the current layer
        } // while()
    } // if()

    else if( layer == ThreeN - 1 ) { // arrived at the last layer
        Perm( dataBase, 0, ThreeN ) ; // perm it

        while ( dataBase[layer] < 9 ) {
            dataBase[layer] ++ ; // and increase the last element in the dataBase
            Perm( dataBase, 0, ThreeN ) ; // perm it again
        } // while()
    } // if()
} //GivenLength()

int main( int argc, const char * argv[] ) {
    int command = 0 ;
    char continueOrNot = '\0' ;

    cout << "*******************************************" << endl ; // welcome message
    cout << "*******     Permutation Practice      *****" << endl ;
    cout << "******* 0 : Quit                      *****" << endl ;
    cout << "******* 1 : N numbers from 1 ... 9    *****" << endl ;
    cout << "******* 2 : N numbers from user input *****" << endl ;
    cout << "******* 3 : N numbers from 1 ... 9    *****" << endl ;
    cout << "*******************************************" << endl ;

    do {

        cout << endl << "Please enter your choice :" << endl ;
        cin >> command ; // read in user command

        while ( command > 3 || command < 0 ) { //wrong command situation
            cout << "Error command! please enter an acceptable command :" << endl ;
            cin >> command ;
        } // while()

        if ( command == 0 ) { // bye :(((
            cout << "Bye :(((" << endl ;
            return 0 ;
        } // if()

        if ( command == 1 ) { // function one
            cout << "Please enter your N ( 1~12 ) :" << endl ;
            cin >> OneN ; // read in the N

            while ( OneN <= 0 || OneN > 13 ) { // wrong N situation
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> OneN ;
            } // while()

            clock_t time ; // create a time variable
            time = clock() ; // start the timer
            LesserThan() ; // run the function
            time = clock() - time ; // get the precise time
            cout << "Time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
        } // if()
        else if ( command == 2 ) { // function two
            cout << "Please enter your N ( 1~12 ) :" << endl ;
            cin >> TwoN ; // read in the N

            while ( TwoN < 1 || TwoN > 13 ) { // wrong N situation
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> TwoN ;
            } // while()

            clock_t time ; // create a time variable
            time = clock() ; // start the timer
            GivenN() ; // run the function
            time = clock() - time ; // get the precise time
            cout << "Time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
        } // if()
        else if ( command == 3 ) { // function two
            cout << "Please enter your N ( 1~12 ) :" << endl ;
            cin >> ThreeN ; // read in the N

            while ( ThreeN <= 0 || ThreeN > 13 ) { // wrong N situation
                cout << "Error N! please enter an acceptable N :" << endl ;
                cin >> ThreeN ;
            } // while()

            vector<int> dataBase;
            for ( int i = 1 ; i <= ThreeN ; i ++ ) dataBase.push_back(i) ;
            clock_t time ; // create a time variable
            time = clock() ; // start the timer
            GivenLength( dataBase, 0 ) ; // run the function
            time = clock() - time ; // get the precise time
            cout << "Time = " << time * 1000 / CLOCKS_PER_SEC << " ms" << endl ; // print out the time
        } // if()

        cout << "Do you want to practice again? (Y/N)" << endl ; // print again message
        cin >> continueOrNot ; // read in yes or no

        while( continueOrNot != 'Y' && continueOrNot != 'y' && continueOrNot != 'N' && continueOrNot != 'n' ) { // wrong again message situation
            cout << "Error command! please enter an acceptable command :" << endl ;
            cin >> continueOrNot ;
        } // while()

        Count = 0 ; // reset count
        Number = 1 ; // reset result count

    } while( continueOrNot == 'Y' || continueOrNot == 'y' ) ;

    cout << "Bye :(((" ; // print out bye message
}
