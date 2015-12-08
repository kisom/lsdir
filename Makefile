TARGET =	lsdir
CPPFLAGS =	-std=c++14
LDFLAGS =	-lc++

$(TARGET): $(TARGET).o
	clang -o $@ $(LDFLAGS) $(TARGET).o

$(TARGET).o: $(TARGET).cc
	clang -c $(CPPFLAGS) $(TARGET).cc

.PHONY: clean
clean:
	rm -f $(TARGET) $(TARGET).o
