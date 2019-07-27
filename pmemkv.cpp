/*
 * pmemkv.cpp -- demo a persistent memory key-value store
 */

#include <iostream>
#include <cassert>
#include <libpmemkv.hpp>

using namespace pmem::kv;
using std::cerr;
using std::cout;
using std::endl;
using std::string;

auto PATH = "/pmem/kvfile";

const uint64_t SIZE = 1024 * 1024 * 1024;  // 1 Gig

/*
 * kvprint -- print a single key-value pair
 */
int kvprint(string_view k, string_view v) {
    cout << "key: " << k.data() << ", value: " << v.data() << endl;
    return 0;
}

int main() {

    pmemkv_config *cfg = pmemkv_config_new();
    assert(cfg != nullptr);

    if (pmemkv_config_put_string(cfg, "path", PATH) != PMEMKV_STATUS_OK) {
        cerr << pmemkv_errormsg() << endl;
        return 1;
    }

    if (pmemkv_config_put_uint64(cfg, "force_create", 1) != PMEMKV_STATUS_OK) {
        cerr << pmemkv_errormsg() << endl;
        return 1;
    }

    if (pmemkv_config_put_uint64(cfg, "size", SIZE) != PMEMKV_STATUS_OK) {
        cerr << pmemkv_errormsg() << endl;
        return 1;
    }

    // Create a key-value store using the "cmap" engine.
    db *kv = new db();
    assert(kv != nullptr);

    if (kv->open("cmap", cfg) != status::OK) {
        cerr << db::errormsg() << endl;
        return 1;
    }

    // add some keys and values
    if (kv->put("key1", "value1") != status::OK) {
        cerr << db::errormsg() << endl;
        return 1;
    }
    if (kv->put("key2", "value2") != status::OK) {
        cerr << db::errormsg() << endl;
        return 1;
    }
    if (kv->put("key3", "value3") != status::OK) {
        cerr << db::errormsg() << endl;
        return 1;
    }

    // iterate through the key-value store
    kv->get_all(kvprint);

    // Stop the engine.
    delete kv;

    return 0;
}
