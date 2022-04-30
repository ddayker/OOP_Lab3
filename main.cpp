#include <iostream>
#include <math.h>
#include <cmath>
#include <stdlib.h>
using namespace std;

/*
 Создать классы «Транспортное средство», «Самолет», «Поезд», «Автомобиль» с необходимым набором полей и методов. Создать массив объектов базового класса и заполнить этот массив объектами базового и производных классов. Определить время и стоимость перевозки для указанных городов и расстояний. Вывести данные о наиболее быстрой и экономичной поездке на экран и в файл. Классы должны содержать методы получения и изменения значений всех полей. Все поля классов должны быть объявлены с атрибутами private или protected.
 */


class Vehicle{
    
protected:
    string type;
    int speed;
    
public:
    
    virtual int getPrice(int weight, int distance){
        cout <<" Цена не определена\n";
        return 0;
    }
    
    int getTime(int distance){
        return distance/speed;
    }
    
    string getType(){
        return type;
    }
    
    Vehicle(const Vehicle &other){
        type = other.type;
        speed = other.speed;
        
    }
    
    Vehicle(string type,int speed,int maxweight){
        this->type = type;
        this->speed = speed;

        
        
    }
    
    Vehicle(){
        type = "Не определен";
        speed = 0;
    }
    
    ~Vehicle(){};
};

class Car : public Vehicle{
    
public:
    
    Car(){
        type = "Truck";
        speed = 40;
    }
    
     int getPrice(int weight, int distance){
        return weight*distance/280;
    }
    
    ~Car(){};
    
};
class Train : public Vehicle{
    
public:
    
    Train(){
        type = "Train";
        speed = 30;
    }
    
    int getPrice(int weight, int distance){
        return 1000+weight*distance/400;
    }
    ~Train(){};
};


class Plane : public Vehicle{
    
public:
    
    Plane(){
        type = "Plane";
        speed = 300;
    }
    
    int getPrice(int weight, int distance){
        return 3000+weight*distance/160;
    }
    
    ~Plane(){};
};

class City{
    
private:
    string name;
    double latitude;
    double longitude;
    
public:
    City(){};
    
    City(string name, double latitude, double longitude){
        this->name = name;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    
    string getName(){
        return name;
    }
    
    double getLatitude(){
        return latitude;
    }
    
    double getLongitude(){
        return longitude;
    }
    
    ~City(){};
};

int distance(City City1, City City2)
{
   long int EARTH_RADIUS = 6372795;
    double PI = 3.14;
   
   double lat1 = City1.getLatitude() * PI / 180;
   double lat2 = City2.getLatitude() * PI / 180;
   double long1 = City1.getLongitude() * PI / 180;
   double long2 = City2.getLongitude() * PI / 180;
    
   double a = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(long2 - long1));
   return (EARTH_RADIUS * a)/1000;
}

int input(int a, int b){
    int input;
    
    while(true){
    cout << "--> ";
    cin >> input;
     if (cin.fail())
    {
           cout << "\nНекорректно, повторите ввод:" << endl;
        cin.clear();
        while(cin.get()!='\n');
        
    }
     else if ( input<a || input>b) cout << "\nНекорректно, повторите ввод:" << endl;
     else break;
    }
    
    return input;
}

City cityChoice(){
    int choice;
    cout<<"| 1 - Минск                          |\n";
    cout<<"| 2 - Москва                         |\n";
    cout<<"| 3 - Cанкт-Петербург                |\n";
    cout<<"| 4 - Вильнюс                        |\n";
    cout<<"| 5 - Варшава                        |\n";
    cout<<"| 6 - Прага                          |\n";
    cout<<"| 7 - Рига                           |\n";
    cout<<"| 8 - Таллин                         |\n";
    cout<<"--------------------------------------\n";
    choice = input(1, 8);
    switch (choice){
        case 1: return City("Minsk",53.9, 27.5667);
            break;
        case 2: return City("Moscow",55.7522, 37.6156);
            break;
        case 3: return City("St. Petersburg",59.9386, 30.3141);
            break;
        case 4: return City("Vilnius",54.6892, 25.2798);
            break;
        case 5: return City("Warsaw",52.2298, 21.0118);
            break;
        case 6: return City("Prague",50.088, 14.4208);
            break;
        case 7: return City("Riga",56.946, 24.1059);
            break;
        case 8: return City("Tallinn",59.437, 24.7535);
            break;
    }
    return City();
}



