#include "board_utils.hpp"

namespace rule2022
{

    bool is_strong_piece(PieceType t)
    {
        return t == PieceType::ROOK || t == PieceType::HORSE || t == PieceType::CANNON;
    }

    bool is_cjdz(const Board &board)
    {
        if (board.steps() <= 3)
        {
            return false;
        }
        // auto player = OPPONENT(board.next_player());
        auto seq = board.get_last_moves(3);
        auto first = seq.front();
        auto eat = seq.back();
        auto b0 = board.clone();
        b0.undoNSteps(3);
        // auto cands_0 = board.GetCandidatesByPlayer(player, true);
        auto is_exist = b0.HasPiece(eat.info.tgt);
        // 第一步将军、最后一步吃
        // 吃移动的棋子为将军移动所提之子，即吃移动开始坐标为将军移动的目标坐标
        // 所吃子原本就在最初的棋盘上【非填将产生】
        // 满足以上条件，即抽将吃子
        // return first.is_check() && eat.is_eat() && !contains(cands_0, eat) && is_exist;
        return first.is_check() && eat.is_eat() && eat.from == first.to && is_exist;
    }

    bool is_jdz_sequence(const moveVec_t &hist, const Move &cand)
    {
        if (hist.empty())
        {
            // 本应该限定将军，但部分直接输入的移动会出错
            // 放宽 true
            return true;
        }
        auto t = hist.size();
        // 如尾部二项都仅仅为吃而非将，候选如非吃，组合无效。即进入互吃阶段
        // 限制双方
        if (t >= 2)
        {
            auto first = hist[t - 2];
            auto second = hist[t - 1];
            if (first.is_eat() && !first.is_check() && second.is_eat() && !second.is_check() && !cand.is_eat())
            {
                return false;
            }
        }
        // 先手限制
        if (t % 2 == 0)
        {
            if (t >= 2)
            {
                auto first = hist[t - 2];
                // 先手非将后不得再将【将军同时吃例外】
                if (!first.is_check() && cand.is_check() && !cand.is_eat())
                {
                    return false;
                }
            }
            if (t >= 4)
            {
                // 先手连续二次将军而不吃子【即前二次将军都没吃子，候选将军组合无效】
                auto first = hist[t - 4];
                auto second = hist[t - 2];
                if (first.is_check() && !first.is_eat() &&
                    second.is_check() && !second.is_eat() &&
                    cand.is_check() && !cand.is_eat())
                {
                    return false;
                }
            }
            // if (t >= 6)
            // {
            //     // 先手连续四次将军而不吃子【即前三次将军都没吃子，候选将军组合无效】
            //     auto first = hist[t - 6];
            //     auto second = hist[t - 4];
            //     auto three = hist[t - 2];
            //     if (first.is_check() && !first.is_eat() &&
            //         second.is_check() && !second.is_eat() &&
            //         three.is_check() && !three.is_eat() &&
            //         cand.is_check() && !cand.is_eat())
            //     {
            //         return false;
            //     }
            // }
        }
        return true;
    }

