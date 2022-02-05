/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/

// Authors: Muhammad Muneeb and Hylton Carboo

typedef enum {t_check, t_read, t_write, t_id, t_literal, t_gets, t_if,
    t_fi, t_do, t_od, t_equal, t_notequal, t_smaller,
    t_greater, t_smallerequal,t_greaterequal, t_add, t_sub, t_mul,
    t_div, t_lparen, t_rparen, t_eof, t_eps} token;

extern char token_image[100];
extern token scan();
extern std::string getImage();
