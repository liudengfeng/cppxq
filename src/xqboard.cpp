#include "xqboard.hpp"

bool is_participated(const Coord &c, const moveVec_t &hist)
{
    for (size_t i = 0; i < hist.size(); i++)
    {
        if (i % 2 == 1)
        {
            continue;
        }
        if (hist[i].from == c)
        {
            return true;
        }
    }
    return false;
}

bool is_participated(const Move &m, const moveVec_t &hist)
{
    for (size_t i = 0; i < hist.size(); i++)
    {
        if (i % 2 == 1)
        {
            continue;
        }
        if (hist[i] == m)
        {
            return true;
        }
    }
    return false;
}

bool is_participated(const moveVec_t &related_eats, const moveVec_t &hist)
{
    for (auto m : related_eats)
    {
        if (m == hist[0])
        {
            return true;
        }
    }
    return false;
}

moveVec_t get_dui_path(const Move &m, const moveVec_t &path)
{
    // 兑子模拟路径可能出现不匹配
    // 验证path二项：
    // 1. 净收益为正
    // 2. 第一项棋子价值等于被兑子价值
    // assertm(get_net_gain(path) > 0 && get_piece_value(m.info.tgt) == get_piece_value(path.front().info.tgt),
    //         "兑子路径应当满足条件：1. 净收益为正；2. 第一项棋子价值等于被兑子价值");
    if (get_net_gain(path) > 0 && get_piece_value(m.info.tgt) == get_piece_value(path.front().info.tgt))
    {
        return {m, path.front()};
    }
    else
    {
        return {};
    }
}

bool is_pk_move(const Move &move)
{
    return move.info.src.piece == PieceType::KING ||
           move.info.src.piece == PieceType::PAWN;
}

Move get_pk_eat(const moveVec_t &hist)
{
    for (size_t i = 0; i < hist.size(); i++)
    {
        if (i % 2 == 1)
        {
            continue;
        }
        if (is_pk_move(hist[i]) && hist[i].is_eat())
        {
            return hist[i];
        }
    }
    return EMPTY_MOVE;
}

bool only_has_one_attack(const Board &board, Move &moved)
{
    auto player = OPPONENT(board.next_player());
    auto cands = board.GetCandidatesByPlayer(player, true);
    int num = 0;
    int v = 0;
    std::map<Coord, int> counter;
    for (auto m : cands)
    {
        v = get_piece_value(m.info.src);
        if (v >= STRONG_VALUE && v != KING_VALUE)
        {
            if (counter.count(m.from) == 0)
            {
                num += 1;
            }
            counter[m.from] = 1;
        }
    }
    return counter[moved.to] == 1 && num == 1;
}

bool is_xian(const Board &board, Move &moved, const moveVec_t &hist)
{
    auto t = hist.size();
    auto back = hist.back();
    auto prev = board.get_previous_move();
    // 2022 26.1.3 上一着将军，走动帅(将)应将直接判“闲”
    if (prev.is_check() && moved.info.src.piece == PieceType::KING)
    {
        return true;
    }
    auto player = OPPONENT(board.next_player());
    auto b0 = board.clone();
    b0.undoMove();
    if (is_pk_move(moved))
    {
        // 参考图图16-1 参考图图16-3
        // 避吃判捉，非闲
        if (is_avoid_eat(board, moved))
        {
            return false;
        }
        auto eats = board.GetCandidatesForEat(player, true);
        auto zhuo = t % 2 == 1 ? hist.back() : hist[t - 2];
        // 走动帅、兵捉，且没有其他棋子可捉同一目标 图14-1 图14-3
        // 26.1 帅(将)、兵(卒)本身允许长捉(见图14)。
        if (is_pk_move(zhuo) && std::none_of(eats.begin(), eats.end(), [=](const Move &e)
                                             { return e.to == zhuo.to && e != zhuo; }))
        {
            return true;
        }
    }
    else if (is_pk_move(hist.front()) || is_pk_move(hist.back()))
    {
        auto zhuo = get_pk_eat(hist);
        // 2022 26.1.2 帅(将)、兵(卒)与其他子配合的“捉”，如走动前并不存在，而是走动后新产生，且当前所动之子非帅(将)、兵(卒)，按“捉”处理(参考图16)
        if (zhuo.IsValid() && hist.front().info.is_jointed)
        {
            // 将军得子时
            if (hist.front().is_check())
            {
                // 2022 26.8 兵(卒)吃子时产生其他子“将军”，按“捉”处理
                if (zhuo.is_other_check())
                {
                    // 参考图图11-2
                    return false;
                }
                else
                {
                    // 参考图图13-3
                    return true;
                }
            }
            // 互吃子得子时
            else
            {
                // 此处需包含自杀行为
                auto eats0 = b0.GetCandidatesForEat(player, false);
                // 新产生的，判捉
                if (!contains(eats0, zhuo))
                {
                    return false;
                }
                else
                {
                    // 参考图图5-3 参考图图5-5 车配合兵捉象，并非新产生的，判闲
                    return true;
                }
            }
        }
    }
    // 26.2 守和方只有一个进攻子时，占据守和要点，附带产生的捉士象按“闲”处理(见图18-3、参考图19)。
    if (hist.size() % 2 == 1 &&
        (back.info.tgt.piece == PieceType::ELEPHANT || back.info.tgt.piece == PieceType::GUARD))
    {
        // 至少得有三步移动
        if (board.steps() < 4)
        {
            return false;
        }
        auto player = OPPONENT(board.next_player());
        // board.show_board(true, "一个进攻子");
        // 只有一个进攻子
        bool has_one_attack = only_has_one_attack(board, moved);
        if (!has_one_attack)
        {
            return false;
        }
        // 被对手杀
        auto b2 = board.clone();
        b2.undoNSteps(3);
        auto oppo = OPPONENT(player);
        b2.SetPlayer(oppo);
        // b2.show_board();
        ShaSimulator simulate(b2, oppo);
        if (simulate.IsTrue())
        {
            return true;
        }
    }
    return false;
}

std::vector<PieceType> _eats_before_move(const Board &board)
{
    std::vector<PieceType> eats;
    auto moved = board.get_last_move();
    auto b2 = board.clone();
    b2.undoMove();
    for (auto &m : b2.GetCandidatesFrom(moved.from))
    {
        // 限定无根子
        if (!m.info.tgt.IsEmpty() && !b2.HasRootProtected(m))
        {
            eats.push_back(m.info.tgt.piece);
        }
    }
    return eats;
}

std::vector<std::pair<PieceInfo, PieceInfo>> get_zhuo_objects(const moveVec_t &hist)
{
    std::vector<std::pair<PieceInfo, PieceInfo>> zhuoes;
    if (!hist.empty() && hist.size() <= 2)
    {
        zhuoes.emplace_back(hist[0].info.src, hist[0].info.tgt);
    }
    else
    {
        auto g = get_net_gain(hist);
        int total = 0;
        for (size_t i = 0; i < hist.size(); i++)
        {
            if (i % 2 == 1)
            {
                continue;
            }
            auto p = get_piece_value(hist[i].info.tgt);
            // 非空才添加
            if (p >= 1 && p <= g && total <= g)
            {
                zhuoes.emplace_back(hist[i].info.src, hist[i].info.tgt);
                total += p;
            }
            if (total >= g)
            {
                break;
            }
        }
    }
    return zhuoes;
}

