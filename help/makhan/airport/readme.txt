

clang airport_client.c -o client
clang airport_server.c -pthread -o server

./server cases.txt
./client
<спрашивает ip сервера>

