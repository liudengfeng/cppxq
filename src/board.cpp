#include "board.hpp"

inline size_t getZobristIndex(Coord c, const Color player, const PieceType p)
{
    assertm(p != PieceType::EMPTY, "不得为空");
    size_t index, s;
    s = player == S_RED ? 1 : 2;
    // [1,90]
    index = c.id() + 1;
    return s * index * static_cast<size_t>(p) - 1;
}

std::pair<int, int> deltaXY(const Coord c1, const Coord c2)
{
    std::pair<int, int> d;
    d.first = c1.x - c2.x;
    d.second = c1.y - c2.y;
    return d;
}

std::string action2str(int action)
{
    return I2M.at(action);
}

int str2action(const std::string movestr)
{
    return M2I.at(movestr);
}

std::string move2lr(const std::string movestr)
{
    auto m = make_move(movestr);
    return m.fliplr().toString();
}

std::string getSymbol(const PieceType p, const Color c)
{
    if (p == PieceType::EMPTY)
    {
        return "+";
    }

    bool cond = (c == S_RED);

    switch (p)
    {
    case PieceType::KING:
        return cond ? "K" : "k";
    case PieceType::GUARD:
        return cond ? "A" : "a";
    case PieceType::ELEPHANT:
        return cond ? "B" : "b";
    case PieceType::HORSE:
        return cond ? "N" : "n";
    case PieceType::ROOK:
        return cond ? "R" : "r";
    case PieceType::CANNON:
        return cond ? "C" : "c";
    case PieceType::PAWN:
        return cond ? "P" : "p";
    default:
        return "+";
        break;
    }
}

std::string getCNSymbol(const PieceType p, const Color c)
{
    if (p == PieceType::EMPTY)
        return "＋";

    bool cond = (c == S_RED);

    switch (p)
    {
    case PieceType::KING:
        return cond ? "帅" : "将";
    case PieceType::GUARD:
        return cond ? "仕" : "士";
    case PieceType::ELEPHANT:
        return cond ? "相" : "象";
    case PieceType::HORSE:
        return cond ? "傌" : "馬";
    case PieceType::ROOK:
        return cond ? "俥" : "車";
    case PieceType::CANNON:
        return cond ? "炮" : "砲";
    case PieceType::PAWN:
        return cond ? "兵" : "卒";
    default:
        return "＋";
        break;
    }
}

std::string color_cn_name(const Color &player)
{
    return player == S_RED ? "红" : player == S_BLACK ? "黑"
                                                      : "空";
}

bool is_cross_river_pawn(const PieceInfo &p)
{
    auto piece = p.piece;
    auto color = p.color;
    if (piece != PieceType::PAWN)
    {
        return false;
    }
    if (color == S_RED)
    {
        if (p.coord.y > 4)
        {
            return true;
        }
    }
    else
    {
        if (p.coord.y < 5)
        {
            return true;
        }
    }
    return false;
}

bool is_just_cross_river_pawn(const PieceInfo &p)
{
    if (p.piece != PieceType::PAWN)
    {
        return false;
    }
    auto color = p.color;
    std::vector<Coord> cs;
    // 从吃子一方的角度考虑
    if (color == S_BLACK)
    {
        cs.emplace_back(0, 4);
        cs.emplace_back(2, 4);
        cs.emplace_back(4, 4);
        cs.emplace_back(6, 4);
        cs.emplace_back(8, 4);
    }
    else
    {
        cs.emplace_back(0, 5);
        cs.emplace_back(2, 5);
        cs.emplace_back(4, 5);
        cs.emplace_back(6, 5);
        cs.emplace_back(8, 5);
    }
    return contains(cs, p.coord);
}

bool is_in_same_line(const Coord &c1, const Coord &c2)
{
    return c1.x == c2.x || c1.y == c2.y;
}

int get_piece_value(const PieceInfo &p)
{
    switch (p.piece)
    {
    case PieceType::EMPTY:
        return 0;
        break;
    case PieceType::KING:
        return 1200;
        break;
    case PieceType::GUARD:
        return 1;
        break;
    case PieceType::ELEPHANT:
        return 1;
        break;
    case PieceType::HORSE:
        return 100;
        break;
    case PieceType::ROOK:
        return 200;
        break;
    case PieceType::CANNON:
        return 100;
        break;
    case PieceType::PAWN:
        // 过河才计算子力
        // 过河价值 = 马或炮
        if (is_cross_river_pawn(p))
        {
            return 100;
        }
        else
        {
            return 0;
        }
        break;
    default:
        return 0;
        break;
    }
}

Board::Board()
// : logger_(logging::getIndexedLogger("Board-", ""))
{
    reset();
}

void Board::init_board()
{
    this->set_pieces(str2coord("00"), S_RED, PieceType::ROOK);
    this->set_pieces(str2coord("10"), S_RED, PieceType::HORSE);
    this->set_pieces(str2coord("20"), S_RED, PieceType::ELEPHANT);
    this->set_pieces(str2coord("30"), S_RED, PieceType::GUARD);
    this->set_pieces(str2coord("40"), S_RED, PieceType::KING);
    this->set_pieces(str2coord("50"), S_RED, PieceType::GUARD);
    this->set_pieces(str2coord("60"), S_RED, PieceType::ELEPHANT);
    this->set_pieces(str2coord("70"), S_RED, PieceType::HORSE);
    this->set_pieces(str2coord("80"), S_RED, PieceType::ROOK);

    this->set_pieces(str2coord("12"), S_RED, PieceType::CANNON);
    this->set_pieces(str2coord("72"), S_RED, PieceType::CANNON);

    this->set_pieces(str2coord("03"), S_RED, PieceType::PAWN);
    this->set_pieces(str2coord("23"), S_RED, PieceType::PAWN);
    this->set_pieces(str2coord("43"), S_RED, PieceType::PAWN);
    this->set_pieces(str2coord("63"), S_RED, PieceType::PAWN);
    this->set_pieces(str2coord("83"), S_RED, PieceType::PAWN);

    this->set_pieces(str2coord("09"), S_BLACK, PieceType::ROOK);
    this->set_pieces(str2coord("19"), S_BLACK, PieceType::HORSE);
    this->set_pieces(str2coord("29"), S_BLACK, PieceType::ELEPHANT);
    this->set_pieces(str2coord("39"), S_BLACK, PieceType::GUARD);
    this->set_pieces(str2coord("49"), S_BLACK, PieceType::KING);
    this->set_pieces(str2coord("59"), S_BLACK, PieceType::GUARD);
    this->set_pieces(str2coord("69"), S_BLACK, PieceType::ELEPHANT);
    this->set_pieces(str2coord("79"), S_BLACK, PieceType::HORSE);
    this->set_pieces(str2coord("89"), S_BLACK, PieceType::ROOK);

    this->set_pieces(str2coord("17"), S_BLACK, PieceType::CANNON);
    this->set_pieces(str2coord("77"), S_BLACK, PieceType::CANNON);

    this->set_pieces(str2coord("06"), S_BLACK, PieceType::PAWN);
    this->set_pieces(str2coord("26"), S_BLACK, PieceType::PAWN);
    this->set_pieces(str2coord("46"), S_BLACK, PieceType::PAWN);
    this->set_pieces(str2coord("66"), S_BLACK, PieceType::PAWN);
    this->set_pieces(str2coord("86"), S_BLACK, PieceType::PAWN);

    // this->verifyBoard();
}

void Board::clear()
{
    // The initial ply number is 1.
    _ply = 1;
    _hash = INIT_HASH;
    _hash_keys.clear();
    _hash_keys.push_back(_hash);
    _next_player = S_RED;
    _first_player = S_RED;
    _no_eat = 0;
    _result = NO_RESULT;
    _s_reason = "";
    _infos.clear();
    _moves_history.clear();
    for (size_t i = 0; i < NUM_INTERSECTION; i++)
    {
        _infos.emplace_back(S_EMPTY, PieceType::EMPTY);
    }
}

void Board::reset()
{
    clear();
    init_board();
}

Board Board::clone() const
{
    Board b2;
    b2._infos = _infos;
    b2._hash = _hash;
    b2._hash_keys = _hash_keys;
    b2._moves_history = _moves_history;
    b2._next_player = _next_player;
    b2._ply = _ply;
    b2._no_eat = _no_eat;
    b2._result = _result;
    return b2;
}

void Board::clear_history()
{
    _ply = 1;
    _hash_keys.clear();
    _moves_history.clear();
}

Board Board::flipup() const
{
    Color player;
    Board b2 = this->clone();
    // 初始化的棋盘需要清理
    b2.clear();
    // 清理后设定player
    player = OPPONENT(this->_next_player);
    b2.SetPlayer(player);
    Coord c;
    for (size_t i = 0; i < NUM_INTERSECTION; i++)
    {
        auto old = _infos[i];
        auto x = i % BOARD_WIDTH;
        auto y = i / BOARD_WIDTH;
        c = Coord(8 - x, 9 - y);
        if (old.color == S_RED || old.color == S_BLACK)
        {
            player = OPPONENT(old.color);
            b2.set_pieces(c, player, old.piece);
        }
    }
    b2._no_eat = this->_no_eat;
    b2._ply = this->_ply;
    return b2;
}

Board Board::fliplr() const
{
    Board b2 = this->clone();
    // 初始化的棋盘需要清理
    b2.clear();
    Coord c;
    Color player;
    for (size_t i = 0; i < NUM_INTERSECTION; i++)
    {
        auto old = _infos[i];
        auto x = i % BOARD_WIDTH;
        auto y = i / BOARD_WIDTH;
        c = Coord(8 - x, y);
        if (old.color == S_RED || old.color == S_BLACK)
        {
            player = old.color;
            b2.set_pieces(c, player, old.piece);
        }
    }
    b2._no_eat = this->_no_eat;
    b2._ply = this->_ply;
    return b2;
}

