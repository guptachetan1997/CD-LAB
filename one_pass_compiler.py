SYMBOL_TABLE = dict()

class Lexer():
	def __init__(self):
		SYMBOL_TABLE["int"] = {"uuid" : 1, "value" : "int", "koi" : "k"};
		SYMBOL_TABLE["double"] = {"uuid" : 2, "value" : "double", "koi" : "k"};
		SYMBOL_TABLE["float"] = {"uuid" : 3, "value" : "float", "koi" : "k"};
		SYMBOL_TABLE["char"] = {"uuid" : 4, "value" : "char", "koi" : "k"};
		SYMBOL_TABLE["return"] = {"uuid" : 5, "value" : "return", "koi" : "k"};
		self.symbol_table_pointer = 6

	def isKeywordOrIdentifier(self, lexeme):
		# 0 : New Idetifier
		# 1 : Keyword
		# 2 : Recurring Identifier
		try:
			lookup = SYMBOL_TABLE[lexeme]
		except:
			lookup = None
		if lookup:
			if(lookup["koi"] == "k"):
				return 1
			else:
				return 2
		else:
			return 0

	def isOperator(self, c):
		return c in ['+', '-', '/', '*', '%', '=']

	def isAlnum(self, c):
		return c.isalnum();
	
	def isDelimiter(self, c):
		return c in [",", ";", " ", "$"];
	
	def getTokens(self, filename):
		tokenStreams = []
		buffer = ""
		buffer_pointer = 0
		with open(filename) as sourceFile:
			lines = sourceFile.readlines()
			for line in lines:
				tokenStream = ""
				for c in line:
					if self.isOperator(c):
						tokenStream += "<OP,{}>_".format(c)
					elif self.isAlnum(c):
						buffer += c
					elif self.isDelimiter(c) and len(buffer) is not 0:
						kw_id_check = self.isKeywordOrIdentifier(buffer)
						if kw_id_check == 1:
							tokenStream += "<KW,{}>_".format(SYMBOL_TABLE[buffer]["uuid"])
						elif(buffer[0] in "0,1,2,3,4,5,6,7,8,9".split(",")):
							print("error")
						else:
							if(kw_id_check != 2):
								SYMBOL_TABLE[buffer] = {
									"uuid" : self.symbol_table_pointer,
									"value" : buffer,
									"koi" : "i"
								}
								self.symbol_table_pointer+=1
							tokenStream += "<ID,{}>_".format(SYMBOL_TABLE[buffer]["uuid"])
						buffer = ""
				tokenStreams.append(tokenStream)
		return tokenStreams


class Parser():

	def parse(self, buffer, s_t_ref):
		self.buffer = buffer + "$";
		self.pointer = 0;
		self.l = buffer[self.pointer];
		self.error_flag = 0;
		self.s_t_ref = s_t_ref
		self.byte_code = ""
		self.main()
		return self.byte_code

	def advance(self, c):
		if(self.l == c):
			self.pointer+=1
			self.l = self.buffer[self.pointer];
		else:
			self.error_flag = 1

	def F(self):
		if(self.l == "i"):
			# print("F->i")
			self.advance("i")
			self.byte_code += self.s_t_ref[self.pointer-1]["value"]

	def H(self):
		if(self.l == "*"):
			# print("H->*FH")
			self.advance("*")
			self.F()
			self.byte_code += "*"
			self.H()
		else:
			# print("H->#")
			return

	def G(self):
		if(self.l == "+"):
			# print("G->+TG")
			self.advance("+")
			self.T()
			self.byte_code += "+"
			self.G()
		else:
			# print("G->#")
			return

	def T(self):
		# print("T->FH")
		self.F()
		self.H()

	def E(self):
		# print("E->TG")
		self.T()
		self.G()

	def main(self):
		self.E()
		if(self.l == "$"):
			return

def main():
	print("------------BYTECODE------------")
	lexical_analyser = Lexer()
	parser = Parser()
	token_streams = lexical_analyser.getTokens("one_pass_test.cpp")
	for ts in token_streams:
		splits = ts.split("_")[:-1]
		converted_line = ""
		s_t_ref = []
		for thing in splits:
			x = thing.split(",")
			if(x[0] == "<KW"):
				converted_line += "k"
			elif(x[0] == "<OP"):
				converted_line += x[1][:-1]
				s_t_ref.append({})
			elif(x[0] == "<ID"):
				converted_line += "i"
				for temp in SYMBOL_TABLE:
					if(SYMBOL_TABLE[temp]["uuid"] == int(x[1][:-1])):
						s_t_ref.append(SYMBOL_TABLE[temp])
						break
		print(parser.parse(converted_line, s_t_ref))

if __name__ == '__main__':
	main()