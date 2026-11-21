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
    int curr_speed;
    bool is_engine_on;
    Car(string Brand_Name,string Model_name,int max_speed,int max_speed_rev,int max_gear){
        this->Brand_Name=Brand_Name;
        this->Model_name=Model_name;
        this->max_speed=max_speed;
        this->max_speed_rev=max_speed_rev;
        this->curr_speed=0;
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
    virtual void accelerate()=0;
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
class ManualCar:public Car{
    public:
    int max_gear;
    int curr_gear;
    ManualCar(string Brand_Name,string Model_name,int max_speed,int max_speed_rev,int max_gear):Car(Brand_Name,Model_name,max_speed,max_speed_rev,max_gear){
        this->Brand_Name=Brand_Name;
        this->Model_name=Model_name;
        this->max_speed=max_speed;
        this->max_speed_rev=max_speed_rev;
        this->curr_speed=0;
        this->max_gear=max_gear;
        this->curr_gear=0;
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
};
class ElectricCar:public Car{
public:
    int Battery_percentage;
    ElectricCar(string Brand_Name,string Model_name,int max_speed,int max_speed_rev,int Battery_percentage):Car(Brand_Name,Model_name,max_speed,max_speed_rev,0){
        this->Brand_Name=Brand_Name;
        this->Model_name=Model_name;
        this->max_speed=max_speed;
        this->max_speed_rev=max_speed_rev;
        this->curr_speed=0;
        this->Battery_percentage=Battery_percentage;
    }
    void accelerate(){
        if(!is_engine_on){
            cout<<"Engine is off. Start the engine first"<<endl;
            return;
        }
        if(curr_speed+20<max_speed){
            curr_speed+=20;
            Battery_percentage-=1;
            return;
        }
        curr_speed=max_speed;
        Battery_percentage-=1;
    }
};
void addCars(vector<ManualCar>&cars){
    cars.push_back(ManualCar("Bugatti","Chiron Super Sport 300+",490,40,7));
    cars.push_back(ManualCar("Ferrari","SF90 Stradale",340,35,8));
    cars.push_back(ManualCar("Lamborghini","Aventador Ultimae",355,35,7));
    cars.push_back(ManualCar("Porsche","911 Turbo S",330,32,8));
    cars.push_back(ManualCar("BMW","M3",305,30,7));
}
void addCars(vector<ElectricCar>&cars){
    cars.push_back(ElectricCar("Tesla","Model S Plaid",322,0,100));
    cars.push_back(ElectricCar("Lucid","Air Dream Edition",270,0,100));
    cars.push_back(ElectricCar("Porsche","Taycan Turbo S",260,0,100));
    cars.push_back(ElectricCar("Audi","e-tron GT RS",250,0,100));
    cars.push_back(ElectricCar("Rivian","R1T",250,0,100));
}
void Manualcar(vector<ManualCar>&cars){
    for(int i=0;i<cars.size();i++){
        cout<<"Car "<<i+1<<": "<<endl;
        cout<<"Brand Name: "<<cars[i].Brand_Name<<" ";
        cout<<"Model Name: "<<cars[i].Model_name<<endl;
    }
    int car_choice;
    cout<<"Enter your choice of car : ";
    cin>>car_choice;
    ManualCar* car=&cars[car_choice-1];
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
}
void Electriccar(vector<ElectricCar>&cars){
    for(int i=0;i<cars.size();i++){
        cout<<"Car "<<i+1<<": "<<endl;
        cout<<"Brand Name: "<<cars[i].Brand_Name<<" ";
        cout<<"Model Name: "<<cars[i].Model_name<<endl;
    }
    int car_choice;
    cout<<"Enter your choice of car : ";
    cin>>car_choice;
    ElectricCar* car=&cars[car_choice-1];
    while(true){
        cout<<"1.Start Engine"<<endl;
        cout<<"2.Accelerate"<<endl;
        cout<<"3.Brake"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"5.See Current Speed and Battery Percentage"<<endl;
        int choice;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                car->start();
                sleep(1);
                break;
            case 2:
                car->accelerate();
                sleep(1);
                break;
            case 3:
                car->Brake();
                sleep(1);
                break;
            case 4:
                car->curr_speed=0;
                cout<<"Exiting..."<<endl;
                sleep(1);
                break;
            case 5:
                cout<<"Current Speed: "<<car->curr_speed<<" km/h"<<endl;
                cout<<"Battery Percentage: "<<car->Battery_percentage<<"%"<<endl;
                sleep(1);
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
        if(choice==4){
            break;
        }
    }
}
int main(){
    vector<ManualCar>ManualCars;
    vector<ElectricCar> ElecCars;
    addCars(ManualCars);
    addCars(ElecCars);
    int choice;
    cout<<"Enter 1 for Manual Cars and 2 for Electric Cars: ";
    cin>>choice;
    if(choice==1) Manualcar(ManualCars);
    else if(choice==2) Electriccar(ElecCars);
    else cout<<"Invalid choice"<<endl;
    return 0;
}