    moveVec_t related_eat_after_moved(const Board &board, bool for_next_player)
    {
        // 最简版本
        moveVec_t res;
        if (board.steps() < 2)
        {
            return {};
        }
        auto player = OPPONENT(board.next_player());
        if (for_next_player)
        {
            player = OPPONENT(player);
        }
        auto b0 = board.clone();
        b0.undoMove();
        // b0.show_board(true, "回退一步");
        // board.show_board(true, "相关吃");
        auto last = board.get_last_move();
        // 被将军的一方，所有吃都要包含。即不应将前提下的所有吃子
        auto old_eats = b0.GetCandidatesForEat(player, false);
        auto new_eats = board.GetCandidatesForEat(player, true);

        // 务必重新排序
        std::stable_sort(old_eats.begin(), old_eats.end(), [](const Move &a, const Move &b)
                         { return a < b; });
        std::stable_sort(new_eats.begin(), new_eats.end(), [](const Move &a, const Move &b)
                         { return a < b; });

        // 新增部分
        std::set_difference(new_eats.begin(), new_eats.end(),
                            old_eats.begin(), old_eats.end(),
                            std::back_inserter(res));

        // 当价值相等时，优先最后移动
        if (!for_next_player)
        {
            std::stable_sort(res.begin(), res.end(), [=](const Move &lhs, const Move &rhs)
                             { if(get_piece_value(lhs.info.tgt) == get_piece_value(rhs.info.tgt))
                             { 
                                return (lhs.from == last.to) > (rhs.from == last.to);
                             }
                             else
                             {
                                return get_piece_value(lhs.info.tgt) > get_piece_value(rhs.info.tgt);} });
            // 当移动车、炮时，原本可以吃，不列入相关部分
            if (last.info.src.piece == PieceType::ROOK || last.info.src.piece == PieceType::ROOK)
            {
                moveVec_t r_c;
                for (auto e : new_eats)
                {
                    if (e.from == last.to)
                    {
                        Move m{last.from, e.to};
                        if (contains(old_eats, m))
                        {
                            r_c.push_back(e);
                        }
                    }
                }
                // fmt::print("重叠 {}\n", r_c);
                res.erase(std::remove_if(res.begin(), res.end(),
                                         [=](const Move &m)
                                         {
                                             return contains(r_c, m);
                                         }),
                          res.end());
            }
        }
        else
        {
            // 按目标价值排序【从大到小】
            std::stable_sort(res.begin(), res.end(), [](const Move &lhs, const Move &rhs)
                             { return get_piece_value(lhs.info.tgt) > get_piece_value(rhs.info.tgt); });
        }
        return res;
    }

    moveVec_t new_added_eats(const moveVec_t &news, const moveVec_t &olds)
    {
        moveVec_t cands;
        auto old_eats = olds;
        auto new_eats = news;
        // 务必重新排序
        std::stable_sort(old_eats.begin(), old_eats.end(), [](const Move &a, const Move &b)
                         { return a < b; });
        std::stable_sort(new_eats.begin(), new_eats.end(), [](const Move &a, const Move &b)
                         { return a < b; });

        // 新增部分
        std::set_difference(new_eats.begin(), new_eats.end(),
                            old_eats.begin(), old_eats.end(),
                            std::back_inserter(cands));

        // 删除吃将、帅
        cands.erase(std::remove_if(cands.begin(), cands.end(),
                                   [](const Move &m)
                                   {
                                       return m.info.tgt.piece == PieceType::KING;
                                   }),
                    cands.end());

        // 按目标价值排序【从大到小】
        std::stable_sort(cands.begin(), cands.end(), [](const Move &lhs, const Move &rhs)
                         { return get_piece_value(lhs.info.tgt) > get_piece_value(rhs.info.tgt); });

        return cands;
    }

    // moveVec_t eat_checked_cands(const Board &board)
    // {
    //     moveVec_t cands;
    //     auto hist = board.get_last_moves(3);
    //     if (hist.size() == 3)
    //     {
    //         auto first = hist.front();
    //         auto last = hist.back();
    //         if (first.is_check() && last.is_eat() && last.from != first.to)
    //         {
    //             auto player = board.next_player();
    //             auto eats = board.GetCandidatesForEat(player, true);
    //             std::for_each(eats.begin(), eats.end(), [&](const Move &m)
    //                           {if(m.to == first.to){cands.push_back(m);}; });
    //         }
    //     }
    //     return cands;
    // }

    moveVec_t related_dui_moves(Board board)
    {
        moveVec_t res;
        if (board.steps() >= 2)
        {
            auto player = OPPONENT(board.next_player());
            auto opponent = OPPONENT(player);
            auto eats = related_eat_after_moved(board, false);
            auto cands = board.GetCandidatesForEat(player, true);
            for (auto &e : eats)
            {
                auto eats_back = board.CandidatesForEatFrom(opponent, e.to);
                for (auto eb : eats_back)
                {
                    if (get_piece_value(eb.info.tgt) == get_piece_value(e.info.tgt))
                    {
                        auto move = make_move(eb.to.x, eb.to.y, eb.from.x, eb.from.y);
                        if (contains(cands, move) && !contains(res, eb))
                        {
                            res.push_back(eb);
                        }
                    }
                }
            }
        }
        return res;
    }

