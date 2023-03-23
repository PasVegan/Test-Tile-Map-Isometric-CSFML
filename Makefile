SRCS	=	main_sprite.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS = -O3 -lm \
-Ofast -ftree-vectorize -masm=intel \
-march=native -fopenmp -ffast-math -mfpmath=sse -flto -mavx2 -funroll-loops \
-fno-inline -fno-builtin \
-lcsfml-graphics -lcsfml-system -lcsfml-window -I./include

all:
	@gcc $(SRCS) -o rpg $(CFLAGS)

debug: CFLAGS += -g3
debug: all

clean:
	@rm -rf *.o .idea/
	@find . -type f,d \( -name "*~" -o -name "\#*\#" \) -delete
	@find . -type f,d -name "vgcore*" -delete

fclean: clean
	@find . -name "rpg" -delete

re:	fclean all
