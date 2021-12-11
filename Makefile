TARGET=cpplua.hpp
DEST=/usr/local/include/cpp-lua-parsing
install:
	@mkdir -vp $(DEST)
	@install -v $(TARGET) $(DEST)/$(TARGET)

uninstall:
	@rm -rfv $(DEST)

