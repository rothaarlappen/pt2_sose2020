#include <ostream>
#include <iostream>
#include <string>

class Amount
{

public:

	enum CURRENCY{
		EUR,
		USD
	};
	enum TAX_RATE{
		NORMAL = 16,
		REDUCED = 5
	};

	Amount(){};
	// Sinn? Ist das gefragt?
	Amount operator=(Amount& amount){
		currency_ = amount.get_cur();
		taxRate_ = amount.get_tax_rate();
		netto_ = amount.get_netto();
		brutto_ = amount.get_brutto();
		return *this;
	};

	Amount(const CURRENCY cur = EUR, const TAX_RATE TAX_RATE = NORMAL, float brutto = 0, float netto = 0, std::string text = "") : 
		currency_		{cur},
		taxRate_{TAX_RATE},
		brutto_	{	(netto)		? calculcateBrutto(): 	brutto},
		netto_	{ 	(brutto)	? calculateNetto()	: 	netto},
		text_ 	{text}
		{};

	// getter:
	CURRENCY get_cur() {return currency_;};
	TAX_RATE get_tax_rate() {return taxRate_;};

	float get_tax_value() { return brutto_ - netto_; };
	float get_netto() {return netto_;};
	float get_brutto() {return brutto_;};
	
	// setter:
	void convertToNewCurrency(CURRENCY newCurrency) { 
		brutto_ = brutto_ * changeRates_[currency_] * changeRates_[newCurrency];
		netto_ = netto_ * changeRates_[currency_] * changeRates_[newCurrency];
		currency_ = newCurrency;
	};

	void set_tax_rate(TAX_RATE new_tax_rate) {
		taxRate_ = new_tax_rate;
		netto_ = calculateNetto();
	};
	void set_netto(float new_netto) {
		netto_ = new_netto;
		brutto_ = calculcateBrutto();
	};
	
	// Steht nicht in der Aufgabenstellung? Notwendig?
	void set_brutto(float new_brutto) {
		brutto_ = new_brutto;
		netto_ = calculateNetto();
	};

private:
	CURRENCY currency_;
	TAX_RATE taxRate_;
	float netto_;
	float brutto_;

	std::string text_;

	float changeRates_[2] {1.0000, 1.1395};

	float calculateNetto(){ 
		return brutto_ / taxAsFactor();
	};
	float calculcateBrutto(){
		return netto_ * taxAsFactor();
	};
	
	// Some magic only accountants understand
	float taxAsFactor(){ return (1+(taxRate_/100)); };
};


void test()
{
	// Todo 6.2
	// Implement tests? 
	Amount x = Amount(Amount::EUR, Amount::NORMAL, 0, 0);
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
	std::cout << x.get_tax_rate() << std::endl;
	std::cout << x.get_netto() << std::endl;
	std::cout << x.get_cur() << std::endl;
	std::cout << "Set to Dollar" << std::endl;
	x.convertToNewCurrency(Amount::USD);
	std::cout << x.get_brutto() << std::endl;
	std::cout << x.get_tax_rate() << std::endl;
	std::cout << x.get_netto() << std::endl;
	std::cout << x.get_cur() << std::endl;
}

int main()
{
	test();
	return 0;
}
