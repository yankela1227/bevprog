
/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

#include "std_lib_facilities.h"

struct Token {
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
    Token(char ch,string s) : kind(ch), name(s) { } //token with a name
};

class Token_stream {
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();
	void unget(Token t) { buffer=t; full=true; }

	void ignore(char);
};
const char let = 'L';
const char quit = 'Q';
const char print = ';';
const char number = '8';
const char name = 'a';
const char square = 's';
const char power = 'p';

const string declaration_keyword = "#";
const string quit_keyword = "exit";
const string sqrt_keyword = "sqrt";
const string pow_keyword = "pow";


Token Token_stream::get()
{
	if (full) { full=false; return buffer; }
	char ch;
	cin >> ch;
	switch (ch) {
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ';':
	case '=':
	case ',':
		return Token(ch);
	case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{	cin.unget();
		double val;
		cin >> val;
		return Token(number,val);
	}
	default:
		if (isalpha(ch)||ch=='#') {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch; //+was missing: attach characters
			cin.unget();
			if (s == declaration_keyword) return Token(let); //returns added: otherwise name would've returned
			if (s == quit_keyword) return Token(quit);
            if(s == sqrt_keyword) return Token(square);
            if(s == pow_keyword) return Token(power);
            return Token(name,s);
		}
		cout << ch <<endl;
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c==buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch;
	while (cin>>ch)
		if (ch==c) return;
}

struct Variable {
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined name ",s);
}

void set_value(string s, double d)
{
	for (int i = 0; i<=names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined name ",s);
}

bool is_declared(string s)
{
	for (int i = 0; i<names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{	double d = expression();
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return d;
	}
	case ')':
	{	double d = expression();
		t = ts.get();
		if (t.kind != '(') error("')' expected");
		return d;
	}

	case '-':
		return - primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
    case square: {                                        //square
        t=ts.get();
        if(t.kind!='(') error("'(' expected");
        double value = primary();
        t=ts.get();
        if(t.kind!=')') error("')' expected");
        if(value<0) error("Number must me >=0");
        return sqrt(value);
    }
    case power: {                                         //power
		t = ts.get();
		if(t.kind != '(') error("'(' expected");
		double value = primary();
		t = ts.get();
		if(t.kind != ',') error(", expected");
		int i = narrow_cast<int>(expression());
		t = ts.get();
		if(t.kind != ')') error("')' expected");
		return pow(value,i);
	}
	default:
		error("primary expected");
	}
}

double term()
{
	double left = primary();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{	double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

double expression()
{
	double left = term();
	while(true) {
		Token t = ts.get();
		switch(t.kind) {
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != 'a') error ("name expected in declaration");
	string name = t.name;
	if (is_declared(name)) error(name, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of " ,name);
	double d = expression();
	names.push_back(Variable(name,d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while(true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t=ts.get();
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch(runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

	try {
	    names.push_back(Variable{"k",1000.0}); // predefined k = 1000;
        set_value("k",1000.0);
		calculate();
		return 0;
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << endl;
		char c;
		while (cin >>c&& c!=';') ;
		return 1;
	}
	catch (...) {
		cerr << "exception\n";
		char c;
		while (cin>>c && c!=';');
		return 2;
	}
