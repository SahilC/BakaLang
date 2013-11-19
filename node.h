#include<iostream>
#include<vector>
#include<llvm/Value.h>

typedef std::vector<NStatement*> Slist;
typedef std::vector<NExpression*> EList;
typedef std::vector<NVariableDeclaration*> VList;

class  Node {
public:
	virtual ~ Node() {}
	virtual llvm::Value* codeGen(CodeGenContext& context){}
};

class NExpression : public Node {

};

class NStatement : public Node {

};

class NInteger : public NExpression {
public:
		long long value;
		NInteger(long long val){
			value=val;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NDouble : public NExpression {
public:
		double value;
		NDouble(double val){
			value=val;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NIdentifier : public NExpression {
public:
		std::string value;
		NIdentifier(const std::string val){
			value=val;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NMethodCall : public NExpression {
public:
		const NIdentifier& id;
		EList arguments;
		NMethodCall(const NIdentifier& val,EList& arg){
			id=val;
			arguments=arg;
		}
		NMethodCall(const NIdentifier& val){
			id=val;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBinaryOperator : public NExpression {
public:
		int op;
		NExpression& lhs;
		NExpression& rhs;
		NBinaryOperator(NExpression& l,int op,NExpression& r){
			op=op;
			lhs=l;
			rhs=r;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NAssignment : public NExpression {
public:
		NIdentifier& id;
		NExpression& rhs;
		NAssignment(NIdentifier& id,NExpression& exp){
			id=id;
			rhs=exp;
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBlock : public NExpression {
public:
		Slist statements;
		NBlock() {
		}
		virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NExpressionStatement : public NStatement {
public:
	NExpression& expression;
	NExpressionStatement(NExpression& exp) {
		expression=exp;
	}
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NVariableDeclaration : public NStatement {
public:
	const NIdentifier& type;
	NIdentifier& id;
	NExpression *assignment;
	NVariableDeclaration(const NIdentifier& t,NIdentifier& i) {
		id=i;
		type=t;
	}
	NVariableDeclaration(const NIdentifier& t,NIdentifier& i,NExpression& e) {
		id=t;
		type=t;
		assignment=e;
	}
	virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NFunctionDeclaration : public NStatement {
public:
	NIdentifier& id;
	NIdentifier& retType;
	VList arguments;
	NBlock& block;
	NFunctionDeclaration(const NIdentifier& i,const NIdentifier& r,const VList& arg,NBlock& n) {
		id=i;
		retType=r;
		arguments=arg;
		block=n;
	}
	virtual llvm::Value* codeGen(CodeGenContext& context); 
};