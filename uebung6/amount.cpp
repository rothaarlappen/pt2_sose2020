#include <ostream>
#include <iostream>
#include <string>
#include <iomanip>

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

	Amount operator=(Amount& amount){
		currency_ = amount.currency_;
		taxRate_ = amount.taxRate_;
		netto_ = amount.netto_;
		brutto_ = amount.brutto_;
		return *this;
	};

	Amount(const CURRENCY cur = EUR, const TAX_RATE TAX_RATE = NORMAL, float brutto = 0, float netto = 0, std::string text = "kein Name") : 
		currency_		{cur},
		taxRate_{TAX_RATE},
		brutto_	{	(netto)		? calculcateBrutto(): 	brutto},
		netto_	{ 	(brutto)	? calculateNetto()	: 	netto},
		text_ 	{text}
		{};

	// getter:
	CURRENCY getCur() {return currency_;};
	TAX_RATE getTaxRate() {return taxRate_;};

	float getTaxValue() { return brutto_ - netto_; };
	float getNetto() {return netto_;};
	float getBrutto() {return brutto_;};
	
	// setter:
	void convertToNewCurrency(CURRENCY newCurrency) { 
		brutto_ = brutto_ * changeRates_[newCurrency] / changeRates_[currency_];
		netto_ = netto_ * changeRates_[newCurrency] / changeRates_[currency_];
		currency_ = newCurrency;
	};

	void setTaxRate(TAX_RATE new_tax_rate) {
		taxRate_ = new_tax_rate;
		netto_ = calculateNetto();
	};
	void setNetto(float new_netto) {
		netto_ = new_netto;
		brutto_ = calculcateBrutto();
	};
	
	void setText (std::string newText){ text_ = newText; };

	void print(){
		std::cout << "Item: " << text_ << ", Brutto: " << std::fixed << std::setprecision(2) 
		<< brutto_ << getZeichen() << ", Netto: " << std::fixed << std::setprecision(2) 
		<< netto_ << getZeichen() << std::endl;
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
	
	std::string getZeichen(){
		return (currency_)? "$" : "€";
	}
	// Some magic only accountants understand
	float taxAsFactor(){ return (1+(taxRate_/100.0)); };
};


void test()
{
	// Todo 6.2
	// Implement tests? 
	std::cout << "Initialisiere ein Objekt des Typs Amount." << std::endl;
	Amount x = Amount(Amount::EUR, Amount::NORMAL, 0, 0);
	x.print();
	std::cout << "\n" << "Setze den Netto Wert auf 69 €" << std::endl;
	x.setNetto(69);
	x.print();
	std::cout << "\n" << "Setze die Währung auf USD" << std::endl;
	x.convertToNewCurrency(Amount::USD);
	x.print();
	std::cout << "\n" << "Wir wollen doch EUR haben :)" << std::endl;
	x.convertToNewCurrency(Amount::EUR);
	x.print();
	std::cout << "\n" << "'Kein Name' heißt jetzt Wassermelone" << std::endl;
	x.setText("Wassermelone");
	x.print();
	std::cout << "\n" << "Wassermelonen werden weniger besteuert, weil Baum:" << std::endl;
	x.setTaxRate(Amount::REDUCED);
	x.print();
	std::cout << "\n" << "Wir wollen eine zweite Wassermelone" << std::endl;
	Amount y = x;
	y.print();
	std::cout << "\n" << "Wir wollen Fahrrad mit Netto-Betrag" << std::endl;
	Amount f {Amount::EUR,Amount::NORMAL, 0,400.5, "Fahrrad"};
	f.print();
	std::cout << "\n" << "Wir wollen einen Betrag" << std::endl;
	Amount z {};
	z.print();

}

int main()
{
	test();
	return 0;
}
