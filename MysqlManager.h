#pragma once
#include<mysql.h>
#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Student {
	int id;
	string name;
	int age;
};

class MysqlManager {

public:

	MysqlManager();

	~MysqlManager();

public:

	bool insert_inf(Student& stu);
	bool update_inf(Student& stu);
	bool delete_inf(int id);
	vector<Student> query_inf(string condition);

public:

	MYSQL* con;

	// Mysql配置信息,数据库和表先自行创建
	const char* host = "127.0.0.1";
	const char* user = "root";
	const char* password = "2125jht";
	const char* database_name = "student_inf";
	const char* table_name = "student";

	// Mysql端口号 默认3306
	const int port = 3306; 

};