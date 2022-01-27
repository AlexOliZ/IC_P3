fcm.o: ./fcm.o
		g++ test_fcm.cpp fcm.cpp -o exec_fcm

lang.o:  ./lang.o
		g++ test_lang.cpp lang.cpp fcm.cpp -o exec_lang