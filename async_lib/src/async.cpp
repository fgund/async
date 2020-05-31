#include "async.h"
#include "bulk.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include <sstream>

Bulk* bulk_unit;
namespace async {

handle_t connect(std::size_t bulk) {
    bulk_unit = new Bulk(bulk);
    auto console_logger = std::make_shared<ConsoleLogger>();
    auto file_logger = std::make_shared<FileLogger>();
    bulk_unit->GetResultNotifier().AddObserver(console_logger);
    bulk_unit->GetResultNotifier().AddObserver(file_logger);
    bulk_unit->GetTimeNotifier().AddObserver(file_logger);
    return reinterpret_cast<void*> (bulk_unit);
}

void receive(handle_t handle, const char *data, std::size_t size) {
    Bulk* blk = reinterpret_cast<Bulk*> (handle);
    std::stringstream sstream({data, size});
    std::string token;
    while (std::getline(sstream, token, '\n')){
        std::cout << "Token: "<<token <<'\n';
       blk->Process(std::move(token));
    }
}

void disconnect(handle_t handle) {
    Bulk* blk = reinterpret_cast<Bulk*> (handle);
    delete blk;
}

}
