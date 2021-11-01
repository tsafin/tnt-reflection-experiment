enum field_type {
	FIELD_TYPE_ANY = 0,
	FIELD_TYPE_UNSIGNED,
	FIELD_TYPE_STRING,
	FIELD_TYPE_NUMBER,
	FIELD_TYPE_DOUBLE,
	FIELD_TYPE_INTEGER,
	FIELD_TYPE_BOOLEAN,
	FIELD_TYPE_VARBINARY,
	FIELD_TYPE_SCALAR,
	FIELD_TYPE_DECIMAL,
	FIELD_TYPE_UUID,
	FIELD_TYPE_ARRAY,
	FIELD_TYPE_MAP,
	field_type_MAX
};
enum on_conflict_action {
	ON_CONFLICT_ACTION_NONE = 0,
	ON_CONFLICT_ACTION_ROLLBACK,
	ON_CONFLICT_ACTION_ABORT,
	ON_CONFLICT_ACTION_FAIL,
	ON_CONFLICT_ACTION_IGNORE,
	ON_CONFLICT_ACTION_REPLACE,
	ON_CONFLICT_ACTION_DEFAULT,
	on_conflict_action_MAX
};
enum sort_order {
	SORT_ORDER_ASC = 0,
	SORT_ORDER_DESC,
	SORT_ORDER_UNDEF,
	sort_order_MAX
};
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
	const char *sql_query;
	enum ast_type ast_type;
	bool keep_ast;
	union {
		struct Expr *expr;
		struct Select *select;
		struct sql_trigger *trigger;
	};
};
typedef long long int sql_int64;
typedef unsigned long long int sql_uint64;
typedef sql_int64 sql_int64;
typedef sql_uint64 sql_uint64;
typedef struct sql_stmt sql_stmt;
typedef struct sql_context sql_context;
typedef struct sql sql;
typedef struct Mem sql_value;
typedef struct sql_file sql_file;
struct sql_file {
	const struct sql_io_methods *pMethods;
};
typedef int (*sql_callback)(void *, int, char **, char **);
typedef sql_int64 i64;
typedef sql_uint64 u64;
typedef unsigned int u32;
typedef unsigned short int u16;
typedef short int i16;
typedef unsigned char u8;
typedef signed char i8;
typedef u32 tRowcnt;
typedef short int LogEst;
typedef u64 uptr;
struct AggInfo {
	u8 directMode;
	u8 useSortingIdx;
	int sortingIdx;
	int sortingIdxPTab;
	int nSortingColumn;
	int mnReg, mxReg;
	struct ExprList *pGroupBy;
	struct AggInfo_col {
		struct space_def *space_def;
		int iTable;
		int iColumn;
		int iSorterColumn;
		int iMem;
		struct Expr *pExpr;
	} * aCol;
	int nColumn;
	int nAccumulator;
	struct AggInfo_func {
		struct Expr *pExpr;
		struct func *func;
		int iMem;
		int iDistinct;
		int reg_eph;
	} * aFunc;
	int nFunc;
};
typedef int ynVar;
struct Expr {
	u8 op;
	union {
		enum field_type type;
		enum on_conflict_action on_conflict_action;
	};
	u32 flags;
	union {
		char *zToken;
		int iValue;
	} u;
	struct Expr *pLeft;
	struct Expr *pRight;
	union {
		struct ExprList *pList;
		struct Select *pSelect;
	} x;
	int nHeight;
	int iTable;
	ynVar iColumn;
	i16 iAgg;
	i16 iRightJoinTable;
	u8 op2;
	struct AggInfo *pAggInfo;
	struct space_def *space_def;
};
struct ExprList {
	int nExpr;
	struct ExprList_item {
		struct Expr *pExpr;
		char *zName;
		char *zSpan;
		enum sort_order sort_order;
		unsigned done	    : 1;
		unsigned bSpanIsTab : 1;
		unsigned reusable   : 1;
		union {
			struct {
				u16 iOrderByCol;
				u16 iAlias;
			} x;
			int iConstExprReg;
		} u;
	} * a;
};
struct ExprSpan {
	struct Expr *pExpr;
	const char *zStart;
	const char *zEnd;
};
struct IdList {
	struct IdList_item {
		char *zName;
		int idx;
	} * a;
	int nId;
};
typedef u64 Bitmask;
struct SrcList {
	int nSrc;
	u32 nAlloc;
	struct SrcList_item {
		char *zName;
		char *zAlias;
		struct space *space;
		struct Select *pSelect;
		int addrFillSub;
		int regReturn;
		int regResult;
		struct {
			u8 jointype;
			unsigned notIndexed   : 1;
			unsigned isIndexedBy  : 1;
			unsigned isTabFunc    : 1;
			unsigned isCorrelated : 1;
			unsigned viaCoroutine : 1;
			unsigned isRecursive  : 1;
		} fg;
		u8 iSelectId;
		int iCursor;
		struct Expr *pOn;
		struct IdList *pUsing;
		Bitmask colUsed;
		union {
			char *zIndexedBy;
			struct ExprList *pFuncArg;
		} u1;
		struct index_def *pIBIndex;
	} a[1];
};
struct Select {
	struct ExprList *pEList;
	u8 op;
	LogEst nSelectRow;
	u32 selFlags;
	int iLimit, iOffset;
	char zSelName[12];
	int addrOpenEphm[2];
	struct SrcList *pSrc;
	struct Expr *pWhere;
	struct ExprList *pGroupBy;
	struct Expr *pHaving;
	struct ExprList *pOrderBy;
	struct Select *pPrior;
	struct Select *pNext;
	struct Expr *pLimit;
	struct Expr *pOffset;
	struct With *pWith;
};
struct SelectDest {
	u8 eDest;
	enum field_type *dest_type;
	int iSDParm;
	int reg_eph;
	int iSdst;
	int nSdst;
	struct ExprList *pOrderBy;
};
struct With {
	int nCte;
	struct With *pOuter;
	struct Cte {
		char *zName;
		struct ExprList *pCols;
		struct Select *pSelect;
		const char *zCteErr;
	} a[1];
};
