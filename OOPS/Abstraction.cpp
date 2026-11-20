#include<iostream>
#include<vector>
#include<ctime>
#include<unistd.h>
#include<string>
using namespace std;
class Car{
    public:
    string Brand_Name;
    string Model_name;
    int max_speed;
    int max_speed_rev;
    int max_gear;
    int curr_speed;
    int curr_gear;
    bool is_engine_on;
    Car(string Brand_Name,string Model_name,int max_speed,int max_speed_rev,int max_gear){
        this->Brand_Name=Brand_Name;
        this->Model_name=Model_name;
        this->max_speed=max_speed;
        this->max_speed_rev=max_speed_rev;
        this->max_gear=max_gear;
        this->curr_speed=0;
        this->curr_gear=0;
        this->is_engine_on=false;
    }
    void start(){
        if(is_engine_on){
            cout<<"Engine is already on"<<endl;
            return;
        }
        is_engine_on=true;
        cout<<"Engine started"<<endl;
    }
    void changeGear(string gear){
        if(gear=="r"||gear=="R"){
            if(curr_speed>0){
                cout<<"Cannot change to reverse gear while moving forward"<<endl;
                return;
            }
            curr_gear=-1;
            cout<<"Gear changed to Reverse"<<endl;
            return ;
        }   
        int gear_num=stoi(gear);
        if(gear_num<1 || gear_num>max_gear){
            cout<<"Invalid gear"<<endl;
            return;
        }
        curr_gear=gear_num;
        cout<<"Gear changed to "<<curr_gear<<endl;
    }
    void accelerate(){
        if(!is_engine_on){
            cout<<"Engine is off. Start the engine first"<<endl;
            return;
        }
        if(curr_gear==0){
            cout<<"Cannot accelerate in neutral gear"<<endl;
            return;
        }
        if(curr_gear==-1){
            if(curr_speed>0){
                cout<<"Cannot accelerate in reverse gear while moving forward"<<endl;
                return;
            }
            if(curr_speed+20<max_speed_rev){
                curr_speed+=20;
                return;
            }
            curr_speed=max_speed_rev;
            return;
        }
        if(curr_speed+20<max_speed){
            curr_speed+=20;
            return;
        }
        curr_speed=max_speed;
    }
    void Brake(){
        if(curr_speed==0){
            cout<<"Car is already stopped"<<endl;
            return;
        }
        curr_speed-=20;
        if(curr_speed<0){
            curr_speed=0;
        }
    }
};
void addCars(vector<Car>&cars){
    cars.push_back(Car("Bugatti","Chiron Super Sport 300+",490,40,7));
    cars.push_back(Car("Ferrari","SF90 Stradale",340,35,8));
    cars.push_back(Car("Lamborghini","Aventador Ultimae",355,35,7));
    cars.push_back(Car("Porsche","911 Turbo S",330,32,8));
    cars.push_back(Car("BMW","M3",305,30,7));
}
int main(){
    vector<Car>cars;
    int garage_size=5 ;
    addCars(cars);
    for(int i=0;i<garage_size;i++){
        cout<<"Car "<<i+1<<": "<<endl;
        cout<<"Brand Name: "<<cars[i].Brand_Name<<" ";
        cout<<"Model Name: "<<cars[i].Model_name<<endl;
    }
    Car* car;
    int choice ;
    cout<<"Enter the car number you want to select (1-5): ";
    cin>>choice;
    if(choice>=1 && choice<=garage_size){
        car=&cars[choice-1];
        cout<<"You have selected: "<<car->Brand_Name<<" "<<car->Model_name<<endl;
    }
    else{
        cout<<"Invalid choice!"<<endl;
    }
    while(true){
        cout<<"1.Start Engine"<<endl;
        cout<<"2.Change Gear"<<endl;
        cout<<"3.Accelerate"<<endl;
        cout<<"4.Brake"<<endl;
        cout<<"5.Exit"<<endl;
        cout<<"6.See Current Speed and Gear"<<endl;
        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                car->start();
                sleep(1);
                break;
            case 2:{
                string gear;
                cout<<"Enter the gear to change to (1-"<<car->max_gear<<") for reverse r: ";
                cin>>gear;
                car->changeGear(gear);
                cout<<"Current Gear: "<<car->curr_gear<<endl;
                sleep(1);
                break;
            }
            case 3:
                car->accelerate();
                sleep(1);
                break;
            case 4:
                car->Brake();
                sleep(1);
                break;
            case 5:
                car->curr_speed=0;
                car->curr_gear=0;
                cout<<"Exiting..."<<endl;
                sleep(1);
                break;
            case 6:
                cout<<"Current Speed: "<<car->curr_speed<<" km/h"<<endl;
                cout<<"Current Gear: "<<car->curr_gear<<endl;
                sleep(1);
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
        if(choice==5){
            break;
        }
    }
    return 0;
}