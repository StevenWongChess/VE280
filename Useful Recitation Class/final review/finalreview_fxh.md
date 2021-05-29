VE280 Final Review
===

#### August 4

###### Xiaohan Fu

<!-- page_number: true -->
<!-- footer: UM-SJTU Joint Institute, VE280SU2019-->

---

# Outline

1. Exercise for Virtual/Polymorphism
2. Note for Virtual Destructor
3. Exercise for STL

---

# Exercise for Virtual/Polymorphism

Read the following class declaration and implementation, try to write down the output of the main program.

header:
```cpp
//
// Created by Reapor Yurnero on 2019-08-04.
//

#ifndef FINAL_REVIEW_ANIMALS_D_H
#define FINAL_REVIEW_ANIMALS_D_H

class Animal {
public:
    virtual void Speak() = 0;

    virtual void Eat() = 0;
};

class Sick {

public:
    void TakeMed();

protected:
    int med;
};

class Cow : public Animal {

public:
    Cow(int f = 0);

    virtual void Speak();

    void Eat();

protected:
    int grass;
};

class SickCow : public virtual Cow, public Sick {

public:
    SickCow(int f = 0, int m = 0);

    void Speak();
};

class MadCow : public virtual Cow {

public:
    MadCow(int f = 0, int p = 0);

    void Speak();

    void TakePills();

protected:
    int pills;
};

class SickMadCow : public SickCow, public MadCow {

public:
    SickMadCow(int f = 0, int m = 0, int p = 0);

    void Speak();
};

#endif //FINAL_REVIEW_ANIMALS_D_H
```
implementation:
```cpp
//
// Created by Reapor Yurnero on 2019-08-04.
//

#include <iostream>
#include "animals-d.h"

using namespace std;

void Sick::TakeMed() {
    if (med > 0) {
        med--;
        cout << "I feel better\n";
    }

    else cout << "I'm dying\n";
}

Cow::Cow(int f) { grass = f; }

void Cow::Speak() { cout << "Moo.\n"; }

void Cow::Eat() {
    if (grass > 0) {
        grass--;
        cout << "Thanks I'm full\n";
    }

    else cout << "I'm hungry\n";
}

SickCow::SickCow(int f, int m) {
    grass = f;
    med = m;
}

void SickCow::Speak() { cout << "Ahem... Moo\n"; }

MadCow::MadCow(int f, int p) {
    grass = f;
    pills = p;
}

void MadCow::Speak() { cout << "Woof\n"; }

void MadCow::TakePills() {

    if (pills > 0) {
        pills--;
        cout << "Moof, that's better\n";
    }

    else cout << "Woof woof woof!\n";
}

SickMadCow::SickMadCow(int f, int m, int p) {
    grass = f;
    med = m;
    pills = p;
}

void SickMadCow::Speak() { cout << "Ahem... Woof\n"; }
```
Main:
```cpp
#include <iostream>
#include "animals-d.h"

using namespace std;

int main() {
    SickCow c1(1, 1);
    c1.Speak();
    c1.Eat();
    c1.TakeMed();
    c1.Eat();
    c1.TakeMed();
    cout << endl;
    MadCow c2(1, 1);
    c2.Speak();
    c2.Eat();
    c2.TakePills();
    c2.Eat();
    c2.TakePills();
    cout << endl;
    SickMadCow c3(1, 1, 1);
    c3.Speak();
    c3.Eat();
    c3.TakePills();
    c3.TakeMed();
    c3.Eat();
    c3.TakePills();
    c3.TakeMed();
    SickMadCow c4(1, 1, 0);
    Cow *c5 = &c4;
    c4.Speak();
    c4.Eat();
    c4.TakePills();
    c4.TakeMed();
    c5->Speak();
    c5->Eat(); //c5->TakePills(); c5->TakeMed();
}
```

Solution:
```
Ahem... Moo
Thanks I'm full
I feel better
I'm hungry
I'm dying

Woof
Thanks I'm full
Moof, that's better
I'm hungry
Woof woof woof!

Ahem... Woof
Thanks I'm full
Moof, that's better
I feel better
I'm hungry
Woof woof woof!
I'm dying
Ahem... Woof
Thanks I'm full
Woof woof woof!
I feel better
Ahem... Woof
I'm hungry
```

# Note for Virtual Destructor

Virtual member function is of great use also for destructors. See the following scenario:
```cpp
class TimeKeeper {
public:
    TimeKeeper();
    ~TimeKeeper();
    ...
};

class AtomClock: public TimeKeeper{ ... };
class WaterClock: public TimeKeeper { ... };
class WristWatch: public TimeKeeper { ... };


class TimeKeeperFactory
{
public:
     TimeKeeperFactory();
    ~ TimeKeeperFactory();
    TimeKeeper* getTimerKeeper(int i) {
        // a method in TimeKeepFactory, which returns a TimeKeeper's derived class
        if(i == 0){
            return new AtomClock();
        } else if (i == 1){
            return new WaterClock();
        } else if( i== 2){
            return new WristWatch();
        } else{
            throw std::invalid_argument( "invalid input" );
        }
    }

};


TimeKeeper* ptk = getTimerKeeper(1);
...
delete ptk;
```
This program is likely to have memory leak when these derived classes have their own allocted memory space.

Another typical example is when you are trying to inherit from a built-in class which has no virtual destructor
```cpp
SpecialString* pss = new SpecialString("xxxx");
std::string* ps;
...
ps = pss;
...
delete ps;
```

# Exercise for STL
Given a string array
```cpp
string colors[8] = {"red","blue","yellow","black", "green","green","red","red"};
```
Transform it into a vector and remove all duplicate elements from the color vector

Solution:
```cpp
//
// Created by Reapor Yurnero on 2019-08-04.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

bool cmp1(string s1, string s2) { return (s1.compare(s2) < 0); }

bool cmp2(string s1, string s2) { return (s1.compare(s2) == 0); }

int main() {
    string colors[8] = {"red", "blue", "yellow", "black", "green", "green", "red", "red"};
    vector<string> colorvect(colors, colors + 8);
    vector<string>::iterator it;
    sort(colorvect.begin(), colorvect.end(), cmp1);
    it = unique(colorvect.begin(), colorvect.end(), cmp2);
    colorvect.resize(distance(colorvect.begin(), it));
    for (it = colorvect.begin(); it != colorvect.end(); ++it)
        cout << ' ' << *it;
    cout << endl;
}
```