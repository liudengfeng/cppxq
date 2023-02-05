#include "common.hpp"

Coord::Coord(int id_)
{
    x = id_ % BOARD_WIDTH;
    y = id_ / BOARD_WIDTH;
};

Coord::Coord(int x_, int y_) : x(x_), y(y_){};

// 默认构造非法位置
Coord::Coord() : x(9), y(9){};

size_t Coord::id() const { return static_cast<size_t>(y * BOARD_WIDTH + x); };

// 左右对称的坐标
Coord Coord::fliplr() const { return Coord(8 - x, y); };
// 上下左右对称的坐标
Coord Coord::UDLR() const { return Coord(8 - x, 9 - y); };

bool Coord::on_board() const
{
    // fmt::print("onboard x = {} y = {}\n", x, y);
    return x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT;
};

bool Coord::off_board() const
{
    // fmt::print("off_board x = {} y = {}\n", x, y);
    return x < 0 || x >= BOARD_WIDTH || y < 0 || y >= BOARD_HEIGHT;
};

bool Coord::IsInFort() const
{
    if (off_board())
    {
        return false;
    }
    if (x < 3 || x > 5)
        return false;
    if (y > 2 && y < 7)
        return false;
    return true;
};

std::string Coord::toString() const { return fmt::format("{}{}", x, y); };

bool PieceInfo::IsEmpty() const { return !HAS_CHESS(this->color); };

bool PieceInfo::IsOpponent(const PieceInfo p2) const { return OPPONENT(this->color) == p2.color; };

bool PieceInfo::IsFriend(const PieceInfo p2) const
{
    return !this->IsEmpty() &&
           !p2.IsEmpty() &&
           this->color == p2.color;
};

bool Move::IsValid() const { return from.on_board() && to.on_board() && from != to; };

bool Move::is_check() const { return info.jj_after_moved.empty() ? false : info.jj_after_moved[0].color == info.src.color; };

bool Move::is_jointed_check() const
{
    return this->is_check() && std::any_of(info.jj_after_moved.begin(), info.jj_after_moved.end(), [this](const PieceInfo &p)
                                           { return p.coord != this->to; });
};

bool Move::is_other_check() const
{
    return this->is_check() && std::none_of(info.jj_after_moved.begin(), info.jj_after_moved.end(), [this](const PieceInfo &p)
                                            { return p.coord == this->to; });
};

bool Move::is_eat() const { return info.tgt.color == OPPONENT(info.src.color); };

std::string Move::toString() const { return from.toString() + to.toString(); };

Move Move::FT() const
{
    return Move(to, from);
};

Move Move::fliplr() const
{
    Coord from_(8 - from.x, from.y);
    Coord to_(8 - to.x, to.y);
    return Move(from_, to_);
};

Move Move::UDLR() const
{
    Coord from_(8 - from.x, 9 - from.y);
    Coord to_(8 - to.x, 9 - to.y);
    return Move(from_, to_);
};