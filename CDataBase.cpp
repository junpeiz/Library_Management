#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <regex>
#include <cctype>
#include <iterator>
#include <exception>
#include "CDataBase.h"
using namespace std;

CDataBase::CDataBase(string host, string user, string passwd, string db) {
	_host = host.c_str();
	_user = user.c_str();
	_passwd = passwd.c_str();
	_db = db.c_str();

	_bOpen = false;
	Open();
}

CDataBase::~CDataBase() {
	Close();
}

bool CDataBase::GetConState() {
	return _bOpen;
}

bool CDataBase::Open() {
	if (!mysql_init(&mysql)) {
		printf("\nFailed to initate MySQL connection ");
		return false;
	}
	if (!mysql_real_connect(&mysql, _host, _user, _passwd, _db, 0, NULL, 0)) {
		printf("Failed to connect to MySQL: Error: %s\n ", mysql_error(&mysql));
		return false;
	}
	printf("Logged on to database sucessfully\n ");
	_bOpen = true;
	return _bOpen;
}

void CDataBase::Close() {
	if (_bOpen) {
		mysql_close(&mysql);
		_bOpen = false;
	}
}

bool CDataBase::ExecuteSql(const char * chSql) {
	if (!GetConState())
		return false;
	if (mysql_real_query(&mysql, chSql, strlen(chSql)) == 0)
		return true;
}

MYSQL_RES * CDataBase::OpenRecordset(const char * chSql) {
	MYSQL_RES *rs = NULL;
	if (ExecuteSql(chSql)) {
		rs = mysql_store_result(&mysql);
	}
	return rs;
}

void CDataBase::FreeResult(MYSQL_RES *result) {
	if (result)
		mysql_free_result(result);
}

bool CDataBase::single_into_stock(string book_attr)
{
	vector<string> attributes;
	split(attributes, book_attr, ',');
	if (attributes.size() != book_attri_num){
		//throw invalid_argument("Invalid Single book in");
		return false;
	}
	string Select_Query("select * from book where bno = ");
	Select_Query += "\"" + (attributes[0]) + "\"" + ";";

	//judge if the book is already in the database 
	MYSQL_RES *res = NULL;
	res = OpenRecordset(Select_Query.c_str());
	if (res) 
	{
		if (res->row_count == 0)   //Insert a new book into the database
		{
			string Insert_demand("insert into book values(");
			for (auto i = 0; i < book_attri_num; ++i)
			{
				if (book_attri_type[i] == Char)
					Insert_demand += "\"" + attributes[i] + "\"";
				else if (book_attri_type[i] == Int)
					Insert_demand += attributes[i];
				Insert_demand += ",";
			}
			Insert_demand.back() = ')';
			Insert_demand += ";";
			ExecuteSql(Insert_demand.c_str());
		}
		else
		{
			string Update_demand("update book set ");
			Update_demand += "category = " + quote(attributes[1]) + ",";
			Update_demand += "title = " + quote(attributes[2]) + ",";
			Update_demand += "press = " + quote(attributes[3]) + ",";
			Update_demand += "year = " + attributes[4] + ",";
			Update_demand += "author = " + quote(attributes[5]) + ",";
			Update_demand += "price = " + attributes[6] + ",";
			Update_demand += "total = " + attributes[7] + ",";
			Update_demand += "stock = " + attributes[8] + " ";
			Update_demand += "where bno = " + quote(attributes[0]) + ";";
			ExecuteSql(Update_demand.c_str());
		}
	}
	else
		throw invalid_argument("Some error during the insertion(single book)");
	FreeResult(res);
}

bool CDataBase::bundle_into_stock(string file_path)
{
	fstream filein;
	filein.open(file_path.c_str(), ios::in);
	if (!filein)
		return false;
	while (!filein.eof()){
		string book_data;
		getline(filein, book_data);
		single_into_stock(book_data);
	}
	return true;
}

string CDataBase::borrowed_list(int &result_num, string cno)
{
	string result = "";
	string search_card_res = card_search(cno);
	if (search_card_res.empty()){
		//throw invalid_argument("There is no such cno in the card list");
		return result;
	}
	string search_query("select * from borrow where cno = ");
	search_query += cno;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	res = OpenRecordset(search_query.c_str());
	if (res)
	{
        result_num = res->row_count;
		if (res->row_count == 0){
			cout << "This cno hasn't borrowed any book" << endl;
			return result;
		}
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++) {
				result += string(row[t]) + ",";
			}
			result += "\n";
		}
	}
	else
		throw invalid_argument("Some error during the borrowed list searching");
	return result;
}

string CDataBase::book_search(int &row_num, string attribute, string search_key)
{
	string search_query("select * from book where ");
	search_query += attribute + " = " + quote(search_key);
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	res = OpenRecordset(search_query.c_str());
	string result = "";
	if (res)
	{
		row_num = res->row_count;
		if (res->row_count == 0){
			cout << "No such book" << endl;
			return result;
		}
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++) {
				result += string(row[t]) + ",";
			}
			result += "\n";
		}
	}
	else
		throw invalid_argument("Some error during the book searching");
	return result;
}

string CDataBase::book_range_search(int &row_num, string attribute, int low_bound, int up_bound)
{
    stringstream search_query;
    search_query << "select * from book where ";
	search_query << attribute << " between " << low_bound << " and " << up_bound;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	res = OpenRecordset(search_query.str().c_str());
	string result = "";
	if (res)
	{
		row_num = res->row_count;
		if (res->row_count == 0){
			cout << "No such book" << endl;
			return result;
		}
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++) {
				result += string(row[t]) + ",";
			}
			result += "\n";
		}
	}
	else
		throw invalid_argument("Some error during the book searching");
	return result;
}

