# ----------------------------
# Makefile Options
# ----------------------------

NAME        ?= Binary
COMPRESSED  ?= YES
ICON        ?= images/icon.png
DESCRIPTION ?= "Binary Converter and Addition"
ARCHIVED    ?= NO

CFLAGS      ?= -Wall -Wextra -Oz --std=c99
CXXFLAGS    ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
