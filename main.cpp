#include <iostream>
#include <vector>
#include <cmath>

class point {
private:
    int x, y;
public:
    explicit point(int x=0, int y=0):
            x(x),y(y) {
    }
    point(const point& p) {
        this->x = p.x;
        this->y = p.y;
    }
    point & operator = (const point& p){
        this->x=p.x;
        this->y=p.y;
        return *this;
    }
    int kX() const{
        return this->x;
    }
    int kY() const{
        return this->y;
    }
};

class broken {
protected:
    std::vector <point> points;
public:
    explicit broken(const std::vector <point>& points):
            points(points){
    }
    broken(const broken& b) {
        this->points = b.points;
    }
    broken& operator = (const broken& b) {
        this->points = b.points;
        return *this;
    }
    int count() const{
        return this->points.size();
    }

    virtual double lenght() const{
        double l=0;
        for (int i=0; i<this->count()-1; i++)
            l+=sqrt(pow(this->points[i].kX()-this->points[i+1].kX(),2)+pow(this->points[i].kY()-this->points[i+1].kY(),2));
        return l;
    }
};

class closed : public broken{
public:
    virtual double lenght() const{
        double l=0;
        for (int i=0; i<this->count()-1; i++)
            l+=sqrt(pow(this->points[i].kX()-this->points[i+1].kX(),2)+pow(this->points[i].kY()-this->points[i+1].kY(),2));
        l+=sqrt(pow(this->points[0].kX()-this->points[this->count()-1].kX(),2)+pow(this->points[0].kY()-this->points[this->count()-1].kY(),2));
        return l;
    }
};

class polygon { // проверка на выпуклость
protected:
    std::vector <point> vertecies;
public:
    explicit polygon( const std::vector <point> &vertecies):
            vertecies(vertecies){
    }
    polygon(const polygon& p){
        this->vertecies=p.vertecies;
    }
    polygon& operator = (const polygon& p) {
        this->vertecies= p.vertecies;
        return *this;
    }
    int count() const{
        return this->vertecies.size();
    }
    bool convex() const{
        int s;
        if (((vertecies[1].kX() - vertecies[0].kX()) * (vertecies[2].kY() - vertecies[1].kY()) - (vertecies[1].kY() - vertecies[0].kY()) * (vertecies[2].kX() - vertecies[1].kX())) < 0)
            s = -1;
        else s = 1;
        for (int i = 1; i < vertecies.size() - 2; i++) {
            double v = (vertecies[i+1].kX() - vertecies[i].kX()) * (vertecies[i+2].kY() - vertecies[i+1].kY()) - (vertecies[i+1].kY() - vertecies[i].kY()) * (vertecies[i+2].kX() - vertecies[i+1].kX());
            if (v < 0 && s > 0) return false;
            if (v > 0 && s < 0) return false;
        }
        return true;
    }
    double perimetr() const{
        double p=0;
        for (int i=0; i< this->count()-1; i++)
            p+=sqrt(pow(this->vertecies[i].kX()-this->vertecies[i+1].kX(),2)+pow(this->vertecies[i].kY()-this->vertecies[i+1].kY(),2));
        p+=sqrt(pow(this->vertecies[0].kX()-this->vertecies[this->count()-1].kX(),2)+pow(this->vertecies[0].kY()-this->vertecies[this->count()-1].kY(),2));
        return p;
    }

    virtual double area() const{
        double s=0;
        for (int i=0; i< this->count()-1;i++)
            s+=this->vertecies[i].kX()*this->vertecies[i+1].kY() - this->vertecies[i+1].kX()*this->vertecies[i].kY();
        s+=this->vertecies[this->count()-1].kX()*this->vertecies[1].kY() - this->vertecies[1].kX()*this->vertecies[this->count()-1].kY();
        s= s/2;
        return s;
    }
};

class triangle : public polygon {
public:
    explicit triangle (const std::vector <point> &vertecies) : polygon(vertecies){
        if (vertecies.size() != 3)
            std::cout << "Error";
        else {
            double s1 = (this->vertecies[2].kX()-this->vertecies[0].kX())*(this->vertecies[1].kY()-this->vertecies[0].kY());
            double s2 = (this->vertecies[1].kX()- this->vertecies[0].kX())*(this->vertecies[2].kY()-this->vertecies[0].kY());
            if (s1 == s2)
                std::cout << "Error";
        }
    }
    virtual double area() const{
        double s=0.5*((this->vertecies[1].kX()- this->vertecies[0].kX())*(this->vertecies[2].kY()-this->vertecies[0].kY())-(this->vertecies[2].kX()-this->vertecies[0].kX())*(this->vertecies[1].kY()-this->vertecies[0].kY()));
        return s;
    }
};

class trapezoid : public polygon { //virtual площади
public:
    explicit trapezoid (std::vector <point> vertecies) : polygon(vertecies){
        if (vertecies.size() == 4){
            double cos1 = ((vertecies[0].kX()-vertecies[1].kX())*(vertecies[2].kX()-vertecies[3].kX())+ (vertecies[0].kY()-vertecies[1].kY())*(vertecies[2].kY()-vertecies[3].kY()))/(sqrt(pow(vertecies[0].kX()-vertecies[1].kX(),2)+pow(vertecies[0].kY()-vertecies[1].kY(),2))*sqrt(pow(vertecies[2].kX()-vertecies[3].kX(),2)+pow(vertecies[2].kY()-vertecies[3].kY(),2)));
            double cos2 = ((vertecies[1].kX()-vertecies[2].kX())*(vertecies[3].kX()-vertecies[0].kX())+ (vertecies[1].kY()-vertecies[2].kY())*(vertecies[3].kY()-vertecies[0].kY()))/(sqrt(pow(vertecies[1].kX()-vertecies[2].kX(),2)+pow(vertecies[3].kY()-vertecies[0].kY(),2))*sqrt(pow(vertecies[1].kX()-vertecies[2].kX(),2)+pow(vertecies[3].kY()-vertecies[0].kY(),2)));
            if(!((std::abs(cos1) == 1 and std::abs(cos2) != 1) or (std::abs(cos1) != 1 and std::abs(cos2) == 1)))
                std::cout << "Error";
            else{
                if (!this->convex())
                    std::cout << "Error";
            }
        }
        else
            std::cout << "Error";
    }
    virtual double area(){
        return 0;
    }
};

class correctpolygon : public polygon{ //проверка на углы
public:
    explicit correctpolygon( std::vector <point> vertecies) : polygon(vertecies){
        double side = (sqrt(pow(vertecies[0].kX()-vertecies[vertecies.size()-1].kX(),2)+pow(vertecies[0].kY()-vertecies[vertecies.size()-1].kY(),2)));
        for (int i=0; i< vertecies.size()-1; i++) {
            if (sqrt(pow(vertecies[i].kX() - vertecies[i + 1].kX(), 2) +
                     pow(vertecies[i].kY() - vertecies[i + 1].kY(), 2)) != side) {
                std::cout << "Error";
                return;
            }
        }
        if (!this->convex()) {
            std::cout << "Error";
            return;
        }
    }
};

int main(){

    return 0;
}