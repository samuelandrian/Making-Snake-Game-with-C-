#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
//conio. h dibutuhkan pada fungsi input
//conio.h console input output


//windows.h untuk fungsi sleep
using namespace std;
bool GameOver;

//dibutuhkan map
const int width = 20;
const int height = 20;

//dibutuhkan score
int score;

//dibutuhkan track direction
enum eDirection{STOP = 0,LEFT,RIGHT,UP,DOWN};

eDirection dir; //variable dirrection



int x,y;//head position

int fruitX,fruitY;//fruit position

//taill
int tailX[100],tailY[100];
int nTail;//length tail
//


void Setup()
{
    GameOver = false;//saat game mulai GameOver = flase
    dir = STOP;//track direction = stop(0)
    x = width/2;//posisi head berada di tengah map
    y = height/2;
    fruitX = rand()%width;//akan membreikan nilai antara zero sampai width
    fruitY = rand()%height;
    score = 0;

}

void Draw()
{
    system("cls");//clear gamabar


    //draw map
    for(int i=0;i<width+2;i++)//batas paling atas
        cout<<"#";
    cout<<endl;

    //gambar batas pinggir map

    for(int i = 0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";

            if(i==y&&j==x)
                    cout<<"O";
            else if(i==fruitY&&j==fruitX)
                    cout<<"F";
            else
            {
                bool print = false;
                for(int k = 0;k<nTail;k++)
                {
                    //karna nilai tailX[0] dan tailY[0]
                    //awalannya di assign nilai head
                    //seterusnya saat nilai head berubah maka
                    //nilai tainya mengikuti nilai head sebelumnya


                    if(tailX[k]==j&&tailY[k]==i)//memprint nilai head sebelumnya (tail)
                    {

                        cout<<"o";
                        print = true;
                    }

                }
                if(!print)
                    cout<<" ";

            }
            if(j==(width-1))
                cout<<"#";
        }
        cout<<endl;
    }


    for (int i =0;i<width+2;i++)//batas paling bawah
        cout<<"#";
    cout<<endl;
    cout<<"score : "<<score;
}

void Input()
{
    if(_kbhit())//check is keyboard is preessed?
    {
        switch(_getch())
        {
        case 'a' :
            dir = LEFT;
            break;
        case 'w' :
            dir = UP;
            break;
        case 'd' :
            dir = RIGHT;
            break;
        case 's' :
            dir = DOWN;
            break;
        case 'x' ://terminate the game
            GameOver = true;
            break;
        }
    }

}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X,prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1;i<nTail;i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }



    switch(dir)
    {

    case LEFT :
        x--;
        break;
    case UP :
        y--;
        break;
    case DOWN :
        y++;
        break;
    case RIGHT :
        x++;
        break;
    default :
        break;
    }
    //terminate game after head
    //if(x>width||x<0||y>height||y<0)
      //  GameOver = true;

    if(x>=width)
        x = 0;
    if(x<0)
        x = width-1;
    if(y>=height)
        y=0;
    if(y<0)
        y = height-1;


    //terminate if it eat itself
    for(int i = 0;i<nTail;i++)
    {
        if(tailX[i]==x&&tailY[i]==y)
            GameOver = true;
    }


    //if eat the fruit  then score increased
    if(x==fruitX&&y==fruitY)
    {

        score +=1;
        fruitX = rand()%width;//fruit dibuat random lagi
        fruitY = rand()%height;
        nTail +=1;//increase the tail
    }


}







int main()
{

    Setup();
    while(!GameOver)
    {
        Draw();
        Input();
        Logic();
        //Sleep(10); //fungsi sleep bila perlu diperlambat
    }


    return 0;
}
