#pragma once

#include <stdint.h>
#include <string>
#include <cassert>
#include <algorithm>

#include <fmt/format.h>
#include <fmt/color.h>
#include <fmt/ranges.h>

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

#define BOARD_PROMPT "a b c d e f g h i"
#define BOARD_NUM_PROMPT "０１２３４５６７８"

// 是否显示调试结果
constexpr bool USE_DEBUG = false;
// 是否显示错误
constexpr bool VIEW_ERROR = false;

// 分类棋子价值
constexpr int KING_VALUE = 1200;
constexpr int STRONG_VALUE = 100;
constexpr int WEAK_VALUE = 1;

// 三次违规
constexpr int MAX_NUM_VIOLATION = 3;
// 模拟最大次数，超过即退出模拟
constexpr int MAX_NUM_OF_MOCK = 800;
constexpr int BOARD_WIDTH = 9;
constexpr int BOARD_HEIGHT = 10;
constexpr int NUM_INTERSECTION = BOARD_WIDTH * BOARD_HEIGHT;
// Maximum possible value of coords.
constexpr int BOUND_COORD = BOARD_HEIGHT * BOARD_WIDTH;
constexpr uint64_t BOARD_NUM_ACTION = 2086;

// Maximum move. 正常比赛一般不超过200
constexpr int BOARD_MAX_MOVE = 200;
// 双方连续未吃子步数
constexpr int MAX_MOVE_NO_EAT = 120;

constexpr size_t NUM_OF_HISTORY = 18;

// 模拟最大深度
constexpr size_t SIMULATE_MAX_DEPTH = 8;

/// @brief 坐标
struct Coord
{
	int x = 9;
	int y = 9;

	Coord(int id_);

	Coord(int x_, int y_);

	Coord();

	/// @brief 序号
	/// @return 序号
	size_t id() const;

	/// @brief 左右对称的坐标
	/// @return 坐标
	Coord fliplr() const;

	/// @brief 与该坐标上下左右对称的坐标
	/// @return 坐标
	Coord UDLR() const;

	/// @brief 坐标是否在棋盘上
	/// @return 真或假
	bool on_board() const;

	/// @brief 坐标是否不在棋盘上
	/// @return 真或假
	bool off_board() const;

	/// @brief 棋子位置是否在九宫格内
	/// @return 真或假
	bool IsInFort() const;

	/// @brief 坐标字符串表达
	/// @return 字符串
	std::string toString() const;

	Coord &operator+=(const Coord &rhs) // compound assignment (does not need to be a member,
	{									// but often is, to modify the private members)
		x += rhs.x;
		y += rhs.y;
		return *this; // return the result by reference
	};

	// friends defined inside class body are inline and are hidden from non-ADL lookup
	friend Coord operator+(Coord lhs,		 // passing lhs by value helps optimize chained a+b+c
						   const Coord &rhs) // otherwise, both parameters may be const references
	{
		lhs += rhs; // reuse compound assignment
		return lhs; // return the result by value (uses move constructor)
	};

	friend bool operator>(const Coord &c1, const Coord &c2)
	{
		auto lv = c1.y * BOARD_WIDTH + c1.x;
		auto rv = c2.y * BOARD_WIDTH + c2.x;
		return lv > rv;
	};

	friend bool operator<(const Coord &c1, const Coord &c2)
	{
		auto lv = c1.y * BOARD_WIDTH + c1.x;
		auto rv = c2.y * BOARD_WIDTH + c2.x;
		return lv < rv;
	};

	friend bool operator==(const Coord &c1, const Coord &c2)
	{
		return c1.x == c2.x && c1.y == c2.y;
	};

	friend bool operator!=(const Coord &c1, const Coord &c2)
	{
		return c1.x != c2.x || c1.y != c2.y;
	};
};

typedef unsigned char Color;

constexpr int S_EMPTY = 0;
constexpr int S_RED = 1;
constexpr int S_BLACK = 2;