int main(int argc, const char * argv[]) {
    
    FILE *fp;

    Vehicle **transport = new Vehicle*[3];
    
    transport[0] = new Car();
    transport[1] =  new Train();
    transport[2] = new Plane();
    
    while(1){
    cout<<"\n--------------------------------------";
    cout<<"\n|       Выбор начальной точки        |";
    cout<<"\n|------------------------------------|\n";
    City City1 = cityChoice();
    City City2;
    
    while(1){
        cout<<"\n--------------------------------------";
        cout<<"\n|       Выбор конечной точки         |";
        cout<<"\n|------------------------------------|\n";
    City2 = cityChoice();
        if ( City1.getName() == City2.getName())
            cout << "\nНекорректный выбор. Один и тот же город был выбран два раза. Повторите попытку:\n";
        else break;}

    
    int dist = distance(City1, City2);
    
    
    cout <<"Введите вес груза (кг):\n";
    int weight;
    while(true){
    cout << "--> ";
    cin >> weight;
     if (cin.fail())
    {
           cout << "\nНекорректно, повторите ввод:" << endl;
        cin.clear();
        while(cin.get()!='\n');
        
    }
     else if ( weight<200 ) cout << "\nСлишком легкий груз, повторите ввод:" << endl;
     else if ( weight>20000) cout << "\nСлишком тяжелый груз, повторите ввод:" << endl;
     else break;
    }
    
    string one = " - ";
        
     printf(" \n ---------------------------------------------------------------------------------------\n");
        printf(" | Вид транспорта |           Маршрут         | Расстояние |      Цена     |    Время  |\n");
        printf(" |-------------------------------------------------------------------------------------|\n");
        for (int i=0; i<3;i++){
            printf(" | %14s | %25s |%6d (km) |%8d (BYN) | %4d (h)  |\n", transport[i]->getType().c_str(),(City1.getName()+one+City2.getName()).c_str(),  dist, transport[i]->getPrice(weight,dist), transport[i]->getTime(dist)  );
        printf(" |-------------------------------------------------------------------------------------|\n");
        }
        printf(" ---------------------------------------------------------------------------------------\n");
    
    int minimum = min(min(transport[0]->getPrice(weight,dist),transport[1]->getPrice(weight,dist)),transport[2]->getPrice(weight,dist));
    
    int i=0;
    while (i<3){
        if(transport[i]->getPrice(weight,dist)==minimum) break;
        i++;
    }
    cout <<" Наиболее дешевая поездка:\n";
    printf(" |-------------------------------------------------------------------------------------|\n");
        printf(" | %14s | %25s |%6d (km) |%8d (BYN) | %4d (h)  |\n", transport[i]->getType().c_str(),(City1.getName()+one+City2.getName()).c_str(),  dist, transport[i]->getPrice(weight,dist), transport[i]->getTime(dist)  );
    printf(" |-------------------------------------------------------------------------------------|\n");
    
    cout <<" Наиболее быстрая поездка:\n";
    printf(" |-------------------------------------------------------------------------------------|\n");
        printf(" | %14s | %25s |%6d (km) |%8d (BYN) | %4d (h)  |\n", transport[2]->getType().c_str(),(City1.getName()+one+City2.getName()).c_str(),  dist, transport[2]->getPrice(weight,dist), transport[2]->getTime(dist)  );
    printf(" |-------------------------------------------------------------------------------------|\n");
    
    cout<<"Записать данные в файл?\n";
    cout<<"1) - Да\n2) - Нет\n";
    int ch;
    ch = input(1, 2);
    if (ch==1){
        fp= fopen("INFO.txt","a+t");
        fprintf(fp, "Наиболее дешевая поездка:" );
        fprintf(fp, "| %s | %s |%d (km) |%d (BYN) | %d (h)| \n", transport[i]->getType().c_str(),(City1.getName()+one+City2.getName()).c_str(),  dist, transport[i]->getPrice(weight,dist), transport[i]->getTime(dist) );
        fprintf(fp, "Наиболее быстрая поездка:" );
    fprintf(fp, "| %s | %s |%d (km) |%d (BYN) | %d (h)| \n", transport[2]->getType().c_str(),(City1.getName()+one+City2.getName()).c_str(),  dist, transport[2]->getPrice(weight,dist), transport[2]->getTime(dist) );
        cout<<"Данные записаны в файл!\n";
    }
    
    
    cout<<"\nПродолжить?\n";
    cout<<"1) - Да\n2) - Выход\n";
    ch = input(1, 2);
    if (ch==2){
        cout<<"Программа завершена...\n";
        delete [] transport;
        exit(0);
    }
    }
    return 0;
}