moveVec_t ensure_zhuo_objects_before_moved(const Board &board, moveVec_t hist)
{
    // 为空或偶数长度，直接返回
    if (hist.empty() || hist.size() % 2 == 0)
    {
        return hist;
    }
    auto player = board.next_player();
    auto b0 = board.clone();
    b0.SetPlayer(player);
    for (auto m : hist)
    {
        b0.SimulateMove(m);
        if (b0.is_game_ended())
        {
            return {};
        }
    }
    // 如吃后被对手所杀，返回空列表
    ShaSimulator simulate(b0, OPPONENT(player));
    if (simulate.IsTrue())
    {
        return {};
    }
    return hist;
}

moveVec_t get_zhuo_objects_before_moved(const Board &board)
{
    auto player = OPPONENT(board.next_player());
    auto last = board.get_last_move();
    auto b0 = board.clone();
    b0.undoMove();
    // b0.show_board();
    // 检查原本可吃得子 如图05-1
    auto cands = b0.GetCandidatesForEat(player, true);
    std::set<Coord> tgts;
    for (auto e : cands)
    {
        if (e.from != last.from)
        {
            continue;
        }
        if (b0.NotCrossRiverPawn(e.to))
        {
            continue;
        }
        tgts.insert(e.to);
    }
    for (auto tgt : tgts)
    {
        ChiSimulator simulator(b0, player);
        simulator.set_target(tgt);
        if (simulator.IsTrue())
        {
            auto n = simulator.ReasonablePath();
            auto hist = ensure_zhuo_objects_before_moved(b0, n->history);
            if (!hist.empty())
            {
                return hist;
            }
        }
    }
    JdzSimulator simulator(b0, player);
    // 将军得子 如参考图06-1
    if (simulator.IsTrue())
    {
        auto n = simulator.ReasonablePath();
        // b0.show_board(true, fmt::format("最后一步：{} 路径={} v={}", last.toString(), n->history, get_net_gain(n->history)));
        return n->history;
    }
    return {};
}

bool _is_same_dz(const moveVec_t &before, const moveVec_t &after)
{
    return get_net_gain(before) == get_net_gain(after);
}

bool is_pk_zhuo(const Board &board, Move &moved, const moveVec_t &hist)
{
    if (is_pk_move(moved) || is_pk_move(hist.front()) || is_pk_move(hist.back()))
    {
        auto player = OPPONENT(board.next_player());
        auto eats = board.GetCandidatesForEat(player, true);
        auto b0 = board.clone();
        b0.undoMove();
        auto eats0 = b0.GetCandidatesForEat(player, true);
        auto tgt = hist.back().to;
        // 图 15-1 15-3 其他子也可捉路径中的对象
        // 检查是否为新增的捉
        // 26.1.1 走动帅(将)、兵(卒)后，其他子产生新的“捉”，按“捉”处理(见图15)。
        if (std::any_of(eats.begin(), eats.end(), [=](const Move &e)
                        { return e.to == tgt && e.from != hist.back().from && !contains(eats0, e); }))
        {
            return true;
        }
        // 26.1.1 走动帅(将)、兵(卒)后与其他子配合同时产生“捉”，按“捉”处理(参考图16)。
        if (is_pk_move(moved))
        {
            // 1. 走前收到攻击，走后没收到攻击
            // 2. 移动将帅后新增的，其他子可吃有价值的对象，即非帅、兵吃 参考图20-1
            if ((b0.BeingAttacked(moved.from) && !board.BeingAttacked(moved.to)) ||
                std::any_of(eats.begin(), eats.end(), [=](const Move &e)
                            { return !is_pk_move(e) && get_piece_value(e.info.tgt) >= WEAK_VALUE && !contains(eats0, e); }))
            {
                return true;
            }
        }
    }
    return false;
}

