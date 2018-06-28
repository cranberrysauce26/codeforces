#include <bits/stdc++.h>
#define LOCAL
#ifdef LOCAL
#define DEBUG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define DEBUG(fmt, ...)
#endif

using namespace std;
#define szof(v) ((int)(v).size())
#define allof(v) begin(v), end(v)
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, ll> pll;

#include <iostream>
#include <string>
using namespace std;
 
  class fraction {
   private:
        int numerator;
        int denominator;
     
  public :
    int getNum() { return numerator; }
        int getDenom() { return denominator; }
        fraction();
        fraction(int, int);
          //fraction(int num = 1, int denom = 1):numerator(num), denominator(denom) {}
    fraction operator+(fraction);
        fraction operator-(fraction);
        fraction operator*(fraction);
        fraction operator/(fraction);
        fraction& operator++();
        fraction& operator--();
        bool operator==(fraction);
        bool operator!=(fraction);
        bool operator<(fraction);
        friend ostream& operator<<(ostream& out, const fraction& value);
        friend istream& operator>>(istream& in, fraction& value);
        string print();
};
 
  fraction::fraction(int num, int denom) {
        numerator = num;
        denominator = denom;
}
 
  fraction fraction::operator+(fraction Frac) {
        if (numerator == 0 || Frac.getNum() == 0) {
                if (numerator != 0) {
                        return fraction(numerator, denominator);
                    
        }
                else {
                    return fraction(Frac.getNum(), Frac.getDenom());
                    
        }
            
    }
        else {
                return fraction(
            (numerator * Frac.getDenom()) + (denominator * Frac.getNum()),
            denominator * Frac.getDenom());
                
    }
         
}
 
  fraction fraction::operator-(fraction Frac) {
        if (numerator == 0 || Frac.getNum() == 0) {
                if (numerator != 0) {
                        return fraction(numerator, denominator);
                    
        }
                else {
                    return fraction(Frac.getNum(), Frac.getDenom());
                    
        }
            
    }
        else {
                return fraction(
            (numerator * Frac.getDenom()) - (denominator * Frac.getNum()),
            denominator * Frac.getDenom());
                
    }
         
}
 
  fraction fraction::operator*(fraction Frac) {
        return fraction((Frac.getNum() * numerator),
                        (Frac.getDenom() * denominator));
}
 
  fraction fraction::operator/(fraction Frac) {
        return fraction((Frac.getNum() * denominator),
                        (Frac.getDenom() * numerator));
}
 
  bool fraction::operator==(fraction Frac) {
    return ((Frac.getNum() == numerator) && (Frac.getDenom() == denominator));
}
 
  bool fraction::operator!=(fraction Frac) {
    return ((Frac.getNum() != numerator) || (Frac.getDenom() != denominator));
}
 
  bool fraction::operator<(fraction Frac) {
    double first, second;
        if (denominator != 0) {
                first = numerator / (double)denominator;
            
    }
        else {
                first = 0.0;
            
    }
        if (Frac.getDenom() != 0) {
                second = Frac.getNum() / (double)Frac.getDenom();
            
    }
        else {
                second = 0.0;
            
    }
        return (first < second);
}
 
  fraction& fraction::operator++() {
        if (denominator != 0) {
                numerator += denominator;
                return *this;
            
    }
        else {
                cout << "Enter a proper fraction!";
            
    }
     
 
}
 
  fraction& fraction::operator--() {
        if (denominator != 0) {
                numerator -= denominator;
                return *this;
            
    }
        else {
                cout << "Enter a proper fraction!";
            
    }
     
 
}
 
  ostream& operator<<(ostream& out, const fraction& value) {
        out << value.numerator << "/" << value.denominator;
        return out;
}
 
  istream& operator>>(istream& in, fraction& value) {
        int num, denom;
        in >> num >> denom;
        value = fraction(num, denom);
        return in;
}

map<pair<fraction, fraction>, int> vals;
int y1[100], y2[100];
void mmain() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &y1[i]);
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d", &y2[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int i2 = 0; j2 < n; ++i2) {
                for (int j2 = 0; j2 < m; ++j2) {
                    if (i2==i && j2==j) continue;
                    int dy1 = y2[j]-y1[i];
                    int dy2 = y2[j2]-y1[i2];
                    if (dy1!=dy2) {
                        
                    }
                }
            }
        }
    }
}

int main() {
#ifdef LOCAL
    clock_t begin = clock();
    printf("*********Starting program*********\n\n");
    freopen("data.txt", "r", stdin);
#endif
    mmain();
#ifdef LOCAL
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("\nTime taken: %lf\n", elapsed_secs);
#endif
}