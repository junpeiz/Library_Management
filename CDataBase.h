#ifndef CDATABASE_H
#define	CDATABASE_H

#include <cstdio>
#include <string>
#include <vector>
#include <mysql.h>

using namespace std;

const int book_attri_num = 9;
const int card_attri_num = 4;
//the max day of keeping a book is two weeks
const int max_borrow_time = 1209600;
enum attri_type{ Char, Int };
const vector<attri_type> book_attri_type ={Char, Char, Char, Char, Int, Char, Int, Int, Int};
const vector<string> Card_Attributes = { string("cno"), string("name"), string("department"), string("type") };

class CDataBase
{
public:
	CDataBase(string host, string user, string passwd, string db);
	~CDataBase();
	bool ExecuteSql(const char * chSql);
	MYSQL_RES * OpenRecordset(const char * chSql);
	void FreeResult(MYSQL_RES *result);

	bool single_into_stock(string book_attr);
	bool bundle_into_stock(string file_path);
    string borrowed_list(int &result_num, string cno);
	string book_search(int &row_num, string attribute, string search_key);
	string book_range_search(int &row_num, string attribute, int low_bound, int up_bound);
	string card_search(string cno);
	bool borrow_book(string bno, string cno);
	bool return_book(string bno, string cno);
	bool manage_card_insert(string card_info);
	bool manage_card_update(string cno, const int index, string newinfo);
	bool manage_card_delete(string cno);

private:
	MYSQL mysql;
	bool _bOpen;
	const char * _host;
	const char * _user;
	const char * _passwd;
	const char * _db;

protected:
	bool Open();
	void Close();
	bool GetConState();
};

void split(vector<string> &elements, string str, const char flag);
string quote(const string &str);

#endif	
