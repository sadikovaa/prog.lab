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
    point(const point& p):
            x(p.x), y(p.y){
    }
    point & operator = (const point& p){
        if (&p != this){
            this->x=p.x;
            this->y=p.y;
        }
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
        if(points.size() < 2)
            throw points.size();
    }
    broken(const broken& b):
            points(b.points){
    }
    broken& operator = (const broken& b) {
        if (&b != this)
            this->points = b.points;
        return *this;
    }
    int count() const{
        return this->points.size();
    }
    virtual double length() const{
        double l=0;
        for (int i=0; i<this->count()-1; i++)
            l+=sqrt(pow(this->points[i].kX()-this->points[i+1].kX(),2)+pow(this->points[i].kY()-this->points[i+1].kY(),2));
        return l;
    }
    point getpoint(int i) const{
        return points[i];
    }
    point back() const{
        return points.back();
    }
    point front() const {
        return points.front();
    }
};

class closed : public broken{
public:
    explicit closed (const  std:: vector <point>& points ) : broken(points){
        if(points.size() < 3)
            throw points.size();
    }
    double length() const override{
        double l= broken::length();
        l+=sqrt(pow(this->points.front().kX()-this->points.back().kX(),2)+pow(this->points.front().kY()-this->points.back().kY(),2));
        return l;
    }
};

class polygon {
protected:
    closed vertecies; // замкнутая ломанная!!
public:
    bool convex() const{
        int s;
        if (!(((vertecies.getpoint(1).kX() - vertecies.front().kX()) * (vertecies.getpoint(2).kY() - vertecies.getpoint(1).kY()) -
               (vertecies.getpoint(1).kY() - vertecies.front().kY()) * (vertecies.getpoint(2).kX() - vertecies.getpoint(1).kX())) < 0))
            s = 1;
        else s = -1;
        for (int i = 1; i < vertecies.count() - 2; i++) {
            double v = (vertecies.getpoint(i+1).kX() - vertecies.getpoint(i).kX()) * (vertecies.getpoint(i+2).kY() -vertecies.getpoint(i+1).kY())
                    - (vertecies.getpoint(i+1).kY() - vertecies.getpoint(i).kY()) * (vertecies.getpoint(i+2).kX() - vertecies.getpoint(i+2).kX());
            if (v < 0 && s > 0) return false;
            if (v > 0 && s < 0) return false;
        }
        return true;
    }
    explicit polygon( const std::vector <point> &vertecies):
            vertecies(vertecies){
            if (vertecies.size() < 3)
                throw vertecies.size();
            if (!this->convex())
                throw "Not convex!";
    }
    polygon(const polygon& p):
            vertecies(p.vertecies){
    }
    polygon& operator = (const polygon& p) {
        if (&p != this)
            this->vertecies= p.vertecies;
        return *this;
    }
    int count() const{
        return this->vertecies.count();
    }
    double perimetr() const{
        double p = this->vertecies.length();
        return  p;
    }

    virtual double area() const{
        double s=0;
        for (int i=0; i< this->count()-1;i++)
            s+=this->vertecies.getpoint(i).kX()*this->vertecies.getpoint(i+1).kY() - this->vertecies.getpoint(i+1).kX()*this->vertecies.getpoint(i).kY();
        s+=this->vertecies.back().kX()*this->vertecies.getpoint(1).kY() - this->vertecies.getpoint(1).kX()*this->vertecies.back().kY();
        s= s/2;
        return s;
    }
};

class triangle : public polygon {
public:
    explicit triangle (const std::vector <point> &vertecies) : polygon(vertecies){
            if (vertecies.size() != 3)
                throw vertecies.size();
            double s1 = (this->vertecies.getpoint(2).kX()-this->vertecies.front().kX())*(this->vertecies.getpoint(1).kY()-this->vertecies.front().kY());
            double s2 = (this->vertecies.getpoint(1).kX()- this->vertecies.front().kX())*(this->vertecies.getpoint(2).kY()-this->vertecies.front().kY());
            if (s1 == s2)
                throw "line";
    }
    double area() const override{
        double s=0.5*((this->vertecies.getpoint(1).kX()- this->vertecies.front().kX())*(this->vertecies.getpoint(2).kY()-this->vertecies.front().kY())-
                (this->vertecies.getpoint(2).kX()-this->vertecies.front().kX())*(this->vertecies.getpoint(1).kY()-this->vertecies.front().kY()));
        return s;
    }
};

class trapezoid : public polygon {
public:
    explicit trapezoid (std::vector <point> &vertecies) : polygon(vertecies){
            if (vertecies.size() != 4)
                throw vertecies.size();
            double cos1 = ((vertecies.front().kX()-vertecies[1].kX())*(vertecies[2].kX()-vertecies[3].kX())+ (vertecies.front().kY()-vertecies[1].kY())*(vertecies[2].kY()-vertecies[3].kY()))/(sqrt(pow(vertecies.front().kX()-vertecies[1].kX(),2)+pow(vertecies.front().kY()-vertecies[1].kY(),2))*sqrt(pow(vertecies[2].kX()-vertecies[3].kX(),2)+pow(vertecies[2].kY()-vertecies[3].kY(),2)));
            double cos2 = ((vertecies[1].kX()-vertecies[2].kX())*(vertecies[3].kX()-vertecies.front().kX())+ (vertecies[1].kY()-vertecies[2].kY())*(vertecies[3].kY()-vertecies.front().kY()))/(sqrt(pow(vertecies[1].kX()-vertecies[2].kX(),2)+pow(vertecies[3].kY()-vertecies.front().kY(),2))*sqrt(pow(vertecies[1].kX()-vertecies[2].kX(),2)+pow(vertecies[3].kY()-vertecies.front().kY(),2)));
            if(!((std::abs(cos1) == 1 and std::abs(cos2) != 1) or (std::abs(cos1) != 1 and std::abs(cos2) == 1)))
                throw "twisted";
    }
};

class correctpolygon : public polygon{
public:
    explicit correctpolygon( std::vector <point> &vertecies) : polygon(vertecies){
        double side = (sqrt(pow(vertecies.front().kX() - vertecies[vertecies.size() - 1].kX(), 2) +pow(vertecies.front().kY() - vertecies[vertecies.size() - 1].kY(), 2)));
        for (int i = 0; i < vertecies.size() - 1; i++)
            if (sqrt(pow(vertecies[i].kX() - vertecies[i + 1].kX(), 2) + pow(vertecies[i].kY() - vertecies[i + 1].kY(), 2)) != side)
                throw "different sides";
    }
};

int main(){

    return 0;
}
