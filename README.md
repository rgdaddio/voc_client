# voc_client<br>
This is a c++ VOC reference client application.<br>

What does it do? It caches web content like the SDK.<br>

//To build on Ubuntu machines<br>
sudo apt-get install libjson0 libjson0-dev<br>
sudo apt-get install sqlite3 libsqlite3-dev<br>
sudo apt-get install libboost-dev<br>
sudo apt-get install libboost-thread-dev<br>
sudo apt-get install libboost-regex-dev<br>
sudo apt-get install libboost-filesystem-dev<br>>
make

//To run and register<br>
client_app \<server\> \<schema name\> \<tenant_id\> \<public key\><br>

//Run ingester in the sub directory "test"<br>
test/test_ingest.py<br>

//To fill the cache type as the option<br>
cacheFill<br>

//To exit<br>
^C<br>

//To test<br>
\<path-to-browser\>/\<yourbrowser\> test/voc.html<br>
