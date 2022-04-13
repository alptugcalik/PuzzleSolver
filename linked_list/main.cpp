#include <iostream>
#include <fstream>

using namespace std;

class Sokoban{
private:
    char puzzleArray[6][8];     // stores the puzzle
    int currentRow; // points to the current row of the user
    int currentColumn; // points to the current column of the user
public:
    Sokoban(char** data); // declaration of the constructor that takes puzzle from char array
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
Sokoban::Sokoban(char** data){
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


// Node class in order to implement a doubly linked list
template <class T>
class Node{
public:
    // members are public in order to reach them in ease
    Node <T> *next;
    Node <T> *prev;
    T data;
    //methods
    Node(const T& item); //constructor
};

//constructor
template <class T>
Node<T>::Node(const T& item){
    data = item; // assign data
    next = NULL; // assign next
    prev = NULL; // assign prev
}

//Doubly Linked list class
template <class T>
class LinkedList{
public:
    // member that holds the head of the linked list
    // it is public for easiness
    Node <T> *head;
    //methods
    LinkedList(); // constructor
    void InsertNode(Node<T> *newNode); // method to insert a node from the head
    Node<T>* deleteHead(void); // method to delete the last added node

};

//constructor
template <class T>
LinkedList<T>::LinkedList(){
    head = NULL; // the list is empty
}

//InsertNode
template <class T>
void LinkedList<T>::InsertNode(Node<T>* newNode){
    //Operations to insert the node to the head of the list
    if(head == NULL) head = newNode; // check if the linked list is empty
    else{
    newNode->next = head;
    newNode->prev = head->prev;
    head->prev->next = newNode;
    head -> prev = newNode;
    head = newNode;
    }
}

//Delete Head
template <class T>
Node<T>* LinkedList<T>:: deleteHead(void){
    //Operations to delete the node at the head of the list
    Node<T> *temp;
    temp = head;
    head->next->prev = head->prev;
    head->prev->next = head->next;
    head = head->next;
    return temp;
}

// new StackQueue class in order to implement doubly linked list method
template <class T>
class StackQueue2{
private:
    LinkedList<T> linkedList;  // storage is changed with a doubly linked list
public:
    StackQueue2(const T &item); // constructor
    void push(const T& newObject); // add
    T pop(void); //  remove
    bool is_empty(void); // checks if the stack is empty
};

//constructor
template <class T>
StackQueue2 <T>::StackQueue2(const T &item){
    // at the constructor, the head of the linked list is generated and the first input item is inputted to the constructor of the linked list
    Node<T>* newNode = new Node<T> (item); // new node is generated
    //newNode->data = item; // the data is stored at that node
    // next and prev members are initialized such that they point to the current node
    // this leads to generate a head of doubly linked list
    newNode->next = newNode;
    newNode->prev = newNode;
    linkedList.InsertNode(newNode); // the head of the linked list is initialized
}

//push
template <class T>
void StackQueue2<T>::push(const T& newObject){
    Node<T>* newNode = new Node<T> (newObject); // new node is generated
                                            // the data is stored at that node
    linkedList.InsertNode(newNode); // the node is added at head
}

// pop
template <class T>
T StackQueue2<T>::pop(void){
    Node<T> *tempNode; // temporary node is generated
    tempNode = linkedList.head; // head is assigned to this node
    linkedList.deleteHead();
    return tempNode->data;
}

// is_empty
template <class T>
bool StackQueue2<T>::is_empty(void){
    return (linkedList.head == linkedList.head->next && linkedList.head == linkedList.head->prev);
}

int main()
{
    Sokoban sokoban; // puzzle is taken from the file
    // head node is generated with sokoban by using the constructor of the stackqueue2 class
    StackQueue2<Sokoban> stackQueue2(sokoban);
    char x;
    sokoban.print_puzzle(); // initial puzzle is printed
    stackQueue2.push(sokoban); // initial puzzle is loaded to stack
    while(true){
        if(sokoban.is_solved()==true)
            cout<<"The puzzle is solved!!!!"<<endl;
        cin>>x;
        // the following conditions are checks the input charachter
        if(x=='w'){
            if(sokoban.move_up()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle(); //prints the puzzle after the motion
                stackQueue2.push(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='a'){
            if(sokoban.move_left()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue2.push(sokoban); //add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='s'){
            if(sokoban.move_down()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue2.push(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='d'){
            if(sokoban.move_right()){ // checks if the move is possible and if it is, generates the move
                sokoban.print_puzzle();//prints the puzzle after the motion
                stackQueue2.push(sokoban);//add the current state to the stack
            }
            else
                cout<<"The move is not valid!"<<endl;
        }
        else if(x=='z'){
            stackQueue2.pop(); // deletes the current state
            sokoban=stackQueue2.pop(); // takes the previous state from the stack
            stackQueue2.push(sokoban); // since the previous state is deleted, it is added again
            sokoban.print_puzzle(); // puzzle is printed
        }
        else if(x=='r'){
            while(!stackQueue2.is_empty()){ // deletes all moves until the first move is reached
                sokoban=stackQueue2.pop();
                sokoban.print_puzzle(); // prints each move
            }
            return 0; // the program terminates after replay
        }
        else
            cout<<"Please enter a valid input!"<<endl;

    }


    return 0;
}
