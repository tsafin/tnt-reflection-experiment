local io = require 'io'
local ffi = require 'ffi'
local ParseBack = require 'parseback'

local filename = 'tnt-sql-ast.h'
local f, err = io.open(filename)
if f == nil then
    error(("Can not open file '%s': %s"):format(filename, tostring(err)))
end

local cDefs = f:read '*a'

ffi.cdef(cDefs)

local yaml = require 'yaml'

print (ParseBack.typeinfo(ffi.typeof('struct sql_parsed_ast')))
--print (yaml.encode(ParseBack.typeinfo(ffi.typeof('enum ast_type'))))