bool is_response_jj_xian(const Board &board, Move &moved, const moveVec_t &hist)
{
    if (board.steps() >= 3)
    {
        // 参考图22-4  红炮失去保护，是自己造成的被捉状态。黑车捉炮
        auto prev = board.get_last_moves(2);
        if (prev.front().is_check() && moved.info.src.piece != PieceType::KING)
        {
            auto player = OPPONENT(board.next_player());
            auto b0 = board.clone();
            auto eats = b0.GetCandidatesForEat(player, true);
            if (contains(eats, hist.front()))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (prev.front().is_check() && moved.info.src.piece == PieceType::KING)
        {
            return true;
        }
    }
    return false;
}

Move get_cut_root_eat(const Board &board)
{
    Move move = EMPTY_MOVE;
    // 当前走子方
    auto player = OPPONENT(board.next_player());
    auto after = board.GetCandidatesForEatNoRoot(player);
    if (after.empty())
    {
        return move;
    }
    auto b1 = board.clone();
    b1.undoMove();
    // b1.show_board();
    auto before = b1.GetCandidatesForEatNoRoot(player);

    // 候选移动为二者相交部分
    moveVec_t cands;
    std::set_intersection(after.begin(), after.end(), before.begin(), before.end(),
                          std::back_inserter(cands));

    // 验证：先吃掉无根子，模拟观察是否能被对手吃回
    for (auto &m : cands)
    {
        auto b2 = board.clone();
        b2.undoMove();
        try
        {
            // 吃无根子
            b2.DoMove(m);
            if (is_can_protected_last_eated(b2))
            {
                return m;
            }
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            continue;
        }
    }
    return move;
}

Coord get_common_attack(const Board &board, Move &moved)
{
    Coord tgt;
    std::map<Coord, size_t> counter;
    // 需要初始化
    counter[tgt] = 0;
    auto player = OPPONENT(board.next_player());
    auto eats = board.CandidatesForEatFrom(player, moved.to);
    // 统计吃目标受到的攻击数量
    for (auto m : eats)
    {
        // 排除未过河的兵、卒受攻击数量
        if (board.NotCrossRiverPawn(m.to))
        {
            continue;
        }
        auto eats_to = board.GetCandidatesForTargetEat(m.to);
        counter[m.to] = eats_to.size();
    }
    auto one = *std::max_element(counter.begin(), counter.end(), [](auto p1, auto p2)
                                 { return p1.second < p2.second; });
    if (one.second >= 2)
    {
        return one.first;
    }
    else
    {
        return tgt;
    }
}

void mark_xian_flag(Move &moved, bool &ended)
{
    moved.info.move_t = MoveType::XIAN;
    ended = true;
}

void mark_dui_flag(Move &moved, const Move &move)
{
    moved.info.dui_src = move.info.src;
    moved.info.dui_tgt = move.info.tgt;
}

void mark_sha_flag(const Board &board, Move &moved, bool &ended)
{
    // 26.1.2 走动帅(将)应将而产生的“捉”“杀”，按“闲”处理
    auto prev = board.get_previous_move();
    auto last = board.get_last_move();
    // 26.1.2 走动帅(将)应将而产生的“捉”“杀”，按“闲”处理；
    if (prev.is_check() && last.info.src.piece == PieceType::KING)
    {
        moved.info.move_t = MoveType::XIAN;
    }
    else
    {
        moved.info.move_t = MoveType::SHA;
    }
    ended = true;
}

void mark_zhuo_flag(const Board &board, Move &moved, bool &ended, const moveVec_t &hist)
{
    auto player = OPPONENT(board.next_player());
    if (is_xian(board, moved, hist))
    {
        mark_xian_flag(moved, ended);
    }
    else
    {
        moved.info.move_t = MoveType::ZHUO;
        // 剔除非必要的尾部兑
        auto trimed = get_trimed_tail_path(hist);
        moved.info.zhuo_src = trimed.front().info.src;
        moved.info.zhuo_tgt = trimed.back().info.tgt;
        // 首先使用模拟结果联合捉子属性
        moved.info.is_jointed = hist.front().info.is_jointed;

        // 第一项为吃车时的得子，只记录得车
        if (trimed.front().info.tgt.piece == PieceType::ROOK)
        {
            moved.info.zhuo_tgt = trimed.front().info.tgt;
            moved.info.no_root_protected = !board.HasRootProtected(trimed.front());
        }
        else
        {
            if (hist.size() % 2 == 0)
            {
                auto t = hist.size();
                auto zhuo = hist[t - 2];
                // 记录根保护信息
                moved.info.no_root_protected = !board.HasRootProtected(zhuo.to);
            }
            else
            {
                // 记录根保护信息
                // 如为有效吃
                auto eats = board.GetCandidatesForEat(player, true);
                if (contains(eats, trimed.back()))
                {
                    moved.info.no_root_protected = !board.HasRootProtected(trimed.back());
                }
                else
                {
                    moved.info.no_root_protected = !board.HasRootProtected(trimed.back().to);
                }
            }
        }
        ended = true;
    }
}

moveVec_t _simulate_cdz(const Board &board, const Color &player,
                        const Move &dui, const Coord &tgt)
{
    ChiSimulator simulator(board, player);
    simulator.set_not_allowed(dui);
    simulator.set_target(tgt);
    auto n = simulator.ReasonablePath();
    if (simulator.IsTrue())
    {
        return n->history;
    }
    return {};
}

bool is_can_protected_last_eated(const Board &board)
{
    // board.show_board(true, "is_can_protected_last_eated");
    auto player = board.next_player();
    auto last = board.get_last_move();
    JdzSimulator simulator(board, player);
    // 单纯杀没有被判定为得子
    if (simulator.IsTrue())
    {
        auto n = simulator.ReasonablePath();
        // n->print(player);
        if (!n->history.empty() && n->history.back().to == last.to)
        {
            return true;
        }
    }
    return false;
}

bool is_be_killed(const Board &board, const Color &player, Move eat)
{
    auto b0 = board.clone();
    b0.undoMove();
    auto eats = b0.GetCandidatesForEat(player, true);
    // 1. 当回退一步被对手将军，不算避杀
    // 2. 吃无效时
    if (b0.IsCheck(OPPONENT(player)) || !contains(eats, eat))
    {
        return false;
    }
    b0.SetPlayer(player);
    b0.DoMove(eat);
    ShaSimulator simulator(b0, OPPONENT(player));
    return simulator.IsTrue();
}

bool is_jj_related(const Board &board, Move &moved, const moveVec_t &hist, const moveVec_t &cands)
{
    auto zhuo = hist.front();
    // 如果走子避吃，无需再检查同样得子
    // 避吃
    if (is_avoid_eat(board, moved))
    {
        // fmt::print("避吃 {}\n", hist);
        return true;
    }
    auto b0 = board.clone();
    b0.undoMove();
    // 当移动后使得捉子第一步可直接吃而不被吃回 参考图图12-4
    auto player = OPPONENT(board.next_player());
    auto cands0 = b0.GetCandidatesByPlayer(player, true);
    if (contains(cands0, zhuo) && contains(cands, zhuo))
    {
        b0.SetPlayer(player);
        b0.SimulateMove(zhuo);
        auto cands0 = b0.GetCandidatesByPlayer(OPPONENT(player), true);

        auto b1 = board.clone();
        b1.SetPlayer(player);
        b1.SimulateMove(zhuo);
        auto cands1 = b1.GetCandidatesByPlayer(OPPONENT(player), true);

        // 此前可吃回、移动后不可吃回
        if (std::any_of(cands0.begin(), cands0.end(), [=](const Move &m)
                        { return m.to == zhuo.to; }) &&
            std::none_of(cands1.begin(), cands1.end(), [=](const Move &m)
                         { return m.to == zhuo.to; }))
        {
            // fmt::print("可吃 {}\n", hist);
            return true;
        }
    }
    return false;
}

bool is_avoid_eat(const Board &board, Move &moved)
{
    auto b0 = board.clone();
    b0.undoMove();
    if (b0.BeingAttacked(moved.from) && !board.BeingAttacked(moved.to))
    {
        return true;
    }
    return false;
}

moveVec_t _simulate_jjdz(const Board &board, const Color &player, const Move &dui)
{
    JdzSimulator simulator(board, player);
    // 排除兑的影响
    simulator.set_not_allowed(dui);
    auto n = simulator.ReasonablePath();
    if (simulator.IsTrue())
    {
        return n->history;
    }
    return {};
}

moveVec_t get_dui_history(const Board &board, const Coord &tgt, Move dui)
{
    Board b2;
    moveVec_t dui_hist;
    auto player = board.next_player();
    if (tgt.on_board() && dui.to == tgt)
    {
        b2 = board.clone();
        b2.SetPlayer(player);
        b2.DoMove(dui);
        auto cands = b2.GetCandidatesForTargetEat(tgt, true);
        for (auto m : cands)
        {
            if (m.is_check())
            {
                // dui_hist = _simulate_jjdz(b2, OPPONENT(player), EMPTY_MOVE, m);
                dui_hist = _simulate_jjdz(b2, OPPONENT(player), EMPTY_MOVE);
            }
            else
            {
                dui_hist = _simulate_cdz(b2, OPPONENT(player), EMPTY_MOVE, tgt);
            }
            if (!dui_hist.empty())
            {
                return get_dui_path(dui, dui_hist);
            }
        }
        // b2.show_board(true, "兑子开始棋局");
        // fmt::print("移动 {} 兑历史: {}\n", dui, dui_hist);
    }
    return {};
}

bool _has_strong_piece_to_eat(const Board &board, const Color &player)
{
    // board.show_board(true, "应将后是否有强子可吃");
    auto b1 = board.clone();
    auto oppo = OPPONENT(player);
    b1.SetPlayer(oppo);
    auto cands = b1.GetCandidatesByPlayer(oppo, true);
    bool checked;
    // 检查无论对手如何应将，player都一定会有机会吃到强子
    for (auto m : cands)
    {
        b1.DoMove(m);
        checked = false;
        auto eats = b1.GetCandidatesForEat(player, true);
        for (auto e : eats)
        {
            // 注意需要排除目标为将、帅
            if (is_strong_piece(e.info.tgt.piece) || b1.IsCrossRiverPawn(e.to))
            {
                // b1.show_board(true, e.toString());
                checked = true;
                break;
            }
        }
        if (!checked)
        {
            return false;
        }
        b1.undoMove();
    }
    return true;
}

void mark_xian(const Board &board, Move &moved, bool &ended)
{
    if (ended)
    {
        return;
    }
    // auto player = OPPONENT(board.next_player());
    auto prev = board.get_previous_move();
    // 如果上一步将军，本次移动为帅、将，移动本身默认为闲，退出
    auto case1 = prev.info.move_t == MoveType::JIANG && moved.info.src.piece == PieceType::KING;
    if (case1)
    {
        mark_xian_flag(moved, ended);
        return;
    }
}

void mark_jj(const Board &board, Move &moved, bool &ended)
{
    auto current_player = OPPONENT(board.int_next_player());
    if (board.IsCheck(current_player))
    {
        moved.info.move_t = MoveType::JIANG;
        ended = true;
    }
}

void mark_dui(const Board &board, Move &moved, bool &ended, const Coord &c, Move dui)
{
    if (ended)
    {
        return;
    }
    // 不存在有效的兑坐标
    if (c.off_board())
    {
        return;
    }
    auto hist_dui = get_dui_history(board, c, dui);
    if (!hist_dui.empty())
    {
        assertm(hist_dui.size() == 2, "兑序列长度应为2");
        // 标记为`捉`，则标记为兑，结束
        moved.info.move_t = MoveType::DUI;
        // 暂时不能结束
        ended = false;
        // 进一步检查是否存在其他棋子可捉兑坐标棋子 参考图 图49-4
        if (board.NumberOfAttacked(dui.from) >= 3)
        {
            auto eats = board.GetCandidatesForTargetEat(dui.from, true);
            for (auto e : eats)
            {
                if (e == dui.FT() || e.from == hist_dui[1].from)
                {
                    continue;
                }
                mark_zhuo_flag(board, moved, ended, {e});
                return;
            }
        }
    }
    // 当不存在兑时，直接返回
    else
    {
        return;
    }

    auto player = OPPONENT(board.next_player());
    auto b1 = board.clone();
    for (auto &m : hist_dui)
    {
        b1.DoMove(m);
    }

    // 兑后将军，进一步检查将军得子
    // 图30-3 图17-3 兑后将军
    // 第二部分的条件简化将军得子模拟
    if (b1.IsCheck(player) && _has_strong_piece_to_eat(b1, player))
    {
        // 恢复最后一步的将军移动
        auto b2 = b1.clone();
        b2.undoMove();
        // b2.show_board();
        auto jj = hist_dui.back();
        // 完成兑，但排除最后一步将军，以此基础进行将军得子模拟
        // 在已经完成兑的基础上继续将军得子模拟，与兑无关
        // auto hist_jjdz = _simulate_jjdz(b2, player, EMPTY_MOVE, jj);
        auto hist_jjdz = _simulate_jjdz(b2, player, EMPTY_MOVE);
        // 回退的将军可能同时吃子，所以将军得子模拟记录必须要大于其吃子价值，即扣除兑子价值外，有附加增值才算得子
        if (!hist_jjdz.empty() && get_net_gain(hist_jjdz) > get_piece_value(jj.info.tgt))
        {
            // 兑后捉，标记相应信息
            moved.info.move_t = MoveType::ZHUO;
            moved.info.zhuo_src = hist_dui.front().info.tgt;
            moved.info.zhuo_tgt = hist_jjdz.back().info.tgt;
            moved.info.no_root_protected = board.HasRootProtected(hist_jjdz.back().to);
        }
    }

    // 检查**兑后**的杀【注意回退走子方吃回移动，在此基础上模拟】
    // 图29 首着如改走车五平二，因黑方8路车不能离线，判杀
    auto b2 = b1.clone();
    b2.undoMove();
    // b2.show_board();
    if (!hist_dui.empty())
    {
        // b2.show_board(true, "兑杀");
        ShaSimulator simulator_sha(b2, player);
        simulator_sha.set_not_allowed(hist_dui.front().FT());
        if (simulator_sha.IsTrue())
        {
            // fmt::print("兑+杀\n");
            mark_sha_flag(board, moved, ended);
        }
        else
        {
            // 已经检查过兑后捉，且非杀时，结束模拟
            if (moved.info.move_t == MoveType::ZHUO)
            {
                ended = true;
            }
        }
    }
}

void mark_sha(const Board &board, Move &moved, bool &ended, Move dui)
{
    if (ended)
    {
        return;
    }
    auto player = OPPONENT(board.next_player());
    ShaSimulator simulator(board, player);
    if (moved.info.move_t == MoveType::DUI)
    {
        simulator.set_not_allowed(dui);
    }
    if (simulator.IsTrue())
    {
        // auto n = simulator.ReasonablePath();
        // fmt::print("禁止移动 = {} 杀路径 = {}\n", dui.toString(), n->path());
        mark_sha_flag(board, moved, ended);
    }
}

void mark_zhuo_no_root(const Board &board, Move &moved, bool &ended, Move eat)
{
    if (ended)
    {
        return;
    }
    auto player = OPPONENT(board.next_player());
    // 注意：需要检查吃后是否导致新增相关吃
    auto b2 = board.clone();
    b2.SetPlayer(player);
    b2.SimulateMove(eat);
    // 吃后非将军 图 03-2
    // 参考图26-2 移动前后都可捉无根保护的象，但非相关吃。车、炮移动前可吃已经剔除
    if (!eat.is_check())
    {
        auto related = related_eat_after_moved(b2, true);
        if (related.empty())
        {
            mark_zhuo_flag(board, moved, ended, {eat});
        }
    }
}

void mark_zhuo_cut_root(const Board &board, Move &moved, bool &ended, moveVec_t related)
{
    // 断根捉子前提条件：不存在相关吃
    if (ended || !related.empty())
    {
        return;
    }
    // 当不存在相关吃时的捉，检查是否存在断根捉子
    auto eat = get_cut_root_eat(board);
    if (eat.IsValid())
    {
        mark_zhuo_flag(board, moved, ended, {eat});
    }
}

void _zhuo_avoid_eated(const Board &board, Move &moved, bool &ended, moveVec_t related)
{
    if (ended || !related.empty())
    {
        return;
    }
    auto b0 = board.clone();
    b0.undoMove();
    bool a0 = b0.NumberOfAttacked(moved.from);
    bool a1 = board.NumberOfAttacked(moved.to);
    // 避开攻击
    if (a1 < a0)
    {
        auto player = OPPONENT(board.next_player());
        auto eats = board.GetCandidatesForEat(player, true);
        std::set<Coord> tgts;
        for (auto m : eats)
        {
            if (contains(related, m))
            {
                continue;
            }
            if (board.NotCrossRiverPawn(m.to))
            {
                continue;
            }
            tgts.insert(m.to);
        }
        for (auto tgt : tgts)
        {
            auto hist = _simulate_cdz(board, player, EMPTY_MOVE, tgt);
            if (!hist.empty())
            {
                mark_zhuo_flag(board, moved, ended, hist);
                return;
            }
        }
    }
}

void mark_zhuo_avoid_killed(const Board &board, Move &moved, bool &ended, const moveVec_t &related)
{
    if (ended)
    {
        return;
    }
    if (!((related.empty() && is_pk_move(moved)) || !is_pk_move(moved)))
    {
        return;
    }
    moveVec_t hist;
    auto player = OPPONENT(board.next_player());
    auto b0 = board.clone();
    b0.undoMove();
    auto old_eats = b0.GetCandidatesForEat(player, true);
    auto eats = board.GetCandidatesForEat(player, true);
    // 按目标价值排序【从大到小】
    std::stable_sort(eats.begin(), eats.end(), [](const Move &lhs, const Move &rhs)
                     { return get_piece_value(lhs.info.tgt) > get_piece_value(rhs.info.tgt); });
    std::vector<Coord> tgts;
    for (auto e : eats)
    {
        if (contains(old_eats, e))
        {
            if (!contains(related, e))
            {
                if (!contains(tgts, e.to))
                {
                    tgts.push_back(e.to);
                }
            }
        }
    }
    for (auto tgt : tgts)
    {
        hist = _simulate_cdz(board, player, EMPTY_MOVE, tgt);
        // 图08-2
        // 参考图20-4
        // 必须限定真正意义上的得子 参考图 25-4 兑后被杀
        if (!hist.empty() && get_net_gain(hist) > WEAK_VALUE)
        {
            // 吃后将被杀，证明为避杀得子
            auto eat = hist[0];
            if (is_be_killed(board, player, eat))
            {
                mark_zhuo_flag(board, moved, ended, {eat});
                break;
            }
        }
    }
}

void mark_zhuo_jjdz(const Board &board, Move &moved, bool &ended, const Move &dui, const moveVec_t &related, const moveVec_t &cands)
{
    if (ended)
    {
        return;
    }
    auto player = OPPONENT(board.next_player());
    auto hist = _simulate_jjdz(board, player, dui);
    if (!hist.empty())
    {
        // 首先检查应将
        if (is_response_jj_xian(board, moved, hist))
        {
            mark_xian_flag(moved, ended);
        }
        // 将军得子是`moved`移动的直接结果
        else if (is_participated(related, hist))
        {
            mark_zhuo_flag(board, moved, ended, hist);
        }
        else if (is_jj_related(board, moved, hist, cands))
        {
            mark_zhuo_flag(board, moved, ended, hist);
        }
        else
        {
            // 图 05-1 红方退车前就可吃底士，退车后吃士结果没有发生变化 判闲
            auto before = get_zhuo_objects_before_moved(board);
            if (_is_same_dz(before, hist))
            {
                moved.info.z2x = true;
                // 结束模拟
                ended = true;
            }
            else
            {
                mark_zhuo_flag(board, moved, ended, hist);
            }
        }
    }
}

void mark_zhuo_not_related_chi(const Board &board, Move &moved, bool &ended, const Move &dui_eat, const moveVec_t &related_eats)
{
    if (ended)
    {
        return;
    }
    auto player = OPPONENT(board.next_player());
    // 此处须使用所有相关移动组，比较出最优
    ChiSimulator simulator(board, player);
    simulator.set_not_allowed(dui_eat);
    // 排除已经检查过的相关吃
    simulator.set_checked_start_moves(related_eats);
    auto chi = simulator.ReasonablePath();
    auto path = simulator.ReasonablePath(false);
    if (simulator.IsTrue())
    {
        auto hist = chi->history;
        auto first = hist.front();
        auto prev = board.get_previous_move();
        // 参考图图34-3 移动上一着被捉对象，证明相关
        if (board.steps() >= 2 && prev.info.chs && prev.info.move_t == MoveType::ZHUO)
        {
            if (prev.info.zhuo_tgt.coord == moved.from)
            {
                mark_zhuo_flag(board, moved, ended, hist);
                return;
            }
        }
        if (is_response_jj_xian(board, moved, hist))
        {
            // 参考图22-4
            mark_xian_flag(moved, ended);
            return;
        }
        if (is_participated(moved.to, path->history))
        {
            mark_zhuo_flag(board, moved, ended, hist);
        }
        else
        {
            if (is_avoid_eat(board, moved))
            {
                if (hist.size() == 1)
                {
                    // 图11-1 图11-3 避吃、联合捉、假根
                    if (first.info.is_jointed && board.IsFakeRootProtected(first.to))
                    {
                        mark_zhuo_flag(board, moved, ended, hist);
                        return;
                    }
                    if (board.steps() >= 3)
                    {
                        // 参考图21-4 红马被黑车捉的状态，是红方自己造成的，与moved无关，判闲
                        auto b00 = board.clone();
                        b00.undoNSteps(2);
                        // 参考图21-4 对手本身造成
                        if (b00.NumberOfProtected(hist.front().to) >= 1 && board.NumberOfProtected(hist.front().to) == 0)
                        {
                            mark_xian_flag(moved, ended);
                            return;
                        }
                    }
                    // 图12-2 图12-4 避吃、吃其他无根子
                    if (!board.HasRootProtected(first))
                    {
                        mark_zhuo_flag(board, moved, ended, hist);
                        return;
                    }
                }
                // 参考图图37-2 37-4 如果移除所动之子，依旧可得子，但被捉对象减少保护数量
                auto b0 = board.clone();
                b0.ClearPiece(moved.to);
                if (b0.NumberOfProtected(hist.back().to) < board.NumberOfProtected(hist.back().to))
                {
                    ChiSimulator simulator0(b0, player);
                    if (hist.size() % 2 == 1)
                    {
                        // 设置捉目标
                        simulator0.set_target(hist.back().to);
                    }
                    simulator0.set_not_allowed(dui_eat);
                    // 排除已经检查过的相关吃
                    simulator0.set_checked_start_moves(related_eats);
                    auto chi0 = simulator0.ReasonablePath();
                    if (simulator0.IsTrue())
                    {
                        auto hist0 = chi0->history;
                        // 回退一步同样得子，证明无关
                        if (get_net_gain(hist0) == get_net_gain(hist))
                        {
                            mark_xian_flag(moved, ended);
                            return;
                        }
                    }
                }
            }
        }
        auto b0 = board.clone();
        b0.undoMove();
        // 原本就存在
        if (path->history.size() == 1 && !hist.front().info.is_jointed)
        {
            auto zhuo = hist.back();
            // 参考图图47-1 车受到攻击 证明相关，判捉
            if (b0.NumberOfAttacked(zhuo.from) <= 0)
            {
                auto eats = b0.GetCandidatesForEat(player, true);
                if (contains(eats, zhuo))
                {
                    mark_xian_flag(moved, ended);
                    return;
                }
            }
        }
        else
        {
            ChiSimulator simulator0(b0, player);
            if (hist.size() % 2 == 1)
            {
                // 设置捉目标
                simulator0.set_target(hist.back().to);
            }
            simulator0.set_not_allowed(dui_eat);
            // 排除已经检查过的相关吃
            simulator0.set_checked_start_moves(related_eats);
            auto chi0 = simulator0.ReasonablePath();
            // 原本存在的捉与最后移动无关：即回退一步也可得
            // 参考图图6-2
            if (simulator0.IsTrue())
            {
                auto hist0 = chi0->history;
                // 回退一步同样得子，证明无关
                if (get_net_gain(hist0) == get_net_gain(hist))
                {
                    mark_xian_flag(moved, ended);
                    return;
                }
            }
        }
        mark_zhuo_flag(board, moved, ended, hist);
    }
}

void mark_zhuo_related_chi(const Board &board, Move &moved, bool &ended, const Move &dui_eat, const moveVec_t &related_eats)
{
    if (ended)
    {
        return;
    }
    auto player = OPPONENT(board.next_player());
    auto tgt = get_common_attack(board, moved);
    // 此处须使用所有相关移动组，比较出最优
    ChiSimulator simulator(board, player);
    if (tgt.on_board())
    {
        // 相关吃已经按照吃子价值降序排列
        for (auto e : related_eats)
        {
            if (board.GetPiecesInfo(e.to) > board.GetPiecesInfo(tgt))
            {
                tgt = e.to;
                break;
            }
        }
    }
    // 只有目标为强子时才有效
    if (tgt.on_board() && board.GetPiecesInfo(tgt) >= STRONG_VALUE)
    {
        simulator.set_target(tgt);
    }
    // 当不存在共同攻击目标，且相关吃为空时，直接退出
    else if (related_eats.empty())
    {
        return;
    }
    simulator.set_start_moves(related_eats);
    simulator.set_not_allowed(dui_eat);
    auto chi = simulator.ReasonablePath();
    if (simulator.IsTrue())
    {
        auto hist = chi->history;
        mark_zhuo_flag(board, moved, ended, hist);
    }
}

void mark_zhuo_chi_jjdz(const Board &board, Move &moved, bool &ended, moveVec_t related, Move dui)
{
    // 当此前标注为闲时才执行
    if (moved.info.move_t == MoveType::XIAN)
    {
        bool is_dz = false;
        std::vector<moveVec_t> paths;
        moveVec_t path;
        for (auto &m : related)
        {
            if (m != dui)
            {
                auto b1 = board.clone();
                auto player = OPPONENT(board.next_player());
                b1.SetPlayer(player);
                b1.DoMove(m);
                // 对手吃回
                auto eat_backs = b1.GetCandidatesForTargetEat(m.to, true);
                if (!eat_backs.empty())
                {
                    for (auto eb : eat_backs)
                    {
                        b1.DoMove(eb);
                        auto hist = _simulate_jjdz(b1, player, dui);
                        if (!hist.empty())
                        {
                            path.clear();
                            path.push_back(m);
                            path.push_back(eb);
                            path.front().info.is_jointed = hist.front().info.is_jointed;
                            path.insert(path.end(), hist.begin(), hist.end());
                            // fmt::print("{}\n", path);
                            paths.push_back(path);
                        }
                        b1.undoMove();
                    }
                }
            }
            // 当相关吃中存在任一路径，无论对手如何应对，都可得子时，结束
            // 参考图 34 黑方应该继续将军得车
            if (!paths.empty() && std::all_of(paths.begin(), paths.end(), [](const moveVec_t &p)
                                              { return is_path_dezi(p); }))
            {
                is_dz = true;
                break;
            }
        }
        if (is_dz)
        {
            auto r_path = *std::min_element(paths.begin(), paths.end(), [](const moveVec_t &h1, const moveVec_t &h2)
                                            { return get_net_gain(h1) < get_net_gain(h2); });

            moved.info.chs = true;
            if (!is_only_one_zhuo(r_path))
            {
                r_path.front().info.is_jointed = true;
            }
            mark_zhuo_flag(board, moved, ended, r_path);
        }
    }
}

bool is_jj_first(const Board &board, Move &moved, const moveVec_t &cands, const moveVec_t &related, Move dui)
{
    // 不存在相关吃 图02-3
    auto tgt = get_common_attack(board, moved);
    if (related.empty() && tgt.off_board())
    {
        return true;
    }
    // 相关吃中存在吃同时将军时 图03-2
    for (auto m : related)
    {
        if (m == dui)
        {
            continue;
        }
        if (m.is_check() && m.is_eat() && !board.HasRootProtected(m))
        {
            return true;
        }
    }
    // 移动候选中存在非吃移动，走后其他子将军 图09-2
    for (auto m : cands)
    {
        if (m == dui)
        {
            continue;
        }
        if (m.is_jointed_check() && !m.is_eat())
        {
            return true;
        }
    }
    return false;
}

Move get_can_not_offline_eat(const Board &board, const moveVec_t &cands)
{
    Move move = EMPTY_MOVE;
    for (auto m : cands)
    {
        if (m.is_eat() && can_not_offline(board, m.to))
        {
            return m;
        }
    }
    return move;
}

Move get_noroot_eat(const Board &board, const moveVec_t &cands, moveVec_t related, const Move &dui)
{
    // 参考图图39-3 走车避吃，但原本就在可捉不得离线的车
    Move move = EMPTY_MOVE;
    for (auto &m : related)
    {
        if (m == dui)
        {
            continue;
        }
        // 此处务必适用未执行的移动测试根保护
        if (!board.HasRootProtected(m) && get_piece_value(m.info.tgt) >= WEAK_VALUE && !board.immediately_loss_once_moved(m))
        {
            move = m;
            break;
        }
    }
    // 二次检索
    if (move.IsValid() && move.info.src.piece == PieceType::KING)
    {
        for (auto &m : related)
        {
            if (m == dui || m == move)
            {
                continue;
            }
            // 在相关吃中，同等条件下，优先非帅、兵捉无根子
            if (get_piece_value(m.info.tgt) >= get_piece_value(move.info.tgt))
            {
                // 此处务必适用未执行的移动测试根保护
                if (!board.HasRootProtected(m) && !board.immediately_loss_once_moved(m))
                {
                    move = m;
                    break;
                }
            }
        }
    }
    auto eat = get_can_not_offline_eat(board, cands);
    if (eat.IsValid() && get_piece_value(eat.info.tgt) > get_piece_value(move.info.tgt))
    {
        return EMPTY_MOVE;
    }
    else
    {
        return move;
    }
}

void mark_zhuo(const Board &board, Move &moved, bool &ended, moveVec_t related, Move dui)
{
    if (ended)
    {
        return;
    }

    // 完成兑、杀检查后，对已经标记为兑且相关吃只有`兑`时，无需再检查
    if (moved.info.move_t == MoveType::DUI && related.size() == 1 && contains(related, dui))
    {
        ended = true;
        return;
    }

    auto player = OPPONENT(board.next_player());
    auto cands = board.GetCandidatesByPlayer(player);

    // 相关吃为空时，首先检测断根捉子、然后将军捉子
    if (related.empty())
    {
        // 断根捉子
        mark_zhuo_cut_root(board, moved, ended, related);
    }

    // 参考图 14-4 车可捉无根马 必须优先将军得车模拟，否则错误形成捉马结论
    if (is_jj_first(board, moved, cands, related, dui))
    {
        // fmt::print("将军得子模拟优先\n");
        mark_zhuo_jjdz(board, moved, ended, dui, related, cands);
    }

    // 避杀捉子
    // 图08-2 参考图20-4
    mark_zhuo_avoid_killed(board, moved, ended, related);

    // 捉无根子【先执行避杀，然后处理无根子】
    // 图08-1 由于互吃模拟没有考虑对手吃后导致被杀的情形，无法得到期望结果。直接使用吃无根子
    // 参考图39-3 如先执行捉无根子，则会判捉象，忽略了捉黑方不能离线的车
    if (!ended)
    {
        auto eat = get_noroot_eat(board, cands, related, dui);
        if (eat.IsValid())
        {
            mark_zhuo_no_root(board, moved, ended, eat);
        }
    }

    mark_zhuo_related_chi(board, moved, ended, dui, related);

    if (!is_pk_move(moved))
    {
        // 将相关吃排除，检验其他有效吃，以此为基础进行互吃模拟得子
        mark_zhuo_not_related_chi(board, moved, ended, dui, related);
    }

    // 吃、吃回、将军得子
    mark_zhuo_chi_jjdz(board, moved, ended, related, dui);
}

void mark_move(Board &board, Move &moved)
{
    helper::MyClock clock;
    clock.restart();

    auto related = related_eat_after_moved(board, false);
    auto dui_move = get_dui_move(board);
    auto dui_coord = get_dui_coord(board);

    bool ended = false;
    // 默认为闲
    moved.info.move_t = MoveType::XIAN;

    // 注意：以下判定顺序不能变
    clock.setStartPoint();
    mark_xian(board, moved, ended);
    clock.record(fmt::format("标记闲({})，用时", moved));

    clock.setStartPoint();
    mark_jj(board, moved, ended);
    clock.record(fmt::format("标记将({})，用时", moved));

    clock.setStartPoint();
    mark_dui(board, moved, ended, dui_coord, dui_move);
    clock.record(fmt::format("标记兑({})，用时", moved));

    clock.setStartPoint();
    mark_sha(board, moved, ended, dui_move.FT());
    clock.record(fmt::format("标记杀({})，用时", moved));

    clock.setStartPoint();
    mark_zhuo(board, moved, ended, related, dui_move.FT());
    clock.record(fmt::format("标记捉({})，用时", moved));

    if (USE_DEBUG)
    {
        fmt::print("{}\n\n", clock.summary());
    }

    // 完成类型标记
    moved.info.marked = true;
    board.MarkLastMove(moved);
}

std::vector<std::vector<size_t>> get_combination_idx(size_t n)
{
    std::vector<size_t> seq;
    std::set<size_t> nums;
    std::vector<std::vector<size_t>> idx;
    size_t a, b;
    for (size_t i = 0; i < n; i++)
    {
        seq.push_back(i);
    }
    do
    {
        a = seq[0];
        b = seq[1];
        if (!contains(nums, a + b))
        {
            idx.push_back({a, b});
        }
        nums.insert(a + b);
    } while (std::next_permutation(seq.begin(), seq.end()));
    return idx;
}

bool is_prohibit_group(const Move &one, const Move &two)
{
    // 长将
    if (one.info.move_t == MoveType::JIANG && two.info.move_t == MoveType::JIANG)
    {
        return true;
    }
    // 长杀
    else if (one.info.move_t == MoveType::SHA && two.info.move_t == MoveType::SHA)
    {
        return true;
    }
    // 长捉
    else if (one.info.move_t == MoveType::ZHUO && two.info.move_t == MoveType::ZHUO)
    {
        return true;
    }
    // 一将一杀
    else if ((one.info.move_t == MoveType::JIANG && two.info.move_t == MoveType::SHA) ||
             (one.info.move_t == MoveType::SHA && two.info.move_t == MoveType::JIANG))
    {
        return true;
    }
    // 一将一捉
    else if ((one.info.move_t == MoveType::JIANG && two.info.move_t == MoveType::ZHUO) ||
             (one.info.move_t == MoveType::ZHUO && two.info.move_t == MoveType::JIANG))
    {
        return true;
    }
    // 一杀一捉
    else if ((one.info.move_t == MoveType::SHA && two.info.move_t == MoveType::ZHUO) ||
             (one.info.move_t == MoveType::ZHUO && two.info.move_t == MoveType::SHA))
    {
        return true;
    }
    return false;
}

bool is_prohibit_group(const moveVec_t &moves)
{
    auto idx = get_combination_idx(moves.size());
    for (auto p : idx)
    {
        // 分解为2个一组逐对检查
        if (!is_prohibit_group(moves.at(p[0]), moves.at(p[1])))
        {
            return false;
        }
    }
    return true;
}

bool is_r9moves(const moveVec_t &moves)
{
    if (moves.size() != 9)
    {
        return false;
    }
    std::set<Coord> locs;
    bool all_f = is_prohibit_group(moves);
    std::for_each(moves.begin(), moves.end(), [&](const Move &m)
                  { locs.insert(m.to); });
    return moves.size() == 9 && all_f && locs.size() >= 3;
}

bool should_change(const Move &one, const Move &two)
{
    // 凡单方长杀
    if (one.info.move_t == MoveType::SHA && two.info.move_t == MoveType::SHA)
    {
        return true;
    }
    // 一将一杀
    else if (one.info.move_t == MoveType::JIANG || two.info.move_t == MoveType::SHA)
    {
        return true;
    }
    // 长捉车
    else if (one.info.zhuo_tgt.piece == PieceType::ROOK && two.info.zhuo_tgt.piece == PieceType::ROOK)
    {
        return true;
    }
    // 长捉无根子
    else if (one.info.no_root_protected && two.info.no_root_protected)
    {
        return true;
    }
    // 一将(杀)一捉车(无根子)
    else if (((one.info.move_t == MoveType::JIANG || one.info.move_t == MoveType::SHA) &&
              (two.info.zhuo_tgt.piece == PieceType::ROOK || two.info.no_root_protected)) ||
             ((two.info.move_t == MoveType::JIANG || two.info.move_t == MoveType::SHA) &&
              (one.info.zhuo_tgt.piece == PieceType::ROOK || one.info.no_root_protected)))
    {
        return true;
    }
    // 一捉车、一捉无根子
    else if ((one.info.zhuo_tgt.piece == PieceType::ROOK && two.info.no_root_protected) ||
             (two.info.zhuo_tgt.piece == PieceType::ROOK && one.info.no_root_protected))
    {
        return true;
    }
    return false;
}

bool should_change(const moveVec_t &moves)
{
    auto idx = get_combination_idx(moves.size());
    for (auto p : idx)
    {
        // 分解为2个一组逐对检查
        if (!should_change(moves.at(p[0]), moves.at(p[1])))
        {
            return false;
        }
    }
    return true;
}

moveVec_t get_gamer_history(const moveVec_t &moves, bool first)
{
    moveVec_t former, latter;
    size_t i = 0;
    for (const auto &m : moves)
    {
        i += 1;
        if (i % 2 == 1)
        {
            former.push_back(m);
        }
        else
        {
            latter.push_back(m);
        }
    }
    if (first)
    {
        return former;
    }
    else
    {
        return latter;
    }
}

Result adjudicate(const moveVec_t &moves)
{
    assertm(moves.size() % 2 == 0, "moves.size() 应为偶数");
    auto former = get_gamer_history(moves, true);
    auto latter = get_gamer_history(moves, false);
    if (former.size() == 9 && latter.size() == 9)
    {
        auto f9_ = is_r9moves(former);
        auto l9_ = is_r9moves(latter);
        if (f9_ && !l9_)
        {
            return -1;
        }
        else if (!f9_ && l9_)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        auto f_p = is_prohibit_group(former);
        auto l_p = is_prohibit_group(latter);
        if (f_p && !l_p)
        {
            return -1;
        }
        else if (!f_p && l_p)
        {
            return 1;
        }
        else if (!f_p && !l_p)
        {
            return 0;
        }
        else
        {
            auto f_ = should_change(former);
            auto l_ = should_change(latter);
            if (f_ && !l_)
            {
                return -1;
            }
            else if (!f_ && l_)
            {
                return 1;
            }
            else
            {
                // 26.9.2 凡单方长捉车，对方联合捉车，前者变着。
                // 26.9.3 凡单方长捉无根子，对方联合捉无根子，前者变着。
                // auto all_zhuo = std::all_of(moves.begin(), moves.end(), [](const auto &m)
                //                             { return m.info.move_t == MoveType::ZHUO; });
                // if (all_zhuo)
                // {
                // 前者有任一为联合捉
                auto f_j = std::any_of(former.begin(), former.end(), [](const auto &m)
                                       { return m.info.move_t == MoveType::ZHUO && m.info.is_jointed; });
                // 后者有任一为联合捉
                auto l_j = std::any_of(latter.begin(), latter.end(), [](const auto &m)
                                       { return m.info.move_t == MoveType::ZHUO && m.info.is_jointed; });

                // 根据案例调整，如一方联合捉，非联合捉变着
                if (!f_j && l_j)
                {
                    return -1;
                }
                // 图 25 红方联合捉、黑长捉车，黑方变着【并没有限定红方捉对象为车】
                else if (f_j && !l_j)
                {
                    return 1;
                }
                // }
            }
        }
    }
    return 0;
}

Result adjudicate(const moveVec_t &moves, Color starter)
{
    auto res = adjudicate(moves);
    int sign = starter == S_RED ? 1 : -1;
    return sign * res;
}

XqBoard XqBoard::clone() const
{
    XqBoard b2;
    b2._infos = _infos;
    b2._hash = _hash;
    b2._hash_keys = _hash_keys;
    b2._moves_history = _moves_history;
    b2._next_player = _next_player;
    b2._ply = _ply;
    b2._no_eat = _no_eat;
    b2._result = _result;
    b2._mark_flag = _mark_flag;
    return b2;
}

bool XqBoard::is_continue_mark()
{
    auto recent = get_last_moves(18);
    auto former = get_gamer_history(recent, true);
    auto latter = get_gamer_history(recent, false);
    // 双方都含已经标注过的闲时，退出
    if (std::any_of(former.begin(), former.end(), [](const Move &m)
                    { return m.info.marked && m.info.move_t == MoveType::XIAN; }) &&
        std::any_of(latter.begin(), latter.end(), [](const Move &m)
                    { return m.info.marked && m.info.move_t == MoveType::XIAN; }))
    {
        return false;
    }
    return true;
}

void XqBoard::on_over_18_steps()
{
    auto s = _moves_history.size();
    auto recent = get_last_moves(18);
    // 含吃移动时，退出
    if (std::any_of(recent.begin(), recent.end(), [](const Move &m)
                    { return m.is_eat(); }))
    {
        return;
    }
    for (auto i = 0; i < 18; i++)
    {
        Board b2 = this->clone();
        if (is_continue_mark())
        {
            if (i >= 1)
            {
                b2.undoNSteps(i);
            }
            auto move = recent[18 - i - 1];
            if (!move.info.marked)
            {
                mark_move(b2, move);
                mark_moved_type(move, s - i - 1);
            }
        }
        else
        {
            // 只有双方都含确认的闲类型，就可退出标注
            break;
        }
    }
    // 使用更新后的历史
    recent = get_last_moves(18);
    auto former = get_gamer_history(recent, true);
    auto latter = get_gamer_history(recent, false);
    auto f_p = is_prohibit_group(former);
    auto l_p = is_prohibit_group(latter);
    if (f_p || l_p)
    {
        _result = adjudicate(recent, next_player());
        _s_reason = fmt::format("{}三点连续交替重复", _result == RED_WIN ? "黑方" : "红方");
    }
}

void XqBoard::step(Move &move)
{
    if (_result != 2)
    {
        auto msg = fmt::format("执行移动({})，但游戏已经结束", move.toString());
        on_board_error(msg);
        // throw std::runtime_error(msg);
    }
    // 走子
    DoMove(move);
    if (_result == 2)
    {
        if (_ply > 18 && _mark_flag)
        {
            on_over_18_steps();
        }
        auto t = repetition_size();
        size_t times = MAX_NUM_VIOLATION;
        bool repeat = true;
        if (!_mark_flag)
        {
            // 当不使用规则判断时，谁率先导致重复局面三次，且此前二轮双方着法反复二次
            if (is_multi_repetitive(t, times - 1) && _ply >= 10)
            {
                auto last_m = this->get_last_moves(5).front();
                auto last_9 = this->get_last_moves(9);
                for (size_t i = 0; i < 4; i++)
                {
                    if (last_9[i] != last_9[i + 4])
                    {
                        repeat = false;
                        break;
                    }
                }
                // if (last_m == move && repeat)
                // {
                //     // 当实行简单规则时，谁先重复即负
                //     _reason = B_FinishReason::FR_MAX_REPEATION;
                //     this->_result = this->_next_player == S_RED ? RED_WIN : RED_LOSE;
                //     _s_reason = fmt::format("{}三次重复", _result == RED_WIN ? "黑方" : "红方");
                // }
                if (last_m == move && repeat)
                {
                    // 当实行简单规则时，重复即判和，游戏结束
                    _reason = B_FinishReason::FR_MAX_REPEATION;
                    this->_result = DRAW;
                    _s_reason = fmt::format("{}三次重复", _result == RED_WIN ? "黑方" : "红方");
                }
            }
        }
        else
        {
            // 局面重复三次，最近12着反复三次
            if (is_multi_repetitive(t, times) && _ply >= 13)
            {
                auto last_12 = this->get_last_moves(12);
                // 检查最近12着是否重复三次
                for (size_t i = 0; i < 4; i++)
                {
                    if ((last_12[i] != last_12[i + 4]) || (last_12[i + 4] != last_12[i + 8]))
                    {
                        repeat = false;
                        break;
                    }
                }
                if (repeat)
                {
                    on_repeat(t, times);
                }
            }
        }
    }
}

void XqBoard::step(const int move_id)
{
    Move move = make_move(I2M.at(move_id));
    step(move);
}

void XqBoard::step(const std::string move_str)
{
    Move move = make_move(move_str);
    step(move);
}

void XqBoard::step(int x1, int y1, int x2, int y2)
{
    Move move = make_move(fmt::format("{}{}{}{}", x1, y1, x2, y2));
    step(move);
}

void XqBoard::on_repeat(size_t t, size_t /*times*/)
{
    auto recent = get_last_moves(t);
    // fmt::print("XqBoard::on_repeat {} times = {}\n", recent, times);

    Board b2 = this->clone();
    b2.undoNSteps(t);
    for (auto &move : recent)
    {
        b2.DoMove(move);
        if (!move.info.marked)
        {
            mark_move(b2, move);
        }
    }
    // 按规则判断最终结果，应变着而不变着者负
    _result = adjudicate(recent, b2.next_player());
    if (_result == 0)
    {
        _s_reason = "双方不变判和";
    }
    else
    {
        _s_reason = fmt::format("{}应变着，不变判负", _result == RED_WIN ? "黑方" : "红方");
    }
}