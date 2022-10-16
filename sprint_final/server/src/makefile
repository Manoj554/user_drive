all: release

release:
	gcc -o ../bin/server -Werror server.c  ./modules/handle-connection/HandleConnection.c ./modules/handle-connection/HandleConnection.h ./modules/delete-file/DeleteFile.c ./modules/delete-file/DeleteFile.h ./modules/authentication/Authentication.c ./modules/authentication/Authentication.h ./modules/common/Common.c ./modules/common/Common.h ./modules/list-all/ListAll.c ./modules/list-all/ListAll.h ./modules/push-download-file/PushDownloadFile.c ./modules/push-download-file/PushDownloadFile.h ./modules/get-user-file/GetUserFile.c ./modules/get-user-file/GetUserFile.h
