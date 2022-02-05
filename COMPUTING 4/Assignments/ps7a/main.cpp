//by: Phong Hong Vo (pvo)

#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
	std::string regex_begin = "([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+): .*\\(log.c.166\\) server started.*";
	std::string regex_end = "([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+):([0-9]+).([0-9]+):INFO: oejs.AbstractConnector:Started SelectChannelConnector@0.0.0.0:9080.*";
	boost::regex begin_boot(regex_begin);
	boost::regex end_boot(regex_end);
	std::ifstream logfile(argv[1]);
	std::string newfile = argv[1];
	std::ofstream outputfile(newfile + ".rpt", std::ofstream::out);
	std::string pos;
	boost::posix_time::ptime beginTime;
	using boost::posix_time::time_duration;
	bool isCompleted = true;
	int _code = 1;
	if (argc != 2) {
		throw std::runtime_error("Please input the log file");
	} else {
		if (logfile.is_open()) {
		} 
		else {
			throw std::runtime_error("Cannot open file");
		}
		while (logfile.eof() == false) {
			std::getline(logfile, pos);
			boost::smatch startT, endT;
			if (regex_match(pos, startT, begin_boot)) {
				boost::gregorian::date dateT(stoi(startT[1]), stoi(startT[2]), stoi(startT[3]));
				boost::posix_time::ptime _startT(dateT, time_duration(stoi(startT[4]), stoi(startT[5]), stoi(startT[6]))); // NOLINT
				beginTime = _startT;
				if (!isCompleted) {
					outputfile << "**** Incomplete boot ****\n" << std::endl;
				}
				outputfile 	<< "=== Device boot ===\n"
							<< _code << "(" << argv[1] << "): "
							<< startT[1] << "-" << startT[2] << "-"
							<< startT[3] << " " << startT[4] << ":"
							<< startT[5] << ":" << startT[6]
							<< " Boot Start" << std::endl;
				isCompleted = false;
			}
			else if (regex_match(pos, endT, end_boot)) {
				boost::gregorian::date dateT(stoi(endT[1]), stoi(endT[2]), stoi(endT[3]));
				boost::posix_time::ptime finishTime(dateT, time_duration(stoi(endT[4]), stoi(endT[5]), stoi(endT[6]))); // NOLINT
				outputfile 	<< _code << "(" << argv[1] << "): "
							<< endT[1] << "-" << endT[2] << "-"
							<< endT[3] << " " << endT[4] << ":"
							<< endT[5] << ":" << endT[6]
							<< " Boot Completed" << std::endl;
							time_duration time_d = finishTime - beginTime;
							outputfile << "    "
							<< " Boot Time: " << time_d.total_milliseconds() << "ms\n" << std::endl;
				isCompleted = true;
			}
			_code++;
		}
		outputfile.close();
		logfile.close();
	}
	return 0;
}
