#include "state.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "snake_utils.h"

/* Helper function definitions */
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch);
static bool is_tail(char c);
static bool is_head(char c);
static bool is_snake(char c);
static char body_to_tail(char c);
static char head_to_body(char c);
static unsigned int get_next_row(unsigned int cur_row, char c);
static unsigned int get_next_col(unsigned int cur_col, char c);
static void find_head(game_state_t* state, unsigned int snum);
static char next_square(game_state_t* state, unsigned int snum);
static void update_tail(game_state_t* state, unsigned int snum);
static void update_head(game_state_t* state, unsigned int snum);

/* Task 1 */
game_state_t* create_default_state() {
  // TODO: Implement this function.
  game_state_t* new_game = (game_state_t*)malloc(sizeof(game_state_t));
  
  new_game->num_snakes = 1;
  new_game->snakes = (snake_t*)malloc(new_game->num_snakes*sizeof(snake_t));

  new_game->num_rows = 18;

  new_game->snakes[0].tail_row = 2;
  new_game->snakes[0].tail_col = 2;
  new_game->snakes[0].head_row = 2;
  new_game->snakes[0].head_col = 4;
  new_game->snakes[0].live = true;
  
  //allocate valyes for board first
  new_game->board = (char**)malloc(sizeof(char*) * new_game->num_rows);

  for(unsigned int i=0;i<new_game->num_rows;i++)
    new_game->board[i] = (char*)malloc(sizeof(char) * 21);
  
  char* board_values[18] = {
    "####################\n",
    "#                  #\n",
    "# d>D    *         #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "#                  #\n",
    "####################\n"
  };

  //copy the values to the actual board
  for(unsigned int i = 0; i < new_game->num_rows; i++){
    strcpy(new_game->board[i], board_values[i]);    
  }

  return new_game;
}
/* Task 2 */
void free_state(game_state_t* state) {
  // TODO: Implement this function.
  if(state == NULL)
    return;
  if(state->board == NULL)
    return;
  if(state->snakes == NULL)
    return;
    
  for(unsigned int i = 0; i < state->num_rows; i++){
    free(state->board[i]);
  }
  free(state->board);
  free(state->snakes);
  free(state);
}

/* Task 3 */
void print_board(game_state_t* state, FILE* fp) {
  // TODO: Implement this function.

  for(unsigned int i=0;i<state->num_rows;i++){
    for(unsigned int j = 0;state->board[i][j]!='\n';j++){
      fprintf(fp,"%c",state->board[i][j]);
    }
    fprintf(fp,"%c",'\n');
  }
  return;
}

/*
  Saves the current state into filename. Does not modify the state object.
  (already implemented for you).
*/
void save_board(game_state_t* state, char* filename) {
  FILE* f = fopen(filename, "w");
  print_board(state, f);
  fclose(f);
}

/* Task 4.1 */

/*
  Helper function to get a character from the board
  (already implemented for you).
*/
char get_board_at(game_state_t* state, unsigned int row, unsigned int col) {
  return state->board[row][col];
}

/*
  Helper function to set a character on the board
  (already implemented for you).
*/
static void set_board_at(game_state_t* state, unsigned int row, unsigned int col, char ch) {
  state->board[row][col] = ch;
}

