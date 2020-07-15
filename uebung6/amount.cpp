#include <ostream>
#include <iostream>

class Amount
{
private:
	// Todo 6.2
	// Implement class Amount
	int cur;
	float tax;
	float netto;
	float brutto;
	float change_rate[2] {1.0000, 1.1395};

public:

	enum {
		EUR,
		USD
	};

	enum {
		NOR = 16,
		RED = 5
	};

	Amount(){};

	Amount operator=(Amount& amount){
		cur = amount.get_cur();
		tax = amount.get_tax();
		netto = amount.get_netto();
		brutto = amount.get_brutto();
		return *this;
	};
	Amount(int cur = EUR, float tax = NOR, float brutto = 0, float netto = 0) : 
		cur{cur},
		tax{tax},
		brutto{(netto)? netto * (1+(tax/100)): brutto},
		netto{(brutto)? brutto / (1+(tax/100)): netto} {};

	// getter:
	int get_cur() {return cur;};
	float get_tax() {return tax;};
	float get_netto() {return netto;};
	float get_brutto() {return brutto;};

	// setter:
	void set_cur(int new_cur) { 
		brutto = brutto * change_rate[cur] * change_rate[new_cur];
		netto = netto * change_rate[cur] * change_rate[new_cur];
		cur = new_cur;
	};
	void set_tax(float new_tax) {
		tax = new_tax;
		netto = brutto / (1+(tax/100));
	};
	void set_netto(float new_netto) {
		brutto = new_netto;
		brutto = new_netto * (1+(tax/100));
	};
	void set_brutto(float new_brutto) {
		brutto = new_brutto;
		netto = brutto / (1+(tax/100));
	};

};


void test()
{
	// Todo 6.2
	// Implement tests
	Amount x = Amount(Amount::EUR,Amount::NOR,0,0);
	x.set_brutto(2);
	std::cout << "x -> 2" << std::endl;
	Amount y = x;
	std::cout << "some text" << std::endl;
	std::cout << x.get_brutto() << std::endl;
	std::cout << y.get_brutto() << std::endl;
	x.set_brutto(1.9);
	std::cout << "x -> 1.9" << std::endl;
	std::cout << x.get_brutto() << std::endl;
	std::cout << y.get_brutto() << std::endl;
	std::cout << "test all getters:" << std::endl;
	std::cout << x.get_brutto() << std::endl;
	std::cout << x.get_tax() << std::endl;
	std::cout << x.get_netto() << std::endl;
	std::cout << x.get_cur() << std::endl;
	std::cout << "Set to Dollar" << std::endl;
	x.set_cur(Amount::USD);
	std::cout << x.get_brutto() << std::endl;
	std::cout << x.get_tax() << std::endl;
	std::cout << x.get_netto() << std::endl;
	std::cout << x.get_cur() << std::endl;
}

int main()
{
	test();
	return 0;
}
