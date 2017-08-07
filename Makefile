all_console: build_console run_console
clean:
	rm main.exe
build_console:
	g++ console_main.cpp -o console_main.exe -lfcgi++ -lfcgi -lcurl -lcurlpp -pthread -lstdc++fs -lmysqlclient -I./
run_console:
	./console_main.exe
