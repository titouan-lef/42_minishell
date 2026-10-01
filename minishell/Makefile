# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tle-floc <tle-floc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/15 14:44:24 by lguerbig          #+#    #+#              #
#    Updated: 2025/02/13 20:15:53 by tle-floc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#===================== BASE =====================#

CC				:=	cc
CFLAGS			+=	-Wall -Wextra -Werror -MP -MMD
BUILD_DIR		:=	.build/
HEADERS			:=	./include/
NAME			:=	minishell

#==================== SOURCE ====================#

LIBFT_DIR		=	./libft/
LIBFT_HEADER	=	./libft/include
LIBFT			=	$(LIBFT_DIR)libft.a
SRC_DIR			=	./src/
SRC				=	minishell.c																	\
					execution/execution.c														\
					execution/exit_utils.c														\
					execution/exec_suite/logic_ope_exec_bonus.c									\
					execution/exec_suite/cmd_exec/cmd_exec.c									\
					execution/exec_suite/cmd_exec/builtin/builtin.c								\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/echo.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/env.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/exit.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/export/export.c			\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/export/print_export.c	\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/pwd.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/unset.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/cd/cd.c					\
					execution/exec_suite/cmd_exec/builtin/builtin_suite/cd/goto_dir.c			\
					execution/exec_suite/cmd_exec/external_cmd/external_cmd_exec.c				\
					execution/exec_suite/cmd_exec/external_cmd/update_cmd_path.c				\
					execution/exec_suite/cmd_exec/redir/redir_suite.c							\
					execution/exec_suite/cmd_exec/redir/redir.c									\
					execution/exec_suite/pipe_exec/pipe_exec.c									\
					execution/exec_suite/pipe_exec/cmd_order/first_cmd.c						\
					execution/exec_suite/pipe_exec/cmd_order/last_cmd.c							\
					execution/exec_suite/pipe_exec/cmd_order/midle_cmd.c						\
					execution/exec_suite/pipe_exec/stack/stack_primitive.c						\
					expansion/expand_utils.c													\
					expansion/expansions.c														\
					expansion/expansion_suite/exit_status.c										\
					expansion/expansion_suite/quote_removal.c									\
					expansion/expansion_suite/tilde_bonus.c										\
					expansion/expansion_suite/environment_variable/get_env_var.c				\
					expansion/expansion_suite/environment_variable/replace_env_var.c			\
					expansion/expansion_suite/environment_variable/variable_expansion.c			\
					expansion/expansion_suite/wildcard/get_files_bonus.c						\
					expansion/expansion_suite/wildcard/pathname_expansion_bonus.c				\
					expansion/expansion_suite/wildcard/replace_wildcard_bonus.c					\
					here_doc/here_doc.c															\
					here_doc/here_doc_utils.c													\
					input/display.c																\
					input/read_lines.c															\
					lexer/lexer.c																\
					lexer/get_token/get_operator_bonus.c										\
					lexer/get_token/get_redir.c													\
					lexer/get_token/get_word.c													\
					parser/parser.c																\
					parser/build_ast/cmd_state.c												\
					parser/build_ast/control_ope_state_bonus.c									\
					parser/build_ast/state_utils.c												\
					parser/build_ast/state.c													\
					utils/compare_utils_bonus.c													\
					utils/path_utils.c															\
					utils/tab_utils.c															\
					utils/token_utils.c															\
					utils/queue/queue_primitive.c												\
					utils/queue/queue_utils.c													\
					utils/signal/signal_handler.c												\
					utils/signal/signals.c														\
					utils/tree/tree_primitive.c													\
					utils/tree/tree_push.c

#==================== OBJECT ====================#

OBJ				:=	$(SRC:%.c=$(BUILD_DIR)%.o)
OBJ_DIR			:=	$(sort $(shell dirname $(OBJ)))

#================== DEPENDENCY ==================#

DEP				:=	$(SRC:%.c=$(BUILD_DIR)%.d)

#==================== COLOR =====================#

