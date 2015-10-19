CXX=g++
RM=rm -f
FLAGS=-g -Wall
LDFLAGS=-g
SSLLIB=-L/usr/lib -lssl -lcrypto

SRC=$(wildcard *.cpp)
OBJ=$(subst .cpp,.o,$(SRC))

all: set1 depend

set1: s1c1 s1c2 s1c3 s1c4 s1c5 s1c6 s1c7 s1c8

s1c1: b64.o hex.o set1_challenge1.o
	$(CXX) $(LDFLAGS) -o s1c1 b64.o hex.o set1_challenge1.o

s1c2: hex.o xor.o set1_challenge2.o
	$(CXX) $(LDFLAGS) -o s1c2 hex.o xor.o set1_challenge2.o

s1c3: hex.o xor.o identify.o set1_challenge3.o
	$(CXX) $(LDFLAGS) -o s1c3 hex.o xor.o identify.o set1_challenge3.o

s1c4: hex.o xor.o identify.o set1_challenge4.o
	$(CXX) $(LDFLAGS) -o s1c4 hex.o xor.o identify.o set1_challenge4.o

s1c5: hex.o xor.o set1_challenge5.o
	$(CXX) $(LDFLAGS) -o s1c5 hex.o xor.o set1_challenge5.o

s1c6: identify.o xor.o b64.o set1_challenge6.o
	$(CXX) $(LDFLAGS) -o s1c6 identify.o xor.o b64.o set1_challenge6.o

s1c7: b64.o set1_challenge7.o
	$(CXX) $(LDFLAGS) $(SSLLIB) -o s1c7 b64.o set1_challenge7.o

s1c8: xor.o hex.o identify.o set1_challenge8.o 
	$(CXX) $(LDFLAGS) -o s1c8 xor.o hex.o identify.o set1_challenge8.o

depend: .depend

.depend: $(SRC)
	$(RM) ./.depend
	$(CXX) $(FLAGS) -MM $^>>./.depend

clean:
	$(RM) $(OBJ)

dist-clean: clean
	$(RM) *~ .depend

include .depend
