/*
 * Copyright (C) 2022 Clownacy
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"





int check_file_format(const char* name, const char* extension)
{
    const char* ldot = strrchr(name, '.');
    if (ldot != NULL)
    {
        size_t length = strlen(extension);
        return strncmp(ldot + 1, extension, length) == 0;
    }

    return 0;
}



int assemble(int argc, char **argv)
{
	int exit_code = EXIT_SUCCESS;

	cc_bool print_usage;
	const char *input_file_path;
	const char *output_file_path;
	const char *listing_file_path;
	const char *symbol_file_path;
	cc_bool case_insensitive;
	cc_bool debug;
	cc_bool equ_set_descope_local_labels;
	int i;

	print_usage = cc_false;
	input_file_path = NULL;
	output_file_path = NULL;
	listing_file_path = NULL;
	symbol_file_path = NULL;
	case_insensitive = cc_false;
	debug = cc_false;
	equ_set_descope_local_labels = cc_false;

    for (i = 2; i < argc; ++i)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'h':
					print_usage = cc_true;
					continue;

				case 'i':
					if (i < argc && argv[i + 1][0] != '-')
					{
						++i;
						input_file_path = argv[i];
					}

					continue;

				case 'o':
					if (i < argc && argv[i + 1][0] != '-')
					{
						++i;
						output_file_path = argv[i];
					}

					continue;

				case 'l':
					if (i < argc && argv[i + 1][0] != '-')
					{
						++i;
						listing_file_path = argv[i];
					}

					continue;

				case 's':
					if (i < argc && argv[i + 1][0] != '-')
					{
						++i;
						symbol_file_path = argv[i];
					}

					continue;

				case 'c':
					case_insensitive = cc_true;
					continue;

				case 'b':
					debug = cc_true;
					continue;

				case 'd':
					equ_set_descope_local_labels = cc_true;
					continue;
			}
		}

		fprintf(stderr, "Error: Unrecognised option '%s'.\n", argv[i]);
		exit_code = EXIT_FAILURE;
	}

    if (argc < 2 || print_usage)
        {
            fputs(
                "**Assembler** an assembler for the Motorola 68000.\n"
                "\n"
                "**Options**\n"
                " -i [path] - Input file.\n"
                " -o [path] - Output file.\n"
                " -l [path] - Listing file. Optional.\n"
                " -s [path] - asm68k-style symbol file. Optional.\n"
                " -c        - Enable case-insensitive mode.\n"
                " -b        - Enable Bison's debug output.\n"
                " -d        - Allow EQU/SET to descope local labels.\n"
                , stdout);
        }
    else
        {
            if (output_file_path == NULL)
            {
                ASSSEMBLER_ERROR("Output file path must be specified with '-o'.");
            }
            else
            {
                if (input_file_path == NULL)
                {
                    ASSSEMBLER_ERROR("Could not open input file.");
                }
                else
                {

                    if (!check_file_format(input_file_path, "X68"))
                    {
                        FASSSEMBLER_ERROR("Invalid file format in input file %s.", input_file_path);
                    }
                    else if (!check_file_format(output_file_path, "B68"))
                    {
                        FASSSEMBLER_ERROR("Invalid file format in output file %s.", output_file_path);
                    }
                    else
                    {
                        char *tmp = "tmp";
                        char *output_file_tmp_path;
                        if((output_file_tmp_path = malloc(strlen(output_file_path) + strlen(tmp) + 1)) != NULL){
                            output_file_tmp_path[0] = '\0';
                            strcat(output_file_tmp_path, output_file_path);
                            strcat(output_file_tmp_path, tmp);
                        }

                        FILE *input_file;
                        FILE *output_file;
                        FILE *output_file_tmp;

                        input_file = fopen(input_file_path, "r");
                        output_file_tmp = fopen(output_file_tmp_path, "wb");

                        if (output_file_tmp == NULL)
                        {
                            ASSSEMBLER_ERROR("Could not open output file.");
                        }
                        else
                        {
                            FILE *listing_file;
                            FILE *symbol_file;

                            if (listing_file_path == NULL)
                            {
                                listing_file = NULL;
                            }
                            else
                            {
                                listing_file = fopen(listing_file_path, "w");

                                if (listing_file == NULL)
                                    ASSSEMBLER_ERROR("Could not open listing file.");
                            }

                            if (symbol_file_path == NULL)
                            {
                                symbol_file = NULL;
                            }
                            else
                            {
                                symbol_file = fopen(symbol_file_path, "wb");

                                if (symbol_file == NULL)
                                    ASSSEMBLER_ERROR("Could not open symbol file.");
                            }

                            if (!ClownAssembler_Assemble(input_file, output_file_tmp, listing_file, symbol_file, input_file_path, debug, case_insensitive, equ_set_descope_local_labels))
                            {
                                ASSSEMBLER_ERROR("Could not assemble.");
                            }
                            else
                            {
                                fclose(output_file_tmp);

                                output_file_tmp = fopen(output_file_tmp_path, "rb");
                                output_file     = fopen(output_file_path, "wb");

                                if (output_file == NULL || output_file_tmp == NULL)
                                {
                                    ASSSEMBLER_ERROR("Could not open output file.");
                                }
                                else
                                {
                                    char ch;
                                    while(fread(&ch, 1, 1, output_file_tmp) != 0)
                                          fputc(ch, output_file);

                                    fclose(output_file);
                                }
                            }

                            if (listing_file != NULL)
                                fclose(listing_file);

                            fclose(output_file_tmp);

                            remove(output_file_tmp_path);
                        }

                        if (output_file_tmp_path)
                            free(output_file_tmp_path);

                        fclose(input_file);
                    }
                }
            }
        }

    return !exit_code;
}