constexpr int M_RESIGN = 2086;
constexpr int M_INVALID = 2087;
constexpr int M_CLEAR = 2088;

#define STR_BOOL(s) ((s) ? "true" : "false")
#define STR_CHESS(s) ((s) == S_RED ? "R" : ((s) == S_BLACK ? "B" : "U"))
#define EMPTY(s) ((s) == S_EMPTY)

// 结果
typedef int Result;
#define NO_RESULT 2
#define RED_WIN 1
#define DRAW 0
#define RED_LOSE -1

// 棋子类型
// 空=0、兵=1、士=2、象=3、炮=4、马=5、车=6、帅=7
enum class PieceType
{
	EMPTY = 0,
	PAWN,
	GUARD,
	ELEPHANT,
	CANNON,
	HORSE,
	ROOK,
	KING
};

// 将=0、杀=1、捉=2、打=3、兑=4、献=5、拦=6、跟=7、闲=8
enum class MoveType
{
	// 照将
	JIANG = 0,
	// 杀着
	SHA,
	// 捉子
	ZHUO,
	// 打 以上三项统称
	DA,
	// 兑子
	DUI,
	// 献子
	XIANG,
	// 拦
	LAN,
	// 跟
	GENG,
	// 闲
	// 凡走子性质不属于将、杀、捉，统称为“闲”。兑、献、拦、跟，均属“闲”的范畴。
	XIAN,
};

constexpr const char *MoveTypeToString(MoveType e) noexcept
{
	switch (e)
	{
	case MoveType::JIANG:
		return "将";
	case MoveType::SHA:
		return "杀";
	case MoveType::ZHUO:
		return "捉";
	case MoveType::DUI:
		return "兑";
	case MoveType::XIAN:
		return "闲";
	default:
		return "闲";
	}
};

#define HAS_CHESS(s) (((s) == S_RED) || ((s) == S_BLACK))

constexpr Color OPPONENT(int p)
{
	return (Color)(S_BLACK + S_RED - (int)(p));
}

// 棋子价值
// 车、马、炮、过河兵(卒)、士、相(象)，均算“子力”。帅(将)、未过河兵(卒)，不算“子力”。“子力”简称“子”。
// 子力价值是衡量子力得失的尺度，也是判断是否“捉子”的依据之一。
// 原则上，一车相当于双马、双炮或一马一炮；马炮相等；士相(象)相等；过河兵(卒)价值浮动，一兵换取数子或一子换取数兵均不算得子。

// 棋盘子力价值、数量统计
struct PieceCount
{
	int value = 0;
	size_t weak = 0;
	size_t strong = 0;
	size_t pawn_not_cross = 0;
	size_t pawn_cross_river = 0;
};

struct PiecesValue
{
	int red;
	int black;
};

struct GamePieceCount
{
	PieceCount red;
	PieceCount black;
};

/// @brief 棋子颜色、类型、坐标详细信息
struct PieceInfo
{
	Color color = S_EMPTY;
	PieceType piece = PieceType::EMPTY;
	Coord coord = {9, 9};

	PieceInfo() : color(S_EMPTY), piece(PieceType::EMPTY), coord(9, 9){};

	PieceInfo(Color color_, PieceType piece_) : color(color_), piece(piece_){};

	PieceInfo(Color color_, PieceType piece_, Coord coord_) : color(color_), piece(piece_), coord(coord_){};

	/// @brief 该处是否为空白
	/// @return 真或假
	bool IsEmpty() const;

	/// @brief 与另外棋子是否为对手
	/// @param p2 棋子信息
	/// @return 真或假
	bool IsOpponent(const PieceInfo p2) const;

	/// @brief 与另外棋子是否为友军
	/// @param p2 棋子信息
	/// @return 真或假
	bool IsFriend(const PieceInfo p2) const;

