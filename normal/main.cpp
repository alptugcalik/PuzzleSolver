/* file stream library */ /* required for file IO */
#include <iostream>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;

class Sokoban{
private:
         // stores the puzzle
    int currentRow; // points to the current row of the user
    int currentColumn; // points to the current column of the user
public:
    char puzzleArray[6][8];
    Sokoban(char data[6][8] ); // declaration of the constructor that takes puzzle from char array
    Sokoban(const Sokoban& copiedSokoban); // declaration of the copy constructor
    Sokoban& operator=(const Sokoban& rhs); // declaration of the copy assignment operator
    Sokoban(); // declaration of the constructor that takes puzzle from a file
    bool move_up(); // move methods
    bool move_down();
    bool move_left();
    bool move_right();
    bool is_solved() const; // checks if puzzle is solved
    void print_puzzle() const;   // prints the puzzle
};

//constructor
Sokoban::Sokoban(char data[6][8] ){
    // store the puzzle and find the initial position of the character
    for(int i=0;i<6;i++){
            for(int j=0;j<8;j++){
                    puzzleArray[i][j] = data[i][j]; // copying the members
                    if(puzzleArray[i][j]=='@' || puzzleArray[i][j]=='+'){
                        currentRow = i;
                        currentColumn = j;
                    }
            }
    }
}

//copy constructor
Sokoban::Sokoban(const Sokoban& copiedSokoban){
     for(int i=0;i<6;i++){
            for(int j=0;j<8;j++){
                    puzzleArray[i][j] = copiedSokoban.puzzleArray[i][j]; // copying the members
            }
    }
    currentColumn=copiedSokoban.currentColumn;//assigning the values of the members
    currentRow=copiedSokoban.currentRow;
}

//copy assignment operator
Sokoban&Sokoban:: operator=(const Sokoban& rhs){
    for(int i=0;i<6;i++){
            for(int j=0;j<8;j++){
                    puzzleArray[i][j] = rhs.puzzleArray[i][j]; // copying the members
            }
    }
    currentRow=rhs.currentRow;
    currentColumn=rhs.currentColumn;
    return *this;
}

//constructor that takes the puzzle from a file
Sokoban::Sokoban(){
    string path = "sample_puzzle.txt";
    char data[6][8];
    char dummy;
    ifstream file;
    file.open(path);
    for(int i=0; i<6; ++i){
        for(int j=0; j<8; ++j){
            file >> noskipws >> data[i][j];
            puzzleArray[i][j]=data[i][j];
            if(puzzleArray[i][j]=='@' || puzzleArray[i][j]=='+'){
                        currentRow = i;
                        currentColumn = j;
            }
        }
        file >> noskipws >> dummy;
    }
    file.close();

}

