NAME 	= minirt

SRC_DIR	= srcs/
SRC_BONUS_DIR = srcs_bonus/


SRCS	=	srcs/intersections/cylinder_intersections.c srcs/intersections/intersections.c \
			srcs/intersections/obj_intersections.c srcs/intersections/pyramid_intersections.c \
 			srcs/mlx_stuff/events.c srcs/mlx_stuff/mlx_init.c \
			srcs/parsing/ambient_light.c srcs/parsing/camera.c srcs/parsing/cylinder.c \
 			srcs/parsing/light.c srcs/parsing/parse_file_utils.c srcs/parsing/parse_file.c \
			srcs/parsing/parse_utils2.c srcs/parsing/plane.c srcs/parsing/pyramid.c srcs/parsing/set_objects.c srcs/parsing/sphere.c \
			srcs/rendering/hits.c srcs/rendering/rendering_utils.c \
			srcs/rendering/rendering_utils2.c srcs/rendering/rendering.c \
			srcs/shading/normal.c srcs/shading/pyramid_normal.c srcs/shading/shading.c \
			srcs/tuples_stuff/tuples_operations.c srcs/tuples_stuff/tuples_operations2.c \
			srcs/various_utils/color_utils.c srcs/various_utils/free.c srcs/various_utils/matrix_utils.c srcs/various_utils/safe.c \
			srcs/various_utils/utils_debug.c srcs/various_utils/utils.c \
			srcs/main.c

OBJ_DIR	= objects/
OBJS 	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)/%.o)
INC		= -I ./includes

LIBFT		= libft/libft.a

ARCH	:= $(shell uname -m)
UNAME_S	:= $(shell uname -s)

ifeq ($(UNAME_S), Linux)
	MLX_DIR 	= ./minilibx-l
	MLX_PATH	= minilibx-l/libmlx_linux.a
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	CFLAGS	=  -finline-functions -ftree-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing \
	 		-fomit-frame-pointer -flto  -O3  -Wall -Wextra -Werror
else 
	MLX_DIR		= ./minilibx
	MLX_PATH	= minilibx/libmlx.a
	MLX_FLAGS	= -framework OPenGL -framework AppKit
	MLX_OBJ		= -Imlx -c
	CFLAGS = -O3

endif 

MLX_LIB		= -L$(MLX_DIR) -lmlx 

RED   		= \033[1;38;5;196m
PINK  		= \033[1;38;5;213m
NC			= \033[0m
FACE		= 😏

all: ${NAME}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} $(INC) -c $< -o $@

$(OBJ_DIR)/$(SRC_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@cc ${CFLAGS} $(INC) -c $< -o $@

${NAME}: ${OBJS}
	@make -C libft
	@make -C $(MLX_DIR)
	@cc ${CFLAGS} ${OBJS} $(INC) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o ${NAME}
	@printf "\r${RED}Compiling $(FACE) : [${PINK}%-50s${PINK}${PINK}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJ_DIR) -type f -name '*.o' | wc -l) \* \
	 50 / $(words $(SRCS))))) $$(find $(OBJ_DIR) -type f -name '*.o' | wc -l) $(words $(SRCS))

bonus: ${OBJS_BONUS}
	@make -C libft
	@make -C $(MLX_DIR)
	@cc ${CFLAGS} ${OBJS_BONUS} $(INC) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o ${NAME}_bonus

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -C ./libft
	@make clean -C ./$(MLX_DIR)

fclean: clean
	@rm -rf ${NAME}
	@rm -rf ${NAME}_bonus
	@make fclean -C ./libft 

re: fclean all

.PHONY: all clean fclean re