moveVec_t Board::GetMoveHistory() const
{
    return _moves_history;
}

moveVec_t Board::get_last_moves(size_t n) const
{
    moveVec_t moves;
    if (n > _moves_history.size())
    {
        return moves;
    }
    size_t start = _moves_history.size() - n;
    // 保持自然顺序
    for (size_t i = 0; i < n; i++)
    {
        moves.push_back(_moves_history[start + i]);
    }
    return moves;
}

void Board::MarkLastMove(const Move &m)
{
    Move &last = _moves_history.back();
    // 复制info对象
    last.info = m.info;
}

void Board::mark_moved_type(const Move &m, size_t i)
{
    assertm(i < _moves_history.size(), "替换移动历史必须提供有效索引");
    Move &to_replace = _moves_history[i];
    // 复制info对象
    to_replace.info = m.info;
}

Move Board::get_last_move() const
{
    if (_moves_history.empty())
    {
        // 返回无效移动
        return EMPTY_MOVE;
    }
    return _moves_history.back();
}

Move Board::get_previous_move() const
{
    if (_moves_history.size() < 2)
    {
        // 返回无效移动
        return EMPTY_MOVE;
    }
    auto t = _moves_history.size();
    return _moves_history[t - 2];
}

std::string Board::board_view_string(const bool viewDetail, const std::string &title) const
{
    std::string res = fmt::format(fg(fmt::color::sky_blue), "\n{:=^20}\n\n", title);
    for (int j = BOARD_HEIGHT - 1; j >= 0; --j)
    {
        res += fmt::format(fg(fmt::color::sky_blue), "{:d} ", j);
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            Coord c = Coord(i, j);
            Color color = this->_infos[c.id()].color;
            PieceType p = this->_infos[c.id()].piece;
            if (color == S_RED)
            {
                res += fmt::format(fg(fmt::color::red), "{}", getCNSymbol(p, color));
            }
            else if (color == S_BLACK)
            {
                res += fmt::format(fg(fmt::color::dark_green), "{}", getCNSymbol(p, color));
            }
            else
            {
                res += fmt::format(fg(fmt::color::gainsboro), "{}", getCNSymbol(p, color));
            }
        }
        res += fmt::format(fg(fmt::color::ivory), "{}", "\n");
    }
    res += fmt::format(fg(fmt::color::ivory), "{}", "  ");
    res += fmt::format(fg(fmt::color::sky_blue), "{}", BOARD_NUM_PROMPT);
    res += fmt::format(fg(fmt::color::ivory), "{}", "\n");
    auto player = this->_next_player;
    if (viewDetail)
    {
        auto m = this->get_last_move();
        // std::string last_move = m.IsValid() ? fmt::format("{}", m) : "";
        std::string last_move = _ply >= 2 ? fmt::format("{}", m) : "";
        if (m.IsValid())
        {
            res += fmt::format(fg(fmt::color::sky_blue),
                               "轮到{}走子，共{:>3}步，最后一步({})\n", player == S_RED ? "红方" : "黑方", this->_ply - 1, last_move);
        }
        else
        {
            res += fmt::format(fg(fmt::color::sky_blue),
                               "轮到{}走子\n", player == S_RED ? "红方" : "黑方");
        }
        if (_ply >= 2)
        {
            res += fmt::format(fg(fmt::color::sky_blue), "走子记录：\n{}\n", get_move_history_view_string());
        }
    }
    if (_result != NO_RESULT)
    {
        res += fmt::format(fg(fmt::color::sky_blue), "游戏结束。");
        if (_result == DRAW)
        {
            res += fmt::format(fg(fmt::color::green), "平局");
        }
        else if (_result == RED_WIN)
        {
            res += fmt::format(fg(fmt::color::red), "红胜");
        }
        else if (_result == RED_LOSE)
        {
            res += fmt::format(fg(fmt::color::green), "黑胜");
        }
        res += fmt::format(fg(fmt::color::sky_blue), "[{}]\n", _s_reason);
    }
    else
    {
        res += fmt::format(fg(fmt::color::sky_blue), "\n对局中......");
    }
    res += "\n";
    return res;
}

void Board::show_board(const bool viewDetail, const std::string &title) const
{
    auto res = board_view_string(viewDetail, title);
    fmt::print("{}", res);
    std::cout << std::flush;
}

Piece Board::get_piece(int x, int y) const
{
    Piece p;
    Coord c = Coord(x, y);
    Color color = this->_infos[c.id()].color;
    PieceType pid = this->_infos[c.id()].piece;
    p.x = x;
    p.y = y;
    p.color_id = static_cast<int>(color);
    p.piece_id = static_cast<int>(pid);
    p.color_name = color_cn_name(color);
    p.piece_name = getCNSymbol(pid, color);
    return p;
}

std::vector<std::vector<std::string>> Board::piece_cn_names() const
{
    std::vector<std::vector<std::string>> res;
    for (int j = BOARD_HEIGHT - 1; j >= 0; --j)
    {
        std::vector<std::string> row;
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            Coord c = Coord(i, j);
            Color color = this->_infos[c.id()].color;
            PieceType p = this->_infos[c.id()].piece;
            row.push_back(getCNSymbol(p, color));
        }
        res.push_back(row);
    }
    return res;
}

std::vector<std::vector<std::string>> Board::piece_cn_colors() const
{
    std::vector<std::vector<std::string>> res;
    for (int j = BOARD_HEIGHT - 1; j >= 0; --j)
    {
        std::vector<std::string> row;
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            Coord c = Coord(i, j);
            Color color = this->_infos[c.id()].color;
            row.push_back(color_cn_name(color));
        }
        res.push_back(row);
    }
    return res;
}

std::string Board::next_player_string() const
{
    return this->_next_player == S_RED ? "红方" : "黑方";
}

std::string Board::game_result_string() const
{
    std::string res = "对局中......";
    if (_result != NO_RESULT)
    {
        res = "游戏结束";
        if (_result == DRAW)
        {
            res += "（平局）";
        }
        else if (_result == RED_WIN)
        {
            res += "（红胜）";
        }
        else if (_result == RED_LOSE)
        {
            res += "（黑胜）";
        }
        res += fmt::format("[{}]", _s_reason);
    }
    return res;
}

std::string Board::board_string(const bool viewDetail) const
{
    std::string str;
    str += "\n";
    for (int j = BOARD_HEIGHT - 1; j >= 0; --j)
    {
        str += fmt::format("{:d} ", j);
        for (int i = 0; i < BOARD_WIDTH; ++i)
        {
            Coord c = Coord(i, j);
            Color color = this->_infos[c.id()].color;
            PieceType p = this->_infos[c.id()].piece;
            str += getCNSymbol(p, color);
        }
        str += "\n";
    }
    str += fmt::format("{}", "  ");
    str += fmt::format("{}", BOARD_NUM_PROMPT);
    str += fmt::format("{}", "\n");
    if (viewDetail)
    {
        str += fmt::format("第{:>3}步 ", this->_ply);
        auto m = this->get_last_move();
        std::string last_move = _ply == 1 ? "" : fmt::format("{}", m);
        str += fmt::format("最后一步({}) player = {}\n",
                           last_move,
                           this->_next_player == S_RED ? "红方" : "黑方");
    }
    return str;
}

std::string Board::get_rb_fen() const
{
    auto b1 = this->flipup();
    return b1.get_fen_string(false, true, true);
}

std::string Board::get_lr_fen() const
{
    auto b1 = this->fliplr();
    return b1.get_fen_string(false, true, true);
}

int Board::get_piece_id(int x, int y) const
{
    Coord c(x, y);
    return static_cast<int>(_infos[c.id()].piece);
}

int Board::get_piece_bid(int x, int y) const
{
    Coord c(x, y);
    auto b_ind = [](const PieceType &p, const Color &color)
    {
        auto pid = static_cast<int>(p) - 1;
        if (color == S_BLACK)
        {
            pid += 7;
        }
        return pid;
    };
    auto p = _infos[c.id()].piece;
    auto color = _infos[c.id()].color;
    if (color == S_EMPTY)
    {
        return -1;
    }
    else
    {
        return b_ind(p, color);
    }
}

std::vector<std::vector<std::vector<int>>> Board::getActionFeature(int action)
{
    auto move = make_move(I2M.at(action));
    std::vector<std::vector<std::vector<int>>> res;
    std::vector<int> row(BOARD_WIDTH, 0);
    std::vector<std::vector<int>> tab(BOARD_HEIGHT, row);
    // 建立一个空白表
    for (size_t i = 0; i < 14; i++)
    {
        res.push_back(tab);
    }
    // 移动棋子开始坐标的棋子标记1
    auto src = _infos[move.from.id()];
    auto src_id = static_cast<int>(src.piece) - 1;
    res.at(src_id).at(9 - move.from.y).at(move.from.x) = 1;
    auto tgt = _infos[move.to.id()];
    if (!tgt.IsEmpty())
    {
        auto tgt_id = static_cast<int>(tgt.piece) - 1 + 7;
        res.at(tgt_id).at(9 - move.to.y).at(move.to.x) = 1;
    }
    return res;
}

std::vector<std::vector<int>> Board::get2d(bool lr)
{
    if (lr)
    {
        auto b2 = fliplr();
        return b2.get2d(false);
    }
    std::vector<std::vector<int>> res;
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        std::vector<int> row(BOARD_WIDTH, 0);
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            auto c = Coord(x, y);
            auto color = this->_infos[c.id()].color;
            auto p = this->_infos[c.id()].piece;
            auto pid = static_cast<int>(p);
            if (color == S_BLACK)
            {
                pid *= -1;
            }
            row[x] = pid;
        }
        res.push_back(row);
    }
    return res;
}

