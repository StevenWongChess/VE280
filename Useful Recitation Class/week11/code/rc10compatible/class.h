// class.h
class Base {
public: string a;
Base(const Base& base)
: str(base.a) {
    cout << "cp Base\n"; }
void print() {
    cout << a << endl; }
};
class Derived : public Base {
public: // ... 
Derived(const Derived& d)
: Base(d) {
    cout << "cp Derived\n"; }
};