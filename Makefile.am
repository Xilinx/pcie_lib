
lib_LTLIBRARIES = libvcu_pcie.la

AM_DEFAULT_SOURCE_EXT = .c

vcu_pcie_lib_INC_DIR = ./include
vcu_pcie_lib_SRC_DIR = ./src

#NOTE:In some build system, single $ character is not interpreted correctly and removed, so we have added $$ to overcome such issue.
PCI_CFLAGS_PKG_CONFIG = $$(pkg-config --cflags glib-2.0)

nodist_libvcu_pcie_la_SOURCES = \
		$(vcu_pcie_lib_INC_DIR)/pcie_abstract.h

libvcu_pcie_la_includedir = /usr/include

libvcu_pcie_la_include_HEADERS = \
		$(vcu_pcie_lib_INC_DIR)/pcie_abstract.h

libvcu_pcie_la_SOURCES = \
		$(vcu_pcie_lib_SRC_DIR)/pcie_abstract.c

libvcu_pcie_la_CFLAGS = $(PCI_CFLAGS_PKG_CONFIG) -I$(vcu_pcie_lib_INC_DIR)
