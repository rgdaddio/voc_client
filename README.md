# voc_client
g++ client.cpp test_client.cpp -lboost_system -lpthread -lboost_thread -lcrypto -lssl -lrt -ljson-c
./client <server> <schema name> <tenant_id> <public key>