    // 辅助函数
    Move get_dui_move(const Board &board)
    {
        Move res = EMPTY_MOVE;
        auto next_player = board.next_player();
        auto opponent = OPPONENT(next_player);
        auto cands0 = board.GetCandidatesForEat(next_player, true);
        auto cands1 = board.GetCandidatesForEat(opponent, true);
        auto is_dui = [=](const Move &m)
        { return contains(cands1, m.FT()) && board.GetPiecesInfo(m.from) == board.GetPiecesInfo(m.to); };
        auto result = std::find_if(cands0.begin(), cands0.end(), is_dui);
        if (result != cands0.end())
        {
            auto m = *result;
            if (!board.immediately_loss_once_moved(m))
            {
                res = m;
            }
        }
        return res;
    }

    Coord get_dui_coord(const Board &board)
    {
        auto res = EMPTY_COORD;
        auto last = board.get_last_move();
        if (last.IsValid())
        {
            auto dui = get_dui_move(board);
            if (dui.IsValid())
            {
                // 证明相关
                auto player = board.next_player();
                auto b0 = board.clone();
                b0.undoMove();
                auto cands0 = b0.GetCandidates(player);
                if (!contains(cands0, dui))
                {
                    return dui.to;
                }
                // 兑已经存在
                else
                {
                    auto b2 = board.clone();
                    auto player = board.next_player();
                    b2.SetPlayer(player);

                    // 最后一步促使兑
                    auto eats0 = b2.GetCandidatesForEat(OPPONENT(player), true);
                    auto is_dui0 = [=](const Move &m)
                    { return m.from == last.to && m.to == dui.from; };
                    auto result0 = std::find_if(eats0.begin(), eats0.end(), is_dui0);
                    if (result0 != eats0.end())
                    {
                        return dui.to;
                    }

                    // 最后一步加强兑
                    b2.DoMove(dui);
                    auto eats = b2.GetCandidatesForEat(OPPONENT(player), true);
                    auto is_dui = [=](const Move &m)
                    { return last.to == m.from && m.to == dui.to; };
                    auto result = std::find_if(eats.begin(), eats.end(), is_dui);
                    if (result != eats.end())
                    {
                        return dui.to;
                    }
                }
            }
        }
        return res;
    }

    void sorted_jj_cands(const Board &board, const Color &player, moveVec_t &jjs)
    {
        std::map<Move, int> maps, o_maps;
        moveVec_t responses, eats;
        int v = 0;
        auto b2 = board.clone();
        b2.SetPlayer(player);
        for (auto jj : jjs)
        {
            b2.DoMove(jj);
            responses = b2.GetCandidatesByPlayer(OPPONENT(player));
            o_maps.clear();
            for (auto o : responses)
            {
                b2.DoMove(o);
                if (!b2.is_game_ended())
                {
                    eats = b2.CandidatesForEatFrom(player, jj.to);
                    // 首先设置为将军同时吃子的价值
                    v = get_piece_value(jj.info.tgt);
                    if (!board.HasRootProtected(jj.to))
                    {
                        v *= 2;
                    }
                    // 吃无根子保护的，加倍计算棋子价值
                    for (auto e : eats)
                    {
                        if (e.info.tgt.piece != PieceType::KING)
                        {
                            if (!b2.HasRootProtected(e))
                            {
                                v += 2 * get_piece_value(e.info.tgt);
                            }
                            else
                            {
                                v += get_piece_value(e.info.tgt);
                            }
                        }
                    }
                    o_maps[o] = v;
                }
                b2.undoMove();
            }
            auto it = std::min_element(o_maps.begin(), o_maps.end(), [](auto l, auto r)
                                       { return l.second < r.second; });
            maps[jj] = it->second;
            b2.undoMove();
        }
        std::stable_sort(jjs.begin(), jjs.end(), [&](const Move &l, const Move &r)
                         { return maps[l] > maps[r]; });
    }
}
