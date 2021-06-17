/*********************************************************************
 * copyright (C) 2017-2021 Xilinx, Inc.
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

#include <pcie_abstract.h>

#define GET_FILE_LENGTH           0x0
#define GET_ENC_PARAMS            0x1
#define SET_READ_OFFSET           0x2
#define SET_WRITE_OFFSET          0x3
#define SET_READ_TRANSFER_DONE    0x5
#define CLR_READ_TRANSFER_DONE    0x6
#define SET_WRITE_TRANSFER_DONE   0x7
#define CLR_WRITE_TRANSFER_DONE   0x8
#define GET_RESOLUTION            0x9
#define GET_MODE                  0xa
#define GET_FPS                   0xb
#define GET_FORMAT                0xc

int pcie_open()
{
    int fpga_fd;

    fpga_fd = open(DEVICE_NAME, O_RDWR);
    if (fpga_fd < 0) {
        printf("unable to open device %d.\n", fpga_fd);
        return -EINVAL;
    }

    return fpga_fd;
}

unsigned long int pcie_get_file_length(int fpga_fd)
{
    unsigned long int file_length = 0;
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_FILE_LENGTH, &file_length);
        if (ret < 0)
            printf("unable to run ioctl for file_length.\n");
        else
            printf("file_length is %lu bytes.\n", file_length);
    }
    return file_length;
}

int pcie_get_input_resolution(int fpga_fd, struct resolution *input_res)
{
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_RESOLUTION, input_res);
        if (ret < 0)
            printf("unable to run ioctl for input resolution.\n");
        else
            printf("Input resolution is %u X %u\n", input_res->width, input_res->height);

    }
    return ret;
}

int pcie_get_use_case_type(int fpga_fd)
{
    unsigned int use_case_type;
    char use_case_name[3][10] = {{"Encode"}, {"Decode"}, {"Transcode"}};
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_MODE, &use_case_type);
        if (ret < 0)
            printf("unable to run ioctl for input use case type.\n");
        else
            printf("Running %s use case\n", use_case_name[use_case_type]);
    }
    return use_case_type;
}

int pcie_get_fps(int fpga_fd)
{
    int ret = 0;
    unsigned int fps;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_FPS, &fps);
        if (ret < 0)
            printf("unable to run ioctl for FPS.\n");
        else
            printf("Input FPS is %u\n", fps);
    }
    return fps;
}

int pcie_get_format(int fpga_fd)
{
    int ret = 0;
    unsigned int fmt;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_FORMAT, &fmt);
        if (ret < 0)
            printf("unable to run ioctl for format.\n");
    }
    return fmt;
}

int pcie_get_enc_params(int fpga_fd, struct enc_params *params )
{
    int ret = 0 ;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, GET_ENC_PARAMS, params);
        if (ret < 0)
            printf("unable to run ioctl for encoder params.\n");
    }
    return ret;
}

int pcie_set_read_transfer_done(int fpga_fd, int value)
{
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, SET_READ_TRANSFER_DONE, &value);
        if (ret < 0) {
            printf("unable to run ioctl for read transfer done.\n");
            return ret;
        }
        else {
            printf("successfully set read transfer done\n");
            return ret;
        }
    }
    return ret;
}

int pcie_set_write_transfer_done(int fpga_fd, int value)
{
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, SET_WRITE_TRANSFER_DONE, &value);
        if (ret < 0) {
            printf("unable to run ioctl for write transfer done.\n");
            return ret;
        }
        else {
            printf("successfully set write transfer done\n");
            return ret;
        }
    }
    return ret;
}

int pcie_clr_read_transfer_done(int fpga_fd, int value)
{
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, CLR_READ_TRANSFER_DONE, &value);
        if (ret < 0) {
            printf("unable to run ioctl for read transfer done.\n");
            return ret;
        }
        else {
            printf("successfully set read transfer done\n");
            return ret;
        }
    }
    return ret;
}

int pcie_clr_write_transfer_done(int fpga_fd, int value)
{
    int ret = 0;

    if (fpga_fd > 0) {
        ret = ioctl(fpga_fd, CLR_WRITE_TRANSFER_DONE, &value);
        if (ret < 0) {
            printf("unable to run ioctl for write transfer done.\n");
            return ret;
        }
        else {
            printf("successfully set write transfer done\n");
            return ret;
        }
    }
    return ret;
}


int pcie_read(int fpga_fd, int size, unsigned long int offset, char *buff)
{
    long int rc = 0;
    unsigned long int lseek_cnt = 0;

    if (fpga_fd >= 0) {
        if (offset) {
            lseek_cnt = lseek(fpga_fd, offset, SEEK_SET);
            if (lseek_cnt != offset) {
                printf("seek off 0x%lx != 0x%lx.\n", lseek_cnt, offset);
                return -EIO;
            }
        }
        rc = read(fpga_fd, buff, size);
        if (rc < 0) {
            printf("read size = 0x%lx 0x%lx 0x%x 0x%x.\n", rc, rc, size, size);
                perror("read file");
            return -EIO;
        }

    }

    return rc;
}

int pcie_write(int fpga_fd, int size, int offset, char *buff)
{
    long int rc = 0;


    if (fpga_fd >= 0) {
        rc = write(fpga_fd, buff, size);
        if (rc < 0) {
            printf("write size = 0x%lx 0x%lx 0x%x 0x%x.\n",rc, rc, size, size);
            perror("write file");
            return -EIO;
        }
    }
    return rc;
}

void pcie_close(int fpga_fd)
{
    close(fpga_fd);
}