std::vector<std::vector<std::vector<int>>> Board::get3d(bool lr)
{
    if (lr)
    {
        auto b2 = fliplr();
        return b2.get3d(false);
    }
    int pid;
    std::vector<std::vector<std::vector<int>>> res;
    std::vector<int> row(BOARD_WIDTH, 0);
    std::vector<std::vector<int>> tab(BOARD_HEIGHT, row);
    auto p_ind = [](const PieceType &p, const Color &color)
    {
        auto pid = static_cast<int>(p) - 1;
        if (color == S_BLACK)
        {
            pid += 7;
        }
        return pid;
    };
    for (size_t i = 0; i < 14; i++)
    {
        res.push_back(tab);
    }
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            auto c = Coord(x, y);
            auto color = this->_infos[c.id()].color;
            auto p = this->_infos[c.id()].piece;
            if (color != S_EMPTY)
            {
                pid = p_ind(p, color);
                res.at(pid).at(9 - y).at(x) = 1;
            }
        }
    }
    return res;
}

std::vector<Piece> Board::get_pieces(bool lr)
{
    if (lr)
    {
        auto b2 = fliplr();
        return b2.get_pieces(false);
    }
    std::vector<Piece> res;
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            auto c = Coord(x, y);
            auto color = this->_infos[c.id()].color;
            auto p = this->_infos[c.id()].piece;
            if (color != S_EMPTY)
            {
                Piece piece;
                piece.x = x;
                piece.y = y;
                piece.color_id = static_cast<int>(color);
                piece.piece_id = static_cast<int>(p);
                piece.color_name = color_cn_name(color);
                piece.piece_name = getCNSymbol(p, color);
                res.push_back(piece);
            }
        }
    }
    return res;
}

void Board::on_board_error(const std::string msg)
{
    if (VIEW_ERROR)
    {
        fmt::print(fg(fmt::color::dark_green), "\n错误信息:{}\n", msg);
        this->show_board(true, "ERROR");
    }
    throw std::out_of_range(msg);
}

