#include<iostream>
#include<map>
#include<string>
using namespace std;

/**/



enum  PROTOCOTYPE
{
	PROTOCOTYPE1 = 0,
	PROTOCOTYPE2 = 2

};
class abstractprototype
{	
	protected:
	string _protname;
	double _height;
public:
	abstractprototype(string& name):_protname(name){}
	virtual ~abstractprototype(){}
    virtual abstractprototype*  clone()= 0;
	void method(double height)
	{
	  _height = height;
	  cout << "_protname is " << _protname  << "_height " << _height << endl;	}
};


class contreteprototype1 : public abstractprototype
{
	double size1;
public:
		contreteprototype1(string& name,double _logh):abstractprototype(name),size1(_logh){}
		~contreteprototype1(){}
		virtual abstractprototype* clone(){return new contreteprototype1(this); }

};
class contreteprototype2 : public abstractprototype
{
	double size2;
public:
		contreteprototype2(string& name,double _logh):abstractprototype(name),size2(_logh){}
		~contreteprototype2(){}
		
		virtual abstractprototype* clone(){return new contreteprototype2(this);}
};

class protofactory
{
public:	
	map<PROTOCOTYPE, abstractprototype*> _map;
	protofactory(){
			_map[PROTOCOTYPE1] = new contreteprototype1("type1",50);
			_map[PROTOCOTYPE2] = new contreteprototype2("type2",2.3);

	}
	abstractprototype* clone(PROTOCOTYPE type)
	{	
		return _map[type] ->clone();
	}
	
	~protofactory(){
			delete _map[PROTOCOTYPE1];
			delete _map[PROTOCOTYPE2];
	}


};


int main()
{
  protofactory f;
  abstractprototype* ab1 =   f.clone(PROTOCOTYPE1);
  ab1->method(100);
  abstractprototype* ab2 =  f.clone(PROTOCOTYPE2);
  ab2 ->method(2.2);
  delete ab1;
  delete ab2;
 return 0;
}
