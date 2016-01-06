TARGET = chatserver
OUT_DIR= ./bin

INCLUDES = -I ./include
CCFLAGS =  

CC = g++

LIBS = -lpthread

############################
#files and dirs

SRC_DIR = ./src

SRCS_cpp = $(foreach n,$(SRC_DIR),$(wildcard $(n)/*.cpp)) $(foreach n,$(SRC_DIR),$(wildcard $(n)/*.c))

###############################
#OBJS
SUB_OUT_DIR = $(addprefix $(OUT_DIR)/OBJS/,$(SRC_DIR))
$(shell mkdir -p $(OUT_DIR) $(OUT_DIR)/OBJS $(SUB_OUT_DIR))
LOBJS = $(patsubst %.cpp,%.o,$(SRCS_cpp))
OUT_OBJS = $(addprefix $(OUT_DIR)/OBJS/,$(LOBJS))
OBJS = $(OUT_OBJS)

#################################

$(TARGET) :$(OBJS)
	$(CC) $(CCFLAGS) -o $(OUT_DIR)/$(TARGET) $(OBJS) $(EXTERN_OBJS)  $(LIBS) $(INCLUDES)

$(OUT_DIR)/OBJS/%.o:%.cpp
	$(CC) -c $(CCFLAGS) $< -o $@  $(INCLUDES)


clean:
	rm $(OUT_DIR)/OBJS -rf
	rm $(OUT_DIR)/$(TARGET) -rf

echo:
	echo    $(EXPR_FILE)
	echo    $(SRCS_cpp)
	#echo   "OBJS:"
	echo    $(OBJS)
	echo    $(SUB_OUT_DIR)