	friend bool operator<(const PieceInfo &p1, const PieceInfo &p2)
	{
		if (p1.color == p2.color)
		{
			if (p1.piece == p2.piece)
			{
				return p1.coord < p2.coord;
			}
			else
			{
				return p1.piece < p2.piece;
			}
		}
		else
		{
			return p1.color < p2.color;
		}
	}

	friend bool operator==(const PieceInfo &p1, const PieceInfo &p2)
	{
		return (p1.color == p2.color && p1.piece == p2.piece && p1.coord == p2.coord);
	}

	friend bool operator!=(const PieceInfo &p1, const PieceInfo &p2)
	{
		return (p1.color != p2.color || p1.piece != p2.piece || p1.coord != p2.coord);
	}
};

struct MoveTypeInfo
{
	// 是否完成类型标记
	bool marked = false;

	// 移动类型
	MoveType move_t = MoveType::XIAN;

	// 移动后本可得子，但前后本质没有发生变化，依旧判闲
	bool z2x = false;

	// 吃后被将军失子 参考图图34-2
	bool chs = false;

	// 提子
	PieceInfo src;

	// 目标棋子
	PieceInfo tgt;

	// 照面、将死特殊得分
	int s_score = 0;

	// 是否形成重复局面
	bool s_draw = false;

	// 移动完成后，实际将军的棋子
	std::vector<PieceInfo> jj_after_moved;

	// 目标棋子无根保护
	bool no_root_protected = false;

	// 兑使用的棋子
	PieceInfo dui_src;

	// 兑目标棋子
	PieceInfo dui_tgt;

	// 捉使用的棋子
	PieceInfo zhuo_src;

	// 捉目标棋子
	PieceInfo zhuo_tgt;

	// 是否为联合捉子
	bool is_jointed = false;

	// 记录棋盘在此移动前连续未吃子计数
	short preNoEat = 0;
};

struct Move
{
	Coord from;
	Coord to;
	MoveTypeInfo info;

	Move() : from(9, 9), to(9, 9){};

	Move(int x1, int y1, int x2, int y2) : from{x1, y1}, to{x2, y2}
	{
		assertm(IsValid(), "无效移动构造");
	};

	Move(Coord from_, Coord to_) : from(from_), to(to_){};

	/// @brief 移动是否有效
	/// @return 真或假
	bool IsValid() const;

	/// @brief 移动是否将军
	/// @return 真或假
	bool is_check() const;

	/// @brief 移动是否联合将军，即移动为将军，且有其他棋子将军
	/// @return 真或假
	bool is_jointed_check() const;

	/// @brief 移动是否其他子将军，即移动为将军，但非所动之子将军
	/// @return 真或假
	bool is_other_check() const;

	/// @brief 移动是否吃子
	/// @return 真或假
	bool is_eat() const;

	/// @brief 移动字符串表达
	/// @return 字符串
	std::string toString() const;

	/// @brief 该移动开始与结束坐标互换后的移动
	/// @return 移动
	Move FT() const;

	/// @brief 与该移动左右对称的移动
	/// @return 移动
	Move fliplr() const;

	/// @brief 与该移动上下左右对称的移动
	/// @return 移动
	Move UDLR() const;

	friend bool operator>(const Move &m1, const Move &m2)
	{
		if (m1.from == m2.from)
		{
			return m1.to > m2.to;
		}
		else
		{
			return m1.from > m2.from;
		}
	}

	friend bool operator<(const Move &m1, const Move &m2)
	{
		if (m1.from == m2.from)
		{
			return m1.to < m2.to;
		}
		else
		{
			return m1.from < m2.from;
		}
	}

	friend bool operator==(const Move &m1, const Move &m2)
	{
		return (m1.from == m2.from && m1.to == m2.to);
	}

	friend bool operator!=(const Move &m1, const Move &m2)
	{
		return (m1.from != m2.from || m1.to != m2.to);
	}
};

