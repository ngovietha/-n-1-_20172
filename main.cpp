#include<iostream>
#include<stdio.h>
#include<gmp.h>
#include<gmpxx.h>
using namespace std;
void error(string s) {
	throw runtime_error(s);
}
class Token {
public:
	char kind;
	mpz_class value;
	Token(char ch)
		:kind(ch), value(0) {}
	Token(char ch, mpz_class val)
		:kind(ch), value(val) {}
};
class Token_stream {
public:
	Token_stream();
	Token get();
	void putback(Token t);
private:
	bool full;
	Token buffer;
};
Token_stream::Token_stream()
	:full(false), buffer(0) {}
void Token_stream::putback(Token t) {
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}
Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	cin >> ch;
	switch (ch) {
	case'=':
	case'q':
	case'(': case')': case'+':case'-':case'*':case'/':case'%':case'!':case'^':
		return Token(ch);
	case'.':
	case'0':case'1':case'2':case'3':case'4':
	case'5':case'6':case'7':case'8':case'9':
	{
		cin.putback(ch);
		 double val;
	cin>> val;
		return Token('8', val);
	}
	default:
		error(  "Ban chi co the nhap vao so thuc va cac phep toan + - * / ! ^ ") ;
	}
}
Token_stream ts;




 mpz_class expression();
mpz_class primary() {
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{   mpz_class d= expression();
	t = ts.get();
	if (t.kind != ')') error("Thieu dau dong ngoac!!!");
	return d;
	}case'8':
		return t.value;
	default:
		error("Bieu thuc ban nhap khong dung!!!");

	}
}
mpz_class term1() {
	mpz_class left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind) {
		case'!':
		    {mpz_class fact = 1;

    for (int i=2; i<=left; ++i)
         fact*= i;left=fact;}
            t = ts.get();
			break;
        case '^':
        mpz_ui_pow_ui (left.get_mpz_t(), left.get_ui(), primary().get_ui());
        t=ts.get();
      default:
			ts.putback(t);
			return left;
		}
	}
}
mpz_class term() {
	mpz_class left=term1();

	Token t = ts.get();
	while (true)
	{
		switch (t.kind) {
		case'*':
			left *= term1();
			t = ts.get();
			break;

		case'/':
		{
			mpz_class d = term1();
			if (d == 0) error("Khong the chia cho 0 !!!");
			left /= d;
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}
        mpz_class  expression() {
		mpz_class left= term();

		Token t = ts.get();
		while (true)
		{
			switch (t.kind) {
			case'+':
				left += term();
				t = ts.get();
				break;
			case '-':
				left -= term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
			}

		}
	}


		int main()
		{
			cout << "					  welcome to our simple calculator" << endl;
			cout << "		Moi ban nhap bieu thuc voi so nguyen,ket thuc boi dau bang.Cac phep toan + - * / ! ^ " << endl;
			cout << "				  De thoat khoi may tinh, nhan 'q', sau do nhan enter 2 lan " << endl;


				try {
					mpz_class val = 0;
					while (cin) {

						Token t = ts.get();
						if (t.kind == 'q') break;
						if (t.kind == '=')
							cout<<val.get_str(10)<<endl;
						else
							ts.putback(t);
						val = expression();

					}
				}

				catch (runtime_error&e) {
					cerr<<"runtime error: " <<e.what()<< endl;
				}
		}

