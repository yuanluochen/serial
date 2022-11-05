TARGET = a.out
$(TARGET):clean all
all:
		make -C ./app
		make -C ./hardware
		make -C ./main
		make -C ./obj

.PHONY:clean
clean:
		make -C ./obj clean
		$(RM) $(TARGET)