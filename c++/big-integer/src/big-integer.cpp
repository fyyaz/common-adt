#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>

using std::cin;
using std::cout;
using std::endl;

const int MAXN = (int)1e5+2,POS = 1,NEG = -1;


class bigint{
    private:
        char dig[MAXN];
        int end,signbit;

    // stuff
    public:
        bigint();
        bigint(const std::string&v);
        bigint(int v);
        bigint(long long v);
        void print();

    // helper methods
    private:
        void add(const bigint &b);
        void sub(const bigint &b);
        void mul(const bigint &b);

    // arithmetic operators
    public:
        bigint operator +  (const bigint&b);
        bigint operator -  (const bigint&b);
        bigint operator *  (const bigint&b);
        bigint operator /  (const bigint&b);
        bigint operator %  (const bigint&b);

    // assignment operators
    public:
        void operator =  (const bigint&b);
        void operator =  (int v);
        void operator =  (long long v);
        void operator += (const bigint&b);
        void operator -= (const bigint&b);
        void operator *= (const bigint&b);
        void operator /= (const bigint&b);

    // boolean operators
    public:
        bool operator <    (const bigint&num)const;
        bool operator >    (const bigint&num)const;
        bool operator >=   (const bigint&num)const;
        bool operator <=   (const bigint&num)const;
        bool operator !=   (const bigint&num)const;
        bool operator ==   (const bigint&num)const;
};

// constructors
bigint::bigint(){
    dig[0] = '0';
    end = 0;
    signbit = POS;
}
bigint::bigint(const std::string&s){
    end = 0;
    if(s[0] == '-'){
        this->signbit = -1;
        for(int i = s.size()-1, j = 0;i>=1;i--)
            this->dig[j++] = s[i];
        this->end = s.size()-2;
    }
    else{
        this->signbit = 1;
        for(int i = s.size()-1, j = 0;i>=0;i--)
            this->dig[j++] = s[i];
        this->end = s.size()-1;
    }
}
bigint::bigint(int v){
    end = 0;
    this->dig[0] = '0';
    if(v >= 0)
        this->signbit = POS;
    else {
        this->signbit = NEG;
        v*=-1;
    }
    for(long long i = 0;i < MAXN && v!=0;i++){
        dig[i] = (v%10)+'0';
        v/=10;
        if(v!=0)
            end++;
    }
}
bigint::bigint(long long v){
    end = 0;
    this->dig[0] = '0';
     if(v >= 0)
        this->signbit = POS;
    else {
        this->signbit = NEG;
        v*=-1;
    }
    for(long long i = 0;i < MAXN && v!=0;i++){
        dig[i] = (v%10)+'0';
        v/=10;
        if(v!=0)
            end++;
    }
}

// helper methods
void bigint::add(const bigint &b){
    // simply increasing magnitude
    int e = std::max(this->end,b.end),carry = 0;
    for(int i = 0,sum = 0;i <= e+1;i++){
        sum = carry;
        carry = 0;
        if(!isdigit(this->dig[i]) && !isdigit(b.dig[i])&& sum == 0)
            break;
        else{
            if(isdigit(this->dig[i]))
                sum+= this->dig[i]-'0';
            if(isdigit(b.dig[i]))
                sum+= b.dig[i]-'0';
            if(sum >= 10){
                sum%=10;
                carry = 1;
            }
            this->dig[i] = sum+'0';
            this->end=i;
        }
    }
}
void bigint::sub(const bigint &b){
    int e = std::max(this->end,b.end), burrow = 0;
    for(int i = 0;i <= e;i++){
        int d = this->dig[i]-'0' - burrow;
        burrow = 0;
        if(isdigit(b.dig[i])){
            if(d-(b.dig[i]-'0') < 0){
                d+=10;
                burrow = 1;
                d-=b.dig[i]-'0';
            }else
                d-=b.dig[i]-'0';
        }
        if(!isdigit(b.dig[i])){
            if(d < 0){
                d+=10;
                burrow = 1;
            }
        }
        this->dig[i] = d+'0';
        this->end = i;
    }
    while(this->dig[this->end] == '0' && this->end !=0)
        this->end--;
    if(this->dig[this->end] == 0 && this->dig[0] == 0)// avoid -0
        this->signbit = POS;
}
void bigint::mul(const bigint &b){
    // TODO

}
void bigint::print(){
    if(signbit==NEG)printf("-");
    for(int i = end;i>=0;i--){
        printf("%c",dig[i]);
    }
    printf("\n");
}

