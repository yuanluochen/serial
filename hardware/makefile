INCLUDE = -I/home/yuanluochen/code/c/serial/include
OBJ = $(patsubst %.c,%.o, $(wildcard ./*.c)) #替换当前目录下所有.c文件的文件名
TARGET = hardware
$(TARGET):$(OBJ)
	mv $(OBJ) ../obj 
%.o:%.c
	gcc -c -g $^ -o $@ $(INCLUDE)

