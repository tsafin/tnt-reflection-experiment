local ffi = require 'ffi'
local ParseBack = require 'parseback'
----------------- utils -------------

local show do
	local function q(s)
		return type(s)=='string' and ('%q'):format(s) or s
	end

	local function qk(s)
		if type(s) == 'string' and s:match('^[_%a][_%w]*$') then
			return s
		end
		return ('[%s]'):format(q(s))
	end

	function show(var)
		local tv = type(var)
		if tv == 'table' then
			local o = {}
			for k, v in pairs(var) do
				if type(k) ~= 'number' or k < 1 or k > #var or math.floor(k)~=k then
					o[#o+1] = string.format('%s=%s', show(qk(k)), show(q(v)))
				end
			end
			for i = 1, #var do
				o[#o+1] = show(q(var[i]))
			end
			return '{'..table.concat(o, ', ')..'}'
		else
			return tostring(var)
		end
	end
end

ffi.cdef [[
// comment 1
struct Expr;
struct Select;
struct sql_trigger;

//< comment 2
/* comment 3 */
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

yaml = require 'yaml'
print (yaml.encode(ParseBack.typeinfo(ffi.typeof('struct sql_parsed_ast'))))
print (yaml.encode(ParseBack.typeinfo(ffi.typeof('enum ast_type'))))
