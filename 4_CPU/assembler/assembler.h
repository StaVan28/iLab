
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

//-----------------------------------------------------------------
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#include "txtlib.h"
#include "labels.h"
#include "settings.h"
#include "ram.h"

//-----------------------------------------------------------------

enum pass_of_asm {
    FRST_PASS = 1,
    SCND_PASS = 2,
};

//-----------------------------------------------------------------

#define IF_STRCMP_ORD(cmd, cmd_str)                             \
        if (!strcmp(file_info->text_[indx].line_, cmd_str))     \
        {                                                       \
            READING_DATA(cmd, char)                             \
        }                                                       \

//-

#define IF_STRCMP_JMP(cmd, cmd_str)                                                                     \
        if (!strcmp(file_info->text_[indx].line_, cmd_str)) {                                           \
                                                                                                        \
            if (pass_of_asm == FRST_PASS) {                                                             \
                POINTER_ON_(*buffer_data, tmp_IP, char) = cmd;                                          \
            }                                                                                           \
                                                                                                        \
            tmp_IP += sizeof(char);                                                                     \
            indx++;                                                                                     \
                                                                                                        \
            if (pass_of_asm == FRST_PASS) {                                                             \
                table_labels->check_label(file_info->text_[indx].line_, POISON_POSITION, FROM_JMP_CMD); \
            }                                                                                           \
            if (pass_of_asm == SCND_PASS) {                                                             \
                int position = table_labels->find_label(file_info->text_[indx].line_);                  \
                POINTER_ON_(*buffer_data, tmp_IP, int) = position;                                      \
            }                                                                                           \
                                                                                                        \
            tmp_IP += sizeof(int);                                                                      \
                                                                                                        \
        }                                                                                               \

//-

#define IF_STRCMP_MRK(label)                                                                        \
        if (strchr(file_info->text_[indx].line_, label)) {                                          \
                                                                                                    \
            if (pass_of_asm == FRST_PASS) {                                                         \
                table_labels->check_label(file_info->text_[indx].line_, tmp_IP, FROM_MARK_LABEL);   \
                POINTER_ON_(*buffer_data, tmp_IP, char) = NOP_CMD;                                  \
            }                                                                                       \
                                                                                                    \
            tmp_IP += sizeof(char);                                                                 \
        }                                                                                           \

//-

#define IF_STRCMP_REG(reg, cmd_str)                             \
        if (!strcmp(file_info->text_[indx].line_, cmd_str)) {   \
            READING_DATA(reg, char)                             \
        }                                                       \

//-

#define READING_DATA(cmd, format)                                 \
            if (pass_of_asm == FRST_PASS) {                       \
                POINTER_ON_(*buffer_data, tmp_IP, format) = cmd;  \
            }                                                     \
                                                                  \
            tmp_IP += sizeof(format);                             \

//-

#define PARSING_PUSH do                                                                \
                     {                                                                 \
                         double value = strtod(file_info->text_[indx].line_, nullptr); \
                                                                                       \
                         if ((tmp_command & CONST_CMD_MASK) && errno == 0)             \
                         {                                                             \
                             if (ram_flag)                                             \
                             {                                                         \
                                 READING_DATA(value, double)                           \
                             }                                                         \
                             else                                                      \
                             {                                                         \
                                 READING_DATA((int)value, int)                         \
                             }                                                         \
                                                                                       \
                             tmp_command |= CONST_CMD_MASK;                            \
                             const_flag   = false;                                     \
                         }                                                             \
                         else if (reg_flag && errno != 0)                              \
                         {                                                             \
                             IF_STRCMP_REG     (EAX_REG, "eax")                        \
                                                                                       \
                             else IF_STRCMP_REG(EBX_REG, "ebx")                        \
                                                                                       \
                             else IF_STRCMP_REG(ECX_REG, "ecx")                        \
                                                                                       \
                             else IF_STRCMP_REG(EDX_REG, "edx")                        \
                                                                                       \
                             errno = 0;                                                \
                                                                                       \
                             tmp_command |= REG_CMD_MASK;                              \
                             reg_flag     = false;                                     \
                         }                                                             \
                     } while (false)                                                   \

//-

//-----------------------------------------------------------------

void assembling_file(const char* file_path = "./txt/", const char* source = "source");

void pass_of_assembler(int pass_of_asm, Text* file_info, Labels* table_labels, char** buffer_data);

void scnd_pass_of_assembler(Text* file_info, Labels* table_labels, char** buffer_data);

void add_CPU_info_in_buf(char* buffer_data, int num_of_bytes);

void parsing_push(Text* file_info, int indx, char tmp_command, bool const_flag, bool reg_flag, bool ram_flag);

//-----------------------------------------------------------------

#endif // ASSEMBLER_H_INCLUDED