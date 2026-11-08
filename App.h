#include  "Table.h"
#include <string>

class App
{
public:
    App(const App& other) = delete;
    App& operator=(const App& other) = delete;
    
    static App& getApp();

    void run();
    void print();

    void setPath(const std::string& path);

    Table& getTable();
    std::string getPath() const;
private:
    App() = default;

    std::string path;
};