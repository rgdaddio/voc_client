# voc_client
g++ <client.cpp> <test_client.cpp> <client_db.cpp> <client_json.cpp>  -lboost_system -lboost_thread -lpthread  -lcrypto -lssl -ljson-c -lsqlite3 -o client

client <server> <schema name> <tenant_id> <public key>
