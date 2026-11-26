#include<iostream>
#include<vector>
using namespace std;
class Products{
private:
    string product_name;
    double product_price;
public:
    Products(string name,double price){
        product_name=name;
        product_price=price;
    }
    void setProductName(string name){
        product_name=name;
    }
    void setProductPrice(double price){
        product_price=price;
    }
    string getProductName(){
        return product_name;
    }
    double getProductPrice(){
        return product_price;
    }
};
class shoppingCart{
private:
    vector<Products*> products;
public:
    void addProduct(Products* product){
        products.push_back(product);
    }
    void removeProduct(int idx){
        if(idx >= 0 && idx < products.size()){
            products.erase(products.begin() + idx);
        }
    }
    void showProducts(){
        cout<<"Products in the cart:"<<endl;
        for(int i=0;i<products.size();i++){
            cout<<products[i]->getProductName()<<" - "<<products[i]->getProductPrice()<<endl;
        }
    }
    double calculateTotalPrice(){
        double total_price=0;
        for(int i=0;i<products.size();i++){
            total_price+=products[i]->getProductPrice();
        }
        return total_price;
    }
    void printInvoice(){
        cout<<"Invoice:"<<endl;
        for(int i=0;i<products.size();i++){
            cout<<products[i]->getProductName()<<" - "<<products[i]->getProductPrice()<<endl;
        }
        for(int i=0;i<products.size();i++){
            cout<<" - ";
        }
        cout<<"Total: "<<calculateTotalPrice()<<" - "<<endl;
    }
};
void addProduct(shoppingCart* cart){
    Products* product1 = new Products("Laptop",1000);
    Products* product2 = new Products("Mouse",50);
    Products* product3 = new Products("Keyboard",80);
    cart->addProduct(product1);
    cart->addProduct(product2);
    cart->addProduct(product3);
}
int main(){
    shoppingCart* cart = new shoppingCart();
    addProduct(cart);
    cart->showProducts();
    cart->printInvoice();
    return 0;
}