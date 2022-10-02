#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define WORD_LIST_FILE_NAME "wordlist.txt"
#define MAX_WORD_LIST_COUNT 512 // Maximum number of words a wordlist can contain

#define BOARD_SIZE 15
#define CROSSED_CELL 'X'
#define EMPTY_CELL '*'
#define WORD_COUNT 3           // Count of random words that will be placed to board
#define WORD_LENGTH BOARD_SIZE // Assumed a word length can not be greater than board size

// user actions
#define MAX_INPUT_LENGTH 128
#define EXIT_COMMAND 0
#define WRONG_GUESS -1
#define CORRECT_GUESS 1
#define MAX_TRY 3
#define SCORE_POINT 2 // The acquired point when guess is correct

// Directions
#define DIR_LEFT_TO_RIGHT 0
#define DIR_RIGHT_TO_LEFT 1
#define DIR_UP_TO_DOWN 2
#define DIR_DOWN_TO_UP 3
#define DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT 4
#define DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT 5
#define DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT 6
#define DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT 7

typedef char Board[BOARD_SIZE][BOARD_SIZE];
typedef char Word[WORD_LENGTH + 1];
typedef struct BoardItem
{
  Word word;
  int row_begin;
  int col_begin;
  int direction;
  bool crossed;
} BoardItem;

void empty_the_board(Board board);
void print_board(Board board);
int determine_row_end(int row_begin, int direction, int len);
int determine_col_end(int col_begin, int direction, int len);
bool is_indexes_out_of_range(int row_begin, int row_end, int col_begin, int col_end);
bool is_place_not_empty(Board board, Word word, int direction, int row_begin, int col_begin);
void fill_words(Board board, BoardItem items[WORD_COUNT]);
void insert_word_to_board(Board board, BoardItem item);
void fill_random_characters(Board board);
bool is_word_selected_already(Word word, BoardItem items[WORD_COUNT]);
void read_random_words_from_file(BoardItem items[WORD_COUNT]);
void read_user_input(char *input);
int find_word(Word word, Board board, BoardItem items[WORD_COUNT], int row_begin, int col_begin);
void cross_the_word(Board board, BoardItem items[], int index);
void fill_words(Board board, BoardItem items[WORD_COUNT]);
char rand_char();

int main()
{
  srand(time(NULL));

  Board board;
  BoardItem items[WORD_COUNT];

  empty_the_board(board);
  read_random_words_from_file(items);
  fill_words(board, items);
  fill_random_characters(board);

  int points = 0;
  int word_founded = 0;
  int tries_left = MAX_TRY;
  char input[MAX_INPUT_LENGTH + 1];
  int last_action = 0;

  while (tries_left > 0 && word_founded < WORD_COUNT)
  {
    printf("\n");
    print_board(board);
    if (last_action == WRONG_GUESS)
    {
      printf("Wrong choice! You have only %d lefts.\n", tries_left);
    }
    else if (last_action == CORRECT_GUESS)
    {
      printf("Founded! You got %d points. Your total points: %d\n", SCORE_POINT, points);
    }
    printf("Enter coordinates and word:");

    read_user_input(input);
    if (strcmp(input, ":q") == 0)
    {
      last_action = EXIT_COMMAND;
      break;
    }

    // parse input
    Word word;
    int row_begin, col_begin;
    sscanf(input, "%d %d %s", &row_begin, &col_begin, word);

    int index = find_word(word, board, items, row_begin, col_begin);
    if (index != -1)
    {
      word_founded++;
      points += SCORE_POINT;
      cross_the_word(board, items, index);
      last_action = CORRECT_GUESS;
    }
    else
    {
      tries_left--;
      last_action = WRONG_GUESS;
    }
  }

  printf("\n");
  print_board(board);
  if (last_action == CORRECT_GUESS)
    printf("\nCongrats! You won the game. Total points: %d\n", points);
  else if (last_action == WRONG_GUESS)
    printf("\nGame over! You got %d points. Maybe next time...\n", points);
  else
    printf("\nGame terminated. You got %d points.\n", points);

  return 0;
}

void empty_the_board(Board board)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      board[i][j] = EMPTY_CELL;
    }
  }
}

