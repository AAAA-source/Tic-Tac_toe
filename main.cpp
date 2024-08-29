#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using std::cin ;
using std::cout ;
using std::string ;
using std::endl ;
using std::vector ;
using std::pair ;

vector< vector<pair<int , int>> > past_game_record ;

void record( pair<int , int> now )
{
    past_game_record.back().push_back( now ) ;
}


void print_board( vector<vector<int> >board )
{
    cout << "   1  2  3" << endl ;
    cout << endl ;
    for(int i = 0 ; i < 3 ; i++) {
        cout << i + 1 << "  " ;
        for(int j = 0 ; j < 3 ; j++)
            if ( board[i][j] == 0 )
                cout << "   " ;
            else
                cout << board[i][j] << "  " ;
        cout << endl ;
    }
    cout << endl ;
    return ;
}

int win( vector<vector<int> >& board )
{
    for(int i = 0 ; i < 3 ; ++i) {
        if ( board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0 )
            return board[i][0] ;
        if ( board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0 )
            return board[0][i] ;
    }

    if ( board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0 )
        return board[0][0] ;
    if ( board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != 0 )
        return board[0][2] ;
    
    return 0 ;
}

bool full( vector<vector<int> >& board )
{
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < 3 ; j++)
            if ( board[i][j] == 0 )
                return false ;
    }
    return true ;
}

void two_people_competition(void)
{
    vector< vector<int> > board (3 , vector<int>(3) ) ;
    
    // 1 mean the front hand
    // 2 mean the back hand
    int now = 0 ;
    print_board(board) ;
    while ( !win(board) && !full(board) ) {
        cout << "Player " << now + 1 << " 's turn!" << endl ;
        
        int row , column ;
        cin >> row >> column ;
        while ( board[row - 1][column - 1] != 0 ) {
            cout << "this grid is already filled" << endl ;
            cin >> row >> column ;
        }
        
        board[row - 1][column - 1] = now + 1 ;
        
        record( {row - 1 , column - 1} ) ;
        
        print_board(board) ;
        now = (now + 1) % 2 ;
    }
    
    if ( win(board) )
        cout << "Player " << win(board) << " win the game " << endl ;
    else
        cout << "Draw" << endl ;
    
    return ;
}

int possible(int i , int j , vector<vector<int> >* v , int target)
{
    vector< vector<int> > &board = *v ;
    int count = 0 ;
    if ( board[i][0] != target && board[i][1] != target && board[i][2] != target)
        count++ ;
    if ( board[0][j] != target && board[1][j] != target && board[2][j] != target )
        count++ ;
    if ( i == j && board[0][0] != target && board[1][1] != target && board[2][2] != target )
        count++ ;
    if ( i + j == 2 && board[0][2] != target && board[1][1] != target && board[2][0] != target )
        count++ ;
    return count ;
}


pair<int , int> choose( vector<vector<int> >* v )
{
    vector< vector<int> > &board = *v ;
    
    
    // win
    for(int i = 0 ; i < 3 ; i++) {
        int count = 0 ;
        for(int j = 0 ; j < 3 ; j++) {
            if ( board[i][j] == 2 )
                count++ ;
            else if ( board[i][j] == 1 )
                count-- ;
        }
        if ( count == 2 ){
            for(int j = 0 ; j < 3 ; j++) {
                if ( board[i][j] == 0 )
                    return pair<int , int>(i , j) ;
            }
        }
    }
    for(int j = 0 ; j < 3 ; j++) {
        int count = 0 ;
        for(int i = 0 ; i < 3 ; i++) {
            if ( board[i][j] == 2 )
                count++ ;
            else if ( board[i][j] == 1 )
                count-- ;
        }
        if ( count == 2 ){
            for(int i = 0 ; i < 3 ; i++) {
                if ( board[i][j] == 0 )
                    return pair<int , int>(i , j) ;
            }
        }
    }
    
    
    // not loose
    for(int i = 0 ; i < 3 ; i++) {
        int count = 0 ;
        for(int j = 0 ; j < 3 ; j++) {
            if ( board[i][j] == 1 )
                count++ ;
            else if ( board[i][j] == 2 )
                count-- ;
        }
        if ( count == 2 ){
            for(int j = 0 ; j < 3 ; j++) {
                if ( board[i][j] == 0 )
                    return pair<int , int>(i , j) ;
            }
        }
    }
    
    for(int j = 0 ; j < 3 ; j++) {
        int count = 0 ;
        for(int i = 0 ; i < 3 ; i++) {
            if ( board[i][j] == 1 )
                count++ ;
            else if ( board[i][j] == 2 )
                count-- ;
        }
        if ( count == 2 ){
            for(int i = 0 ; i < 3 ; i++) {
                if ( board[i][j] == 0 )
                    return pair<int , int>(i , j) ;
            }
        }
    }
    
    // find best solution
    pair<int , int> candidate ;
    int max = -1 ;
    for(int i = 0 ; i < 3 ; i++) {
        for(int j = 0 ; j < 3 ; j++) {
            if ( board[i][j] == 1 )
                continue ;
            if ( possible(i , j , &board , 1) + possible(i , j , &board , 2) > max ) {
                candidate = pair<int , int>(i , j) ;
                max = possible(i , j , &board , 1) + possible(i , j , &board , 2) ;
            }
        }
    }
    
    
    return candidate ;
}


