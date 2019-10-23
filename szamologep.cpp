#include "std_lib_facilities.h"
    const char number = '8';		// a floating-point number
    const char quit = 'q';		// an exit command
    const char print = ';';
    const string prompt = "> ";
    const string result = "= ";
//------------------------------------------------------------------------------

class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) {}
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }

};

//------------------------------------------------------------------------------

class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t); // put a Token back
    void ignore(char c);
private:
    bool full{false};        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

void Token_stream::ignore(char c)
	// skip characters until we find a c; also discard that c
{
	// first look in buffer:
	if (full && c==buffer.kind) {	// && means and
		full = false;
		return;
	}
	full = false;	// discard the contents of buffer
	// now search input:
	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}


//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get()
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
        full=false;
        return buffer;
    }

    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case print:    // for "print"
    case quit:    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '9':
        {
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
            return Token(number,val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':    // handle '(' expression ')'
        {
            double d = expression();
            t = ts.get();
            if (t.kind != ')') error("')' expected");
            return d;
        }
    case number:            // we use '8' to represent a number
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
    double left = primary();
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch (t.kind) {
        case '*':{
            left *= primary();
            t = ts.get();
            break;
        }
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}
void clean_up_mess()
{
		ts.ignore(print);
}


void calculate(){
    while (cin) try {
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print) t=ts.get();	// first discard all �prints�
			if (t.kind == quit) return;		// quit
			ts.putback(t);
			cout << result << expression() << endl;
		}
		catch (exception& e) {
		cerr << e.what() << endl;		// write error message
		clean_up_mess();		// <<< The tricky part!
	}


}
//------------------------------------------------------------------------------

int main()
{
    cout << "Welcome to our simple calculator. Please enter expressions using floating-point numbers." << endl;
    cout << "Available operators: \n";
    cout << "+ => Plus\n" ;
    cout << "- => Minus\n" ;
    cout << "* => Multiple\n" ;
    cout << "/ => Divide\n";
    cout << "( ... ) => Paranteses\n" ;
    cout << "To exit the program, enter: q\n" ;
    cout << "To print results, enter: ;\n" ;
try
{
    calculate();
    keep_window_open();	// cope with Windows console mode
	return 0;

}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
	keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
	keep_window_open();
    return 2;
}
}
//------------------------------------------------------------------------------
