#include <iostream>
#include "SETCOLORFUN.h"
#include <windows.h>
using namespace std;

enum COLOR{yellow = 0, green, blue, purple, red};
class ColoredBox {
private:
    char** arr;
    char character;
    int length;
    int width;
    int color;
public:
    static int MaxArea;
    ColoredBox(){};
    ColoredBox(int len, int wid, int color, char c ){
        length = len;
        width = wid;
        character = c;
        SetColor(color);
        arr = new char *[length];
        for (int i = 0; i < length; i++) {
            arr[i] = new char[width];
        }
        for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    arr[i][j] = c;
            }
        }
    }

    ColoredBox(int len, int wid){
        length = len;
        width = wid;
        arr = new char *[length];
        for (int i = 0; i < length; i++) {
            arr[i] = new char[width];
        }
        for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    arr[i][j] = '#';
            }
        }
    }

    ColoredBox(int len, int wid, char c){
        length = len;
        width = wid;
        character = c;
        arr = new char *[length];
        for (int i = 0; i < length; i++) {
            arr[i] = new char[width];
        }
        for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    arr[i][j] = c;
            }
        }
    }

    void set_char(char c){
        character = c;
    }

    void set_length(int len){
        length = len;
    }

    void set_width(int wid){
        width = wid;
    }

    void SetColor(int ForgC)
    {
        WORD wColor;
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        //We use csbi for the wAttributes word.
        if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
        {
            //Mask out all but the background attribute, and add in the forgournd color
            wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
            SetConsoleTextAttribute(hStdOut, wColor);
        }
        color = ForgC;
        return;
    }


    char get_char(){
        return character;
    }

    int get_length(){
        return length;
    }

    int get_width(){
        return width;
    }

    int get_color(){
        return color;
    }

    char** get_charArr(){
        return arr;
    }

    int getArea(){
        int area = length*width;
        if(area > MaxArea){
            MaxArea = area;
        }
        return area;
    }

    int getMaxArea(){
        return MaxArea;
    }

    void displayTransposed();
    void display();
    void displayChess(int Color);
    void displayWider();
    void displayObject();
    ~ColoredBox(){ delete[] arr; };
};

int ColoredBox::MaxArea = 0;

void ColoredBox::displayTransposed(){
    char**  arr2 = new char *[width];
    for (int i = 0; i < width; i++) {
        arr2[i] = new char[length];
    }
    for (int i = 0; i < length; i++) {
            for (int j = 0; j < width; j++) {
                arr2[j][i] = arr[i][j];
        }
    }
    for (int i = 0; i < width; i++) {
            for (int j = 0; j < length; j++) {
                cout << arr2[i][j] ;
        }
        cout << endl;
        }        cout << endl;
}

void ColoredBox::displayWider(){
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout << arr[i][j] << " " ;
        }
        cout << endl;
    }
    cout << endl;
}

void ColoredBox::displayChess(int Color){
    int old_color = color;
    cout << old_color << endl;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if((i+j) % 2 == 0){
                SetColor(Color);
            }
            else{
                SetColor(old_color);
            }
            cout << arr[i][j] ;
        }
        cout << endl;
    }
    cout << endl;
    SetColor(old_color);
}

void ColoredBox::display(){
    char** arr = get_charArr();
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void ColoredBox::displayObject(){
    cout << "the length is: " << get_length() << endl;
    cout << "the width is: " << get_width() << endl;
    //cout << "the color is: " << get_color() << endl;
    cout << "the character is: " << get_char() << endl;
    cout << "the shape: \n";
    char** arr = get_charArr();
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int main()
{
    int len,wid,col,col2;
    char boxChar;
    cout<<"Enter length and width of the box separated by a space: ";
    cin>>len>>wid;
    ColoredBox *cb1;
    cb1 = new ColoredBox(len,wid);
    cb1->display();
    cout<<"Set the box to another color: ";
    cin>>col;
    cb1->SetColor(col);
    cout<<"Displaying Transposed: "<<endl;
    cb1->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb1->displayWider();
    cout<<"Displaying Chess, enter the other color: " << endl;
    cin>>col2;
    cb1->displayChess(col2);
    cout<<endl<<"Area="<<cb1->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea() << endl;
    delete cb1;
    cout<<"Enter length,width,color,character of the box separated by spaces: ";
    cin>>len>>wid>>col>>boxChar;
    ColoredBox* cb2;
    cb2 = new ColoredBox(len,wid,col,boxChar);
    cb2->display();
    cout<<"Displaying Transposed: "<<endl;
    cb2->displayTransposed();
    cout<<"Displaying Wider: "<<endl;
    cb2->displayWider();
    cout<<"Displaying Chess, enter the other color: "<<endl;
    cin>>col2;
    cb2->displayChess(col2);
    cout<<"Displaying original again:"<<endl;
    cb2->display();
    cout<<endl<<"Area="<<cb2->getArea();
    cout<<endl<<"Max Area="<<cb1->getMaxArea() << endl;
    delete cb2;
    return 0;
}

