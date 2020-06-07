#ifndef BULK_MANAGER
#define BULK_MANAGER

#include <map>
#include "bulk.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"

class BulkManager
{
public:
    int AddBulk(std::size_t bulk_size){

        int key = std::size(bulks) + 1;
        std::shared_ptr<ConsoleLogger> console_logger = std::make_shared<ConsoleLogger>();
        std::shared_ptr<FileLogger> file_logger = std::make_shared<FileLogger>();
        bulks[key] = std::make_unique<Bulk>(bulk_size);
        bulks[key]->GetResultNotifier().AddObserver(console_logger);
        bulks[key]->GetResultNotifier().AddObserver(file_logger);
        bulks[key]->GetTimeNotifier().AddObserver(file_logger);

        return key;
    }
    void Process(int key, std::string cmd){
        std::string::size_type iter;
        std::string tmp = unfinished_cmds[key];
        tmp.append(cmd);
        while((iter = tmp.find('\n')) != tmp.npos) {
            bulks[key]->Process(tmp.substr(0,iter));
            tmp = tmp.substr(iter+1);
        }
        unfinished_cmds[key] = tmp;
    }
    void RemoveBulk(int key){
        bulks.erase(key);
    }

private:

    std::map<int, std::string> unfinished_cmds;
    std::map <int, std::unique_ptr<Bulk> > bulks;
};

#endif //BULK_MANAGER