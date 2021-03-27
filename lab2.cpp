#include <iostream>
#include <vector>

typedef struct s{
    float coefficient=0;
    int degree=0;

} monomial;

bool comparator(monomial &m1, monomial &m2){
    return m1.degree<m2.degree;
}

class polynomial{
private:
    std::vector <monomial> members;
public:
      void sort(){
        std::sort(members.begin(), members.end(), comparator);

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
    ~polynomial(){
            members.clear();
    }
    polynomial& operator = (const polynomial& p){
        if (&p != this)
            this->members=p.members;
        return *this;
    }
    bool operator == (const polynomial& p){
        if (members.size() == p.count()){
            for (int i=0; i<members.size(); i++)
                if (members[i].degree != p.degree(i) || members[i].coefficient != p.coefficient(i))
                    return false;
        }else
            return false;
        return true;
    }
    bool operator != (const polynomial& p){
        return !(*this == p);
    }
    polynomial& operator += (const polynomial& p){
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
    polynomial operator + (const polynomial& p){
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
    polynomial operator - (const polynomial& p){
        polynomial newp(*this);
        newp+=p;
        return newp;
    }
    polynomial& operator *=(int a){
        for (int i=0; i<members.size(); i++)
            members[i].coefficient*=a;
        return *this;
    }
    polynomial operator *(int a){
        polynomial newp(*this);
        newp*=a;
        return newp;
    }
    polynomial& operator /=(int a){
        for (int i=0; i<members.size(); i++)
            members[i].coefficient/=a;
        return *this;
    }
    polynomial operator /(int a){
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