bool Sokoban::move_up(){
    if(puzzleArray[currentRow-1][currentColumn]== '#')//upper cell is a wall
        return false;
    else if(puzzleArray[currentRow-1][currentColumn] == ' '){ // upper cell is empty
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow-1][currentColumn]='@';
        currentRow--;
        return true;
    }
    else if(puzzleArray[currentRow-1][currentColumn] == '.'){// upper cell is a target location
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow-1][currentColumn]='+';
        currentRow--;
        return true;
    }
    else if(puzzleArray[currentRow-1][currentColumn] == '$'){//upper cell is a movable box
        if(puzzleArray[currentRow-2][currentColumn] == ' '){ // upper cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow-1][currentColumn]='@';
            puzzleArray[currentRow-2][currentColumn]='$';
            currentRow--;
            return true;
        }
        else if(puzzleArray[currentRow-2][currentColumn] == '.'){ // upper cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow-1][currentColumn]='@';
            puzzleArray[currentRow-2][currentColumn]='*';
            currentRow--;
            return true;
        }
        else
            return false;
    }
    else if(puzzleArray[currentRow-1][currentColumn] == '*'){//upper cell is a movable box at a target location
        if(puzzleArray[currentRow-2][currentColumn] == ' '){ // upper cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow-1][currentColumn]='+';
            puzzleArray[currentRow-2][currentColumn]='$';
            currentRow--;
            return true;
        }
        else if(puzzleArray[currentRow-2][currentColumn] == '.'){ // upper cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow-1][currentColumn]='+';
            puzzleArray[currentRow-2][currentColumn]='*';
            currentRow--;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool Sokoban::move_down(){
    if(puzzleArray[currentRow+1][currentColumn]== '#')//lower cell is a wall
        return false;
    else if(puzzleArray[currentRow+1][currentColumn] == ' '){ // lower cell is empty
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow+1][currentColumn]='@';
        currentRow++;
        return true;
    }
    else if(puzzleArray[currentRow+1][currentColumn] == '.'){// lower cell is a target location
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow+1][currentColumn]='+';
        currentRow++;
        return true;
    }
    else if(puzzleArray[currentRow+1][currentColumn] == '$'){//lower cell is a movable box
        if(puzzleArray[currentRow+2][currentColumn] == ' '){ // lower cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow+1][currentColumn]='@';
            puzzleArray[currentRow+2][currentColumn]='$';
            currentRow++;
            return true;
        }
        else if(puzzleArray[currentRow+2][currentColumn] == '.'){ // lower cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow+1][currentColumn]='@';
            puzzleArray[currentRow+2][currentColumn]='*';
            currentRow++;
            return true;
        }
        else
            return false;
    }
    else if(puzzleArray[currentRow+1][currentColumn] == '*'){//lower cell is a movable box at a target location
        if(puzzleArray[currentRow+2][currentColumn] == ' '){ // lower cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow+1][currentColumn]='+';
            puzzleArray[currentRow+2][currentColumn]='$';
            currentRow++;
            return true;
        }
        else if(puzzleArray[currentRow+2][currentColumn] == '.'){ // lower cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow+1][currentColumn]='+';
            puzzleArray[currentRow+2][currentColumn]='*';
            currentRow++;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool Sokoban::move_left(){
    if(puzzleArray[currentRow][currentColumn-1]== '#')//left cell is a wall
        return false;
    else if(puzzleArray[currentRow][currentColumn-1] == ' '){ // left cell is empty
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow][currentColumn-1]='@';
        currentColumn--;
        return true;
    }
    else if(puzzleArray[currentRow][currentColumn-1] == '.'){// left cell is a target location
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow][currentColumn-1]='+';
        currentColumn--;
        return true;
    }
    else if(puzzleArray[currentRow][currentColumn-1] == '$'){//left cell is a movable box
        if(puzzleArray[currentRow][currentColumn-2] == ' '){ // left cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn-1]='@';
            puzzleArray[currentRow][currentColumn-2]='$';
            currentColumn--;
            return true;
        }
        else if(puzzleArray[currentRow][currentColumn-2] == '.'){ // left cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn-1]='@';
            puzzleArray[currentRow][currentColumn-2]='*';
            currentColumn--;
            return true;
        }
        else
            return false;
    }
    else if(puzzleArray[currentRow][currentColumn-1] == '*'){//left cell is a movable box at a target location
        if(puzzleArray[currentRow][currentColumn-2] == ' '){ // left cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn-1]='+';
            puzzleArray[currentRow][currentColumn-2]='$';
            currentColumn--;
            return true;
        }
        else if(puzzleArray[currentRow][currentColumn-2] == '.'){ // left cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn-1]='+';
            puzzleArray[currentRow][currentColumn-2]='*';
            currentColumn--;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool Sokoban::move_right(){
    if(puzzleArray[currentRow][currentColumn+1]== '#')//right cell is a wall
        return false;
    else if(puzzleArray[currentRow][currentColumn+1] == ' '){ // right cell is empty
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow][currentColumn+1]='@';
        currentColumn++;
        return true;
    }
    else if(puzzleArray[currentRow][currentColumn+1] == '.'){// right cell is a target location
        if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
            puzzleArray[currentRow][currentColumn]=' ';
        else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
            puzzleArray[currentRow][currentColumn]='.';
        puzzleArray[currentRow][currentColumn+1]='+';
        currentColumn++;
        return true;
    }
    else if(puzzleArray[currentRow][currentColumn+1] == '$'){//right cell is a movable box
        if(puzzleArray[currentRow][currentColumn+2] == ' '){ // right cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn+1]='@';
            puzzleArray[currentRow][currentColumn+2]='$';
            currentColumn++;
            return true;
        }
        else if(puzzleArray[currentRow][currentColumn+2] == '.'){ // right cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn+1]='@';
            puzzleArray[currentRow][currentColumn+2]='*';
            currentColumn++;
            return true;
        }
        else
            return false;
    }
    else if(puzzleArray[currentRow][currentColumn+1] == '*'){//right cell is a movable box at a target location
        if(puzzleArray[currentRow][currentColumn+2] == ' '){ // right cell of the movable box is empty
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+')//user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn+1]='+';
            puzzleArray[currentRow][currentColumn+2]='$';
            currentColumn++;
            return true;
        }
        else if(puzzleArray[currentRow][currentColumn+2] == '.'){ // right cell of the movable box is a target location
            if(puzzleArray[currentRow][currentColumn]=='@') // user is not at a target location
                puzzleArray[currentRow][currentColumn]=' ';
            else if(puzzleArray[currentRow][currentColumn]=='+') //user is at a target location
                puzzleArray[currentRow][currentColumn]='.';
            puzzleArray[currentRow][currentColumn+1]='+';
            puzzleArray[currentRow][currentColumn+2]='*';
            currentColumn++;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool Sokoban::is_solved()const{
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            if(puzzleArray[i][j]=='$')// if any of the moving boxes is not at a target location
                return false;
        }
    }
    return true; // all boxes are at target locations
}

void Sokoban::print_puzzle()const{ //prints the puzzle
    for(int i=0;i<6;i++){
        for(int j=0;j<8;j++){
            cout<<puzzleArray[i][j];
        }
        cout<<endl;
    }
}

template <class T>
class StackQueue{
private:
    T elements[MAXSIZE];  // storage of T elements
    int front,rear,count; // in order to generate circular queue
public:
    StackQueue(); // constructor
    void push_front(const T& newObject); // add to front
    T pop_front(void); //  remove from front
    T pop_rear(void);   // remove from rear
    bool is_empty(void); // checks if the stack is empty
};

//constructor
template <class T>
StackQueue<T>::StackQueue(){
    front=-1; //initialize members
    rear=0;
    count = 0;
}

//push front
template <class T>
void StackQueue<T>::push_front(const T& newObject){
    T temp;
    if(count==100){ // check if the stack is full
        cerr<<"Stack overflow!"<<endl;
    }
    else{
        front=(front+1)%MAXSIZE;//generating a circular memory in order to avoid empty spaces
        elements[front]=newObject;
        count++; //increase element number
    }

}

// pop front
template <class T>
T StackQueue<T>::pop_front(void){
    T temp;
    if(count==0){ // check if the stack is empty
        cerr<<"Stack is empty!"<<endl;
    }
    else{
        temp = elements[front];
        front = (front-1)%MAXSIZE; //generating a circular memory in order to avoid empty spaces
        count--; //DECREASE ELEMENT NUMBER
        return temp;
    }
}

// pop rear
template <class T>
T StackQueue<T>::pop_rear(void){
    T temp;
    if(count==0){ // check if the stack is empty
        cerr<<"Stack is empty!"<<endl;
    }
    else{
        temp = elements[rear];
        rear = (rear+1)%MAXSIZE; //generating a circular memory in order to avoid empty spaces
        count--; //decrease element number
        return temp;
    }
}

// is_empty
template <class T>
bool StackQueue<T>::is_empty(void){
    return (count==0);
}


int main()
{

    char ask[6][8]  = {{'#','#','#','#','#','#','#','#'},
                    {'#',' ',' ',' ',' ',' ',' ','#'},
                    {'#',' ',' ',' ',' ','$',' ','#'},
                    {'#',' ',' ',' ',' ',' ',' ','#'},
                    {'#',' ',' ',' ',' ',' ','@','#'},
                    {'#','#','#','#','#','#','#','#'}
                    };
    Sokoban sokoban(ask);
    Sokoban sokoban2;
    sokoban = sokoban2;
    StackQueue<Sokoban> stackQueue;
    char x;
    sokoban.print_puzzle(); // initial puzzle is printed
    stackQueue.push_front(sokoban); // initial puzzle is loaded to stack
    while(true){
        if(sokoban.is_solved()==true)
            cout<<"The puzzle is solved!!!!"<<endl;
        cin>>x;
        // the following conditions are checks the input charachter
        if(x=='w'){
            if(sokoban.move_up()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle(); //prints the puzzle after the motion
                stackQueue.push_front(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='a'){
            if(sokoban.move_left()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue.push_front(sokoban); //add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='s'){
            if(sokoban.move_down()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue.push_front(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='d'){
            if(sokoban.move_right()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue.push_front(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='z'){
            stackQueue.pop_front(); // deletes the current state
            sokoban=stackQueue.pop_front(); // takes the previous state from the stack
            stackQueue.push_front(sokoban); // since the previous state is deleted, it is added again
            sokoban.print_puzzle(); // puzzle is printed
        }
        else if(x=='r'){
            while(!stackQueue.is_empty()){ // deletes all moves until the first move is reached
                sokoban=stackQueue.pop_rear();
                sokoban.print_puzzle(); // prints each move
            }
            return 0; // the program terminates after replay
        }
        else
            cout<<"Please enter a valid input!"<<endl;


    }


    return 0;
}
