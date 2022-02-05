#include <iostream>
#include <string>
#include "LFSR.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) {
	LFSR l("00111", 2);
	BOOST_REQUIRE(l.step() == 1);
	BOOST_REQUIRE(l.step() == 1);
	BOOST_REQUIRE(l.step() == 0);
	BOOST_REQUIRE(l.step() == 0);
	BOOST_REQUIRE(l.step() == 0);
	BOOST_REQUIRE(l.step() == 1);
	BOOST_REQUIRE(l.step() == 1);
	BOOST_REQUIRE(l.step() == 0);
  	LFSR l2("00111", 2);
  	BOOST_REQUIRE(l2.generate(8) == 198);
}

/*Register bits include 7 bits and tap position at 4.
  The function simulates one step and check if the vacated bit printed out 
  is equal with the computation. It keeps provoking step() 11 times
  Calling method generate() to test whether the integer result is equal with 
  the computation after simulating 5 steps*/
BOOST_AUTO_TEST_CASE(sevenBitsTapAtFour) {
	LFSR lfsr("0110011",4);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==1);
	LFSR lfsr2("0110011",4);
	BOOST_REQUIRE(lfsr2.generate(5)==31);
}

/*Register bits include 13 bits and tap position at 11.
  The function simulates one step and check if the vacated bit printed out 
  is equal with the computation. It keeps provoking step() 9 times
  Calling method generate() to test whether the integer result is equal with 
  the computation after simulating 7 steps*/
BOOST_AUTO_TEST_CASE(thirteenBitsTapAtEleven) {
	LFSR lfsr("00101000110010",11);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==1);
	LFSR lfsr2("00101000110010",11);
	BOOST_REQUIRE(lfsr2.generate(7)==69);
}

/*Register bits include 4 bits and tap position at 2.
  The function simulates one step and check if the vacated bit printed out 
  is equal with the computation. It keeps provoking step() 5 times
  Calling method generate() to test whether the integer result is equal with 
  the computation after simulating 3 steps*/
BOOST_AUTO_TEST_CASE(fourBitsTapAtTwo) {
	LFSR lfsr("0111",2);
	BOOST_REQUIRE(lfsr.step()==1);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==0);
	BOOST_REQUIRE(lfsr.step()==1);
	LFSR lfsr2("0111",2);
	BOOST_REQUIRE(lfsr2.generate(3)==4);
}


