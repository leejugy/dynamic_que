OBJ=main
FILES=main.c dynamic_que.c que_ctl.c
all:
	$(CC) -o $(OBJ) $(FILES)