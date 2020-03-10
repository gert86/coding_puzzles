#include<QString>

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

// Conclusion:
// Egal wie ich ableite, innerhalb der Klasse kann ich immer nur auf public und protected der Basisklasse zugreifen.
// Die Art wie ich ableite bestimmt nur welches access Level man von außerhalb hat.
//   - DerivedPublic: Man kann nur auf public zugreifen (genaue wie bei Base)
//   - DerivedProtected: Kein Zugriff mehr von außen, auch public wurden inaccessible
//   - DerivedPrivate:   Kein Zugriff mehr von außen, auch public wurden inaccessible
// Ob auf members oder methods zugegriffen wird macht keinen Unterschied.
//
// Einen polymorphen Pointer kann man nur anlegen wenn public abgeleitet wurde!!!


using namespace std;

//---------------------------------------------------------------
class Base
{
private:
    int m_priv = 1;
    virtual void printPrivate()
    {
        cout << "Base::printPrivate." << endl;
        cout << "m_priv = " << m_priv << endl;
        cout << "m_prot = " << m_prot << endl;
        cout << "m_publ = " << m_publ << endl;
    }

protected:
    int m_prot = 2;
    virtual void printProtected()
    {
        cout << "Base::printProtected." << endl;
        cout << "m_priv = " << m_priv << endl;
        cout << "m_prot = " << m_prot << endl;
        cout << "m_publ = " << m_publ << endl;
    }

public:
    int m_publ = 3;
    virtual void printPublic()
    {
        cout << "Base::printPublic." << endl;
        cout << "m_priv = " << m_priv << endl;
        cout << "m_prot = " << m_prot << endl;
        cout << "m_publ = " << m_publ << endl;
    }
};

//---------------------------------------------------------------
class DerivedPrivate : private Base
{
public:
    void doSomethingWithMembers()
    {
        cout << "DerivedPrivate::doSomethingWithMembers." << endl;
        //cout << "m_priv = " << ++m_priv << endl;      // no access - private (even for derived classes)
        cout << "m_prot = " << ++m_prot << endl;
        cout << "m_publ = " << ++m_publ << endl;
    }

    void doSomethingWithMethods()
    {
        cout << "DerivedPrivate::doSomethingWithMethods." << endl;
        //printPrivate();                               // no access - private (even for derived classes)
        printProtected();
        printPublic();
    }
};

//---------------------------------------------------------------
class DerivedProtected : protected Base
{
public:
    void doSomethingWithMembers()
    {
        cout << "DerivedProtected::doSomethingWithMembers." << endl;
        //cout << "m_priv = " << ++m_priv << endl;      // no access - private (even for derived classes)
        cout << "m_prot = " << ++m_prot << endl;
        cout << "m_publ = " << ++m_publ << endl;
    }

    void doSomethingWithMethods()
    {
        cout << "DerivedProtected::doSomethingWithMethods." << endl;
        //printPrivate();                               // no access - private (even for derived classes)
        printProtected();
        printPublic();
    }
};

//---------------------------------------------------------------
class DerivedPublic : public Base
{
public:
    void doSomethingWithMembers()
    {
        cout << "DerivedPublic::doSomethingWithMembers." << endl;
        //cout << "m_priv = " << ++m_priv << endl;      // no access - private (even for derived classes)
        cout << "m_prot = " << ++m_prot << endl;
        cout << "m_publ = " << ++m_publ << endl;
    }

    void doSomethingWithMethods()
    {
        cout << "DerivedPublic::doSomethingWithMethods." << endl;
        //printPrivate();                               // no access - private (even for derived classes)
        printProtected();
        printPublic();
    }
};





//---------------------------------------------------------------
class DerivedProtectedPublic : public DerivedProtected
{
public:
    void doSomethingWithMembers()
    {
        cout << "DerivedProtectedPublic::doSomethingWithMembers." << endl;
        //cout << "m_priv = " << ++m_priv << endl;      // no access - private (even for derived classes)
        cout << "m_prot = " << ++m_prot << endl;
        cout << "m_publ = " << ++m_publ << endl;
    }

    void doSomethingWithMethods()
    {
        cout << "DerivedProtectedPublic::doSomethingWithMethods." << endl;
        //printPrivate();                               // no access - private (even for derived classes)
        printProtected();
        printPublic();
    }
};



//---------------------------------------------------------------
int main(int argc, char *argv[])
{    
    // outside access to Base
    Base base;
    //int a1 = base.m_priv;      // no access - private
    //int b1 = base.m_prot;      // no access - protected
    int c1 = base.m_publ;        // OK
    //base.printPrivate();       // no access - private
    //base.printProtected();     // no access - protected
    base.printPublic();          // OK

    // outside access to DerivedPrivate
    DerivedPrivate der_priv;
    //int a2 = der_priv.m_priv;      // no access - private
    //int b2 = der_priv.m_prot;      // no access - protected
    //int c2 = der_priv.m_publ;      // no access - inaccessible
    //der_priv.printPrivate();       // no access - private
    //der_priv.printProtected();     // no access - protected
    //der_priv.printPublic();        // no access - inaccessible

    // outside access to DerivedProtected
    DerivedProtected der_prot;
    //int a3 = der_prot.m_priv;      // no access - private
    //int b3 = der_prot.m_prot;      // no access - protected
    //int c3 = der_prot.m_publ;      // no access - inaccessible
    //der_prot.printPrivate();       // no access - private
    //der_prot.printProtected();     // no access - protected
    //der_prot.printPublic();        // no access - inaccessible

    // outside access to DerivedPublic
    DerivedPublic der_pub;
    //int a4 = der_pub.m_priv;      // no access - private
    //int b4 = der_pub.m_prot;      // no access - protected
    int c4 = der_pub.m_publ;        // OK
    //der_pub.printPrivate();       // no access - private
    //der_pub.printProtected();     // no access - protected
    der_pub.printPublic();          // OK


    // outside access to DerivedProtectedPublic
    DerivedProtectedPublic der_prot_pub;
    //zint a5 = der_prot_pub.m_priv;      // no access - private
    //int b5 = der_prot_pub.m_prot;      // no access - protected
    //int c5 = der_prot_pub.m_publ;      // no access - inaccessible
    //der_prot_pub.printPrivate();       // no access - private
    //der_prot_pub.printProtected();     // no access - protected
    //der_prot_pub.printPublic();        // no access - inaccessible



    //Base *polymorph_priv = new DerivedPrivate();      // Base is an inaccessible base of DerivedPrivate
    //Base *polymorph_prot = new DerivedProtected();    // Base is an inaccessible base of DerivedPrivate
    Base *polymorph_publ = new DerivedPublic();         // OK



    return 0;
}
