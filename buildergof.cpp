#include<iostream>
#include<vector>
#include<string>
using namespace std;
     
class Product1{
public:
	vector<string> parts_;
public:
	void ListPart() const
	{
		std::cout<< "Product parts_: ";
		for(const auto& i : parts_)
			if(i == parts_.back())
				std::cout << i;
			else
				std::cout <<i << ",";

		std::cout <<"\n\n";
	}
};

class Builder
{
public:
	virtual ~Builder(){}
	virtual void ProductPartA() const = 0;
	virtual void ProductPartB() const = 0;
	virtual void ProductPartC() const = 0;
};

class ConcreteBuilder : public Builder
{
	Product1* product;
public:
	ConcreteBuilder()
	{
		Reset();
	}	
	~ConcreteBuilder()
	{
		delete product;
	}
	void Reset()
	{
		product = new Product1();
	}
	void ProductPartA()const override
	{
		product->parts_.push_back("PartA1");
	}
	void ProductPartB()const override
	{
		product->parts_.push_back("PartB2");
	}
	void ProductPartC()const override
	{
		product->parts_.push_back("PartC#");
	}
	Product1* GetProduct()
	{
		Product1* result= product;
		Reset();
		return result;
	}
};

class Director
{
	Builder* _builder;
public:
	void set_builder(Builder* builder)
	{
		_builder=builder;
	}
	void BuildMinmaViableProduct()
	{
		_builder->ProductPartA();
	}
	void BuildFullFeaturedProduct()
	{
		_builder->ProductPartA();
		_builder->ProductPartB();
		_builder->ProductPartC();
	}
};
void ClientCode(Director& director)
{
	ConcreteBuilder* builder  = new ConcreteBuilder();
	director.set_builder(builder);
	cout << "Standard basic product:\n";
	director.BuildMinmaViableProduct();


	Product1 *p = builder->GetProduct();
	p->ListPart();
	delete p;
	
	cout << "Standard full featured product:\n";

	director.BuildFullFeaturedProduct();
	
	p = builder->GetProduct();
	p->ListPart();
	delete p;
	p=nullptr;

	cout << " Costom product:\n";
	builder->ProductPartA();
	builder->ProductPartB();
	builder->ProductPartC();
	p=builder->GetProduct();
	p->ListPart();
	delete p;
	delete builder;
}

int main()
{
	Director* director = new Director();
	ClientCode(*director);
	delete director;
	return 0;
}
