
auto Program = +Block;

auto Block = Declaration | Function | Object;

auto Declaration = Identifier >> '=' >> Expression;
auto Function = Normal_function | Quick_function;
auto Object = Identifier >> ':' >> *Identifier >> eol 
    >> *(Declaration | Object);

auto Identifier = alpha >> *(alnum | '_');
auto Expression = ('(' >> Expression >> ')') | (Expression >> Operation >> -Expression) | Identifier | Value;
auto Normal_function = "def" >> Identifier >> *Identifier >> eol
    >> *Program | ("return" >> Expression);
auto Quick_function = Identifier >> '=' >> '$' >> *Identifier >> eol
	>> *Program | ("return" >> Expression);