void print_board(Board board)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      printf("%c ", board[i][j]);
    }
    printf("\n");
  }
}

void fill_random_characters(Board board)
{
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] == EMPTY_CELL)
        board[i][j] = rand_char();
    }
  }
}

char rand_char()
{
  return 'a' + rand() % 26;
}

int determine_row_end(int row_begin, int direction, int len)
{
  switch (direction)
  {
  case DIR_LEFT_TO_RIGHT:
  case DIR_RIGHT_TO_LEFT:
    return row_begin;

  case DIR_UP_TO_DOWN:
  case DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT:
  case DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT:
    return row_begin + len;

  case DIR_DOWN_TO_UP:
  case DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT:
  case DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT:
    return row_begin - len;
  }
}

int determine_col_end(int col_begin, int direction, int len)
{
  switch (direction)
  {
  case DIR_UP_TO_DOWN:
  case DIR_DOWN_TO_UP:
    return col_begin;

  case DIR_LEFT_TO_RIGHT:
  case DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT:
  case DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT:
    return col_begin + len;

  case DIR_RIGHT_TO_LEFT:
  case DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT:
  case DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT:
    return col_begin - len;
  }
}

bool is_indexes_out_of_range(int row_begin, int row_end, int col_begin, int col_end)
{
  return row_begin < 0 || row_end < 0 || col_begin < 0 || col_end < 0 || row_begin > BOARD_SIZE || row_end > BOARD_SIZE || col_begin > BOARD_SIZE || col_end > BOARD_SIZE;
}

bool is_place_not_empty(Board board, Word word, int direction, int row_begin, int col_begin)
{
  int len = strlen(word);

  switch (direction)
  {
  case DIR_LEFT_TO_RIGHT:
    for (int i = 0; i < len; i++)
      if (board[row_begin][col_begin + i] != EMPTY_CELL)
        return true;
    break;

  case DIR_RIGHT_TO_LEFT:
    for (int i = 0; i < len; i++)
      if (board[row_begin][col_begin - i] != EMPTY_CELL)
        return true;
    break;

  case DIR_UP_TO_DOWN:
    for (int i = 0; i < len; i++)
      if (board[row_begin + i][col_begin] != EMPTY_CELL)
        return true;
    break;

  case DIR_DOWN_TO_UP:
    for (int i = 0; i < len; i++)
      if (board[row_begin - i][col_begin] != EMPTY_CELL)
        return true;
    break;

  case DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT:
    for (int i = 0; i < len; i++)
      if (board[row_begin + i][col_begin + i] != EMPTY_CELL)
        return true;
    break;

  case DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT:
    for (int i = 0; i < len; i++)
      if (board[row_begin + i][col_begin - i] != EMPTY_CELL)
        return true;
    break;

  case DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT:
    for (int i = 0; i < len; i++)
      if (board[row_begin - i][col_begin + i] != EMPTY_CELL)
        return true;
    break;

  case DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT:
    for (int i = 0; i < len; i++)
      if (board[row_begin - i][col_begin - i] != EMPTY_CELL)
        return true;
    break;
  }

  return false;
}

void insert_word_to_board(Board board, BoardItem item)
{
  int len = strlen(item.word);

  switch (item.direction)
  {
  case DIR_LEFT_TO_RIGHT:
    for (int i = 0; i < len; i++)
      board[item.row_begin][item.col_begin + i] = item.word[i];
    break;

  case DIR_RIGHT_TO_LEFT:
    for (int i = 0; i < len; i++)
      board[item.row_begin][item.col_begin - i] = item.word[i];
    break;

  case DIR_UP_TO_DOWN:
    for (int i = 0; i < len; i++)
      board[item.row_begin + i][item.col_begin] = item.word[i];
    break;

  case DIR_DOWN_TO_UP:
    for (int i = 0; i < len; i++)
      board[item.row_begin - i][item.col_begin] = item.word[i];
    break;

  case DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT:
    for (int i = 0; i < len; i++)
      board[item.row_begin + i][item.col_begin + i] = item.word[i];
    break;

  case DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT:
    for (int i = 0; i < len; i++)
      board[item.row_begin + i][item.col_begin - i] = item.word[i];
    break;

  case DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT:
    for (int i = 0; i < len; i++)
      board[item.row_begin - i][item.col_begin + i] = item.word[i];
    break;

  case DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT:
    for (int i = 0; i < len; i++)
      board[item.row_begin - i][item.col_begin - i] = item.word[i];
    break;
  }
}