void play_with_computer(void)
{
    cout << "Do you want to go first?(Y/N)" << endl ;
    string s ;
    cin >> s ;
    bool cursor = (s == "Y")? 0 : 1 ;
    
    vector< vector<int> > board (3 , vector<int>(3) ) ;
    print_board(board) ;
    while ( !win(board) && !full(board) ) {
        if ( !cursor ) {
            // player's turn
            cout << "That's your turn" << endl ;
            int row , column ;
            cin >> row >> column ;
            while (  board[row - 1][column - 1] != 0 ) {
                cout << "this grid is already filled" << endl ;
                cin >> row >> column ;
            }
            
            board[row - 1][column - 1] = cursor + 1 ;
            
            record( {row - 1 , column - 1} ) ;
        }
        else {
            pair<int , int> result = choose(&board) ;
            board[result.first][result.second] = 2 ;
            
            record( result ) ;
        }
        print_board(board) ;
        cursor = !cursor ;
    }
    
    if ( win(board) )
        cout << ( (win(board) == 1)? "You" : "Computer" ) << " win " << endl ;
    else
        cout << "Draw" << endl ;
    
}

bool game(void)
{
    cout << "1 play with others" << endl ;
    cout << "2 play with computer" << endl ;
    
    
    int choice ;
    cin >> choice ;
    if ( choice == 1 ) {
        past_game_record.push_back({}) ;
        two_people_competition() ;
    }
    else {
        if ( choice != 2 )
            return false ;
        past_game_record.push_back({}) ;
        play_with_computer() ;
    }
    
    return true ;
}

void print_message(void)
{
    cout << "press 1 to start the game" << endl  ;
    cout << "press 2 to check the history" << endl  ;
    cout << "press 3 to read the rules" << endl ;
    cout << "press -1 to closed the game" << endl ;
}

bool print_record(void)
{
    cout << "Review" << endl ;
    
    if ( past_game_record.empty() ) {
        cout << "no record" << endl ;
        return 0 ;
    }
    
    
    decltype(past_game_record.size()) index = past_game_record.size() - 1 ;
    
    
    bool finished = false ;
    while ( !finished ) {
        cout << "index : " << index << endl ;
        if ( index != past_game_record.size() - 1 )
            cout << "next game? (please input next)" << endl ;
        if ( index != 0 )
            cout << "last game? (please input last)" << endl ;
        cout << "this game? (please input this)" << endl ;
        
        string s ;
        cin >> s ;
        
        if ( s == "last" ) {
            index-- ;
        }
        else if ( s == "next" ) {
            index++ ;
        }
        else if ( s == "this" ) {
            bool now = 0 ;
            vector<vector<int>> board(3 , vector<int>(3)) ;
            for( auto &i : past_game_record[index] ) {
                board[ i.first ][ i.second ] = now + 1 ;
                
                print_board(board) ;
                
                now = !now ;
            }
            finished = true ;
        }
        else {
            cout << "Wrong input " << endl ;
            break ;
        }
        
    }
    
    return finished ;
}

bool print_rule(void)
{
    std::ifstream file("rules.txt");
    
    if ( !file ) {
        cout << "Failed" << endl ;
        return false  ;
    }
    
    string line ;
    while ( std::getline(file , line) ) {
        cout << line << endl ;
    }
    
    
    file.close() ;
    return true ;
}



int main(void)
{
    cout << "Welcome to Tic-Tac-Toe game" << endl  ;
    print_message() ;
    
    int input ;
    cin >> input ;
    while (input != -1) {
        switch (input) {
            case 1 :
                if(!game())
                    cout << "Failed" << endl ;
                break ;
            case 2 :
                print_record() ;
                break ;
            case 3 :
                if ( !print_rule() ) {
                    cout << "file failed " << endl ;
                }
                break ;
            
                
            default :
                cout << "Please select the right mode" << endl ;
        }
        print_message() ;
        cin >> input ;
    }
    
    
    return 0 ;
}
