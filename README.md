# voc_client<br>
This is a c++ refence client application.<br>

What does it do? It caches web content like the SDK<br>

//To build<br>
sudo apt-get install libjson0 libjson0-dev<br>
sudo apt-get install sqlite3 libsqlite3-dev<br>
sudo apt-get install libboost-dev<br>
sudo apt-get install libboost-thread-dev<br>
sudo apt-get install libboost-regex-dev<br>
sudo apt-get install libboost-filesystem-dev<br>>
make

//To run<br>
client \<server\> \<schema name\> \<tenant_id\> \<public key\><br>

//To test<br>
\<path-to-browser\>/\<yourbrowser\> test/voc.html<br>