// 空白坐标
const Coord EMPTY_COORD = {9, 9};
// 禁止坐标
const Coord PROHIBIT_COORD = {9, 1};
const Coord STOP_COORD = {9, 2};
const Move EMPTY_MOVE = {EMPTY_COORD, EMPTY_COORD};
const Move PROHIBIT_MOVE = {PROHIBIT_COORD, PROHIBIT_COORD};
const Move STOP_MOVE = {STOP_COORD, STOP_COORD};

// Faster access to neighbors.
// L/R means x-1/x+1
// T/B means y-1/y+1
inline Coord TO_L(const Coord &c)
{
	return Coord(c.x - 1, c.y);
}

inline Coord TO_R(const Coord &c)
{
	return Coord(c.x + 1, c.y);
}

inline Coord TO_T(const Coord &c)
{
	return Coord(c.x, c.y + 1);
}

inline Coord TO_B(const Coord &c)
{
	return Coord(c.x, c.y - 1);
}
// Left, top, right, bottom
static const int delta4[4][2] = {{-1, 0}, {0, -1}, {+1, 0}, {0, 1}};
// 红兵 Left, top, right
static const int RP[3][2] = {{-1, 0}, {0, 1}, {+1, 0}};
// 黑卒 Left, bottom, right
static const int BP[3][2] = {{-1, 0}, {0, -1}, {+1, 0}};

// 士 对角位移
static const int GU[4][2] = {{-1, -1},
							 {-1, 1},
							 {1, -1},
							 {1, 1}};
// 象 田字位移
static const int EL[4][2] = {{2, 2},
							 {2, -2},
							 {-2, 2},
							 {-2, -2}};

static const int EL_EYE[4][2] = {{1, 1},
								 {1, -1},
								 {-1, 1},
								 {-1, -1}};
// 马 日字位移
static const int HO[8][2] = {{-2, -1},
							 {-2, 1},
							 {-1, -2},
							 {-1, 2},
							 {1, 2},
							 {1, -2},
							 {2, -1},
							 {2, 1}};

static const int HO_LEG[8][2] = {{-1, 0}, {-1, 0}, {0, -1}, {0, 1}, {0, 1}, {0, -1}, {1, 0}, {1, 0}};

static const int delta8[8][2] = {{-1, 0},
								 {0, -1},
								 {+1, 0},
								 {0, 1},
								 {-1, -1},
								 {-1, 1},
								 {1, -1},
								 {1, 1}};

#define __STR_EXPAND(tok) #tok
#define __STR(tok) __STR_EXPAND(tok)

