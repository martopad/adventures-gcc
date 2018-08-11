//To Compile g++-8 -std=c++17 -I ../BOOSTEXPERIMENTS/boost_1_67_0/ practice.cpp -pthread -lboost_unit_test_framework -o a.out -lboost_thread -lpthread -lboost_chrono -lboost_system -lboost_date_time -lstdc++fs -L ../BOOSTEXPERIMENTS/boost_1_67_0/stage/lib/
#include <iostream>
#include <string>
#include <regex>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <map>
#include <filesystem>
#include <boost/date_time.hpp>
//#include <boost/filesystem.hpp>



std::string return_current_time_and_date()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

std::string getCurrentDate()
{
  boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
  boost::posix_time::time_duration durObj = timeLocal.time_of_day();
  // std::string CurrentDate="";

	// //std::cout << "Time Object = " << durObj << std::endl;
  // CurrentDate = to_simple_string(durObj);//timeLocal.date().month();// + timeLocal.date().day() + timeLocal.date().year();
  std::stringstream ss;
  //return CurrentDate;

	ss << timeLocal.date().month()<<"-";
	ss << timeLocal.date().day()<<"-";
  ss << timeLocal.date().year();
	//ss << timeLocal.time_of_day().hours();
	//ss << timeLocal.time_of_day().minutes();
	//ss << timeLocal.time_of_day().seconds();
  return ss.str();
}

std::string returnFirstMatch (std::string strToSearch, std::regex pattern)
{
    //std::cout << "WEW" << std::endl;
    auto words_begin =
        std::sregex_iterator(strToSearch.begin(), strToSearch.end(), pattern);
    auto words_end = std::sregex_iterator();

    std::cout << "Found "
              << std::distance(words_begin, words_end)
              << " words\n";

    // for (std::sregex_iterator i = words_begin; i != words_end; ++i)
    // {
        std::smatch match = *words_begin;
        std::string match_str = match.str();

        //if (match_str.size() > N)
        //{
            //std::cout << "  " << match_str << '\n';
            return match_str;
        //}
    //}
}

// void writetoafile()
// {
//     std::ofstream myfile;
//     myfile.open ("example.txt", std::ios::out | std::ios::app);
//     myfile << threadmap.find(std::this_thread::get_id())->second << ": Writing this to a file.\n";
//     myfile.close();
// }

int main ()
{
  int tm_mday;  // day of month from 1 to 31
  int tm_mon;   // month of year from 0 to 11
  int tm_year;  // year since 1900
  std::regex month("[A-Za-z][A-Za-z][A-Za-z]");
  std::regex day("[0-9][0-9]");
  std::regex year("2[0-9][0-9][0-9]");
  std::string CurrentDate = getCurrentDate();
  std::cout <<"The Date today is(Boost): "<< CurrentDate << std::endl;
  std::cout <<"The Date today is(std):" << return_current_time_and_date() << std::endl;

  if (std::regex_search(CurrentDate, month))
  {
      std::cout << returnFirstMatch(CurrentDate, month) << std::endl;
  }

  if (std::regex_search(CurrentDate, day))
  {
      std::cout << returnFirstMatch(CurrentDate, day) << std::endl;
  }

  if (std::regex_search(CurrentDate, year))
  {
      std::cout << returnFirstMatch(CurrentDate, year) << std::endl;
  }

  std::cout << "Current path: " << std::filesystem::current_path() << std::endl;




  int quantity;
  std::string nameoflate;
  std::cout << "How many are late today?" << std::endl;
  std::cin >> quantity;
  std::string lates[quantity]  = {""};

  for(int currentlate = 0; currentlate < quantity; ++currentlate)
  {
      std::cout << "Please enter the name of the " << currentlate+1 << " out of " << quantity << " late today" << std::endl;
      std::cin >> nameoflate;
      lates[currentlate] = nameoflate;
  }

  std::cout << "The lates are: " << std::endl;

  for(auto element : lates)
  {
    std::cout << element << std::endl;
  }

  std::cout << return_current_time_and_date() << std::endl;






  /*
  if (std::regex_match ("subject", std::regex("(sub)(.*)") ))
    std::cout << "string literal matched\n";

  const char cstr[] = "subject";
  std::string s ("subject");
  std::regex e ("(sub)(.*)");

  if (std::regex_match (s,e))
    std::cout << "string object matched\n";

  if ( std::regex_match ( s.begin(), s.end(), e ) )
    std::cout << "range matched\n";

  std::cmatch cm;    // same as std::match_results<const char*> cm;
  std::regex_match (cstr,cm,e);
  std::cout << "string literal with " << cm.size() << " matches\n";

  std::smatch sm;    // same as std::match_results<string::const_iterator> sm;
  std::regex_match (s,sm,e);
  std::cout << "string object with " << sm.size() << " matches\n";

  std::regex_match ( s.cbegin(), s.cend(), sm, e);
  std::cout << "range with " << sm.size() << " matches\n";

  // using explicit flags:
  std::regex_match ( cstr, cm, e, std::regex_constants::match_default );

  std::cout << "the matches were: ";
  for (unsigned i=0; i<cm.size(); ++i) {
    std::cout << "[" << cm[i] << "] ";
  }

  std::cout << std::endl;
  */
  return 0;
}