class items {
  private:
    //vector used to clear out vectors
    vector<string> emptyVector;

    //vector with the columWidths for display functions
    int columnSpace;
    vector<int> columnWidths;

    string tableType;

    //objects to be inserted into hash table
    struct item {
      string key;
      vector<string> data;
      //defualt constructor
      item() {
        vector<string> emptyVector;
        key = "";
        data = emptyVector;
      }
    };

    //hash table - initalize with 2000 buckets to avoid rehashing
    vector<item> p = vector<item>(2000);
  public:
    //constructor
    items(string _tableType) {
      tableType = _tableType;
      columnWidths.push_back(0);
      columnSpace = 2;
    }
    ~items() {}
    //utility functions
    int hashF(string);
    void updateTableSizes();
    vector<string> query(vector<string>);
    //hash table functions
    bool insert(vector<string>, string);
    bool delete_(vector<string>);
    bool update(vector<string>, string);
    void select(vector<string>);
    void display();
    void display(string);
    void write(int, string);
    void project(vector<string> query, vector<string> selCol);
};
