/*
Caleb Favela
Professor Azuaje
20 November 2020

*/

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

//utility functions used in math problem functions
int inputInt(string message);
void swap(int &n1, int &n2);
int makeRandomInt(int lowest, int highest);
void printExpression(int n1, char op, int n2);
//Functions to run upon selection
void promptAdditionProblem();
void promptMultiplicationProblem();
void promptSubtractionProblem();
void promptDivisionProblem();
void printExit();

class Item{
    private:
    //pointer to the Item's function
    void (*action)();    
    public:
        
        string name;
        int number;
        Item(string n, int num);
        //using pointers in order to set/pass in a function as a parameter
        void addAction(void (*f)());
        void runAction();
};

class Menu{
    int itemsCount;
    int menuZero = 0;
    public:
        vector<Item> items;
        string title;
        //sets title, and starts item count
        Menu(string t);
        void addItem(string name);
        void printMenu();
        //inputs choice with validation
        int choiceInput(string message);
        void selectItem(int itemNum);
        Item getItemByNumber(int num);
        int getItemsCount();
};


int main(){
    //input variable, and predetermined exit option
    int itemSelected = 0;
    int exitOption = 2;

    Menu mathProblemMenu = Menu("Simple math problems");
    mathProblemMenu.addItem("Addition problem.");
    // mathProblemMenu.addItem("Subtraction problem.");
    // mathProblemMenu.addItem("Multiplication problem.");
    // mathProblemMenu.addItem("Division problem.");
    mathProblemMenu.addItem("Exit program.");
    //--------------------------------The problem so far
    mathProblemMenu.items.at(0).addAction(promptAdditionProblem);//this works
    mathProblemMenu.getItemByNumber(1).addAction(promptAdditionProblem);//this doesn't
    // mathProblemMenu.getItemByNumber(2).addAction(promptSubtractionProblem);
    // mathProblemMenu.getItemByNumber(3).addAction(promptMultiplicationProblem);
    // mathProblemMenu.getItemByNumber(4).addAction(promptDivisionProblem);
    //mathProblemMenu.getItemByNumber(exitOption).addAction(printExit);

    while(itemSelected != exitOption){
        mathProblemMenu.printMenu();
        itemSelected = mathProblemMenu.choiceInput("Choose a type of math problem:");
        mathProblemMenu.selectItem(itemSelected);
    }

    return 0;
}

void testPrompt(){
    cout << "Launched testPrompt."<< endl;
}

//implementation for class Menu functions
Menu::Menu(string t){
    title = t;
    itemsCount = menuZero;
}
void Menu::addItem(string name){
    itemsCount++;
    items.push_back(Item(name, itemsCount));
}
void Menu::printMenu(){
    printf("%s\n\n", title.c_str());
    for(int i=0; i<items.size(); i++){
        printf("%d. %s\n",items.at(i).number, items.at(i).name.c_str());
    }
}
int Menu::choiceInput(string message = ""){
    bool isValid = false;
    int input;
    printf("%s (%d-%d)\n",message.c_str(), menuZero+1, itemsCount);
    //validation loop
    while (isValid == false){
        cin >> input;
        //check for non-integer
        if (cin.fail()){
            cout << "That is not an integer, try again:";
            //clear flag and remove buffer values for next cin
            cin.clear();
            cin.ignore(32767,'\n');
        }
        //check for out of bounds
        else {
            bool notWithinBounds = (input > itemsCount || input < menuZero+1);
            if(notWithinBounds){
                cout << "That is not within bounds, try again:";
            }
            else
            {
                isValid = true;
            }    
        }
    }
    return input;
}
void Menu::selectItem(int itemNum){
    // getItemByNumber(itemNum).runAction();
    getItemByNumber(itemNum).runAction();
}
Item Menu::getItemByNumber(int num){
    return items.at(menuZero+num-1);
}
int Menu::getItemsCount(){
    return itemsCount;
}

//Implementation for class Item functions
Item::Item(string n, int num){
    name = n;
    number = num;
}
//using pointers in order to set/pass in a function as a parameter
void Item::addAction(void (*f)()){
    action = f;
}
void Item::runAction(){
    //run function from pointer var
    action();
}

int inputInt(string message =""){
    bool isValid = false;
    int input;
    printf("%s\n",message.c_str());
    //validation loop
    while (!isValid){
        cin >> input;
        //check for non-double
        if (cin.fail()){
            //remove previous input from cin buffer
            cin.ignore(32767,'\n');
            cout << "That is not a whole number, try again:";
        }
        else {
            isValid = true;
        }
    }
    return input;
}
void swap(int &n1, int &n2){
    int temp = n1;
    n1 = n2;
    n2 = temp;
}
int makeRandomInt(int lowest, int highest){
    unsigned int seed = time(0);//figure out how to improve
    srand(seed);
    return lowest + rand() % highest;
}
void printExpression(int n1, char op, int n2){
    printf("%d %c %d = ?", n1, op, n2);
}
void promptAdditionProblem(){
    int guess =0;
    int num1 = makeRandomInt(0,12);
    int num2 = makeRandomInt(0,12);
    int ans = num1 + num2;
    printExpression(num1,'+',num2);
    guess = inputInt();
    while(guess != ans){
        cout << "That is incorrect, try again:" << endl;
        printExpression(num1,'+',num2);
        guess = inputInt();
    }       
    cout << "Correct!" << endl;
}
void promptMultiplicationProblem(){
    int guess =0;
    int num1 = makeRandomInt(0,12);
    int num2 = makeRandomInt(0,12);
    int ans = num1 * num2;
    printExpression(num1,'*',num2);
    guess = inputInt();
    while(guess != ans){
        cout << "That is incorrect, try again:" << endl;
        printExpression(num1,'*',num2);
        guess = inputInt();
    }     
    cout << "Correct!" << endl;
}
void promptSubtractionProblem(){
    int guess =0;
    int num1 = makeRandomInt(0,12);
    int num2 = makeRandomInt(0,12);
    if(num1 < num2){
        swap(num1, num2);
    }
    int ans = num1 - num2;
    printExpression(num1,'-',num2);
    guess = inputInt();
    while(guess != ans){
        cout << "That is incorrect, try again:" << endl;
        printExpression(num1,'-',num2);
        guess = inputInt();
    }
    cout << "Correct!" << endl;
}
void promptDivisionProblem(){
    int guess =0;
    int quotient = makeRandomInt(0,12);
    int divisor = makeRandomInt(0,12);
    int dividend = quotient * divisor;
    printExpression(dividend,'/',divisor);
    guess = inputInt();
    while(guess != quotient){
        cout << "That is incorrect, try again:" << endl;
        printExpression(dividend,'/',divisor);
        guess = inputInt();
    }
    cout << "Correct!" << endl;
}
void printExit(){
    cout << "Exiting..." << endl;
}

//TODO: organize number and indexs on item vector