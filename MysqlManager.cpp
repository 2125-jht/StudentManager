#include "MysqlManager.h"

MysqlManager::MysqlManager() {

	con = mysql_init(NULL);

	// 设置字符编码
	mysql_options(con, MYSQL_SET_CHARSET_NAME, "GBK");

	// 连接数据库
	bool connect_err = mysql_real_connect(con, host, user, password, database_name, port, NULL, 0);
	if (!connect_err) {
		fprintf(stderr, "Failed to connect to database : %s\n", mysql_error(con));
	}
	else {
		printf("Connect to mysql.\n");
	}

}

MysqlManager::~MysqlManager() {

	mysql_close(con);

}

bool MysqlManager::insert_inf(Student& stu) {

	char sql[256];
	sprintf_s(sql, "INSERT into %s values (%d,'%s',%d)", table_name, stu.id, stu.name.c_str(), stu.age);

	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to insert data : %s\n", mysql_error(con));
		return false;
	}
	else {
		printf("Finished the insert-sql.\n");
		return true;
	}

}

bool MysqlManager::update_inf(Student& stu) {

	// 按姓名更新
	char sql[256];
	sprintf_s(sql, "UPDATE %s SET id = %d, name = '%s', age = %d "
		"WHERE name = '%s'", table_name, stu.id, stu.name.c_str(), stu.age, stu.name.c_str());

	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to update data : %s\n", mysql_error(con));
		return false;
	}
	else {
		printf("Finished the update-sql.\n");
		return true;
	}

}

bool MysqlManager::delete_inf(int id) {

	// 按学号删除
	char sql[256];
	sprintf_s(sql, "DELETE FROM %s WHERE id = %d", table_name, id);

	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to delete data : %s\n", mysql_error(con));
		return false;
	}
	else {
		printf("Finished the delete-sql.\n");
		return true;
	}

}

vector<Student> MysqlManager::query_inf(string condition) {

	vector<Student> stuList;

	char sql[256];
	sprintf_s(sql, "SELECT * FROM %s ", condition.c_str());

	if (mysql_query(con, sql)) {
		fprintf(stderr, "Failed to query data : %s\n", mysql_error(con));
		return {};
	}

	MYSQL_RES* res = mysql_store_result(con);
	MYSQL_ROW row;
	while (row = mysql_fetch_row(res)) {
		Student stu;
		stu.id = atoi(row[0]);
		stu.name = row[1];
		stu.age = atoi(row[2]);

		stuList.push_back(stu);
	}

	printf("Finished the query-sql.\n");
	return stuList;

}