local ffi = require 'ffi'
local ParseBack = require 'parseback'

ffi.cdef [[
struct Expr;
struct Select;
struct sql_trigger;

enum ast_type {
	AST_TYPE_UNDEFINED = 0,
	AST_TYPE_SELECT,
	AST_TYPE_EXPR,
	AST_TYPE_TRIGGER,
	ast_type_MAX
};

struct sql_parsed_ast {
	const char* sql_query;   /**< original query */
	enum ast_type ast_type;  /**< Type of parsed_ast member. */
	bool keep_ast;    /**< Keep AST after .parse */
	union {
		struct Expr *expr;
		struct Select *select;
		struct sql_trigger *trigger;
	};
};
]]


-- print (ParseBack.dot('union {struct {int x, y;}; long il; struct {Point px; union blurb bl;} st;}[5]'))
-- print (ParseBack.dot('enum twoenums', true))
-- print (ParseBack.dot('getit', true))
-- print (ParseBack.dot('enum ast_type', true))
print (ParseBack.dot('struct sql_parsed_ast', true))
