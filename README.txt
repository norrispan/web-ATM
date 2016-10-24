Guide to complie the server and client:

Server:
	1. Open the terminal
	2. Copy and paste the following command then press enter

		c99 -o server server.c s_basic.c s_balance.c s_withdraw.c s_deposit.c s_transfer.c s_record.c -lpthread

Client
 	1. Open the terminal
	2. Copy and paste the following command then press enter

		c99 -o client client.c c_basic.c c_balance.c c_withdraw.c c_deposit.c c_transfer.c

Please keep all the .txt file in ./data folder