// arithmetic operators
bigint bigint::operator +  (const bigint&b){
    bigint c(*this);
    c+=b;
    return c;
}
bigint bigint::operator -  (const bigint&b){
    bigint c(*this);
    c-=b;
    return c;
}
bigint bigint::operator *  (const bigint&b){
    bigint c(*this);
    c*=b;
    return c;
}
// assignment operators
void bigint::operator += (const bigint&b){
    if(this->signbit == POS && b.signbit == POS || this->signbit == NEG && b.signbit == NEG)
        this->add(b);
    else if(this->signbit == POS && b.signbit == NEG){
        if(*this >= b)
            this->sub(b);
        else{
            bigint a(*this);
            *this = b;
            this->sub(a);
        }
    }
    else if(this->signbit == NEG && b.signbit == POS){
        if(*this >= b)
            this->sub(b);
        else{
            bigint a(*this);
            *this = b;
            this->sub(a);
        }
    }
}
void bigint::operator -= (const bigint&b){
    if(this->signbit == POS && b.signbit == POS || this->signbit == NEG && b.signbit == NEG){
        if(*this >= b)
            this->sub(b);
        else{
            bigint a(*this);
            *this = b;
            this->sub(a);
            this->signbit = (this->signbit == POS && b.signbit == POS) ? NEG:POS;
        }
    }
    else if(this->signbit == POS && b.signbit == NEG || this->signbit == NEG && b.signbit == POS)
        this->add(b);
}
void bigint::operator *= (const bigint&b){
    if(this->signbit == NEG && b.signbit == NEG)
        this->signbit = POS;
    else if(this->signbit == NEG || b.signbit == NEG)
        this->signbit = NEG;
    this->mul(b);
}

void bigint::operator = (const bigint&b){
    strcpy(this->dig,b.dig);
    this->signbit = b.signbit;
    this->end = b.end;
}
void bigint::operator = (int v){
    end = 0;
    this->dig[0] = '0';
    if(v >= 0)
        this->signbit = POS;
    else {
        this->signbit = NEG;
        v*=-1;
    }
    for(long long i = 0;i < MAXN && v!=0;i++){
        dig[i] = (v%10)+'0';
        v/=10;
        if(v!=0)
            end++;
    }
}
void bigint::operator = (long long v){
    end = 0;
    this->dig[0] = '0';
    if(v >= 0)
        this->signbit = POS;
    else {
        this->signbit = NEG;
        v*=-1;
    }
    for(long long i = 0;i < MAXN && v!=0;i++){
        dig[i] = (v%10)+'0';
        v/=10;
        if(v!=0)
            end++;
    }
}

// boolean operators
bool bigint::operator <  (const bigint&b)const{
    if(this->end < b.end)
        return true;
    else if(this->end > b.end)
        return false;
    else{
        int e = std::min(this->end,b.end);
        for(int i = 0;i <= e;i++){
            if(this->dig[i]==b.dig[i])continue;
            return this->dig[i] < b.dig[i];
        }
    }
}
bool bigint::operator >  (const bigint&b)const{
    return !(*this < b);
}
bool bigint::operator >= (const bigint&b)const{
    return !(*this < b);
}
bool bigint::operator <= (const bigint&b)const{
    return !(b < *this);
}
bool bigint::operator != (const bigint&b)const{
    return (*this< b || b < *this);
}
bool bigint::operator == (const bigint&b)const{
    return !(*this!=b);
}

// ------------------------------divider ----------------------------------------

int main(){
    //freopen("input.txt","r",stdin);
    std::string s1,s2;
    cin >> s1 >> s2;
    bigint a(s1),b(s2);
    a+=b;
    a.print();
    return 0;
}
