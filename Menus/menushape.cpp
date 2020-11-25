/*
Caleb Favela
Professor Azuaje
20 November 2020

Description:
Two classes (Items and Menu) deal with menu creation, use, and selection of item. Functions called by 
the seleciton of a menu item is dealt with seperately, including the exit option.
Area calculations and prompts are seperate public functions specific to this program

*/

#include <iostream>

#include <string>
#include <vector>

using namespace std;

const double PI = 3.14159265;
//Math functions
double calcCircleArea(double r);
double calcRectangleArea(double l, double w);
double calcSquareArea(double s);
double calcTriangleArea(double b, double h);
//Our program options
void promptCircleArea();
void promptRectangleArea();
void promptSquareArea();
void promptTriangleArea();
//answer printing format used in prompt functions
void printAreaAns(double a);
//Empty exiting statement to run when exiting
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
    int exitOption = 5;

    Menu shapeMenu = Menu("Shape Area Calculator:");
    shapeMenu.addItem("Calculate the area of a Circle.");
    shapeMenu.addItem("Calculate the area of a Rectangle.");
    shapeMenu.addItem("Calculate the area of a Square.");
    shapeMenu.addItem("Calculate the area of a Triangle.");
    shapeMenu.addItem("Exit Program.");

    //adding items functions for each items index
    shapeMenu.items.at(0).addAction(promptCircleArea);
    shapeMenu.items.at(1).addAction(promptRectangleArea);
    shapeMenu.items.at(2).addAction(promptSquareArea);
    shapeMenu.items.at(3).addAction(promptTriangleArea);
    shapeMenu.items[exitOption-1].addAction(printExit);

    while(itemSelected != exitOption){
        shapeMenu.printMenu();
        itemSelected = shapeMenu.choiceInput("Choose a shape to calculate the area of:");
        shapeMenu.selectItem(itemSelected);//---------------------------------------------------spooky call
    }
    return 0;
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
    //run function from pointer reference
    action();
}



void printExit(){
    cout << "Exiting..." << endl;
}
//provides validation for all cacl area functions
double inputDouble(string message){
    bool isValid = false;
    double input;
    printf("%s\n",message.c_str());
    //validation loop
    while (isValid == false){
        cin >> input;
        //check for non-double
        if (cin.fail()){
            //remove previous input from cin buffer
            cin.ignore(32767,'\n');
            cout << "That is not a number, try again:";
        }
        else {
            isValid = true;
        }
    }
    return input;
}

///neat printing for all calc area functions
void printAreaAns(double a){
    printf("The area is: %.2f\n\n", a);
}

void promptCircleArea(){
    double radius = inputDouble("Enter the radius to find the area of a circle: ");
    double ans = calcCircleArea(radius);
    printAreaAns(ans);
}
double calcCircleArea(double r){
    return PI * (r *r);
}

void promptRectangleArea(){
    double l = inputDouble("Enter the length to find the area of a rectangle: ");
    double w = inputDouble("Enter the width to find the area of a rectangle: ");
    double ans = calcRectangleArea(l,w);
    printAreaAns(ans);
}
double calcRectangleArea(double l,double w){
    return l * w;
}

void promptSquareArea(){
    double side = inputDouble("Enter the side to find the area of a square: ");
    double ans = calcSquareArea(side);
    printAreaAns(ans);
}
double calcSquareArea(double s){
    return s * s;
}

void promptTriangleArea(){
    double b = inputDouble("Enter the base to find the area of a rectangle: ");
    double h = inputDouble("Enter the height to find the area of a rectangle: ");
    double ans = calcTriangleArea(b,h);
    printAreaAns(ans);
}
double calcTriangleArea(double b, double h){
    return b * h * 0.5;
}

// Todo: (improve) avoid direct reference of item vector, and improve validation readability