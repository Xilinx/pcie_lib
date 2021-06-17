/*********************************************************************
 * Copyright (C) 2017-2021 Xilinx, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 ********************************************************************/

#ifndef INCLUDE_PCIE_ABSTRAINCLUDE_PCIE_SRC_C_CT_H_
#define INCLUDE_PCIE_ABSTRACT_H_

#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#define DEVICE_NAME  "/dev/pciep0"
#define SIZE_DEFAULT 8388608

typedef struct enc_params {
    bool   enable_l2Cache;
    bool   low_bandwidth;
    bool   filler_data;
    bool   max_picture_size;
    unsigned int      bitrate;
    unsigned int      gop_len;
    unsigned int      b_frame;
    unsigned int      slice;
    unsigned int      qp_mode;
    unsigned int      rc_mode;
    unsigned int      enc_type;
    unsigned int      gop_mode;
    unsigned int      profile;
    unsigned int      min_qp;
    unsigned int      max_qp;
    unsigned int      cpb_size;
    unsigned int      initial_delay;
    unsigned int      periodicity_idr;
} enc_params;


typedef struct resolution {
    unsigned int      width;
    unsigned int      height;
} resolution;

int pcie_open();

unsigned long int pcie_get_file_length(int fpga_fd);

int pcie_get_enc_params(int fpga_fd, struct enc_params *params);

int pcie_read(int fpga_fd, int size, unsigned long int offset, char *buff);

int pcie_write(int fpga_fd, int size, int offset, char *buff);

int pcie_set_read_transfer_done(int fpga_fd, int value);

int pcie_set_write_transfer_done(int fpga_fd, int value);

int pcie_get_input_resolution(int fpga_fd, struct resolution *input_res);

int pcie_get_use_case_type(int fpga_fd);

int pcie_get_fps(int fpga_fd);

int pcie_get_format(int fpga_fd);

#endif //INCLUDE_PCIE_ABSTRACT_H_