void read_random_words_from_file(BoardItem items[WORD_COUNT])
{
  FILE *fp = fopen(WORD_LIST_FILE_NAME, "r");
  Word buffer[MAX_WORD_LIST_COUNT];
  int count = 0;

  // read line by line to word array
  while (fgets(buffer[count], WORD_LENGTH, fp))
  {
    buffer[count][strcspn(buffer[count], "\r\n")] = 0;
    if (strlen(buffer[count]) == 0)
      continue;
    count++;
  }

  int selected = 0;
  while (selected < WORD_COUNT)
  {
    int index = rand() % count;
    if (is_word_selected_already(buffer[index], items))
      continue;

    strcpy(items[selected].word, buffer[index]);
    selected++;
  }
}

bool is_word_selected_already(Word word, BoardItem items[WORD_COUNT])
{
  for (int i = 0; i < WORD_COUNT; i++)
    if (strcmp(items[i].word, word) == 0)
      return true;

  return false;
}

void fill_words(Board board, BoardItem items[WORD_COUNT])
{
  for (int i = 0; i < WORD_COUNT; i++)
  {
    // BoardItem *item = &items[i];
    int len = strlen(items[i].word);

    while (true)
    {
      int direction = rand() % 8;
      int row_begin = rand() % BOARD_SIZE;
      int col_begin = rand() % BOARD_SIZE;
      int row_end = determine_row_end(row_begin, direction, len);
      int col_end = determine_col_end(col_begin, direction, len);

      if (is_indexes_out_of_range(row_begin, row_end, col_begin, col_end))
        continue;

      if (is_place_not_empty(board, items[i].word, direction, row_begin, col_begin))
        continue;

      items[i].direction = direction;
      items[i].row_begin = row_begin;
      items[i].col_begin = col_begin;
      items[i].crossed = false;
      insert_word_to_board(board, items[i]);
      break;
    }
  }
}

void cross_the_word(Board board, BoardItem items[], int index)
{
  int len = strlen(items[index].word);
  items[index].crossed = true;

  switch (items[index].direction)
  {
  case DIR_LEFT_TO_RIGHT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin][items[index].col_begin + i] = CROSSED_CELL;
    break;

  case DIR_RIGHT_TO_LEFT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin][items[index].col_begin - i] = CROSSED_CELL;
    break;

  case DIR_UP_TO_DOWN:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin + i][items[index].col_begin] = CROSSED_CELL;
    break;

  case DIR_DOWN_TO_UP:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin - i][items[index].col_begin] = CROSSED_CELL;
    break;

  case DIR_DIAGONAL_TOP_LEFT_TO_BOTTOM_RIGHT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin + i][items[index].col_begin + i] = CROSSED_CELL;
    break;

  case DIR_DIAGONAL_TOP_RIGHT_TO_BOTTOM_LEFT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin + i][items[index].col_begin - i] = CROSSED_CELL;
    break;

  case DIR_DIAGONAL_BOTTOM_LEFT_TO_TOP_RIGHT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin - i][items[index].col_begin + i] = CROSSED_CELL;
    break;

  case DIR_DIAGONAL_BOTTOM_RIGHT_TO_TOP_LEFT:
    for (int i = 0; i < len; i++)
      board[items[index].row_begin - i][items[index].col_begin - i] = CROSSED_CELL;
    break;
  }
}

int find_word(Word word, Board board, BoardItem items[WORD_COUNT], int row_begin, int col_begin)
{
  for (int i = 0; i < WORD_COUNT; i++)
  {
    if ((strcmp(items[i].word, word) == 0) &&
        items[i].col_begin == col_begin &&
        items[i].row_begin == row_begin &&
        !items[i].crossed)
      return i;
  }

  return -1;
}

void read_user_input(char *input)
{
  fgets(input, MAX_INPUT_LENGTH, stdin);
  input[strlen(input) - 1] = 0; // remove the newline at the end
}