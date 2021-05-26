#include <iostream>
using namespace std;
char Board[10][10];

class Robot {
    private:
        int xLocation;
        int yLocation;
        bool cargoBed;
        char load;
    public:
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


Robot::Robot(){
}

Robot::Robot(int xLocation, int yLocation, bool cargoBed, char load){
   this->xLocation = xLocation;
   this->yLocation = yLocation;
   this->cargoBed = cargoBed;
   this->load = load;
}

void Robot::setXLocation(int xLocation){
   this->xLocation = xLocation;
}

void Robot::setYLocation(int yLocation){
   this->yLocation = yLocation;
}

void Robot::setCargoBed(bool cargoBed){
   this->cargoBed = cargoBed;
}

void Robot::setLoad(char load){
   this->load = load;
}

int Robot::getXLocation() const{
   return xLocation;
}

int Robot::getYLocation() const{
   return yLocation;
}

bool Robot::getCargoBed() const{
   return cargoBed;
}

char Robot::getLoad() const{
   return load;
}

bool Robot::MoveTo(int x, int y){

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

bool Robot::pickUp(int x, int y)
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

bool Robot::dropOff(int x, int y)
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

Robot::~Robot(){
}

ostream& operator<<(ostream& os, const Robot& Obj)
{
   os << "ROBOT: (" << Obj.getXLocation() << ", " << Obj.getYLocation() << ") :" << Obj.getLoad() << endl;
   return os;
}

void print2D(){
   for (int i = 0; i < 10; i++){
       for (int j = 0; j < 10; j++){
           cout << Board[i][j] << " ";
       }
       cout << endl;
   }
   cout << endl << endl;
}

void initialize2D(){
   for (int i = 0; i < 10; i++){
       for (int j = 0; j < 10; j++){
           Board[i][j] = '.';
       }
   }
   Board[3][8] = 'B';
   Board[2][6] = 'C';
}

void clear(char grid[10][10]){
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