INIT			:=	\033[0m
BLACK			:=	\033[30m
RED				:=	\033[31m
GREEN			:=	\033[32m
YELLOW			:=	\033[33m
BLUE			:=	\033[34m
MAGENTA			:=	\033[35m
CYAN			:=	\033[36m

#===================== RULE =====================#

DISPLAY_TRACKER	:=	.display_done

ifndef VERBOSE
.SILENT:
endif

all: $(NAME)

bonus: $(NAME)

$(DISPLAY_TRACKER):
				printf "\n"
				printf " /░░      /░░ /░░           /░░           /░░                 /░░ /░░\n"
				printf "| ░░░    /░░░|__/          |__/          | ░░                | ░░| ░░\n"
				printf "| ░░░░  /░░░░ /░░ /░░░░░░░  /░░  /░░░░░░░| ░░░░░░░   /░░░░░░ | ░░| ░░\n"
				printf "| ░░ ░░/░░ ░░| ░░| ░░__  ░░| ░░ /░░_____/| ░░__  ░░ /░░__  ░░| ░░| ░░\n"
				printf "| ░░  ░░░| ░░| ░░| ░░  \ ░░| ░░|  ░░░░░░ | ░░  \ ░░| ░░░░░░░░| ░░| ░░\n"
				printf "| ░░\  ░ | ░░| ░░| ░░  | ░░| ░░ \____  ░░| ░░  | ░░| ░░_____/| ░░| ░░\n"
				printf "| ░░ \/  | ░░| ░░| ░░  | ░░| ░░ /░░░░░░░/| ░░  | ░░|  ░░░░░░░| ░░| ░░\n"
				printf "|__/     |__/|__/|__/  |__/|__/|_______/ |__/  |__/ \_______/|__/|__/\n"
				printf "\n"
				touch $(DISPLAY_TRACKER)
				sleep 0.5

$(LIBFT):
				printf "$(BLUE)Making libft🔨$(INIT)\n"
				$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(NAME): $(DISPLAY_TRACKER) $(LIBFT) $(OBJ)
				$(CC) -lreadline -I$(HEADERS) -I$(LIBFT_HEADER) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
				printf "$(GREEN)$(NAME) ready ✅️✅️$(INIT)\n"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
				printf "$(GREEN)Compiling : $(MAGENTA)$<$(INIT)\n"
				$(CC) -I$(HEADERS) -I$(LIBFT_HEADER) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
				mkdir -p $@

clean:
				if [ -d $(LIBFT_DIR)$(BUILD_DIR) ];\
				then printf "$(BLUE)Cleanning libft✨🧹$(INIT)\n";\
				$(MAKE) $@ -C $(LIBFT_DIR) --no-print-directory;\
				fi;
				if [ -d $(BUILD_DIR) ];\
				then printf "$(BLUE)Cleanning $(NAME)✨🧹$(INIT)\n";\
				printf "$(RED)Removing directory : $(BLUE)$(BUILD_DIR)$(INIT)\n";\
				rm -rf $(BUILD_DIR);\
				fi;
				rm -f $(DISPLAY_TRACKER)

fclean: clean
				if [ -f $(LIBFT) ];\
				then printf "$(BLUE)Cleanning libft✨🧹$(INIT)\n";\
				$(MAKE) $@ -C $(LIBFT_DIR) --no-print-directory;\
				fi;
				if [ -f $(NAME) ];\
				then printf "$(BLUE)Cleanning $(NAME)✨🧹$(INIT)\n";\
				printf "$(RED)Removing : $(MAGENTA)$(NAME)$(INIT)\n";\
				rm -f $(NAME);\
				fi;
				rm -f $(DISPLAY_TRACKER)

re:
				rm -f $(DISPLAY_TRACKER)
				$(MAKE) $(DISPLAY_TRACKER) --no-print-directory
				$(MAKE)	fclean --no-print-directory
				touch $(DISPLAY_TRACKER)
				$(MAKE) all --no-print-directory

tester: $(LIBFT) $(filter-out minishell.c ,$(OBJ))
				cp $(LIBFT) $(NAME).a
				ar -rs $(NAME).a $(filter-out minishell.c ,$(OBJ))
				printf "$(GREEN)$(NAME).a ready for tester ✅️✅️$(INIT)\n";\

.PHONY := all clean fclean re bonus tester

-include $(DEP)
