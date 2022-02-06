// Main.cpp
//
#include "Account.hpp"

MYSQL* make_mysql_conn()
{
	int port = 3306;
	const char* hostname = "localhost";
	const char* username = "root";
	const char* password = "admin";
	const char* database = "save";
	MYSQL* conn;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, hostname, username, password, database, port, NULL, 0);
	if (conn) {
		cout << "Successful connection to database!" << endl;
		return conn;
	}
	else
	{
		cout << "Connection to database unsuccessful!" << endl;
		return NULL;
	}
}

void read_transactions(MYSQL* conn, map<int, Transaction>& transactions, map<int, Account>& accounts)
{
	int count = 0;
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query = 
		"SELECT transaction_id, account_number, transaction_datetime, transaction_amount, post_date, merchant_number, merchant_description, merchant_state, merchant_category_code, transaction_number FROM transactions";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		//Add and process transactions
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			int transaction_id = stoi(row[0]);
			int account_number = stoi(row[1]);
			string transaction_datetime = row[2];
			
			double transaction_amount = stod(string(row[3]));
			string post_date = row[4];
			string merchant_number = row[5];
			string merchant_description = row[6];
			string merchant_state = row[7];
			int merchant_category_code = stoi(row[8]);
			int transaction_number = stoi(row[9]);
			
			
			Transaction new_transaction = Transaction(transaction_id, account_number, transaction_datetime, transaction_amount, post_date, merchant_number, merchant_description, merchant_state, merchant_category_code, transaction_number);		
			transactions.insert(pair<int, Transaction>(account_number, new_transaction));

			//Update merchant transactions in each account
			//cout << account_number;
			accounts[account_number].add_transaction_merchant(new_transaction);
			count++;
		}
		

	}
	else
	{
		cout << "Transactions Query failed: " << mysql_error(conn) << endl;
	}
	cout << "Total number of rows  " << count;
}

void read_accounts(MYSQL* conn, map<int, Account>& accounts)
{
	int qstate;
	MYSQL_ROW row;
	MYSQL_RES* res;
	string query = "SELECT first_name, last_name, street_address, unit, city, state, zip, dob, ssn, email_address, mobile_number, account_number FROM accounts";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			int unit_x = -1;
			string first_name = row[0];
			string last_name = row[1];
			string street_address = row[2];
			if (row[3] != NULL)
				unit_x = stoi(row[3]);
			string city = row[4];
			string state = row[5];
			string zip = row[6];
			string dob = row[7];
			string ssn = row[8];
			string email_address = row[9];
			long long mobile_number = stoll(row[10]);
			int account_number = stoi(row[11]);

			Account new_account = Account(first_name, last_name, street_address, unit_x, city, state, zip, dob, ssn, email_address, mobile_number, account_number);
			
			accounts.insert(pair<int, Account>(account_number, new_account));
		}
	}
	else
	{
		cout << "Accounts Query failed: " << mysql_error(conn) << endl;
	}
}

void apply_flag_rules(map<int, Account>& accounts, vector<Transaction_Account>& flagged_transactions_rule_1, vector<Transaction_Account>& flagged_transactions_rule_2)
{
	//Iterate over each of the accounts
	auto iter = accounts.begin();
	while (iter != accounts.end()) {
		//Call rule 1
		iter->second.filter_transactions_rule_1(flagged_transactions_rule_1);
		
		//Call rule 2
		iter->second.filter_transactions_rule_2(flagged_transactions_rule_2);
		
		++iter;
	}
	

}
void write_flagged_transactions(map<int, Account> accounts, vector<Transaction_Account>& flagged_transactions_rule_1, vector<Transaction_Account>& transactions_rule_2)
{

}

int main()
{
	MYSQL* conn = make_mysql_conn();
	map<int, Account> accounts;
	map<int, Transaction> transactions;
	vector<Transaction_Account> flagged_transactions_rule_1;
	vector<Transaction_Account> flagged_transactions_rule_2;
	if (conn) {
		read_accounts(conn, accounts);
		read_transactions(conn, transactions, accounts);
	}
	apply_flag_rules(accounts, flagged_transactions_rule_1, flagged_transactions_rule_2);
	for (int i = 0; i < flagged_transactions_rule_2.size(); i++)
	{
		cout << "Shopped State: " << flagged_transactions_rule_2[i].get_shopped_state() << "Actual: " << flagged_transactions_rule_2[i].get_actual_state() << endl;
	}
	for (int i = 0; i < flagged_transactions_rule_1.size(); i++)
	{
		cout <<  "Transaction Amount: " << flagged_transactions_rule_1[i].get_transaction_amount() << endl;
	}
	write_flagged_transactions(accounts, flagged_transactions_rule_1, flagged_transactions_rule_2);


	return 0;
}
