/*
*****************************************************************************
								DBS211 NAA
							Project 1 - Part 1
								Group 1

Project Manager:
Full Name  : Kiara Rina Pelenio (ToT)
Student ID#: 
Oracle ID  : 

Group Members:
Full Name  : Minchan (Chad) Song
Student ID#:
Oracle ID  :

Full Name  : Hiu (Bob) Pang Tang
Student ID#:
Oracle ID  :

Full Name  : Tian (Andrew) Ma
Student ID#: 100691211
Oracle ID  : A18

Full Name  : Ron Austin Saguros
Student ID#: 111045225
Oracle ID  : A25

*****************************************************************************
*/


#include <iostream>
#include <iomanip>
#include <occi.h>

using oracle::occi::Environment;
using oracle::occi::Connection;
using namespace oracle::occi;
using namespace std;

// This function is formatted to display the column names for Part 1.
void displayColumnNames() {
	cout.setf(ios::left);
	cout << setw(14) << "Employee Id" << setw(19) << "First Name" << setw(19) 
		 << "Last Name" << setw(18) << "Phone" << "Extension" << endl;
	cout.unsetf(ios::left);
	cout << string(12, '-') << "  " << string(17, '-') << "  " << string(17, '-') 
		 << "  " << string(16, '-') << "  " << string(9, '-') << endl;
}

// This function is formatted to display the row data for Part 1.
void displayRowData(ResultSet* rs) {
	cout.setf(ios::left);
	cout << setw(14) << rs->getInt(1);
	cout << setw(19) << rs->getString(2);
	cout << setw(19) << rs->getString(3);
	cout << setw(18) << rs->getString(4);
	cout << rs->getString(5) << endl;
	cout.unsetf(ios::left);
}

int main(void) {

	/* OCCI Variables */
	Environment* env = nullptr;
	Connection* conn = nullptr;
	Statement* stmt = nullptr;
	ResultSet* rs = nullptr;

	/* Used Variables */
	string user = "putYourUsernameHere";
	string pass = "putYourPasswordHere";
	string constr = "myoracle12c.senecacollege.ca:1521/oracle12c";

	try {
		/* Establish Connection */
		env = Environment::createEnvironment(Environment::DEFAULT);
		conn = env->createConnection(user, pass, constr);

		/* Creating a Statement for Report 1*/
		stmt = conn->createStatement(
			"SELECT		e.employeenumber," 
			"			e.firstname,"
			"			e.lastname,"
			"			o.phone,"
			"			e.extension "	
			"FROM	employees	e "
			"JOIN	offices		o "
			"ON		e.officecode = o.officecode "
			"WHERE	o.city LIKE 'San Francisco' "
			"ORDER BY e.employeenumber");

		/* Execute and Display Query Results if not empty */
		rs = stmt->executeQuery();
		
		if (!rs->next()) {
			cout << "ResultSet is empty." << endl;
		}
		else {
			
			/* Display Header */
			cout << string(25, '-') << " Report 1 (Employee Report) " << string(35, '-') << endl;
			displayColumnNames();

			/* Display Query Data */
			do {
				displayRowData(rs);
			} while (rs->next());

			cout << endl;
		}

		/* Creating a Statement for Report 2*/
		stmt = conn->createStatement(
			"SELECT	DISTINCT	m.employeenumber,"
			"					m.firstname,"
			"					m.lastname,"
			"					o.phone,"
			"					m.extension "
			"FROM	employees	m "
			"JOIN	employees	e "
			"	ON		e.reportsto = m.employeenumber "
			"JOIN	offices		o "
			"	ON		m.officecode = o.officecode "
			"ORDER BY m.employeenumber");

		/* Execute and Display Query Results if not empty */
		rs = stmt->executeQuery();

		if (!rs->next()) {
			cout << "ResultSet is empty." << endl;
		}
		else {

			/* Display Header */
			cout << string(25, '-') << " Report 2 (Manager Report) " << string(36, '-') << endl;
			displayColumnNames();

			/* Display Query Data */
			do {
				displayRowData(rs);
			} while (rs->next());
		}

		conn->terminateStatement(stmt);	
		env->terminateConnection(conn);
		Environment::terminateEnvironment(env);
	}
	catch (SQLException& sqlExcp) {
		cout << sqlExcp.getErrorCode() << ": " << sqlExcp.getMessage();
	}
	return 0;
}
