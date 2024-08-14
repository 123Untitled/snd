
# -- O P E R A T I N G  S Y S T E M -------------------------------------------

# get OS name, assume we are on unix system
override OS := $(shell uname -s)

# check for macOSX
ifeq ($(OS),Darwin)

    override PLATFORM  := macosx
    override THREAD    := $(shell sysctl -n hw.ncpu)
    override FRAMEWORK := -framework CoreMIDI -framework CoreAudio -framework CoreFoundation

# check for Linux
else ifeq ($(OS),Linux)

    override PLATFORM  := linux
    override THREAD    := $(shell nproc)
    override FRAMEWORK := -lasound

else

    $(error $(shell echo "Unsupported OS: \033[1;32m$(OS)\033[0m"))

endif



# -- S E T T I N G S ----------------------------------------------------------

# set default target
.DEFAULT_GOAL := all

# use one shell for all commands
.ONESHELL:

# delete intermediate files on error
.DELETE_ON_ERROR:

# silent mode
.SILENT:

# set shell program
override SHELL := $(shell which zsh)

# set shell flags
.SHELLFLAGS := -d -f -c -e -o pipefail -u

# set make flags
override MAKEFLAGS += --warn-undefined-variables --no-builtin-rules \
					  --jobs=$(THREAD) --output-sync=target \
					  --no-print-directory



# -- T A R G E T S ------------------------------------------------------------

# project name
override PROJECT = msh

# main executable
override EXEC = exec_$(PROJECT)

# compile commands for clangd
override COMPILE_DB = compile_commands.json


# -- D I R E C T O R I E S ----------------------------------------------------

# source directory
override SRC_DIR := sources

# include directory
override INC_DIR := includes


# -- S O U R C E S ------------------------------------------------------------

# get all source files
override SRCS := $(shell find $(SRC_DIR) -type f -name "*.cpp")

# pattern substitution for object files
override OBJS := $(SRCS:%.cpp=%.o)

# pattern substitution for dependency files
override DEPS := $(OBJS:%.o=%.d)


# -- C O M P I L E R  S E T T I N G S -----------------------------------------

# make directory if not exists
override MKDIR := mkdir -p

# remove recursively force
override RM := rm -rvf

# compiler
#CXX := $(shell which g++)
#CXX := /opt/homebrew/Cellar/llvm/16.0.4/bin/clang++
override CXX := clang++

# compiler standard
override STD := -std=c++2a

# compiler optimization
override OPT := -O0 -g3

# debug flags
override DEBUG := -g3

# compiler flags
override FLAGS := -Wall -Wextra -Werror -Wpedantic \
			-Wno-unused -Wno-unused-variable -Wno-unused-parameter \
			-Winline -Weffc++ -ferror-limit=10

# dependency flags
override DFLAGS = -MT $@ -MMD -MP -MF $*.d

# include flags
override INCLUDES := -I$(INC_DIR)

# cxx flags
override CXXFLAGS := $(STD) $(OPT) $(DEBUG) $(FLAGS) $(INCLUDES)

# linker flags
override LDFLAGS := $(FRAMEWORK)



# -- P H O N Y  T A R G E T S -------------------------------------------------

.PHONY: ascii all clean fclean re .WAIT

# not parallel
.NOTPARALLEL: $(COMPILE_DB) re fclean clean ascii


# -- M A I N  T A R G E T S ---------------------------------------------------

all: ascii $(EXEC) .WAIT $(COMPILE_DB)
	echo 'export PATH=$$PATH:$(shell pwd)'


# -- E X E C U T A B L E  T A R G E T -------------------------------------------

$(EXEC): $(OBJS)
	echo 'linking' $@
	$(CXX) $^ $(LDFLAGS) -o $@


# -- C O M P I L A T I O N ------------------------------------------------------

-include $(DEPS)
%.o : %.cpp Makefile
	echo 'compiling' $(notdir $<)
	$(CXX) $(CXXFLAGS) $(DFLAGS) -c $< -o $@


# -- C O M P I L E  C O M M A N D S ---------------------------------------------

$(COMPILE_DB): $(SRCS) Makefile
	echo 'generating' $@
	$(call GENERATE_CDB)


# -- C L E A N I N G ------------------------------------------------------------

clean:
	$(RM) $(OBJS) $(DEPS) $(COMPILE_DB) .cache


fclean: clean
	$(RM) $(EXEC)


# -- R E C O M P I L E --------------------------------------------------------

re: fclean all


# -- A S C I I  A R T ---------------------------------------------------------

ascii:
	echo \
		"\x1b[32m" \
		"   ▁▁▁▁▁▁▁▁  ▁▁▁▁▁▁▁▁  ▁▁▁▁ ▁▁▁  ▁▁▁▁▁▁▁▁	\n" \
		"  ╱        ╲╱        ╲╱    ╱   ╲╱        ╲	\n" \
		" ╱         ╱         ╱         ╱         ╱	\n" \
		"╱         ╱         ╱        ▁╱       ▁▁╱	\n" \
		"╲▁▁╱▁▁╱▁▁╱╲▁▁▁╱▁▁▁▁╱╲▁▁▁▁╱▁▁▁╱╲▁▁▁▁▁▁▁▁╱	\n" \
		'\t\t\tGNU Make''\x1b[0m'': '$(MAKE_VERSION)"\n"


# generate compile_commands.json
define GENERATE_CDB
local CONTENT='[\n'
for FILE in $(SRCS); do
CONTENT+='\t{\n\t\t"directory": "'$$(pwd)'",\n\t\t"file": "'$$FILE'",\n\t\t"output": "'$${FILE%.cpp}.o'",\n\t\t"arguments": [\n\t\t\t"$(CXX)",\n'
	for FLAG in $(CXXFLAGS); do
		CONTENT+='\t\t\t"'$$FLAG'",\n'
	done
	CONTENT+='\t\t\t"-c",\n\t\t\t"'$$FILE'",\n\t\t\t"-o",\n\t\t\t"'$${FILE%.cpp}'.o"\n\t\t]\n\t},\n'
done
echo $${CONTENT%',\n'}'\n]' > $@
endef
