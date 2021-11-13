.PHONY: force clean all

SOURCEFILES:= 	src/OMSMain.cpp	\
	        src/OMSToNse.cpp   \
	        src/ExchngConnector.cpp   \
	        src/OMSHandler.cpp   \
		src/TcpSocket.cpp

all:
	g++ -std=c++17 -g -Wall $(CFLAGS) $(SEARCHPATH) $(SOURCEFILES) $(LOCALFLAGS)

clean:
	rm -f bin/Test

force: clean all

SEARCHPATH +=	-I ./inc/

LOCALFLAGS += -o bin/OMSRun

