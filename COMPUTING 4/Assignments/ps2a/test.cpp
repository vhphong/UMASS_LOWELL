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

// three extra bit strings to be tested

BOOST_AUTO_TEST_CASE(sevenBitsTapAtTwo){
	LFSR l3("1000110", 2);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 0);
	
	LFSR l3_("1000110", 2);
	BOOST_REQUIRE(l3_.generate(6) == 17);
}



BOOST_AUTO_TEST_CASE(tenBitsTapAtFour){
	LFSR l3("1100010110", 4);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	
	LFSR l3_("1100010110", 4);
	BOOST_REQUIRE(l3_.generate(5) == 14);
}



BOOST_AUTO_TEST_CASE(fifteenBitsTapAtEleven){
	LFSR l3("101110100011010", 11);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 0);
	BOOST_REQUIRE(l3.step() == 1);
	BOOST_REQUIRE(l3.step() == 1);
	
	LFSR l3_("101110100011010", 11);
	BOOST_REQUIRE(l3_.generate(7) == 53);
}
