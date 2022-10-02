#include <stdio.h>

#define MAX_INPUT_LEN 250
#define INPUT_FILENAME "input.txt"
#define OUTPUT_FILENAME "output.txt"

int read_tree(FILE *fp, char *buffer);
void parse_and_write_tree(FILE *fp, char *buffer, int size);
void parse(FILE *fp, char *buffer, int size, int level, int *cursor);
void write_node(FILE *fp, char character, int level);

int main()
{

    char tree_str[MAX_INPUT_LEN + 1];
    FILE *fp_input = fopen(INPUT_FILENAME, "r");
    int len = read_tree(fp_input, tree_str);
    fclose(fp_input);

    FILE *fp_output = fopen(OUTPUT_FILENAME, "w+");
    parse_and_write_tree(fp_output, tree_str, len);
    fclose(fp_output);

    return 0;
}

int read_tree(FILE *fp, char *buffer)
{
    int len = 0;
    if (fp != NULL)
    {
        len = fread(buffer, sizeof(char), MAX_INPUT_LEN + 1, fp);
        buffer[len] = '\0';
    }

    return len;
}

void parse_and_write_tree(FILE *fp, char *buffer, int size)
{
    int cursor = 0;
    parse(fp, buffer, size, 0, &cursor);
}

void parse(FILE *fp, char *buffer, int size, int level, int *cursor)
{
    if ((*cursor) == size)
        return;

    int index = *cursor;
    *cursor = index + 1;

    switch (buffer[index])
    {
    case ')':
        return;
    case '(':
        parse(fp, buffer, size, level + 1, cursor);
        break;
    case ',':
        fprintf(fp, "\n");
    case ' ':
        break;
    default:
        write_node(fp, buffer[index], level);
        break;
    }

    return parse(fp, buffer, size, level, cursor);
}

void write_node(FILE *fp, char character, int level)
{
    for (int i = 0; i < level; i++)
        fprintf(fp, "-");

    fprintf(fp, "%c", character);
}