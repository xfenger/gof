/* 
 * 备忘录模式是一个行为设计模式，允许在不透露类内部的细节实现类的复制和恢复对象以前的状态
 *
 *
 * 适用场景
 * 	  当你需要创建对象状态快照来恢复之前的状态时，可以使用备忘录模式
 * 	  	备忘录模式允许你复制对象中的全部状态（包括私有成员变量），并将其独立于对象进行保存。尽管大部分人因为‘撤销’才记得
 * 	  	使用这个设计模式，但其实他在处理事务时*（比如需要在出现错误时回滚一个操作）的过程中也必不可少
 * 	  当直接访问对象的成员变量、获取器或将设置器将导致封装器被突破时，可以使用该模式
 * 	   	备忘录让对象自行复制创其状态的快照。任何其他对象都不能读取，这保障了数据的安全性
 * 	优点
 * 		可以在不破坏对象封装性的情况下创建对象状态快照
 * 		可以通过负责人维护原发器状态历史记录来简化原发器代码
 * 	缺点
 * 		如果在程序中频繁地创建备份，程序将消耗大量的内存
 * 		负责人必须完整跟踪原发器的生命周期，这样才能销毁弃用备忘录
 * 		不能确保备忘录中的代码不被修改
 * 	关系
 */
 


#include<iostream>

#include<string>
#include<ctime>
#include<random>
class ConcreteMemento;
class Memento;
class Caretaker;
//原发器
using namespace std;
class Memento
{
	public:
		virtual string GetName()const =0;
		virtual string date()const = 0;
		virtual string status()const= 0;
};
class ConcreteMemento : public Memento
{
	private:
		string _status;
		string _date;
	public:
		ConcreteMemento(string status ):_status(status)
	{
		time_t now = time(0);
		_date = ctime(&now);	
	}
	string status() const override
	{
		return _status;
	}
	string GetName()const override
	{
	 return   _date + " /(" + _status.substr(0,9) + "...)";
	}
	string date()const override
	{
		return _date;
	}
};
class Originator
{
	string _status;
	string GenalRandomString(int length = 10)
	{
		const char alph[]  = "0123456789abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ";
		int stringslength = sizeof(alph) - 1;
		string str ;
		for(int i = 0; i <length ;i++)
			str+=alph[rand() %stringslength];
		return str;
	}
public:
	void Dosomething()
	{
		cout << "Originator: I'm do some thing ."<<endl;
		_status = GenalRandomString(50);
		cout << "Originator and status has changed to:"<< _status <<endl;
	}
	Originator(string status):_status(status)
	{
		cout << " Originator: My status has change to : "<< _status << endl;
	}
	Memento*  save()
	{
		return new ConcreteMemento(this->_status);
	}
	void restore(Memento* memento)
	{
		_status = memento->status();
		std::cout << "Originator : My status has change to " << _status <<endl;
	}
};
class Caretaker
{
	vector<Memento* > _que_memento;
	Originator* _Originator;
public:
	Caretaker(Originator* originator):_Originator(originator){}
	void backup()
	{
		cout << "Caretaker: saveing originator's status..."<< endl;
		_que_memento.push_back(_Originator->save());
	}
	void undo()
	{
		if(_que_memento.empty())return ;
		Memento* memento  = _que_memento.back();
		cout << " Caretaker : Restoring status to : " << memento-> GetName() << endl;
		try
		{
			_Originator->restore(memento);
		}
		catch(...)
		{
			this -> undo();
		}
	}
	void ShowHistory()const{
		cout << " Caretaker: Here 's the list of memento:"<<endl;
		for (Memento* memento : _que_memento)
			cout << memento->GetName() << endl;
	}
};


void clientcode()
{
	Originator* originator  = new Originator("ye-Ye-Xiao-xiao-feng-Feng");
	Caretaker*  caretaker   = new  Caretaker(originator);
	caretaker->backup();
	originator->Dosomething();
	caretaker->backup();
	originator->Dosomething();
	caretaker->backup();
	originator->Dosomething();
	caretaker->backup();
	originator->Dosomething();
	caretaker->backup();
	originator->Dosomething();
	caretaker->backup();
	cout << endl;
	caretaker->ShowHistory();
	cout << " now ,let's rollbsck"<< endl;
	caretaker->undo();
	cout << " now ,let's rollbsck"<< endl;
	caretaker->undo();
	delete originator;
	delete caretaker;
}
int main()
{
	
	srand(static_cast<unsigned int> (time(NULL)));
	clientcode();
	return 0;

}