/*
  Returns true if c is part of the snake's tail.
  The snake consists of these characters: "wasd"
  Returns false otherwise.
*/
static bool is_tail(char c) {
  // TODO: Implement this function.
  switch(c){
    case 'w':
    case 'a':
    case 's':
    case 'd':
      return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake's head.
  The snake consists of these characters: "WASDx"
  Returns false otherwise.
*/
static bool is_head(char c) {
  // TODO: Implement this function.
  switch(c){
    case 'W':
    case 'A':
    case 'S':
    case 'D':
      return true;
  }
  return false;
}

/*
  Returns true if c is part of the snake.
  The snake consists of these characters: "wasd^<v>WASDx"
*/
static bool is_snake(char c) {
  // TODO: Implement this function.
  switch(c){
    case 'w':
    case 'a':
    case 's':
    case 'd':
    case 'W':
    case 'A':
    case 'S':
    case 'D':
    case '^':
    case '<':
    case 'v':
    case '>':
      return true;
  }
  return false;
}

/*
  Converts a character in the snake's body ("^<v>")
  to the matching character representing the snake's
  tail ("wasd").
*/
static char body_to_tail(char c) {
  // TODO: Implement this function.
  switch(c){
    case '^':
      return 'w';
    case '<':
      return 'a';
    case '>':
      return 'd';
    case 'v':
      return 's';
  }
  return '?';
}

/*
  Converts a character in the snake's head ("WASD")
  to the matching character representing the snake's
  body ("^<v>").
*/
static char head_to_body(char c) {
  // TODO: Implement this function.
  switch(c){
    case 'W':
      return '^';
    case 'A':
      return '<';
    case 'D':
      return '>';
    case 'S':
      return 'v';
  }
  return '?';
}

/*
  Returns cur_row + 1 if c is 'v' or 's' or 'S'.
  Returns cur_row - 1 if c is '^' or 'w' or 'W'.
  Returns cur_row otherwise.
*/
static unsigned int get_next_row(unsigned int cur_row, char c) {
  // TODO: Implement this function.
  if((c=='v')||(c=='s')||(c=='S'))
    return cur_row+1;
  else if((c=='^')||(c=='w')||(c=='W'))
    return cur_row-1;
  return cur_row;
}

/*
  Returns cur_col + 1 if c is '>' or 'd' or 'D'.
  Returns cur_col - 1 if c is '<' or 'a' or 'A'.
  Returns cur_col otherwise.
*/
static unsigned int get_next_col(unsigned int cur_col, char c) {
  // TODO: Implement this function.
  if((c=='>')||(c=='d')||(c=='D'))
    return cur_col+1;
  else if((c=='<')||(c=='a')||(c=='A'))
    return cur_col-1;
  return cur_col;
}

/*
  Task 4.2

  Helper function for update_state. Return the character in the cell the snake is moving into.

  This function should not modify anything.
*/
static char next_square(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  // * Selected snake is snum
  // * need to move it by 1 unit
  // * return the character in the cell the snake is moving into
  // * this function should not modify anything

  unsigned int snake_head_row = state->snakes[snum].head_row;
  unsigned int snake_head_col = state->snakes[snum].head_col;

  char snake_head = get_board_at(state,snake_head_row,snake_head_col);

  if(is_head(snake_head)){
    unsigned int next_row = get_next_row(snake_head_row,snake_head);
    unsigned int next_col = get_next_col(snake_head_col,snake_head);

    return get_board_at(state,next_row,next_col);
  }
  return '?';
}

/*
  Task 4.3

  Helper function for update_state. Update the head...

  ...on the board: add a character where the snake is moving

  ...in the snake struct: update the row and col of the head

  Note that this function ignores food, walls, and snake bodies when moving the head.
*/
static void update_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  // !Note that this function ignores food, walls, and snake bodies when moving the head.
  unsigned int snake_head_row = state->snakes[snum].head_row;
  unsigned int snake_head_col = state->snakes[snum].head_col;

  char snake_head = get_board_at(state,snake_head_row,snake_head_col);

  if(is_head(snake_head)){
    unsigned int next_row = get_next_row(snake_head_row,snake_head);
    unsigned int next_col = get_next_col(snake_head_col,snake_head);

    state->snakes[snum].head_row = next_row;
    state->snakes[snum].head_col = next_col;

    set_board_at(state,next_row,next_col,snake_head);
    set_board_at(state,snake_head_row,snake_head_col,head_to_body(snake_head));

    return;
  }
  return;
}

/*
  Task 4.4

  Helper function for update_state. Update the tail...

  ...on the board: blank out the current tail, and change the new
  tail from a body character (^<v>) into a tail character (wasd)

  ...in the snake struct: update the row and col of the tail
*/
static void update_tail(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  // !Note that this function ignores food, walls, and snake bodies when moving the head.
  unsigned int snake_tail_row = state->snakes[snum].tail_row;
  unsigned int snake_tail_col = state->snakes[snum].tail_col;

  char snake_tail = get_board_at(state,snake_tail_row,snake_tail_col);

  if(is_tail(snake_tail)){
    unsigned int next_row = get_next_row(snake_tail_row,snake_tail);
    unsigned int next_col = get_next_col(snake_tail_col,snake_tail);

    state->snakes[snum].tail_row = next_row;
    state->snakes[snum].tail_col = next_col;

    char next_square = get_board_at(state,next_row,next_col);
    char next_snake_tail = body_to_tail(next_square);

    set_board_at(state,next_row,next_col,next_snake_tail);
    set_board_at(state,snake_tail_row,snake_tail_col,' ');

    return;
  }
  return;

  return;
}

/* Task 4.5 */
void update_state(game_state_t* state, int (*add_food)(game_state_t* state)) {
  // TODO: Implement this function.
  // * update the state of the game
  // * add food to the board
  // * update the state of the snakes
  for(unsigned int i=0;i<state->num_snakes;i++){
    char next_square_char = next_square(state,i);

    if((is_snake(next_square_char))||(next_square_char=='#')){
      state->snakes[i].live = false;
      state->board[state->snakes[i].head_row][state->snakes[i].head_col] = 'x'; 
    }
    else if(next_square_char=='*'){
      update_head(state,i);
      add_food(state);
    }
    else{
      update_head(state,i);
      update_tail(state,i);
    }
  }

  return;
}

/* Task 5 */
game_state_t* load_board(FILE* fp) {
  // TODO: Implement this function.
  game_state_t* new_game = (game_state_t*)malloc(sizeof(game_state_t));
  new_game->num_snakes = 0;
  new_game->snakes = NULL;

  new_game->board = NULL;
  new_game->num_rows=1;
  new_game->board = (char**)realloc(new_game->board,sizeof(char*)*new_game->num_rows);
  new_game->board[0] = NULL;
  unsigned int col_index=0;

  char c;
  while((c=fgetc(fp))!=EOF){
    unsigned int row_index = new_game->num_rows-1;
    new_game->board[row_index] = (char*)realloc(new_game->board[row_index],sizeof(char)*(col_index+2));  // Allocate space for the new char and the null terminator
    new_game->board[row_index][col_index] = c;
    new_game->board[row_index][col_index+1] = '\0';  // Null-terminate the string
    col_index++;
    if(c=='\n'){
      new_game->num_rows++;
      new_game->board = (char**)realloc(new_game->board,sizeof(char*)*new_game->num_rows);
      new_game->board[new_game->num_rows-1] = NULL;
      col_index=0;
    }
  }

  new_game->num_rows--;

  return new_game;
}

/*
  Task 6.1

  Helper function for initialize_snakes.
  Given a snake struct with the tail row and col filled in,
  trace through the board to find the head row and col, and
  fill in the head row and col in the struct.
*/
static void find_head(game_state_t* state, unsigned int snum) {
  // TODO: Implement this function.
  // * Given a snake struct with the tail row and col filled in,
  // * trace through the board to find the head row and col.

  unsigned int snake_curr_row = state->snakes[snum].tail_row;
  unsigned int snake_curr_col = state->snakes[snum].tail_col;

  char curr_snake_bodypart = get_board_at(state,snake_curr_row,snake_curr_col);

  while(!is_head(curr_snake_bodypart)){
    snake_curr_col = get_next_col(snake_curr_col,curr_snake_bodypart);
    snake_curr_row = get_next_row(snake_curr_row,curr_snake_bodypart);
    curr_snake_bodypart = get_board_at(state,snake_curr_row,snake_curr_col);
  }

  state->snakes[snum].head_row = snake_curr_row;
  state->snakes[snum].head_col = snake_curr_col;

  return;
}

/* Task 6.2 */
game_state_t* initialize_snakes(game_state_t* state) {
  // TODO: Implement this function.
  unsigned int snake_count=0;

  for(unsigned int i=0;i<state->num_rows;i++){
    for(unsigned int j=0;state->board[i][j]!='\n';j++){
      if(is_tail(state->board[i][j])){
        state->snakes = (snake_t*)realloc(state->snakes,sizeof(snake_t)*(snake_count+1));
        state->snakes[snake_count].tail_row = i;
        state->snakes[snake_count].tail_col = j;
        state->snakes[snake_count].live = true;
        find_head(state,snake_count);
        snake_count++;
      }
    }
  }

  state->num_snakes = snake_count;

  return state;
}
