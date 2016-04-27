#include <iostream>
#include <string>
#include <vector>
#include <boost/spirit/include/qi.hpp>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;
namespace qi = boost::spirit::qi;
using qi::rule;
using qi::grammar;
using qi::parse;
namespace ascii = boost::spirit::ascii;
using ascii::alpha;
using ascii::space;
using ascii::space_type;

struct syntax : grammar<string::iterator, vector<string>()> {
	syntax(): syntax::base_type(start) {
		start = *space >> (+alpha % +space) >> *space;
	}
	rule<string::iterator, vector<string>()> start;
};

int main() {

	string s;
	syntax expr;

	while(getline(cin, s)) {
		string::iterator begin = s.begin();
		vector<string> ans;
		bool ok = parse(begin, s.end(), expr, ans);
		if(ok && begin == s.end()) {
			cout << "Success" << endl;
			cout << ans[0].length() << endl;
			for(int i=1;i<ans.size()-1;i++) {
				cout << ans[i] << endl;
			}
		} else {
			cout << "Failed" << endl;
		}
	}

}



