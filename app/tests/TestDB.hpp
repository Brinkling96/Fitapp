
class DB_connection;

struct TestDB{

    DB_connection* conn;
    
    TestDB();
    ~TestDB();
    
    private:
    void createTestTables();

    void insertData();
};