string CDataBase::card_search(string cno)
{
	string search_query("select * from card where ");
	search_query += string("cno") + " = " + quote(cno);
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	res = OpenRecordset(search_query.c_str());
	string result = "";
	if (res)
	{
		while (row = mysql_fetch_row(res)) {
			for (int t = 0; t < mysql_num_fields(res); t++) {
				result += string(row[t]) + ",";
			}
			result += "\n";
		}
	}
	else
		throw invalid_argument("Some error during the card searching");
	return result;
}

bool CDataBase::borrow_book(string bno, string cno)
{
    int num = 0;
    string search_book_res = book_search(num, string("bno"), bno);
	if (search_book_res.empty()){
		throw std::invalid_argument("No such book");
		return false;
	}
	vector<string> book_info;
	split(book_info, search_book_res, ',');
	int book_stock = atoi(book_info[8].c_str());
	if (book_stock <= 0){
		throw std::invalid_argument("This book is out of stock");
		return false;
	}
	string update_book_query("update book set stock = stock - 1 where bno = ");
	update_book_query += quote(bno);
	string update_borrow_query("insert into borrow values(");
	stringstream temp;
	time_t current_time = time(nullptr);
	temp << current_time << "," <<current_time + max_borrow_time;
	update_borrow_query += quote(cno) + "," + quote(bno) + "," + temp.str() + ")";
	if (ExecuteSql(update_book_query.c_str()) && ExecuteSql(update_borrow_query.c_str()))
		return true;
	else{
		throw std::invalid_argument("Borrow the book failed");
		return false;
	}
}

bool CDataBase::return_book(string bno, string cno)
{
    int num = 0;
    string search_book_res = book_search(num, string("bno"), bno);
	if (search_book_res.empty()){
		throw std::invalid_argument("No such book number");
		return false;
	}
	string search_card_res = card_search(cno);
	if (search_card_res.empty()){
		throw std::invalid_argument("No such card number");
		return false;
	}
	string update_book_query("update book set stock = stock + 1 where bno = ");
	update_book_query += quote(bno);
	string update_borrow_query("delete from borrow where bno = ");
	update_borrow_query += quote(bno) + " and cno = " + quote(cno);
	if (ExecuteSql(update_book_query.c_str()) && ExecuteSql(update_borrow_query.c_str()))
		return true;
	else{
		throw std::invalid_argument("Return the book failed");
		return false;
	}
}

bool CDataBase::manage_card_insert(string card_info)
{
	vector<string> temp;
	split(temp, card_info, ',');
	if (temp.size() != card_attri_num || (temp[3] != string("T") && temp[3] != string("S"))){
		//throw invalid_argument("Invalid Card Information");
		return false;
	}
	string search_card_res = card_search(temp[0]);
	if (!search_card_res.empty()){
		//throw invalid_argument("This cno already in the list");
		return false;
	}
	string insert_query("insert into card values(");
	for (unsigned int i = 0; i < temp.size(); i++)
		if (i < temp.size() - 1)
			insert_query += quote(temp[i]) + ",";
		else
			insert_query += quote(temp[i]);
	insert_query += ")";
	if (ExecuteSql(insert_query.c_str()))
		return true;
	else{
		//throw invalid_argument("Insert new card into the list failed");
		return false;
	}
}

bool CDataBase::manage_card_update(string cno, const int index, string newinfo)
{
	if (index > 3){
		//throw std::logic_error("Out of range");
		return false;
	}
	string search_card_res = card_search(cno);
	if (search_card_res.empty()){
		//throw invalid_argument("There is no such cno in the card list");
		return false;
	}
	string update_query("update card set ");
	update_query += Card_Attributes[index] + " = " + quote(newinfo);
	update_query += "where cno = " + quote(cno);
	if (ExecuteSql(update_query.c_str()))
		return true;
	else{
		//throw invalid_argument("Update card information into the list failed");
		return false;
	}
}

bool CDataBase::manage_card_delete(string cno)
{
	string search_card_res = card_search(cno);
	if (search_card_res.empty()){
		//throw invalid_argument("There is no such cno in the card list");
		return false;
	}
	string delete_query("delete from card where cno = ");
	delete_query += quote(cno);
	if (ExecuteSql(delete_query.c_str()))
		return true;
	else{
		//throw invalid_argument("Delete the card from the list failed");
		return false;
	}
}

void split(vector<string> &elements, string str, const char flag)
{
	int begin = 0, pos = 0;
	string temp;
	pos = str.find(flag, begin);
	while (pos != string::npos){
		//delete the blank char
		while (str[begin] == ' ' || str[begin] == '\t' || str[begin] == '\n')
			begin++;
		temp.assign(str, begin, pos - begin);
		elements.push_back(temp);
		begin = pos + 1;
		pos = str.find(flag, begin);
	}
	//delete the blank char in the end of the string
	while (str[begin] == ' ' || str[begin] == '\t' || str[begin] == '\n')
		begin++;
	pos = str.length() - 1;
	while (str[pos] == ' ' || str[pos] == '\t' || str[pos] == '\n')
		pos--;
	temp.assign(str, begin, pos - begin + 1);
	elements.push_back(temp);
}

string quote(const string &str)
{
	return "\"" + str + "\"";
}
