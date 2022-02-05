//
//  test.cpp
//  a2_syntax_error_recovery
//
//  Created by CS Admin on 2/18/18.
//  Copyright © 2018 Viet Tran Quoc Hoang. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Scanner.h"
#include "Parser.h"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>
using namespace std;
static token input_token;

BOOST_AUTO_TEST_CASE(T_ALPHA) {
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_read);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_write);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_if);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_fi);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_do);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_od);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_check);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_id);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_eof);
}

BOOST_AUTO_TEST_CASE(T_DIGIT) {
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_literal);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_literal);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_literal);
}

BOOST_AUTO_TEST_CASE(T_OPERATOR) {
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_eq_eq);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_not_eq);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_less_eq);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_great_eq);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_gets);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_less);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_great);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_add);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_sub);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_div);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_mul);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_lparen);
    input_token = scan();
    BOOST_CHECK_EQUAL(input_token, t_rparen);
    
}