// Local check
#define FOR3RP(c, ii, cc)                               \
	for (int ii = 0; ii < 3; ++ii)                      \
	{                                                   \
		const Coord temp = Coord(RP[ii][0], RP[ii][1]); \
		Coord cc = c + temp;

#define ENDFOR3RP }

#define FOR3BP(c, ii, cc)                               \
	for (int ii = 0; ii < 3; ++ii)                      \
	{                                                   \
		const Coord temp = Coord(BP[ii][0], BP[ii][1]); \
		Coord cc = c + temp;

#define ENDFOR3BP }

#define FOR4(c, ii, cc)                                         \
	for (int ii = 0; ii < 4; ++ii)                              \
	{                                                           \
		const Coord temp = Coord(delta4[ii][0], delta4[ii][1]); \
		Coord cc = c + temp;

#define ENDFOR4 }

#define FORDIAG4(c, ii, cc)                             \
	for (int ii = 0; ii < 4; ++ii)                      \
	{                                                   \
		const Coord temp = Coord(GU[ii][0], GU[ii][1]); \
		Coord cc = c + temp;

#define ENDFORDIAG4 }

#define FOREL4(c, ii, cc)                                             \
	for (int ii = 0; ii < 4; ++ii)                                    \
	{                                                                 \
		const Coord temp_c = Coord(EL[ii][0], EL[ii][1]);             \
		Coord cc = c + temp_c;                                        \
		const Coord temp_c_eye = Coord(EL_EYE[ii][0], EL_EYE[ii][1]); \
		Coord cc_eye = c + temp_c_eye;

#define ENDFOREL4 }

#define FORHO8(c, ii, cc)                                           \
	for (int ii = 0; ii < 8; ++ii)                                  \
	{                                                               \
		const Coord temp_c = Coord(HO[ii][0], HO[ii][1]);           \
		Coord cc = c + temp_c;                                      \
		const Coord temp_leg = Coord(HO_LEG[ii][0], HO_LEG[ii][1]); \
		Coord cc_leg = c + temp_leg;

#define ENDFORHO8 }

// Zero based.
extern inline Coord getCoord(int x, int y)
{
	return Coord(x, y);
}

inline std::string coord2str(const Coord c)
{
	int x = c.x;
	int y = c.y;
	return fmt::format("{}{}", x, y);
}

inline Coord str2coord(const std::string &s)
{
	auto num = std::stoi(s);
	auto x = num / 10;
	auto y = num % 10;

	Coord c(x, y);
	if (c.off_board())
		return M_INVALID;
	return c;
}

// 生成移动
inline Move make_move(const std::string m)
{
	return {str2coord(m.substr(0, 2)), str2coord(m.substr(2, 4))};
}

inline Move make_move(int x1, int y1, int x2, int y2)
{
	return {Coord(x1, y1), Coord(x2, y2)};
}

// 转换为移动列表
inline std::vector<Move> iccs2Moves(const std::string iccs)
{
	const std::string nums = "0123456789";
	std::vector<Move> res;
	std::string m;
	for (size_t i = 0; i < iccs.length() / 4; i++)
	{
		m = iccs.substr(i * 4, 4);
		m = fmt::format("{}{}{}{}", nums[m[0] - 'a'], m[1], nums[m[2] - 'a'], m[3]);
		res.push_back(make_move(m));
	}
	return res;
}

template <>
struct fmt::formatter<Move>
{
	// Presentation format: 'f' - fixed, 'e' - exponential.
	char presentation = 'f';

	// Parses format specifications of the form ['f' | 'e'].
	constexpr auto parse(format_parse_context &ctx) -> decltype(ctx.begin())
	{
		// [ctx.begin(), ctx.end()) is a character range that contains a part of
		// the format string starting from the format specifications to be parsed,
		// e.g. in
		//
		//   fmt::format("{:f} - Move of interest", Move{1, 2});
		//
		// the range will contain "f} - Move of interest". The formatter should
		// parse specifiers until '}' or the end of the range. In this example
		// the formatter should parse the 'f' specifier and return an iterator
		// Moveing to '}'.

		// Please also note that this character range may be empty, in case of
		// the "{}" format string, so therefore you should check ctx.begin()
		// for equality with ctx.end().

		// Parse the presentation format and store it in the formatter:
		auto it = ctx.begin(), end = ctx.end();
		if (it != end && (*it == 'f' || *it == 'e'))
			presentation = *it++;

		// Check if reached the end of the range:
		if (it != end && *it != '}')
			throw format_error("invalid format");

		// Return an iterator past the end of the parsed range:
		return it;
	}

	// Formats the Move p using the parsed format specification (presentation)
	// stored in this formatter.
	template <typename FormatContext>
	auto format(const Move &m, FormatContext &ctx) const -> decltype(ctx.out())
	{
		// ctx.out() is an output iterator to write to.
		return format_to(
			ctx.out(),
			"{}{}",
			coord2str(m.from), coord2str(m.to));
	}
};

namespace std
{
	template <>
	struct hash<Move>
	{
		size_t operator()(const Move &m) const
		{
			const size_t h1(std::hash<int>{}(m.from.x));
			const size_t h2(std::hash<int>{}(m.from.y));
			const size_t h3(std::hash<int>{}(m.to.x));
			const size_t h4(std::hash<int>{}(m.to.y));
			return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
		}
	};
};
