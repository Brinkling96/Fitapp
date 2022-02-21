static std::array<char*,5> inputs = {"I am the exe name","testDB","5433","sean","testdb"};

struct TestDB{
    DB_connection* conn;

    TestDB();

    ~TestDB();
    
    private:

    void createTestTables();

    void insertData();
};