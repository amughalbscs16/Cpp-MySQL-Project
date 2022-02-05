#include "Transaction.hpp"

class Account {
private:
	string first_name;
	string last_name;
	string street_address;
	int unit;
	string city;
	string state;
	string zip;
	string dob;
	string ssn;
	string email_address;
	long long mobile_number;
	int account_number;
	// string string: 
	// merchant_num -> count_transactions
	map <string, int> negative_count_merchant;
	// merchant_num -> sum_transactions;
	map <string, double> negative_sum_transaction;
	// merchant_num -> count_transactions
	map <string, int> positive_count_merchant;
	// merchant_num -> sum_transactions;
	map <string, double> positive_sum_transaction;
	//merchant_num -> transaction_number -> Transaction 
	map < string, map<int, Transaction> > merchant_transactions;
	

public:
	Account()
	{

	}
	Account(string fname, string lname, string st_ad, int unit, string city, string state, string zip, string dob, string ssn, string email, long long mob_num, int acc_num)
	{
		this->set_first_name(fname);
		this->set_last_name(lname);
		this->set_street_address(st_ad);
		this->set_unit(unit);
		this->set_city(city);
		this->set_state(state);
		this->set_zip(zip);
		this->set_dob(dob);
		this->set_ssn(ssn);
		this->set_email_address(email);
		this->set_mobile_number(mob_num);
		this->set_account_number(acc_num);
	}
	void filter_transactions_rule_1()
	{
		// if key in map
		// if transaction_amount > 2*average
		// write info in a file.
		if (true)
		{
			return;
		}
		//
		else
		{
			return;
		}
	}
	void filter_transaction_rule_2() {

	}

	void add_transaction_merchant(Transaction trans)
	{
		/*
		// merchant_num -> count_transactions
		map <string, int> count_merchant_transactions;
		// merchant_num -> sum_transactions;
		map <string, double> sum_transaction;
		//merchant_num -> transaction_number -> Transaction 
		map < string, map<int, Transaction> > merchant_transactions;
		*/
		// if transaction positive
			// if a merchant in 
			// positive_merchant_count
			//	update value += 1
			// if a merchant not in positive_merchant_count
			// initialize with 0
		
		// Taking positives into account just in case (+ives are very low in number, and I was not sure if it is credit or debit) 
		if (trans.get_transaction_amount() > 0)
		{
			//If merchant in positive_count_merchant
			if (this->positive_count_merchant.find(trans.get_merchant_number()) != this->positive_count_merchant.end())
			{
				this->positive_count_merchant[trans.get_merchant_number()] += 1;
				this->positive_sum_transaction[trans.get_merchant_number()] += trans.get_transaction_amount();
			}
			else
			{
				this->positive_count_merchant.insert(pair<string, int>(trans.get_merchant_number(), 1));
				this->positive_sum_transaction.insert(pair<string, double>(trans.get_merchant_number(), trans.get_transaction_amount()));
			}
			cout << "positive value" << this->positive_count_merchant[trans.get_merchant_number()] << " " << this->positive_sum_transaction[trans.get_merchant_number()] << endl;

		}
		// If Negatives (Majority of the given cases)
		else if (trans.get_transaction_amount() < 0)
		{
			// If merchant in negative_count_merchant
			if (this->negative_count_merchant.find(trans.get_merchant_number()) != this->negative_count_merchant.end())
			{
				this->negative_count_merchant[trans.get_merchant_number()] += 1;
				this->negative_sum_transaction[trans.get_merchant_number()] += trans.get_transaction_amount();
			}
			else
			{
				this->negative_count_merchant.insert(pair<string, int>(trans.get_merchant_number(), 1));
				this->negative_sum_transaction.insert(pair<string, double>(trans.get_merchant_number(), trans.get_transaction_amount()));
			}
			cout << "negative value" << this->negative_count_merchant[trans.get_merchant_number()] << " " << this->negative_sum_transaction[trans.get_merchant_number()] << endl;

		}

		//if (map < string, map<int, Transaction> >)

			

		// if transaction negative
			
		/*
		//Rule 2
		if (this->get_state().compare(trans.get_merchant_state()) != 0)
		{
			cout << "Account ID:" << this->get_account_number() << " Trans " << trans.get_account_number() << " - ";
			cout << "Actual State: " << this->get_state() << " Merchant State:" << trans.get_merchant_state() << endl;
		}
		*/

		return;
	}
	double get_average_transaction(string merchant)
	{
		//return average transaction of a merchant.
		return 0.0;
	}
	void set_first_name(string first_name)
	{
		this->first_name = first_name;
	}
	void set_last_name(string last_name)
	{
		this->last_name = last_name;
	}
	void set_street_address(string address)
	{
		this->street_address = address;
	}
	void set_unit(int unit)
	{
		this->unit = unit;
	}
	void set_city(string city)
	{
		this->city = city;
	}
	void set_state(string state)
	{
		this->state = state;
	}
	void set_zip(string zip)
	{
		this->zip = zip;
	}
	void set_dob(string dob) {
		this->dob = dob;
	}
	void set_ssn(string ssn) {
		this->ssn = ssn;
	}
	void set_email_address(string email)
	{
		this->email_address = email;
	}
	void set_mobile_number(long long mobile_number) {
		this->mobile_number = mobile_number;
	}
	void set_account_number(int account_number)
	{
		this->account_number = account_number;
	}

	string get_first_name()
	{
		return this->first_name;
	}
	string get_last_name()
	{
		return this->last_name;
	}
	string get_street_address()
	{
		return this->street_address;
	}
	int get_unit()
	{
		return this->unit;
	}
	string get_city()
	{
		return this->city;
	}
	string get_state()
	{
		return this->state;
	}
	string get_zip()
	{
		return this->zip;
	}
	string get_dob() {
		return this->dob;
	}
	string get_ssn() {
		return this->ssn;
	}
	string get_email_address()
	{
		return this->email_address;
	}
	long long get_mobile_number() {
		return this->mobile_number;
	}
	int get_account_number()
	{
		return this->account_number;
	}

};