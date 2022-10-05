#include "loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

generic_u8_t size_by_row_len(generic_u8_t len);
bit is_valid_row(generic_u8_t len);



typedef struct __bytecode_data__
{
    generic_u16_t code;
    generic_u32_t *ext1;
    generic_u8_t  size;

} bytecode;

generic_32_t data_size = -1;



bytecode** read_bytecode(char *filename)
{
    FILE    *fp;
    char    *line = NULL;
    size_t  len   = 0;
    ssize_t read;
    bytecode** data = NULL;

    fp = fopen(filename, "r");

    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n') data_size++;
    }
    fclose(fp);

    data = calloc((generic_u32_t) data_size, sizeof (*data));

    fp = fopen(filename, "r");

    generic_u32_t pos = 0, validator = 0;
    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (is_valid_row(read) && validator > 0)
        {
            bytecode *curr = malloc(sizeof (*curr));

            char  op[5];
            char  immediate[9];
            char* end = NULL;
            long  value;

            for (generic_u8_t i = 0; i < 9; i++)
                immediate[i] = 0;

            strncpy(op, line, 4);

            value = strtol(op, &end, 16);

            curr->code = (generic_u16_t) value;

            if (read > 5)
            {
                end = NULL;
                strncpy(immediate, line+4, read-5);
                value = strtol(immediate, &end, 16);

                curr->ext1  = malloc(sizeof (*curr->ext1));
                *curr->ext1 = (generic_u32_t) value;

                generic_u8_t size = size_by_row_len(read);

                if (size == 0xFF)
                    { PANIC("[PANIC] Error incomes while loading an invalid bytecode\n"); }

                curr->size = size;
            }
            else
            {
                curr->ext1 = NULL;
            }

            data[pos++] = curr;
        }

        if (validator == 0 && is_valid_row(read)) validator++;
    }
    fclose(fp);

    if (line) free(line);

    return data;
}



void destroy_loader_data(bytecode **data)
{
    if (data)
    {
        for (generic_u32_t i = 0; i < ((generic_u32_t) data_size); i++)
        {
            if (data[i])
            {
                if (data[i]->ext1) free(data[i]->ext1);
                free(data[i]);
            }
        }

        free(data);
    }
}



generic_u32_t load_executable(char *filename)
{
    bytecode **b = read_bytecode(filename);

    if (b)
    {
        generic_u32_t span = 0;
        for (generic_u32_t iter = 0; iter < ((generic_u32_t) data_size); iter++)
        {
            if (b[iter])
            {
                bytecode *curr = b[iter];

                write_word(get_pc() + span, curr->code);
                span += WORD_SPAN;

                if (curr->ext1)
                {
                    switch (curr->size)
                    {
                        case BYTE:
                            write_byte(get_pc() + span, *curr->ext1);
                            span += BYTE_SPAN;
                            break;
                        case WORD:
                            write_word(get_pc() + span, *curr->ext1);
                            span += WORD_SPAN;
                            break;
                        case LONG:
                            write_long(get_pc() + span, *curr->ext1);
                            span += LONG_SPAN;
                            break;
                    }
                }
            }
        }

        destroy_loader_data(b);

        return ((generic_u32_t)(get_pc() + span));
    }

    return (LOAD_ERROR);
}



generic_u8_t size_by_row_len(generic_u8_t len)
{
    switch (len) {
        case 7:
            return BYTE;
        case 9:
            return WORD;
        case 13:
            return LONG;
        default:
            return 0xFF;
    }
}


bit is_valid_row(generic_u8_t len)
{
    switch (len) {
        case 5:
        case 7:
        case 9:
        case 13:
            return 1;
        default:
            return 0;
    }
}
