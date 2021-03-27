#include <iostream>
#include <vector>
#include <algorithm>
typedef struct s{
    float coefficient=0;
    int degree=0;

} monomial;
bool comparator(const monomial &m1, const monomial &m2){
    return m1.degree<m2.degree;
}
class polynomial{
private:
    std::vector <monomial> members;

public:
    void sort(){
        std::sort(members.begin(), members.end(), comparator);
        for (int i=0; i< members.size()-1; i++){
            if (members[i].degree == members[i+1].degree){
                members[i].coefficient +=members[i+1].coefficient;
                for (int j=i+1; j< members.size()-1; j++)
                    members[j] = members[j+1];
                members.pop_back();
            }
        }

    }
    int count() const{
        return members.size();
    }
    int degree(int i) const{
        return members[i].degree;
    }
    float coefficient(int i) const{
        return members[i].coefficient;
    }
    monomial member(int i) const{
        return members[i];
    }
    explicit polynomial (std:: vector <monomial>&  members):
            members(members){
        sort();
    }
    polynomial (const polynomial& p):
            members(p.members){
        sort();
    }
    polynomial& operator = (const polynomial& p){
        if (&p != this)
            this->members=p.members;
        return *this;
    }
    ~polynomial(){
    }
    bool operator == (const polynomial& p) const{
        if (members.size() == p.count()){
            for (int i=0; i<members.size(); i++)
                if (members[i].degree != p.degree(i) || members[i].coefficient != p.coefficient(i))
                    return false;
        }else
            return false;
        return true;
    }
    bool operator != (const polynomial& p) const{
        return !(*this == p);
    }
    polynomial& operator += (const polynomial& p) {
        int j =0;
        for (int i=0; i < p.count(); i++){
            if (members[j].degree == p.degree(i))
                members[j].coefficient+=p.coefficient(i);
            else{
                while (j < members.size() && members[j].degree != p.degree(i))
                    j++;
                if (j == members.size()) {
                    members.push_back(p.member(i));
                    j=0;
                }
                else
                    members[j].coefficient+=p.coefficient(i);
            }
        }
        sort();
        return *this;
    }
    polynomial operator + (const polynomial& p) const{
        polynomial newp(*this);
        newp+=p;
        return newp;
    }
    polynomial& operator -= (const polynomial& p){
        int j =0;
        for (int i=0; i < p.count(); i++){
            if (members[j].degree == p.degree(i))
                members[j].coefficient-=p.coefficient(i);
            else{
                while (j < members.size() && members[j].degree != p.degree(i))
                    j++;
                if (j == members.size()) {
                    members.push_back(p.member(i));
                    j=0;
                }
                else
                    members[j].coefficient-=p.coefficient(i);
            }
        }
        sort();
        return *this;
    }
    polynomial operator - (const polynomial& p) const{
        polynomial newp(*this);
        newp+=p;
        return newp;
    }
    polynomial& operator *=(int a){
        for (int i=0; i<members.size(); i++)
            members[i].coefficient*=a;
        return *this;
    }
    polynomial operator *(int a)  const{
        polynomial newp(*this);
        newp*=a;
        return newp;
    }
    polynomial operator *= (const polynomial& p){
        std::vector <monomial> newp;
        for (int i=0; i< this->count(); i++)
            for (int j=0; j< p.count(); j++){
                monomial m;
                m.coefficient=this->coefficient(i)*p.coefficient(j);
                m.degree=this->degree(i)*p.degree(j);
                newp.push_back(m);
            }
        members = newp;
        sort();
        return *this;
    }
    polynomial operator *(const polynomial& p)  const{
        polynomial newp(*this);
        newp*=p;
        return newp;
    }
    polynomial& operator /=(int a){
        for (int i=0; i<members.size(); i++)
            members[i].coefficient/=a;
        return *this;
    }
    polynomial operator /(int a) const{
        polynomial newp(*this);
        newp/=a;
        return newp;
    }
    friend std::ostream& operator<<(std::ostream &out, const polynomial& p);
    friend std:: istream& operator>>(std::istream &in, polynomial&p);

};
std::ostream& operator<<(std::ostream &out, const polynomial& p){
    for (int i=0; i<p.members.size(); i++){
        if (p.members[i].coefficient>0)
            out << "+";
        out <<p.members[i].coefficient<<"x^"<<p.members[i].degree;
    }
    return  out;
}
std:: istream& operator>>(std::istream &in, polynomial& p){
    p.members.clear();
    int n;
    in >> n;
    for (int i=0; i<n; i++)
        in >> p.members[i].coefficient >> p.members[i].degree;
    return in;
}
int main(){


    return 0;
}
