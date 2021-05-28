#include <iostream>
using namespace std;
char Board[10][10];

class Robot {
    private: //data fields
        int xLocation;
        int yLocation;
        bool cargoBed;
        char load;
    public: //constructors
        Robot();
        Robot(int xLocation, int yLocation, bool cargoBed, char load);
        void setXLocation(int xLocation);
        void setYLocation(int yLocation);
        void setCargoBed(bool cargoBed);
        void setLoad(char load);
        int getXLocation() const;
        int getYLocation() const;
        bool getCargoBed() const;
        char getLoad() const;
        bool MoveTo(int x, int y);
        bool pickUp(int x, int y);
        bool dropOff(int x, int y);
        friend ostream& operator<<(ostream& os, const Robot& Obj);
        ~Robot();
};


Robot::Robot(){ //default constructor
}

Robot::Robot(int xLocation, int yLocation, bool cargoBed, char load){ //constructor with parameter
   this->xLocation = xLocation;
   this->yLocation = yLocation;
   this->cargoBed = cargoBed;
   this->load = load;
}

void Robot::setXLocation(int xLocation){ //sets new x location
   this->xLocation = xLocation;
}

void Robot::setYLocation(int yLocation){ //sets new y location
   this->yLocation = yLocation;
}

void Robot::setCargoBed(bool cargoBed){ //sets load on cargo to be true or false
   this->cargoBed = cargoBed;
}

void Robot::setLoad(char load){ //sets new load 
   this->load = load;
}

int Robot::getXLocation() const{ //gets x location
   return xLocation;
}

int Robot::getYLocation() const{ //gets y location
   return yLocation;
}

bool Robot::getCargoBed() const{ //checks if there is load
   return cargoBed;
}

char Robot::getLoad() const{ //gets load
   return load;
}

bool Robot::MoveTo(int x, int y){ //moves to the given x and y coordinates on board

   if (x >= 0 && x < 10 && y >= 0 && y < 10)
   {
       int i = xLocation;
       int j = yLocation;
       for (i ; i != x; )
       {
           if (x < i)
           {
               i--;
           }
           if (x > i)
           {
               i++;
           }
           for (j ; j != y; )
           {
               if (y < j)
               {
                   j--;
               }
               if (y > j)
               {
                   j++;
               }
           }
       }
       xLocation = i;
       yLocation = j;
       return true;
   }
   return false;
}

bool Robot::pickUp(int x, int y) //picks up load on given coordinates
{
   if (Board[x][y] != '.' && cargoBed == false && load == '.'){
       MoveTo(x, y);
       load = Board[x][y];
       cargoBed = true;
       Board[x][y] = '.';
       return true;
   }
   return false;
}

bool Robot::dropOff(int x, int y) //drops off load on given coordinates
{
   if (Board[x][y] == '.' && cargoBed == true && load != '.')
   {
       MoveTo(x, y);
       Board[x][y] = load;
       cargoBed = false;
       load = '.';
   }
   return false;
}

Robot::~Robot(){ //destructor
}

ostream& operator<<(ostream& os, const Robot& Obj) //friend function that can be given special access to private memebers
{
   os << "ROBOT: (" << Obj.getXLocation() << ", " << Obj.getYLocation() << ") :" << Obj.getLoad() << endl;
   return os;
}

void print2D(){ //prints board
   for (int i = 0; i < 10; i++){
       for (int j = 0; j < 10; j++){
           cout << Board[i][j] << " ";
       }
       cout << endl;
   }
   cout << endl << endl;
}

void initialize2D(){ //initial place of load
   for (int i = 0; i < 10; i++){
       for (int j = 0; j < 10; j++){
           Board[i][j] = '.';
       }
   }
   Board[3][8] = 'B';
   Board[2][6] = 'C';
}

void clear(char grid[10][10]){ //deletes robot if there is no load
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(grid[i][j] != '.'){
                Robot * r = new Robot(0, 0, false, '.');
                r->MoveTo(i, j);
                r->pickUp(i, j);
                delete r;
            }
        }
    }
}
int main(){
    initialize2D();

    cout << "After initializing" << endl;
    print2D();

    Robot R1(1, 5, false, '.');
    Robot R2(4, 4, false, '.');

    cout << "Robots R1 and R2 created"<< endl;
    cout << "R1: " << R1;
    cout << "R2: " << R2;


    cout << "R1 and R2 moved " << endl;
    R1.MoveTo(9, 2);
    R2.MoveTo(3, 4);
    cout << "R1: " << R1;
    cout << "R2: " << R2 << endl;

    cout << "R1 picked up and dropped off B" << endl;
    R1.pickUp(3, 8);
    R1.dropOff(9, 9);
    print2D();
    cout << "R1: " << R1;
    cout << "R2: " << R2<< endl;

    cout << "R2 picked up and dropped off C" << endl;
    R2.pickUp(2, 6);
    R2.dropOff(0, 0);
    print2D();
    cout << "R1: " << R1;
    cout << "R2: " << R2 << endl;

    cout << "clearing..." << endl;
    clear(Board);
    print2D();

   return 0;
}
