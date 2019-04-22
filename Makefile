NAME = ps

# src_dir = ./sources/
# obj_dir = ./objects/
# lib_dir = ./library/
# inc_dir = ./includes/ $(lib_dir)glfw/include/

SRC_PATH := ./sources/
SRC_SUB_PATH :=	OCL_manager/ \
				OGL_manager/
OBJ_PATH := ./objects/
LIB_PATH := ./library/
INC_PATH := ./includes/ \
			$(LIB_PATH)glfw/include/ \
			# ./includes/glad/ \
			# $(LIB_PATH)glad/include/ \
			# $(LIB_PATH)glfw/deps/ \
			# $(LIB_PATH)glad/include/KHR

GCC_FLGS = -pedantic -g3 -g
# -Werror -Wextra -Wall
CPP_FLGS += -Wno-c++11-extensions
GCC_LIBS = -lglfw3 -lGLEW -framework AppKit -framework OpenGL -framework OpenCL -framework GLUT -framework IOKit -framework CoreVideo

SYSCONF_LINK = g++ -std=c++11
LDFLAGS      = -O3 
LIB_NAME 	= glfw/src/ glew/
INC 		:= $(addprefix -I,$(INC_PATH) $(addprefix ./includes/, $(SRC_SUB_PATH)))
LIB 		:= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

sources_sub_path = $(addprefix $(SRC_PATH), $(SRC_SUB_PATH))
object_sub_path = $(addprefix $(OBJ_PATH), $(SRC_SUB_PATH))

object_sub_cpp := $(patsubst %.cpp, %.o, $(wildcard $(addsuffix *.cpp, $(sources_sub_path))))
objectcpp := $(patsubst %.cpp, %.o, $(wildcard $(addprefix $(SRC_PATH), *.cpp)))
objectc := $(patsubst %.c, %.o, $(wildcard $(addprefix $(SRC_PATH), *.c)))

objectcpp := $(patsubst $(SRC_PATH)%.o, $(OBJ_PATH)%.o, $(objectcpp) $(object_sub_cpp))
objectc := $(patsubst $(SRC_PATH)%.o, $(OBJ_PATH)%.o, $(objectc))

objectcpp := $(objectcpp:.cpp=.o)
objectc := $(objectc:.c=.o)

object := $(objectcpp)
# $(objectc)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(object_sub_path) $(object)
		$(SYSCONF_LINK) $(GCC_FLGS) $(LDFLAGS) -o $@ $(INC) $(object) $(GCC_LIBS) $(LIB)

$(object_sub_path) : $(OBJ_PATH)
		mkdir -p $@

$(OBJ_PATH) :
		mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
		$(SYSCONF_LINK) $(GCC_FLGS) $(CPP_FLGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		gcc $(GCC_FLGS) -c $< -o $@ $(INC)

clean:
		rm -f $(object)
		rm -rf $(object_sub_path)
		rm -rf $(OBJ_PATH)

fclean: clean
		rm -f $(NAME)

re: fclean all
