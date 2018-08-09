class Interface
{
public:
    Interface(){}
    virtual ~Interface(){}
    virtual void method1() = 0;    // "= 0" part makes this method pure virtual, and
                                   // also makes this class abstract.
    virtual void method2() = 0;

protected:
    using typeA = std::pair<int, int>;
    int newmember;
};

class Concrete : public Interface
{
private:
    int myMember;

public:
    Concrete(){}
    ~Concrete(){}
    void method1();
    void method2();
};

// Provide implementation for the first method
void Concrete::method1()
{
    newmember = 10;
}

// Provide implementation for the second method
void Concrete::method2()
{
    // Your implementation
}

class Concrete2 : public Concrete
{

public:
    Concrete2(){}
    ~Concrete2(){}
    void method1();
    void method2();
    void method3(typeA wew);
};
void Concrete2::method3(typeA wew)
{


}

// Provide implementation for the first method
void Concrete2::method1()
{
    newmember = 1;
}

// Provide implementation for the second method
void Concrete2::method2()
{
    // Your implementation
}

int main ()
{
  Interface *e = new Concrete();
  Interface *f = new Concrete2();
  e->method1();
  f->method1();
  delete f;
  return 0;
}