void Board::verifyBoard()
{
    int red_king = 0;
    int black_king = 0;
    int red_guard = 0;
    int black_guard = 0;
    int red_elephant = 0;
    int black_elephant = 0;
    int red_horse = 0;
    int black_horse = 0;
    int red_rook = 0;
    int black_rook = 0;
    int red_cannon = 0;
    int black_cannon = 0;
    int red_pawn = 0;
    int black_pawn = 0;
    for (size_t i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    {
        auto p = this->_infos[i].piece;
        auto c = this->_infos[i].color;
        auto x = i % BOARD_WIDTH;
        auto y = i / BOARD_WIDTH;
        if (c == S_RED)
        {
            switch (p)
            {
            case PieceType::KING:
                if (x < 3 || x > 5 || y > 2)
                {
                    this->on_board_error(fmt::format("红'帅'({},{})位置错误", x, y));
                }
                ++red_king;
                break;
            case PieceType::GUARD:
                if (!((y == 0 && (x == 3 || x == 5)) || (y == 1 && x == 4) || (y == 2 && (x == 3 || x == 5))))
                {
                    this->on_board_error(fmt::format("红'士'({},{})位置错误", x, y));
                }
                ++red_guard;
                break;
            case PieceType::ELEPHANT:
                if (!((y == 0 && (x == 2 || x == 6)) || (y == 2 && (x == 0 || x == 4 || x == 8)) || (y == 4 && (x == 2 || x == 6))))
                {
                    this->on_board_error(fmt::format("红'相'({},{})位置错误", x, y));
                }
                ++red_elephant;
                break;
            case PieceType::HORSE:
                ++red_horse;
                break;
            case PieceType::ROOK:
                ++red_rook;
                break;
            case PieceType::CANNON:
                ++red_cannon;
                break;
            case PieceType::PAWN:
                if (y < 3 || (y <= 4 && x % 2 == 1))
                {
                    this->on_board_error(fmt::format("红'兵'({},{})位置错误", x, y));
                }
                ++red_pawn;
                break;
            default:
                break;
            }
        }
        else
        {
            switch (p)
            {
            case PieceType::KING:
                if (x < 3 || x > 5 || y < 7)
                {
                    this->on_board_error(fmt::format("黑'将'({},{})位置错误", x, y));
                }
                ++black_king;
                break;
            case PieceType::GUARD:
                if (!((y == 9 && (x == 3 || x == 5)) || (y == 8 && x == 4) || (y == 7 && (x == 3 || x == 5))))
                {
                    this->on_board_error(fmt::format("黑'仕'({},{})位置错误", x, y));
                }
                ++black_guard;
                break;
            case PieceType::ELEPHANT:
                if (!((y == 9 && (x == 2 || x == 6)) || (y == 7 && (x == 0 || x == 4 || x == 8)) || (y == 5 && (x == 2 || x == 6))))
                {
                    this->on_board_error(fmt::format("红'相'({},{})位置错误", x, y));
                }
                ++black_elephant;
                break;
            case PieceType::HORSE:
                ++black_horse;
                break;
            case PieceType::ROOK:
                ++black_rook;
                break;
            case PieceType::CANNON:
                ++black_cannon;
                break;
            case PieceType::PAWN:
                if (y > 6 || (y >= 5 && x % 2 == 1))
                {
                    this->on_board_error(fmt::format("黑'卒'({},{})位置错误", x, y));
                }
                ++black_pawn;
                break;
            default:
                break;
            }
        }
    }

    if (red_king != 1)
    {
        this->on_board_error(fmt::format("红方应当有且仅有一个'帅'"));
    }

    if (black_king != 1)
    {
        this->on_board_error(fmt::format("黑方应当有且仅有一个'将'"));
    }

    if (red_guard > 2)
    {
        this->on_board_error(fmt::format("红方最多二个'士'"));
    }

    if (black_guard > 2)
    {
        this->on_board_error(fmt::format("黑方最多二个'士'"));
    }

    if (red_elephant > 2)
    {
        this->on_board_error(fmt::format("红方最多二个'相'"));
    }

    if (black_elephant > 2)
    {
        this->on_board_error(fmt::format("黑方最多二个'象'"));
    }

    if (red_horse > 2)
    {
        this->on_board_error(fmt::format("红方最多二个'傌'"));
    }

    if (black_horse > 2)
    {
        this->on_board_error(fmt::format("黑方最多二个'馬'"));
    }

    if (red_rook > 2)
    {
        this->on_board_error(fmt::format("红方最多二个'俥'"));
    }

    if (black_rook > 2)
    {
        this->on_board_error(fmt::format("黑方最多二个'車'"));
    }

    if (red_cannon > 2)
    {
        this->on_board_error(fmt::format("红方最多二个'炮'"));
    }

    if (black_cannon > 2)
    {
        this->on_board_error(fmt::format("黑方最多二个'砲'"));
    }

    if (red_pawn > 5)
    {
        this->on_board_error("红方最多五个'兵'");
    }

    if (black_pawn > 5)
    {
        this->on_board_error("黑方最多五个'卒'");
    }
}

// void Board::SetPlayer(char c)
// {
//     if (std::tolower(c) == 'b' || std::tolower(c) == 'w')
//     {
//         _next_player = S_BLACK;
//         _first_player = S_BLACK;
//     }
//     else if (std::tolower(c) == 'r')
//     {
//         _next_player = S_RED;
//         _first_player = S_RED;
//     }
//     else
//     {
//         throw std::runtime_error("走子方设置错误!");
//     }
// }

void Board::SetPlayer(Color player)
{
    if (player == S_RED)
    {
        SetPlayer("R");
    }
    else if (player == S_BLACK)
    {
        SetPlayer("B");
    }
    else
    {
        throw std::runtime_error(fmt::format(
            "只能是红或黑，输入为：{}", color_cn_name(player)));
    }
}

void Board::SetPlayer(std::string str)
{
    if (str == "B" || str == "b" || str == "黑" || str == "黑方")
    {
        _next_player = S_BLACK;
        _first_player = S_BLACK;
    }
    else if (str == "R" || str == "r" || str == "W" || str == "w" || str == "红" || str == "红方")
    {
        _next_player = S_RED;
        _first_player = S_RED;
    }
    else
    {
        throw std::runtime_error("走子方设置错误!");
    }
}

void Board::SetResult(int r, const std::string reason)
{
    if (r == 1)
    {
        _result = RED_WIN;
    }
    else if (r == 0)
    {
        _result = DRAW;
    }
    else
    {
        _result = RED_LOSE;
    }
    _s_reason = reason;
}

void Board::ClearPiece(Coord c)
{
    this->_infos[c.id()].piece = PieceType::EMPTY;
    this->_infos[c.id()].color = S_EMPTY;
}

void Board::set_pieces(std::string str, bool verify, bool include_no_eat)
{
    bool notFen = str.find("/") == std::string::npos;
    // 当不是fen格式而include_no_eat为真时，触发异常
    if (notFen && include_no_eat)
    {
        throw std::runtime_error("输入字符串非标准fen格式，无法解析连续未吃子数量!");
    }
    std::string ps;
    auto elems = helper::split(str, ' ');
    if (notFen)
    {
        ps = str;
    }
    else
    {
        str = elems[0];
        if (elems.size() >= 2)
        {
            auto player = elems[1];
            SetPlayer(player);
        }
        char p;
        int n;
        for (size_t i = 0; i < str.size(); i++)
        {
            p = str[i];
            if (p == '/')
            {
                continue;
            }
            else if (std::isdigit(p))
            {
                n = p - '0';
                for (size_t i = 0; i < static_cast<size_t>(n); i++)
                {
                    ps += '+';
                }
            }
            else
            {
                ps += p;
            }
        }
    }
    if (elems.size() == 6)
    {
        // if (include_no_eat)
        // {
        // 第四部分
        auto e = elems[3];
        if (e != "-" && e != "0")
        {
            _set_no_eat_num(std::stoi(e));
        }
        // }
        // 步数
        auto s = elems[5];
        if (s == "0")
        {
            _set_steps(1);
        }
        else if (s != "-" && s != "0")
        {
            _set_steps(std::stoi(s));
        }
    }
    if (ps.length() != NUM_INTERSECTION)
    {
        throw std::out_of_range("字符串其长度应为90!");
    }
    // assertm(ps.length() == NUM_INTERSECTION, "字符串其长度应为90");
    Coord c, i;
    for (size_t y = 0; y < BOARD_HEIGHT; y++)
    {
        for (size_t x = 0; x < BOARD_WIDTH; x++)
        {
            c = Coord(x, 9 - y);
            i = Coord(x, y);
            this->set_pieces(ps[i.id()], c);
        }
    }
    if (verify)
    {
        this->verifyBoard();
    }
}

void Board::set_pieces(char p, const Coord coord, bool h)
{
    PieceType piece;
    Color color = p == '+' ? S_EMPTY : std::isupper(p) ? S_RED
                                                       : S_BLACK;

    switch (std::toupper(p))
    {
    case 'K':
        piece = PieceType::KING;
        break;
    case 'A':
        piece = PieceType::GUARD;
        break;
    case 'B':
        piece = PieceType::ELEPHANT;
        break;
    case 'N':
        piece = PieceType::HORSE;
        break;
    case 'R':
        piece = PieceType::ROOK;
        break;
    case 'C':
        piece = PieceType::CANNON;
        break;
    case 'P':
        piece = PieceType::PAWN;
        break;
    default:
        piece = PieceType::EMPTY;
        break;
    }
    this->set_pieces(coord, color, piece, h);
}

void Board::set_pieces(Coord c, Color s, PieceType p, bool h)
{
    PieceType old_p = this->_infos[c.id()].piece;
    Color old_c = this->_infos[c.id()].color;

    if (h)
    {
        if (old_c == S_RED || old_c == S_BLACK)
        {
            auto old_i = getZobristIndex(c, old_c, old_p);
            this->_hash ^= _board_hash[old_i];
        }
    }

    this->_infos[c.id()] = PieceInfo(s, p, c);

    if (h)
    {
        if (s == S_RED || s == S_BLACK)
        {
            auto i = getZobristIndex(c, s, p);
            this->_hash ^= _board_hash[i];
        }
    }

    // 确保保留最初 hash
    if (_ply == 1)
    {
        _hash_keys.clear();
        // 保留最新的_hash值
        _hash_keys.push_back(this->_hash);
    }
}

infoVec_t Board::find_PCs(const Color &player) const
{
    infoVec_t res;
    for (size_t i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
    {
        if (_infos[i].color == player)
        {
            res.push_back(_infos[i]);
        }
    }
    return res;
}

void Board::add_red_king_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FOR4(c, i, c_target)
    {
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 1
        if (abs(d.first) + abs(d.second) == 1 && c_target.IsInFort())
        {
            if (c_target.y >= 0 && c_target.y <= 2)
            {
                m.from = c;
                m.to = c_target;
                m.info.src = PieceInfo(S_RED, PieceType::KING, c);
                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFOR4
}

void Board::add_black_king_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FOR4(c, i, c_target)
    {
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 1
        if (abs(d.first) + abs(d.second) == 1 && c_target.IsInFort())
        {
            if (c_target.y >= 7 && c_target.y <= 9)
            {
                m.from = c;
                m.to = c_target;
                m.info.src = PieceInfo(S_BLACK, PieceType::KING, c);
                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFOR4
}

void Board::add_red_guard_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FORDIAG4(c, i, c_target)
    {
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 2
        if (abs(d.first) + abs(d.second) == 2 && c_target.IsInFort())
        {
            if (c_target.y >= 0 && c_target.y <= 2)
            {
                m.from = c;
                m.to = c_target;
                m.info.src = PieceInfo(S_RED, PieceType::GUARD, c);
                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFORDIAG4
}

void Board::add_black_guard_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FORDIAG4(c, i, c_target)
    {
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 2
        if (abs(d.first) + abs(d.second) == 2 && c_target.IsInFort())
        {
            if (c_target.y >= 7 && c_target.y <= 9)
            {
                m.from = c;
                m.to = c_target;
                m.info.src = PieceInfo(S_BLACK, PieceType::GUARD, c);
                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFORDIAG4
}

void Board::add_red_elephant_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FOREL4(c, i, c_target)
    {
        // 在没有被塞住象眼时
        auto has_eye = _infos[cc_eye.id()].piece != PieceType::EMPTY;
        if (!has_eye)
        {
            // 目标区域有效
            auto d = deltaXY(c, c_target);
            // abs(delta_x) + abs(delta_y) = 4
            if (abs(d.first) + abs(d.second) == 4 && c_target.on_board())
            {
                if (c_target.y >= 0 && c_target.y <= 4)
                {
                    m.from = c;
                    m.to = c_target;
                    m.info.src = PieceInfo(S_RED, PieceType::ELEPHANT, c);
                    if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                    {
                        m.info.tgt = _infos[c_target.id()];
                        moves.push_back(m);
                    }
                }
            }
        }
    }
    ENDFOREL4
}

void Board::add_black_elephant_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FOREL4(c, i, c_target)
    {
        // 在没有被塞住象眼时
        auto has_eye = _infos[cc_eye.id()].piece != PieceType::EMPTY;
        if (!has_eye)
        {
            // 目标区域有效
            auto d = deltaXY(c, c_target);
            // abs(delta_x) + abs(delta_y) = 4
            if (abs(d.first) + abs(d.second) == 4 && c_target.on_board())
            {
                if (c_target.y >= 5 && c_target.y <= 9)
                {
                    m.from = c;
                    m.to = c_target;
                    m.info.src = PieceInfo(S_BLACK, PieceType::ELEPHANT, c);
                    if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                    {
                        m.info.tgt = _infos[c_target.id()];
                        moves.push_back(m);
                    }
                }
            }
        }
    }
    ENDFOREL4
}

void Board::add_horse_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    FORHO8(c, i, c_target)
    {
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 3
        if (abs(d.first) + abs(d.second) == 3 && c_target.on_board())
        {
            // 马腿位置是否有子存在
            bool has_leg = _infos[cc_leg.id()].piece != PieceType::EMPTY;
            if (!has_leg)
            {
                m.from = c;
                m.to = c_target;
                auto player = _infos[c.id()].color;
                m.info.src = PieceInfo(player, PieceType::HORSE, c);
                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFORHO8
}

void Board::add_cannon_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    Coord c_target;

    // 上下左右移动
    // left
    c_target = c;
    do
    {
        c_target = TO_L(c_target);
        if (c_target.on_board() && c_target.x < c.x)
        {
            // std::cout << "开始位置(" << c.x << c.y << ")左移=>"
            //           << "x = " << c_target.x << " y = " << c_target.y << std::endl;
            if (_infos[c_target.id()].piece == PieceType::EMPTY)
            {
                m.from = c;
                m.to = c_target;
                auto player = _infos[c.id()].color;
                m.info.src = PieceInfo(player, PieceType::CANNON, c);
                moves.push_back(m);
            }
            else
            {
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x >= 0);

    // right
    c_target = c;
    do
    {
        c_target = TO_R(c_target);
        if (c_target.on_board() && c_target.x > c.x)
        {

            if (_infos[c_target.id()].piece == PieceType::EMPTY)
            {
                m.from = c;
                m.to = c_target;
                auto player = _infos[c.id()].color;
                m.info.src = PieceInfo(player, PieceType::CANNON, c);
                moves.push_back(m);
            }
            else
            {
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x < BOARD_WIDTH);

    // up
    c_target = c;
    do
    {
        c_target = TO_T(c_target);
        if (c_target.on_board() && c_target.y > c.y)
        {
            if (_infos[c_target.id()].piece == PieceType::EMPTY)
            {
                m.from = c;
                m.to = c_target;
                auto player = _infos[c.id()].color;
                m.info.src = PieceInfo(player, PieceType::CANNON, c);
                moves.push_back(m);
            }
            else
            {
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y < BOARD_HEIGHT);

    // down
    c_target = c;
    do
    {
        c_target = TO_B(c_target);
        if (c_target.on_board() && c_target.y < c.y)
        {
            if (_infos[c_target.id()].piece == PieceType::EMPTY)
            {
                m.from = c;
                m.to = c_target;
                auto player = _infos[c.id()].color;
                m.info.src = PieceInfo(player, PieceType::CANNON, c);
                moves.push_back(m);
            }
            else
            {
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y >= 0);

    // 吃子
    // 先找炮架，然后找目标
    Color enemy = OPPONENT(_infos[c.id()].color);
    Coord target;

    // left
    c_target = c;
    bool found = false;
    do
    {
        c_target = TO_L(c_target);
        if (c_target.on_board() && c_target.x < c.x)
        {
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                found = true;
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x >= 0);

    if (found)
    {
        target = c_target;
        do
        {
            target = TO_L(target);
            if (target.on_board() && target.x < c_target.x)
            {
                // 首先出现我方棋子，退出
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == OPPONENT(enemy))
                {
                    break;
                }
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == enemy)
                {
                    m.from = c;
                    m.to = target;

                    auto player = _infos[c.id()].color;
                    m.info.src = PieceInfo(player, PieceType::CANNON, c);
                    m.info.tgt = _infos[target.id()];
                    moves.push_back(m);
                    break;
                }
            }
        } while (target.y == c_target.y && target.x >= 0);
    }

    // 右
    c_target = c;
    found = false;
    do
    {
        c_target = TO_R(c_target);
        if (c_target.on_board() && c_target.x > c.x)
        {
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                found = true;
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x < BOARD_WIDTH);

    if (found)
    {
        target = c_target;
        do
        {
            target = TO_R(target);
            if (target.on_board() && target.x > c_target.x)
            {
                // 首先出现我方棋子，退出
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == OPPONENT(enemy))
                {
                    break;
                }
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == enemy)
                {
                    m.from = c;
                    m.to = target;

                    auto player = _infos[c.id()].color;
                    m.info.src = PieceInfo(player, PieceType::CANNON, c);
                    m.info.tgt = _infos[target.id()];
                    moves.push_back(m);
                    break;
                }
            }
        } while (target.y == c_target.y && target.x < BOARD_WIDTH);
    }

    // 上
    c_target = c;
    found = false;
    do
    {
        c_target = TO_T(c_target);
        if (c_target.on_board() && c_target.y > c.y)
        {
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                found = true;
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y < BOARD_HEIGHT);

    if (found)
    {
        target = c_target;
        do
        {
            target = TO_T(target);
            if (target.on_board() && target.y > c_target.y)
            {
                // 首先出现我方棋子，退出
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == OPPONENT(enemy))
                {
                    break;
                }
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == enemy)
                {
                    m.from = c;
                    m.to = target;

                    auto player = _infos[c.id()].color;
                    m.info.src = PieceInfo(player, PieceType::CANNON, c);
                    m.info.tgt = _infos[target.id()];
                    moves.push_back(m);
                    break;
                }
            }
        } while (target.x == c_target.x && target.y < BOARD_HEIGHT);
    }

    // 下
    c_target = c;
    found = false;
    do
    {
        c_target = TO_B(c_target);
        if (c_target.on_board() && c_target.y < c.y)
        {
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                found = true;
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y >= 0);

    if (found)
    {
        target = c_target;
        do
        {
            target = TO_B(target);
            if (target.on_board() && target.y < c_target.y)
            {
                // 首先出现我方棋子，退出
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == OPPONENT(enemy))
                {
                    break;
                }
                if (_infos[target.id()].piece != PieceType::EMPTY && _infos[target.id()].color == enemy)
                {
                    m.from = c;
                    m.to = target;

                    auto player = _infos[c.id()].color;
                    m.info.src = PieceInfo(player, PieceType::CANNON, c);
                    m.info.tgt = _infos[target.id()];
                    moves.push_back(m);
                    break;
                }
            }
        } while (target.x == c_target.x && target.y >= 0);
    }
}

void Board::add_rook_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    Coord c_target;

    // left
    c_target = c;
    do
    {
        c_target = TO_L(c_target);
        if (c_target.on_board() && c_target.x < c.x)
        {
            // std::cout << "开始位置(" << c.x << c.y << ")左移=>"
            //           << "x = " << c_target.x << " y = " << c_target.y << std::endl;

            m.from = c;
            m.to = c_target;

            m.info.src.piece = PieceType::ROOK;

            auto player = _infos[c.id()].color;
            m.info.src = PieceInfo(player, PieceType::ROOK, c);

            if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
            {
                m.info.tgt = _infos[c_target.id()];
                moves.push_back(m);
            }
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x >= 0);

    // right
    c_target = c;
    do
    {
        c_target = TO_R(c_target);
        if (c_target.on_board() && c_target.x > c.x)
        {
            // std::cout << "开始位置(" << c.x << c.y << ")右移=>"
            //           << "x = " << c_target.x << " y = " << c_target.y << std::endl;

            m.from = c;
            m.to = c_target;

            auto player = _infos[c.id()].color;
            m.info.src = PieceInfo(player, PieceType::ROOK, c);

            if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
            {
                m.info.tgt = _infos[c_target.id()];
                moves.push_back(m);
            }
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                break;
            }
        }
    } while (c_target.y == c.y && c_target.x < BOARD_WIDTH);

    // up
    c_target = c;
    do
    {
        c_target = TO_T(c_target);
        if (c_target.on_board() && c_target.y > c.y)
        {
            // std::cout << "开始位置(" << c.x << c.y << ")上移=>"
            //           << "x = " << c_target.x << " y = " << c_target.y << std::endl;

            m.from = c;
            m.to = c_target;

            auto player = _infos[c.id()].color;
            m.info.src = PieceInfo(player, PieceType::ROOK, c);

            if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
            {
                m.info.tgt = _infos[c_target.id()];
                moves.push_back(m);
            }
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y < BOARD_HEIGHT);

    // down
    c_target = c;
    do
    {
        c_target = TO_B(c_target);
        if (c_target.on_board() && c_target.y < c.y)
        {

            m.from = c;
            m.to = c_target;

            auto player = _infos[c.id()].color;
            m.info.src = PieceInfo(player, PieceType::ROOK, c);

            if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
            {
                m.info.tgt = _infos[c_target.id()];
                moves.push_back(m);
            }
            if (_infos[c_target.id()].piece != PieceType::EMPTY)
            {
                break;
            }
        }
    } while (c_target.x == c.x && c_target.y >= 0);
}

void Board::add_red_pawn_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;

    auto y = c.y;
    FOR3RP(c, i, c_target)
    {
        // 未过河不得横向移动
        if (y <= 4 && abs(RP[i][0]) == 1)
        {
            continue;
        }
        // 目标区域有效
        auto d = deltaXY(c, c_target);
        // abs(delta_x) + abs(delta_y) = 1
        if (abs(d.first) + abs(d.second) == 1 && c_target.on_board())
        {
            if (c_target.y >= 5 || ((c_target.x % 2 == 0 && c_target.y == 3) || (c_target.x % 2 == 0 && c_target.y == 4)))
            {

                m.from = c;
                m.to = c_target;

                m.info.src = PieceInfo(S_RED, PieceType::PAWN, c);

                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFOR3RP
}

void Board::add_black_pawn_moves(const Coord &c, moveVec_t &moves) const
{
    Move m;
    auto y = c.y;
    FOR3BP(c, i, c_target)
    {
        // 未过河不得横向移动
        if (y > 6 && abs(RP[i][0]) == 1)
        {
            continue;
        }
        // 目标区域有效
        auto d = deltaXY(c, c_target);

        // abs(delta_x) + abs(delta_y) = 1
        if (abs(d.first) + abs(d.second) == 1 && c_target.on_board())
        {
            if (c_target.y <= 4 || ((c_target.x % 2 == 0 && c_target.y == 5) || (c_target.x % 2 == 0 && c_target.y == 6)))
            {
                m.from = c;
                m.to = c_target;

                m.info.src = PieceInfo(S_BLACK, PieceType::PAWN, c);

                if (!_infos[c.id()].IsFriend(_infos[c_target.id()]))
                {
                    m.info.tgt = _infos[c_target.id()];
                    moves.push_back(m);
                }
            }
        }
    }
    ENDFOR3BP
}

void Board::add_cand_factory(const PieceInfo &p, moveVec_t &moves) const
{
    if (p.piece == PieceType::KING)
    {
        if (p.color == S_RED)
        {
            add_red_king_moves(p.coord, moves);
        }
        else
        {
            add_black_king_moves(p.coord, moves);
        }
    }
    else if (p.piece == PieceType::GUARD)
    {
        if (p.color == S_RED)
        {
            add_red_guard_moves(p.coord, moves);
        }
        else
        {
            add_black_guard_moves(p.coord, moves);
        }
    }
    else if (p.piece == PieceType::ELEPHANT)
    {
        if (p.color == S_RED)
        {
            add_red_elephant_moves(p.coord, moves);
        }
        else
        {
            add_black_elephant_moves(p.coord, moves);
        }
    }
    else if (p.piece == PieceType::PAWN)
    {
        if (p.color == S_RED)
        {
            add_red_pawn_moves(p.coord, moves);
        }
        else
        {
            add_black_pawn_moves(p.coord, moves);
        }
    }
    else if (p.piece == PieceType::CANNON)
    {
        add_cannon_moves(p.coord, moves);
    }
    else if (p.piece == PieceType::HORSE)
    {
        add_horse_moves(p.coord, moves);
    }
    else if (p.piece == PieceType::ROOK)
    {
        add_rook_moves(p.coord, moves);
    }
}

moveVec_t Board::GetCandidates(const Color &player) const
{
    moveVec_t moves = _Candidates(player);
    auto ememy = OPPONENT(player);
    auto king_coord = GetCoordOfKing(ememy);
    // 生成将军信息
    if (!this->IsCheck(player))
    {
        for (auto &m : moves)
        {
            _gen_jj_info(player, m, king_coord);
        }
    }
    std::stable_sort(moves.begin(), moves.end());
    return moves;
}

moveVec_t Board::GetCandidatesForTargetEat(const Coord &tgt, bool exclude) const
{
    moveVec_t cands, res;
    auto info = _infos[tgt.id()];
    if (info.IsEmpty())
    {
        return res;
    }
    auto player = OPPONENT(info.color);
    cands = GetCandidatesForEat(player, exclude);
    for (auto &move : cands)
    {
        if (move.to == tgt)
        {
            res.push_back(move);
        }
    }
    return res;
}

moveVec_t Board::CandidatesForEatFrom(const Color &player, const Coord start) const
{
    moveVec_t res;
    auto cands = GetCandidates(player);
    if (start.on_board())
    {
        for (auto &move : cands)
        {
            if (move.from == start &&
                !_infos[move.to.id()].IsEmpty() &&
                _infos[move.to.id()].piece != PieceType::KING)
            {
                res.push_back(move);
            }
        }
    }
    else
    {
        for (auto &move : cands)
        {
            if (!_infos[move.to.id()].IsEmpty() &&
                _infos[move.to.id()].piece != PieceType::KING)
            {
                res.push_back(move);
            }
        }
    }
    return res;
}

moveVec_t Board::GetCandidatesForEatNoRoot(const Color &player, const Coord start) const
{
    moveVec_t res;
    auto cands = GetCandidatesByPlayer(player, true);
    if (start.on_board())
    {
        for (auto &move : cands)
        {
            if (move.from == start &&
                !HasRootProtected(move) &&
                !_infos[move.to.id()].IsEmpty() &&
                _infos[move.to.id()].piece != PieceType::KING)
            {
                res.push_back(move);
            }
        }
    }
    else
    {
        for (auto &move : cands)
        {
            if (!HasRootProtected(move) &&
                !_infos[move.to.id()].IsEmpty() &&
                _infos[move.to.id()].piece != PieceType::KING)
            {
                res.push_back(move);
            }
        }
    }
    return res;
}

bool Board::is_game_ended() const
{
    return _result != NO_RESULT;
}

int Board::final_result() const
{
    return _result;
}

void Board::_do_move(const Move &move)
{
    auto src = this->_infos[move.from.id()];
    // 走子
    set_pieces(move.from, S_EMPTY, PieceType::EMPTY);
    set_pieces(move.to, src.color, src.piece);
}

void Board::_simple_move(Move &move)
{
    if (this->_result != 2)
    {
        on_board_error(fmt::format("执行移动{}，但游戏已经结束", move));
    }
    auto src = this->_infos[move.from.id()];
    auto tgt = this->_infos[move.to.id()];

    auto msg = fmt::format("移动({})，轮到{}方走子，提子为{}方(_simple_move)",
                           move,
                           color_cn_name(_next_player),
                           color_cn_name(src.color));

    if (src.color != _next_player)
    {
        on_board_error(msg);
    }

    move.info.src = src;
    move.info.tgt = tgt;

    // 保存盘面连续未吃子计数
    move.info.preNoEat = this->_no_eat;

    // 方便处理初始hash
    this->_ply += 1;
    // 走子
    set_pieces(move.from, S_EMPTY, PieceType::EMPTY);
    set_pieces(move.to, src.color, src.piece);

    _gen_jj_info(src.color, move);

    // 被吃掉将或帅
    if (tgt.piece == PieceType::KING)
    {
        _reason = B_FinishReason::FR_EATED;
        _result = tgt.color == S_RED ? RED_LOSE : RED_WIN;
        _s_reason = fmt::format("{}{}被吃", _result == RED_WIN ? "黑方" : "红方", getCNSymbol(tgt.piece, tgt.color));
    }

    this->_next_player = OPPONENT(src.color);

    // 保留历史 hash
    _hash_keys.push_back(_hash);

    // 与将军有关
    // 由第一着开始，凡双方共走120步仍未有去子记录者，不论局势如何，均作为和局。
    // 在一局棋内“将军”最多只计十步
    // TODO:单独再计算将军???
    // 目标为空，累加连续未吃子计数；否则清0
    if (tgt.piece == PieceType::EMPTY)
    {
        this->_no_eat += 1;
    }
    else
    {
        this->_no_eat = 0;
    }
}

void Board::on_repeat(size_t t, size_t times)
{
    // 模拟时重复一次即判闲
    // 走前局面重复，走后与上一周期的移动相同，则为重复
    if (is_multi_repetitive(t, times))
    {
        // 修改为判和
        this->_result = DRAW;
        this->_reason = B_FinishReason::FR_MAX_REPEATION;
        this->_s_reason = fmt::format("模拟时{}{}次重复", _next_player == S_RED ? "黑方" : "红方", times);
    }
}

void Board::DoMove(Move &move)
{
    _simple_move(move);

    // 更新历史记录
    _moves_history.push_back(move);

    // 游戏结果
    _ruling();
}

void Board::SimulateMove(Move &move)
{
    DoMove(move);
    // 移动后计算重复周期
    auto t = repetition_size();
    if (is_multi_repetitive(t, 1))
    {
        on_repeat(t, 1);
    }
}

void Board::undo_simple_move(const Move &move)
{
    // 恢复
    set_pieces(move.from, move.info.src.color, move.info.src.piece);
    set_pieces(move.to, move.info.tgt.color, move.info.tgt.piece);

    this->_next_player = move.info.src.color;
    this->_ply -= 1;
    // 自`移动`存储的信息中恢复连续未吃子数
    this->_no_eat = move.info.preNoEat;
    this->_result = NO_RESULT;
    // 在历史记录中移除最后移动
    _moves_history.pop_back();
    _hash_keys.pop_back();
}

void Board::undoMove()
{
    if (_ply <= 1)
    {
        throw std::runtime_error("已经回退到初始位置!");
    }
    const auto move = get_last_move();
    undo_simple_move(move);
}

void Board::undoNSteps(const int n)
{
    if (n > static_cast<int>(_ply - 1))
    {
        auto msg = fmt::format("计划回退{}步，但移动历史长度为{}！", n, _ply - 1);
        throw std::runtime_error(msg);
    }
    for (int i = 0; i < n; i++)
    {
        undoMove();
    }
}

Coord Board::GetCoordOfKing(const Color &s) const
{
    if (s == S_RED)
    {
        for (size_t x = 3; x <= 5; x++)
        {
            for (size_t y = 0; y <= 2; y++)
            {
                auto c = Coord(x, y);
                if (this->_infos[c.id()].color == s && this->_infos[c.id()].piece == PieceType::KING)
                {
                    return c;
                }
            }
        }
    }
    else if (s == S_BLACK)
    {
        for (size_t x = 3; x <= 5; x++)
        {
            for (size_t y = 7; y <= 9; y++)
            {
                auto c = Coord(x, y);
                if (this->_infos[c.id()].color == s && this->_infos[c.id()].piece == PieceType::KING)
                {
                    return c;
                }
            }
        }
    }
    return Coord(90);
}

bool Board::IsFace2Face()
{
    auto red = GetCoordOfKing(S_RED);
    auto black = GetCoordOfKing(S_BLACK);
    if (red == Coord(90) || black == Coord(90))
    {
        return false;
    }
    if (red.x != black.x)
    {
        return false;
    }
    Coord c;
    auto x = red.x;
    for (int y = red.y + 1; y < black.y; y++)
    {
        c = Coord(x, y);
        if (!this->_infos[c.id()].IsEmpty())
        {
            return false;
        }
    }
    return true;
}

bool Board::IsCheck(const Color &player) const
{
    assert(!EMPTY(player));
    auto ememy = OPPONENT(player);
    auto king_coord = GetCoordOfKing(ememy);
    if (king_coord.off_board())
    {
        return false;
    }
    // 避免陷入死循环
    auto cands = _Candidates(player);
    for (const auto &m : cands)
    {
        if (m.to == king_coord)
        {
            return true;
        }
    }
    return false;
}

int Board::GetPiecesInfo(const Coord &coord) const
{
    auto p = this->_infos[coord.id()].piece;
    switch (p)
    {
    case PieceType::KING:
        return KING_VALUE;
        break;
    case PieceType::GUARD:
        return WEAK_VALUE;
        break;
    case PieceType::ELEPHANT:
        return WEAK_VALUE;
        break;
    case PieceType::HORSE:
        return STRONG_VALUE;
        break;
    case PieceType::ROOK:
        return 2 * STRONG_VALUE;
        break;
    case PieceType::CANNON:
        return STRONG_VALUE;
        break;
    case PieceType::PAWN:
        // 过河才计算子力
        // 过河价值 = 马或炮
        if (IsCrossRiverPawn(coord))
        {
            return STRONG_VALUE;
        }
        else
        {
            return 0;
        }
        break;
    default:
        return 0;
        break;
    }
}

GamePieceCount Board::GetPiecesInfo() const
{
    PieceCount red;
    PieceCount black;
    for (size_t i = 0; i < NUM_INTERSECTION; i++)
    {
        Coord coord(i);
        auto p = this->_infos[i].piece;
        auto c = this->_infos[i].color;
        if (c == S_RED)
        {
            switch (p)
            {
            case PieceType::KING:
                break;
            case PieceType::GUARD:
                red.weak += 1;
                break;
            case PieceType::ELEPHANT:
                red.weak += 1;
                break;
            case PieceType::HORSE:
                red.value += STRONG_VALUE;
                red.strong += 1;
                break;
            case PieceType::ROOK:
                red.value += 2 * STRONG_VALUE;
                red.strong += 1;
                break;
            case PieceType::CANNON:
                red.value += STRONG_VALUE;
                red.strong += 1;
                break;
            case PieceType::PAWN:
                if (coord.y > 4)
                {
                    red.pawn_cross_river += 1;
                }
                else
                {
                    red.pawn_not_cross += 1;
                }
                break;
            default:
                break;
            }
        }
        else if (c == S_BLACK)
        {
            switch (p)
            {
            case PieceType::KING:
                break;
            case PieceType::GUARD:
                black.weak += 1;
                break;
            case PieceType::ELEPHANT:
                black.weak += 1;
                break;
            case PieceType::HORSE:
                black.value += STRONG_VALUE;
                black.strong += 1;
                break;
            case PieceType::ROOK:
                black.value += 2 * STRONG_VALUE;
                black.strong += 1;
                break;
            case PieceType::CANNON:
                black.value += STRONG_VALUE;
                black.strong += 1;
                break;
            case PieceType::PAWN:
                // 过河才计算子力
                if (coord.y < 5)
                {
                    black.pawn_cross_river += 1;
                }
                else
                {
                    black.pawn_not_cross += 1;
                }
                break;
            default:
                break;
            }
        }
    }
    return {red, black};
}

PiecesValue Board::GetTotalValue()
{
    int red = 0;
    int black = 0;
    for (size_t i = 0; i < NUM_INTERSECTION; i++)
    {
        Coord coord(i);
        auto c = this->_infos[i].color;
        if (c == S_RED)
        {
            red += GetPiecesInfo(coord);
        }
        else if (c == S_BLACK)
        {
            black += GetPiecesInfo(coord);
        }
    }
    return {red, black};
}

bool Board::IsInsufficientMaterial()
{
    GamePieceCount v = GetPiecesInfo();
    return v.red.strong == 0 && v.red.pawn_not_cross == 0 && v.red.pawn_cross_river == 0 &&
           v.black.strong == 0 && v.black.pawn_not_cross == 0 && v.black.pawn_cross_river == 0;
}

bool Board::IsCheckmate(const Color &player)
{
    auto moves = GetCandidatesByPlayer(player, true);
    return moves.empty();
}

size_t Board::repetition_size() const
{
    // 计数从1开始，连续四着才可能重复。
    // 在局面重复的前提下，如
    if (_ply <= 5)
    {
        return 0;
    }
    auto last_hash = _hash;
    bool found = false;
    size_t found_counter = 0;
    size_t back = 0;
    for (auto it = _hash_keys.rbegin(); it != _hash_keys.rend(); it++)
    {
        if (last_hash == *it)
        {
            found_counter += 1;
        }
        if (found_counter == 2)
        {
            found = true;
            break;
        }
        // 单个循环最多9个回合
        if (back == NUM_OF_HISTORY)
        {
            break;
        }
        back += 1;
    }
    if (found)
    {
        return back;
    }
    return 0;
}

bool Board::is_multi_repetitive(size_t t, size_t times) const
{
    if (_moves_history.size() < t * times || t == 0)
    {
        return false;
    }
    auto b2 = this->clone();
    for (size_t i = 0; i < times; i++)
    {
        b2.undoNSteps(t);
        if (b2.hash() != this->_hash)
        {
            return false;
            break;
        }
    }
    return true;
}

void Board::_ruling()
{
    // 游戏已经结束
    if (_result != NO_RESULT)
    {
        return;
    }
    // 走后形成将帅照面，当前走子方输
    if (IsFace2Face())
    {
        _reason = B_FinishReason::FR_FF;
        this->_result = this->_next_player == S_RED ? RED_WIN : RED_LOSE;
        _s_reason = fmt::format("{}走子后形成将帅照面", _result == RED_WIN ? "黑方" : "红方");
        return;
    }
    // 双方无力进攻，判和
    if (IsInsufficientMaterial())
    {
        _reason = B_FinishReason::FR_NO_POWER;
        this->_result = DRAW;
        _s_reason = "双方无力进攻";
        return;
    }
    // 被对手将死
    if (IsCheckmate(this->_next_player))
    {
        // show_board(true, "将死");
        _reason = B_FinishReason::FR_END;
        this->_result = this->_next_player == S_RED ? RED_LOSE : RED_WIN;
        _s_reason = fmt::format("{}被将死", _result == RED_WIN ? "黑方" : "红方");
        // logger_->info(_result == RED_WIN ? "黑方被将死" : "红方被将死");
        return;
    }
    // 连续未吃子，判和
    if (this->_no_eat >= MAX_MOVE_NO_EAT)
    {
        _reason = B_FinishReason::FR_MAX_NO_EAT;
        this->_result = DRAW;
        _s_reason = "连续120步未吃子";
        return;
    }
    // // 未应将判负
    // if (_ply >= 3)
    // {
    //     auto current_player = OPPONENT(this->_next_player);
    //     auto prev = get_previous_move();
    //     if (prev.is_check() && IsCheck(OPPONENT(current_player)))
    //     {
    //         this->_reason = B_FinishReason::FR_NO_REPLY;
    //         this->_result = current_player == S_RED ? RED_LOSE : RED_WIN;
    //         this->_s_reason = fmt::format("{}未应将", current_player == S_RED ? "红方" : "黑方");
    //         return;
    //     }
    // }
}

moveVec_t Board::_Candidates(const Color &player) const
{
    moveVec_t moves;
    auto pcs = find_PCs(player);
    for (size_t i = 0; i < pcs.size(); i++)
    {
        add_cand_factory(pcs[i], moves);
    }
    return moves;
}

void Board::_gen_jj_info(const Color &player, Move &before_move, Coord king_coord) const
{
    auto b = this->clone();
    b.SetPlayer(player);
    b._do_move(before_move);
    if (b.IsCheck(player))
    {
        auto cands = b._Candidates(player);
        for (auto m : cands)
        {
            if (m.to == king_coord)
            {
                before_move.info.jj_after_moved.push_back(m.info.src);
            }
        }
    }
}

void Board::_gen_jj_info(const Color &player, Move &moved) const
{
    auto ememy = OPPONENT(player);
    auto king_coord = this->GetCoordOfKing(ememy);
    if (this->IsCheck(player))
    {
        auto cands = this->_Candidates(player);
        for (auto m : cands)
        {
            if (m.to == king_coord)
            {
                moved.info.jj_after_moved.push_back(m.info.src);
            }
        }
    }
    else
    {
        moved.info.jj_after_moved.clear();
    }
}

void Board::_set_no_eat_num(int t)
{
    this->_no_eat = static_cast<size_t>(t);
}

void Board::_set_steps(int t)
{
    this->_ply = static_cast<size_t>(t);
}

bool Board::immediately_loss_once_moved(Move &move) const
{
    // 使用克隆避免递归调用
    Board b1 = this->clone();
    auto player = b1._infos[move.from.id()].color;
    // this->show_board(true, move.toString());
    assertm(!EMPTY(player), "必须指定玩家，不得为空");
    b1.SetPlayer(player);
    // 不得使用`simpleMove`
    b1._simple_move(move);
    auto opponent = OPPONENT(player);
    auto cands = b1.GetCandidatesForCheck(opponent);
    for (auto &m : cands)
    {
        auto b2 = b1.clone();
        b2._simple_move(m);
        if (b2.IsCheckmate(player))
        {
            return true;
        }
    }
    return false;
}

Move Board::get_one_step_kill_move() const
{
    auto player = this->next_player();
    auto ememy = OPPONENT(player);
    auto king_coord = this->GetCoordOfKing(ememy);
    // 首先检查是否可以直接吃将、帅
    auto cands = GetCandidates(player);
    for (auto &m : cands)
    {
        // 当可直接吃将、帅时，也算一步杀
        if (m.to == king_coord)
        {
            return m;
        }
    }
    // 然后检查一步棋是否可以将死对方
    cands = GetCandidatesForCheck(player);
    for (auto &m : cands)
    {
        auto b2 = this->clone();
        b2._simple_move(m);
        if (b2.IsCheckmate(OPPONENT(player)))
        {
            return m;
        }
    }
    return EMPTY_MOVE;
}

moveVec_t Board::GetCandidatesByPlayer(const Color &player, bool exclude) const
{
    moveVec_t res;
    auto oppo = OPPONENT(player);
    auto cands = GetCandidates(player);
    if (!exclude)
    {
        return cands;
    }
    for (auto &move : cands)
    {
        auto b2 = this->clone();
        b2.SetPlayer(player);
        // b2.clear_history();
        b2._do_move(move);
        // b2.show_board(true, "测试");
        // 只要走后不形成照脸或依然被对方将军
        if (b2.IsCheck(oppo) || b2.IsFace2Face())
        // if (b2.IsCheck(move, oppo) || b2.IsFace2Face())
        {
            continue;
        }
        res.push_back(move);
    }
    return res;
}

std::vector<int> Board::legal_ations() const
{
    std::vector<int> res;
    Color player = next_player();
    auto moves = GetCandidatesByPlayer(player);
    for (auto &m : moves)
    {
        res.push_back(M2I.at(m.toString()));
    }
    return res;
}

std::vector<int> Board::eat_actions() const
{
    std::vector<int> res;
    Color player = next_player();
    auto moves = GetCandidatesForEat(player);
    for (auto &m : moves)
    {
        res.push_back(M2I.at(m.toString()));
    }
    return res;
}

moveVec_t Board::GetCandidatesFrom(const Coord &start, bool exclude) const
{
    moveVec_t res, cands;
    auto player = _infos[start.id()].color;
    cands = GetCandidatesByPlayer(player, exclude);
    for (auto &move : cands)
    {
        if (move.from == start)
        {
            res.push_back(move);
        }
    }
    return res;
}

moveVec_t Board::GetCandidatesForCheck(const Color &player, const Coord start) const
{
    moveVec_t res;
    auto b2 = this->clone();
    b2.SetPlayer(player);
    auto cands = b2.GetCandidatesByPlayer(player);
    if (start.on_board())
    {
        for (auto move : cands)
        {
            if (move.is_check() && move.from == start)
            {
                res.push_back(move);
            }
        }
    }
    else
    {
        for (auto move : cands)
        {
            if (move.is_check())
            {
                res.push_back(move);
            }
        }
    }
    return res;
}

moveVec_t Board::GetCandidatesForEat(const Color &player, bool exclude) const
{
    moveVec_t cands, eats;
    cands = GetCandidatesByPlayer(player, exclude);
    for (auto &move : cands)
    {
        if (move.is_eat())
        {
            eats.push_back(move);
        }
    }
    std::stable_sort(eats.begin(), eats.end(), [](const Move &a, const Move &b)
                     { return get_piece_value(a.info.tgt) > get_piece_value(b.info.tgt); });

    return eats;
}

// moveVec_t Board::GetCandidatesForEat(const Color &player, const Coord exclude) const
// {
//     moveVec_t res;
//     auto cands = GetCandidatesByPlayer(player);
//     for (auto &move : cands)
//     {
//         // if (!move.info.tgt.IsEmpty() &&
//         //     _infos[move.to.id()].piece != PieceType::KING)
//         if (!move.info.tgt.IsEmpty())
//         {
//             if (exclude.on_board() && move.from == exclude)
//             {
//                 continue;
//             }
//             res.push_back(move);
//         }
//     }
//     return res;
// }

bool Board::tryMove(const Move &move)
{
    if (!move.IsValid())
    {
        return false;
    }
    if (is_game_ended())
    {
        return false;
    }
    if (_next_player != _infos[move.from.id()].color)
    {
        return false;
    }
    if (_infos[move.from.id()].IsEmpty())
    {
        return false;
    }
    auto player = _infos[move.from.id()].color;
    auto valid_moves = GetCandidatesByPlayer(player);
    return contains(valid_moves, move);
}

bool Board::NotCrossRiverPawn(const Coord &c) const
{
    auto piece = _infos[c.id()].piece;
    auto color = _infos[c.id()].color;
    if (piece != PieceType::PAWN)
    {
        return false;
    }
    if (color == S_RED)
    {
        if ((c.x % 2 == 0) && (c.y >= 3 && c.y <= 4))
        {
            return true;
        }
    }
    else
    {
        if ((c.x % 2 == 0) && (c.y >= 5 && c.y <= 6))
        {
            return true;
        }
    }
    return false;
}

bool Board::IsCrossRiverPawn(const Coord &c) const
{
    auto piece = _infos[c.id()].piece;
    auto color = _infos[c.id()].color;
    if (piece != PieceType::PAWN)
    {
        return false;
    }
    if (color == S_RED)
    {
        if (c.y > 4)
        {
            return true;
        }
    }
    else
    {
        if (c.y < 5)
        {
            return true;
        }
    }
    return false;
}

bool Board::HasRootProtected(const Coord &src, const Coord &tgt) const
{
    Board b2 = this->clone();
    auto src_info = b2._infos[src.id()];
    auto tgt_info = b2._infos[tgt.id()];
    if (src_info.IsEmpty() || tgt_info.IsEmpty())
    {
        return false;
    }
    auto color = tgt_info.color;
    auto piece = tgt_info.piece;
    b2.set_pieces(tgt, OPPONENT(color), piece, false);
    b2.SetPlayer(color);
    auto cands = b2.GetCandidatesForTargetEat(tgt, true);
    for (auto &m : cands)
    {
        if (m.from == src)
        {
            return true;
        }
    }
    return false;
}

bool Board::HasRootProtected(const Move &eat) const
{
    auto b2 = this->clone();
    // 关注的是所吃之子是否受到保护
    auto info = b2.pieces()[eat.to.id()];
    if (info.IsEmpty())
    {
        return false;
    }
    auto player = info.color;
    b2.SetPlayer(OPPONENT(player));
    auto m = eat;
    b2._simple_move(m);
    auto cands = b2.GetCandidatesByPlayer(player, true);
    return std::any_of(cands.begin(), cands.end(), [=](const Move &m)
                       { return m.to == eat.to; });
}

bool Board::HasRootProtected(const Coord &c) const
{
    Board b2 = this->clone();
    auto info = b2._infos[c.id()];
    if (info.IsEmpty())
    {
        return false;
    }
    auto player = info.color;
    auto piece = info.piece;
    auto cands = b2.GetCandidatesForTargetEat(c, true);
    if (cands.empty())
    {
        // NB：首先标记为对手棋子，然后进行判断
        b2.set_pieces(c, OPPONENT(player), piece);
        b2.SetPlayer(player);
        auto cands = b2.GetCandidatesByPlayer(player, true);
        return std::any_of(cands.begin(), cands.end(), [=](const Move &m)
                           { return m.to == c; });
    }
    else
    {
        std::set<Move> counter;
        for (auto m : cands)
        {
            Board b0 = this->clone();
            b0.SetPlayer(OPPONENT(player));
            b0._simple_move(m);
            auto eb = b0.GetCandidatesForTargetEat(m.to, true);
            for (auto e : eb)
            {
                counter.insert(e);
            }
        }
        return !counter.empty();
    }
}

bool Board::HasPiece(const PieceInfo &p) const
{
    auto info = this->_infos[p.coord.id()];
    return info.color == p.color && info.piece == p.piece;
}

bool Board::IsFakeRootProtected(const Coord &c) const
{
    // this->show_board();
    Board b2 = this->clone();
    auto info = b2._infos[c.id()];
    if (info.IsEmpty())
    {
        return false;
    }
    auto player = info.color;
    auto piece = info.piece;
    // NB：首先标记为对手棋子，然后进行判断
    b2.set_pieces(c, OPPONENT(player), piece);
    b2.SetPlayer(player);
    auto cands0 = b2.GetCandidatesByPlayer(player, false);
    auto cands1 = b2.GetCandidatesByPlayer(player, true);
    // 不考虑自杀可吃回
    auto c0 = std::any_of(cands0.begin(), cands0.end(), [=](const Move &m)
                          { return m.to == c; });
    // 但排除自杀后不能吃回
    auto c1 = std::all_of(cands1.begin(), cands1.end(), [=](const Move &m)
                          { return m.to != c; });
    return c0 && c1;
}

coordVec_t Board::RootProtectedCoords(const Coord &c) const
{
    coordVec_t res;
    Board b2 = this->clone();
    auto info = b2._infos[c.id()];
    if (info.IsEmpty())
    {
        return res;
    }
    auto player = info.color;
    auto piece = info.piece;
    // NB：首先标记为对手棋子，然后进行判断
    b2.set_pieces(c, OPPONENT(player), piece);
    b2.SetPlayer(player);
    auto cands = b2.GetCandidatesByPlayer(player, true);
    std::for_each(cands.begin(), cands.end(), [&res, c](const Move &m)
                  { if(m.is_eat() && m.to == c){res.push_back(m.from);}; });
    return res;
}

size_t Board::NumberOfAttacked(const Coord &c) const
{
    return GetCandidatesForTargetEat(c, false).size();
}

size_t Board::NumberOfProtected(const Coord &c) const
{
    Board b2 = this->clone();
    auto info = b2._infos[c.id()];
    if (info.IsEmpty())
    {
        return 0;
    }
    auto color = info.color;
    auto piece = info.piece;
    b2.set_pieces(c, OPPONENT(color), piece, false);
    b2.SetPlayer(color);
    // 不关心是否造成自杀的根保护
    auto cands = b2.GetCandidatesForTargetEat(c, false);
    return cands.size();
}

bool Board::BeingAttacked(const Coord &c) const
{
    Board b2 = this->clone();
    auto info = b2._infos[c.id()];
    if (info.IsEmpty())
    {
        return false;
    }
    // 不排除自杀
    auto cand = b2.GetCandidatesForTargetEat(c);
    if (!cand.empty())
    {
        return true;
    }
    return false;
}

bool Board::IsPinned(const Coord &c) const
{
    return BeingAttacked(c) && HasRootProtected(c);
}

std::string Board::get_move_history_string() const
{
    std::string history = "";
    for (const auto &m : _moves_history)
    {
        // history += fmt::format("{}{}{}{}", m.from.x, m.from.y, m.to.x, m.to.y);
        history += fmt::format("{}", m);
    }
    return history;
}

std::string Board::get_move_history_view_string() const
{
    std::string history;
    int i = 0;
    if (_first_player == S_BLACK)
    {
        i = 1;
        history += "    ";
    }
    for (const Move m : _moves_history)
    {
        if (i % 2 == 0)
        {
            history += fmt::format(fg(fmt::color::red), "{}", m.toString());
        }
        else
        {
            history += fmt::format(fg(fmt::color::sea_green), "-{}\n", m.toString());
        }
        i += 1;
    }
    return history;
}

std::string Board::get_fen_string(bool include_moves, bool simple, bool include_no_eat)
{
    std::string fen = "";
    std::string row;
    int e = 0;
    Coord c1;
    Color player;
    PieceType piece;
    for (size_t y = 0; y < BOARD_HEIGHT; y++)
    {
        e = 0;
        row = "";
        for (size_t x = 0; x < BOARD_WIDTH; x++)
        {
            c1 = Coord(x, 9 - y);
            player = this->_infos[c1.id()].color;
            piece = this->_infos[c1.id()].piece;
            if (piece == PieceType::EMPTY)
            {
                e += 1;
            }
            else
            {
                if (e > 0)
                {
                    row += std::to_string(e);
                    e = 0;
                }
                row += getSymbol(piece, player);
            }
        }
        if (e > 0)
        {
            row += std::to_string(e);
        }
        fen += row;
        if (y != 9)
        {
            fen += "/";
        }
    }
    std::string turn = this->_next_player == S_RED ? "r" : "b";
    auto half_num = this->_ply;
    std::string history = "-";
    std::string no_eat_str = "-";
    if (include_no_eat)
    {
        no_eat_str = fmt::format("{}", _no_eat);
    }
    auto full_num = (half_num - 1) / 2 + (half_num - 1) % 2;
    if (simple && !include_no_eat)
    {
        return fmt::format("{} {}", fen, turn);
    }
    if (include_moves)
    {
        history = get_move_history_string();
    }
    return fmt::format("{} {} {} {} {} {}", fen, turn, history, no_eat_str, full_num, half_num);
};
