#include "async.h"
#include "BulkManager.h"

BulkManager bulk_unit;
namespace async {

handle_t connect(std::size_t bulk) {
    return bulk_unit.AddBulk(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size) {
    bulk_unit.Process(handle, std::string (data,size));
}

void disconnect(handle_t handle) {
    bulk_unit.RemoveBulk(handle);
}

}
