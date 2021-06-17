CC				:= clang
CFLAGS			:= -Iinclude
LD				:= $(CC)
LD_FLAGS		:= 

RM				:= rm -rf

TARGET_SERVER	:= server
TARGET_CLIENT	:= client

CLIENT_SRC		:= $(addprefix src/client/, main.c)
CLIENT_OBJ		:= $(CLIENT_SRC:%.c=%.o)
SERVER_SRC		:= $(addprefix src/server/, main.c)
SERVER_OBJ		:= $(SERVER_SRC:%.c=%.o)

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(SERVER_OBJ)
	$(LD) $(LD_FLAGS) -o $(TARGET_SERVER) $(SERVER_OBJ)  

$(TARGET_CLIENT): $(CLIENT_OBJ)
	$(LD) $(LD_FLAGS) -o $(TARGET_CLIENT) $(CLIENT_OBJ)  

clean:
	$(RM) $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	$(RM) $(TARGET_CLIENT) $(TARGET_SERVER)

re: fclean all

%.o:%.c
	$(CC) $(CFLAGS) $< -c -o $@
