/* Definitions the scanner shares with the parser
    Michael L. Scott, 2008-2017.
*/
/* Name: Hoang Do
   Student ID: 01521888
   Partner: David Huynh */

typedef enum {t_read, t_write, t_id, t_literal, t_gets,
                t_add, t_sub, t_mul, t_div, t_lparen, t_rparen, t_eof,
                t_if, t_fi, t_do, t_od, t_check, t_eq, t_noteq, t_less, t_greater,
                t_lesseq, t_greatereq} token;

extern char token_image[100];

extern token scan();
